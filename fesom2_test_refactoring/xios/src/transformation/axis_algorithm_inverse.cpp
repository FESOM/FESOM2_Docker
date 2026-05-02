/*!
   \file axis_algorithm_inverse.hpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 29 June 2015

   \brief Algorithm for inversing an axis..
 */
#include "axis_algorithm_inverse.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "axis.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "inverse_axis.hpp"
#include "client_client_dht_template.hpp"

namespace xios {

CGenericAlgorithmTransformation* CAxisAlgorithmInverse::create(CGrid* gridDst, CGrid* gridSrc,
                                                               CTransformation<CAxis>* transformation,
                                                               int elementPositionInGrid,
                                                               std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                               std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                               std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                               std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                               std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                               std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CAxis*> axisListDestP = gridDst->getAxis();
  std::vector<CAxis*> axisListSrcP  = gridSrc->getAxis();

  CInverseAxis* inverseAxis = dynamic_cast<CInverseAxis*> (transformation);
  int axisDstIndex = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int axisSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CAxisAlgorithmInverse(axisListDestP[axisDstIndex], axisListSrcP[axisSrcIndex], inverseAxis));
}
CATCH

bool CAxisAlgorithmInverse::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_INVERSE_AXIS, create);
}
CATCH

CAxisAlgorithmInverse::CAxisAlgorithmInverse(CAxis* axisDestination, CAxis* axisSource, CInverseAxis* inverseAxis)
 : CAxisAlgorithmTransformation(axisDestination, axisSource)
TRY
{
  if (axisDestination->n_glo.getValue() != axisSource->n_glo.getValue())
  {
    ERROR("CAxisAlgorithmInverse::CAxisAlgorithmInverse(CAxis* axisDestination, CAxis* axisSource)",
           << "Two axis have different global size"
           << "Size of axis source " <<axisSource->getId() << " is " << axisSource->n_glo.getValue()  << std::endl
           << "Size of axis destination " <<axisDestination->getId() << " is " << axisDestination->n_glo.getValue());
  }
}
CATCH

void CAxisAlgorithmInverse::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  int globalIndexSize = axisDestGlobalIndex_.size();
  for (int idx = 0; idx < globalIndexSize; ++idx)
  {
    transMap[axisDestGlobalIndex_[idx]].push_back(axisDestGlobalSize_-axisDestGlobalIndex_[idx]-1);
    transWeight[axisDestGlobalIndex_[idx]].push_back(1.0);
  }

  int niSrc   = axisSrc_->n.getValue();
  int sizeSrc = axisSrc_->n_glo.getValue();
  if (niSrc != sizeSrc) updateAxisValue();
  else
  {
    for (int idx = 0; idx < sizeSrc; ++idx)
    {
      axisDest_->value(idx) = axisSrc_->value(sizeSrc-idx-1);
    }
  }
}
CATCH

