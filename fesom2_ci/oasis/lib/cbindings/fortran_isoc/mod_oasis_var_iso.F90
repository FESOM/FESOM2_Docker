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


subroutine oasis_def_var_iso(id_nports, cdport, id_part, &
     bundle_size, kinout, ktype, kinfo) bind(C)
  use iso_c_binding, only: c_int, c_ptr, c_bool
  use cbindings
  use mod_oasis
  implicit none
  include "mpif.h"
  integer (c_int), intent(out) :: id_nports
  type(c_ptr), intent(in) :: cdport
  integer (c_int), intent(in) :: id_part
  integer (c_int), intent(in) :: bundle_size
  integer (c_int), intent(in) :: kinout
  integer (c_int), intent(in) :: ktype
  integer (c_int), intent(out) :: kinfo

  integer :: id_nports_f
  character(len=:), allocatable :: cdport_f
  integer :: id_part_f
  integer :: id_var_nodims_f(2)
  integer kinout_f
  integer :: ktype_f
  integer :: kinfo_f

  integer :: i

  call foasis_string_to_fortran(cdport, cdport_f)
  id_part_f=id_part
  id_var_nodims_f(1)=0
  id_var_nodims_f(2)=bundle_size
  kinout_f=kinout
  ktype_f=ktype

  call oasis_def_var(id_nports_f, cdport_f, id_part_f, &
  id_var_nodims_f, kinout_f, ktype_f, kinfo_f)

  id_nports=id_nports_f
  kinfo=kinfo_f
end subroutine oasis_def_var_iso
