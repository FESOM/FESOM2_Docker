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


import pyoasis.exception


def check_types(types, arguments):
    """Checks the arguments of a function."""
    if len(arguments) != len(types):
        raise pyoasis.PyOasisException("The function requires "
                                       + str(len(types)) + " arguments.")
    i = 0
    for (t, a) in zip(types, arguments):
        if t == list:
            if a is not None and not isinstance(a, t):
                raise pyoasis.PyOasisException("Argument " + str(i)
                                               + " must be of type "
                                               + str(t) + ".")
            try:
                ty_list = type(a[0])
            except IndexError:
                raise pyoasis.PyOasisException("The function requires a list but got "+str(a))
            for element in a:
                if (type(element) != int and type(element) != str) or \
                    type(element) != ty_list:
                    raise pyoasis.PyOasisException(
                        "The elements of the list in argument "
                        + str(i) + " must be all integers or strings.")
        else:
            if a is not None and not isinstance(a, t):
                raise pyoasis.PyOasisException("Argument " + str(i)
                                               + " must be of type "
                                               + str(t) + ".")

        i = i + 1
