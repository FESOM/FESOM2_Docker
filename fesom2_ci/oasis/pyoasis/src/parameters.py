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


from enum import Enum


class OasisParameters(Enum):
    """
    Enumeration of parameters used by OASIS (values: OASIS_OUT, \
    OASIS_IN)
    """
    OASIS_OK          = 0
    OASIS_ERROR       = -10
    OASIS_NOTDEF      = -2
    OASIS_VAR_UNCPL   = -1
    OASIS_OUT         = 20
    OASIS_IN          = 21
    OASIS_INOUT       = 2
    OASIS_RECVD       = 3
    OASIS_SENT        = 4
    OASIS_LOCTRANS    = 5
    OASIS_TOREST      = 6
    OASIS_OUTPUT      = 7
    OASIS_SENTOUT     = 8
    OASIS_TORESTOUT   = 9
    OASIS_FROMREST    = 10
    OASIS_INPUT       = 11
    OASIS_RECVOUT     = 12
    OASIS_FROMRESTOUT = 13
    OASIS_WAITGROUP   = 14
    OK          = OASIS_OK
    NOTDEF      = OASIS_NOTDEF
    VAR_UNCPL   = OASIS_VAR_UNCPL
    OUT         = OASIS_OUT
    IN          = OASIS_IN
    INOUT       = OASIS_INOUT
    RECVD       = OASIS_RECVD
    SENT        = OASIS_SENT
    LOCTRANS    = OASIS_LOCTRANS
    TOREST      = OASIS_TOREST
    OUTPUT      = OASIS_OUTPUT
    SENTOUT     = OASIS_SENTOUT
    TORESTOUT   = OASIS_TORESTOUT
    FROMREST    = OASIS_FROMREST
    INPUT       = OASIS_INPUT
    RECVOUT     = OASIS_RECVOUT
    FROMRESTOUT = OASIS_FROMRESTOUT
    WAITGROUP   = OASIS_WAITGROUP
