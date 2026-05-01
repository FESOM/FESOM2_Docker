!
! !DESCRIPTION:
!
!> Load balancing methods
!
!>  Take wall clock time before and after selected OASIS actions 
!>  and calculate quantities to help evaluating coupled component
!>  load imbalance and other performance related quantities
!
! Available routines:
!  oasis_lb_init              initialise global timers
!  oasis_lb_allocate          allocates timers
!  oasis_lb_define            fill timers header
!  oasis_lb_measure           fill timers
!  oasis_lb_print             calculate and output load imbalance evaluation
!
!
! !REVISION HISTORY:
!
!   Date      Programmer     Description
! ----------  ----------     -----------
! 22.07.2020  E. Maisonnave  created (based on mod_oasis_timer.F90 from M.H.)
!
!----------------------------------------------------------------------

module mod_oasis_load_balancing

   use mod_oasis_kinds
   use mod_oasis_data
   use mod_oasis_sys
   USE mod_oasis_mpi
   USE netcdf

   implicit none
   private

   public oasis_lb_init
   public oasis_lb_allocate
   public oasis_lb_define
   public oasis_lb_measure
   public oasis_lb_print
   public oasis_lb_stop

   !> Storage for timer data
   type timeline_lb
      !
      ! timer
      real(ip_single_p)     :: timer
      !
      ! kind of the measured quantity 
      integer(kind=ip_i4_p) :: kind
      !
      ! id of the field
      integer(kind=ip_i4_p) :: field
      !
      ! id of the counterpart coupled component 
      integer(kind=ip_i4_p) :: cntp
      !
      ! id of the timestep (from msec)
      integer(kind=ip_i4_p) :: tsid
      !
   end type timeline_lb

   ! This array stores the timeline : the dates of every coupling events
   !  and three informations related to the event : 
   !    - its kind, 
   !    - the coupling field ID (if applicable)
   !    - the counterpart model in the coupling exchange (if applicable)

   type(timeline_lb) , pointer :: local_timeline(:)



   ! ID flags : kind of coupling events
   integer(kind=ip_i4_p), parameter, public :: LB_PUT  = 1  ! send coupling field
   integer(kind=ip_i4_p), parameter, public :: LB_GET  = 2  ! receive coupling field
   integer(kind=ip_i4_p), parameter, public :: LB_MAP  = 3  ! map or interpolate
   integer(kind=ip_i4_p), parameter, public :: LB_OUT  = 4  ! output to netCDF file
   integer(kind=ip_i4_p), parameter, public :: LB_READ = 5  ! input from netCDF file
   integer(kind=ip_i4_p), parameter, public :: LB_RST  = 6  ! restart writing
   integer(kind=ip_i4_p), parameter, public :: LB_TRN  = 7  ! partial restart writing
   ! Put here the maximum of field related events
   integer(kind=ip_i4_p), parameter, public :: LB_MAX  = 7

   ! Operation performed during initialisation phase ( = 2 = LB_NB_INIT_TIMING )
   integer(kind=ip_i4_p), parameter, public :: LB_PART = 8  ! partition declaration
   integer(kind=ip_i4_p), parameter, public :: LB_ENDF = 9  ! end of definition phase 
   ! Put here the maximum of initialisation related events
   integer(kind=ip_i4_p), parameter         :: LB_NB_INIT_TIMING = 2

   integer(kind=ip_i4_p), parameter, public :: LB_TERM = 10 ! termination phase

   integer(kind=ip_i4_p), parameter, public :: LB_UNDF = 0  ! undefined kind of event



!  These 3 arrays store information related to the coupling events associated to 
!  a component : event description arrays

   integer(kind=ip_i4_p)  , pointer :: local_table_lb(:)          ! ID of the couplig field/event
   integer(kind=ip_i4_p)  , pointer :: local_coupler_lb(:)        ! ID of the coupler
   integer(kind=ip_i4_p)  , pointer :: local_counterpart_lb(:)    ! ID of the counterpart model
   integer(kind=ip_i4_p)  , pointer :: local_tsid_lb(:)           ! ID of the timestep for each coupling event


   real(ip_double_p) :: dl_simu_wtimer(2)

   integer(kind=ip_i4_p) :: ievent, ievent_old 
   logical ::               ldo_lb_analysis = .TRUE.

   contains

! --------------------------------------------------------------------------------

!> Initializes the timer methods, called once in an application

      subroutine oasis_lb_init 

         implicit none

         character(len=*),parameter :: subname = '(oasis_timer_init)'
! 
!        First of all, take measurement of simulation start
!
         dl_simu_wtimer(1) = MPI_WTIME()

      end subroutine oasis_lb_init

! --------------------------------------------------------------------------------

