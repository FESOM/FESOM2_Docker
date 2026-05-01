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


from pyoasis.exception import *
from pyoasis.parameters import *
from pyoasis.debug import *
from pyoasis.asarray import *
from pyoasis.checktypes import *
from pyoasis.abort import *
from pyoasis.component import *
from pyoasis.partition import *
from pyoasis.var import *
from pyoasis.grid import *
import sys

globals()["OASIS"] = pyoasis.parameters.OasisParameters


# Global error handler
def global_except_hook(exctype, value,
                       traceback):
    """
    Shuts down a whole MPI application if
    one of the processes fails
    """
    import sys
    try:
        import mpi4py.MPI
        sys.stderr.write("\n***********************\
******************************\n" +
         "Uncaught exception was detected on rank {}. \n".format(
                         mpi4py.MPI.COMM_WORLD.Get_rank()))
        from traceback import print_exception
        print_exception(exctype, value, traceback)
        sys.stderr.flush()
    finally:
        try:
            import mpi4py.MPI
            mpi4py.MPI.COMM_WORLD.Abort(1)
        except Exception as e:
            sys.stderr.write("*****************************************************\n")
            sys.stderr.write("Sorry, we failed to stop MPI, this process will hang.\n")
            sys.stderr.write("*****************************************************\n")
            sys.stderr.flush()
            raise e


sys.excepthook = global_except_hook
