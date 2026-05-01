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


"""OASIS variable data and methods"""

from enum import Enum
import ctypes
from ctypes import cdll, CDLL, c_int, c_char_p


class OasisVarParameters(Enum):
    """"""
    OASIS_DOUBLE = 8


cdll.LoadLibrary("liboasis.cbind.so")
LIB = CDLL("liboasis.cbind.so")


LIB.oasis_c_def_var.argtypes = [ctypes.POINTER(ctypes.c_int), c_char_p, ctypes.c_int,
                                ctypes.c_int, ctypes.c_int, ctypes.c_int]
LIB.oasis_c_def_var.restype = ctypes.c_int

def def_var(id_part, cdport, id_var_nodims, kinout):
    """The OASIS user interface to define variables"""
    id_nports = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_def_var(id_nports, cdport.encode(), id_part, id_var_nodims,
                                kinout, OasisVarParameters.OASIS_DOUBLE.value)
    return id_nports.value, kinfo
