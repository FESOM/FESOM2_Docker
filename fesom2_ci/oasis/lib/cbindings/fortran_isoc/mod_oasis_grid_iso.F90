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


subroutine oasis_start_grids_writing_iso(kinfo) bind(C)
  use iso_c_binding, only: c_int
  use mod_oasis
  implicit none

  integer (c_int), intent(out) :: kinfo

  integer :: kinfo_f

  call oasis_start_grids_writing(kinfo_f)

  kinfo = kinfo_f
  if (kinfo == 1) kinfo = OASIS_Ok

end subroutine oasis_start_grids_writing_iso


subroutine oasis_write_grid_iso(cgrid, nx, ny, nx_loc, ny_loc, lon, lat, partid) bind(C)
  use iso_c_binding, only: c_int, c_double, c_ptr, c_bool
  use cbindings
  use mod_oasis
  implicit none

  type(c_ptr), intent(in) :: cgrid
  integer (c_int), intent (in) :: nx, ny
  integer (c_int), intent (in) :: nx_loc, ny_loc
  real (c_double), intent(in), target :: lon(nx_loc*ny_loc)
  real (c_double), intent(in), target :: lat(nx_loc*ny_loc)
  integer(c_int), intent (in) :: partid  ! -1 if absent

  character(len=:), allocatable :: cgrid_f
  integer ::nx_f, ny_f
  integer :: partid_f
  real (c_double), pointer :: lon2D(:,:)
  real (c_double), pointer :: lat2D(:,:)

  call foasis_string_to_fortran(cgrid, cgrid_f)
  nx_f=nx
  ny_f=ny
  partid_f=partid
  lon2D(1:nx_loc, 1:ny_loc) => lon(:)
  lat2D(1:nx_loc, 1:ny_loc) => lat(:)
  if(partid_f>=0) then
    call oasis_write_grid(cgrid_f, nx_f, ny_f, lon2D, lat2D, partid_f)
  else
    call oasis_write_grid(cgrid_f, nx_f, ny_f, lon2D, lat2D)
  end if
end subroutine oasis_write_grid_iso


subroutine oasis_write_corner_iso(cgrid, nx, ny, nc, nx_loc, ny_loc, clo, cla, partid) bind(C)
  use iso_c_binding, only: c_int, c_double, c_ptr, c_bool
  use cbindings
  use mod_oasis
  implicit none

  type(c_ptr), intent(in) :: cgrid
  integer (c_int), intent (in) :: nx, ny, nc
  integer (c_int), intent (in) :: nx_loc, ny_loc
  real (c_double), intent(in), target :: clo(nx_loc*ny_loc*nc)
  real (c_double), intent(in), target :: cla(nx_loc*ny_loc*nc)
  integer(c_int), intent (in) :: partid  ! -1 if absent

  character(len=:), allocatable :: cgrid_f
  integer ::nx_f, ny_f, nc_f
  integer :: partid_f
  real (c_double), pointer :: clo3D(:,:,:)
  real (c_double), pointer :: cla3D(:,:,:)

  call foasis_string_to_fortran(cgrid, cgrid_f)
  nx_f=nx
  ny_f=ny
  nc_f=nc
  partid_f=partid
  clo3D(1:nx_loc, 1:ny_loc, 1:nc) => clo(:)
  cla3D(1:nx_loc, 1:ny_loc, 1:nc) => cla(:)

  if(partid_f>=0) then
    call oasis_write_corner(cgrid_f, nx_f, ny_f, nc_f, clo3D, cla3D,  partid_f)
  else
    call oasis_write_corner(cgrid_f, nx_f, ny_f, nc_f, clo3D, cla3D)
  endif

end subroutine oasis_write_corner_iso


subroutine oasis_write_mask_iso(cgrid, nx, ny, nx_loc, ny_loc, mask, partid, companion) bind(C)
  use iso_c_binding, only: c_int, c_double, c_ptr, c_bool
  use cbindings
  use mod_oasis
  implicit none

  type(c_ptr), intent(in) :: cgrid
  integer (c_int), intent (in) :: nx, ny
  integer (c_int), intent (in) :: nx_loc, ny_loc
  integer (c_int), intent(in), target :: mask(nx_loc*ny_loc)
  integer(c_int), intent (in) :: partid  ! -1 if absent
  type(c_ptr), intent(in) :: companion

  character(len=:), allocatable :: cgrid_f
  integer :: nx_f, ny_f
  integer :: partid_f
  integer(c_int), pointer :: mask2D(:,:)
  character(len=:), allocatable :: companion_f
  logical :: has_companion

  call foasis_string_to_fortran(cgrid, cgrid_f)
  nx_f=nx
  ny_f=ny
  partid_f=partid
  mask2D(1:nx_loc, 1:ny_loc) => mask(:)
  call foasis_string_to_fortran(companion, companion_f)
  has_companion = trim(companion_f) /= "NULL-STRING"

  if(partid_f>=0) then
    if (has_companion) then
      call oasis_write_mask(cgrid_f, nx_f, ny_f, mask2D, partid_f, companion_f)
    else
      call oasis_write_mask(cgrid_f, nx_f, ny_f, mask2D, partid_f)
    end if
  else
    if (has_companion) then
      call oasis_write_mask(cgrid_f, nx_f, ny_f, mask2D, companion=companion_f)
    else
      call oasis_write_mask(cgrid_f, nx_f, ny_f, mask2D)
    end if
  end if
