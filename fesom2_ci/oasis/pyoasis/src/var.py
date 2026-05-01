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


import numpy
import pyoasis.mod_oasis_auxiliary_routines
import pyoasis.mod_oasis_getput_interface
import pyoasis.mod_oasis_method
import pyoasis.mod_oasis_part
import pyoasis.mod_oasis_sys
import pyoasis.mod_oasis_var


class Var:
    """
    Variable data

    :param string name: name of the variable data
    :type partition: partition identifier
    :param inout: flag indicating whether the data is outgoing \
                   or ingoing
    :type inout: pyoasis.OasisParameter
    :param int bundle_size: size of a bundle of fields
    :raises OasisException: if OASIS is unable to initialise \
                            the variable data
    :raises PyOasisException: if an incorrect parameter is supplied
    """

    def __init__(self, name, partition, inout, bundle_size=1):
        """Constructor"""

        pyoasis.check_types([str, pyoasis.Partition,
                            pyoasis.OasisParameters, int],
                            [name, partition, inout, bundle_size])
        if len(name) == 0:
            raise pyoasis.PyOasisException("Name empty")
        _id_partition = partition._id
        self._partition_local_size = partition.local_size
        if _id_partition < 0:
            raise pyoasis.PyOasisException("Partition identifier <0.")
        if not (inout == pyoasis.OasisParameters.OASIS_IN
                or inout == pyoasis.OasisParameters.OASIS_OUT):
            raise pyoasis.PyOasisException("inout parameter neither OASIS_IN or OASIS_OUT.")
        if bundle_size < 1:
            raise pyoasis.PyOasisException("Bundle size <1.")
        self._name = name
        self.bundle_size = bundle_size
        self.direction = inout
        id_var_nodims = bundle_size
        return_value = pyoasis.mod_oasis_var.def_var(_id_partition,
                                                     self._name,
                                                     id_var_nodims,
                                                     self.direction.value)
        error = return_value[1]
        if error < 0:
            raise pyoasis.OasisException("Error in def_var", error)
        self._id = return_value[0]

    def _check_size(self, field):
        if self.bundle_size == 1:
            if field.ndim == 3:
                if field.shape[-1] == 1 and field.size == self._partition_local_size:
                    return True
                else:
                    return False
            else:
                return True
        else:
            if field.ndim >= 2:
                if field.shape[-1] == self.bundle_size:
                    if numpy.prod(field.shape[:-1]) == self._partition_local_size:
                        return True
            return False

    @property
    def name(self):
        """
        :returns: name of variable data
        :rtype: string
        """
        return self._name

    @property
    def is_active(self):
        """
        :returns: flag indicating if the variable is activated in the namcouple
        :rtype: bool
        """
        return self._id != -1
    
    def put(self, time, field, write_restart=False):
        """
        Sends data to another model.

        :param int time: model time (in seconds) [kstep in OASIS]
        :param pyoasis.asarray field: data
        :param bool write_restart: optional flag for writing a restart file

        :raises OasisException: if OASIS is unable to send \
         data to the other component
        :raises PyOasisException: if an incorrect parameter is supplied
        """
        pyoasis.check_types([int, numpy.ndarray, bool], [time, field,
                            write_restart])
        if(not self._check_size(field)):
            raise pyoasis.OasisException("Field of the wrong size", error)
        error = pyoasis.mod_oasis_getput_interface.put(self._id, time,
                                                       field, write_restart)
        if error < 0:
            raise pyoasis.OasisException("Error in sending data to another component", error)

        try:
            return pyoasis.OasisParameters(error)
        except ValueError:
            raise pyoasis.OasisException("Error in put: returned value not mapped to Oasis parameters", -1)

    def get(self, time, field):
        """
        Gets data from another model.

        :param int time: model time (in seconds) [kstep in OASIS]
        :param pyoasis.asarray field: data

        :raises OasisException: if OASIS is unable to receive \
        data from the other component
        :raises PyOasisException: if an incorrect parameter is supplied
        """
        pyoasis.check_types([int, numpy.ndarray], [time, field])
        if(not self._check_size(field)):
            raise pyoasis.OasisException("Field of the wrong size", error)
        error = pyoasis.mod_oasis_getput_interface.get(self._id, time, field)
        if error < 0:
            raise pyoasis.OasisException("Error in getting data from another component",
                                         error)

        try:
            return pyoasis.OasisParameters(error)
        except ValueError:
            raise pyoasis.OasisException("Error in get: returned value not mapped to Oasis parameters", -1)

    def __str__(self):
        return "Variable data: name: " + self._name + ", id: " + str(self._id)

    def put_inquire(self, time):
        """
        :param int time: model time (in seconds) [msec in OASIS]

        :returns: return value expected at a specified time
        for a given variable

        :rtype: pyoasis.OasisParameters

        :raises OasisException: if OASIS is unable to obtain
        the return code

        :raises PyOasisException: if an incorrect parameter is
        supplied
        """
        pyoasis.check_types([int], [time])
        rcode, ierr = pyoasis.mod_oasis_auxiliary_routines.put_inquire(self._id,
                                                                       time)
        
        if (pyoasis.OasisParameters(ierr) != pyoasis.OasisParameters.OASIS_OK):
            raise pyoasis.OasisException("Error in put_inquire: returned value not a valid Put inquire answer", -1)
        
        try:
            return pyoasis.OasisParameters(rcode)
        except ValueError:
            raise pyoasis.OasisException("Error in put_inquire: returned value not mapped to Oasis parameters", -1)

    @property
    def cpl_freqs(self):
        """
        :returns:  the coupling periods
        :rtype: array of integers
        :raises OasisException: if OASIS is unable to obtain the coupling periods
        """
        freqs, error = pyoasis.mod_oasis_auxiliary_routines.get_freqs_array(self._id,
                                                                            self.direction.value)
        if error < 0:
            raise pyoasis.OasisException("Error in getting coupling frequencies",
                                         error)
        return freqs
