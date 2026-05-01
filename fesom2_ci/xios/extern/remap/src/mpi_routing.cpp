#include "mpi_routing.hpp"
#include "mpi.hpp"
#include "node.hpp"
#include "elt.hpp"
#include "timerRemap.hpp"
#include <iostream>

namespace sphereRemap {

const int verbose = 0;

CMPIRouting::CMPIRouting(MPI_Comm comm) : communicator(comm)
{
	MPI_Comm_rank(comm, &mpiRank);
	MPI_Comm_size(comm, &mpiSize);
}

/* sparse alltoallv when it is known that only a subset of ranks will communicate,
    but message lengths are *known* to receiver */
template <typename T>
void alltoalls_known(const vector<vector<T> >& send, vector<vector<T> >& recv, const vector<int>& ranks, MPI_Comm communicator)
{
	vector<MPI_Request> request(ranks.size() * 2);
	vector<MPI_Status>  status(ranks.size() * 2);

	// communicate data
	int nbRequest = 0;
	for (int i = 0; i < ranks.size(); i++)
		if (recv[i].size())
			MPI_Irecv(&recv[i][0], recv[i].size()*sizeof(T), MPI_CHAR, ranks[i], 0, communicator, &request[nbRequest++]);
	for (int i = 0; i < ranks.size(); i++)
		if (send[i].size())
			MPI_Isend((void *) &send[i][0], send[i].size()*sizeof(T), MPI_CHAR, ranks[i], 0, communicator, &request[nbRequest++]);
	MPI_Waitall(nbRequest, &request[0], &status[0]);
}

/* sparse alltoallv when it is known that only a subset of ranks will communicate,
    but message lengths are *unknown* to receiver */
template <typename T>
void alltoalls_unknown(const vector<vector<T> >& send, vector<vector<T> >& recv, const vector<int>& ranks, MPI_Comm communicator)
{
	vector<MPI_Request> request(ranks.size() * 2);
	vector<MPI_Status>  status(ranks.size() * 2);

	// communicate sizes
	int nbRequest = 0;
	vector<int> sendSizes(ranks.size());
	vector<int> recvSizes(ranks.size());
	for (int i = 0; i < ranks.size(); i++)
		sendSizes[i] = send[i].size();
	for (int i = 0; i < ranks.size(); i++)
		MPI_Irecv(&recvSizes[i], 1, MPI_INT, ranks[i], 0, communicator, &request[nbRequest++]);
	for (int i = 0; i < ranks.size(); i++)
		MPI_Isend(&sendSizes[i], 1, MPI_INT, ranks[i], 0, communicator, &request[nbRequest++]);
	MPI_Waitall(nbRequest, &request[0], &status[0]);

	// allocate
	for (int i = 0; i < ranks.size(); i++)
		if (recvSizes[i]) recv[i].resize(recvSizes[i]);
	// communicate data
	alltoalls_known(send, recv, ranks, communicator);
}

void setElementsSendCnt(int route, vector<int>& sendCnt)
{
	sendCnt[route]++;
}

void setElementsSendCnt(const vector<int>& route, vector<int>& sendCnt)
{
	for (int i = 0; i < route.size(); i++)
		sendCnt[route[i]]++;
}

void setTargetElementIndex(int route, vector<int>& indices, const int *rankToIndex)
{
	int index = rankToIndex[route];
	indices.push_back(index);
}

void setTargetElementIndex(const vector<int>& route, vector<int>& indices, const int *rankToIndex)
{
	for (int i = 0; i < route.size(); i++)
	{
		int index = rankToIndex[route[i]];
		indices.push_back(index);
	}
}

template<typename T>
void CMPIRouting::init(const vector<T>& route, CMPICascade *cascade)
{
	vector<int> nbElementSend(mpiSize);
	int *toSend = new int[mpiSize];
	int *recvCount = new int[mpiSize];
	int *targetRankToIndex;

	for (int i = 0; i < route.size(); i++)
		setElementsSendCnt(route[i], nbElementSend);

	nbTarget = 0;
vector<int> destRanks;
	for (int i = 0; i < mpiSize; i++)
	{
		if (nbElementSend[i] == 0)
			toSend[i] = 0;
		else
		{
destRanks.push_back(i);
			toSend[i] = 1;
			nbTarget++;
		}
		recvCount[i] = 1;
	}
//int recvCntDeb = (stree) ? stree->scatter_reduce(destRanks) : -1;

	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::init(reduce_scatter)").reset();
	CTimer::get("CMPIRouting::init(reduce_scatter)").resume();
	MPI_Reduce_scatter(toSend, &nbSource, recvCount, MPI_INT, MPI_SUM, communicator);
	CTimer::get("CMPIRouting::init(reduce_scatter)").suspend();
	CTimer::get("CMPIRouting::init(reduce_scatter)").print();

	MPI_Alloc_mem(nbTarget *sizeof(int), MPI_INFO_NULL, &targetRank);
	MPI_Alloc_mem(nbSource *sizeof(int), MPI_INFO_NULL, &sourceRank);

	targetRankToIndex = new int[mpiSize];
	int index = 0;
	for (int i = 0; i < mpiSize; i++)
	{
		if (toSend[i] == 1)
		{
			targetRank[index] = i;
			targetRankToIndex[i] = index;
			index++;
		}
	}

	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::init(get_source)").reset();
	CTimer::get("CMPIRouting::init(get_source)").resume();

	MPI_Request *request = new MPI_Request[nbSource + nbTarget];
	MPI_Status  *status = new MPI_Status[nbSource + nbTarget];

	int indexRequest = 0;
	if (verbose) cout << "CMPIRouting::init     nbSource : " << nbSource << " nbTarget : " << nbTarget << endl;
//	assert(recvCntDeb == -1 || recvCntDeb == nbSource);
//cout << mpiRank <<  "DEB : " << recvCntDeb << "    nbSource " << nbSource << " nbTarget : " << nbTarget << endl;
	for (int i = 0; i < nbSource; i++)
	{
		MPI_Irecv(&sourceRank[i], 1, MPI_INT, MPI_ANY_SOURCE, 0, communicator, &request[indexRequest]);
		indexRequest++;
	}
	MPI_Barrier(communicator);
	for (int i = 0; i < nbTarget; i++)
	{
		MPI_Isend(&mpiRank, 1, MPI_INT, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}
	MPI_Waitall(indexRequest, request, status);
	MPI_Barrier(communicator);  //needed
	CTimer::get("CMPIRouting::init(get_source)").suspend();
	CTimer::get("CMPIRouting::init(get_source)").print();

	CTimer::get("CMPIRouting::init(get_source)").reset();
	CTimer::get("CMPIRouting::init(get_source)").resume();

	indexRequest = 0;
	for (int i = 0; i < nbSource; i++)
	{
		MPI_Irecv(&sourceRank[i], 1, MPI_INT, MPI_ANY_SOURCE, 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	for (int i = 0; i < nbTarget; i++)
	{
		MPI_Isend(&mpiRank, 1, MPI_INT, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}
	MPI_Waitall(indexRequest, request, status);
	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::init(get_source)").suspend();
	CTimer::get("CMPIRouting::init(get_source)").print();

	CTimer::get("CMPIRouting::init(send_element)").reset();
	CTimer::get("CMPIRouting::init(send_element)").resume();

	nbTargetElement.resize(nbTarget);
	nbSourceElement.resize(nbSource);

	for (int i = 0; i < route.size(); i++)
		setTargetElementIndex(route[i], targetElementIndex, targetRankToIndex);

	for (int i = 0; i < targetElementIndex.size(); i++)
		nbTargetElement[targetElementIndex[i]]++;

	indexRequest = 0;
	totalSourceElement = 0;
	totalTargetElement = 0;
	for (int i = 0; i < nbSource; i++)
	{
		MPI_Irecv(&nbSourceElement[i], 1, MPI_INT, sourceRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	for (int i = 0; i < nbTarget; i++)
	{
		totalTargetElement += nbTargetElement[i];
		MPI_Isend(&nbTargetElement[i], 1, MPI_INT, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	MPI_Waitall(indexRequest, request, status);

	CTimer::get("CMPIRouting::init(send_element)").suspend();
	CTimer::get("CMPIRouting::init(send_element)").print();

	totalSourceElement = 0;
	for (int i = 0; i < nbSource; i++)
		totalSourceElement += nbSourceElement[i];

	sourceElementIndex.resize(totalSourceElement);

	totalSourceElement = 0;
	for (int i = 0; i < nbSource; i++)
	{
		for (int j = 0; j < nbSourceElement[i]; j++)
		{
			sourceElementIndex[totalSourceElement] = i;
			totalSourceElement++;
		}
	}

	delete[]  toSend;
	delete[]  recvCount;
	delete[]  request;
	delete[]  status;
}


int CMPIRouting::getTotalSourceElement(void)
{
	return totalSourceElement;
}

template<typename T>
void CMPIRouting::transferToTarget(T* targetElements, T* sourceElements)
{
	char** targetBuffer = new char*[nbTarget];
	int* indexTargetBuffer = new int[nbTarget];

	for(int i=0;i<nbTarget; i++)
	{
		targetBuffer[i] = new char[sizeof(T)*nbTargetElement[i]];
		indexTargetBuffer[i]= 0;
	}

	char** sourceBuffer = new char*[nbSource];
	int* indexSourceBuffer = new int[nbSource];

	for(int i=0;i<nbSource; i++)
	{
		sourceBuffer[i] = new char[sizeof(T)*nbSourceElement[i]];
		indexSourceBuffer[i]= 0;
	}

	// pack the data
	int index;
	for(int i=0;i<totalTargetElement;i++)
	{
		index=targetElementIndex[i];
		*((T*) &(targetBuffer[index][indexTargetBuffer[index]])) = targetElements[i];
		indexTargetBuffer[index]+=sizeof(T);
	}


	MPI_Request* request=new MPI_Request[nbSource+nbTarget];
	MPI_Status*  status=new MPI_Status[nbSource+nbTarget];
	int indexRequest=0;

	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::transferToTarget").reset();
	CTimer::get("CMPIRouting::transferToTarget").resume();

	for(int i=0; i<nbSource; i++)
	{
		MPI_Irecv(sourceBuffer[i],nbSourceElement[i]*sizeof(T),MPI_CHAR, sourceRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	for(int i=0;i<nbTarget; i++)
	{
		MPI_Isend(targetBuffer[i],nbTargetElement[i]*sizeof(T), MPI_CHAR, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	MPI_Waitall(indexRequest,request,status);

	CTimer::get("CMPIRouting::transferToTarget").suspend();
	CTimer::get("CMPIRouting::transferToTarget").print();
	MPI_Barrier(communicator);

	// unpack the data
	for(int i=0;i<totalSourceElement;i++)
	{
		index=sourceElementIndex[i];
		sourceElements[i] = *((T*) &(sourceBuffer[index][indexSourceBuffer[index]]));
		indexSourceBuffer[index]+=sizeof(T);
	}

	for(int i=0;i<nbTarget; i++) delete[] targetBuffer[i];
	for(int i=0;i<nbSource; i++) delete[] sourceBuffer[i];
	delete[] targetBuffer;
	delete[] indexTargetBuffer;
	delete[] sourceBuffer;
	delete[] indexSourceBuffer;
	delete[] request;
	delete[] status;
}


template<typename T, typename t_pack, typename t_unpack>
void CMPIRouting::transferToTarget(T* targetElements, T* sourceElements, t_pack pack, t_unpack unpack)
{
	char** targetBuffer = new char*[nbTarget];
	int* indexTargetBuffer = new int[nbTarget];
	int* targetMessageSize = new int[nbTarget];
	int* sourceMessageSize = new int[nbSource];
	int index;

	// compute target buffer size
	for (int i = 0; i < nbTarget; i++)
		targetMessageSize[i] = 0;

	for (int i = 0; i < totalTargetElement; i++)
	{
		index = targetElementIndex[i];
		pack(targetElements[i], NULL, targetMessageSize[index]);
	}

	MPI_Request *request = new MPI_Request[nbSource + nbTarget];
	MPI_Status  *status = new MPI_Status[nbSource + nbTarget];
	int indexRequest = 0;

	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::transferToTarget(messageSize)").reset();
	CTimer::get("CMPIRouting::transferToTarget(messageSize)").resume();

	for(int i=0; i<nbSource; i++)
	{
		MPI_Irecv(&sourceMessageSize[i],1,MPI_INT, sourceRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	for(int i=0; i<nbTarget; i++)
	{
		MPI_Isend(&targetMessageSize[i],1, MPI_INT, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	MPI_Waitall(indexRequest,request,status);

	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::transferToTarget(messageSize)").suspend();
	CTimer::get("CMPIRouting::transferToTarget(messageSize)").print();

	for(int i=0; i<nbTarget; i++)
	{
		targetBuffer[i] = new char[targetMessageSize[i]];
		indexTargetBuffer[i] = 0;
	}

	char** sourceBuffer = new char*[nbSource];
	int* indexSourceBuffer = new int[nbSource];

	for(int i=0;i<nbSource; i++)
	{
		sourceBuffer[i] = new char[sourceMessageSize[i]];
		indexSourceBuffer[i]= 0;
	}

	// pack the data
	for(int i=0; i<totalTargetElement; i++)
	{
		index=targetElementIndex[i];
		pack(targetElements[i], targetBuffer[index], indexTargetBuffer[index] );
	}

	indexRequest=0;

	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::transferToTarget(data)").reset();
	CTimer::get("CMPIRouting::transferToTarget(data)").resume();
	for(int i=0; i<nbSource; i++)
	{
		MPI_Irecv(sourceBuffer[i],sourceMessageSize[i],MPI_CHAR, sourceRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	for(int i=0;i<nbTarget; i++)
	{
		MPI_Isend(targetBuffer[i],targetMessageSize[i], MPI_CHAR, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	MPI_Waitall(indexRequest,request,status);

	MPI_Barrier(communicator);
	CTimer::get("CMPIRouting::transferToTarget(data)").suspend();
	CTimer::get("CMPIRouting::transferToTarget(data)").print();

	// unpack the data
	for(int i=0; i<totalSourceElement; i++)
	{
		index=sourceElementIndex[i];
		unpack(sourceElements[i], sourceBuffer[index], indexSourceBuffer[index]);
	}

	for (int i=0; i<nbTarget; i++) delete[] targetBuffer[i];
	for (int i=0; i<nbSource; i++) delete[] sourceBuffer[i];
	delete[] targetBuffer;
	delete[] indexTargetBuffer;
	delete[] targetMessageSize;
	delete[] sourceBuffer;
	delete[] indexSourceBuffer;
	delete[] sourceMessageSize;
	delete[] request;
	delete[] status;
}

template<typename T>
void CMPIRouting::transferFromSource(T* targetElements, T* sourceElements)
{
	char** targetBuffer = new char*[nbTarget];
	int* indexTargetBuffer = new int[nbTarget];

	for (int i = 0; i < nbTarget; i++)
	{
		targetBuffer[i] = new char[sizeof(T)*nbTargetElement[i]];
		indexTargetBuffer[i] = 0;
	}

	char** sourceBuffer = new char*[nbSource];
	int* indexSourceBuffer = new int[nbSource];

	for (int i = 0; i < nbSource; i++)
	{
		sourceBuffer[i] = new char[sizeof(T)*nbSourceElement[i]];
		indexSourceBuffer[i] = 0;
	}

	// pack the data
	int index;
	for (int i = 0; i < totalSourceElement; i++)
	{
		index = sourceElementIndex[i];
		*((T*) &(sourceBuffer[index][indexSourceBuffer[index]])) = sourceElements[i];
		indexSourceBuffer[index] += sizeof(T);
	}

	MPI_Request* request=new MPI_Request[nbSource+nbTarget];
	MPI_Status*  status=new MPI_Status[nbSource+nbTarget];
	int indexRequest=0;

	for(int i=0; i<nbSource; i++)
	{
		MPI_Isend(sourceBuffer[i],nbSourceElement[i]*sizeof(T),MPI_CHAR, sourceRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	for(int i=0;i<nbTarget; i++)
	{
		MPI_Irecv(targetBuffer[i],nbTargetElement[i]*sizeof(T), MPI_CHAR, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}

	MPI_Waitall(indexRequest,request,status);

	// unpack the data
	for(int i=0;i<totalTargetElement;i++)
	{
		index=targetElementIndex[i];
		targetElements[i] = *((T*) &(targetBuffer[index][indexTargetBuffer[index]]));
		indexTargetBuffer[index]+=sizeof(T);
	}

	for(int i=0;i<nbTarget; i++) delete[] targetBuffer[i];
	for(int i=0;i<nbSource; i++) delete[] sourceBuffer[i];
	delete[] targetBuffer;
	delete[] indexTargetBuffer;
	delete[] sourceBuffer;
	delete[] indexSourceBuffer;
	delete[] request;
	delete[] status;
}


/* number of source and target elements is known from previous call to init() */
template<typename T, typename t_pack, typename t_unpack>
void CMPIRouting::transferFromSource(T *targetElements, T *sourceElements, t_pack pack, t_unpack unpack)
{
	char **targetBuffer = new char*[nbTarget];
	int *indexTargetBuffer = new int[nbTarget];
	int *targetMessageSize = new int[nbTarget];
	int *sourceMessageSize = new int[nbSource];
	int index;

	// compute target buffer size
	for (int i = 0; i < nbSource; i++)  sourceMessageSize[i] = 0;

	for (int i = 0; i < totalSourceElement; i++)
	{
		index = sourceElementIndex[i];
		pack(sourceElements[i], NULL, sourceMessageSize[index]);
	}

	MPI_Request *request = new MPI_Request[nbSource + nbTarget];
	MPI_Status  *status = new MPI_Status[nbSource + nbTarget];
	int indexRequest = 0;
	for (int i = 0; i < nbSource; i++)
	{
		MPI_Isend(&sourceMessageSize[i], 1, MPI_INT, sourceRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}
	for (int i = 0; i < nbTarget; i++)
	{
		MPI_Irecv(&targetMessageSize[i], 1, MPI_INT, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}
	MPI_Waitall(indexRequest, request, status);

	for (int i = 0; i < nbTarget; i++)
	{
		targetBuffer[i] = new char[targetMessageSize[i]];
		indexTargetBuffer[i] = 0;
	}

	char **sourceBuffer = new char*[nbSource];
	int *indexSourceBuffer = new int[nbSource];

	for (int i = 0; i < nbSource; i++)
	{
		sourceBuffer[i] = new char[sourceMessageSize[i]];
		indexSourceBuffer[i] = 0;
	}


	// pack the data
	for (int i = 0; i < totalSourceElement; i++)
	{
		index = sourceElementIndex[i];
		pack(sourceElements[i], sourceBuffer[index], indexSourceBuffer[index] );
	}

	indexRequest = 0;
	for (int i = 0; i < nbSource; i++)
	{
		MPI_Isend(sourceBuffer[i], sourceMessageSize[i], MPI_CHAR, sourceRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}
	for (int i = 0; i < nbTarget; i++)
	{
		MPI_Irecv(targetBuffer[i], targetMessageSize[i], MPI_CHAR, targetRank[i], 0, communicator, &request[indexRequest]);
		indexRequest++;
	}
	MPI_Waitall(indexRequest, request, status);

	// unpack the data
	for (int i = 0; i < totalTargetElement; i++)
	{
		index = targetElementIndex[i];
		unpack(targetElements[i], targetBuffer[index], indexTargetBuffer[index]);
	}

	for (int i = 0; i < nbTarget; i++) delete[] targetBuffer[i];
	for (int i = 0; i < nbSource; i++) delete[] sourceBuffer[i];
	delete[] targetBuffer;
	delete[] indexTargetBuffer;
	delete[] targetMessageSize;
	delete[] sourceBuffer;
	delete[] indexSourceBuffer;
	delete[] sourceMessageSize;
	delete[] request;
	delete[] status;
}

CMPIRouting::~CMPIRouting()
{
};

template void CMPIRouting::init(const std::vector<int>& route, CMPICascade *cascade);
template void CMPIRouting::init(const std::vector<vector<int> >& route, CMPICascade *cascade);

template void CMPIRouting::transferToTarget(int *targetElements, int *sourceElements);
template void CMPIRouting::transferToTarget(int *targetElements, int *sourceElements, void (*pack)(int&, char*, int&), void (* unpack)(int&, char *, int&));
template void CMPIRouting::transferFromSource(int *targetElements, int *sourceElements);
template void CMPIRouting::transferFromSource(int *targetElements, int *sourceElements, void (*pack)(int&, char*, int&), void (* unpack)(int&, char *, int&));

template void CMPIRouting::transferToTarget(Node* targetElements, Node* sourceElements, void (*pack)(Node&, char*, int&), void (* unpack)(Node&, char *, int&));
template void CMPIRouting::transferToTarget(Elt **targetElements, Elt **sourceElements, void (*pack)(Elt *, char*, int&), void (* unpack)(Elt *, char *, int&));
template void CMPIRouting::transferFromSource(std::vector<int> *targetElements, std::vector<int> *sourceElements, void (*pack)(const std::vector<int>&, char*, int&), void (* unpack)(std::vector<int>&, const char *, int&));

struct NES { int cnt; int risc; int rank; };

template void alltoalls_unknown(const std::vector<std::vector<NES> >& send, std::vector<std::vector<NES> >& recv,
                                const std::vector<int>& ranks, MPI_Comm communicator);

template void alltoalls_known(const std::vector<std::vector<int> >& send, std::vector<std::vector<int> >& recv,
                              const std::vector<int>& ranks, MPI_Comm communicator);

}
