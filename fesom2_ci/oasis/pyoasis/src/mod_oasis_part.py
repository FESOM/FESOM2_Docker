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


"""OASIS partition data and methods"""

import numpy
import ctypes
from ctypes import cdll, CDLL, c_int


def asintarray(data):
    """Creates a numpy array containing doubles in Fortran ordering."""
    return numpy.asfortranarray(data, dtype=numpy.int32)


cdll.LoadLibrary("liboasis.cbind.so")
LIB = CDLL("liboasis.cbind.so")

LIB.oasis_c_def_partition.argtypes = [ctypes.POINTER(ctypes.c_int),
                              ctypes.c_int, ctypes.POINTER(ctypes.c_int),
                              ctypes.c_int, ctypes.c_char_p]


def def_partition(parameters, global_size, name):
    """The OASIS user interface to define partitions"""
    id_part = c_int(0)
    kinfo = c_int(0)
    parameters_array = asintarray(parameters)
    n_parameters = len(parameters_array)
    p_parameters = (ctypes.c_int * n_parameters)(*parameters_array)
    kinfo = LIB.oasis_c_def_partition(id_part, n_parameters, p_parameters,
                              global_size, name.encode())
    return id_part.value, kinfo
