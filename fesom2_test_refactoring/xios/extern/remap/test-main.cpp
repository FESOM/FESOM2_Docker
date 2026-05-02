#include "mpi.hpp"
#include <netcdf.h>
#include "errhandle.hpp"
#include "libmapper.hpp"
#include "mapper.hpp"

#include "node.hpp"

using namespace sphereRemap ;

int ncread(double *lon, double *lat, double* val, int nElt, const char* filename)
{
	int ncid, blonid, blatid, valid, neltid;
	size_t nEltCheck;
	exit_on_failure(nc_open(filename, NC_NOWRITE, &ncid), std::string("Cannot open netCDF file ") + filename);
	exit_on_failure(nc_inq_dimid(ncid, "elt", &neltid), std::string("No dimension elt in file ") + filename);
	nc_inq_dimlen(ncid, neltid, &nEltCheck);
	exit_on_failure(nElt != nEltCheck, std::string("Array sizes do not match!"));

	nc_inq_varid(ncid, "bounds_lon", &blonid);
	nc_inq_varid(ncid, "bounds_lat", &blatid);
	nc_inq_varid(ncid, "val", &valid);
	nc_get_var_double(ncid, blonid, lon);
	nc_get_var_double(ncid, blatid, lat);
	nc_get_var_double(ncid, valid, val);
	nc_close(ncid);
}

int ncwriteValue(double *val, const char* filename)
{
  int ncid, valid ;
  nc_open(filename, NC_WRITE, &ncid);
  nc_inq_varid(ncid, "val", &valid);
  nc_put_var_double(ncid, valid, val);
  nc_close(ncid);
}
  


void compute_distribution(int nGlobalElts, int &start, int &nLocalElts)
{
	int mpiSize, mpiRank;
	MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
	start = 0;
	nLocalElts = 0;
	for (int i = 0; i <= mpiRank; i++)
	{
		start += nLocalElts;
		nLocalElts = nGlobalElts/mpiSize;
		if (i < nGlobalElts % mpiSize) nLocalElts++;
	}
}

int main()
{
	int interpOrder = 2;
/* low resolution */
/*
	char srcFile[] = "h14.nc";
	char dstFile[] = "r180x90.nc";
	double srcPole[] = {0, 0, 0};
	double dstPole[] = {0, 0, 1};
	int nSrcElt = 13661;
	int nDstElt = 16200;
*/
/* high resolution */ 

	char srcFile[] = "t740.nc";
	char dstFile[] = "r1440x720.nc";
	double srcPole[] = {0, 0, 0};
	double dstPole[] = {0, 0, 1};
	int nSrcElt = 741034;
	int nDstElt = 1036800;

	int nVert = 10;
	int nSrcLocal, nDstLocal, startSrc, startDst;
	int nWeight;
  int mpi_rank, mpi_size ;

	MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank) ;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size) ;

	double *srcLon = (double *) malloc(nSrcElt*nVert*sizeof(double));	
	double *srcLat = (double *) malloc(nSrcElt*nVert*sizeof(double));	
	double *srcVal = (double *) malloc(nSrcElt*sizeof(double));	
	double *dstLon = (double *) malloc(nDstElt*nVert*sizeof(double));	
	double *dstLat = (double *) malloc(nDstElt*nVert*sizeof(double));	
	double *dstVal = (double *) malloc(nDstElt*sizeof(double));
	double *globalVal = (double *) malloc(nDstElt*sizeof(double));
  
	ncread(srcLon, srcLat, srcVal, nSrcElt, srcFile);
	ncread(dstLon, dstLat, dstVal, nDstElt, dstFile);

	compute_distribution(nSrcElt, startSrc, nSrcLocal);
	compute_distribution(nDstElt, startDst, nDstLocal);



  Mapper mapper(MPI_COMM_WORLD);
  mapper.setVerbosity(PROGRESS) ;
  mapper.setSourceMesh(srcLon + startSrc*nVert, srcLat + startSrc*nVert, nVert, nSrcLocal, srcPole ) ;
  mapper.setTargetMesh(dstLon + startDst*nVert, dstLat + startDst*nVert, nVert, nDstLocal, dstPole ) ;

  for(int i=0;i<nDstElt;i++) dstVal[i]=0 ;
  mapper.setSourceValue(srcVal+ startSrc) ;
  
  
  vector<double> timings = mapper.computeWeights(interpOrder);


  for(int i=0;i<mapper.nWeights;i++)  dstVal[mapper.dstAddress[i]]=dstVal[mapper.dstAddress[i]]+mapper.remapMatrix[i]*srcVal[mapper.sourceWeightId[i]];

/*
	remap_get_num_weights(srcLon + startSrc*nVert, srcLat + startSrc*nVert, nVert, nSrcLocal, srcPole,
	                      dstLon + startDst*nVert, dstLat + startDst*nVert, nVert, nDstLocal, dstPole,
	                      interpOrder, &nWeight);

	double *weights = (double *) malloc(nWeight*sizeof(double));	
	int    *srcIdx  = (int *)    malloc(nWeight*sizeof(int));	
	int    *srcRank = (int *)    malloc(nWeight*sizeof(int));	
	int    *dstIdx  = (int *)    malloc(nWeight*sizeof(int));	

	remap_get_weights(weights, srcIdx, dstIdx);

	free(srcLon); free(srcLat);
	free(dstLon); free(dstLat);
	free(srcIdx); free(dstIdx);
	free(srcRank);
	free(weights);

#ifdef DEBUG
	memory_report();
#endif
*/
  int* displs=new int[mpi_size] ;
  int* recvCount=new int[mpi_size] ;
  
  MPI_Gather(&startDst,1,MPI_INT,displs,1,MPI_INT,0,MPI_COMM_WORLD) ;
  MPI_Gather(&nDstLocal,1,MPI_INT,recvCount,1,MPI_INT,0,MPI_COMM_WORLD) ;
  MPI_Gatherv(dstVal,nDstLocal,MPI_DOUBLE,globalVal,recvCount,displs,MPI_DOUBLE,0,MPI_COMM_WORLD) ;
  if (mpi_rank==0)  ncwriteValue(globalVal, dstFile);
  
	MPI_Finalize();
	return 0;
}
