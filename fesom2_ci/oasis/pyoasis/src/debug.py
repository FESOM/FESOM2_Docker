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


import pyoasis.mod_oasis_auxiliary_routines

import pyoasis.exception
import pyoasis.checktypes


def set_debug(debug):
    pyoasis.check_types([int], [debug])
    if debug < 0:
        raise pyoasis.PyOasisException("Negative debug level")
    error = pyoasis.mod_oasis_auxiliary_routines.set_debug(debug)
    if error < 0:
        raise pyoasis.OasisException("Error in setting debug level", error)


def get_debug():
    rv = pyoasis.mod_oasis_auxiliary_routines.get_debug()
    error = rv[1]
    if error < 0:
        raise pyoasis.OasisException("Error in getting debug level", error)
    debug = rv[0]
    return debug
