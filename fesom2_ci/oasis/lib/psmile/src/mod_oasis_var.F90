
!> OASIS variable data and methods

  MODULE mod_oasis_var

  USE mod_oasis_kinds
  USE mod_oasis_data
  USE mod_oasis_parameters
  USE mod_oasis_sys
  USE mod_oasis_mpi
  USE mod_oasis_timer
  USE mod_oasis_part

  IMPLICIT none

  private

  !--- interfaces ---
  public oasis_def_var
  public oasis_var_setup

  !> Overloaded interface into oasis_def_var to support old and new interface
  interface oasis_def_var ; module procedure &
    oasis_def_var_v1s1, &
    oasis_def_var_v1s2, &
    oasis_def_var_v2
  end interface

  !--- datatypes ---

  integer(ip_intwp_p),public   :: maxvar  !< number of potential variables, derived from namcouple input
  integer(kind=ip_i4_p),parameter,public :: mvarcpl = 10   !< max namcouples per variable

  !> Model variable data for model coupling
  type prism_var_type
     character(len=ic_lvar):: name  !< variable name
     integer(kind=ip_i4_p) :: part  !< variable partition
     integer(kind=ip_i4_p) :: ndim  !< rank of variable
     integer(kind=ip_i4_p) :: num   !< size of variable
     integer(kind=ip_i4_p) :: ops   !< input or output
     integer(kind=ip_i4_p) :: type  !< type kind of variable
     integer(kind=ip_i4_p) :: size  !< total size of field
     integer(kind=ip_i4_p) :: ncpl  !< number of namcouple couplers
     integer(kind=ip_i4_p) :: cpl(mvarcpl)  !< list of namcouple couplers
  end type prism_var_type

  integer(kind=ip_intwp_p),public :: prism_nvar = 0    !< number of variables defined
  TYPE(prism_var_type),POINTER,public :: prism_var(:)  !< list of defined variables

  CONTAINS

!---------------------------------------------------------------

!> The original OASIS user interface to define variables
!> id_var_shape is 1d array (not used)
!> Called via oasis_def_var

  SUBROUTINE oasis_def_var_v1s1(id_nports, cdport, id_part, &
         id_var_nodims, kinout, id_var_shape, ktype, kinfo)
     !---------------------------------------------------------------
     INTEGER(kind=ip_i4_p),intent(out) :: id_nports    !< coupling field ID
     CHARACTER(len=*)     ,intent(in)  :: cdport       !< field name as in namcouple
     INTEGER(kind=ip_i4_p),intent(in)  :: id_part      !< partition ID
     INTEGER(kind=ip_i4_p),intent(in)  :: id_var_nodims(2)  !< rank and number of bundles
     INTEGER(kind=ip_i4_p),intent(in)  :: kinout       !< input or output flag
     INTEGER(kind=ip_i4_p),intent(in)  :: id_var_shape(:) !< size of field (no longer used)
     INTEGER(kind=ip_i4_p),intent(in)  :: ktype        !< type of coupling field
     INTEGER(kind=ip_i4_p),intent(out),optional :: kinfo    !< return code
     !---------------------------------------------------------------
     character(len=*),parameter :: subname = '(oasis_def_var_v1s1)'
     !---------------------------------------------------------------

     call oasis_debug_enter(subname)

     if (present(kinfo)) then
       call oasis_def_var_v2(id_nports, cdport, id_part, &
         id_var_nodims, kinout, ktype, kinfo)
     else
       call oasis_def_var_v2(id_nports, cdport, id_part, &
         id_var_nodims, kinout, ktype)
     endif

     call oasis_debug_exit(subname)

   END SUBROUTINE oasis_def_var_v1s1

!---------------------------------------------------------------

