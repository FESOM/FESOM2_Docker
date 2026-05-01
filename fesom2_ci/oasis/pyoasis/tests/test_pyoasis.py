#!/usr/bin/env python3

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


import pytest
import numpy
import pyoasis
from mpi4py import MPI


# Functions for monkeypatching
def returns_zero(*args):
    return 0

def returns_2_zeros(*args):
    return [0, 0]

def returns_error(*args):
    return -1

def returns_2errors(*args):
    return [-1, -1]

def returns_comm_handle_and_zero(*args):
    return [MPI.COMM_WORLD.py2f(), 0]

def returns_comm_handle_and_error(*args):
    return [MPI.COMM_WORLD.py2f(), -1]

def returns_comm_handle_and_2errors(*args):
    return [MPI.COMM_WORLD.py2f(), -1, -1]

# Compoment class
# Constructor

# Wrong type for 1st argument
def test_Component_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component(42, True)

# Wrong type for 2nd argument
def test_component_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name", 42)

# Wrong type for 3rd argument
def test_component_constructor3():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp_with_comm = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name", True, 42)

# Empty name
def test_component_constructor4():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("")

# 2 components
def test_component_constructor5():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate=returns_zero
        pyoasis.mod_oasis_auxiliary_routines.get_localcomm = returns_comm_handle_and_zero
        pyoasis.Component._n_components = 0
        comp1 = pyoasis.Component("component1")
        comp2 = pyoasis.Component("component2")

# Failure
def test_component_constructor6():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2errors
        pyoasis.mod_oasis_method.terminate=returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")

# get_localcomm failing in constructor
def test_component_constructor7():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_auxiliary_routines.get_localcomm = returns_comm_handle_and_error
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")

# name
def test_component_name():
    pyoasis.mod_oasis_auxiliary_routines.get_localcomm = returns_comm_handle_and_zero
    pyoasis.mod_oasis_method.init_comp = returns_2_zeros
    pyoasis.mod_oasis_method.terminate=returns_zero
    pyoasis.Component._n_components = 0
    name = "name"
    comp = pyoasis.Component(name)
    assert(comp.name == name)

# __del__ failing
def test_destructor():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_auxiliary_routines.get_localcomm = returns_comm_handle_and_zero
        pyoasis.mod_oasis_method.init_comp = returns_2errors
        pyoasis.mod_oasis_method.terminate = returns_error
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")

# create_couplcomm
# Wrong argument type
def test_component_create_couplcomm():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_auxiliary_routines.get_localcomm = returns_comm_handle_and_zero
        pyoasis.mod_oasis_auxiliary_routines.create_couplcomm = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        couplcomm =  comp.create_couplcomm("abc")

# create_couplcomm
# Failure
def test_component_create_couplcomm3():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_auxiliary_routines.create_couplcomm = returns_2errors
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        couplcomm = comp.create_couplcomm(True)

# set_couplcomm
# Failure
def test_component_set_couplcomm():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_auxiliary_routines.create_couplcomm = returns_2errors
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.pyoasis.mod_oasis_auxiliary_routines.set_couplcomm = returns_error
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        comp.set_couplcomm(MPI.COMM_NULL)

# get_intracomm
# Failure
def test_component_get_intracomm():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_auxiliary_routines.create_couplcomm = returns_2errors
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.mod_oasis_auxiliary_routines.get_intracomm = returns_2errors
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        comp.get_intracomm("othercomponent")

# get_intercomm
# Failure
def test_component_set_intercomm():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_auxiliary_routines.create_couplcomm = returns_2errors
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.mod_oasis_auxiliary_routines.get_intercomm = returns_2errors
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        comp.get_intercomm("othercomponent")

# get_multi_intracomm
# Wrong call arguments (component name is not a strings list)
def test_component_get_multi_intracomm1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        comp.get_multi_intracomm(["othercomponent", 42])

# Wrong call arguments (component name is not a list)
def test_component_get_multi_intracomm2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        comp.get_multi_intracomm("othercomponent")

# Failure
def test_component_get_multi_intracomm3():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.mod_oasis_auxiliary_routines.get_multi_intracomm = returns_comm_handle_and_2errors
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        comp.get_multi_intracomm(["othercomponent", "another"])

# Various functions
def test_Component_various_functions():
    pyoasis.mod_oasis_method.init_comp = returns_2_zeros
    pyoasis.mod_oasis_auxiliary_routines.create_couplcomm = returns_2_zeros
    pyoasis.mod_oasis_method.terminate = returns_zero
    pyoasis.Component._n_components = 0
    comp = pyoasis.Component("name")
    assert comp._name == "name"
    assert comp.create_couplcomm(True) == 0

