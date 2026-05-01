# pyOASIS - A Python wrapper for OASIS
# Authors: Philippe Gambron, Rupert Ford
# Copyright (C) 2019 UKRI - STFC

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.

# A copy of the GNU Lesser General Public License, version 3, is supplied
# with this program, in the file lgpl-3.0.txt. It is also available at
# <https://www.gnu.org/licenses/lgpl-3.0.html>.


"""OASIS send/receive (put/get) user interfaces"""

import pyoasis
import ctypes
import numpy as np
from numpy import float32, float64
from ctypes import c_int, cdll, CDLL

cdll.LoadLibrary("liboasis.cbind.so")
LIB = CDLL("liboasis.cbind.so")


def get_sizes(field):
    """Creates an array containing the dimensions of multidimensional fields"""
    sizes = np.ones(3, np.int32)
    sizes[:field.ndim] = field.shape
    return sizes


LIB.oasis_c_put.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int,
                            ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_void_p,
                            ctypes.c_bool, ctypes.POINTER(ctypes.c_int)]
LIB.oasis_c_put.restype = ctypes.c_int


def put(var_id, kstep, field, write_restart):
    """Send 8-byte multidimensional field"""
    sizes = get_sizes(field)
    kinfo = c_int(0)
    ierr = c_int(0)
    p_field = field.ctypes.data
    storage = c_int(1) # colum-major storage cf. OASIS_COL_MAJOR in oasis_c.h 
    if field.dtype == float32:
        fkind = c_int(4)
    elif field.dtype == float64:
        fkind = c_int(8)
    else:
        raise pyoasis.PyOasisException("Data type of field can only by float32 or float64")
    ierr = LIB.oasis_c_put(var_id, kstep, sizes[0], sizes[1], sizes[2], fkind, storage,
                           p_field, write_restart, kinfo)
    if (pyoasis.OasisParameters(ierr) != pyoasis.OasisParameters.OASIS_OK):
        return ierr
    else:
        return kinfo.value


LIB.oasis_c_get.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int,
                            ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_void_p,
                            ctypes.POINTER(ctypes.c_int)]
LIB.oasis_c_get.restype = ctypes.c_int


def get(var_id, kstep, field):
    """Receive 8-byte multidimensional field"""
    sizes = get_sizes(field)
    kinfo = c_int(0)
    ierr = c_int(0)
    p_field = field.ctypes.data
    storage = c_int(1) # colum-major storage cf. OASIS_COL_MAJOR in oasis_c.h 
    if field.dtype == float32:
        fkind = c_int(4)
    elif field.dtype == float64:
        fkind = c_int(8)
    else:
        raise pyoasis.PyOasisException("Data type of field can only by float32 or float64")
    ierr = LIB.oasis_c_get(var_id, kstep, sizes[0], sizes[1], sizes[2], fkind, storage, p_field, kinfo)
    if (pyoasis.OasisParameters(ierr) != pyoasis.OasisParameters.OASIS_OK):
        return ierr
    else:
        return kinfo.value
