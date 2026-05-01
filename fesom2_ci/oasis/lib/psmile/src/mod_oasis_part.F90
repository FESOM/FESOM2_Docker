
!> OASIS partition data and methods

MODULE mod_oasis_part

   USE mod_oasis_kinds
   USE mod_oasis_data
   USE mod_oasis_parameters
   USE mod_oasis_sys
   USE mod_oasis_mpi
   USE mod_oasis_timer
   USE mod_oasis_load_balancing
   USE mod_oasis_io, only: oasis_io_varexists, oasis_io_read_avfld
   USE mct_mod

   implicit none

   private

   !--- interfaces ---
   public :: oasis_def_partition
   public :: oasis_part_setup
   public :: oasis_part_copy
   public :: oasis_part_find
   public :: oasis_part_readgrid
   public :: oasis_part_create

   !--- datatypes ---
   public :: prism_part_type

   integer(kind=ip_intwp_p),parameter :: mpart = 100  !< maximum number of partitions allowed

   !> Partition (decomposition) data for variables
   type prism_part_type
      character(len=ic_lvar2):: partname !< partition name
      type(mct_gsmap)        :: gsmap    !< gsmap on mpi_comm_local
      integer(kind=ip_i4_p)  :: part0    !< if copied, from this part
      integer(kind=ip_i4_p)  :: gsize    !< global size of grid
      integer(kind=ip_i4_p)  :: lsize    !< local size of grid
      integer(kind=ip_i4_p)  :: nx       !< global nx size
      integer(kind=ip_i4_p)  :: ny       !< global ny size
      character(len=ic_lvar) :: gridname !< grid name
      integer(kind=ip_i4_p)  :: mpicom   !< mpicom for partition tasks only
      integer(kind=ip_i4_p)  :: npes     !< tasks count associated with mpicom partition
      integer(kind=ip_i4_p)  :: rank     !< rank of each task for mpicom partition
      type(mct_gsmap)        :: pgsmap   !< same gsmap but on partition mpicom
      logical                :: indxflag !< has indx field been defined
      logical                :: maskflag !< has mask field been defined
      logical                :: areaflag !< has area field been defined
      logical                :: fracflag !< has frac field been defined
      integer(kind=ip_i4_p),pointer  :: indx(:)  !< global index data
      integer(kind=ip_i4_p),pointer  :: mask(:)  !< mask data
      real   (kind=ip_r8_p),pointer  :: area(:)  !< area data
      real   (kind=ip_r8_p),pointer  :: frac(:)  !< frac data
      !--- temporary storage from def_part inputs ---
      integer(kind=ip_i4_p)  :: ig_size  !< def_part setting
      integer(kind=ip_i4_p),pointer  :: kparal(:)  !< def_part setting
   end type prism_part_type

   integer(kind=ip_intwp_p),public :: prism_npart = 0  !< number of partitions defined
   type(prism_part_type)   ,public :: prism_part(mpart)  !< list of defined partitions

   !--- for automatic naming of partname
   !--- better than prism_npart, counts only unnamed parts
   integer(kind=ip_intwp_p)        :: part_name_cnt = 0  !< used to define partition names internally

CONTAINS

!--------------------------------------------------------------------

!> The OASIS user interface to define partitions

  SUBROUTINE oasis_def_partition (id_part, kparal, kinfo, ig_size, name)

!*    *** Def_partition ***   PRISM 1.0
!
!     purpose:
!     --------
!        define a decomposition
!
!     interface:
!     ----------
!        id_part : field decomposition id
!        kparal : type of parallel decomposition
!	 kinfo	: output status
!
!     author:
!     -------
!        Arnaud Caubel - FECIT
!
!  ----------------------------------------------------------------
   INTEGER(kind=ip_intwp_p)              ,intent(out) :: id_part  !< partition id
   INTEGER(kind=ip_intwp_p), DIMENSION(:),intent(in)  :: kparal   !< decomposition information
   INTEGER(kind=ip_intwp_p), optional    ,intent(out) :: kinfo    !< return code
   INTEGER(kind=ip_intwp_p), optional    ,intent(in)  :: ig_size  !< total size of partition
   character(len=*)        , optional    ,intent(in)  :: name     !< name of partition
!  ----------------------------------------------------------------
   integer(kind=ip_intwp_p) :: n
   character(len=*),parameter :: subname = '(oasis_def_partition)'
