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


"""Auxiliary OASIS user interfaces"""

import ctypes
from ctypes import cdll, CDLL, c_int
import numpy
import pyoasis.parameters

cdll.LoadLibrary("liboasis.cbind.so")
LIB = CDLL("liboasis.cbind.so")

LIB.oasis_c_get_localcomm_iso2c.argtypes = [ctypes.POINTER(ctypes.c_int)]
LIB.oasis_c_get_localcomm_iso2c.restype = ctypes.c_int


def get_localcomm():
    """OASIS user query for the local MPI communicator"""
    localcomm = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_get_localcomm_iso2c(localcomm)
    return localcomm.value, kinfo


LIB.oasis_c_create_couplcomm_iso2c.argtypes = [ctypes.c_int, ctypes.c_int,
                                 ctypes.POINTER(ctypes.c_int)]
LIB.oasis_c_create_couplcomm_iso2c.restype = ctypes.c_int


def create_couplcomm(icpl, allcomm):
    """OASIS user call to create a new communicator"""
    cplcomm = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_create_couplcomm_iso2c(icpl, allcomm, cplcomm)
    return cplcomm.value, kinfo


LIB.oasis_c_set_couplcomm_iso2c.argtypes = [ctypes.c_int]
LIB.oasis_c_set_couplcomm_iso2c.restype = ctypes.c_int


def set_couplcomm(couplcomm):
    """OASIS user call to specify a local communicator"""
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_set_couplcomm_iso2c(couplcomm.py2f())
    return kinfo


LIB.oasis_c_get_intercomm_iso2c.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_char_p]
LIB.oasis_c_get_intercomm_iso2c.restype = ctypes.c_int


def get_intercomm(cdnam):
    """OASIS user interface to establish an intercomm communicator between the root of two models"""
    new_comm = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_get_intercomm_iso2c(new_comm, cdnam.encode())
    return new_comm.value, kinfo


LIB.oasis_c_get_intracomm_iso2c.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_char_p]
LIB.oasis_c_get_intracomm_iso2c.restype = ctypes.c_int


def get_intracomm(cdnam):
    """OASIS user interface to establish an intracomm communicator between the root of two models"""
    new_comm = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_get_intracomm_iso2c(new_comm, cdnam.encode())
    return new_comm.value, kinfo


LIB.oasis_c_get_multi_intracomm_iso2c.argtypes = [ctypes.POINTER(ctypes.c_int), ctypes.c_int, ctypes.POINTER(ctypes.c_char_p), ctypes.c_void_p]
LIB.oasis_c_get_multi_intracomm_iso2c.restype = ctypes.c_int


def get_multi_intracomm(cdnam):
    """OASIS user interface to establish an intracomm communicator between the root of more than two models"""
    if isinstance(cdnam, list):
        ncomp = len(cdnam)
    else:
        ncomp = 1
        cdnam = [cdnam]
    new_comm = c_int(0)
    root_ranks_p = numpy.zeros(ncomp, dtype=numpy.int32)
    cdnam_p = (ctypes.c_char_p * ncomp)()
    for i, comp in enumerate(cdnam):
        cdnam_p[i] = comp.encode()
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_get_multi_intracomm_iso2c(new_comm, c_int(ncomp), cdnam_p, root_ranks_p.ctypes.data)
    root_ranks_l = root_ranks_p.tolist()
    root_ranks = {}
    for key, value in zip(cdnam, root_ranks_l):
        root_ranks[key] = value
    return new_comm.value, root_ranks, kinfo


LIB.oasis_c_set_debug.argtypes = [ctypes.c_int]
LIB.oasis_c_set_debug.restype = ctypes.c_int


def set_debug(debug):
    """Set debug level"""
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_set_debug(debug)
    return kinfo


LIB.oasis_c_get_debug.argtypes = [ctypes.POINTER(ctypes.c_int)]
LIB.oasis_c_get_debug.restype = ctypes.c_int


def get_debug():
    """Get debug level"""
    debug = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_get_debug(debug)
    return debug.value, kinfo


LIB.oasis_c_put_inquire.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
LIB.oasis_c_put_inquire.restype = ctypes.c_int


def put_inquire(varid, msec):
    """Gives put return code expected at a specified time
    for a given variable"""
    kinfo = c_int(0)
    ierr = c_int(0)
    ierr = LIB.oasis_c_put_inquire(varid, msec, kinfo)
    return kinfo.value, ierr


LIB.oasis_c_get_ncpl.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_int)]
LIB.oasis_c_get_ncpl.restype = ctypes.c_int


def get_ncpl(varid):
    """Returns the number of unique couplings associated with
    a variable."""
    ncpl = c_int(0)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_get_ncpl(varid, ncpl)
    return ncpl.value, kinfo


LIB.oasis_c_get_freqs.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int,
                          ctypes.c_void_p]
LIB.oasis_c_get_freqs.restype = ctypes.c_int


def get_freqs(varid, mop, ncpl):
    """Returns the coupling periods for a given variable."""
    cpl_freqs_p = numpy.zeros(ncpl, dtype=numpy.int32)
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_get_freqs(varid, c_int(mop), c_int(ncpl), cpl_freqs_p.ctypes.data)
    cpl_freqs = cpl_freqs_p.tolist()
    return cpl_freqs, kinfo


def get_freqs_array(varid, mop):
    """Returns the coupling periods for a given variable."""
    ncpl, kinfo = get_ncpl(varid)
    return get_freqs(varid, mop, ncpl)
