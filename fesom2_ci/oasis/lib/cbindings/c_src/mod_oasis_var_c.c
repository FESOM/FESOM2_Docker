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

int oasis_c_def_var(int* id_nports, const char* cdport, const int id_part, const int bundle_size, const int kinout, const int ktype){
  int kinfo;
  if ( kinout != OASIS_OUT && kinout != OASIS_IN )
    oasis_c_abort(0, "oasis_c_def_var", "kinout argument can only be OASIS_IN or OASIS_OUT", __FILE__, __LINE__);
  if ( ktype != OASIS_Real && ktype != OASIS_Double )
    oasis_c_abort(0, "oasis_c_def_var", "ktype argument can only be OASIS_Real or OASIS_Double", __FILE__, __LINE__);
  oasis_def_var_iso(id_nports, &cdport, &id_part, &bundle_size, &kinout, &ktype, &kinfo);
  return kinfo;
}
