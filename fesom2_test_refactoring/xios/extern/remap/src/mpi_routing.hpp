#ifndef  __MPI_ROUTING_HPP__
#define  __MPI_ROUTING_HPP__

#include "mpi.hpp"
#include <vector>
#include "mpi_cascade.hpp"

namespace sphereRemap {

class CMPIRouting
{

	MPI_Comm communicator;
	int mpiRank;
	int mpiSize;

	int  nbSource;
	int *sourceRank;
	std::vector<int> nbSourceElement;
	int  totalSourceElement;
	std::vector<int> sourceElementIndex;

	int  nbTarget;
	int *targetRank;
	std::vector<int> nbTargetElement;
	std::vector<int> targetElementIndex;
	int  totalTargetElement;


public:
	CMPIRouting(MPI_Comm comm);
	~CMPIRouting();
	template<typename T> void init(const std::vector<T>& route, CMPICascade *cascade = NULL);
	int getTotalSourceElement(void);

	template<typename T> void transferToTarget(T *targetElement, T *sourceElement);
	template<typename T, typename t_pack, typename t_unpack> void transferToTarget(T *targetElement, T *sourceElement, t_pack pack, t_unpack unpack);

	template<typename T> void transferFromSource(T *targetElement, T *sourceElement);
	template<typename T, typename t_pack, typename t_unpack> void transferFromSource(T *targetElement, T *sourceElement, t_pack pack, t_unpack unpack);

};

template <typename T>
void alltoalls_known(const std::vector<std::vector<T> >& send, std::vector<std::vector<T> >& recv,
                     const std::vector<int>& ranks, MPI_Comm communicator);

template <typename T>
void alltoalls_unknown(const std::vector<std::vector<T> >& send, std::vector<std::vector<T> >& recv,
                       const std::vector<int>& ranks, MPI_Comm communicator);
}
#endif