/*!
  Update value on axis after inversing
  After an axis is inversed, not only the data on it must be inversed but also the value
*/
void CAxisAlgorithmInverse::updateAxisValue()
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int clientRank = client->clientRank;
  int nbClient = client->clientSize;

  int niSrc     = axisSrc_->n.getValue();
  int ibeginSrc = axisSrc_->begin.getValue();
  int nSrc = axisSrc_->index.numElements();

  CClientClientDHTInt::Index2VectorInfoTypeMap globalIndex2ProcRank;
  for (int idx = 0; idx < nSrc; ++idx)
  {
    if ((axisSrc_->mask)(idx))
    {
      globalIndex2ProcRank[(axisSrc_->index)(idx)].resize(1);
      globalIndex2ProcRank[(axisSrc_->index)(idx)][0] = clientRank;
    }
  }

  typedef std::unordered_map<size_t, std::vector<double> > GlobalIndexMapFromSrcToDest;
  GlobalIndexMapFromSrcToDest globalIndexMapFromSrcToDest;
  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationIndexMap::const_iterator itb = transMap.begin(), ite = transMap.end(), it;
  CArray<size_t,1> globalSrcIndex(transMap.size());
  int localIndex = 0;
  for (it = itb; it != ite; ++it)
  {
    size_t srcIndex = it->second[0];
    globalIndexMapFromSrcToDest[srcIndex].resize(1);
    globalIndexMapFromSrcToDest[srcIndex][0] = it->first;
    globalSrcIndex(localIndex) = srcIndex;
    ++localIndex;
  }

  CClientClientDHTInt dhtIndexProcRank(globalIndex2ProcRank, client->intraComm);
  dhtIndexProcRank.computeIndexInfoMapping(globalSrcIndex);
  CClientClientDHTInt::Index2VectorInfoTypeMap& computedGlobalIndexOnProc = dhtIndexProcRank.getInfoIndexMap();
  std::unordered_map<int, std::vector<size_t> > globalSrcIndexSendToProc;
  for (int idx = 0; idx < localIndex; ++idx)
  {
    size_t tmpIndex = globalSrcIndex(idx);
    if (1 == computedGlobalIndexOnProc.count(tmpIndex))
    {
      std::vector<int>& tmpVec = computedGlobalIndexOnProc[tmpIndex];
      globalSrcIndexSendToProc[tmpVec[0]].push_back(tmpIndex);
    }
  }

  std::unordered_map<int, std::vector<size_t> >::const_iterator itbIndex = globalSrcIndexSendToProc.begin(), itIndex,
                                                                  iteIndex = globalSrcIndexSendToProc.end();
  std::map<int,int> sendRankSizeMap,recvRankSizeMap;
  int connectedClient = globalSrcIndexSendToProc.size();
  int* recvCount=new int[nbClient];
  int* displ=new int[nbClient];
  int* sendRankBuff=new int[connectedClient];
  int* sendSizeBuff=new int[connectedClient];
  int n = 0;
  for (itIndex = itbIndex; itIndex != iteIndex; ++itIndex, ++n)
  {
    sendRankBuff[n] = itIndex->first;
    int sendSize = itIndex->second.size();
    sendSizeBuff[n] = sendSize;
    sendRankSizeMap[itIndex->first] = sendSize;
  }
  MPI_Allgather(&connectedClient,1,MPI_INT,recvCount,1,MPI_INT,client->intraComm);

  displ[0]=0 ;
  for(int n=1;n<nbClient;n++) displ[n]=displ[n-1]+recvCount[n-1];
  int recvSize=displ[nbClient-1]+recvCount[nbClient-1];
  int* recvRankBuff=new int[recvSize];
  int* recvSizeBuff=new int[recvSize];
  MPI_Allgatherv(sendRankBuff,connectedClient,MPI_INT,recvRankBuff,recvCount,displ,MPI_INT,client->intraComm);
  MPI_Allgatherv(sendSizeBuff,connectedClient,MPI_INT,recvSizeBuff,recvCount,displ,MPI_INT,client->intraComm);
  for (int i = 0; i < nbClient; ++i)
  {
    int currentPos = displ[i];
    for (int j = 0; j < recvCount[i]; ++j)
      if (recvRankBuff[currentPos+j] == clientRank)
      {
        recvRankSizeMap[i] = recvSizeBuff[currentPos+j];
      }
  }

  // Sending global index of grid source to corresponding process as well as the corresponding mask
  std::vector<MPI_Request> requests;
  std::vector<MPI_Status> status;
  std::unordered_map<int, unsigned long* > recvGlobalIndexSrc;
  std::unordered_map<int, double* > sendValueToDest;
  for (std::map<int,int>::const_iterator itRecv = recvRankSizeMap.begin(); itRecv != recvRankSizeMap.end(); ++itRecv)
  {
    int recvRank = itRecv->first;
    int recvSize = itRecv->second;
    recvGlobalIndexSrc[recvRank] = new unsigned long [recvSize];
    sendValueToDest[recvRank] = new double [recvSize];

    requests.push_back(MPI_Request());
    MPI_Irecv(recvGlobalIndexSrc[recvRank], recvSize, MPI_UNSIGNED_LONG, recvRank, 46, client->intraComm, &requests.back());
  }

  std::unordered_map<int, unsigned long* > sendGlobalIndexSrc;
  std::unordered_map<int, double* > recvValueFromSrc;
  for (itIndex = itbIndex; itIndex != iteIndex; ++itIndex)
  {
    int sendRank = itIndex->first;
    int sendSize = sendRankSizeMap[sendRank];
    const std::vector<size_t>& sendIndexMap = itIndex->second;
    std::vector<size_t>::const_iterator itbSend = sendIndexMap.begin(), iteSend = sendIndexMap.end(), itSend;
    sendGlobalIndexSrc[sendRank] = new unsigned long [sendSize];
    recvValueFromSrc[sendRank] = new double [sendSize];
    int countIndex = 0;
    for (itSend = itbSend; itSend != iteSend; ++itSend)
    {
      sendGlobalIndexSrc[sendRank][countIndex] = *itSend;
      ++countIndex;
    }

    // Send global index source and mask
    requests.push_back(MPI_Request());
    MPI_Isend(sendGlobalIndexSrc[sendRank], sendSize, MPI_UNSIGNED_LONG, sendRank, 46, client->intraComm, &requests.back());
  }

  status.resize(requests.size());
  MPI_Waitall(requests.size(), &requests[0], &status[0]);


  std::vector<MPI_Request>().swap(requests);
  std::vector<MPI_Status>().swap(status);

  // Okie, on destination side, we will wait for information of masked index of source
  for (std::map<int,int>::const_iterator itSend = sendRankSizeMap.begin(); itSend != sendRankSizeMap.end(); ++itSend)
  {
    int recvRank = itSend->first;
    int recvSize = itSend->second;

    requests.push_back(MPI_Request());
    MPI_Irecv(recvValueFromSrc[recvRank], recvSize, MPI_DOUBLE, recvRank, 48, client->intraComm, &requests.back());
  }

  for (std::map<int,int>::const_iterator itRecv = recvRankSizeMap.begin(); itRecv != recvRankSizeMap.end(); ++itRecv)
  {
    int recvRank = itRecv->first;
    int recvSize = itRecv->second;
    double* sendValue = sendValueToDest[recvRank];
    unsigned long* recvIndexSrc = recvGlobalIndexSrc[recvRank];
    int realSendSize = 0;
    for (int idx = 0; idx < recvSize; ++idx)
    {
      size_t globalIndex = *(recvIndexSrc+idx);
      int localIndex = globalIndex - ibeginSrc;
      *(sendValue + idx) = axisSrc_->value(localIndex);
    }
    // Okie, now inform the destination which source index are masked
    requests.push_back(MPI_Request());
    MPI_Isend(sendValueToDest[recvRank], recvSize, MPI_DOUBLE, recvRank, 48, client->intraComm, &requests.back());
  }
  status.resize(requests.size());
  MPI_Waitall(requests.size(), &requests[0], &status[0]);


  size_t nGloAxisDest = axisDest_->n_glo.getValue() - 1;
  for (std::map<int,int>::const_iterator itSend = sendRankSizeMap.begin(); itSend != sendRankSizeMap.end(); ++itSend)
  {
    int recvRank = itSend->first;
    int recvSize = itSend->second;

    double* recvValue = recvValueFromSrc[recvRank];
    unsigned long* recvIndex = sendGlobalIndexSrc[recvRank];
    for (int idx = 0; idx < recvSize; ++idx)
    {
      size_t globalIndex = *(recvIndex+idx);
      int localIndex = ((nGloAxisDest-globalIndex) - axisDest_->begin);
      axisDest_->value(localIndex) = *(recvValue + idx);
    }
  }

  delete [] recvCount;
  delete [] displ;
  delete [] sendRankBuff;
  delete [] recvRankBuff;
  delete [] sendSizeBuff;
  delete [] recvSizeBuff;

  std::unordered_map<int, double* >::const_iterator itChar;
  for (itChar = sendValueToDest.begin(); itChar != sendValueToDest.end(); ++itChar)
    delete [] itChar->second;
  for (itChar = recvValueFromSrc.begin(); itChar != recvValueFromSrc.end(); ++itChar)
    delete [] itChar->second;
  std::unordered_map<int, unsigned long* >::const_iterator itLong;
  for (itLong = sendGlobalIndexSrc.begin(); itLong != sendGlobalIndexSrc.end(); ++itLong)
    delete [] itLong->second;
  for (itLong = recvGlobalIndexSrc.begin(); itLong != recvGlobalIndexSrc.end(); ++itLong)
    delete [] itLong->second;
}
CATCH

}
