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


subroutine oasis_get_localcomm_iso(localcomm, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none
  integer (c_int), intent(out) :: localcomm
  integer (c_int), intent(inout) :: kinfo

  integer :: localcomm_f, kinfo_f

  kinfo_f=kinfo

  call oasis_get_localcomm(localcomm_f, kinfo_f)

  localcomm=localcomm_f
  kinfo=kinfo_f

end subroutine oasis_get_localcomm_iso


subroutine oasis_create_couplcomm_iso(icpl, allcomm, cplcomm, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none
  integer (c_int), intent(in) :: icpl, allcomm
  integer (c_int), intent(out) :: cplcomm
  integer (c_int), intent(inout) :: kinfo

  integer :: icpl_f, allcomm_f, cplcomm_f, kinfo_f
  icpl_f=icpl
  allcomm_f=allcomm
  kinfo_f=kinfo

  call oasis_create_couplcomm(icpl_f, allcomm_f, cplcomm_f, kinfo_f)

  cplcomm=cplcomm_f
  kinfo=kinfo_f

end subroutine oasis_create_couplcomm_iso


subroutine oasis_set_couplcomm_iso(localcomm, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none
  integer (c_int), intent(in) :: localcomm
  integer (c_int), intent(inout) :: kinfo

  integer :: localcomm_f
  integer :: kinfo_f

  localcomm_f=localcomm
  kinfo_f=kinfo

  call oasis_set_couplcomm(localcomm_f, kinfo_f)

  kinfo=kinfo_f

end subroutine oasis_set_couplcomm_iso


subroutine oasis_get_intercomm_iso(new_comm, cdnam, kinfo) bind(C)
  use iso_c_binding, only: c_int, c_ptr
  use cbindings, only: foasis_string_to_fortran
  use mod_oasis
  implicit none
  integer (c_int), intent(out) :: new_comm
  type(c_ptr), intent(in) :: cdnam
  integer (c_int), intent(inout) :: kinfo

  integer :: new_comm_f
  character(len=:), allocatable :: cdnam_f
  integer :: kinfo_f

  kinfo_f=kinfo
  call foasis_string_to_fortran(cdnam, cdnam_f)

  call oasis_get_intercomm(new_comm_f, cdnam_f, kinfo_f)

  new_comm=new_comm_f
  kinfo=kinfo_f

end subroutine oasis_get_intercomm_iso


subroutine oasis_get_intracomm_iso(new_comm, cdnam, kinfo) bind(C)
  use iso_c_binding, only: c_int, c_ptr
  use cbindings, only: foasis_string_to_fortran
  use mod_oasis
  implicit none
  integer (c_int), intent(out) :: new_comm
  type(c_ptr), intent(in) :: cdnam
  integer (c_int), intent(inout) :: kinfo

  integer :: new_comm_f
  character(len=:), allocatable :: cdnam_f
  integer :: kinfo_f

  kinfo_f=kinfo
  call foasis_string_to_fortran(cdnam, cdnam_f)

  call oasis_get_intracomm(new_comm_f, cdnam_f, kinfo_f)

  new_comm=new_comm_f
  kinfo=kinfo_f

end subroutine oasis_get_intracomm_iso


subroutine oasis_get_multi_intracomm_iso(new_comm, cdnam_size, cdnam, root_ranks, kinfo) bind(C)
  use iso_c_binding, only: c_int, c_ptr
  use cbindings, only: foasis_stringarray_to_fortran
  use mod_oasis
  implicit none
  integer (c_int), intent(out) :: new_comm
  integer (c_int), intent(in)  :: cdnam_size
  type(c_ptr), dimension(cdnam_size), intent(in) :: cdnam
  integer(c_int), dimension(cdnam_size), intent(out) :: root_ranks
  integer (c_int), intent(inout) :: kinfo

  integer :: new_comm_f
  integer :: cdnam_size_f
  character(len=:), allocatable, dimension(:)  :: cdnam_f
  integer :: kinfo_f

  integer :: ib_str

  kinfo_f=kinfo
  cdnam_size_f=cdnam_size
  call foasis_stringarray_to_fortran(cdnam_size_f, cdnam, cdnam_f)

  call oasis_get_multi_intracomm(new_comm_f, cdnam_f, root_ranks, kinfo_f)

  new_comm=new_comm_f
  kinfo=kinfo_f

  deallocate(cdnam_f)

end subroutine oasis_get_multi_intracomm_iso


subroutine oasis_set_debug_iso(debug, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none

  integer(c_int), intent(in) :: debug
  integer(c_int), intent(inout) :: kinfo

  integer :: debug_f
  integer :: kinfo_f

  debug_f=debug;

  call oasis_set_debug(debug_f, kinfo_f)

  kinfo=kinfo_f
end subroutine oasis_set_debug_iso


subroutine oasis_get_debug_iso(debug, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none

  integer(c_int), intent(out) :: debug
  integer(c_int), intent(inout) :: kinfo

  integer :: debug_f
  integer :: kinfo_f

  call oasis_get_debug(debug_f, kinfo_f)

  debug=debug_f;
  kinfo=kinfo_f
end subroutine oasis_get_debug_iso


subroutine oasis_put_inquire_iso(varid, msec, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none
  integer(c_int), intent(in) :: varid
  integer(c_int), intent(in) :: msec
  integer(c_int), intent(out) :: kinfo

  integer :: varid_f
  integer :: msec_f
  integer :: kinfo_f

  varid_f=varid
  msec_f=msec

  call oasis_put_inquire(varid_f, msec_f, kinfo_f)

  kinfo=kinfo_f
end subroutine oasis_put_inquire_iso


subroutine oasis_get_ncpl_iso(varid, ncpl, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none
  integer(c_int), intent(in) :: varid
  integer(c_int), intent(out) :: ncpl
  integer(c_int), intent(out) :: kinfo

  integer :: varid_f
  integer :: ncpl_f
  integer :: kinfo_f

  varid_f=varid

  call oasis_get_ncpl(varid_f, ncpl_f, kinfo_f)

  ncpl=ncpl_f
  kinfo=kinfo_f
end subroutine oasis_get_ncpl_iso


subroutine oasis_get_freqs_iso(varid, mop, ncpl, cpl_freqs, kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none
  integer(c_int), intent(in) :: varid
  integer(c_int), intent(in) :: mop
  integer(c_int), intent(in) :: ncpl
  integer(c_int), intent(out) :: cpl_freqs(ncpl)
  integer(c_int), intent(out) :: kinfo

  integer :: varid_f
  integer :: mop_f
  integer :: ncpl_f
  integer :: kinfo_f

  varid_f=varid
  mop_f=mop
  ncpl_f=ncpl

  call oasis_get_freqs(varid_f, mop_f, ncpl_f, cpl_freqs, kinfo_f)

  kinfo=kinfo_f
end subroutine oasis_get_freqs_iso