!  ----------------------------------------------------------------

   call oasis_debug_enter(subname)

   if (.not. oasis_coupled) then
     call oasis_debug_exit(subname)
     return
   endif

   kinfo = OASIS_OK

   !-----------------------------------------------
   !> * Increment partition number and store user values
   !-----------------------------------------------

   call oasis_timer_start('part_definition')

   if (ET_debug) CALL oasis_lb_measure(-1,LB_PART)

   prism_npart = prism_npart + 1
   if (prism_npart > mpart) then
      write(nulprt,*) subname,estr,'prism_npart too large = ',prism_npart,mpart
      write(nulprt,*) subname,estr,'increase mpart in mod_oasis_part.F90'
      call oasis_abort(file=__FILE__,line=__LINE__)
   endif
   call oasis_part_zero(prism_part(prism_npart))
   id_part = prism_npart

   if (present(name)) then
      if (len_trim(name) > len(prism_part(prism_npart)%partname)) then
         write(nulprt,*) subname,estr,'part name too long = ',trim(name)
         write(nulprt,*) subname,estr,'part name max length = ',len(prism_part(prism_npart)%partname)
         call oasis_abort(file=__FILE__,line=__LINE__)
      endif
      prism_part(prism_npart)%partname = trim(name)
   else
      part_name_cnt = part_name_cnt + 1
      write(prism_part(prism_npart)%partname,'(a,i6.6)') trim(compnm)//'_part',part_name_cnt
   endif

   if (present(ig_size)) then
      prism_part(prism_npart)%ig_size = ig_size
   endif

   allocate(prism_part(prism_npart)%kparal(size(kparal)))
   prism_part(prism_npart)%kparal = kparal

   if (ET_debug) CALL oasis_lb_measure(-1,LB_PART)

   call oasis_timer_stop('part_definition')

   call oasis_debug_exit(subname)

 END SUBROUTINE oasis_def_partition

!------------------------------------------------------------

