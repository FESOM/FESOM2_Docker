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
import pyoasis.mod_oasis_getput_interface
import pyoasis.mod_oasis_method
import pyoasis.mod_oasis_part
import pyoasis.mod_oasis_sys
import pyoasis.mod_oasis_var


class Partition(object):
    """Base class handling a partition"""

    def _set(self, parameters, global_size, local_size, name):
        """Sets up the partition. Will be called by the inherited classes.
        :raises: OasisException if OASIS is unable to initialise the\
        partition
        :raises PyOasisException: if an incorrect parameter is supplied
"""
        self._local_size = local_size

        return_value = pyoasis.mod_oasis_part.def_partition(parameters,
                                                            global_size, name)
        error = return_value[1]
        if error < 0:
            raise pyoasis.OasisException("Error in def_partition", error)
        self._id = return_value[0]

    @property
    def local_size(self):
        return self._local_size

    def __str__(self):
        return "Partition: id: " + str(self._id)


class SerialPartition(Partition):
    """
    Serial partition

    :param int size: number of points in the partition
    :param int global_size: global size of the grid (optional)
    :param str name: name of the partition (optional)
    :raises OasisException: if OASIS is unable to initialise the partition
    :raises PyOasisException: if an incorrect parameter is supplied
    """

    def __init__(self, size, global_size=-1, name=""):
        """Constructor"""
        pyoasis.check_types([int, int, str], [size, global_size, name])
        if size <= 0:
            raise pyoasis.PyOasisException("Size must be >0.")

        local_size = size

        parameters = [0, 0, size]
        self._set(parameters, global_size, local_size, name)


class ApplePartition(Partition):
    """
    Apple partition

    :param int offset: offset according to the global index
    :param int size: number of points in the partition
    :param int global_size: global size of the grid (optional)
    :param str name: name of the partition (optional)
    :raises OasisException: if OASIS is unable to initialise the
    partition
    :raises PyOasisException: if an incorrect parameter is supplied
    """

    def __init__(self, offset, size, global_size=-1, name=""):
        """Constructor"""
        pyoasis.check_types([int, int, int, str], [offset, size,
                            global_size, name])
        if offset < 0:
            raise pyoasis.PyOasisException("Offset <0.")
        if size <= 0:
            raise pyoasis.PyOasisException("Size <=0.")

        local_size = size

        parameters = [1, offset, size]
        self._set(parameters, global_size, local_size, name)


class BoxPartition(Partition):
    """
    Box partition

    :param int global_offset: offset according to the global index
    :param int local_extent_x: extent in the x direction of the local \
                               partition
    :param int local_extent_y: extent in the y direction of the local \
                               partition
    :param int global_extent_x: global extent in the x direction
    :param int global_size: global size of the grid (optional)
    :param str name: name of the partition (optional)
    :raises OasisException: if OASIS is unable to initialise the partition
    :raises PyOasisException: if an incorrect parameter is supplied
    """

    def __init__(self, global_offset, local_extent_x, local_extent_y,
                 global_extent_x, global_size=-1, name=""):
        """Constructor"""
        pyoasis.check_types([int, int, int, int, int, str],
                            [global_offset, local_extent_x, local_extent_y,
                             global_extent_x, global_size, name])
        if global_offset < 0:
            raise pyoasis.PyOasisException("Global offset <0.")

        if local_extent_x < 0:
            raise pyoasis.PyOasisException("Local extent in x-direction <=0.")

        if local_extent_y < 0:
            raise pyoasis.PyOasisException("Local extent in y-direction <=0.")
        if global_extent_x <= 0:
            raise pyoasis.PyOasisException("Global extent in x-direction <=0.")

        local_size = local_extent_x * local_extent_y

        parameters = [2, global_offset, local_extent_x, local_extent_y,
                      global_extent_x]
        self._set(parameters, global_size, local_size, name)


class OrangePartition(Partition):
    """
    Orange partition

    :param offsets: list of offsets according to the global index
    :type offsets: list of integers
    :param extents: list of the partition extents
    :type extents: list of integers
    :param int global_size: global size of the grid (optional)
    :param str name: name of the partition (optional)
    :raises OasisException: if OASIS is unable to initialise the partition
    :raises PyOasisException: if an incorrect parameter is supplied
    """

    def __init__(self, offsets, extents, global_size=-1, name=""):
        """Constructor"""
        pyoasis.check_types([list, list, int, str], [offsets, extents,
                            global_size, name])
        n_offsets = len(offsets)
        if len(extents) != n_offsets:
            raise pyoasis.PyOasisException("Number of offsets != number of extents")
        for offset in offsets:
            if offset < 0:
                raise pyoasis.PyOasisException("Offset <0.")
        for extent in extents:
            if extent <= 0:
                raise pyoasis.PyOasisException("Extent <=0.")

        local_size = sum(extents)

        parameters = [3, n_offsets]
        for i in range(n_offsets):
            parameters.append(offsets[i])
            parameters.append(extents[i])
        self._set(parameters, global_size, local_size, name)


class PointsPartition(Partition):
    """
    Points partition

    :param global_indices: list containing the global indices of the
                           points in the partition
    :type global_indices: list of integers
    :param int global_size: global size of the grid (optional)
    :param str name: name of the partition (optional)
    :raises OasisException: if OASIS is unable to initialise the partition
    :raises PyOasisException: if an incorrect parameter is supplied
    """

    def __init__(self, global_indices, global_size=-1, name=""):
        """Constructor"""
        pyoasis.check_types([list, int, str], [global_indices, global_size,
                            name])
        if len(global_indices) == 0:
            raise pyoasis.PyOasisException("Global indices list empty.")

        local_size = len(global_indices)

        parameters = [4, len(global_indices)]
        for index in global_indices:
            parameters.append(index)
        self._set(parameters, global_size, local_size, name)
