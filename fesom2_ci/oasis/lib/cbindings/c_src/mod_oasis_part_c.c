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

int oasis_c_def_partition(int* id_part, const int kparal_size, const int* kparal, const int ig_size, const char* name){
  int kinfo;
  int st = kparal[OASIS_Strategy];
  if ((st != OASIS_Serial) && (st != OASIS_Apple) && (st != OASIS_Box) &&
      (st!= OASIS_Orange) && (st != OASIS_Points) )
    oasis_c_abort(0, "oasis_c_def_partition", "Wrong value for kparal[OASIS_Strategy]", __FILE__, __LINE__);
  if ( kparal[OASIS_Strategy] == OASIS_Points ) {
    int kparalf[kparal_size];
    int i;
    kparalf[OASIS_Strategy] = OASIS_Points;
    kparalf[OASIS_Npoints] = kparal[OASIS_Npoints] ;
    for (i = OASIS_Npoints+1; i<kparal_size; i++ ) kparalf[i] = kparal[i]+1;
    oasis_def_partition_iso(id_part, &kparal_size, kparalf, &kinfo, &ig_size, &name);
  } else {
    oasis_def_partition_iso(id_part, &kparal_size, kparal, &kinfo, &ig_size, &name);
  }
  return kinfo;
}
