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
#include <stdlib.h>
#include <string.h>

int oasis_c_put(const int var_id, const int kstep, const int x_size, const int y_size, const int bundle_size, const int fkind, const int storage, const void* fld1, const bool write_restart, int* kinfo){
  bool storage_is1D = ((int)( x_size == 1 ) + (int)( y_size == 1 ) + (int)( bundle_size == 1 )) == 2;
  if ( storage != OASIS_COL_MAJOR && storage != OASIS_ROW_MAJOR )
    oasis_c_abort(0, "oasis_c_put", "storage argument can only be OASIS_ROW_MAJOR or OASIS_COL_MAJOR", __FILE__, __LINE__);
  if ( storage == OASIS_COL_MAJOR || storage_is1D ) {
    if ( fkind == OASIS_Real ) {
      oasis_put_iso_float(&var_id, &kstep, &x_size, &y_size, &bundle_size, (float*)fld1, kinfo, &write_restart);
    } else if ( fkind == OASIS_Double ) {
      oasis_put_iso_double(&var_id, &kstep, &x_size, &y_size, &bundle_size, fld1, kinfo, &write_restart);
    } else {
      oasis_c_abort(0, "oasis_c_put", "fkind argument can only be OASIS_Real or OASIS_Double", __FILE__, __LINE__);
    }
  } else {
    if ( fkind == OASIS_Real ) {
      float* fld2;
      int i,j,k;
      fld2 = (float*) malloc(x_size*y_size*bundle_size*sizeof(float));
      for (i=0; i<x_size; i++) {
	for (j=0; j<y_size; j++) {
	  for (k=0; k<bundle_size; k++) {
	    memcpy(fld2+k*y_size*x_size+j*x_size+i, fld1+(i*y_size*bundle_size+j*bundle_size+k)*sizeof(float), sizeof(float));
	  }
	}
      }
      oasis_put_iso_float(&var_id, &kstep, &x_size, &y_size, &bundle_size, fld2, kinfo, &write_restart);
      free(fld2);
    } else if ( fkind == OASIS_Double ) {
      double* fld2;
      int i,j,k;
      fld2 = (double*) malloc(x_size*y_size*bundle_size*sizeof(double));
      for (i=0; i<x_size; i++) {
	for (j=0; j<y_size; j++) {
	  for (k=0; k<bundle_size; k++) {
	    memcpy(fld2+k*y_size*x_size+j*x_size+i, fld1+(i*y_size*bundle_size+j*bundle_size+k)*sizeof(double), sizeof(double));
	  }
	}
      }
      oasis_put_iso_double(&var_id, &kstep, &x_size, &y_size, &bundle_size, fld2, kinfo, &write_restart);
      free(fld2);
    } else {
      oasis_c_abort(0, "oasis_c_put", "fkind argument can only be OASIS_Real or OASIS_Double", __FILE__, __LINE__);
    }
  }
  if ( IS_VALID_PUT(*kinfo) ) {
    return OASIS_Ok;
  } else {
    return OASIS_Error;
  }
}

int oasis_c_get(const int var_id, const int kstep, const int x_size, const int y_size, const int bundle_size, const int fkind, const int storage, void* fld1, int* kinfo){
  bool storage_is1D = ((int)( x_size == 1 ) + (int)( y_size == 1 ) + (int)( bundle_size == 1 )) == 2;
  if ( storage != OASIS_COL_MAJOR && storage != OASIS_ROW_MAJOR )
    oasis_c_abort(0, "oasis_c_get", "storage argument can only be OASIS_ROW_MAJOR or OASIS_COL_MAJOR", __FILE__, __LINE__);
  if ( storage == OASIS_COL_MAJOR || storage_is1D ) {
    if ( fkind == OASIS_Real ) {
      oasis_get_iso_float(&var_id, &kstep, &x_size, &y_size, &bundle_size, (float*)fld1, kinfo);
    } else if ( fkind == OASIS_Double ) {
      oasis_get_iso_double(&var_id, &kstep, &x_size, &y_size, &bundle_size, fld1, kinfo);
    } else {
      oasis_c_abort(0, "oasis_c_get", "fkind argument can only be OASIS_Real or OASIS_Double", __FILE__, __LINE__);
    }
  } else {
    if ( fkind == OASIS_Real ) {
      float* fld2;
      int i,j,k;
      fld2 = (float*) malloc(x_size*y_size*bundle_size*sizeof(float));
      oasis_get_iso_float(&var_id, &kstep, &x_size, &y_size, &bundle_size, fld2, kinfo);
      for (i=0; i<x_size; i++) {
	for (j=0; j<y_size; j++) {
	  for (k=0; k<bundle_size; k++) {
	    memcpy(fld1+(i*y_size*bundle_size+j*bundle_size+k)*sizeof(float), fld2+k*y_size*x_size+j*x_size+i, sizeof(float));
	  }
	}
      }
      free(fld2);
    } else if ( fkind == OASIS_Double ) {
      double* fld2;
      int i,j,k;
      fld2 = (double*) malloc(x_size*y_size*bundle_size*sizeof(double));
      oasis_get_iso_double(&var_id, &kstep, &x_size, &y_size, &bundle_size, fld2, kinfo);
      for (i=0; i<x_size; i++) {
	for (j=0; j<y_size; j++) {
	  for (k=0; k<bundle_size; k++) {
	    memcpy(fld1+(i*y_size*bundle_size+j*bundle_size+k)*sizeof(double), fld2+k*y_size*x_size+j*x_size+i, sizeof(double));
	  }
	}
      }
      free(fld2);
    } else {
      oasis_c_abort(0, "oasis_c_get", "fkind argument can only be OASIS_Real or OASIS_Double", __FILE__, __LINE__);
    }
  }
  if ( IS_VALID_GET(*kinfo) ) {
    return OASIS_Ok;
  } else {
    return OASIS_Error;
  }
}