!> The original OASIS user interface to define variables
!> id_var_shape is 2d array (not used)
!> Called via oasis_def_var

  SUBROUTINE oasis_def_var_v1s2(id_nports, cdport, id_part, &
         id_var_nodims, kinout, id_var_shape, ktype, kinfo)
     !---------------------------------------------------------------
     INTEGER(kind=ip_i4_p),intent(out) :: id_nports    !< coupling field ID
     CHARACTER(len=*)     ,intent(in)  :: cdport       !< field name as in namcouple
     INTEGER(kind=ip_i4_p),intent(in)  :: id_part      !< partition ID
     INTEGER(kind=ip_i4_p),intent(in)  :: id_var_nodims(2)  !< rank and number of bundles
     INTEGER(kind=ip_i4_p),intent(in)  :: kinout       !< input or output flag
     INTEGER(kind=ip_i4_p),intent(in)  :: id_var_shape(:,:) !< size of field (no longer used)
     INTEGER(kind=ip_i4_p),intent(in)  :: ktype        !< type of coupling field
     INTEGER(kind=ip_i4_p),intent(out),optional :: kinfo    !< return code
     !---------------------------------------------------------------
     character(len=*),parameter :: subname = '(oasis_def_var_v1s2)'
     !---------------------------------------------------------------

     call oasis_debug_enter(subname)

     if (present(kinfo)) then
       call oasis_def_var_v2(id_nports, cdport, id_part, &
         id_var_nodims, kinout, ktype, kinfo)
     else
       call oasis_def_var_v2(id_nports, cdport, id_part, &
         id_var_nodims, kinout, ktype)
     endif

     call oasis_debug_exit(subname)

   END SUBROUTINE oasis_def_var_v1s2

!---------------------------------------------------------------