!> Allocate event related arrays
!
!  Called by oasis_coupler_setup if coupled component, by oasis_enddef if not

      subroutine oasis_lb_allocate (nb_event)

         implicit none

         integer(kind=ip_i4_p)  ,intent(in) :: nb_event  ! number of exchanged fields

         integer(kind=ip_i4_p) :: n, ierror

         character(len=*),parameter :: subname = '(oasis_lb_allocate)'



         ! Add 2 events for partionning and end of definition phases

         ALLOCATE(local_coupler_lb(nb_event+LB_NB_INIT_TIMING+1), stat=ierror)
         IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocate '
         ALLOCATE(local_counterpart_lb(nb_event+LB_NB_INIT_TIMING+1), stat=ierror)
         IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocate '
         ALLOCATE(local_table_lb(nb_event+LB_NB_INIT_TIMING+1), stat=ierror)
         IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocate '
         ALLOCATE(local_tsid_lb(nb_event+LB_NB_INIT_TIMING+1), stat=ierror)
         IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocate '

         ! Initialise arrays with undef value
         ! They keep this value for events not related to exchanges (init)
         DO n = 1, LB_NB_INIT_TIMING + 1

            local_coupler_lb(1:LB_NB_INIT_TIMING+1) = LB_UNDF
            local_counterpart_lb(1:LB_NB_INIT_TIMING+1) = LB_UNDF
            local_table_lb(1:LB_NB_INIT_TIMING+1) = LB_UNDF
            local_tsid_lb(1:LB_NB_INIT_TIMING+1) = LB_UNDF

         ENDDO

         ! The event number is initialised to the number of initialisation related events
         ! and doubled to store before and after event measurement
         ievent = ( LB_NB_INIT_TIMING + 1 ) * 2

         ! In case of uncoupled component, LB_PART event is filled with dummy
         ! measures
         IF ( nb_event == 0 ) THEN
            IF (OASIS_Debug >= 2) &
               write(nulprt,*) subname,' coupled component including uncoupled processes only'
            ! launch fake partitionning measurement'
            CALL oasis_lb_measure(-1, LB_PART)
            CALL oasis_lb_measure(-1, LB_PART)
         ENDIF
         

      end subroutine oasis_lb_allocate

! --------------------------------------------------------------------------------

!> Define the size of the timer arrays
!
!  Called by oasis_coupler_setup if coupled component
!  Called for each coupling field
!

      subroutine oasis_lb_define (icpl, &
                                  ikind_id, &
                                  icpl_id, &
                                  imodelctn_id, &
                                  itsid_id, &
                                  icpl_nb, &
                                  lmap, &
                                  lout, &
                                  lrst, &
                                  ltrn)

         implicit none

         character(len=*),parameter :: subname = '(oasis_lb_define)'

         integer(kind=ip_i4_p)  ,intent(in) :: icpl         ! coupler index 
         integer(kind=ip_i4_p)  ,intent(in) :: ikind_id     ! kind of main operation
         integer(kind=ip_i4_p)  ,intent(in) :: icpl_id      ! coupler id 
         integer(kind=ip_i4_p)  ,intent(in) :: imodelctn_id ! model counterpart id
         integer(kind=ip_i4_p)  ,intent(in) :: itsid_id     ! timestep id
         integer(kind=ip_i4_p)  ,intent(in) :: icpl_nb      ! nb of cpl time steps
         logical ,intent(in), optional :: lmap      ! additional mapping
         logical ,intent(in), optional :: lout      ! additional output
         logical ,intent(in), optional :: lrst      ! additional restart
         logical ,intent(in), optional :: ltrn      ! additional partial restart


         ! fill event description arrays after initialisation index (4)
         integer(kind=ip_i4_p), SAVE :: ne = 4      

         ! By default, coupling events do not come with interpolation, restarts writing
         ! or netCDF output
         logical :: llmap, llout, llrst, lltrn
         llmap = .FALSE. ; llout = .FALSE. ; llrst = .FALSE. ; lltrn = .FALSE.

         if (present(lmap)) llmap = lmap
         if (present(lout)) llout = lout
         if (present(lrst)) llrst = lrst
         if (present(ltrn)) lltrn = ltrn


         ! Fill coupling event description arrays as defined in oasis_coupler_setup
         local_table_lb(ne) = icpl
         local_coupler_lb(ne) = icpl_id
         local_counterpart_lb(ne) = imodelctn_id
         local_tsid_lb(ne) = itsid_id

         ! The event number is incremented by the number of active coupling
         ! exchanges related to the coupling field
         ievent = ievent + icpl_nb*2

         ! The event number is incremented by the number of active coupling
         ! exchanges another time if interpolation
         IF ( llmap ) &
            ievent = ievent + icpl_nb*2

         ! The event number is incremented by the number of active coupling
         ! exchanges another time if netCDF output in link with EXPOUT namcouple option
         IF ( llout .AND. ikind_id /= LB_OUT ) &
            ievent = ievent + icpl_nb*2

         ! The event number is incremented by two if restart writing
         IF ( llrst ) THEN
            ievent = ievent + 2
            ! Two additional events if restart and EXPOUT
            IF ( llout ) &
               ievent = ievent + 2
         ENDIF


         ! Since there is no way to count the number
         ! of partial restart calls before the end of the run, we prefer to
         ! limit our measurement to the first one 
         IF ( lltrn ) &
            ievent = ievent + 2

         ne = ne + 1

         IF (OASIS_Debug >= 10) &
            write(nulprt,*) subname,' New total of timeline events : ', ievent

      end subroutine oasis_lb_define

