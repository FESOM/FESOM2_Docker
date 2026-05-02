#ifndef __XIOS_MPI_TAG_HPP__
#define __XIOS_MPI_TAG_HPP__

/* Tag for mpi communication to send and receive index in distributed hashed table version 2*/
#define MPI_DHT_INDEX 15

/* Tag for mpi communication to send and receive info in distributed hashed table version 2*/
#define MPI_DHT_INFO 12

/* Tag for mpi communication to send and receive index in distributed hashed table version 1*/
#define MPI_DHT_INDEX_0 25

/* Tag for mpi communication to send and receive info in distributed hashed table version 1*/
#define MPI_DHT_INFO_0 22

/* Tag for mpi communication to send and receive index in distributed hashed table version 1*/
#define MPI_DHT_INDEX_1 27

/* Tag for mpi communication to send and receive info in distributed hashed table version 1*/
#define MPI_DHT_INFO_1 24

/* Tag for mpi communication to send and receive info of current grid source in grid transformation*/
#define MPI_GRID_TRANSFORMATION_CURRENT_GRID_INDEX 31

/* Tag for mpi communication to send and receive info of current grid source in grid transformation*/
#define MPI_GRID_TRANSFORMATION_ORIGINAL_GRID_GLOBAL_INDEX 32

/* Tag for mpi communication to send and receive info of current grid source in grid transformation*/
#define MPI_GRID_TRANSFORMATION_ORIGINAL_GRID_LOCAL_INDEX 33

/* Tag for mpi communication to send and receive info of current grid source in grid transformation*/
#define MPI_GRID_TRANSFORMATION_ORIGINAL_GRID_WEIGHT 34

/* Tag for mpi communication to send and receive info grid source and grid destination in transformation mapping*/
#define MPI_TRANSFORMATION_MAPPING_INDEX 35

/* Tag for mpi communication to send and receive info of DOMAIN in domain interpolation*/
#define MPI_DOMAIN_INTERPOLATION_DEST_INDEX 7

/* Tag for mpi communication to send and receive info of DOMAIN in domain interpolation*/
#define MPI_DOMAIN_INTERPOLATION_SRC_INDEX 8

/* Tag for mpi communication to send and receive info of DOMAIN in domain interpolation*/
#define MPI_DOMAIN_INTERPOLATION_WEIGHT 9

/* Tag for mpi communication to send and receive info of DOMAIN in domain interpolation*/
#define MPI_DOMAIN_INTERPOLATION_SOURCE_RANK 10

#endif