!> The updated OASIS user interface to define variables
!> Called via oasis_def_var

  SUBROUTINE oasis_def_var_v2(id_nports, cdport, id_part, &
         id_var_nodims, kinout, ktype, kinfo)
     !---------------------------------------------------------------
     INTEGER(kind=ip_i4_p),intent(out) :: id_nports    !< coupling field ID
     CHARACTER(len=*)     ,intent(in)  :: cdport       !< field name as in namcouple
     INTEGER(kind=ip_i4_p),intent(in)  :: id_part      !< partition ID
     INTEGER(kind=ip_i4_p),intent(in)  :: id_var_nodims(2)  !< rank and number of bundles
     INTEGER(kind=ip_i4_p),intent(in)  :: kinout       !< input or output flag
     INTEGER(kind=ip_i4_p),intent(in)  :: ktype        !< type of coupling field
     INTEGER(kind=ip_i4_p),intent(out),optional :: kinfo    !< return code
     !---------------------------------------------------------------
     INTEGER(kind=ip_i4_p)  :: il_var_nodims_temp(2)  !< rank and number of bundles temporary
     INTEGER(kind=ip_i4_p)  :: n
     CHARACTER(len=ic_lvar) :: trimmed_cdport   ! Trimmed version of cdport
     character(len=*),parameter :: subname  = '(oasis_def_var_v2)'
     character(len=*),parameter :: subnamei = '(oasis_def_var)'
     LOGICAL    :: l_field_in_namcouple
     !---------------------------------------------------------------

     call oasis_debug_enter(subname)
     if (.not. oasis_coupled) then
        call oasis_debug_exit(subname)
        return
     endif

     !-------------------------------------------------     
     !> * Check len of incoming variable name
     ! Trim incoming name once to avoid multiple trim operations
     ! in subsequent loops
     !-------------------------------------------------     

     if (len_trim(cdport) > ic_lvar) then
        WRITE(nulprt,*) subnamei,estr,'variable too long = ',trim(cdport)
        WRITE(nulprt,*) subnamei,estr,'max variable length (ic_lvar) = ',ic_lvar
        call oasis_abort(file=__FILE__,line=__LINE__)
     endif
     trimmed_cdport = trim(cdport)

     if (present(kinfo)) kinfo = OASIS_Ok

     l_field_in_namcouple = .FALSE.
     n = 0

     !-------------------------------------------------     
     !> * Search for field in namcouple field lists
     !-------------------------------------------------

     ! If either condition ceases to be true then bail out of the loop
     DO WHILE (n < size_namfld .AND. (.NOT.l_field_in_namcouple))
        n = n+1
        IF ( (trimmed_cdport == total_namsrcfld(n)).OR.    &
             (trimmed_cdport == total_namdstfld(n)) ) THEN 
              l_field_in_namcouple = .TRUE.
        ENDIF       
     enddo

     !-------------------------------------------------     
     !> * Return if field not found in namcouple
     !-------------------------------------------------     

     if (.not. l_field_in_namcouple) then
        id_nports = OASIS_Var_Uncpl
        if (OASIS_debug >= 2) then
           write(nulprt,*) subnamei,' variable not in namcouple return ',trimmed_cdport
           call oasis_flush(nulprt)
        endif
        call oasis_debug_exit(subname)
        return
     endif

     !-------------------------------------------------     
     !> * Abort if field already defined
     !-------------------------------------------------     

     do n = 1,prism_nvar
        if (trimmed_cdport == prism_var(n)%name) then
           write(nulprt,*) subnamei,estr,'variable already defined with def_var = ',trimmed_cdport
           write(nulprt,*) subnamei,estr,'check oasis_def_var calls in your model'
           call oasis_abort(file=__FILE__,line=__LINE__)
        endif
     enddo

     ! tcraig, this is due to i3.3 in the 2d->1d field bundle renaming
     il_var_nodims_temp(:)=id_var_nodims(:)
     IF (il_var_nodims_temp(2) > 999) THEN
        write(nulprt,*) subnamei,estr,'variable id_var_nodims(2) too large.  limit is 999 ',il_var_nodims_temp(2)
        write(nulprt,*) subnamei,estr,'check oasis_def_var calls in your model'
        call oasis_abort(file=__FILE__,line=__LINE__)
     ENDIF
         
     IF (il_var_nodims_temp(2) <= 0) THEN
         il_var_nodims_temp(2)=1
         WRITE(nulprt,*) subnamei,'WARNING id_var_nodim(2) cannot be negative or 0 ; put to 1'
         call oasis_flush(nulprt)
     ENDIF

     !-------------------------------------------------     
     !> * Increment the variable and store the values
     !-------------------------------------------------     

     prism_nvar = prism_nvar + 1
     id_nports = prism_nvar

     if (prism_nvar > maxvar) then
        write(nulprt,*) subnamei,estr,'prism_nvar too large = ',prism_nvar,maxvar
        write(nulprt,*) subnamei,estr,'check maxvar set in oasis_init_comp'
        call oasis_abort(file=__FILE__,line=__LINE__)
     endif

     call oasis_var_zero(prism_var(prism_nvar))
     prism_var(prism_nvar)%name = trimmed_cdport
     prism_var(prism_nvar)%part = id_part
     prism_var(prism_nvar)%num  = il_var_nodims_temp(2)
     prism_var(prism_nvar)%ops  = kinout
     prism_var(prism_nvar)%type = ktype
     prism_var(prism_nvar)%size = 1
     prism_var(prism_nvar)%ncpl = 0
     prism_var(prism_nvar)%cpl  = 0

     !----------------------------------
     !> * Write some diagnostics
     !----------------------------------

     if (OASIS_debug >= 2) then
        write(nulprt,*) ' '
        write(nulprt,*) subnamei,' prism_nvar    = ',prism_nvar
        write(nulprt,*) subnamei,' varname = ',prism_nvar,trim(prism_var(prism_nvar)%name)
        write(nulprt,*) subnamei,' varpart = ',prism_nvar,prism_var(prism_nvar)%part
        write(nulprt,*) subnamei,' varnum  = ',prism_nvar,prism_var(prism_nvar)%num
        write(nulprt,*) subnamei,' varops  = ',prism_nvar,prism_var(prism_nvar)%ops
        write(nulprt,*) subnamei,' vartype = ',prism_nvar,prism_var(prism_nvar)%type
        write(nulprt,*) ' '
        CALL oasis_flush(nulprt)
     endif

     call oasis_debug_exit(subname)

   END SUBROUTINE oasis_def_var_v2

!---------------------------------------------------------------

