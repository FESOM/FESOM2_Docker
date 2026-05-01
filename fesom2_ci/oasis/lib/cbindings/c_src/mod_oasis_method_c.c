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

int oasis_c_init_comp_with_comm_iso2c(int* comp_id, const char* comp_name, const bool coupled, int commworld){
  int commworld_f=commworld;
  int kinfo;
  oasis_init_comp_with_comm_iso(comp_id, &comp_name, &kinfo, &coupled, &commworld_f);
  return kinfo;
}

int oasis_c_init_comp_iso2c(int* comp_id, const char* comp_name, const bool coupled){
  int kinfo;
  oasis_init_comp_iso(comp_id, &comp_name, &kinfo, &coupled);
  return kinfo;
}


int oasis_c_init_comp_with_comm(int* comp_id, const char* comp_name, const bool coupled, const MPI_Comm commworld){
  int kinfo;
  MPI_Fint commworld_f = MPI_Comm_c2f(commworld);
  oasis_init_comp_with_comm_iso(comp_id, &comp_name, &kinfo, &coupled, &commworld_f);
  return kinfo;
}

int oasis_c_init_comp(int* comp_id, const char* comp_name, const bool coupled){
  int kinfo;
  oasis_init_comp_iso(comp_id, &comp_name, &kinfo, &coupled);
  return kinfo;
}

int oasis_c_enddef(){
  int kinfo;
  oasis_enddef_iso(&kinfo);
  return kinfo;
}

int oasis_c_terminate(){
  int kinfo;
  oasis_terminate_iso(&kinfo);
  return kinfo;
}

