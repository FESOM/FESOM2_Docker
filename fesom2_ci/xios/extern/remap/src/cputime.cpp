#include "mpi.hpp"

namespace sphereRemap {
  
double cputime()
{
	return MPI_Wtime();
}

}