# enddef
# failure
def test_Component_enddef():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_method.init_comp = returns_2_zeros
        pyoasis.mod_oasis_method.enddef = returns_error
        pyoasis.mod_oasis_method.terminate = returns_zero
        pyoasis.Component._n_components = 0
        comp = pyoasis.Component("name")
        localcomm =  comp.enddef()

# __str__
def test_Component_str():
    pyoasis.mod_oasis_method.init_comp = returns_2_zeros
    pyoasis.mod_oasis_method.terminate = returns_zero
    pyoasis.mod_oasis_method.terminate = returns_zero
    pyoasis.Component._n_components = 0
    name = "name"
    comp = pyoasis.Component(name)
    line = str(comp)
    assert line.find(comp._name) >=0
    assert line.find(str(comp._id)) >=0


# SerialPartition
# Constructor

# Wrong argument type
def test_SerialPartition_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.SerialPartition("abc")

# Wrong argument value
def test_SerialPartition_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.SerialPartition(-1)

# Failure
def test_SerialPartition_constructor3():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2errors
        partition = pyoasis.SerialPartition(4)


# __str__
def test_SerialPartition_str():
    pyoasis.mod_oasis_method.init_comp = returns_2_zeros
    pyoasis.mod_oasis_part.def_partition = returns_2_zeros
    partition = pyoasis.SerialPartition(4)
    line = str(partition)
    assert line.find(str(partition._id)) >=0


# ApplePartition
# Constructor

# Wrong 1st argument type
def test_ApplePartition_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.ApplePartition("abc", 4)

# Wrong 2nd argument type
def test_ApplePartition_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.ApplePartition(0, "abc")

# Wrong 1st argument value
def test_ApplePartition_constructor3():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.ApplePartition(-1, 4)

# Wrong 2nd argument value
def test_ApplePartition_constructor4():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.ApplePartition(0, -1)

# Failure
def test_ApplePartition_constructor5():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2errors
        partition = pyoasis.ApplePartition(0, 4)

# __str__
def test_ApplePartition_str():
    pyoasis.mod_oasis_method.init_comp = returns_2_zeros
    pyoasis.mod_oasis_part.def_partition = returns_2_zeros
    partition = pyoasis.ApplePartition(0, 4)
    line = str(partition)
    assert line.find(str(partition._id)) >=0


# BoxPartition
# Constructor

# Wrong 1st argument type
def test_BoxPartition_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition("abc", 10, 10, 10)

# Wrong 2nd argument type
def test_BoxPartition_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition(0, "abc", 10, 10)

# Wrong 3rd argument type
def test_BoxPartition_constructor3():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition(0, 10, "abc", 10)

# Wrong 4th argument type
def test_BoxPartition_constructor4():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition(0, 10, 10, "abc")

# Wrong 1st argument value
def test_BoxPartition_constructor5():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition(-1, 10, 10, 10)

# Wrong 2nd argument value
def test_BoxPartition_constructor6():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition(0, -1, 10, 10)

# Wrong 3rd argument value
def test_BoxPartition_constructor7():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition(0, 10, -1, 10)

# Wrong 4th argument value
def test_BoxPartition_constructor8():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.BoxPartition(0, 10, 10, -1)

# Failure
def test_BoxPartition_constructor9():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2errors
        partition = pyoasis.BoxPartition(0, 10, 10, 10)


# OrangePartition
# Constructor

# Wrong 1st argument type
def test_OrangePartition_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.OrangePartition("abc", [2, 2])

# Wrong 1st argument type
def test_OrangePartition_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.OrangePartition(["a", "b"], [2, 2])

# Wrong 2nd argument type
def test_OrangePartition_constructor3():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.OrangePartition([0, 0], "abc")

# Wrong 2nd argument type
def test_OrangePartition_constructor4():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.OrangePartition([0, 2], ["a", "b"])

# Wrong 1st argument value
def test_OrangePartition_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.OrangePartition([-1, 2], [2, 2])

# Wrong 2nd argument value
def test_OrangePartition_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.OrangePartition([0, 2], [-1, 2])

# Inconsistent list sizes
def test_OrangePartition_constructor3():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.OrangePartition([0, 2, 4], [2, 2])

# Failure
def test_OrangePartition_constructor4():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2errors
        partition = pyoasis.OrangePartition([0, 2], [2, 2])