!> Do measurement
!
! This routine is called before and after each coupling event,
! mainly in oasis_advance_run (coupling exchange events),
! but also in oasis_enddef, oasis_def_partition and oasis_terminate (via oasis_lb_print )

      subroutine oasis_lb_measure(icoupler, ikind, tsid)

         implicit none
         character(len=*),parameter :: subname = '(oasis_lb_measure)'

         integer(kind=ip_i4_p)  ,intent(in) :: icoupler   ! coupler ID
         integer(kind=ip_i4_p)  ,intent(in) :: ikind      ! kind of event

         integer(kind=ip_i4_p)  ,intent(in) ,optional :: tsid    ! timestep ID
         
         integer(kind=ip_i4_p) :: eventid, ierror
         integer(kind=ip_i4_p), SAVE :: event_index = 1   ! Timeline array index

         !Timestep id
         integer(kind=ip_i4_p) :: itsid

         ! Special array to temporarily store timings of initialisation events
         real(ip_single_p), SAVE :: r_init_timers(LB_NB_INIT_TIMING*2)

         real(ip_single_p) :: dmeas  ! measurement

         ! kind of timing : TRUE = before event, FALSE = after event
         logical, SAVE :: tic_tac = .TRUE.

         ! Logical made necessary to identify and limit partial restart writing
         ! event measurement
         logical, SAVE :: over_partial_restart = .FALSE.

         ! If itsid is not provided, put the default value
         IF (present(tsid)) then
            itsid = tsid
         else
            itsid = ispval
         endif

         ! Termination of LB_ENDF can be called twice (restart case)
         ! Skip the second one
         IF ( ikind == LB_ENDF .AND. event_index >= ( LB_NB_INIT_TIMING*2 + 1 )) &
           return

         ! Special recording for init operations
         IF ( ikind == LB_ENDF .OR. ikind == LB_PART ) THEN
            r_init_timers(event_index) = MPI_WTIME() - dl_simu_wtimer(1)
            event_index = event_index + 1
            tic_tac = .NOT. tic_tac
            return
         ENDIF

         ! Special treatment during the first event after intialisation events
         IF ( event_index == ( LB_NB_INIT_TIMING*2 + 1 ) ) THEN

            ! Allocate the array to store the timeline local to the MPI process
            ALLOCATE(local_timeline(ievent), stat=ierror)
            IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocate '

            ! ensure zero values if irregulat event number across processes
            local_timeline(:)%kind = LB_UNDF ; local_timeline(:)%field = LB_UNDF
            local_timeline(:)%cntp = LB_UNDF ; local_timeline(:)%timer = 0.
            local_timeline(:)%tsid = ispval

            ! Fill the timeline array with initialisation measurements
            local_timeline(1:4)%timer = r_init_timers(1:4)
            local_timeline(1:2)%kind = LB_PART
            local_timeline(3:4)%kind = LB_ENDF
            local_timeline(1:4)%field = LB_UNDF
            local_timeline(1:4)%cntp = LB_UNDF
            local_timeline(1:4)%tsid = ispval

         ENDIF

         IF ( event_index > ievent ) THEN
            write(nulprt,*) subname,'Warning: Event after limit '
            call flush(nulprt)
            return
         ENDIF

         ! Detect additional partial restart operations
         IF ( ikind == LB_TRN .AND. over_partial_restart ) return

         ! Warn that partial restart writing measurement is over
         IF ( ikind == LB_TRN .AND. .NOT. tic_tac ) over_partial_restart = .TRUE.

         ! Take measurement
         dmeas = MPI_WTIME() - dl_simu_wtimer(1)

         ! Find the event ID in event description tables related to the coupler
         ! ID of the event
         IF ( ikind == LB_TERM ) THEN
            eventid = 3
         ELSE
            eventid = 1
            DO WHILE ( local_table_lb(eventid) /= icoupler )
               eventid = eventid + 1
            ENDDO
         ENDIF

         IF (OASIS_Debug >= 10) THEN
            write(nulprt,*) subname,' event index, coupler, kind, timestep_id ', &
                                      event_index, icoupler, ikind, itsid
            call flush(nulprt)
         ENDIF

         ! Fill the timeline array
         !   - with timings
         local_timeline(event_index)%timer = dmeas
         !   - with the kind of event as specified during the routine call
         local_timeline(event_index)%kind = ikind
         !   - with the field ID associated to the event ID
         local_timeline(event_index)%field = local_coupler_lb(eventid)
         !   - with the counterpart model ID associated to the event ID
         local_timeline(event_index)%cntp = local_counterpart_lb(eventid)
         !   - with the timestep ID associated to the event ID
         local_timeline(event_index)%tsid = itsid

         ! Increment timeline array index
         event_index = event_index + 1

         ! Change kind of timing 
         tic_tac = .NOT. tic_tac

      end subroutine oasis_lb_measure

!> Print timers
!
! Called once at oasis_termination phase
!

      subroutine oasis_lb_print(component_name, simutime)

         implicit none

         character(len=*)       ,intent(in) :: component_name
         integer(kind=ip_i4_p)  ,intent(in) :: simutime       ! simulated time

         character(len=*),parameter :: subname = '(oasis_lb_print)'
         character(ic_med)          :: filename

         logical :: lopened, l_first_event, l_second_event

         integer(ip_i4_p),parameter :: diag_nb=100
         integer(ip_i4_p) :: n, ierror, nf, nk, ne, np

         integer(ip_i4_p) :: ncid
         integer(ip_i4_p) :: ncvarid(6), ncdimid(2)

         integer(ip_i4_p) :: lb_tag = 4000
         integer(ip_i4_p) :: max_field_nb
         integer(ip_i4_p) :: lastevent

         integer(ip_i4_p), allocatable   :: pair_field_cntp(:)
         integer(ip_i4_p), allocatable   :: ig_globSize(:)
         integer(ip_i4_p), allocatable   :: write_timeline(:)

         real(kind=ip_double_p) :: null_r, dlb_time
         real(kind=ip_double_p) :: soonest_start, latest_stop, clock_spread

         real(kind=ip_single_p) :: timer_max
         real(kind=ip_single_p) :: bk_ev_min, bk_ev_max
         real(kind=ip_single_p) :: wtg_time, cmp_time
         real(kind=ip_single_p) :: lb_diag_buff(diag_nb)
         real(kind=ip_single_p) :: bk_ev_tmp(2)

         real(kind=ip_double_p), allocatable :: dg_simu_wtimer(:)
         real(kind=ip_double_p), allocatable :: g_lb_diag_buff(:,:)

         real(kind=ip_single_p), allocatable :: bk_avg(:)
         real(kind=ip_single_p), allocatable :: bk_minval(:), bk_maxval(:)
         real(kind=ip_single_p), pointer     :: tl_global_timer(:,:)
         real(kind=ip_single_p), allocatable :: tl_sum_kind (:,:,:) 

         logical :: lcontinue

         IF ( mpi_comm_global == MPI_COMM_NULL ) return
