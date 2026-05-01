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
from mpi4py import MPI


class Component(object):
    """
    Component that will be coupled by OASIS3-MCT

    :param str name: name of the component
    :param bool coupled: whether the component will be coupled (default: True)
    :param mpi4py.MPI.Intracomm communicator: global MPI communicator (default: MPI.COMM_WORLD)
    :raises OasisException: if OASIS is unable to initialise the component
    :raises PyOasisException: if an incorrect parameter is supplied
    """

    _n_components = 0

    def __init__(self, name, coupled=True, communicator=None):
        """Constructor"""
        self._initialised = False
        pyoasis.checktypes.check_types([str, bool, MPI.Intracomm],
                                       [name, coupled,
                                       communicator])
        if Component._n_components > 0:
            raise pyoasis.PyOasisException("There should be only one component.")

        Component._n_components += 1

        if len(name) == 0:
            raise pyoasis.PyOasisException("Component name empty.")
        self._name = name
        if communicator:
            self._communicator = communicator
            return_value = pyoasis.mod_oasis_method.init_comp_with_comm(self._name,
                                                                        coupled,
                                                                        self._communicator)
        else:
            return_value = pyoasis.mod_oasis_method.init_comp(self._name,coupled)
        self._initialised = True
        error = return_value[1]
        if error < 0:
            raise pyoasis.OasisException("Error initialising component " + self._name,
                                         error)
        self._id = return_value[0]
        return_value = pyoasis.mod_oasis_auxiliary_routines.get_localcomm()
        error = return_value[1]
        if error < 0:
            raise pyoasis.OasisException("Error in get_localcomm", error)
        self._localcomm_hdle = return_value[0]
        try:
            self.localcomm = MPI.Comm.f2py(self._localcomm_hdle)
        except MPI.Exception:
            self.localcomm = MPI.COMM_NULL
        self.couplcomm = MPI.Comm.Dup(self.localcomm)

    def __del__(self):
        """
        Destructor
        Ends the coupling.
        """
        if self._initialised:
            try:
                error = pyoasis.mod_oasis_method.terminate()
                if error < 0:
                    pyoasis.oasis_abort(self._id, "Component::__del__",
                                        "oasis_terminate failed",
                                        "component.py", 79, error)
                self._initialised = False
            except AttributeError:
                pass

    @property
    def name(self):
        """
        :returns: the name of the component
        :rtype: string
        """
        return self._name

    def create_couplcomm(self, coupled):
        """
        Creates a coupling communicator toto

        :param bool coupled: coupling flag

        :returns: error code
        :rtype: int

        :raises OasisException: if OASIS is unable to create the coupling \
                                communicator
        :raises PyOasisException: if an incorrect parameter is supplied
        """
        allcomm = self._localcomm_hdle
        pyoasis.check_types([bool, int], [coupled, allcomm])
        if coupled:
            icpl = 1
        else:
            icpl = MPI.UNDEFINED
        return_value = pyoasis.mod_oasis_auxiliary_routines.create_couplcomm(icpl,
                                                                             allcomm)
        error = return_value[1]
        if error < 0:
            raise pyoasis.OasisException("Error in create_couplcomm", error)
        self._couplcomm_hdle = return_value[0]
        try:
            self.couplcomm = MPI.Comm.f2py(self._couplcomm_hdle)
        except MPI.Exception:
            self.couplcomm = MPI.COMM_NULL

        return error

    def set_couplcomm(self, couplcomm):
        """
        Sets the coupling communicator
        :param MPI.communicator couplcomm: coupling communicator

        :returns: error code
        :rtype: int

        :raises OasisException: if OASIS is unable to set the coupling \
                                communicator
        :raises PyOasisException: if an incorrect parameter is supplied
        """
        error = pyoasis.mod_oasis_auxiliary_routines.set_couplcomm(couplcomm)
        if error < 0:
            raise pyoasis.OasisException("Error in set_couplcomm", error)
        self._couplcomm_hdle = couplcomm.py2f()
        self.couplcomm = couplcomm

        return error

    def get_intracomm(self, compname):
        """
        :param string compname: name of the other component in the intracommunicator
        :returns: the intracommunicator
        :rtype: MPI.communicator
        :raises OasisException: if OASIS is unable to create the intracommunicator
        :raises PyOasisException: if an incorrect parameter is supplied
        """
        pyoasis.check_types([str],[compname])
        new_comm, error = pyoasis.mod_oasis_auxiliary_routines.get_intracomm(compname)
        if error < 0:
            raise pyoasis.OasisException("Error in get_intracomm", error)
        try:
            return MPI.Comm.f2py(new_comm)
        except MPI.Exception:
            raise pyoasis.OasisException("Error in get_intracomm conversion",
                                         -1)

    def get_multi_intracomm(self, complist):
        """
        :param string complist: list of names of the other component in the intracommunicator
        :returns: the intracommunicator and a dictionary of the ranks of the component roots in the intracommunicator
        :rtype: MPI.communicator, dict
        :raises OasisException: if OASIS is unable to create the intracommunicator
        :raises PyOasisException: if an incorrect parameter is supplied
        """
        pyoasis.check_types([list],[complist])
        new_comm, root_ranks, error = pyoasis.mod_oasis_auxiliary_routines.get_multi_intracomm(complist)
        if error < 0:
            raise pyoasis.OasisException("Error in get_multi_intracomm", error)
        try:
            return MPI.Comm.f2py(new_comm), root_ranks
        except MPI.Exception:
            raise pyoasis.OasisException("Error in get_multi_intracomm conversion",
                                         -1)

    def get_intercomm(self, compname):
        """
        :param string compname: name of the other component
         in the intercommunicator
        :returns: the intercommunicator
        :rtype: MPI.communicator
        :raises OasisException: if OASIS is unable to create
        the intercommunicator
        :raises PyOasisException: if an incorrect parameter is supplied
        """
        pyoasis.check_types([str], [compname])
        new_comm, error = pyoasis.mod_oasis_auxiliary_routines.get_intercomm(compname)
        if error < 0:
            raise pyoasis.OasisException("Error in get_intercomm", error)
        try:
            return MPI.Comm.f2py(new_comm)
        except MPI.Exception:
            raise pyoasis.OasisException("Error in get_intercomm conversion",
                                         -1)

    @staticmethod
    def enddef():
        """
        Ends the initialisation of the component.

        :raises OasisException: if OASIS is unable to end the \
                                initialisation
        """
        error = pyoasis.mod_oasis_method.enddef()
        if error < 0:
            raise pyoasis.OasisException("Error in enddef", error)

    def __str__(self):
        return "Component: name: " + self._name + ", id: " + str(self._id)

    @property
    def debug_level(self):
        """
        Returns the currently set debug level

        :returns: debug level
        :rtype: int

        :raises OasisException: if OASIS is unable to get the debug level
        """
        return pyoasis.get_debug()

    @debug_level.setter
    def debug_level(self, level):
        """
        Set a new debug level
        :param int level: debug level
        :raises OasisException: if OASIS is unable to get the debug level
        """
        pyoasis.set_debug(level)
