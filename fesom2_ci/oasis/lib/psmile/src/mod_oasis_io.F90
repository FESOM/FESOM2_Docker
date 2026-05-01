
!> Provides reusable IO routines for OASIS

MODULE mod_oasis_io

   USE mod_oasis_kinds
   USE mod_oasis_data
   USE mod_oasis_parameters
   USE mod_oasis_mpi
   USE mod_oasis_sys
   USE mod_oasis_ioshr
   USE mct_mod
   USE netcdf

   implicit none

   private

   !--- interfaces ---
   public :: oasis_io_varexists
   public :: oasis_io_read_avfld
   public :: oasis_io_read_avfile
   public :: oasis_io_write_avfile
   public :: oasis_io_read_array
   public :: oasis_io_write_array
   public :: oasis_io_read_avfbf
   public :: oasis_io_write_avfbf
   public :: oasis_io_write_2dgridint_fromroot
   public :: oasis_io_write_2dgridfld_fromroot
   public :: oasis_io_write_3dgridfld_fromroot
   public :: oasis_io_write_fldattr
   public :: oasis_io_read_field_fromroot

   integer(kind=ip_i4_p) :: oasis_io_64bit_offset = nf90_64bit_offset
#ifdef CDF_64BIT_DATA
   integer(kind=ip_i4_p) :: oasis_io_64bit_data   = nf90_64bit_data
#else
   integer(kind=ip_i4_p) :: oasis_io_64bit_data   = nf90_64bit_offset  ! set to offset by default
#endif

!===========================================================================
CONTAINS
!===========================================================================

!===============================================================================

!> Checks whether the var fldname is in the file 

logical function oasis_io_varexists(filename,fldname)

   implicit none

   character(len=*), intent(in) :: filename   !< filename
   character(len=*), intent(in) :: fldname    !< fldname

   !--- local ---
   logical :: exists               ! file exist flag
   integer(ip_i4_p) :: ncid        ! netcf file id
   integer(ip_i4_p) :: varid       ! netcf variable id
   integer(ip_i4_p) :: status      ! error code
   character(len=*),parameter :: subname = '(oasis_io_varexists)'

!-------------------------------------------------------------------------------
   call oasis_debug_enter(subname)

   oasis_io_varexists = .false.
   inquire(file=trim(filename),exist=exists)
   if (exists) then
      status = nf90_open(filename,NF90_NOWRITE,ncid)
      call check_status(status,subname,__FILE__,__LINE__)
      status = nf90_inq_varid(ncid,trim(fldname),varid)
      if (status == NF90_NOERR) then
         oasis_io_varexists = .true.
      endif
      status = nf90_close(ncid)
      call check_status(status,subname,__FILE__,__LINE__)
   endif

   call oasis_debug_exit(subname)

end function oasis_io_varexists

!===============================================================================

!> Reads single field from a file into an attribute Vector

subroutine oasis_io_read_avfld(filename,av,gsmap,mpicom,avfld,filefld,fldtype)

   implicit none

   character(len=*), intent(in) :: filename   !< file name
   type(mct_aVect) , intent(inout) :: av      !< avect
   type(mct_gsmap) , intent(in) :: gsmap      !< gsmap decomp
   integer(ip_i4_p), intent(in) :: mpicom     !< mpi comm
   character(len=*), intent(in) :: avfld      !< av field name
   character(len=*), intent(in) :: filefld    !< file field name
   character(len=*), intent(in),optional :: fldtype       !< kind

   !--- local ---
   integer(ip_i4_p)    :: n,n1,i,j,fk,fk1    ! index
   integer(ip_i4_p)    :: nx          ! 2d global size nx
   integer(ip_i4_p)    :: ny          ! 2d global size ny
   type(mct_aVect)     :: av_g        ! avect global data
   integer(ip_i4_p)    :: master_task,iam,ierr     ! mpi info
   integer(ip_i4_p)    :: ncid,dimid,dimid2(2),varid ! netcdf info
   integer(ip_i4_p)    :: dlen        ! dimension length
   integer(ip_i4_p)    :: status      ! error code
   logical             :: exists      ! file existance
   real(ip_double_p),allocatable :: array2(:,:)
   integer(ip_i4_p) ,allocatable :: array2i(:,:)
   integer(ip_i4_p)    :: ifldtype     ! field type int (1) or real (2)

   character(len=*),parameter :: subname = '(oasis_io_read_avfld)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   if (mpicom == MPI_COMM_NULL) return

   ! empty filename, just return

   call oasis_debug_enter(subname)
   if (len_trim(filename) < 1) then
      call oasis_debug_exit(subname)
      return
   endif

   master_task = 0
   call MPI_COMM_RANK(mpicom,iam,ierr)

   ifldtype = 2   ! real default
   if (present(fldtype)) then
      ifldtype = 0
      if (trim(fldtype) == 'int')  ifldtype = 1
      if (trim(fldtype) == 'real') ifldtype = 2
      if (ifldtype == 0) then
          write(nulprt,*) subname,estr,'in fldtype argument'
          call oasis_abort(file=__FILE__,line=__LINE__)
      endif
   endif

   call mct_aVect_gather(av,av_g,gsmap,master_task,mpicom)

   if (iam == master_task) then

      inquire(file=trim(filename),exist=exists)
      if (exists) then
         status = nf90_open(trim(filename),NF90_NOWRITE,ncid)
         call check_status(status,subname,__FILE__,__LINE__)
      else
         write(nulprt,*) subname,estr,'file missing ',trim(filename)
         call oasis_abort(file=__FILE__,line=__LINE__)
      endif

      status = nf90_inq_varid(ncid,trim(filefld),varid)
      call check_status(status,subname,__FILE__,__LINE__)
      status = nf90_inquire_variable(ncid,varid,ndims=dlen,dimids=dimid2)
      call check_status(status,subname,__FILE__,__LINE__)
      if (dlen > 2) then
         write(nulprt,*) subname,estr,'variable ndims gt 2 ',trim(filefld),dlen
         call oasis_abort(file=__FILE__,line=__LINE__)
      endif
      status = nf90_inquire_dimension(ncid,dimid2(1),len=nx)
      call check_status(status,subname,__FILE__,__LINE__)
      ny = 1
      if (dlen == 2) then
         status = nf90_inquire_dimension(ncid,dimid2(2),len=ny)
         call check_status(status,subname,__FILE__,__LINE__)
      endif

      if (size(av_g%rAttr,dim=2) /= nx*ny) then
         write(nulprt,*) subname,estr,'av gsize nx ny mismatch in file :',&
                                       trim(filename),SIZE(av_g%rAttr,dim=2),nx,ny
         call oasis_abort(file=__FILE__,line=__LINE__)
      endif

      if (ifldtype == 1) then
         allocate(array2i(nx,ny))
         status = nf90_get_var(ncid,varid,array2i)
         call check_status(status,subname,__FILE__,__LINE__)

         n = mct_avect_indexIA(av_g,trim(avfld))
         n1 = 0
         do j = 1,ny
         do i = 1,nx
            n1 = n1 + 1
            av_g%iAttr(n,n1) = array2i(i,j)
         enddo
         enddo
         deallocate(array2i)
      else
         allocate(array2(nx,ny))
         status = nf90_get_var(ncid,varid,array2)
         call check_status(status,subname,__FILE__,__LINE__)

         n = mct_avect_indexRA(av_g,trim(avfld))
         n1 = 0
         do j = 1,ny
         do i = 1,nx
            n1 = n1 + 1
            av_g%rAttr(n,n1) = array2(i,j)
         enddo
         enddo
         deallocate(array2)
      endif

      status = nf90_close(ncid)
      call check_status(status,subname,__FILE__,__LINE__)

   endif

   call mct_aVect_scatter(av_g,av,gsmap,master_task,mpicom)
   if (iam == master_task) then
      call mct_aVect_clean(av_g)
   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_read_avfld

