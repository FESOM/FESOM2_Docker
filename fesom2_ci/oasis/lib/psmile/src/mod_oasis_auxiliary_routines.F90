
!> Auxiliary OASIS user interfaces

MODULE mod_oasis_auxiliary_routines
!---------------------------------------------------------------------

    USE mod_oasis_kinds
    USE mod_oasis_data
    USE mod_oasis_parameters
    USE mod_oasis_coupler
    USE mod_oasis_timer
    USE mod_oasis_var
    USE mod_oasis_sys
    USE mod_oasis_io
    USE mod_oasis_mpi
    USE mct_mod

    implicit none
    private

    public oasis_get_localcomm

! kh 02.12.21
    public oasis_get_localcomm_all_groups

    public oasis_set_couplcomm
    public oasis_create_couplcomm
    public oasis_get_debug
    public oasis_set_debug
    public oasis_get_intercomm
    public oasis_get_intracomm
    public oasis_get_multi_intracomm
    public oasis_get_ncpl
    public oasis_put_inquire
    public oasis_get_freqs

#include "oasis_os.h"

    integer(kind=ip_i4_p)     istatus(MPI_STATUS_SIZE)

!---------------------------------------------------------------------
  CONTAINS
!---------------------------------------------------------------------

!> OASIS user query for the local MPI communicator

  SUBROUTINE oasis_get_localcomm(localcomm,kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(out)   :: localcomm  !< MPI communicator
    INTEGER (kind=ip_intwp_p),intent(inout),optional :: kinfo  !< return code
!   ---------------------------------------------------------
    character(len=*),parameter :: subname = '(oasis_get_localcomm)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    ! from prism_data
    localcomm = mpi_comm_local
    IF (OASIS_debug >= 2) THEN
        WRITE(nulprt,*) 'localcomm :',localcomm
        CALL oasis_FLUSH(nulprt)
    ENDIF

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_get_localcomm

! kh 02.12.21
!----------------------------------------------------------------------

!> OASIS user query for the local MPI communicator for all groups

  SUBROUTINE oasis_get_localcomm_all_groups(localcomm_all_groups,kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(out)   :: localcomm_all_groups  !< MPI communicator
    INTEGER (kind=ip_intwp_p),intent(inout),optional :: kinfo  !< return code
!   ---------------------------------------------------------
    character(len=*),parameter :: subname = '(oasis_get_localcomm_all_groups)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    ! from prism_data
    localcomm_all_groups = mpi_comm_local_all_groups
    IF (OASIS_debug >= 2) THEN
        WRITE(nulprt,*) 'localcomm_all_groups :',localcomm_all_groups
        CALL oasis_FLUSH(nulprt)
    ENDIF

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_get_localcomm_all_groups
!----------------------------------------------------------------------

!> OASIS user call to specify a local communicator

  SUBROUTINE oasis_set_couplcomm(localcomm,kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(in)   :: localcomm  !< MPI communicator
    INTEGER (kind=ip_intwp_p),intent(inout),optional :: kinfo  !< return code
!   ---------------------------------------------------------
    integer(kind=ip_intwp_p) :: ierr
    character(len=*),parameter :: subname = '(oasis_set_couplcomm)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    !------------------------
    !--- update mpi_comm_local from component
    !------------------------

    mpi_comm_local = localcomm

    !------------------------
    !--- and now update necessary info
    !------------------------

    mpi_size_local = -1
    mpi_rank_local = -1
    if (mpi_comm_local /= MPI_COMM_NULL) then
       CALL MPI_Comm_Size(mpi_comm_local,mpi_size_local,ierr)
       call oasis_mpi_chkerr(ierr,trim(subname)//' size')
       CALL MPI_Comm_Rank(mpi_comm_local,mpi_rank_local,ierr)
       call oasis_mpi_chkerr(ierr,trim(subname)//' rank')
       mpi_root_local = 0
    endif

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_set_couplcomm
!----------------------------------------------------------------------

!> OASIS user call to create a new communicator

  SUBROUTINE oasis_create_couplcomm(icpl,allcomm,cplcomm,kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(in)   :: icpl  !< coupling process flag 
    INTEGER (kind=ip_intwp_p),intent(in)   :: allcomm  !< input MPI communicator 
    INTEGER (kind=ip_intwp_p),intent(out)  :: cplcomm  !< reduced MPI communicator
    INTEGER (kind=ip_intwp_p),intent(inout),optional :: kinfo  !< return code
!   ---------------------------------------------------------
    integer(kind=ip_intwp_p) :: ierr
    character(len=*),parameter :: subname = '(oasis_create_couplcomm)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    !------------------------
    !--- generate cplcomm from allcomm and icpl
    !------------------------

    CALL MPI_COMM_Split(allcomm,icpl,1,cplcomm,ierr)
    call oasis_mpi_chkerr(ierr,trim(subname)//' split')

    !------------------------
    !--- update mpi_comm_local from component
    !------------------------

    call oasis_set_couplcomm(cplcomm)

    IF (OASIS_debug >= 2)  THEN
       WRITE (nulprt,*) 'New local coupling comm =',cplcomm
       CALL oasis_flush(nulprt)
    ENDIF

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_create_couplcomm
!----------------------------------------------------------------------

!> OASIS user interface to query debug level

  SUBROUTINE oasis_get_debug(debug,kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(out)   :: debug  !< debug level
    INTEGER (kind=ip_intwp_p),intent(inout),optional :: kinfo  !< return code
!   ---------------------------------------------------------
    character(len=*),parameter :: subname = '(oasis_get_debug)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    debug = OASIS_debug

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_get_debug
!----------------------------------------------------------------------

!> OASIS user interface to set debug level

  SUBROUTINE oasis_set_debug(debug,kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(in)   :: debug  !< debug level
    INTEGER (kind=ip_intwp_p),intent(inout),optional :: kinfo  !< return code
!   ---------------------------------------------------------
    character(len=*),parameter :: subname = '(oasis_set_debug)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    OASIS_debug = debug
    if (OASIS_debug >= 2) then
       write(nulprt,*) subname,' set OASIS_debug to ',OASIS_debug
       CALL oasis_flush(nulprt)
    endif

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_set_debug
!----------------------------------------------------------------------

!> OASIS user interface to establish an MPI intercomm communicator between two models

  SUBROUTINE oasis_get_intercomm(new_comm, cdnam, kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(out) :: new_comm  !< out MPI communicator
    CHARACTER(len=*),intent(in) :: cdnam               !< other model name to link with
    INTEGER (kind=ip_intwp_p),intent(out),optional :: kinfo  !< return code

    INTEGER (kind=ip_intwp_p) :: n, il, ierr, tag, i_me
    INTEGER (KIND=MPI_ADDRESS_KIND) :: imax_tag_mpi
    LOGICAL :: found, ferr
!   ---------------------------------------------------------
    character(len=*),parameter :: subname = '(oasis_get_intercomm)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    found = .false.
    do n = 1,prism_amodels
       if (trim(cdnam) == trim(prism_modnam(n))) then
          if (found) then
             write(nulprt,*) subname,estr,'found same model name twice: ',trim(prism_modnam(n))
             call oasis_abort(file=__FILE__,line=__LINE__)
          endif
          il = n
          found = .true.
       endif
       if (trim(compnm) == trim(prism_modnam(n))) then
          i_me = n
       endif
    enddo

    if (.not. found) then
       write(nulprt,*) subname,estr,'input model name not found'
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif

    IF (OASIS_debug >= 2) THEN
       WRITE(nulprt,*) subname, 'cdnam :',trim(cdnam),' il :',il, &
                       'mpi_root_global(il) :',mpi_root_global(il),&
                       'mpi_comm_local :',mpi_comm_local
       CALL oasis_flush(nulprt)
    ENDIF

    ! Definition of a MPI tag that must be unique for each
    ! intercommunicator
    !
    ! Note: this is not the case if the oasis_get_intercomm routine
    ! is called twice with the same component couple

    tag = prime_nbs(il) * prime_nbs(i_me)

    ! The MPI standard guarantees that the tag upper bound value (MPI_TAG_UB) 
    ! must be at least 32767, which is the case in this implementation, 
    ! given that the maximum tag value is equal to 
    !   prime_nbs(prism_nmodels-1) * prime_nbs(prism_nmodels) = 67x71 = 4757
    !
    ! For that reason, the test below is not mandatory and can be commented in
    ! case of portability issues

    CALL mpi_comm_get_attr(mpi_comm_local, MPI_TAG_UB, imax_tag_mpi, ferr, ierr)

    IF ( ierr == 0 .and. ferr ) THEN
       IF ( tag >= imax_tag_mpi ) THEN
          WRITE(nulprt,*) subname, ' Incorrect value of MPI tag (', tag, &
                                 ') bigger than max value : ', imax_tag_mpi
          CALL oasis_abort(file=__FILE__,line=__LINE__)
       ELSEIF ( OASIS_debug >= 2 ) THEN
          WRITE(nulprt,*) subname, ' MPI tag value and limit : ', tag, imax_tag_mpi
          CALL oasis_flush(nulprt)
       ENDIF
    ENDIF

    IF ( OASIS_debug >= 2 ) THEN
       WRITE(nulprt,*) subname, 'Tag intercomm :', tag
       CALL oasis_flush(nulprt)
    ENDIF

    CALL mpi_intercomm_create(mpi_comm_local, 0, mpi_comm_global, &
                              mpi_root_global(il), tag, new_comm, ierr)

    call oasis_mpi_chkerr(ierr,trim(subname)//' intercomm_create')

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_get_intercomm
!----------------------------------------------------------------------

!> OASIS user interface to establish an intracomm communicator between two components

  SUBROUTINE oasis_get_intracomm(new_comm, cdnam, kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(out) :: new_comm  !< output MPI communicator
    CHARACTER(len=*),intent(in) :: cdnam               !< other model name
    INTEGER (kind=ip_intwp_p),intent(out),optional :: kinfo  !< return code

    INTEGER (kind=ip_intwp_p)  :: tmp_intercomm, ierr
!   ---------------------------------------------------------
    character(len=*),parameter :: subname = '(oasis_get_intracomm)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    if (present(kinfo)) then
       kinfo = OASIS_OK
    endif

    call oasis_get_intercomm(tmp_intercomm, cdnam, kinfo)

    CALL mpi_intercomm_merge(tmp_intercomm,.FALSE., new_comm, ierr)
    call oasis_mpi_chkerr(ierr,trim(subname)//' intercomm_merge')

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_get_intracomm

!----------------------------------------------------------------------

!> OASIS user interface to establish an intracomm communicator between two or more components

  SUBROUTINE oasis_get_multi_intracomm(new_comm, cdnam, root_ranks, kinfo)

    IMPLICIT NONE

    INTEGER (kind=ip_intwp_p),intent(out) :: new_comm      !< output MPI communicator
    CHARACTER(len=*)         ,intent(in)  :: cdnam(:)      !< other model names
    INTEGER (kind=ip_intwp_p),intent(out) :: root_ranks(:) !< root rank of each model in cdnam in new comm
    INTEGER (kind=ip_intwp_p),intent(out) :: kinfo         !< return code

    INTEGER (kind=ip_intwp_p) :: tmp_comm, inter_comm, tmpsize, tmprank
    INTEGER (kind=ip_intwp_p),allocatable :: cdnum(:),rranks(:)
    INTEGER (kind=ip_intwp_p) :: n, k, k2, ierr, tag, icnt, remote_leader
    LOGICAL :: found, found_myself, inter_high
!   ---------------------------------------------------------
    character(len=*),parameter :: subname = '(oasis_get_multi_intracomm)'
!   ---------------------------------------------------------

    call oasis_debug_enter(subname)
    kinfo = OASIS_OK

    if (size(cdnam) /= size(root_ranks)) then
       write(nulprt,*) subname,estr,'cdnam and root_ranks sizes not the same'
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif

    allocate(cdnum(size(cdnam)))

    ! error check list of cdnam values
    ! create list of components involved, cdnum
    found_myself=.false.
    icnt = 0
    do k = 1,size(cdnam)
       !--- skip blank lines
       if (len_trim(cdnam(k)) > 0) then
          !--- must contain me at some point
          if (trim(cdnam(k)) == trim(compnm)) then
             found_myself = .true.
          endif
          !--- must not contain redundant values
          do k2 = k+1 ,size(cdnam)
             if (trim(cdnam(k)) == trim(cdnam(k2))) then
                write(nulprt,*) subname,estr,'model name duplicated in cdnam list: ',trim(cdnam(k))
                call oasis_abort(file=__FILE__,line=__LINE__)
             endif
          enddo
          !--- must contain only valid model names
          found = .false.
          do n = 1,prism_amodels
             if (trim(cdnam(k)) == trim(prism_modnam(n))) then
                if (found) then
                   write(nulprt,*) subname,estr,'found model name twice in cdnam list: ',trim(cdnam(k))
                   call oasis_abort(file=__FILE__,line=__LINE__)
                endif
                found = .true.
                icnt = icnt + 1
                cdnum(icnt) = n
             endif
          enddo
          if (.not.found) then
             write(nulprt,*) subname,estr,'model name does not exist: ',trim(cdnam(k))
             call oasis_abort(file=__FILE__,line=__LINE__)
          endif
       endif
    enddo

    ! check that my component name was in cdnam
    if (.not. found_myself) then
       write(nulprt,*) subname,estr,'must include my model name when calling',trim(compnm)
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif

    ! check there is at least one other valid model to connect to
    if (icnt <= 1) then
       write(nulprt,*) subname,estr,'must have at least 2 model names: ',icnt,cdnam
       call oasis_abort(file=__FILE__,line=__LINE__)
    endif

    ! now sort cdnum so all components are going to call the mpi ops in the same order consistently
    do k = 1,icnt
    do k2 = k+1,icnt
       if (cdnum(k2) < cdnum(k)) then
          n = cdnum(k)
          cdnum(k) = cdnum(k2)
          cdnum(k2) = n
       endif
    enddo
    enddo
    if (OASIS_debug >= 2) then
       write(nulprt,*) subname, 'cdnum=',cdnum(1:icnt)
       call oasis_flush(nulprt)
    endif

    ! order calls by model number via cdnum
    ! create pairwise calls from lower to higher comp ids
    ! don't need to check here, checks above will trap inconsistencies
    !   including each value in cdnam is not repeated and is valid
    ! compute rranks

    allocate(rranks(icnt))
    rranks=-1
    rranks(1)=0
    call MPI_comm_dup(mpi_comm_local, tmp_comm, ierr)
    call oasis_mpi_chkerr(ierr,trim(subname)//' comm_dup local')
    do k = 2,icnt
       n = cdnum(k)
       rranks(k) = rranks(k-1) + mpi_comp_size(cdnum(k-1))
       tag=8000+n
       if (compid == n) then
          remote_leader = mpi_root_global(cdnum(1))  ! root of 1st model 
          inter_high = .true.
       else
          remote_leader = mpi_root_global(n)         ! root of model k
          inter_high = .false.
       endif
       if (compid <= n) then
          if (OASIS_debug >= 2) then
             write(nulprt,'(2a,2i4,a,i6,a,i8)') subname,' k,n =',k,n, &
                             ' remote_leader=',remote_leader, ' tag=',tag
             call MPI_Comm_Size(tmp_comm,tmpsize,ierr)
             call oasis_mpi_chkerr(ierr,trim(subname)//' size')
             call MPI_Comm_Rank(tmp_comm,tmprank,ierr)
             call oasis_mpi_chkerr(ierr,trim(subname)//' rank')
             write(nulprt,*) subname,' tmp_comm size,rank=',tmpsize,tmprank
             call oasis_flush(nulprt)
          endif
          ! inter_comm = tmp_comm + remote_comm
          call MPI_intercomm_create(tmp_comm, 0, mpi_comm_global, &
                                    remote_leader, tag, inter_comm, ierr)
          call oasis_mpi_chkerr(ierr,trim(subname)//' intercomm_create')
          call MPI_comm_free(tmp_comm,ierr)
          call oasis_mpi_chkerr(ierr,trim(subname)//' comm_free tmp_comm')
          ! tmp_comm = inter2intra(inter_comm)
          call MPI_intercomm_merge(inter_comm, inter_high, tmp_comm, ierr)
          call oasis_mpi_chkerr(ierr,trim(subname)//' intercomm_merge')
          call MPI_comm_free(inter_comm,ierr)
          call oasis_mpi_chkerr(ierr,trim(subname)//' comm_free inter_comm')
       endif
    enddo

    new_comm = tmp_comm
    root_ranks = -1
    do n = 1,icnt
       do k = 1,size(cdnam)
          if (cdnam(k) == prism_modnam(cdnum(n))) then
             root_ranks(k) = rranks(n)
          endif
       enddo
    enddo
    if (OASIS_debug >= 2) then
       do k = 1,size(cdnam)
          write(nulprt,'(2a,i4,3a,i8)') subname,' k =',k, &
                          ' cdnam = ',trim(cdnam(k)), &
                          ' root_rank = ',root_ranks(k)
       enddo
       call oasis_flush(nulprt)
    endif

    deallocate(rranks)
    deallocate(cdnum)

    call oasis_debug_exit(subname)

  END SUBROUTINE oasis_get_multi_intracomm
!----------------------------------------------------------------------

!> OASIS user query for the number of unique couplings associated with a variable

  SUBROUTINE oasis_get_ncpl(varid, ncpl, kinfo)

    IMPLICIT none
    !-------------------------------------
    INTEGER(kind=ip_i4_p) , INTENT(in)  :: varid   !< variable id
    INTEGER(kind=ip_i4_p) , INTENT(out) :: ncpl    !< number of namcouple couplings
    INTEGER(kind=ip_i4_p) , INTENT(out) :: kinfo   !< return code
    !-------------------------------------
    CHARACTER(len=ic_lvar)  :: vname
    CHARACTER(len=*),PARAMETER :: subname = 'oasis_get_ncpl'
    !-------------------------------------

    CALL oasis_debug_enter(subname)

    IF (mpi_comm_local == MPI_COMM_NULL) THEN
       WRITE(nulprt,*) subname,estr,'called on non coupling task'
       call oasis_abort(file=__FILE__,line=__LINE__)
    ENDIF

    kinfo = OASIS_OK
    vname = prism_var(varid)%name
    
    IF (varid == OASIS_Var_Uncpl) THEN
       WRITE(nulprt,*) subname,estr,'Routine is called for an invalid varid'
       call oasis_abort(file=__FILE__,line=__LINE__)
    ENDIF
    
    ncpl  = prism_var(varid)%ncpl
    
    IF (ncpl <= 0) THEN
       IF (OASIS_debug >= 2) WRITE(nulprt,*) subname,' Variable not coupled ',&
                              TRIM(vname)
    ELSE 
       IF (OASIS_debug >= 2)  WRITE(nulprt,*) subname,' Variable: ',TRIM(vname),&
                              ' used in ',ncpl,' couplings' 
    ENDIF

    CALL oasis_debug_exit(subname)
    
  END SUBROUTINE oasis_get_ncpl
!---------------------------------------------------------------------

!> OASIS user query for the coupling periods for a given variable

  SUBROUTINE oasis_get_freqs(varid, mop, ncpl, cpl_freqs, kinfo)

    IMPLICIT none
    !-------------------------------------
    INTEGER(kind=ip_i4_p) , INTENT(in)  :: varid          !< variable id
    INTEGER(kind=ip_i4_p) , INTENT(in)  :: mop            !< OASIS_Out or OASIS_In type
    INTEGER(kind=ip_i4_p) , INTENT(in)  :: ncpl           !< number of namcouple couplings
    INTEGER(kind=ip_i4_p) , INTENT(out) :: cpl_freqs(ncpl)!< coupling period (sec)
    INTEGER(kind=ip_i4_p) , INTENT(out) :: kinfo          !< return code
    !-------------------------------------
    CHARACTER(len=ic_lvar)  :: vname
    INTEGER(kind=ip_i4_p)   :: ncpl_calc, cplid, nc
    CHARACTER(len=*),PARAMETER :: subname = 'oasis_get_freqs'
    !-------------------------------------

    CALL oasis_debug_enter(subname)

    IF (mpi_comm_local == MPI_COMM_NULL) THEN
       WRITE(nulprt,*) subname,estr,'called on non coupling task'
       call oasis_abort(file=__FILE__,line=__LINE__)
    ENDIF

    kinfo = OASIS_OK
    vname = prism_var(varid)%name
    
    IF (varid == OASIS_Var_Uncpl) THEN
       WRITE(nulprt,*) subname,estr,'Routine is called for an invalid varid'
       call oasis_abort(file=__FILE__,line=__LINE__)
    ENDIF
    
    ncpl_calc  = prism_var(varid)%ncpl

    IF (ncpl_calc /= ncpl) THEN
       WRITE(nulprt,*) subname,estr,' Wrong number of couplings for variable: ',TRIM(vname), &
                       ncpl_calc, ncpl
       call oasis_abort(file=__FILE__,line=__LINE__)
    ENDIF
    
    IF (ncpl <= 0) THEN
       IF (OASIS_debug >= 2) WRITE(nulprt,*) subname,' variable not coupled ',&
                              TRIM(vname)
    ENDIF

    DO nc = 1,ncpl
       cplid           = prism_var(varid)%cpl(nc)
       IF (mop == OASIS_Out) THEN
          cpl_freqs(nc)   = prism_coupler_put(cplid)%dt
       ENDIF
       IF (mop == OASIS_In ) THEN
          cpl_freqs(nc)   = prism_coupler_get(cplid)%dt
       ENDIF

       IF (OASIS_Debug >=2 ) THEN
          WRITE(nulprt,*)  subname,' Coupling frequency of this field ',TRIM(vname),&
                           ' for coupling ',nc, ' is ',cpl_freqs(nc)
       ENDIF

       IF (cpl_freqs(nc) .le. 0) THEN
          WRITE(nulprt,*) subname,estr,' The coupling frequency is < or equal to 0'
          call oasis_abort(file=__FILE__,line=__LINE__)
       ENDIF
    ENDDO

    CALL oasis_debug_exit(subname)

  END SUBROUTINE oasis_get_freqs
!---------------------------------------------------------------------

!> OASIS user query to indicate put return code expected at a specified time for a given variable

  SUBROUTINE oasis_put_inquire(varid,msec,kinfo)

    IMPLICIT none
    !-------------------------------------
    integer(kind=ip_i4_p) , intent(in)  :: varid   !< variable id
    integer(kind=ip_i4_p) , intent(in)  :: msec    !< model time in seconds
    integer(kind=ip_i4_p) , intent(out) :: kinfo   !< return code
    !-------------------------------------
    character(len=ic_lvar)     :: vname
    INTEGER(kind=ip_i4_p)      :: ncpl, nc, cplid
    INTEGER(kind=ip_i4_p)      :: lag, mseclag, trans, dt, getput, maxtime
    LOGICAL                    :: time_now, sndrcv, output
    character(len=*),parameter :: subname = 'oasis_put_inquire'
    !-------------------------------------

    CALL oasis_debug_enter(subname)

    IF (mpi_comm_local == MPI_COMM_NULL) THEN
       WRITE(nulprt,*) subname,estr,'called on non coupling task'
       call oasis_abort(file=__FILE__,line=__LINE__)
    ENDIF

    kinfo = OASIS_OK
    vname = prism_var(varid)%name
    
    IF (varid == OASIS_Var_Uncpl) THEN
       WRITE(nulprt,*) subname,estr, &
          'Routine oasis_put is called for a variable not in namcouple: it will not be sent'
       call oasis_abort(file=__FILE__,line=__LINE__)
    ENDIF
    
    ncpl  = prism_var(varid)%ncpl
    
    IF (ncpl <= 0) THEN
       IF (OASIS_debug >= 2) WRITE(nulprt,*) subname,' variable not coupled ',&
                              TRIM(vname)
    ENDIF

    DO nc = 1,ncpl

       cplid   = prism_var(varid)%cpl(nc)
       dt      = prism_coupler_put(cplid)%dt
       lag     = prism_coupler_put(cplid)%lag
       getput  = prism_coupler_put(cplid)%getput
       sndrcv  = prism_coupler_put(cplid)%sndrcv
       maxtime = prism_coupler_put(cplid)%maxtime
       output  = prism_coupler_put(cplid)%output
       trans   = prism_coupler_put(cplid)%trans

       !------------------------------------------------
       ! check that lag is reasonable
       !------------------------------------------------

       IF (ABS(lag) > dt) THEN
          WRITE(nulprt,*) subname,estr,' ERROR lag gt dt for cplid',cplid
          call oasis_abort(file=__FILE__,line=__LINE__)
       ENDIF

       !------------------------------------------------
       ! check that field is OASIS_PUT
       !------------------------------------------------

       IF (getput == OASIS3_GET) THEN
          WRITE(nulprt,*) subname,estr,'routine can only be called for OASIS_PUT variable'
          call oasis_abort(file=__FILE__,line=__LINE__)
       ENDIF

       CALL oasis_debug_note(subname//' set mseclag')
       IF (getput == OASIS3_PUT) THEN
          mseclag = msec + lag
       ENDIF

       !------------------------------------------------
       ! check that model hasn't gone past maxtime
       !------------------------------------------------

       if (msec >= maxtime) then
          write(nulprt,*) subname,' at ',msec,mseclag,'  ERROR: ',trim(vname)
          write(nulprt,*) subname,estr,'model time must be strictly smaller than namcouple $RUNTIME =',&
                          msec,maxtime
          call oasis_abort(file=__FILE__,line=__LINE__)
       endif

       time_now = .FALSE.
       IF (MOD(mseclag,dt) == 0) time_now = .TRUE.

       !-------------------------------------------------------------------
       ! Test what is the current status of the field if time_now = .TRUE.
       !-------------------------------------------------------------------

       IF (time_now .EQV. .TRUE.) THEN

          IF (OASIS_debug >= 2) THEN
             WRITE(nulprt,*) subname,' Coupling time for : ',trim(vname)
             WRITE(nulprt,*) subname,'  Coupling time for var for nc : ',&
                 TRIM(mct_avect_exportRList2c(prism_coupler_put(cplid)%avect1)),nc
             WRITE(nulprt,*) subname,' dt,msec,mseclag = ',dt,msec,mseclag
             CALL oasis_flush(nulprt)
          ENDIF

          IF ( (trans == ip_average) .OR. (trans == ip_accumul) .OR. (trans == ip_max) &
                                     .OR. (trans == ip_min) ) THEN
             IF (kinfo == OASIS_OK) kinfo = OASIS_LocTrans
             IF (OASIS_debug >= 2) THEN
                WRITE(nulprt,*) subname,' status at ',msec,mseclag,' WTRN '
                CALL oasis_flush(nulprt)
             ENDIF
          ENDIF

          !-------------------------------------------------------------------
          ! past namcouple runtime (maxtime) no communication
          ! do restart if time+lag = maxtime, this assumes coupling
          ! period and lag and maxtime are all nicely consistent
          !-------------------------------------------------------------------
          IF (mseclag >= maxtime) THEN
             IF (getput == OASIS3_PUT .AND. lag > 0 .AND. mseclag == maxtime) THEN
                kinfo = OASIS_ToRest
                IF (OASIS_debug >= 2) THEN
                   WRITE(nulprt,*) subname,' status at ',msec,mseclag,' WRST '
                   CALL oasis_flush(nulprt)
                ENDIF
             ENDIF
          ENDIF
          
          !------------------------------------------------
          ! communication
          !------------------------------------------------
          IF (sndrcv) THEN
             IF (getput == OASIS3_PUT) THEN
                kinfo = OASIS_sent
                IF (OASIS_debug >= 2) THEN
                   WRITE(nulprt,*) subname,' status at ',msec,mseclag,' will be SENT '
                   CALL oasis_flush(nulprt)
                ENDIF
             ENDIF
          ENDIF

          !------------------------------------------------
          ! save debug file if EXPOUT or OUTPUT
          !------------------------------------------------
          IF (output) THEN
             IF (kinfo == OASIS_sent) THEN
                 kinfo = OASIS_sentout
             ELSEIF (kinfo == OASIS_torest) THEN
                 kinfo = OASIS_torestout
             ELSE
                 kinfo = OASIS_output
             ENDIF
             IF (OASIS_debug >= 2) THEN
                WRITE(nulprt,*) subname,' status at ',msec,mseclag,' will be WRIT '
                CALL oasis_flush(nulprt)
             ENDIF
          ENDIF

          !------------------------------------------------
          ! sav non-instant loctrans operations for future restart
          !   at the end of the run only
          !------------------------------------------------

          IF (mseclag + dt >= maxtime .AND. &
             getput == OASIS3_PUT .and. trans /= ip_instant) then
             IF (OASIS_debug >= 2) THEN
                WRITE(nulprt,*) subname,' at ',msec,mseclag,' will be WTRN: '
                CALL oasis_flush(nulprt)
             ENDIF
          ENDIF
       ELSE
          IF (OASIS_Debug >=2) THEN
              WRITE(nulprt,*) 'Nothing to do'
          ENDIF
       ENDIF ! time_now

       IF (OASIS_debug >= 2) THEN
          WRITE(nulprt,*) subname,' kinfo: ',kinfo
          CALL oasis_flush(nulprt)
       ENDIF
    ENDDO  ! nc

    CALL oasis_debug_exit(subname)

    END SUBROUTINE oasis_put_inquire

!---------------------------------------------------------------------------------
  END MODULE mod_oasis_auxiliary_routines