end subroutine oasis_write_mask_iso


subroutine oasis_write_frac_iso(cgrid, nx, ny, nx_loc, ny_loc, frac, partid, companion) bind(C)
  use iso_c_binding, only: c_int, c_double, c_ptr, c_bool
  use cbindings
  use mod_oasis
  implicit none

  type(c_ptr), intent(in) :: cgrid
  integer (c_int), intent (in) :: nx, ny
  integer (c_int), intent (in) :: nx_loc, ny_loc
  real (c_double), intent(in), target :: frac(nx_loc*ny_loc)
  integer(c_int), intent (in) :: partid  ! -1 if absent
  type(c_ptr), intent(in) :: companion

  character(len=:), allocatable :: cgrid_f
  integer :: nx_f, ny_f
  integer :: partid_f
  real (c_double), pointer :: frac2D(:,:)
  character(len=:), allocatable :: companion_f
  logical :: has_companion

  call foasis_string_to_fortran(cgrid, cgrid_f)
  nx_f=nx
  ny_f=ny
  partid_f=partid
  frac2D(1:nx_loc, 1:ny_loc) => frac(:)
  call foasis_string_to_fortran(companion, companion_f)
  has_companion = trim(companion_f) /= "NULL-STRING"

  if(partid_f>=0) then
    if (has_companion) then
      call oasis_write_frac(cgrid_f, nx_f, ny_f, frac2D, partid_f, companion_f)
    else
      call oasis_write_frac(cgrid_f, nx_f, ny_f, frac2D, partid_f)
    end if
  else
    if (has_companion) then
      call oasis_write_frac(cgrid_f, nx_f, ny_f, frac2D, companion=companion_f)
    else
      call oasis_write_frac(cgrid_f, nx_f, ny_f, frac2D)
    end if
  end if
end subroutine oasis_write_frac_iso


subroutine oasis_write_area_iso(cgrid, nx, ny, nx_loc, ny_loc, area, partid) bind(C)
  use iso_c_binding, only: c_int, c_double, c_ptr, c_bool
  use cbindings
  use mod_oasis
  implicit none

  type(c_ptr), intent(in) :: cgrid
  integer (c_int), intent (in) :: nx, ny
  integer (c_int), intent (in) :: nx_loc, ny_loc
  real (c_double), intent(in), target :: area(nx_loc*ny_loc)
  integer(c_int), intent (in) :: partid  ! -1 if absent

  character(len=:), allocatable :: cgrid_f
  integer :: nx_f, ny_f
  integer :: partid_f
  real (c_double), pointer :: area2D(:,:)

  call foasis_string_to_fortran(cgrid, cgrid_f)
  nx_f=nx
  ny_f=ny
  partid_f=partid
  area2D(1:nx_loc, 1:ny_loc) => area(:)

  if(partid_f>=0) then
    call oasis_write_area(cgrid_f, nx_f, ny_f, area2D, partid_f)
  else
    call oasis_write_area(cgrid_f, nx_f, ny_f, area2D)
  end if
end subroutine oasis_write_area_iso


subroutine oasis_write_angle_iso(cgrid, nx, ny, nx_loc, ny_loc, angle, partid) bind(C)
  use iso_c_binding, only: c_int, c_double, c_ptr, c_bool
  use cbindings
  use mod_oasis
  implicit none

  type(c_ptr), intent(in) :: cgrid
  integer (c_int), intent (in) :: nx, ny
  integer (c_int), intent (in) :: nx_loc, ny_loc
  real (c_double), intent(in), target :: angle(nx_loc*ny_loc)
  integer(c_int), intent (in) :: partid  ! -1 if absent

  character(len=:), allocatable :: cgrid_f
  integer :: nx_f, ny_f
  integer :: partid_f
  real (c_double), pointer :: angle2D(:,:)

  call foasis_string_to_fortran(cgrid, cgrid_f)
  nx_f=nx
  ny_f=ny
  partid_f=partid
  angle2D(1:nx_loc, 1:ny_loc) => angle(:)

  if(partid_f>=0) then
    call oasis_write_angle(cgrid_f, nx_f, ny_f, angle2D, partid_f)
  else
    call oasis_write_angle(cgrid_f, nx_f, ny_f, angle2D)
  end if
end subroutine oasis_write_angle_iso


subroutine oasis_terminate_grids_writing_iso() bind(C)
  use mod_oasis
  implicit none
  call oasis_terminate_grids_writing()
end subroutine oasis_terminate_grids_writing_iso
