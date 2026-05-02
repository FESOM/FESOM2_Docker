#include "mpi_cascade.hpp"
#include <iostream>

namespace sphereRemap {

CMPICascade::CMPICascade(int nodes_per_level, MPI_Comm comm)
{
	int remaining_levels;
	MPI_Comm intraComm;
	int l = 0; // current level
	do {
		level.push_back(comm);
		remaining_levels = ilog(nodes_per_level /*base*/, level[l].size /*arg*/) + 1;
		level[l].group_size = iroot(remaining_levels, level[l].size); // group_size^remaining_levels <= size
		level[l].p_grp_size = level[l].size/level[l].group_size;
	
		MPI_Comm_split(comm, level[l].colour(), level[l].key(), &intraComm);
		MPI_Comm_split(comm, level[l].p_colour(), level[l].p_key(), &(level[l].pg_comm));
		comm = intraComm;
		l++;
	} while (--remaining_levels);
	num_levels = l;
}

}