!===============================================================================

!> Write an attribute keyword value pair to a field

subroutine oasis_io_write_fldattr(filename,fldname,keyword,value)

   ! ---------------------------------------
   ! Designed to work with oasis3 write_grid .
   ! ---------------------------------------

   implicit none

   character(len=*), intent(in) :: filename   !< file name
   character(len=*), intent(in) :: fldname    !< field name
   character(len=*), intent(in) :: keyword    !< attribute name
   character(len=*), intent(in) :: value      !< attribute value

   !--- local ---
   integer(ip_i4_p)    :: ncid,dimid,dimid2(2),varid  ! cdf info
   integer(ip_i4_p)    :: status      ! error code
   integer(ip_i4_p)    :: ind         ! string index
   logical             :: exists      ! file existance
   character(len=ic_med) :: gridname  ! grid name derived from fldname

   character(len=*),parameter :: subname = '(oasis_io_write_fldattr)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   call oasis_debug_enter(subname)

!   expects to run only on 1 pe.
!   if (iam == master_task) then

    if (OASIS_debug >= 5) then
       write(nulprt,*) subname,' write ',trim(filename),' ',trim(fldname)
       write(nulprt,*) subname,' write ',trim(keyword),' ',trim(value)
    endif

    ! open file, must already exist
    inquire(file=trim(filename),exist=exists)
    if (exists) then
       status = nf90_open(filename,NF90_WRITE,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_redef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    else
       write(nulprt,*) subname,estr,'file does not exist'
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif

    ! get varid, must already exist
    status = nf90_inq_varid(ncid,trim(fldname),varid)
    if (status == nf90_noerr) then
       status = nf90_put_att(ncid,varid,trim(keyword),trim(value))
       call check_status(status,subname,__FILE__,__LINE__)
    else
       write(nulprt,*) subname,estr,'variable does not exist ',trim(fldname)
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif

    status = nf90_close(ncid)
    call check_status(status,subname,__FILE__,__LINE__)

!   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_write_fldattr

!===============================================================================

!> Writes all fields from an attribute vector to a file

subroutine oasis_io_write_avfile(rstfile,av,gsmap,mpicom,nx,ny,nampre)

   implicit none

   character(len=*), intent(in) :: rstfile    !< filename
   type(mct_aVect) , intent(in) :: av         !< avect
   type(mct_gsmap) , intent(in) :: gsmap      !< gsmap decomp
   integer(ip_i4_p), intent(in) :: mpicom     !< mpi comm 
   integer(ip_i4_p), intent(in) :: nx         !< 2d global nx size
   integer(ip_i4_p), intent(in) :: ny         !< 2d global ny size
   character(len=*), intent(in),optional :: nampre  !< field name prepend string on file

   !--- local ---
   integer(ip_i4_p)    :: n,n1,i,j,fk,fk1    ! index
   integer(ip_i4_p)    :: nxf,nyf     ! field size on file
   type(mct_aVect)     :: av_g        ! avect global data
   type(mct_string)    :: mstring     ! mct char type
   character(ic_med)   :: itemc       ! string converted to char
   character(ic_med)   :: lnampre     ! local nampre
   character(ic_med)   :: lstring     ! local filename
   integer(ip_i4_p)    :: master_task,iam,ierr     ! mpi info
   integer(ip_i4_p)    :: ncid,dimid,dimid2(2),varid ! netcdf info
   integer(ip_i4_p)    :: dlen        ! dimension length
   integer(ip_i4_p)    :: iflag       ! netcdf control
   integer(ip_i4_p)    :: status      ! error code
   logical             :: exists      ! file existance
   real(ip_double_p),allocatable :: array2(:,:)

   character(len=*),parameter :: subname = '(oasis_io_write_avfile)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   if (mpicom == MPI_COMM_NULL) return

   call oasis_debug_enter(subname)

   ! empty filename, just return

   if (len_trim(rstfile) < 1) then
      call oasis_debug_exit(subname)
      return
   endif

   lnampre = ""
   if (present(nampre)) then
      lnampre = trim(nampre)
   endif

   master_task = 0
   call MPI_COMM_RANK(mpicom,iam,ierr)

   call mct_aVect_gather(av,av_g,gsmap,master_task,mpicom)

   if (iam == master_task) then
      if (size(av_g%rAttr,dim=2) /= nx*ny) then
         write(nulprt,*) subname,estr,'av gsize nx ny mismatch in file :',&
                         trim(lstring),SIZE(av_g%rAttr,dim=2),nx,ny
         call oasis_abort(file=__FILE__,line=__LINE__)
      endif

      inquire(file=trim(rstfile),exist=exists)
      if (exists) then
         status = nf90_open(trim(rstfile),NF90_WRITE,ncid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_redef(ncid)
         call check_status(status,subname,__FILE__,__LINE__)
      else
         iflag = NF90_CLOBBER
         if (cdf_filetype == 'cdf2') iflag = ior(iflag,oasis_io_64bit_offset)
         if (cdf_filetype == 'cdf5') iflag = ior(iflag,oasis_io_64bit_data)
         status = nf90_create(trim(rstfile),iflag,ncid)
         call check_status(status,subname,__FILE__,__LINE__)
      endif

      do n = 1,mct_aVect_nRAttr(av_g)
         call mct_aVect_getRList(mstring,n,av_g)
         itemc = mct_string_toChar(mstring)
         itemc = trim(lnampre)//trim(itemc)
         call mct_string_clean(mstring)

         status = nf90_inq_dimid(ncid,trim(itemc)//'_nx',dimid2(1))
         if (status /= NF90_NOERR) then
            status = nf90_def_dim(ncid,trim(itemc)//'_nx',nx,dimid2(1))
            call check_status(status,subname,__FILE__,__LINE__)
         endif

         status = nf90_inq_dimid(ncid,trim(itemc)//'_ny',dimid2(2))
         if (status /= NF90_NOERR) then
            status = nf90_def_dim(ncid,trim(itemc)//'_ny',ny,dimid2(2))
            call check_status(status,subname,__FILE__,__LINE__)
         endif

         status = nf90_inquire_dimension(ncid,dimid2(1),len=dlen)
         call check_status(status,subname,__FILE__,__LINE__)
         if (dlen /= nx) then
            write(nulprt,*) subname,wstr,'dlen ne nx ',dlen,nx
            call oasis_flush(nulprt)
!            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         status = nf90_inquire_dimension(ncid,dimid2(2),len=dlen)
         call check_status(status,subname,__FILE__,__LINE__)
         if (dlen /= ny) then
            write(nulprt,*) subname,wstr,'dlen ne ny ',dlen,ny
            call oasis_flush(nulprt)
!            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         status = nf90_inq_varid(ncid,trim(itemc),varid)
         if (status /= NF90_NOERR) then
            status = nf90_def_var(ncid,trim(itemc),NF90_DOUBLE,dimid2,varid)
            call check_status(status,subname,__FILE__,__LINE__)
         endif

      enddo

      status = nf90_enddef(ncid)
      call check_status(status,subname,__FILE__,__LINE__)

      nxf = 0
      nyf = 0
      do n = 1,mct_aVect_nRAttr(av_g)
         call mct_aVect_getRList(mstring,n,av_g)
         itemc = mct_string_toChar(mstring)
         itemc = trim(lnampre)//trim(itemc)
         call mct_string_clean(mstring)
         status = nf90_inq_varid(ncid,trim(itemc),varid)
         call check_status(status,subname,__FILE__,__LINE__)
         if (n == 1) then
            status = nf90_inquire_variable(ncid,varid,ndims=dlen,dimids=dimid2)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_inquire_dimension(ncid,dimid2(1),len=nxf)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_inquire_dimension(ncid,dimid2(2),len=nyf)
            call check_status(status,subname,__FILE__,__LINE__)
            if (dlen /= 2 .or. nx*ny /= nxf*nyf) then
               write(nulprt,*) subname,estr,'ndims and size does not match on file'
               call oasis_abort(file=__FILE__,line=__LINE__)
            endif
            allocate(array2(nxf,nyf))
         endif

         n1 = 0
         do j = 1,nyf
         do i = 1,nxf
            n1 = n1 + 1
            array2(i,j) = av_g%rAttr(n,n1)
         enddo
         enddo

         status = nf90_put_var(ncid,varid,array2)
         call check_status(status,subname,__FILE__,__LINE__)
      enddo
      deallocate(array2)
      call mct_aVect_clean(av_g)

      status = nf90_close(ncid)
      call check_status(status,subname,__FILE__,__LINE__)

   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_write_avfile

!===============================================================================

!> Reads all fields for an attribute vector from a file

subroutine oasis_io_read_avfile(rstfile,av,gsmap,mpicom,abort,nampre,didread)

   implicit none

   character(len=*), intent(in) :: rstfile    !< filename
   type(mct_aVect) , intent(inout) :: av      !< avect
   type(mct_gsmap) , intent(in) :: gsmap      !< gsmap decomp
   integer(ip_i4_p), intent(in) :: mpicom     !< mpi comm 
   logical         , intent(in) ,optional :: abort   !< abort on error flag, default is true
   character(len=*), intent(in) ,optional :: nampre  !< name prepend string for fields on file
   logical         , intent(out),optional :: didread !< flag indicating that read was successful

   !--- local ---
   integer(ip_i4_p)    :: n,n1,i,j,fk,fk1    ! index
   integer(ip_i4_p)    :: nx          ! 2d global size nx
   integer(ip_i4_p)    :: ny          ! 2d global size ny
   type(mct_aVect)     :: av_g        ! avect global data
   type(mct_string)    :: mstring     ! mct char type
   character(ic_med)   :: itemc       ! string converted to char
   character(ic_med)   :: lnampre     ! local nampre
   character(ic_med)   :: lstring     ! local filename
   integer(ip_i4_p)    :: master_task,iam,ierr     ! mpi info
   integer(ip_i4_p)    :: ncid,dimid,dimid2(2),varid ! netcdf info
   integer(ip_i4_p)    :: dlen        ! dimension length
   integer(ip_i4_p)    :: status      ! error code
   logical             :: exists      ! file existance
   logical             :: labort      ! local abort flag
   real(ip_double_p),allocatable :: array2(:,:)

   character(len=*),parameter :: subname = '(oasis_io_read_avfile)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   if (mpicom == MPI_COMM_NULL) return

   call oasis_debug_enter(subname)

   if (present(didread)) didread = .false.

   ! empty filename, just return

   if (len_trim(rstfile) < 1) then
      call oasis_debug_exit(subname)
      return
   endif

   labort = .true.
   if (present(abort)) then
      labort = abort
   endif

   lnampre = ""
   if (present(nampre)) then
      lnampre = trim(nampre)
   endif

   master_task = 0
   call MPI_COMM_RANK(mpicom,iam,ierr)

   call mct_aVect_gather(av,av_g,gsmap,master_task,mpicom)

   if (iam == master_task) then

      inquire(file=trim(rstfile),exist=exists)
      if (.not.exists) then
         if (labort) THEN
            write(nulprt,*) subname,estr,'file missing ',trim(rstfile)
            call oasis_abort(file=__FILE__,line=__LINE__)
         else
            write(nulprt,*) subname,wstr,'file missing ',trim(rstfile)
            call oasis_flush(nulprt)
         endif
      else
         status = nf90_open(trim(rstfile),NF90_NOWRITE,ncid)
         call check_status(status,subname,__FILE__,__LINE__)

         do n = 1,mct_aVect_nRAttr(av_g)
            call mct_aVect_getRList(mstring,n,av_g)
            itemc = mct_string_toChar(mstring)
            itemc = trim(lnampre)//trim(itemc)
            call mct_string_clean(mstring)

            status = nf90_inq_varid(ncid,trim(itemc),varid)
            if (status /= NF90_NOERR) then
               if (labort) THEN
                  write(nulprt,*) subname,estr,'var missing on file = ',trim(itemc),':',trim(nf90_strerror(status))
                  call oasis_abort(file=__FILE__,line=__LINE__)
!               else
!                  write(nulprt,*) subname,wstr,'var missing on file = ',trim(itemc),':',trim(nf90_strerror(status))
!                  call oasis_flush(nulprt)
               endif

            else
               status = nf90_inquire_variable(ncid,varid,ndims=dlen,dimids=dimid2)
               call check_status(status,subname,__FILE__,__LINE__)
               if (dlen > 2) then
                  write(nulprt,*) subname,estr,'variable ndims gt 2 on file ',trim(itemc),dlen
                  call oasis_abort(file=__FILE__,line=__LINE__)
               endif
               status = nf90_inquire_dimension(ncid,dimid2(1),len=nx)
               call check_status(status,subname,__FILE__,__LINE__)
               ny = 1
               if (dlen == 2) then
                  status = nf90_inquire_dimension(ncid,dimid2(2),len=ny)
                  call check_status(status,subname,__FILE__,__LINE__)
               endif

               if (size(av_g%rAttr,dim=2) /= nx*ny) then
                  write(nulprt,*) subname,estr,'av gsize nx ny mismatch in file = ',&
                                               trim(rstfile),SIZE(av_g%rAttr,dim=2),nx,ny
                  call oasis_abort(file=__FILE__,line=__LINE__)
               endif

               allocate(array2(nx,ny))

               status = nf90_get_var(ncid,varid,array2)
               call check_status(status,subname,__FILE__,__LINE__)

               n1 = 0
               do j = 1,ny
               do i = 1,nx
                  n1 = n1 + 1
                  av_g%rAttr(n,n1) = array2(i,j)
               enddo
               enddo
               if (present(didread)) didread = .true.

               deallocate(array2)
            endif  ! varid valid
         enddo

         status = nf90_close(ncid)
         call check_status(status,subname,__FILE__,__LINE__)

      endif  ! file exists
   endif

   call mct_aVect_scatter(av_g,av,gsmap,master_task,mpicom)
   if (iam == master_task) then
      call mct_aVect_clean(av_g)
   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_read_avfile

!===============================================================================

!> Reads an integer or real field from a file into an array

subroutine oasis_io_read_array(rstfile,mpicom,iarray,ivarname,rarray,rvarname,abort)

   implicit none

   character(len=*), intent(in) :: rstfile    !< filename
   integer(ip_i4_p), intent(in) :: mpicom     !<  mpi comm
   integer(ip_i4_p), intent(inout),optional :: iarray(:) !< integer data on root
   character(len=*), intent(in),optional :: ivarname     !< integer variable name on file
   real(ip_double_p),intent(inout),optional :: rarray(:) !< real data on root
   character(len=*), intent(in),optional :: rvarname     !< real variable name on file
   logical         , intent(in),optional :: abort        !< abort on error flag, default is true

   !--- local ---
   integer(ip_i4_p)    :: ncnt
   integer(ip_i4_p)    :: master_task,iam,ierr     ! mpi info
   integer(ip_i4_p)    :: ncid,dimid,dimid1(1),varid ! netcdf info
   integer(ip_i4_p)    :: dlen        ! dimension length
   integer(ip_i4_p)    :: status      ! error code
   logical             :: exists      ! file existance
   logical             :: labort      ! local abort flag

   character(len=*),parameter :: subname = '(oasis_io_read_array)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   if (mpicom == MPI_COMM_NULL) return

   call oasis_debug_enter(subname)

   ! empty filename, just return

   if (len_trim(rstfile) < 1) then
      call oasis_debug_exit(subname)
      return
   endif

   labort = .true.
   if (present(abort)) then
      labort = abort
   endif

   master_task = 0
   call MPI_COMM_RANK(mpicom,iam,ierr)

   if (iam == master_task) then

      inquire(file=trim(rstfile),exist=exists)
      if (.not.exists) then
         if (labort) THEN
            write(nulprt,*) subname,estr,'file missing ',trim(rstfile)
            call oasis_abort(file=__FILE__,line=__LINE__)
         else
            write(nulprt,*) subname,wstr,'file missing ',trim(rstfile)
            call oasis_flush(nulprt)
         endif
      else
         status = nf90_open(trim(rstfile),NF90_NOWRITE,ncid)
         call check_status(status,subname,__FILE__,__LINE__)

         if (present(iarray)) then
            if (.not. present(ivarname)) then
               write(nulprt,*) subname,estr,'iarray must have ivarname set'
               call oasis_abort(file=__FILE__,line=__LINE__)
            endif

            ncnt = size(iarray)

            status = nf90_inq_varid(ncid,trim(ivarname),varid)
            if (status /= NF90_NOERR) then
               if (labort) THEN
                  write(nulprt,*) subname,estr,'var missing on file = ',trim(ivarname),':',trim(nf90_strerror(status))
                  call oasis_abort(file=__FILE__,line=__LINE__)
!               else
!                  write(nulprt,*) subname,wstr,'var missing on file = ',trim(ivarname),':',trim(nf90_strerror(status))
!                  call oasis_flush(nulprt)
               endif
            else
               status = nf90_inquire_variable(ncid,varid,ndims=dlen,dimids=dimid1)
               call check_status(status,subname,__FILE__,__LINE__)
               if (dlen /= 1) then
                  write(nulprt,*) subname,estr,'variable ndims ne 1 ',trim(ivarname),dlen
                  call oasis_abort(file=__FILE__,line=__LINE__)
               endif
               status = nf90_inquire_dimension(ncid,dimid1(1),len=dlen)
               call check_status(status,subname,__FILE__,__LINE__)

               if (ncnt /= dlen) then
                  write(nulprt,*) subname,estr,'iarray ncnt dlen mismatch ',ncnt,dlen
                  call oasis_abort(file=__FILE__,line=__LINE__)
               endif

               status = nf90_get_var(ncid,varid,iarray)
               call check_status(status,subname,__FILE__,__LINE__)
            endif
         endif

         if (present(rarray)) then
            if (.not. present(rvarname)) then
               write(nulprt,*) subname,estr,'rarray must have rvarname set'
               call oasis_abort(file=__FILE__,line=__LINE__)
            endif

            ncnt = size(rarray)

            status = nf90_inq_varid(ncid,trim(rvarname),varid)
            if (status /= NF90_NOERR) then
               if (labort) THEN
                  write(nulprt,*) subname,estr,'var missing on file = ',trim(rvarname),':',trim(nf90_strerror(status))
                  call oasis_abort(file=__FILE__,line=__LINE__)
!               else
!                  write(nulprt,*) subname,wstr,'var missing on file = ',trim(rvarname),':',trim(nf90_strerror(status))
!                  call oasis_flush(nulprt)
               endif
            else
               status = nf90_inquire_variable(ncid,varid,ndims=dlen,dimids=dimid1)
               call check_status(status,subname,__FILE__,__LINE__)
               if (dlen /= 1) then
                  write(nulprt,*) subname,estr,'variable ndims ne 1 ',trim(rvarname),dlen
                  call oasis_abort(file=__FILE__,line=__LINE__)
               endif
               status = nf90_inquire_dimension(ncid,dimid1(1),len=dlen)
               call check_status(status,subname,__FILE__,__LINE__)

               if (ncnt /= dlen) then
                  write(nulprt,*) subname,estr,'rarray ncnt dlen mismatch ',ncnt,dlen
                  call oasis_abort(file=__FILE__,line=__LINE__)
               endif

               status = nf90_get_var(ncid,varid,rarray)
               call check_status(status,subname,__FILE__,__LINE__)
            endif
         endif

         status = nf90_close(ncid)
         call check_status(status,subname,__FILE__,__LINE__)

      endif
   endif

   if (present(iarray)) then
      call oasis_mpi_bcast(iarray,mpicom,trim(subname)//':iarray',master_task)
   endif

   if (present(rarray)) then
      call oasis_mpi_bcast(rarray,mpicom,trim(subname)//':rarray',master_task)
   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_read_array

!===============================================================================

!> Writes a real or integer array to a file

subroutine oasis_io_write_array(rstfile,mpicom,iarray,ivarname,rarray,rvarname)

   implicit none

   character(len=*), intent(in) :: rstfile    !< filename
   integer(ip_i4_p), intent(in) :: mpicom     !< mpi comm
   integer(ip_i4_p), intent(in),optional :: iarray(:)   !< integer data on root
   character(len=*), intent(in),optional :: ivarname    !< integer  variable name on file
   real(ip_double_p),intent(in),optional :: rarray(:)   !< real data on root
   character(len=*), intent(in),optional :: rvarname    !< real variable name on file

   !--- local ---
   integer(ip_i4_p)    :: ncnt
   integer(ip_i4_p)    :: master_task,iam,ierr     ! mpi info
   integer(ip_i4_p)    :: ncid,dimid,dimid1(1),varid ! netcdf info
   integer(ip_i4_p)    :: dlen        ! dimension length
   integer(ip_i4_p)    :: iflag       ! netcdf control
   integer(ip_i4_p)    :: status      ! error code
   logical             :: exists      ! file existance

   character(len=*),parameter :: subname = '(oasis_io_write_array)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   if (mpicom == MPI_COMM_NULL) return

   call oasis_debug_enter(subname)

   ! empty filename, just return

   if (len_trim(rstfile) < 1) then
      call oasis_debug_exit(subname)
      return
   endif

   master_task = 0
   call MPI_COMM_RANK(mpicom,iam,ierr)

   if (iam == master_task) then

      inquire(file=trim(rstfile),exist=exists)
      if (exists) then
         write(nulprt,*) 'Attempting to open NetCDF file:', trim(rstfile)

         status = nf90_open(trim(rstfile), NF90_WRITE, ncid)
         write(nulprt,*) 'nf90_open status:', status
         if (status /= nf90_noerr) then
            write(nulprt,*) 'nf90_open error msg:', nf90_strerror(status)
         endif
         call check_status(status, subname, __FILE__, __LINE__)

         write(nulprt,*) 'File opened. ncid =', ncid

         status = nf90_redef(ncid)
         write(nulprt,*) 'nf90_redef status:', status
         if (status /= nf90_noerr) then
            write(nulprt,*) 'nf90_redef error msg:', nf90_strerror(status)
         endif
         call check_status(status, subname, __FILE__, __LINE__)
      else
         iflag = NF90_CLOBBER
         if (cdf_filetype == 'cdf2') iflag = ior(iflag,oasis_io_64bit_offset)
         if (cdf_filetype == 'cdf5') iflag = ior(iflag,oasis_io_64bit_data)
         status = nf90_create(trim(rstfile),iflag,ncid)
         call check_status(status,subname,__FILE__,__LINE__)
      endif

      if (present(iarray)) then
         if (.not. present(ivarname)) then
            write(nulprt,*) subname,estr,'iarray must have ivarname set'
            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         ncnt = size(iarray)

         status = nf90_inq_dimid(ncid,trim(ivarname)//'_ncnt',dimid1(1))
         if (status /= NF90_NOERR) then
            status = nf90_def_dim(ncid,trim(ivarname)//'_ncnt',ncnt,dimid1(1))
            call check_status(status,subname,__FILE__,__LINE__)
         endif

         status = nf90_inquire_dimension(ncid,dimid1(1),len=dlen)
         call check_status(status,subname,__FILE__,__LINE__)
         if (dlen /= ncnt) then
            write(nulprt,*) subname,estr,'iarray dlen ne ncnt ',dlen,ncnt
            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         status = nf90_inq_varid(ncid,trim(ivarname),varid)
         if (status /= NF90_NOERR) then
            status = nf90_def_var(ncid,trim(ivarname),NF90_INT,dimid1,varid)
            call check_status(status,subname,__FILE__,__LINE__)
         endif
      endif

      if (present(rarray)) then
         if (.not. present(rvarname)) then
            write(nulprt,*) subname,estr,'rarray must have rvarname set'
            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         ncnt = size(rarray)

         status = nf90_inq_dimid(ncid,trim(rvarname)//'_ncnt',dimid1(1))
         if (status /= NF90_NOERR) then
            status = nf90_def_dim(ncid,trim(rvarname)//'_ncnt',ncnt,dimid1(1))
            call check_status(status,subname,__FILE__,__LINE__)
         endif

         status = nf90_inquire_dimension(ncid,dimid1(1),len=dlen)
         call check_status(status,subname,__FILE__,__LINE__)
         if (dlen /= ncnt) then
            write(nulprt,*) subname,estr,'rarray dlen ne ncnt ',dlen,ncnt
            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         status = nf90_inq_varid(ncid,trim(rvarname),varid)
         if (status /= NF90_NOERR) then
            status = nf90_def_var(ncid,trim(rvarname),NF90_DOUBLE,dimid1,varid)
            call check_status(status,subname,__FILE__,__LINE__)
         endif
      endif

      status = nf90_enddef(ncid)
      call check_status(status,subname,__FILE__,__LINE__)

      if (present(iarray)) then
         status = nf90_inq_varid(ncid,trim(ivarname),varid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_put_var(ncid,varid,iarray)
         call check_status(status,subname,__FILE__,__LINE__)
      endif

      if (present(rarray)) then
         status = nf90_inq_varid(ncid,trim(rvarname),varid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_put_var(ncid,varid,rarray)
         call check_status(status,subname,__FILE__,__LINE__)
      endif

      status = nf90_close(ncid)
      call check_status(status,subname,__FILE__,__LINE__)

   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_write_array

!===============================================================================

!> Write each field in an attribute vector to an individual files

subroutine oasis_io_write_avfbf(av,gsmap,mpicom,nx,ny,msec,f_string,filename)

   ! ---------------------------------------
   ! This works only for a single av to a file
   ! Optionally can specify time info, and filename info
   ! ---------------------------------------

   implicit none

   type(mct_aVect) , intent(in) :: av         !< avect
   type(mct_gsmap) , intent(in) :: gsmap      !< gsmap decomp
   integer(ip_i4_p), intent(in) :: mpicom     !< mpi comm
   integer(ip_i4_p), intent(in) :: nx         !< 2d global nx size
   integer(ip_i4_p), intent(in) :: ny         !< 2d global ny size
   integer(ip_i4_p), intent(in),optional :: msec      !< optional time info in seconds
   character(len=*), intent(in),optional :: f_string  !< optional f_string to append to filename
   character(len=*), intent(in),optional :: filename  !< optional output filename

   !--- local ---
   integer(ip_i4_p)    :: n,n1,i,j,fk,fk1    ! index
   type(mct_aVect)     :: av_g        ! avect global data
   type(mct_string)    :: mstring     ! mct char type
   character(ic_med)   :: itemc       ! f_string converted to char
   character(ic_med)   :: lfn         ! local filename
   character(ic_med)   :: lstring     ! local filename
   integer(ip_i4_p)    :: master_task,iam,ierr     ! mpi info
   integer(ip_i4_p)    :: ncid,dimid,dimid3(3),varid ! netcdf info
   integer(ip_i4_p)    :: start3(3),count3(3)        ! netcdf info
   integer(ip_i4_p)    :: start1(1),count1(1)        ! netcdf info
   integer(ip_i4_p)    :: lmsec(1)    ! local msec value
   integer(ip_i4_p)    :: dlen        ! dimension length
   integer(ip_i4_p)    :: iflag       ! netcdf control
   integer(ip_i4_p)    :: status      ! error code
   logical             :: exists      ! file existance
   logical             :: newfile     ! to create a new history file
   logical             :: whead,wdata ! for writing restart/history cdf files
   integer(ip_i4_p) ,allocatable :: time(:)
   real(ip_double_p),allocatable :: array3(:,:,:)
   real(ip_double_p)   :: tbnds(2)

   character(len=*),parameter :: subname = '(oasis_io_write_avfbf)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   if (mpicom == MPI_COMM_NULL) return

   call oasis_debug_enter(subname)

   lmsec = 0
   if (present(msec)) then
      lmsec = msec
   endif

   lstring = " "
   if (present(f_string)) then
      lstring = trim(f_string)
   endif

   master_task = 0
   call MPI_COMM_RANK(mpicom,iam,ierr)

#if (PIO_DEFINED)
! tcraig, not working as of Oct 2011
   call oasis_ioshr_wopen(lfn,clobber=.true.,cdf64=.true.)

   do fk = fk1,2
      if (fk == 1) then
         whead = .true.
         wdata = .false.
      elseif (fk == 2) then
         whead = .false.
         wdata = .true.
      else
         write(nulprt,*) subname,estr,'fk illegal'
         call oasis_abort(file=__FILE__,line=__LINE__)
      end if

      call oasis_ioshr_write(lfn,&
               time_units='seconds',time_cal='seconds',time_val=real(lmsec,ip_double_p),&
               nt=1,whead=whead,wdata=wdata)

      call oasis_ioshr_write(lfn, gsmap, av, 'pout', &
               whead=whead,wdata=wdata,nx=nx,ny=ny,nt=1, &
               use_float=.false.)
   
      if (fk == 1) call oasis_ioshr_enddef(lfn)
   enddo

   call oasis_ioshr_close(lfn)
#else

   call mct_aVect_gather(av,av_g,gsmap,master_task,mpicom)
   if (iam == master_task) then
      if (size(av_g%rAttr,dim=2) /= nx*ny) then
         write(nulprt,*) subname,estr,'av gsize nx ny mismatch in file :',&
                                      trim(filename),SIZE(av_g%rAttr,dim=2),nx,ny
         call oasis_abort(file=__FILE__,line=__LINE__)
      endif

      allocate(array3(nx,ny,1))
      do n = 1,mct_aVect_nRAttr(av_g)
         call mct_aVect_getRList(mstring,n,av_g)
         itemc = mct_string_toChar(mstring)
         call mct_string_clean(mstring)
         if (present(filename)) then
            lfn = trim(filename)
         else
            lfn = trim(itemc)//trim(lstring)//'.nc'
         endif
         n1 = 0
         do j = 1,ny
         do i = 1,nx
            n1 = n1 + 1
            array3(i,j,1) = av_g%rAttr(n,n1)
         enddo
         enddo

         start1 = 1
         count1 = 1
         start3 = 1
         count3(1) = nx
         count3(2) = ny
         count3(3) = 1

         newfile = .true.
         inquire(file=trim(lfn),exist=exists)
         if (exists) then
            newfile = .false.
            status = nf90_open(lfn,NF90_WRITE,ncid)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_inq_dimid(ncid,'time',dimid)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_inquire_dimension(ncid,dimid,len=dlen)
            call check_status(status,subname,__FILE__,__LINE__)
            allocate(time(dlen))
            status = nf90_inq_varid(ncid,'time',varid)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_get_var(ncid,varid,time)
            call check_status(status,subname,__FILE__,__LINE__)

            !--- check whether the current time is less than the current file time axis
            !--- if so, then assume this is an old file and clobber it and start new
            do i = 1,dlen
               if (time(i) >= lmsec(1)) newfile=.true.
            enddo
            deallocate(time)
            if (.not.newfile) then
               start1(1) = dlen + 1
               start3(3) = start1(1)
            endif
         endif

         if (newfile) then
            iflag = NF90_CLOBBER
            if (cdf_filetype == 'cdf2') iflag = ior(iflag,oasis_io_64bit_offset)
            if (cdf_filetype == 'cdf5') iflag = ior(iflag,oasis_io_64bit_data)
            status = nf90_create(lfn,iflag,ncid)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_def_dim(ncid,'nx',nx,dimid3(1))
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_def_dim(ncid,'ny',ny,dimid3(2))
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_def_dim(ncid,'time',NF90_UNLIMITED,dimid)
            call check_status(status,subname,__FILE__,__LINE__)
            dimid3(3) = dimid
            status = nf90_def_var(ncid,'time',NF90_INT,dimid,varid)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_def_var(ncid,trim(itemc),NF90_DOUBLE,dimid3,varid)
            call check_status(status,subname,__FILE__,__LINE__)
            status = nf90_enddef(ncid)
            call check_status(status,subname,__FILE__,__LINE__)
         endif

         status = nf90_inq_varid(ncid,'time',varid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_put_var(ncid,varid,lmsec,start1,count1)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_inq_varid(ncid,trim(itemc),varid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_put_var(ncid,varid,array3,start3,count3)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_close(ncid)
         call check_status(status,subname,__FILE__,__LINE__)
      enddo
      deallocate(array3)
      call mct_aVect_clean(av_g)
   endif


#endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_write_avfbf

!===============================================================================

!> Read each field in an attribute vector from individual files

subroutine oasis_io_read_avfbf(av,gsmap,mpicom,msec,f_string,filename)

   ! ---------------------------------------
   ! This works only for a single av from a file
   ! Optionally can specify time info, and filename info
   ! ---------------------------------------

   implicit none

   type(mct_aVect) , intent(inout) :: av     !< avect
   type(mct_gsmap) , intent(in) :: gsmap     !< gsmap decomp
   integer(ip_i4_p), intent(in) :: mpicom    !< mpi comm
   integer(ip_i4_p), intent(in),optional :: msec     !< optional time info in seconds
   character(len=*), intent(in),optional :: f_string !< optional f_string to append to filename
   character(len=*), intent(in),optional :: filename !< optional input filename

   !--- local ---
   integer(ip_i4_p)    :: n,n1,i,j,fk,fk1    ! index
   integer(ip_i4_p)    :: nx,ny       ! grid size from file
   type(mct_aVect)     :: av_g        ! avect global data
   type(mct_string)    :: mstring     ! mct char type
   character(ic_med)   :: itemc       ! f_string converted to char
   character(ic_med)   :: lfn         ! local filename
   character(ic_med)   :: lstring     ! local filename
   integer(ip_i4_p)    :: master_task,iam,ierr     ! mpi info
   integer(ip_i4_p)    :: ncid,dimid,dimid3(3),varid ! netcdf info
   integer(ip_i4_p)    :: start3(3),count3(3)        ! netcdf info
   integer(ip_i4_p)    :: lmsec(1)    ! local msec value
   integer(ip_i4_p)    :: dlen        ! dimension length
   integer(ip_i4_p)    :: status      ! error code
   logical             :: exists      ! file existance
   logical             :: whead,wdata ! for writing restart/history cdf files
   real(ip_double_p),allocatable :: array3(:,:,:)
   integer(ip_i4_p) ,allocatable :: time(:)
   real(ip_double_p)   :: tbnds(2)

   character(len=*),parameter :: subname = '(oasis_io_read_avfbf)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   if (mpicom == MPI_COMM_NULL) return

   call oasis_debug_enter(subname)

   lmsec = 0
   if (present(msec)) then
      lmsec = msec
   endif

   lstring = " "
   if (present(f_string)) then
      lstring = trim(f_string)
   endif

   master_task = 0
   call MPI_COMM_RANK(mpicom,iam,ierr)

   call mct_aVect_gather(av,av_g,gsmap,master_task,mpicom)
   if (iam == master_task) then
      do n = 1,mct_aVect_nRAttr(av_g)
         call mct_aVect_getRList(mstring,n,av_g)
         itemc = mct_string_toChar(mstring)
         call mct_string_clean(mstring)
         if (present(filename)) then
            lfn = trim(filename)
         else
            lfn = trim(itemc)//trim(lstring)//'.nc'
         endif

         inquire(file=trim(lfn),exist=exists)
         if (.not.exists) then
            write(nulprt,*) subname,estr,'file not found ',trim(lfn)
            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         status = nf90_open(lfn,NF90_NOWRITE,ncid)
         call check_status(status,subname,__FILE__,__LINE__)

         status = nf90_inq_dimid(ncid,'time',dimid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_inquire_dimension(ncid,dimid,len=dlen)
         call check_status(status,subname,__FILE__,__LINE__)
         allocate(time(dlen))
         status = nf90_inq_varid(ncid,'time',varid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_get_var(ncid,varid,time)
         call check_status(status,subname,__FILE__,__LINE__)
         n1 = 0
         do j = 1,dlen
            if (time(j) == lmsec(1)) n1 = j
         enddo
         deallocate(time)
         if (n1 < 1) then
            write(nulprt,*) subname,estr,'time not found on file ',trim(lfn),lmsec
            call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         status = nf90_inq_varid(ncid,trim(itemc),varid)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_inquire_variable(ncid,varid,dimids=dimid3)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_inquire_dimension(ncid,dimid3(1),len=nx)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_inquire_dimension(ncid,dimid3(2),len=ny)
         call check_status(status,subname,__FILE__,__LINE__)

         if (size(av_g%rAttr,dim=2) /= nx*ny) then
             write(nulprt,*) subname,estr,'av gsize nx ny mismatch in file :',&
                                           trim(filename),SIZE(av_g%rAttr,dim=2),nx,ny
             call oasis_abort(file=__FILE__,line=__LINE__)
         endif

         start3 = 1
         count3(1) = nx
         count3(2) = ny
         count3(3) = 1
         start3(3) = n1
         allocate(array3(nx,ny,1))

         status = nf90_get_var(ncid,varid,array3,start3,count3)
         call check_status(status,subname,__FILE__,__LINE__)
         status = nf90_close(ncid)
         call check_status(status,subname,__FILE__,__LINE__)

         n1 = 0
         do j = 1,ny
         do i = 1,nx
            n1 = n1 + 1
            av_g%rAttr(n,n1) = array3(i,j,1)
         enddo
         enddo

         deallocate(array3)

      enddo
   endif

   call mct_aVect_scatter(av_g,av,gsmap,master_task,mpicom)
   if (iam == master_task) then
      call mct_aVect_clean(av_g)
   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_read_avfbf

!===============================================================================

!> Read a field on the root task from a file into an array.

subroutine oasis_io_read_field_fromroot(filename,fldname,ifld2,fld2,fld3,nx,ny,nz)

   ! ---------------------------------------
   ! Supports 2d integer or real and 3d real arrays.
   ! ---------------------------------------

   implicit none

   character(len=*) , intent(in) :: filename   !< file name
   character(len=*) , intent(in) :: fldname    !< field name
   integer(ip_i4_p) , intent(inout),optional :: ifld2(:,:)  !< 2d integer array
   real(ip_realwp_p), intent(inout),optional :: fld2(:,:)   !< 2d real array
   real(ip_realwp_p), intent(inout),optional :: fld3(:,:,:) !< 3d real array
   integer(ip_i4_p) , intent(inout),optional :: nx          !< global nx size
   integer(ip_i4_p) , intent(inout),optional :: ny          !< global ny size
   integer(ip_i4_p) , intent(inout),optional :: nz          !< global nz size

   !--- local ---
   integer(ip_i4_p)    :: ncid,varid  ! cdf info
   integer(ip_i4_p)    :: n,ndims,xtype
   integer(ip_i4_p),allocatable :: dimid(:),nd(:)
   integer(ip_i4_p)    :: status      ! error code
   integer(ip_i4_p)    :: ind         ! string index
   logical             :: exists      ! file existance
   character(len=ic_med) :: gridname  ! grid name derived from fldname

   character(len=*),parameter :: subname = '(oasis_io_read_field_fromroot)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   call oasis_debug_enter(subname)

!   expects to run only on 1 pe.
!   if (iam == master_task) then

! EM Since parallel version, must be run only on 1 pe.
   if ( mpi_rank_local  == 0 ) then

     if (OASIS_debug >= 5) then
       write(nulprt,*) subname,' read ',trim(filename),' ',trim(fldname)
     endif

     inquire(file=trim(filename),exist=exists)
     if (exists) then
       status = nf90_open(filename,NF90_NOWRITE,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
     else
       write(nulprt,*) subname,estr,'in filename ',trim(filename)
       call oasis_abort(file=__FILE__,line=__LINE__)
     endif

     status = nf90_inq_varid(ncid,trim(fldname),varid)
     call check_status(status,subname,__FILE__,__LINE__)

     status = nf90_inquire_variable(ncid,varid,ndims=ndims,xtype=xtype)
     call check_status(status,subname,__FILE__,__LINE__)

     allocate(dimid(ndims),nd(ndims))

     status = nf90_inquire_variable(ncid,varid,dimids=dimid)
     call check_status(status,subname,__FILE__,__LINE__)
     do n = 1,ndims
       status = nf90_inquire_dimension(ncid,dimid(n),len=nd(n))
       call check_status(status,subname,__FILE__,__LINE__)
     enddo

     if (present(ifld2) .or. present(fld2) .or. present(fld3)) then
       if (xtype == NF90_INT .and. ndims == 2 .and. present(ifld2)) then
         status = nf90_get_var(ncid,varid,ifld2)
         call check_status(status,subname,__FILE__,__LINE__)
       elseif (xtype /= NF90_INT .and. ndims == 2 .and. present(fld2)) then
         status = nf90_get_var(ncid,varid,fld2)
         call check_status(status,subname,__FILE__,__LINE__)
       elseif (xtype /= NF90_INT .and. ndims == 3 .and. present(fld3)) then
         status = nf90_get_var(ncid,varid,fld3)
         call check_status(status,subname,__FILE__,__LINE__)
       else
         write(nulprt,*) subname,estr,'mismatch in field and data'
         call oasis_abort(file=__FILE__,line=__LINE__)
       endif
     endif
    
     status = nf90_close(ncid)
     call check_status(status,subname,__FILE__,__LINE__)

     if (present(nx)) then
      nx = nd(1)
     endif

     if (present(ny)) then
      ny = nd(2)
     endif

     if (present(nz)) then
      nz = nd(3)
     endif

     deallocate(dimid,nd)

   endif

! Scatter info
! EM Since parallel version, must be broadcasted on a subset of mpi ranks
   call oasis_mpi_bcast(xtype,mpi_comm_map,subname//' xtype')
   call oasis_mpi_bcast(ndims,mpi_comm_map,subname//' ndims')

   if (present(ifld2) .or. present(fld2) .or. present(fld3)) then
     if (xtype == NF90_INT .and. ndims == 2 .and. present(ifld2)) then
       call oasis_mpi_bcast(ifld2,mpi_comm_map,subname//' mask')
     elseif (xtype /= NF90_INT .and. ndims == 2 .and. present(fld2)) then
       call oasis_mpi_bcast(fld2,mpi_comm_map,subname//' others')
     elseif (xtype /= NF90_INT .and. ndims == 3 .and. present(fld3)) then
       call oasis_mpi_bcast(fld3,mpi_comm_map,subname//' corners')
     endif
   endif

   if (present(nx)) call oasis_mpi_bcast(nx,mpi_comm_map,subname//' nx')
   if (present(ny)) call oasis_mpi_bcast(ny,mpi_comm_map,subname//' nx')
   if (present(nz)) call oasis_mpi_bcast(nz,mpi_comm_map,subname//' nx')

!   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_read_field_fromroot

!===============================================================================

!> Write a real array named field from the root task to a file.

subroutine oasis_io_write_2dgridfld_fromroot(filename,fldname,fld,nx,ny)

   ! ---------------------------------------
   ! Designed to work with oasis3 write_grid .
   ! ---------------------------------------

   implicit none

   character(len=*), intent(in) :: filename   !< file name
   character(len=*), intent(in) :: fldname    !< field name
   real(ip_realwp_p),intent(in) :: fld(:,:)   !< 2d real field
   integer(ip_i4_p), intent(in) :: nx         !< 2d global nx size
   integer(ip_i4_p), intent(in) :: ny         !< 2d global ny size

   !--- local ---
   integer(ip_i4_p)    :: ncid,dimid,dimid2(2),varid  ! cdf info
   integer(ip_i4_p)    :: iflag       ! netcdf control
   integer(ip_i4_p)    :: status      ! error code
   integer(ip_i4_p)    :: ind         ! string index
   logical             :: exists      ! file existance
   character(len=ic_med) :: gridname  ! grid name derived from fldname

   character(len=*),parameter :: subname = '(oasis_io_write_2dgridfld_fromroot)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   call oasis_debug_enter(subname)

!   expects to run only on 1 pe.
!   if (iam == master_task) then

    if (OASIS_debug >= 5) then
       write(nulprt,*) subname,' write ',trim(filename),' ',trim(fldname),nx,ny
    endif

    ind = index(trim(fldname),'.')
    if (ind < 2) then
       write(nulprt,*) subname,estr,'in fldname ',trim(fldname)
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif
    gridname = fldname(1:ind-1)

    inquire(file=trim(filename),exist=exists)
    if (exists) then
       status = nf90_open(filename,NF90_WRITE,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_redef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    else
       iflag = NF90_CLOBBER
       if (cdf_filetype == 'cdf2') iflag = ior(iflag,oasis_io_64bit_offset)
       if (cdf_filetype == 'cdf5') iflag = ior(iflag,oasis_io_64bit_data)
       status = nf90_create(filename,iflag,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define x dimension if it doesn't exist
    status = nf90_inq_dimid(ncid,'x_'//trim(gridname),dimid2(1))
    if (status /= NF90_NOERR) then
       status = nf90_def_dim(ncid,'x_'//trim(gridname),nx,dimid2(1))
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define y dimension if it doesn't exist
    status = nf90_inq_dimid(ncid,'y_'//trim(gridname),dimid2(2))
    if (status /= NF90_NOERR) then
       status = nf90_def_dim(ncid,'y_'//trim(gridname),ny,dimid2(2))
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define var if it doesn't exist
    status = nf90_inq_varid(ncid,trim(fldname),varid)
    if (status /= NF90_NOERR) then
       status = nf90_def_var(ncid,trim(fldname),NF90_DOUBLE,dimid2,varid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_enddef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_put_var(ncid,varid,fld)
       call check_status(status,subname,__FILE__,__LINE__)
    else
       status = nf90_enddef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    status = nf90_close(ncid)
    call check_status(status,subname,__FILE__,__LINE__)

!   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_write_2dgridfld_fromroot

!===============================================================================

!> Write an integer array named field from the root task to a file.

subroutine oasis_io_write_2dgridint_fromroot(filename,fldname,fld,nx,ny)

   ! ---------------------------------------
   ! Designed to work with oasis3 write_grid .
   ! ---------------------------------------

   implicit none

   character(len=*), intent(in) :: filename   !< file name
   character(len=*), intent(in) :: fldname    !< field name
   integer(ip_i4_p), intent(in) :: fld(:,:)   !< integer field
   integer(ip_i4_p), intent(in) :: nx         !< 2d global nx size
   integer(ip_i4_p), intent(in) :: ny         !< 2d global ny size

   !--- local ---
   integer(ip_i4_p)    :: ncid,dimid,dimid2(2),varid  ! cdf info
   integer(ip_i4_p)    :: iflag       ! netcdf control
   integer(ip_i4_p)    :: status      ! error code
   integer(ip_i4_p)    :: ind         ! string index
   logical             :: exists      ! file existance
   character(len=ic_med) :: gridname  ! grid name derived from fldname

   character(len=*),parameter :: subname = '(oasis_io_write_2dgridint_fromroot)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   call oasis_debug_enter(subname)

!   expects to run only on 1 pe.
!   if (iam == master_task) then

    if (OASIS_debug >= 5) then
       write(nulprt,*) subname,' write ',trim(filename),' ',trim(fldname),nx,ny
    endif

    ind = index(trim(fldname),'.')
    if (ind < 2) then
       write(nulprt,*) subname,estr,'in fldname ',trim(fldname)
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif
    gridname = fldname(1:ind-1)

    inquire(file=trim(filename),exist=exists)
    if (exists) then
       status = nf90_open(filename,NF90_WRITE,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_redef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    else
       iflag = NF90_CLOBBER
       if (cdf_filetype == 'cdf2') iflag = ior(iflag,oasis_io_64bit_offset)
       if (cdf_filetype == 'cdf5') iflag = ior(iflag,oasis_io_64bit_data)
       status = nf90_create(filename,iflag,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define x dimension if it doesn't exist
    status = nf90_inq_dimid(ncid,'x_'//trim(gridname),dimid2(1))
    if (status /= NF90_NOERR) then
       status = nf90_def_dim(ncid,'x_'//trim(gridname),nx,dimid2(1))
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define y dimension if it doesn't exist
    status = nf90_inq_dimid(ncid,'y_'//trim(gridname),dimid2(2))
    if (status /= NF90_NOERR) then
       status = nf90_def_dim(ncid,'y_'//trim(gridname),ny,dimid2(2))
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define var if it doesn't exist
    status = nf90_inq_varid(ncid,trim(fldname),varid)
    if (status /= NF90_NOERR) then
       status = nf90_def_var(ncid,trim(fldname),NF90_INT,dimid2,varid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_enddef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_put_var(ncid,varid,fld)
       call check_status(status,subname,__FILE__,__LINE__)
    else
       status = nf90_enddef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    status = nf90_close(ncid)
    call check_status(status,subname,__FILE__,__LINE__)

!   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_write_2dgridint_fromroot

!===============================================================================

!> Write a 3d real array named field from the root task to a file.

subroutine oasis_io_write_3dgridfld_fromroot(filename,fldname,fld,nx,ny,nc)
 
   ! ---------------------------------------
   ! Designed to work with oasis3 write_grid.
   ! ---------------------------------------

   implicit none

   character(len=*), intent(in) :: filename   !< file name
   character(len=*), intent(in) :: fldname    !< field name
   real(ip_realwp_p), intent(in) :: fld(:,:,:)!< 3d real array
   integer(ip_i4_p), intent(in) :: nx         !< 3d global nx size
   integer(ip_i4_p), intent(in) :: ny         !< 3d global ny size
   integer(ip_i4_p), intent(in) :: nc         !< 3d global nz size or nc size for corners

   !--- local ---
   integer(ip_i4_p)    :: ncid,dimid,dimid3(3),varid  ! cdf info
   integer(ip_i4_p)    :: iflag       ! netcdf control
   integer(ip_i4_p)    :: status      ! error code
   integer(ip_i4_p)    :: ind         ! string index
   logical             :: exists      ! file existance
   character(len=ic_med) :: gridname  ! grid name derived from fldname

   character(len=*),parameter :: subname = '(oasis_io_write_3dgridfld_fromroot)'

!-------------------------------------------------------------------------------
!
!-------------------------------------------------------------------------------

   call oasis_debug_enter(subname)

!   expects to run only on 1 pe.
!   if (iam == master_task) then

    if (OASIS_debug >= 5) then
       write(nulprt,*) subname,' write ',trim(filename),' ',trim(fldname),nx,ny,nc
    endif

    ind = index(trim(fldname),'.')
    if (ind < 2) then
       write(nulprt,*) subname,estr,'in fldname ',trim(fldname)
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif
    gridname = fldname(1:ind-1)

    inquire(file=trim(filename),exist=exists)
    if (exists) then
       status = nf90_open(filename,NF90_WRITE,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_redef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    else
       iflag = NF90_CLOBBER
       if (cdf_filetype == 'cdf2') iflag = ior(iflag,oasis_io_64bit_offset)
       if (cdf_filetype == 'cdf5') iflag = ior(iflag,oasis_io_64bit_data)
       status = nf90_create(filename,iflag,ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define x dimension if it doesn't exist
    status = nf90_inq_dimid(ncid,'x_'//trim(gridname),dimid3(1))
    if (status /= NF90_NOERR) then
       status = nf90_def_dim(ncid,'x_'//trim(gridname),nx,dimid3(1))
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define y dimension if it doesn't exist
    status = nf90_inq_dimid(ncid,'y_'//trim(gridname),dimid3(2))
    if (status /= NF90_NOERR) then
       status = nf90_def_dim(ncid,'y_'//trim(gridname),ny,dimid3(2))
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define crn dimension if it doesn't exist
    status = nf90_inq_dimid(ncid,'crn_'//trim(gridname),dimid3(3))
    if (status /= NF90_NOERR) then
       status = nf90_def_dim(ncid,'crn_'//trim(gridname),nc,dimid3(3))
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    ! define var if it doesn't exist
    status = nf90_inq_varid(ncid,trim(fldname),varid)
    if (status /= NF90_NOERR) then
       status = nf90_def_var(ncid,trim(fldname),NF90_DOUBLE,dimid3,varid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_enddef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
       status = nf90_put_var(ncid,varid,fld)
       call check_status(status,subname,__FILE__,__LINE__)
    else
       status = nf90_enddef(ncid)
       call check_status(status,subname,__FILE__,__LINE__)
    endif

    status = nf90_close(ncid)
    call check_status(status,subname,__FILE__,__LINE__)

!   endif

   call oasis_debug_exit(subname)

end subroutine oasis_io_write_3dgridfld_fromroot

!-------------------------------------------------------------------

subroutine check_status(stat,subn,file,line)

   integer(ip_i4_p), intent(in) :: stat
   character(len=*), intent(in) :: subn
   character(len=*), intent(in) :: file
   integer(ip_i4_p), intent(in) :: line

   character(len=*),parameter :: subname = '(check_status)'

   if (stat /= NF90_NOERR) then
      write(nulprt,*) subname,estr,' netcdf status'
      write(nulprt,*) trim(subn),' nf90_strerror = ',trim(nf90_strerror(stat))
      call oasis_abort(file=file,line=line)
   endif

end subroutine check_status

!-------------------------------------------------------------------

END MODULE mod_oasis_io
