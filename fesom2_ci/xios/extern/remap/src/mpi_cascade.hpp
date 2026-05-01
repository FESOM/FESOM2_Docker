#ifndef  __MPI_CASCADE_HPP__
#define  __MPI_CASCADE_HPP__

#include "mpi.hpp"
#include <vector>
#include <cassert>
#include "misc.hpp"

namespace sphereRemap {

class CCascadeLevel
{
public:
	CCascadeLevel(MPI_Comm comm) : comm(comm)
	{
		MPI_Comm_size(comm, &size);
		MPI_Comm_rank(comm, &rank);
	}
	int colour() const { return rank % group_size; };
	int key() const { return p_colour() + rank/(p_grp_size*group_size)*p_grp_size; }

	// perpendicular group
	int p_colour() const { return (rank%group_size + rank/group_size) % p_grp_size; }
	int p_key() const { return colour() + rank/(p_grp_size*group_size)*group_size; }

	MPI_Comm comm, pg_comm;
	int rank;
	int size;
	int group_size; // group_size and p_grp_size are interchanged?? FIXME
	int p_grp_size;
};

class CMPICascade
{
public:
	// 
	CMPICascade(int nodes_per_level, MPI_Comm comm);

	int num_levels;
	std::vector<CCascadeLevel> level;
};

}
#endif
