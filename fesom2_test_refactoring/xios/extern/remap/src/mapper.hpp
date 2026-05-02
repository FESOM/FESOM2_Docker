#ifndef  __MAPPER_HPP__
#define __MAPPER_HPP__
#include "parallel_tree.hpp"
#include "mpi.hpp"

namespace sphereRemap {

enum verbosity
{
       SILENT = 0,
       PROGRESS = 1,
       DETAILS = 2
};

void cptOffsetsFromLengths(const int *lengths, int *offsets, int sz);

class Mapper
{
public:
       Mapper(MPI_Comm comm=MPI_COMM_WORLD) : communicator(comm), verbose(SILENT), neighbourElements(NULL), sstree(comm) {}
       ~Mapper();
       void setVerbosity(verbosity v) {verbose=v ;}

       void setSourceMesh(const double* boundsLon, const double* boundsLat, const double* area, int nVertex, int nbCells, const double* pole, const long int* globalId=NULL) ;
       void setTargetMesh(const double* boundsLon, const double* boundsLat, const double* area, int nVertex, int nbCells, const double* pole, const long int* globalId=NULL) ;
       void setSourceValue(const double* val) ;
       void getTargetValue(double* val) ;

       void buildSSTree(vector<Node>& srcMsh, vector<Node>& trgMsh)
       {
         sstree.build(srcMsh, trgMsh);
       }

       /** @param trgElts are the elements of the unstructured target grid
           Returns the timings for substeps: */
       vector<double> computeWeights(int interpOrder, bool renormalize=false, bool quantity=false);
       int getNbWeights(void) { return nWeights ; }
/*
       void getWeigths(double* weights, double* sourceInd, double* targetInd) ;
       void getWeights(vector<double>& weights, vector<double>& sourceInd, vector<double>& targetInd) ;
*/
       /* where weights are returned after call to `computeWeights` */
       double *remapMatrix;
       int *srcAddress;
       int *srcRank;
       int *dstAddress;
       int nWeights;
       long int* sourceWeightId ;
       long int* targetWeightId ;

private:
       /** @return number of weights (local to cpu) */
       int remap(Elt* elements, int nbElements, int order, bool renormalize=false, bool quantity=false);

       void buildMeshTopology();
       void computeGrads();
       void computeIntersection(Elt* elements, int nbElements);

       int verbose;

       /** Holds adaptional leaf nodes as ghost cells for gradient computations (hold neighbour elements from other ranks).
           They will be inserted to the local trees but not saved in its leaf array */
       vector<Node> neighbourNodes;

       int nbNeighbourElements;
       Elt* neighbourElements;

       CParallelTree sstree;
       MPI_Comm communicator ;
       std::vector<Elt>  sourceElements ;
       std::vector<Node> sourceMesh ;
       std::vector<Elt>  targetElements ;
       std::vector<Node> targetMesh ;
       std::vector<long> sourceGlobalId ;
       std::vector<long> targetGlobalId ;

};

}
#endif