!
! 
         ! Make measurement of the time spend waiting the beginning of the
         ! LB analysis phase + the first step of this analysis.
         ! The analysis is synchronised with the oasis_mpi_barrier statement 
         CALL oasis_lb_measure(-1,LB_TERM)

         call oasis_mpi_barrier(mpi_comm_global)

         ! Take performance measurement of the load balancing analysis itself
         ! and exclude this time from the total simulation time
         !
         ! Done by all components, including uncoupled
         !

         dlb_time = MPI_WTIME()

         dl_simu_wtimer(2) = dlb_time

         ! Check if the analysis is possible
         call MPI_AllReduce(ldo_lb_analysis, lcontinue, 1, MPI_LOGICAL, MPI_LAND, &
                            mpi_comm_global, ierror)

         IF (.NOT. lcontinue ) THEN
            WRITE(nulprt,*) subname, ' WARNING: Load balancing analysis impossible '
            return
         ENDIF

         !  ----------
         !  FIRST STEP
         !  ----------
         ! Evaluate total simulation time
         ! for the coupled system and all components separately

         !
         IF (mpi_rank_global /= 0) THEN

            CALL MPI_Gather( dl_simu_wtimer, 2, MPI_DOUBLE, null_r, 0, MPI_DOUBLE, &
                             0, mpi_comm_global, ierror)

         ELSE
          
            ALLOCATE(dg_simu_wtimer(2*mpi_size_global), stat=ierror)
            IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocating total timer'

            dg_simu_wtimer = 0._ip_double_p

            ! All processes send the total simulation time to the master
            CALL MPI_Gather( dl_simu_wtimer, 2, MPI_DOUBLE, dg_simu_wtimer, 2, MPI_DOUBLE, &
                             0, mpi_comm_global, ierror)

            ! The LB analysis is output on a text file
            INQUIRE(unit=nulet, opened=lopened)
            IF (  lopened ) CLOSE(nulet)
            OPEN(nulet, file='load_balancing_info.txt', status='REPLACE')

            !
            !soonest_start = MINVAL(dg_simu_wtimer(1:mpi_size_global*2-1:2))
            !latest_stop   = MAXVAL(dg_simu_wtimer(2:mpi_size_global*2:2))
            soonest_start = MINVAL(dg_simu_wtimer, mask = dg_simu_wtimer > 0._ip_double_p )
            latest_stop   = MAXVAL(dg_simu_wtimer, mask = dg_simu_wtimer > 0._ip_double_p )

            !
            ! Check clock synchronisation
            !
            clock_spread = latest_stop - MINVAL(dg_simu_wtimer(2:mpi_size_global*2:2))

            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' ------------------------------'
            WRITE(nulet,*) ' '
            WRITE(nulet,'(a37,f8.3)') ' Coupled model simulation time (s): ', latest_stop-soonest_start
            WRITE(nulet,*) '    (coupled components only)  '
            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' ------------------------------'
            WRITE(nulet,*) ' '
            WRITE(nulet,'(a16,f10.3)') ' Speed (SYPD) : ', DBLE(simutime) * 365. / ( latest_stop-soonest_start )
            WRITE(nulet,'(a16,f8.3)') ' Cost (CHPSY) : ', DBLE(mpi_size_world) * 24 * ( latest_stop-soonest_start ) / ( DBLE(simutime) * 365. )
            WRITE(nulet,*) ' '


            ! The same anaysis is given per component
            n  = 1

            DO nf = 1, prism_amodels

               soonest_start = latest_stop
               latest_stop   = 0.
               ne = 1

               DO np = 1, mpi_size_world
                  IF ( TRIM(compnmlist(np)) == TRIM(prism_modnam(nf)) ) THEN
                     soonest_start = MIN(dg_simu_wtimer(n),soonest_start)
                     latest_stop = MAX(dg_simu_wtimer(n+1),latest_stop)
                     n = n + 2
                     ne = ne + 1
                  ENDIF
               ENDDO

               WRITE(nulet,'(A7,A10,A19,F8.3)') ' Model ', TRIM(prism_modnam(nf)),&
                      ' simulation time : ', latest_stop-soonest_start
               WRITE(nulet,'(A32,F8.3)') '                  cost (CHPSY): ', &
                      DBLE(ne) * 24 * ( latest_stop-soonest_start ) / ( DBLE(simutime) * 365. )

            ENDDO

            DEALLOCATE(dg_simu_wtimer)

         ENDIF





         !  ----------
         !  SECOND STEP
         !  ----------
         !  Gather timers information and produce one timeline per component 




         ! "before" termination phase measurement
         if (ET_debug) CALL oasis_lb_measure(-1,LB_TERM)

         DEALLOCATE( local_table_lb, local_coupler_lb, local_counterpart_lb, local_tsid_lb )

         IF (OASIS_Debug >= 10) THEN
            write(nulprt,*) subname,' gather size (events) ', ievent
            write(nulprt,*) subname,' communicator size ', mpi_size_local
            call flush(nulprt)
         ENDIF

         IF ( mpi_rank_local /= 0 ) THEN

            CALL MPI_Gather(ievent, 1, MPI_INT, n, 0, MPI_INT, &
                             0, mpi_comm_local, ierror)

            CALL MPI_Gather( local_timeline(:)%timer, ievent, MPI_REAL, &
                             null_r, 0, MPI_REAL, 0, mpi_comm_local, ierror)

         ELSE
 
            ! to avoid unexplained error with PGI compiler
            ALLOCATE(write_timeline(ievent/2), stat=ierror)
            IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocating tmp array '

            ALLOCATE(ig_globSize(mpi_size_local), stat=ierror)
            IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocating table size '

            ! Every process of every component is sending the size of its
            ! timeline to the component master process
            CALL MPI_Gather(ievent, 1, MPI_INT, ig_globSize, 1, MPI_INT, &
                             0, mpi_comm_local, ierror)

            IF (OASIS_Debug >= 10) THEN
               write(nulprt,*) subname,' check local size of timeline ', ig_globSize
               call flush(nulprt)
            ENDIF

            ! Check that there is no block.
            ! The current version of our LB analysis does not accept incoherent 
            ! partitionning in the same component
            DO n = 1, mpi_rank_local
               IF ( ig_globSize(n) /= ievent ) THEN
                 write(nulprt,*) subname, ' Non identical number of events across processes of the same component. We stop '
                 call oasis_abort(file=__FILE__,line=__LINE__)
               ENDIF
            ENDDO

            DEALLOCATE(ig_globSize)

            ! Allocate the timeline array that gathers all process timelines of
            ! the same component.
            ! This array is the memory bound of the LB analysis : 
            !  size = DOUBLE * nb_events * nb_process_per_component
            WRITE(nulprt,'(a16,a42,f13.3)') subname,' Main allocation for timeline. Size (KB): ', &
                                         DBLE(ievent*mpi_size_local*8)/1000.
                               
            call flush(nulprt)


            ALLOCATE ( tl_global_timer(ievent,mpi_size_local), stat=ierror )
            IF (ierror /= 0) then
               WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                               mpi_rank_local,' ERROR allocating component timeline '
               call oasis_abort(file=__FILE__,line=__LINE__)
            ENDIF

            ! Every process of every component is sending its timeline to the
            ! component master process
            CALL MPI_Gather( local_timeline(:)%timer, ievent, MPI_REAL, &
                             tl_global_timer, ievent, MPI_REAL, &
                             0, mpi_comm_local, ierror)


            ! Creation of the netCDF file to save timelines

            write(filename,'(a9,a,a3)') 'timeline_',TRIM(component_name), '.nc'
            ierror = nf90_create(trim(filename),NF90_CLOBBER,ncid)
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' open netcdf file ', ierror; call flush(nulprt)
            ENDIF

            ierror = nf90_put_att(ncid, NF90_GLOBAL, 'source', &
                                  "OASIS coupler instrumented for load balancing analysis")
            ierror = nf90_put_att(ncid, NF90_GLOBAL, 'title', &
                                  "OASIS event (nx) timeline on every MPI process (ny) ")
            ierror = nf90_put_att(ncid, NF90_GLOBAL, 'component_id', compid )

            IF (OASIS_Debug >= 10) THEN
               WRITE(nulprt,*) subname,' global timeline (max 100,100)', &
                               tl_global_timer(1:MIN(100,ievent),1:MIN(100,mpi_size_local))
               call flush(nulprt)
            ENDIF

            ! Remove from the netcdf file non attributed events
            IF ( ANY ( local_timeline(:)%kind == LB_TERM ) ) THEN
               lastevent = 1
               DO WHILE ( local_timeline(lastevent)%kind /= LB_TERM )
                  lastevent = lastevent + 1
               ENDDO
               ievent = MIN ( ievent, lastevent+1 )
            ENDIF

            IF (OASIS_Debug >= 10) &
               WRITE(nulprt,*) subname,' Final timeline length ', ievent

            ierror = nf90_def_dim(ncid,'nx',ievent/2,ncdimid(1))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf dim ', ierror ; call flush(nulprt)
            ENDIF

            ierror = nf90_def_dim(ncid,'ny',mpi_size_local,ncdimid(2))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf dim ', ierror ; call flush(nulprt)
            ENDIF

            ierror = nf90_def_var(ncid,'timer_strt',NF90_FLOAT,ncdimid(:),ncvarid(1))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf var ', ierror ; call flush(nulprt)
            ENDIF
            ierror = nf90_put_att(ncid, ncvarid(1), 'long_name', "Start of OASIS event")
            ierror = nf90_put_att(ncid, ncvarid(1), 'units', "seconds since OASIS initialisation")

            ierror = nf90_def_var(ncid,'timer_stop',NF90_FLOAT,ncdimid(:),ncvarid(2))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf var ', ierror ; call flush(nulprt)
            ENDIF
            ierror = nf90_put_att(ncid, ncvarid(2), 'long_name', "End of OASIS event")
            ierror = nf90_put_att(ncid, ncvarid(2), 'units', "seconds since OASIS initialisation")

            ierror = nf90_def_var(ncid,'kind',NF90_INT,ncdimid(1),ncvarid(3))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf var ', ierror ; call flush(nulprt)
            ENDIF
            ierror = nf90_put_att(ncid, ncvarid(3), 'long_name', "Kind of OASIS event")
            ierror = nf90_put_att(ncid, ncvarid(3), 'standard_name', "Kind")
            ierror = nf90_put_att(ncid, ncvarid(3), 'flag_values', &
                                  "0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10")
            ierror = nf90_put_att(ncid, ncvarid(3), 'flag_meanings', &
                                  "UNDF PUT GET MAP OUT READ RST TRN PART ENDF TERM")
            ierror = nf90_put_att(ncid, ncvarid(3), 'comment', &
                                  "undefined send receive map file_output file_input restart_writing partial_restart_writing partition_def end_def terminate")


            ierror = nf90_def_var(ncid,'field',NF90_INT,ncdimid(1),ncvarid(4))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf var ', ierror ; call flush(nulprt)
            ENDIF
            ierror = nf90_put_att(ncid, ncvarid(4), 'long_name', "OASIS field name ID")
            ierror = nf90_put_att(ncid, ncvarid(4), 'standard_name', "Field")
            ierror = nf90_put_att(ncid, ncvarid(4), 'comment', "Sequence follows namcouple order ")

            ierror = nf90_def_var(ncid,'component',NF90_INT,ncdimid(1),ncvarid(5))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf var ', ierror ; call flush(nulprt)
            ENDIF
            ierror = nf90_put_att(ncid, ncvarid(5), 'long_name', "Counterpart coupled component ID")
            ierror = nf90_put_att(ncid, ncvarid(5), 'standard_name', "Component")
            ierror = nf90_put_att(ncid, ncvarid(5), 'comment', "Sequence follows component MPI rank in global communicator ")

            ierror = nf90_def_var(ncid,'tsid',NF90_INT,ncdimid(1),ncvarid(6))
            ierror = nf90_def_var_fill(ncid, ncvarid(6), 0, ispval)
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' define netcdf var ', ierror ; call flush(nulprt)
            ENDIF
            ierror = nf90_put_att(ncid, ncvarid(6), 'long_name', "Timestep ID (simulated time of compoenent calling Oasis) at this event ")
            ierror = nf90_put_att(ncid, ncvarid(6), 'standard_name', "tsid")
            ierror = nf90_put_att(ncid, ncvarid(6), 'units', "simulated time (seconds)")

            ierror = nf90_enddef(ncid)
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' close netcdf definition ', ierror ; call flush(nulprt)
            ENDIF

            ! before/after event timings are saved in separate variables
            ierror = nf90_put_var(ncid,ncvarid(1),&
                        tl_global_timer(1:ievent-1:2,1:mpi_size_local))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' put netcdf var timeline', ierror ; call flush(nulprt)
            ENDIF

            ierror = nf90_put_var(ncid,ncvarid(2),&
                        tl_global_timer(2:ievent:2,1:mpi_size_local))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' put netcdf var timeline', ierror ; call flush(nulprt)
            ENDIF


            IF (OASIS_Debug >= 10) THEN
               write(nulprt,*) subname, 'check kind  values', local_timeline(:)%kind
               write(nulprt,*) subname, 'check field values', local_timeline(:)%field
               write(nulprt,*) subname, 'check counterpart model  values', local_timeline(:)%cntp
               write(nulprt,*) subname, 'check timestep ID values', local_timeline(:)%tsid
               call flush(nulprt)
            ENDIF

            ! only "before" event characteristics are saved ("after" have the same)
            write_timeline(1:ievent/2) = local_timeline(1:ievent-1:2)%kind
            ierror = nf90_put_var(ncid,ncvarid(3),write_timeline(1:ievent/2))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' put netcdf var kind', ierror ; call flush(nulprt)
            ENDIF

            write_timeline(1:ievent/2) = local_timeline(1:ievent-1:2)%field
            ierror = nf90_put_var(ncid,ncvarid(4),write_timeline(1:ievent/2))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' put netcdf var field', ierror ; call flush(nulprt)
            ENDIF

            write_timeline(1:ievent/2) = local_timeline(1:ievent-1:2)%cntp
            ierror = nf90_put_var(ncid,ncvarid(5),write_timeline(1:ievent/2))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' put netcdf var counterpart model', ierror ; call flush(nulprt)
            ENDIF

            write_timeline(1:ievent/2) = local_timeline(1:ievent-1:2)%tsid
            ierror = nf90_put_var(ncid,ncvarid(6),write_timeline(1:ievent/2))
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' put netcdf var tsid', ierror ; call flush(nulprt)
            ENDIF

            DEALLOCATE(write_timeline)

            ierror = nf90_close(ncid)
            IF (OASIS_Debug >= 2) THEN
               write(nulprt,*) subname,' close netcdf file ', ierror ; call flush(nulprt)
            ENDIF





         !  ----------
         !  THIRD STEP
         !  ----------
         !  Produce summary numbers per component



            max_field_nb = MAXVAL(local_timeline(:)%field)

            ! if all component processes are coupled but dont exchange fields
            IF ( max_field_nb <= 0 ) THEN
               wtg_time = 0. ; cmp_time = 0.
               bk_ev_max = 1. ;  bk_ev_min = 0.
               ALLOCATE( tl_sum_kind (1, LB_MAX, 3) , stat=ierror)
               IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                        mpi_rank_local,' WARNING allocating working buffer '
               tl_sum_kind (1, LB_MAX, 3) = 0.

            ! if not, gather information
            ELSE
               
               ievent_old=SIZE(tl_global_timer, 1)  ! define new integer with size of tl_global_timer
               write(nulprt,*) subname,' old gather size (ievent) ', ievent_old
               write(nulprt,*) subname,' new gather size (ievent) ', ievent
               call flush(nulprt)


               ALLOCATE(bk_minval(ievent_old), stat=ierror)
               IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                        mpi_rank_local,' WARNING allocating working buffer '
               ALLOCATE(bk_maxval(ievent_old), stat=ierror)
               IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocating working buffer '
               ALLOCATE(bk_avg(ievent_old), stat=ierror)
               IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                        mpi_rank_local,' WARNING allocating working buffer '
               ! last measurement, useful to initialise minimum values
               timer_max = MAXVAL(tl_global_timer) 
               PRINT*,"OASIS SIZE(bk_avg)",SIZE(bk_avg)
               PRINT*,"OASIS SIZE(tl_global_timer, 1)",SIZE(tl_global_timer,1)
               ! minimum/maximum and average values across processes, for each
               ! event
               bk_minval(:) = MINVAL ( tl_global_timer(:,:), dim=2)
               bk_maxval(:) = MAXVAL ( tl_global_timer(:,:), dim=2)
               bk_avg(:)    = SUM ( tl_global_timer(:,:), dim=2) / REAL(mpi_size_local,4)

               DEALLOCATE(tl_global_timer)

               ! Identify pair of field/counterpart model 
               IF ( max_field_nb > 0 ) THEN
                  ALLOCATE( pair_field_cntp (max_field_nb), stat=ierror ) 
                  IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                        mpi_rank_local,' WARNING allocating working buffer '
                  pair_field_cntp (:) = LB_UNDF 
                  do ne = 1, ievent
                    IF ( local_timeline(ne)%kind == LB_GET ) &
                       pair_field_cntp(local_timeline(ne)%field) = local_timeline(ne)%cntp
                  enddo
               ENDIF

               ALLOCATE( tl_sum_kind (max_field_nb, LB_MAX, 3), stat=ierror ) 
               IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocating working buffer '
               tl_sum_kind(:,:,:) = 0.

               bk_ev_min = timer_max
               bk_ev_max = 0.

               ! Loops on coupling fields and kind of events
               do nf = 1, max_field_nb; do nk = 1, LB_MAX

                  ! We exclude first and last EVENT per field and per kind 
                  !            (not first and last coupling time step, as in
                  !            LUCIA)
                 
                  l_first_event = .TRUE. 
                  l_second_event = .FALSE. 

                  ! Loop on "before" events
                  do ne = 1, ievent-1, 2

                     ! For a given field and kind of event
                     IF ( local_timeline(ne)%field == nf .AND. &
                          local_timeline(ne)%kind  == nk ) THEN

                        ! max extension of event beginning (jitter)
                        tl_sum_kind(nf,nk,1) = tl_sum_kind(nf,nk,1) + &
                                               ( bk_maxval(ne) - bk_minval(ne) )
                        ! max/max extension (for waiting time mainly)
                        tl_sum_kind(nf,nk,2) = tl_sum_kind(nf,nk,2) + &
                                               ( bk_maxval(ne+1) - bk_maxval(ne) )
                        ! average
                        tl_sum_kind(nf,nk,3) = tl_sum_kind(nf,nk,3) + &
                                               ( bk_avg(ne+1) - bk_avg(ne) )

                        ! evaluate overall bounds of the measurement for the
                        ! component (bk_ev_min,bk_ev_max)
                        IF ( nk /= LB_RST .AND. nk /= LB_TRN ) THEN
                           IF ( l_first_event ) THEN
                              l_first_event = .FALSE.
                              l_second_event = .TRUE.
                              bk_ev_tmp(2) = bk_maxval(ne+1)
                           ELSEIF ( l_second_event ) THEN
                              bk_ev_min = MIN( bk_ev_min, bk_minval(ne) )
                              l_second_event = .FALSE.
                              bk_ev_tmp(2) = bk_ev_tmp(1)
                           ELSE 
                              bk_ev_tmp(2) = bk_ev_tmp(1)
                           ENDIF
                           bk_ev_tmp(1) = bk_maxval(ne+1)
                        ENDIF

                     ENDIF

                  enddo

                  bk_ev_max = MAX( bk_ev_max, bk_ev_tmp(2) )

               enddo; enddo

               ! computation of the waiting time
               wtg_time = SUM(tl_sum_kind(:,LB_PUT:LB_GET,2))

               ! computation of the computing time
               cmp_time = bk_ev_max - bk_ev_min - wtg_time

               DEALLOCATE(bk_avg)
               DEALLOCATE(bk_minval)
               DEALLOCATE(bk_maxval)

            ENDIF

         ENDIF

         DEALLOCATE(local_timeline)




         !  ----------
         !  FOURTH STEP
         !  ----------
         !  Produce global summary numbers for the whole coupled system




         IF ( mpi_rank_local == 0 ) THEN


            lb_diag_buff(:) = 0.

            ! Store load balancing main information: computation vs waiting time
            
            lb_diag_buff(1) = cmp_time 
            lb_diag_buff(2) = wtg_time 

            ! Total jitter
            lb_diag_buff(3) = SUM(tl_sum_kind(:,LB_PUT:LB_GET,1))


            ! Partial coupling cost (%) 
            lb_diag_buff(4) = 100.*wtg_time / (bk_ev_max - bk_ev_min)

            ! Partial coupling cost including OASIS operations (%) 
            lb_diag_buff(5) = 100.* ( wtg_time + SUM(tl_sum_kind(:,LB_MAP:LB_TRN,3)) ) / (bk_ev_max - bk_ev_min)

            ! Total mapping/interpolation 
            lb_diag_buff(6) = SUM(tl_sum_kind(:,LB_MAP,3))

            ! with spread 
            lb_diag_buff(7) = SUM(tl_sum_kind(:,LB_MAP,1))

            ! Total Netcdf output (OUTPUT+EXPOUT+restart)
            lb_diag_buff(8) = SUM(tl_sum_kind(:,LB_OUT:LB_TRN,3))

            ! with spread : 
            lb_diag_buff(9) = SUM(tl_sum_kind(:,LB_OUT:LB_TRN,1))

            ! including restart 
            lb_diag_buff(10) = SUM(tl_sum_kind(:,LB_RST:LB_TRN,3))

            ! with spread : 
            lb_diag_buff(11) = SUM(tl_sum_kind(:,LB_RST:LB_TRN,1))

            ! specific waiting times (oasis_get only)
            do n = 1, prism_amodels
               do nf = 1, max_field_nb
                  IF ( pair_field_cntp(nf) == n ) &
                     lb_diag_buff(11+n) = lb_diag_buff(11+n) + tl_sum_kind(nf,LB_GET,2)
               enddo
            enddo

            IF (OASIS_Debug >= 10) THEN
               DO nf = 1, max_field_nb; DO nk = 1, LB_MAX
                  IF ( SUM(tl_sum_kind(nf,nk,:)) /= 0. ) THEN
                     write(nulprt,*) subname,' valid field/kind results ', nf, nk 
                     write(nulprt,*) subname,' :  ', tl_sum_kind(nf,nk,:)
                     call flush(nulprt)
                  ENDIF
               ENDDO; ENDDO
            ENDIF

            IF ( mpi_rank_global == 0 ) THEN

               allocate ( g_lb_diag_buff ( diag_nb, prism_amodels), stat=ierror ) 
               IF (ierror /= 0) WRITE(nulprt,*) subname,' model :',compid,' proc :',&
                                     mpi_rank_local,' WARNING allocating diagnostic buffer '

               g_lb_diag_buff(:,1) = DBLE(lb_diag_buff(:))

            ELSE

               ! Send information to master root
               call oasis_mpi_send(DBLE(lb_diag_buff),0,lb_tag,mpi_comm_global,'oasis_lb_print')
            ENDIF

            IF ( ALLOCATED(pair_field_cntp) ) DEALLOCATE(pair_field_cntp)
            DEALLOCATE(tl_sum_kind)

         ENDIF


         IF ( mpi_rank_global == 0 ) THEN


            ! Receive information from local roots
            DO n = 2, prism_amodels
               call oasis_mpi_recv(g_lb_diag_buff(:,n), mpi_root_global(n), lb_tag,&
                                   mpi_comm_global,'oasis_lb_print')
            END DO

            WRITE(nulet,*) ' ------------------------------'
            WRITE(nulet,*) ' '
            WRITE(nulet,*) '     Load balance analysis '
            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' ------------------------------'
            WRITE(nulet,*) ' '

            ! Print computation time, "waiting" time

            write(nulet,*) ' Model    /   Computing time  /  Waiting time  '
            WRITE(nulet,*) ' '

            DO n = 1, prism_amodels
               write(nulet,'(a10,a3,f8.3,a3,f8.3)') &
                              TRIM(prism_modnam(n)) , ' / ', &
                              g_lb_diag_buff(1,n), ' / ', &
                              g_lb_diag_buff(2,n)
            ENDDO

            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' ------------------------------'
            WRITE(nulet,*) ' '
            WRITE(nulet,*) '     Additional information '
            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' ------------------------------'

            DO n = 1, prism_amodels
               WRITE(nulet,*) ' '
               WRITE(nulet,*) ' ------------------------------'
               write(nulet,'(a4,a10)') '    ', TRIM(prism_modnam(n))
               WRITE(nulet,*) ' ------------------------------'
               WRITE(nulet,*) ' '
               write(nulet,*) ' Specific oasis_get time '
               write(nulet,*) ' (n/a if no oasis_get) '
               do ne = 1, prism_amodels
                  if ( g_lb_diag_buff(11+ne,n) > 0. ) THEN
                     write(nulet,'(a20,a10)') '         from model ', TRIM(prism_modnam(ne))
                     write(nulet,'(a11,f8.3)') '         : ', g_lb_diag_buff(11+ne,n)
                  endif
               enddo
               WRITE(nulet,*) ' '
               WRITE(nulet,*) ' -------------------'
               WRITE(nulet,*) ' '
               write(nulet,'(a16,f8.3)') ' Total jitter : ', g_lb_diag_buff(3,n)
               WRITE(nulet,*) ' '
               write(nulet,'(a29,f6.2)') ' Partial coupling cost (%) : ', g_lb_diag_buff(4,n)
               write(nulet,'(a56,f6.2)') ' Partial coupling cost including OASIS operations (%) : ', g_lb_diag_buff(5,n)
               WRITE(nulet,*) ' '
               WRITE(nulet,*) ' '
               WRITE(nulet,*) ' OASIS Operations : '
               WRITE(nulet,*) ' -------------------'
               write(nulet,'(a31,f8.3)') ' Total mapping/interpolation : ', g_lb_diag_buff(6,n)
               write(nulet,'(a19,f8.3)') '     with spread : ', g_lb_diag_buff(7,n)
               WRITE(nulet,*) ' '
               write(nulet,'(a46,f8.3)') ' Total Netcdf output (OUTPUT+EXPOUT+restart): ', g_lb_diag_buff(8,n)
               write(nulet,'(a19,f8.3)') '     with spread : ', g_lb_diag_buff(9,n)
               WRITE(nulet,*) ' '
               WRITE(nulet,'(a40,f8.3)') ' Total Netcdf output for restart  only: ', g_lb_diag_buff(10,n)
               write(nulet,'(a19,f8.3)') '     with spread : ', g_lb_diag_buff(11,n)
               WRITE(nulet,*) ' '

               call flush(nulet)

            ENDDO 

            WRITE(nulet,*) ' ------------------------------'
            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' Total time of this load balancing analysis: '
            WRITE(nulet,'(a9,f8.3)') '       : ', MPI_WTIME() - dlb_time
            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' ------------------------------'
            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' Clock spread after synchronise '
            WRITE(nulet,*) ' .i.e. node clocks synchronisation (s) : '
            WRITE(nulet,'(a9,f12.8)') '       : ', clock_spread
            WRITE(nulet,*) ' '
            WRITE(nulet,*) ' ------------------------------'

            CLOSE(nulet)

            IF ( mpi_rank_global == 0 ) DEALLOCATE(g_lb_diag_buff)

         ENDIF



      end subroutine oasis_lb_print

! --------------------------------------------------------------------------------

!>  stop measurement

      subroutine oasis_lb_stop 

         implicit none

         integer(ip_i4_p) :: ierror
         character(len=*),parameter :: subname = '(oasis_timer_stop)'
! 
         ldo_lb_analysis = .FALSE.

      end subroutine oasis_lb_stop

! --------------------------------------------------------------------------------
end module mod_oasis_load_balancing
