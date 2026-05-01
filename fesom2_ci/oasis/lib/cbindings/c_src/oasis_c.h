/* pyOASIS - A Python wrapper for OASIS
   Authors: Philippe Gambron, Rupert Ford
   Copyright (C) 2019 UKRI - STFC
  
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Lesser General Public License for more details.
  
   A copy of the GNU Lesser General Public License, version 3, is supplied
   with this program, in the file lgpl-3.0.txt. It is also available at
   <https://www.gnu.org/licenses/lgpl-3.0.html>. */


#ifndef __OASIS_C_ROUTINES_C_H__
#define __OASIS_C_ROUTINES_C_H__


#include <stdbool.h>
#include <mpi.h>


#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

#define OASIS_CHECK_ERR(x) { \
  int retval = (x); \
  if (retval != OASIS_Ok) { \
     fprintf(stderr, "Runtime error: %s returned %d at %s:%d\n", #x, retval, __FILE__, __LINE__); \
     fflush(stderr); \
     oasis_c_abort(0, #x, "Runtime error", __FILE__, __LINE__); \
  } \
}

#define OASIS_CHECK_MPI_ERR(x) { \
  int retval = (x); \
  if (retval != MPI_SUCCESS) { \
     fprintf(stderr, "Runtime MPI error: %s returned %d at %s:%d\n", #x, retval, __FILE__, __LINE__); \
     fflush(stderr); \
     oasis_c_abort(0, #x, "Runtime MPI error", __FILE__, __LINE__); \
  } \
}

enum mnemonic_params
{
  OASIS_Real          = 4,
  OASIS_REAL          = 4,
  OASIS_Double        = 8,
  OASIS_DOUBLE        = 8,
  OASIS_ROW_MAJOR     = 0,
  OASIS_COL_MAJOR     = 1,
  OASIS_Out           = 20,
  OASIS_OUT           = 20,
  OASIS_In            = 21,
  OASIS_IN            = 21,
  OASIS_Coupled       = 1,
  OASIS_COUPLED       = 1,
  OASIS_Not_Coupled   = 0,
  OASIS_NOT_COUPLED   = 0,
  OASIS_Write_Restart = 1,
  OASIS_WRITE_RESTART = 1,
  OASIS_No_Restart    = 0,
  OASIS_NO_RESTART    = 0,
  OASIS_No_Part       = -1,
  OASIS_NO_PART       = -1
};

#define OASIS_No_Companion "NULL-STRING"

enum partition_params {
  OASIS_Serial        = 0,
  OASIS_Apple         = 1,
  OASIS_Box           = 2,
  OASIS_Orange        = 3,
  OASIS_Points        = 4,
  OASIS_Strategy      = 0,
  OASIS_Segments      = 1,
  OASIS_Npoints       = 1,
  OASIS_Offset        = 1,
  OASIS_Length        = 2,
  OASIS_SizeX         = 2,
  OASIS_SizeY         = 3,
  OASIS_LdX           = 4,
  OASIS_Serial_Params = 3,
  OASIS_Apple_Params  = 3,
  OASIS_Box_Params    = 5,
  OASIS_No_Gsize      = 0
};

#define OASIS_No_Name ""
#define OASIS_Orange_Params(n_segments) (2 + 2*n_segments)
#define OASIS_Points_Params(n_points) (2 + n_points)

enum return_codes
{
  OASIS_Ok            = 0,
  OASIS_Success       = 0,
  OASIS_Error         = -10,
  OASIS_NotDef        = -2,
  OASIS_Var_Uncpl     = -1,
  OASIS_InOut         = 2,
  OASIS_Recvd         = 3,
  OASIS_Sent          = 4,
  OASIS_LocTrans      = 5,
  OASIS_ToRest        = 6,
  OASIS_Output        = 7,
  OASIS_SentOut       = 8,
  OASIS_ToRestOut     = 9,
  OASIS_FromRest      = 10,
  OASIS_Input         = 11,
  OASIS_RecvOut       = 12,
  OASIS_FromRestOut   = 13,
  OASIS_Waitgroup     = 14
};

/* C interfaces with MPI Communicator defined as C MPI_Comm (for C) */

int oasis_c_get_localcomm(MPI_Comm* localcomm);

int oasis_c_create_couplcomm(const int icpl, const MPI_Comm allcomm, MPI_Comm* cplcomm);

int oasis_c_set_couplcomm(const MPI_Comm localcomm);

int oasis_c_get_intercomm(MPI_Comm* new_comm, char* cdnam);

int oasis_c_get_intracomm(MPI_Comm* new_comm, char* cdnam);

int oasis_c_get_multi_intracomm(MPI_Comm* new_comm, const int cdnam_size, char** cdnam, int* root_ranks);

int oasis_c_set_debug(const int debug);

int oasis_c_get_debug(int* debug);

int oasis_c_put_inquire(int varid, int msec, int *kinfo);

int oasis_c_get_ncpl(const int varid, int* ncpl);

int oasis_c_get_freqs(const int varid, const int mop, const int ncpl, int* cpl_freqs);

int oasis_c_put(const int var_id, const int kstep, const int x_size, const int y_size, const int bundle_size, const int fkind, const int storage, const void* fld1, const bool write_restart, int* kinfo);

int oasis_c_get(const int var_id, const int kstep, const int x_size, const int y_size, const int bundle_size, const int fkind, const int storage, void* fld1, int* kinfo);

int oasis_c_start_grids_writing();

int oasis_c_write_grid(const char* cgrid, const int nx, const int ny, const int nx_loc, const int ny_loc, const double* lon, const double* lat, const int partid);

int oasis_c_write_corner(const char* cgrid, const int nx, const int ny, const int nc, const int nx_loc, const int ny_loc, const double* clo, const double* cla, const int partid);

int oasis_c_write_mask(const char* cgrid, const int nx, const int ny, const int nx_loc, const int ny_loc, const int* mask, const int partid, const char* companion);

int oasis_c_write_frac(const char* cgrid, const int nx, const int ny, const int nx_loc, const int ny_loc, const double* frac, const int partid, const char* companion);

int oasis_c_write_area(const char* cgrid, const int nx, const int ny, const int nx_loc, const int ny_loc, const double* area, const int partid);

int oasis_c_write_angle(const char* cgrid, const int nx, const int ny, const int nx_loc, const int ny_loc, const double* angle, const int partid);

int oasis_c_terminate_grids_writing();

int oasis_c_init_comp_with_comm(int* mynummod, const char* cdnam, const bool coupled, const MPI_Comm commworld);

int oasis_c_init_comp(int* mynummod, const char* cdnam, const bool coupled);

int oasis_c_enddef();

int oasis_c_terminate();

int oasis_c_def_partition(int* id_part, const int kparal_size, const int* kparal, const int ig_size, const char* name);

int oasis_c_abort(const int id_compid, const char* cd_routine, const char* cd_message, const char* file, const int line);

int oasis_c_def_var(int* id_nports, const char* cdport, const int id_part, const int bundle_size, const int kinout, const int ktype);

#define IS_VALID_PUT(k) ( k == OASIS_Ok) || ( k == OASIS_Output ) || ( k == OASIS_ToRestOut ) || \
      ( k == OASIS_ToRest ) || ( k == OASIS_SentOut ) || ( k == OASIS_Sent ) || \
      ( k == OASIS_LocTrans ) || ( k == OASIS_Waitgroup )

#define IS_VALID_GET(k) ( k == OASIS_Ok) || ( k == OASIS_Input ) || ( k == OASIS_FromRestOut ) || \
      ( k == OASIS_Recvd ) || ( k == OASIS_RecvOut ) || ( k == OASIS_Output )

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif


#endif
