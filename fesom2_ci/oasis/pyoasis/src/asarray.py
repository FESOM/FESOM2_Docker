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


import pyoasis
import numpy


def asarray(data, dtype=numpy.float64):
    """
    Numpy array of double precision floating point numbers in Fortran ordering

    :param data: any object that can be used to initialise a numpy array

    :param dtype: the numpy datatype of the returned array

    :raises PyOasisException: if a Numpy array cannot be initialised
    """
    if dtype != numpy.float64 and dtype != numpy.float32:
        raise pyoasis.PyOasisException("Array dtype can only be float32 or float64")
    try:
        return numpy.asfortranarray(data, dtype=dtype)
    except:
        raise pyoasis.PyOasisException("Unable to initialise the Numpy array")