# PointsPartition
# Constructor

# Wrong 1st argument type
def test_PointsPartition_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.PointsPartition("abc")

# Wrong 1st argument type
def test_PointsPartition_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        partition = pyoasis.PointsPartition(["abc", 7])

# Empty list
def test_PointsPartition_constructor3():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        points = []
        partition = pyoasis.PointsPartition(points)

# Failure
def test_PointsPartition_constructor4():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2errors
        partition = pyoasis.PointsPartition([0, 1])


# Var
# Constructor

# Wrong type 1st argument
def test_Var_constructor1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var(42, partition, pyoasis.OasisParameters.OASIS_OUT, 1)

# Wrong type 2nd argument
def test_Var_constructor2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", 42, pyoasis.OasisParameters.OASIS_OUT, 1)

# Wrong type 3rd argument
def test_Var_constructor3():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, "abc", 1)

# Wrong type 4th argument
def test_Var_constructor4():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT, "abc")

# Wrong value 1st argument
def test_Var_constructor5():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("", partition, pyoasis.OasisParameters.OASIS_OUT, 1)

# Wrong value 4th argument
def test_Var_constructor6():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT, 0)

# Failure
def test_Var_constructor8():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2errors
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT)

# partition_id < 0
def test_Var_constructor9():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        partition = pyoasis.SerialPartition(4)
        partition._id=-1
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT)

#name
def test_Var_name():
    pyoasis.mod_oasis_part.def_partition = returns_2_zeros
    pyoasis.mod_oasis_var.def_var = returns_2_zeros
    pyoasis.mod_oasis_getput_interface.put=returns_zero
    partition = pyoasis.SerialPartition(4)
    name = "name"
    var = pyoasis.Var(name, partition, pyoasis.OasisParameters.OASIS_OUT)
    assert(var.name == name)

# put
# Wrong type 1st argument
def test_Var_put1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_getput_interface.put=returns_zero
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT)
        field = pyoasis.asarray(range(4))
        var.put("abc", field)

# Wrong type 2nd argument
def test_Var_put2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_getput_interface.put=returns_zero
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT)
        field = pyoasis.asarray(range(4))
        var.put(0, 42)

# Field wrong side
def test_Var_put4():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_getput_interface.put = returns_zero
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT)
        field = pyoasis.asarray(range(4), range(4))
        var.put(0, field)

# Failure
def test_Var_put3():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_getput_interface.put = returns_error
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_OUT)
        field = pyoasis.asarray(range(4))
        var.put(0, field)

# get
# Wrong type 1st argument
def test_Var_get1():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_getput_interface.get = returns_zero
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_IN)
        field = pyoasis.asarray(numpy.zeros(4))
        var.get("abc", field)

# Wrong type 2nd argument
def test_Var_get2():
    with pytest.raises(pyoasis.PyOasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_getput_interface.get = returns_zero
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_IN)
        field = pyoasis.asarray(numpy.zeros(4))
        var.get(0, 42)

# Failure
def test_Var_get3():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_getput_interface.get = returns_error
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_IN)
        field = pyoasis.asarray(numpy.zeros(4))
        var.get(0, field)

# __str__
def test_SerialPartition_str():
    pyoasis.mod_oasis_part.def_partition = returns_2_zeros
    pyoasis.mod_oasis_var.def_var = returns_2_zeros
    pyoasis.mod_oasis_getput_interface.get = returns_zero
    partition = pyoasis.SerialPartition(4)
    var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_IN)
    line = str(var)
    assert line.find(var._name) >=0
    assert line.find(str(var._id)) >=0

# cpl_freqs
def test_Var_cpl_freqs():
    with pytest.raises(pyoasis.OasisException):
        pyoasis.mod_oasis_part.def_partition = returns_2_zeros
        pyoasis.mod_oasis_var.def_var = returns_2_zeros
        pyoasis.mod_oasis_auxiliary_routines.get_freqs_array = returns_2errors
        partition = pyoasis.SerialPartition(4)
        var = pyoasis.Var("name", partition, pyoasis.OasisParameters.OASIS_IN)
        var.cpl_freqs


# Grid
# Constructor
# Grid name empty
def test_Grid_constructor():
    with pytest.raises(pyoasis.PyOasisException):
        grid = pyoasis.Grid("", 2, 2, pyoasis.asarray([[1, 2], [3, 4]]),
                        pyoasis.asarray([[1, 2], [3, 4]]))
