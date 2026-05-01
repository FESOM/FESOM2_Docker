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


#include "oasis_c.h"
#include "oasis_c_iso.h"


int oasis_c_get_localcomm_iso2c(int* localcomm){
  int kinfo;
  oasis_get_localcomm_iso(localcomm, &kinfo);
  return kinfo;
}

int oasis_c_create_couplcomm_iso2c(const int icpl, const int allcomm, int* cplcomm){
  int kinfo;
  oasis_create_couplcomm_iso(&icpl, &allcomm, cplcomm, &kinfo);
  return kinfo;
}

int oasis_c_set_couplcomm_iso2c(const int localcomm){
  int kinfo;
  oasis_set_couplcomm_iso(&localcomm, &kinfo);
  return kinfo;
}

int oasis_c_get_intercomm_iso2c(int* new_comm, char* cdnam){
  int kinfo;
  oasis_get_intercomm_iso(new_comm, &cdnam, &kinfo);
  return kinfo;
}

int oasis_c_get_intracomm_iso2c(int* new_comm, char* cdnam){
  int kinfo;
  oasis_get_intracomm_iso(new_comm, &cdnam, &kinfo);
  return kinfo;
}

int oasis_c_get_multi_intracomm_iso2c(int* new_comm, const int cdnam_size, char** cdnam, int* root_ranks){
  int kinfo;
  oasis_get_multi_intracomm_iso(new_comm, &cdnam_size, cdnam, root_ranks, &kinfo);
  return kinfo;
}



int oasis_c_get_localcomm(MPI_Comm *localcomm){
  int kinfo;
  MPI_Fint fcomm;
  oasis_get_localcomm_iso(&fcomm, &kinfo);
  *localcomm = MPI_Comm_f2c(fcomm);
  return kinfo;
}

int oasis_c_create_couplcomm(const int icpl, const MPI_Comm allcomm, MPI_Comm *cplcomm){
  int kinfo;
  MPI_Fint fcplcomm;
  MPI_Fint fallcomm;
  fallcomm = MPI_Comm_c2f(allcomm);
  oasis_create_couplcomm_iso(&icpl, &fallcomm, &fcplcomm, &kinfo);
  *cplcomm = MPI_Comm_f2c(fcplcomm);
  return kinfo;
}

int oasis_c_set_couplcomm(const MPI_Comm localcomm){
  int kinfo;
  MPI_Fint fcomm;
  fcomm = MPI_Comm_c2f(localcomm);
  oasis_set_couplcomm_iso(&fcomm, &kinfo);
  return kinfo;
}

int oasis_c_get_intercomm(MPI_Comm *new_comm, char* cdnam){
  int kinfo;
  MPI_Fint fcomm;
  oasis_get_intercomm_iso(&fcomm, &cdnam, &kinfo);
  *new_comm = MPI_Comm_f2c(fcomm);
  return kinfo;
}

int oasis_c_get_intracomm(MPI_Comm *new_comm, char* cdnam){
  int kinfo;
  MPI_Fint fcomm;
  oasis_get_intracomm_iso(&fcomm, &cdnam, &kinfo);
  *new_comm = MPI_Comm_f2c(fcomm);
  return kinfo;
}

int oasis_c_get_multi_intracomm(MPI_Comm *new_comm, const int cdnam_size, char** cdnam, int* root_ranks){
  int kinfo;
  MPI_Fint fcomm;
  oasis_get_multi_intracomm_iso(&fcomm, &cdnam_size, cdnam, root_ranks, &kinfo);
  *new_comm = MPI_Comm_f2c(fcomm);
  return kinfo;
}

int oasis_c_set_debug(const int debug){
  int kinfo;
  oasis_set_debug_iso(&debug, &kinfo);
  return kinfo;
}

int oasis_c_get_debug(int* debug){
  int kinfo;
  oasis_get_debug_iso(debug, &kinfo);
  return kinfo;
}

int oasis_c_put_inquire(const int varid, const int msec, int *kinfo){
  oasis_put_inquire_iso(&varid, &msec, kinfo);
  if ( IS_VALID_PUT(*kinfo) ) {
    return OASIS_Ok;
  } else {
    return OASIS_Error;
  }
}

int oasis_c_get_ncpl(const int varid, int* ncpl){
  int kinfo;
  oasis_get_ncpl_iso(&varid, ncpl, &kinfo);
  return kinfo;
}

int oasis_c_get_freqs(const int varid, const int mop, const int ncpl, int* cpl_freqs){
  int kinfo;
  oasis_get_freqs_iso(&varid, &mop, &ncpl, cpl_freqs, &kinfo);
  return kinfo;
}
