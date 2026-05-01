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


"""High level OASIS user interfaces"""

import ctypes
from ctypes import cdll, CDLL, c_int, c_char_p


cdll.LoadLibrary("liboasis.cbind.so")
LIB = CDLL("liboasis.cbind.so")


LIB.oasis_c_init_comp_with_comm_iso2c.argtypes = [ctypes.POINTER(ctypes.c_int), c_char_p,
                          ctypes.c_bool, ctypes.c_int]
LIB.oasis_c_init_comp_with_comm_iso2c.restype = ctypes.c_int


def init_comp_with_comm(comp_name, coupled, communicator):
    """OASIS user init method"""
    comp_id = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_init_comp_with_comm_iso2c(comp_id, comp_name.encode(), coupled,
                  communicator.py2f())
    return comp_id.value, kinfo


LIB.oasis_c_init_comp_iso2c.argtypes = [ctypes.POINTER(ctypes.c_int), c_char_p,
                          ctypes.c_bool]
LIB.oasis_c_init_comp_iso2c.restype = ctypes.c_int


def init_comp(comp_name, coupled):
    """OASIS user init method"""
    comp_id = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_init_comp_iso2c(comp_id, comp_name.encode(), coupled)
    return comp_id.value, kinfo


LIB.oasis_c_enddef.argtypes = None
LIB.oasis_c_enddef.restype = ctypes.c_int


def enddef():
    """OASIS user interface specifying the OASIS definition phase is complete"""
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_enddef()
    return kinfo


LIB.oasis_c_terminate.argtypes = None
LIB.oasis_c_terminate.restype = ctypes.c_int


def terminate():
    """OASIS user finalize method"""
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_terminate()
    return kinfo