!> Synchronize partitions across all tasks, called at oasis enddef.

  SUBROUTINE oasis_part_setup()
   IMPLICIT NONE

   !--------------------------------------------------------
   integer(kind=ip_intwp_p) :: m,n,k,p,nsegs,numel,taskid
   INTEGER(kind=ip_intwp_p) :: icpl,ierr,ilen
   integer(kind=ip_intwp_p),pointer :: start(:),length(:)
   integer(kind=ip_intwp_p),pointer :: kparal(:)
   integer(kind=ip_intwp_p) :: ig_size
   integer(kind=ip_intwp_p) :: pcnt
   logical                  :: found
   character(len=ic_lvar2), allocatable :: pname0(:),pname(:)
   logical, parameter :: local_timers_on = .false.
   character(len=*),parameter :: subname = '(oasis_part_setup)'
   !--------------------------------------------------------

   call oasis_debug_enter(subname)

   if (local_timers_on) then
      call oasis_timer_start('part_setup_barrier')
      if (mpi_comm_local /= MPI_COMM_NULL) &
               call MPI_BARRIER(mpi_comm_local, ierr)
      call oasis_timer_stop('part_setup_barrier')
   endif
   if (local_timers_on) call oasis_timer_start('part_setup')

   !-----------------------------------------------
   !> * Generate reduced partname list
   !-----------------------------------------------
   IF (local_timers_on) CALL oasis_timer_start('part_setup_reducelists')
   allocate(pname0(prism_npart))
   do n = 1,prism_npart
      pname0(n) = prism_part(n)%partname
   enddo
   call oasis_mpi_reducelists(pname0,mpi_comm_local,pcnt,pname,'part_setup',fastcheck=.true.)
   deallocate(pname0)
   IF (local_timers_on) CALL oasis_timer_stop('part_setup_reducelists')

   !-------------------------------------------------     
   !> * Define all partitions on all tasks
   !-------------------------------------------------     

   if (local_timers_on) then
      call oasis_timer_start('part_setup_initgsm_barrier')
      if (mpi_comm_local /= MPI_COMM_NULL) &
               call MPI_BARRIER(mpi_comm_local, ierr)
      call oasis_timer_stop('part_setup_initgsm_barrier')
   endif
   IF (local_timers_on) CALL oasis_timer_start('part_setup_initgsm')
   do p = 1,pcnt

      if (local_timers_on) call oasis_timer_start('part_setup_initgsm_A')
      !--- set m, either a prism_part that already exists
      found = .false.
      n = 0
      do while (n < prism_npart .and. .not.found)
         n = n + 1
         if (prism_part(n)%partname == pname(p)) then
            m = n
            found = .true.
         endif
      enddo
      if (local_timers_on) call oasis_timer_stop('part_setup_initgsm_A')

      if (local_timers_on) call oasis_timer_start('part_setup_initgsm_B')
      !--- or m is a new prism_part that must be instantiated
      !--- and set to have no data
      if (.not.found) then
         prism_npart = prism_npart + 1
         m = prism_npart
         call oasis_part_zero(prism_part(prism_npart))
         prism_part(prism_npart)%partname = pname(p)
         allocate(prism_part(prism_npart)%kparal(3))
         prism_part(prism_npart)%kparal = 0
      endif
      if (local_timers_on) call oasis_timer_stop('part_setup_initgsm_B')

      !-------------------------------------------------     
      !> * Convert kparal information to data for the gsmap
      !-------------------------------------------------     

      if (local_timers_on) call oasis_timer_start('part_setup_initgsm_C')
      allocate(kparal(size(prism_part(m)%kparal)))
      kparal = prism_part(m)%kparal
      ig_size = prism_part(m)%ig_size

      if (kparal(CLIM_Strategy) == CLIM_Serial) then
         nsegs = 1
         allocate(start(nsegs),length(nsegs))
         start (1) = 1
         length(1) = kparal(CLIM_Length)
         numel = nsegs
         if (length(1) == 0) numel = 0
      elseif (kparal(CLIM_Strategy) == CLIM_Apple) then
         nsegs = 1
         allocate(start(nsegs),length(nsegs))
         start (1) = kparal(CLIM_Offset) + 1
         length(1) = kparal(CLIM_Length)
         numel = nsegs
         if (length(1) == 0) numel = 0
      elseif (kparal(CLIM_Strategy) == CLIM_Box) then
         nsegs = kparal(CLIM_SizeY)
         allocate(start(nsegs),length(nsegs))
         do n = 1,nsegs
            start (n) = kparal(CLIM_Offset) + (n-1)*kparal(CLIM_LdX) + 1
            length(n) = kparal(CLIM_SizeX)
         enddo
         numel = nsegs
         if (kparal(CLIM_SizeY)*kparal(CLIM_SizeX) == 0) numel = 0
      elseif (kparal(CLIM_Strategy) == CLIM_Orange) then
         nsegs = kparal(CLIM_Segments)
         allocate(start(nsegs),length(nsegs))
         numel = 0
         DO n = 1,nsegs
           ilen = kparal((n-1)*2 + 4)
           IF (ilen > 0) THEN
               numel = numel + 1
               start(numel)  = kparal((n-1)*2 + 3) + 1
               length(numel) = ilen
           ENDIF
         ENDDO 
      elseif (kparal(CLIM_Strategy) == CLIM_Points) then
         nsegs = kparal(CLIM_Segments)
         allocate(start(nsegs),length(nsegs))
         numel = 0
         if (nsegs > 0) then
           !--- initialize first segment, nsegs=1,n=1,k=3
           nsegs = 1
           n = 1
           k = n+2
           start(nsegs)  = kparal(k)
           length(nsegs) = 1
           !--- compute rest of segments from n=2,k=4
           do n = 2,kparal(CLIM_Segments)
              k = n+2
              if (kparal(k)-kparal(k-1) == 1) then
                 length(nsegs) = length(nsegs) + 1
              else
                 nsegs = nsegs + 1
                 start(nsegs)  = kparal(k)
                 length(nsegs) = 1
              endif
           enddo
           numel = nsegs
         endif
      else
         write(nulprt,*) subname,estr,'part strategy unknown in def_part = ',kparal(CLIM_Strategy)
         write(nulprt,*) subname,estr,'strategy set in kparal array index ',CLIM_Strategy
         call oasis_abort(file=__FILE__,line=__LINE__)
      endif

      IF (OASIS_debug >= 30)  THEN
         WRITE(nulprt,*) subname, ' Nsegs before calling mct_gsmap_init :',nsegs
         WRITE(nulprt,*) subname, ' Numel before calling mct_gsmap_init :',numel
         CALL oasis_flush(nulprt)
      ENDIF

      if (local_timers_on) call oasis_timer_stop('part_setup_initgsm_C')
   
      !-------------------------------------------------     
      !> * Initialize the local gsmap and partition gsmap
      !-------------------------------------------------     

      if (local_timers_on) call oasis_timer_start('part_setup_initgsm_D')
      if (mpi_comm_local /= MPI_COMM_NULL) then
         if (ig_size > 0) then
            call mct_gsmap_init(prism_part(m)%gsmap,start,length,mpi_root_local,&
                                mpi_comm_local,compid,numel=numel,gsize=ig_size)
         else
            call mct_gsmap_init(prism_part(m)%gsmap,start,length,mpi_root_local,&
                                mpi_comm_local,compid,numel=numel)
         endif
         prism_part(m)%gsize = mct_gsmap_gsize(prism_part(m)%gsmap)
         prism_part(m)%lsize = mct_gsmap_lsize(prism_part(m)%gsmap,mpi_comm_local)
         icpl = MPI_UNDEFINED
         if (numel > 0) icpl = 1
         CALL MPI_COMM_Split(mpi_comm_local,icpl,1,prism_part(m)%mpicom,ierr)
         if (numel > 0) then
            CALL MPI_Comm_Size ( prism_part(m)%mpicom, prism_part(m)%npes, ierr )
            CALL MPI_Comm_Rank ( prism_part(m)%mpicom, prism_part(m)%rank, ierr )
            if (ig_size > 0) then
               call mct_gsmap_init(prism_part(m)%pgsmap,start,length,0, &
                                   prism_part(m)%mpicom,compid,numel=numel,gsize=ig_size)
            else
               call mct_gsmap_init(prism_part(m)%pgsmap,start,length,0, &
                                   prism_part(m)%mpicom,compid,numel=numel)
            endif
         else
            ! override mpicom created by split with null
            prism_part(m)%mpicom = MPI_COMM_NULL
         endif
      !else
      !! set by default
      !   prism_part(m)%gsize = -1
      !   prism_part(m)%mpicom = MPI_COMM_NULL
      endif
      if (local_timers_on) call oasis_timer_stop('part_setup_initgsm_D')
   
      if (local_timers_on) call oasis_timer_start('part_setup_initgsm_E')
      deallocate(start,length)
      deallocate(kparal)
      deallocate(prism_part(m)%kparal)
   
      if (OASIS_debug >= 2) then
         call oasis_part_write(prism_part(m),m)
      endif
      if (local_timers_on) call oasis_timer_stop('part_setup_initgsm_E')

   enddo   ! p = 1,pcnt

   deallocate(pname)

   if (local_timers_on) call oasis_timer_stop ('part_setup_initgsm')
   if (local_timers_on) call oasis_timer_stop('part_setup')

   call oasis_debug_exit(subname)

 END SUBROUTINE oasis_part_setup

