#include "mpi.hpp"
#include <vector>
#include <cassert>
#include <cstring>
#ifdef WRITE_TIMING
#include <fstream>
#endif

#include "node.hpp"
#include "grid.hpp"
#include "circle.hpp" // cptRadius
#include "elt.hpp"
#include "meshutil.hpp" // cptArea
#include "mapper.hpp"
#include "cputime.hpp" // cputime

using namespace sphereRemap ;

/* mapper is a ponter to a global class instance whoes members are allocated in the first step (finding the sizes of the weight arrays)
   and deallocated during the second step (computing the weights) */
Mapper *mapper;


/** xxx_bounds_yyy is of length n_vert_per_cell_xxx*n_cell_xxx
   This function computes the weights and returns number of weights is returned through the last argument.
   To get the actuall weights, use `remap_get_weights`.
*/
extern "C" void remap_get_num_weights(const double* src_bounds_lon, const double* src_bounds_lat, int n_vert_per_cell_src, int n_cell_src,
                     const double* src_pole,
                     const double* dst_bounds_lon, const double* dst_bounds_lat, int n_vert_per_cell_dst, int n_cell_dst,
                     const double* dst_pole,
                     int order, int* n_weights)
{
	assert(src_bounds_lon);
	assert(src_bounds_lat);
	assert(n_vert_per_cell_src >= 3);
	assert(n_cell_src >= 4);
	assert(dst_bounds_lon);
	assert(dst_bounds_lat);
	assert(n_vert_per_cell_dst >= 3);
	assert(n_cell_dst >= 4);
	assert(1 <= order && order <= 2);
  double* src_area=NULL ;
  double* dst_area=NULL ;
  mapper = new Mapper(MPI_COMM_WORLD);
  mapper->setVerbosity(PROGRESS) ;
  mapper->setSourceMesh(src_bounds_lon, src_bounds_lat, src_area, n_vert_per_cell_src, n_cell_src, src_pole ) ;
  mapper->setTargetMesh(dst_bounds_lon, dst_bounds_lat, dst_area, n_vert_per_cell_dst, n_cell_dst, dst_pole ) ;

/*
	srcGrid.pole = Coord(src_pole[0], src_pole[1], src_pole[2]);
	tgtGrid.pole = Coord(dst_pole[0], dst_pole[1], dst_pole[2]);

	int mpiRank, mpiSize;
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

	std::vector<Elt>  src_elt; src_elt.reserve(n_cell_src);
	std::vector<Node> src_msh; src_msh.reserve(n_cell_src);
	for (int i = 0; i < n_cell_src; i++)
	{
		int offs = i*n_vert_per_cell_src;
		Elt elt(src_bounds_lon + offs, src_bounds_lat + offs, n_vert_per_cell_src);
		elt.src_id.rank = mpiRank;
		elt.src_id.ind = i;
		src_elt.push_back(elt);
		src_msh.push_back(Node(elt.x, cptRadius(elt), &src_elt.back()));
		cptEltGeom(src_elt[i], Coord(src_pole[0], src_pole[1], src_pole[2]));
	}
	std::vector<Elt>  dst_elt; dst_elt.reserve(n_cell_dst);
	std::vector<Node> dst_msh; dst_msh.reserve(n_cell_dst);
	for (int i = 0; i < n_cell_dst; i++)
	{
		int offs = i*n_vert_per_cell_dst;
		Elt elt(dst_bounds_lon + offs, dst_bounds_lat + offs, n_vert_per_cell_dst);
		dst_elt.push_back(elt);
		dst_msh.push_back(Node(elt.x, cptRadius(elt), &dst_elt.back()));
		cptEltGeom(dst_elt[i], Coord(dst_pole[0], dst_pole[1], dst_pole[2]));
	}
	double tic = cputime();
	mapper = new Mapper(MPI_COMM_WORLD);
  mapper->setVerbosity(PROGRESS) ;
	mapper->buildSSTree(src_msh, dst_msh);
	double tac = cputime();
	vector<double> timings = mapper->computeWeights(dst_elt, src_elt, order);
*/

  vector<double> timings = mapper->computeWeights(order);
/*
#ifdef WRITE_TIMING
	int nGloWeights, gloSrcSize, gloDstSize;
	int locSrcSize = src_elt.size();
	int locDstSize = dst_elt.size();
	MPI_Reduce(&(mapper->nWeights), &nGloWeights, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&locSrcSize, &gloSrcSize, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&locDstSize, &gloDstSize, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (mpiRank == 0)
	{
		ofstream timeout;
		timeout.open("timings.txt", fstream::out | fstream::app);
		timeout << mpiSize << " " << src_elt.size() << " " << dst_elt.size() << " " << nGloWeights
			<< " " << tac-tic << " " << timings[0] << " " << timings[1] << " " << timings[2] << endl;
		timeout.close();
	}
#endif
*/

	*n_weights = mapper->nWeights;

}

extern "C" void remap_get_barycentres_and_areas(const double* bounds_lon, const double* bounds_lat, int n_vert_per_cell, int n_cell,
                     const double* pole,
                     double* centre_lon, double* centre_lat, double* areas)
{
	for (int i = 0; i < n_cell; i++)
	{
		int offs = i*n_vert_per_cell;
		Elt elt(bounds_lon + offs, bounds_lat + offs, n_vert_per_cell);
		cptEltGeom(elt, Coord(pole[0], pole[1], pole[2]));
		if (centre_lon && centre_lat) lonlat(elt.x, centre_lon[i], centre_lat[i]);
		if (areas) areas[i] = elt.area;
	}
}

/*
extern "C" void remap_get_weights(double* weights, int* src_indices, int* src_ranks, int* dst_indices)
{
	memcpy(weights, mapper->remapMatrix, mapper->nWeights*sizeof(double));
	memcpy(src_indices, mapper->srcAddress, mapper->nWeights*sizeof(int));
	memcpy(src_ranks, mapper->srcRank, mapper->nWeights*sizeof(int));
	memcpy(dst_indices, mapper->dstAddress, mapper->nWeights*sizeof(int));
	delete mapper;
}
*/

extern "C" void remap_get_weights(double* weights, int* src_indices, int* dst_indices)
{
	memcpy(weights, mapper->remapMatrix, mapper->nWeights*sizeof(double));
	memcpy(src_indices, mapper->srcAddress, mapper->nWeights*sizeof(int));
	memcpy(dst_indices, mapper->dstAddress, mapper->nWeights*sizeof(int));
	delete mapper;
}

extern "C" void mpi_init()
{
	/*int argc = 0;
	char **argv = NULL;
	MPI_Init(&argc, &argv);*/
	MPI_Init(NULL, NULL);
}

extern "C" int mpi_rank()
{
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	return rank;
}

extern "C" int mpi_size()
{
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	return size;
}

extern "C" void mpi_finalize()
{
	MPI_Finalize();
}
