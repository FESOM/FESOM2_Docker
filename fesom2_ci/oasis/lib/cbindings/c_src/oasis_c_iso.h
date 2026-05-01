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


#ifndef __OASIS_C_ISO_ROUTINES_C_H__
#define __OASIS_C_ISO_ROUTINES_C_H__


#include <stdbool.h>
#include <mpi.h>


/* FORTRAN interfaces */

void oasis_get_localcomm_iso(int* localcomm, int* kinfo);

void oasis_create_couplcomm_iso(const int* icpl, const int* allcomm, int* cplcomm, int* kinfo);

void oasis_set_couplcomm_iso(const int* localcomm, int* kinfo);

void oasis_get_intercomm_iso(int* new_comm, char** cdnam, int* kinfo);

void oasis_get_intracomm_iso(int* new_comm, char** cdnam, int* kinfo);

void oasis_get_multi_intracomm_iso(int* new_comm, const int* cdnam_size, char** cdnam, int* root_ranks, int* kinfo);

void oasis_set_debug_iso(const int* debug, int* kinfo);

void oasis_get_debug_iso(int* debug, int* kinfo);

void oasis_put_inquire_iso(const int* varid, const int* msec, int* kinfo);

void oasis_get_ncpl_iso(const int* varid, int* ncpl, int* kinfo);

void oasis_get_freqs_iso(const int* varid, const int* mop, const int* ncpl, int* cpl_freqs, int* kinfo);

void oasis_put_iso_double(const int* var_id, const int* kstep, const int* size1, const int* size2, const int* size3, const double* fld1, int* kinfo, const bool* write_restart);

void oasis_get_iso_double(const int* var_id, const int* kstep, const int* size1, const int* size2, const int* size3, double* fld1, int* kinfo);

void oasis_put_iso_float(const int* var_id, const int* kstep, const int* size1, const int* size2, const int* size3, const float* fld1, int* kinfo, const bool* write_restart);

void oasis_get_iso_float(const int* var_id, const int* kstep, const int* size1, const int* size2, const int* size3, float* fld1, int* kinfo);

void oasis_start_grids_writing_iso(int *kinfo);

void oasis_write_grid_iso(const char** cgrid, const int* nx, const int* ny, const int* nx_loc, const int* ny_loc, const double* lon, const double* lat, const int* partid);

void oasis_write_corner_iso(const char** cgrid, const int* nx, const int* ny, const int* nc, const int* nx_loc, const int* ny_loc, const double* clo, const double* cla, const int* partid);

void oasis_write_mask_iso(const char** cgrid, const int* nx, const int* ny, const int* nx_loc, const int* ny_loc, const int* mask, const int* partid, const char** companion);

void oasis_write_frac_iso(const char** cgrid, const int* nx, const int* ny, const int* nx_loc, const int* ny_loc, const double* frac, const int* partid, const char** companion);

void oasis_write_area_iso(const char** cgrid, const int* nx, const int* ny, const int* nx_loc, const int* ny_loc, const double* area, const int* partid);

void oasis_write_angle_iso(const char** cgrid, const int* nx, const int* ny, const int* nx_loc, const int* ny_loc, const double* angle, const int* partid);

void oasis_terminate_grids_writing_iso();

void oasis_init_comp_with_comm_iso(int* mynummod, const char** cdnam, int* kinfo, const bool* coupled, const int* commworld);

void oasis_init_comp_iso(int* mynummod, const char** cdnam, int* kinfo, const bool* coupled);

void oasis_enddef_iso(int* kinfo);

void oasis_terminate_iso(int* kinfo);

extern void oasis_def_partition_iso(int* id_part, const int* kparal_size, const int* kparal, int* kinfo, const int *ig_size, const char** name);

void oasis_abort_iso(const int* id_compid, const char** cd_routine, const char** cd_message, const char** file, const int* line, const int* rcode);

void oasis_def_var_iso(int* id_nports, const char** cdport, const int* id_part, const int* bundle_size, const int* kinout, const int* ktype, int* kinfo);


/* C interfaces with MPI Communicator defined as int (for python or C++) */

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

int oasis_c_get_localcomm_iso2c(int* localcomm);

int oasis_c_create_couplcomm_iso2c(const int icpl, const int allcomm, int* cplcomm);

int oasis_c_set_couplcomm_iso2c(const int localcomm);

int oasis_c_get_intercomm_iso2c(int* new_comm, char* cdnam);

int oasis_c_get_intracomm_iso2c(int* new_comm, char* cdnam);

int oasis_c_get_multi_intracomm_iso2c(int* new_comm, const int cdnam_size, char** cdnam, int* root_ranks);

int oasis_c_init_comp_with_comm_iso2c(int* mynummod, const char* cdnam, const bool coupled, const int commworld);

int oasis_c_init_comp_iso2c(int* mynummod, const char* cdnam, const bool coupled);

#endif