!------------------------------------------------------------

!> Zero partition information

  SUBROUTINE oasis_part_zero(s_prism_part)

  IMPLICIT NONE

  type(prism_part_type),intent(inout) :: s_prism_part
  !--------------------------------------------------------
  character(len=*),parameter :: subname = '(oasis_part_zero)'
  !--------------------------------------------------------

   call oasis_debug_enter(subname)

   s_prism_part%partname = trim(cspval)
   s_prism_part%part0    = -1
   s_prism_part%gsize    = -1
   s_prism_part%lsize    = -1
   s_prism_part%nx       = -1
   s_prism_part%ny       = -1
   s_prism_part%gridname = trim(cspval)
   s_prism_part%mpicom   = MPI_COMM_NULL
   s_prism_part%npes     = -1
   s_prism_part%rank     = -1
   s_prism_part%ig_size  = -1
   s_prism_part%indxflag = .false.
   s_prism_part%maskflag = .false.
   s_prism_part%areaflag = .false.
   s_prism_part%fracflag = .false.

   call oasis_debug_exit(subname)

 END SUBROUTINE oasis_part_zero

!------------------------------------------------------------

!> Print parition information

  SUBROUTINE oasis_part_write(s_prism_part,npart)

  IMPLICIT NONE

  type(prism_part_type),intent(in) :: s_prism_part
  integer(ip_i4_p)     ,intent(in) :: npart
  !--------------------------------------------------------
  character(len=*),parameter :: subname = '(oasis_part_write)'
  !--------------------------------------------------------

   call oasis_debug_enter(subname)

   write(nulprt,*) ' '
   write(nulprt,*) subname,' partnm = ',trim(s_prism_part%partname)
   write(nulprt,*) subname,' npart  = ',npart
   write(nulprt,*) subname,' part0  = ',s_prism_part%part0
   write(nulprt,*) subname,' mpicom = ',s_prism_part%mpicom
   write(nulprt,*) subname,' npes   = ',s_prism_part%npes
   write(nulprt,*) subname,' rank   = ',s_prism_part%rank
   write(nulprt,*) subname,' compid = ',s_prism_part%gsmap%comp_id
   write(nulprt,*) subname,' ngseg  = ',s_prism_part%gsmap%ngseg
   write(nulprt,*) subname,' gsize  = ',s_prism_part%gsmap%gsize
   write(nulprt,*) subname,' lsize  = ',s_prism_part%lsize
   write(nulprt,*) subname,' indx   = ',size(s_prism_part%indx)
   if (s_prism_part%gsmap%ngseg > 10) then
      IF (mpi_comm_local /= MPI_COMM_NULL) THEN
         WRITE(nulprt,*) subname,' start  = ',s_prism_part%gsmap%start(1:10)
         WRITE(nulprt,*) subname,' length = ',s_prism_part%gsmap%length(1:10)
         WRITE(nulprt,*) subname,' pe_loc = ',s_prism_part%gsmap%pe_loc(1:10)
      ENDIF
      IF (s_prism_part%mpicom /= MPI_COMM_NULL) THEN
         WRITE(nulprt,*) subname,' pstart = ',s_prism_part%pgsmap%start(1:10)
         WRITE(nulprt,*) subname,' plength= ',s_prism_part%pgsmap%length(1:10)
         WRITE(nulprt,*) subname,' ppe_loc= ',s_prism_part%pgsmap%pe_loc(1:10)
      ENDIF
   else
      IF (mpi_comm_local /= MPI_COMM_NULL) THEN
         WRITE(nulprt,*) subname,' start  = ',s_prism_part%gsmap%start
         WRITE(nulprt,*) subname,' length = ',s_prism_part%gsmap%length
         WRITE(nulprt,*) subname,' pe_loc = ',s_prism_part%gsmap%pe_loc
      ENDIF
      IF (s_prism_part%mpicom /= MPI_COMM_NULL) THEN
         WRITE(nulprt,*) subname,' pstart = ',s_prism_part%pgsmap%start
         WRITE(nulprt,*) subname,' plength= ',s_prism_part%pgsmap%length
         WRITE(nulprt,*) subname,' ppe_loc= ',s_prism_part%pgsmap%pe_loc
      ENDIF
   endif
   if (s_prism_part%indxflag) write(nulprt,*) subname,' indxflag = ',s_prism_part%indxflag
   if (s_prism_part%maskflag) write(nulprt,*) subname,' maskflag = ',s_prism_part%maskflag
   if (s_prism_part%areaflag) write(nulprt,*) subname,' areaflag = ',s_prism_part%areaflag
   if (s_prism_part%fracflag) write(nulprt,*) subname,' fracflag = ',s_prism_part%fracflag
   write(nulprt,*) ' '
   CALL oasis_flush(nulprt)

   call oasis_debug_exit(subname)

 END SUBROUTINE oasis_part_write

