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


"""System type methods"""

import ctypes
from ctypes import cdll, CDLL, c_int, c_char_p

cdll.LoadLibrary("liboasis.cbind.so")
LIB = CDLL("liboasis.cbind.so")


LIB.oasis_c_abort.argtypes = [ctypes.c_int, c_char_p, c_char_p, c_char_p, c_int]
LIB.oasis_c_abort.restype = ctypes.c_int

def oasis_abort(comp_id, routine, message, filename, line):
    """OASIS abort method, publicly available to users"""
    kinfo = c_int(0)
    kinfo = LIB.oasis_c_abort(comp_id, routine.encode(), message.encode(),
                    filename.encode(), line)
    return kinfo
