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

import pyoasis.mod_oasis_grid
import pyoasis.mod_oasis_part
import numpy


class Grid(object):
    """
    Grid declared via pyoasis API and written to netcdf files grids.nc
    masks.nc areas.nc

    :param string cgrid: grid name (should be shorter than 64 char)
    :param int nx_global: global (non distributed) x size of the grid
    :param int ny_global: global (non distributed) y size of the grid
    :param numpy.array lon: longitudes of the cell centres (2D array)
    :param numpy.array lat: latitudes of the cell centres (2D array)
    :param type partition: optional partition object for distributed grids
    :raises PyOasisException: if the name is empty
    """

    _counter = 0

    def __init__(self, cgrid, nx_global, ny_global, lon, lat, partition=None):
        """Constructor"""
        pyoasis.checktypes.check_types([str, int, int, numpy.ndarray,
                                       numpy.ndarray, pyoasis.Partition],
                                       [cgrid, nx_global, ny_global, lon,
                                       lat, partition])
        if len(cgrid) == 0:
            raise pyoasis.PyOasisException("Grid name empty.")
        self._cgrid = cgrid
        self._nx_glo = nx_global
        self._ny_glo = ny_global
        if partition:
            self._part_id = partition._id
        else:
            self._part_id = -1

        if Grid._counter == 0:
            kinfo = pyoasis.mod_oasis_grid.start_grids_writing()
        Grid._counter += 1
        pyoasis.mod_oasis_grid.write_grid(self._cgrid, self._nx_glo,
                                          self._ny_glo, lon, lat,
                                          self._part_id)

    def set_corners(self, clo, cla):
        """
        Sets corner latitudes and longitudes

        :param clo: array longitudes
        :type clo: array of double-precision floating numbers

        :param cla: array longitudes
        :type cla: array of double-precision floating numbers
        """
        pyoasis.checktypes.check_types([numpy.ndarray, numpy.ndarray],
                                       [clo, cla])
        pyoasis.mod_oasis_grid.write_corner(self._cgrid, self._nx_glo,
                                            self._ny_glo, clo, cla,
                                            self._part_id)

    def set_mask(self, mask, companion=None):
        """
        Sets integer mask values

        :param mask: mask array
        :type mask: array of integer numbers

        :param companion: companion
        :type companion: str
        """
        pyoasis.checktypes.check_types([numpy.ndarray, str], [mask,
                                       companion])
        if not companion:
            companion = "NULL-STRING"
        pyoasis.mod_oasis_grid.write_mask(self._cgrid, self._nx_glo,
                                          self._ny_glo, mask,
                                          self._part_id, companion)

    def set_frac(self, frac, companion=None):
        pyoasis.checktypes.check_types([numpy.ndarray, str], [frac,
                                       companion])
        if not companion:
            companion = "NULL-STRING"
        pyoasis.mod_oasis_grid.write_frac(self._cgrid, self._nx_glo,
                                          self._ny_glo, frac,
                                          self._part_id, companion)

    def set_area(self, area):
        """
        Set area values

        :param area: mask array

        :type area: array of double precision floating numbers
        """
        pyoasis.checktypes.check_types([numpy.ndarray], [area])
        pyoasis.mod_oasis_grid.write_area(self._cgrid, self._nx_glo,
                                          self._ny_glo, area,
                                          self._part_id)

    def set_angle(self, angle):
        """
        Set angle values

        :param angle: mask array

        :type angle: array of double precision floating numbers
        """
        pyoasis.checktypes.check_types([numpy.ndarray], [angle])
        pyoasis.mod_oasis_grid.write_angle(self._cgrid, self._nx_glo,
                                           self._ny_glo, angle,
                                           self._part_id)

    def write(self):
        """
        Writes the grid
        """
        Grid._counter -= 1
        if Grid._counter == 0:
            pyoasis.mod_oasis_grid.terminate_grids_writing()