!------------------------------------------------------------

!> Read grid data into partition

  SUBROUTINE oasis_part_readgrid()
   IMPLICIT NONE

   !--------------------------------------------------------
   integer(kind=ip_intwp_p) :: m
   integer(kind=ip_intwp_p) :: ierr
   integer(kind=ip_intwp_p) :: lsize,kmask,karea,kfrac
   character(len=ic_lvar)   :: gridname
   type(mct_aVect)          :: avin
   logical, parameter :: local_timers_on = .false.
   character(len=*),parameter :: subname = '(oasis_part_readgrid)'
   !--------------------------------------------------------

   call oasis_debug_enter(subname)

   if (local_timers_on) then
      call oasis_timer_start('part_readgrid_barrier')
      if (mpi_comm_local /= MPI_COMM_NULL) &
               call MPI_BARRIER(mpi_comm_local, ierr)
      call oasis_timer_stop('part_readgrid_barrier')
   endif
   if (local_timers_on) call oasis_timer_start('part_readgrid')

   do m = 1,prism_npart
      gridname = prism_part(m)%gridname
      if (prism_part(m)%rank == 0 .and. OASIS_debug >= 2) write(nulprt,*) subname,m,trim(prism_part(m)%partname),' ',trim(gridname)
      if (prism_part(m)%mpicom /= MPI_COMM_NULL) then
         lsize = mct_gsmap_lsize(prism_part(m)%pgsmap, prism_part(m)%mpicom)
      else
         lsize = 0
      endif

      ! store indx first
      prism_part(m)%indxflag = .true.
      call mct_gsmap_OrderedPoints(prism_part(m)%pgsmap, prism_part(m)%rank, prism_part(m)%indx)
      if (prism_part(m)%rank == 0 .and. OASIS_debug >= 2) then
         write(nulprt,*) subname,' set indx ',trim(gridname),' for ',trim(prism_part(m)%partname), size(prism_part(m)%indx)
         if (size(prism_part(m)%indx) > 0) then
            write(nulprt,*) subname,' indx = ',prism_part(m)%indx(1:min(10,size(prism_part(m)%indx)))
         endif
      endif

      ! read mask, area, frac
      call mct_avect_init(avin,iList='mask',rList='area:frac',lsize=lsize)
      call mct_avect_zero(avin)
      kmask = mct_aVect_indexIA(avin,'mask')
      karea = mct_aVect_indexRA(avin,'area')
      kfrac = mct_aVect_indexRA(avin,'frac')
      if (oasis_io_varexists('areas.nc',trim(gridname)//'.srf')) then
         call oasis_io_read_avfld('areas.nc',avin, &
            prism_part(m)%pgsmap, prism_part(m)%mpicom,'area',trim(gridname)//'.srf',fldtype='real')
         prism_part(m)%areaflag = .true.
         allocate(prism_part(m)%area(lsize))
         prism_part(m)%area(:) = avin%rAttr(karea,:)
         if (prism_part(m)%rank == 0 .and. OASIS_debug >= 2) write(nulprt,*) subname,' read area ',trim(gridname),' for ',trim(prism_part(m)%partname) ! ,minval(prism_part(m)%area),maxval(prism_part(m)%area)
      endif
      if (oasis_io_varexists('masks.nc',trim(gridname)//'.frc')) then
         call oasis_io_read_avfld('masks.nc',avin, &
            prism_part(m)%pgsmap, prism_part(m)%mpicom,'frac',trim(gridname)//'.frc',fldtype='real')
         prism_part(m)%fracflag = .true.
         allocate(prism_part(m)%frac(lsize))
         prism_part(m)%frac(:) = avin%rAttr(kfrac,:)
         if (prism_part(m)%rank == 0 .and. OASIS_debug >= 2) write(nulprt,*) subname,' read frac ',trim(gridname),' for ',trim(prism_part(m)%partname) ! ,minval(prism_part(m)%frac),maxval(prism_part(m)%frac)
      endif
      if (oasis_io_varexists('masks.nc',trim(gridname)//'.msk')) then
         call oasis_io_read_avfld('masks.nc',avin, &
            prism_part(m)%pgsmap, prism_part(m)%mpicom,'mask',trim(gridname)//'.msk',fldtype='int')
         prism_part(m)%maskflag = .true.
         allocate(prism_part(m)%mask(lsize))
         prism_part(m)%mask(:) = avin%iAttr(kmask,:)
         if (prism_part(m)%rank == 0 .and. OASIS_debug >= 2) write(nulprt,*) subname,' read mask ',trim(gridname),' for ',trim(prism_part(m)%partname) ! ,minval(prism_part(m)%mask),maxval(prism_part(m)%mask)
      endif
      call mct_avect_clean(avin)
   enddo

   if (local_timers_on) call oasis_timer_stop('part_readgrid')

   call oasis_debug_exit(subname)

 END SUBROUTINE oasis_part_readgrid

!------------------------------------------------------------

!> Copy base partition to new partition

  SUBROUTINE oasis_part_copy(partbase,partnew)

  IMPLICIT NONE

  integer(ip_i4_p),intent(in)  :: partbase !< base partition id
  integer(ip_i4_p),intent(out) :: partnew  !<  new partition id
  !--------------------------------------------------------
  integer(ip_i4_p) :: lsize
  character(len=*),parameter :: subname = '(oasis_part_copy)'
  !--------------------------------------------------------

  call oasis_debug_enter(subname)

  prism_npart = prism_npart + 1
  call oasis_part_zero(prism_part(prism_npart))
  
  part_name_cnt = part_name_cnt + 1
  write(prism_part(prism_npart)%partname,'(a,i6.6)') trim(compnm)//'_part',part_name_cnt
  prism_part(prism_npart)%part0    = partbase
  prism_part(prism_npart)%gsize    = prism_part(partbase)%gsize
  prism_part(prism_npart)%lsize    = prism_part(partbase)%lsize
  prism_part(prism_npart)%mpicom   = prism_part(partbase)%mpicom
  prism_part(prism_npart)%npes     = prism_part(partbase)%npes
  prism_part(prism_npart)%rank     = prism_part(partbase)%rank
  prism_part(prism_npart)%indxflag = prism_part(partbase)%indxflag
  prism_part(prism_npart)%maskflag = prism_part(partbase)%maskflag
  prism_part(prism_npart)%areaflag = prism_part(partbase)%areaflag
  prism_part(prism_npart)%fracflag = prism_part(partbase)%fracflag
  prism_part(prism_npart)%ig_size  = prism_part(partbase)%ig_size

  if (prism_part(prism_npart)%mpicom /= MPI_COMM_NULL) then
     lsize = mct_gsmap_lsize(prism_part(prism_npart)%pgsmap, prism_part(prism_npart)%mpicom)
  else
     lsize = 0
  endif
  if (prism_part(partbase)%indxflag) then
     allocate(prism_part(prism_npart)%indx(lsize))
     prism_part(prism_npart)%indx(:) = prism_part(partbase)%indx(:)
  endif
  if (prism_part(partbase)%maskflag) then
     allocate(prism_part(prism_npart)%mask(lsize))
     prism_part(prism_npart)%mask(:) = prism_part(partbase)%mask(:)
  endif
  if (prism_part(partbase)%areaflag) then
     allocate(prism_part(prism_npart)%area(lsize))
     prism_part(prism_npart)%area(:) = prism_part(partbase)%area(:)
  endif
  if (prism_part(partbase)%fracflag) then
     allocate(prism_part(prism_npart)%frac(lsize))
     prism_part(prism_npart)%frac(:) = prism_part(partbase)%frac(:)
  endif

  if (associated(prism_part(partbase)%kparal)) then
     allocate(prism_part(prism_npart)%kparal(size(prism_part(partbase)%kparal)))
     prism_part(prism_npart)%kparal(:) = prism_part(partbase)%kparal(:)
  endif

  if (prism_part(partbase)%gsize > 0) then
     ! if test is proxy for testing initialized gsmap
     call mct_gsMap_copy(prism_part(partbase)%gsmap , prism_part(prism_npart)%gsmap)
     call mct_gsMap_copy(prism_part(partbase)%pgsmap, prism_part(prism_npart)%pgsmap)
  endif

  partnew = prism_npart

  call oasis_debug_exit(subname)

END SUBROUTINE oasis_part_copy

!------------------------------------------------------------

!> Find matching base partition to new partition

  SUBROUTINE oasis_part_find(partbase,partnew,nx,ny,gridname)

  IMPLICIT NONE

  integer(ip_i4_p),intent(in)    :: partbase !< base partition id
  integer(ip_i4_p),intent(inout) :: partnew  !<  new partition id
  integer(ip_i4_p),intent(in)    :: nx       !<  new partition nx
  integer(ip_i4_p),intent(in)    :: ny       !<  new partition ny
  character(len=*),intent(in)    :: gridname !<  new partition gridname
  !--------------------------------------------------------
  integer(ip_i4_p) :: n
  character(len=*),parameter :: subname = '(oasis_part_find)'
  !--------------------------------------------------------

  call oasis_debug_enter(subname)

  ! Find a duplicated part that matches the "base" partid and grid

  partnew = -1
  n = 0
  do while (partnew < 0 .and. n < prism_npart)
     n = n + 1
     if (prism_part(n)%part0 == partbase .and. &
         prism_part(n)%nx    == nx       .and. &
         prism_part(n)%ny    == ny       .and. &
         trim(prism_part(n)%gridname) == trim(gridname)) then
        partnew = n
     endif
  enddo

  call oasis_debug_exit(subname)

END SUBROUTINE oasis_part_find

!------------------------------------------------------------

!> Create a new partition internally, needed for mapping

  SUBROUTINE oasis_part_create(id_part,TYPE,gsize,nx,ny,gridname,gscomm,mpicom,gridID)

  IMPLICIT NONE

  integer(ip_i4_p),intent(out) :: id_part  !< partition id
  character(len=*),intent(in)  :: type     !< type of decomposition specified
  integer(ip_i4_p),intent(in)  :: gsize    !< global size of grid
  integer(ip_i4_p),intent(in)  :: nx       !< global nx size
  integer(ip_i4_p),intent(in)  :: ny       !< global ny size
  character(len=*),intent(in)  :: gridname !< grid name
  integer(ip_i4_p),intent(in)  :: gscomm   !< global seg map communicator
  integer(ip_i4_p),intent(in)  :: mpicom   !< local mpi comm
  integer(ip_i4_p), optional   :: gridID(:)!< gridcell ID
  !--------------------------------------------------------
  integer(ip_i4_p) :: gsrank
  integer(ip_i4_p) :: gssize
  integer(ip_i4_p) :: numel
  integer(ip_i4_p),pointer :: start(:),length(:)
  integer(ip_i4_p),pointer :: llist(:),glist(:)
  integer(ip_i4_p) :: pts
  integer(ip_i4_p) :: found,foundall
  integer(ip_i4_p) :: n
  integer(ip_i4_p) :: ierr
  character(len=*),parameter :: subname = '(oasis_part_create)'
  !--------------------------------------------------------

  call oasis_debug_enter(subname)

  if (gscomm /= MPI_COMM_NULL) then
     call MPI_COMM_RANK(gscomm,gsrank,ierr)
     call MPI_COMM_SIZE(gscomm,gssize,ierr)
  else
     gsrank = -1
     gssize = -1 
  endif

  if (OASIS_debug >= 15) then
     write(nulprt,*) subname,' called with ',gsize,nx,ny,trim(gridname)
     write(nulprt,*) subname,' local ',gsrank,gssize
  endif

  if ((type == 'decomp_wghtfile' .and. .not.present(gridID)) .or. &
      (type /= 'decomp_wghtfile' .and.      present(gridID))) then
     write(nulprt,*) subname,estr,'decomp_wghtfile and gridID arguments inconsistent ',trim(type)
     call oasis_abort(file=__FILE__,line=__LINE__)
  endif

  !-----------------------------------------------
  !> * Check if an existing gsmap can be reused
  !-----------------------------------------------

  id_part = -1
  found = 0
  n = 0
  do while (found == 0 .and. n < prism_npart)
     n = n + 1
     if (prism_part(n)%gsize == gsize .and. &
        trim(prism_part(n)%gridname) == trim(gridname) .and. &
        prism_part(n)%mpicom == gscomm .and. &
        prism_part(n)%nx == nx .and. &
        prism_part(n)%ny == ny) then
        id_part = n
        found = 1
     endif
  enddo

  !-----------------------------------------------
  !> * Check that all tasks agree and if so, return with that partition id
  !-----------------------------------------------

  foundall = -1
  call oasis_mpi_min(found,foundall,mpicom,string=subname//' found',all=.true.)
  if (foundall == 1) then
     if (OASIS_debug >= 2) then
        write(nulprt,*) subname,' reuse part ',prism_npart,gsize
     endif
     call oasis_debug_exit(subname)
     return
  endif

  !-----------------------------------------------
  !> * Instantiate a decomposition based on gsize and type
  !-----------------------------------------------

  prism_npart = prism_npart + 1
  call oasis_part_zero(prism_part(prism_npart))

  !-----------------------------------------------
  !>   * Create a new partition and set values
  !-----------------------------------------------

  part_name_cnt = part_name_cnt + 1
  write(prism_part(prism_npart)%partname,'(a,i6.6)') trim(compnm)//'_part',part_name_cnt
  prism_part(prism_npart)%gsize = gsize
  prism_part(prism_npart)%nx = nx
  prism_part(prism_npart)%ny = ny
  prism_part(prism_npart)%gridname = trim(gridname)
  prism_part(prism_npart)%mpicom = gscomm
  prism_part(prism_npart)%npes = gssize
  prism_part(prism_npart)%rank = gsrank

  allocate(start(1),length(1))
  start = 1
  length = 0
  numel = 0

  if (trim(type) == 'decomp_1d') then
     pts = 0
     if (gsrank >= 0) then
        numel = 1
        length(1) = gsize/gssize
        pts = gsize - length(1)*gssize
        if (gsrank < pts) length(1) = length(1) + 1
        start(1) = gsize/gssize*(gsrank) + min(gsrank,pts) + 1
     endif

     if (OASIS_debug >= 15) then
        write(nulprt,*) subname,trim(type),numel,start,length,pts
     endif

  elseif (trim(type) == 'decomp_wghtfile') then
     allocate(llist(gsize),glist(gsize))
     llist = -1
     numel = 0
     if (gsrank >= 0) then
        if (OASIS_debug >= 15) then
           write(nulprt,*) subname,' wgts1 ',size(gridID)
           write(nulprt,*) subname,' gridID ',minval(gridID),maxval(gridID)
        endif
        do n = 1,size(gridID)
           if (gridID(n) > 0 .and. gridID(n) <= gsize) then
              numel = numel + 1
              llist(gridID(n)) = gsrank
!           elseif (gridID(n) > gsize) then
! tcraig, allow > gsize and ignore it, errors trapped/ignored in map read
!              write(nulprt,*) subname,estr,'gridID > gsize',gridID(n),gsize
!              call oasis_abort(file=__FILE__,line=__LINE__)
!           else
! tcraig, allow <= 0 and ignore it, errors trapped/ignored in map read
!              write(nulprt,*) subname,estr,'gridID <= 0',gridID(n),gsize
!              call oasis_abort(file=__FILE__,line=__LINE__)
          endif
        enddo

        ! this computes the max MPI rank that includes the gridcell
        ! max is arbitrary but this forces each gridcell to be associated with just one rank
        call oasis_mpi_max(llist,glist,gscomm,string=trim(subname)//' glist',all=.true.)

        deallocate(llist)
        deallocate(start,length)
        allocate(start(numel),length(numel))
        start = -1
        length = -1
        numel = 0
        do n = 1,gsize
           if (glist(n) == gsrank) then
              numel = numel + 1
              if (numel > size(gridID)) then
                 write(nulprt,*) subname,estr,'numel error ',numel,size(gridID)
                 call oasis_abort(file=__FILE__,line=__LINE__)
              endif
              start(numel) = n
              length(numel) = 1
           endif
        enddo
        deallocate(glist)
     endif   ! gsrank >= 0

     if (OASIS_debug >= 15) then
        write(nulprt,*) subname,trim(type),numel
        call oasis_flush(nulprt)
     endif

  else
     write(nulprt,*) subname,estr,'type argument unknown = ',trim(type)
     call oasis_abort(file=__FILE__,line=__LINE__)
  endif

  !-----------------------------------------------
  !>   * Initialize the partition gsmap and pgsmap
  !-----------------------------------------------

  call mct_gsmap_init(prism_part(prism_npart)%gsmap,start,length,0,mpicom,compid,gsize=gsize,numel=numel)
  if (gsrank >= 0) then
     call mct_gsmap_init(prism_part(prism_npart)%pgsmap,start,length,0, &
                         prism_part(prism_npart)%mpicom,compid,gsize=gsize,numel=numel)
  endif
  deallocate(start,length)
  if (OASIS_debug >= 2) then
     write(nulprt,*) subname,' create new part ',prism_npart,gsize
     call oasis_part_write(prism_part(prism_npart),prism_npart)
  endif

  id_part = prism_npart

  call oasis_debug_exit(subname)

END SUBROUTINE oasis_part_create

!------------------------------------------------------------

END MODULE mod_oasis_part
