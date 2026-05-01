! pyOASIS - A Python wrapper for OASIS
! Authors: Philippe Gambron, Rupert Ford
! Copyright (C) 2019 UKRI - STFC

! This program is free software: you can redistribute it and/or modify
! it under the terms of the GNU Lesser General Public License as
! published by the Free Software Foundation, either version 3 of the
! License, or any later version.

! This program is distributed in the hope that it will be useful,
! but WITHOUT ANY WARRANTY; without even the implied warranty of
! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
! GNU Lesser General Public License for more details.

! A copy of the GNU Lesser General Public License, version 3, is supplied
! with this program, in the file lgpl-3.0.txt. It is also available at
! <https://www.gnu.org/licenses/lgpl-3.0.html>.


subroutine oasis_abort_iso(id_compid, cd_routine, cd_message, file, line, rcode) bind(C)
  use iso_c_binding, only: c_int, c_ptr
  use cbindings
  use mod_oasis
  implicit none
  integer(kind=c_int), intent(in) :: id_compid
  type(c_ptr), intent(in) :: cd_routine
  type(c_ptr), intent(in) :: cd_message
  type(c_ptr), intent(in) :: file
  integer(kind=c_int), intent(in) :: line
  integer(kind=c_int), intent(in) :: rcode

  integer :: id_compid_f
  character(len=:), allocatable :: cd_routine_f, cd_message_f, file_f
  integer :: line_f, rcode_f

  id_compid_f=id_compid
  call foasis_string_to_fortran(cd_routine, cd_routine_f)
  call foasis_string_to_fortran(cd_message, cd_message_f)
  call foasis_string_to_fortran(file, file_f)
  line_f=line
  rcode_f=rcode

  call oasis_abort(id_compid_f, cd_routine_f, cd_message_f, file_f, line_f, rcode_f)
end subroutine oasis_abort_iso