!> Synchronize variables across all tasks, called at oasis enddef.

  SUBROUTINE oasis_var_setup()
   IMPLICIT NONE

   !--------------------------------------------------------
   integer(kind=ip_intwp_p) :: m,n,p,v
   INTEGER(kind=ip_intwp_p) :: ierr, taskid
   integer(kind=ip_intwp_p) :: vcnt
   logical                  :: found, fastcheckout
   character(len=ic_lvar)  ,allocatable :: vname0(:),vname(:)
   character(len=ic_lvar2) ,allocatable :: pname0(:),pname(:)
   integer(kind=ip_intwp_p),allocatable :: inout0(:),inout(:)
   integer(kind=ip_intwp_p),allocatable :: vanum0(:),vanum(:)
   logical, parameter :: local_timers_on = .false.
   character(len=*),parameter :: subname = '(oasis_var_setup)'
   !--------------------------------------------------------

   call oasis_debug_enter(subname)

   IF (local_timers_on) call oasis_timer_start('var_setup')

   IF (local_timers_on) call oasis_timer_start('var_setup_reducelists')
   allocate(vname0(prism_nvar))
   allocate(pname0(prism_nvar))
   allocate(inout0(prism_nvar))
   allocate(vanum0(prism_nvar))
   do n = 1,prism_nvar
      vname0(n) = prism_var(n)%name
      inout0(n) = prism_var(n)%ops
      vanum0(n) = prism_var(n)%num
      pname0(n) = prism_part(prism_var(n)%part)%partname
   enddo

   call oasis_mpi_reducelists(vname0,mpi_comm_local,vcnt,vname,'var_setup', &
        fastcheck=.true.,fastcheckout=fastcheckout, &
        linp2=pname0,lout2=pname,linp3=inout0,lout3=inout,linp4=vanum0,lout4=vanum)

   deallocate(vname0)
   deallocate(pname0)
   deallocate(inout0)
   deallocate(vanum0)
   IF (local_timers_on) call oasis_timer_stop('var_setup_reducelists')

   !-------------------------------------------------     
   !> * Initialize variables on tasks where they are not previously defined.
   ! if fastcheck worked, then don't need to do this extra work to add undefined vars
   !-------------------------------------------------     

   if (.not. fastcheckout) then

      if (local_timers_on) call oasis_timer_start('var_setup_initvar')
      do v = 1,vcnt

         !--- either a prism_var that already exists
         found = .false.
         n = 0
         do while (n < prism_nvar .and. .not.found)
            n = n + 1
            if (prism_var(n)%name == vname(v)) then
               found = .true.
            endif
         enddo

         !--- or a new prism_var that must be instantiated
         if (.not.found) then
            prism_nvar = prism_nvar + 1

            call oasis_var_zero(prism_var(prism_nvar))
            prism_var(prism_nvar)%name = vname(v)
            prism_var(prism_nvar)%ops  = inout(v)
            prism_var(prism_nvar)%num  = vanum(v)
            prism_var(prism_nvar)%ncpl = 0
            !--- figure out the local part id for the part name
            p = 0
            found = .false.
            do while (p < prism_npart .and. .not.found)
               p = p + 1
               if (prism_part(p)%partname == pname(v)) then
                  found = .true.
               endif
            enddo
            if (found) then
               prism_var(prism_nvar)%part = p
               if (OASIS_debug >= 15) then
                  write(nulprt,*) subname,' found part match ',trim(vname(v)),trim(pname(v)),p
               endif
            else
               write(nulprt,*) subname,estr,'prism part not found part = ',trim(pname(v)),' var = ',trim(vname(v))
               call oasis_abort(file=__FILE__,line=__LINE__)
            endif
   
            if (OASIS_debug >= 2) then
               write(nulprt,*) ' '
               write(nulprt,*) subname,' add var = ',prism_nvar,trim(prism_var(prism_nvar)%name),&
                               prism_var(prism_nvar)%part,&
                               trim(prism_part(prism_var(prism_nvar)%part)%partname),prism_var(prism_nvar)%ops
               CALL oasis_flush(nulprt)
            ENDIF
         endif

      enddo   ! v = 1,vcnt
      if (local_timers_on) call oasis_timer_stop ('var_setup_initvar')

   endif   ! fastcheckout

   deallocate(vname,pname,inout,vanum)

   IF (local_timers_on) call oasis_timer_stop('var_setup')
      
   call oasis_debug_exit(subname)

   END SUBROUTINE oasis_var_setup

!---------------------------------------------------------------

!> Zero variable information

  SUBROUTINE oasis_var_zero(prism_var)
   IMPLICIT NONE

   !--------------------------------------------------------
   type(prism_var_type),intent(inout) :: prism_var
   character(len=*),parameter :: subname = '(oasis_var_zero)'
   !--------------------------------------------------------

   call oasis_debug_enter(subname)

   prism_var%name = 'oasis_var_name_unset'
   prism_var%part = -1
   prism_var%ndim = -1
   prism_var%num  = -1
   prism_var%ops  = -1
   prism_var%type = -1
   prism_var%size = -1
   prism_var%ncpl = 0
   prism_var%cpl  = -1

   call oasis_debug_exit(subname)

   END SUBROUTINE oasis_var_zero

!---------------------------------------------------------------
 END MODULE mod_oasis_var

