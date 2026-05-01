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


subroutine oasis_def_partition_iso(id_part, kparal_size, kparal, kinfo, ig_size, name) bind(C)
  use iso_c_binding, only: c_int, c_ptr
  use cbindings
  use mod_oasis
  implicit none
  integer (c_int), intent(out) :: id_part
  integer (c_int), intent(in) :: kparal_size
  integer (c_int), intent(in), dimension(kparal_size) :: kparal
  integer (c_int), intent(in) :: ig_size
  type    (c_ptr), intent(in) :: name
  integer (c_int), intent(out) :: kinfo

  integer :: id_part_f
  integer :: kinfo_f
  character(len=:), allocatable :: name_f

  call foasis_string_to_fortran(name, name_f)

  if (ig_size <= 0) then
     if ( trim(name_f) == "" ) then
        call oasis_def_partition(id_part_f, kparal, kinfo_f)
     else
        call oasis_def_partition(id_part_f, kparal, kinfo_f, &
           & name=trim(name_f))
     end if
  else
     if ( trim(name_f) == "" ) then
        call oasis_def_partition(id_part_f, kparal, kinfo_f, &
           & ig_size=ig_size)
     else
        call oasis_def_partition(id_part_f, kparal, kinfo_f, &
           & ig_size=ig_size, name=trim(name_f))
     end if
  end if

  id_part=id_part_f
  kinfo=kinfo_f
end subroutine oasis_def_partition_iso
