PROGRAM generic_testcase 
  USE xios
  USE mod_wait
  IMPLICIT NONE
  INCLUDE "mpif.h"
  INTEGER,PARAMETER :: unit=10
  INTEGER,PARAMETER :: len_str=255
  INTEGER :: ierr

  INTEGER :: nb_proc_atm
  INTEGER :: nb_proc_oce
  INTEGER :: nb_proc_surf
  CHARACTER(LEN=len_str)  :: proc_distribution
  CHARACTER(LEN=len_str)  :: start_date
  CHARACTER(LEN=len_str)  :: duration
  DOUBLE PRECISION        :: sypd
  NAMELIST /params_run/    nb_proc_atm, nb_proc_surf, nb_proc_oce, & 
                           duration, sypd, start_date, proc_distribution


  TYPE tmodel_params
    CHARACTER(len_str)  :: timestep=""
    CHARACTER(len_str)  :: domain=""
    DOUBLE PRECISION    :: domain_proc_frac
    INTEGER             :: domain_proc_n
    CHARACTER(len_str)  :: axis=""
    DOUBLE PRECISION    :: axis_proc_frac
    INTEGER             :: axis_proc_n
    INTEGER             :: ensemble_proc_n
    INTEGER             :: ni 
    INTEGER             :: nj 
    INTEGER             :: nlev
    CHARACTER(len_str)  :: init_field2D=""
    DOUBLE PRECISION    :: pressure_factor
    LOGICAL :: domain_mask
    LOGICAL :: axis_mask
    LOGICAL :: mask3d
    INTEGER             :: field_sub_freq 
    INTEGER             :: field_sub_offset
  END TYPE  tmodel_params



  CHARACTER(len_str)  :: timestep_atm
  CHARACTER(len_str)  :: domain_atm 
  CHARACTER(len_str)  :: axis_atm 
  INTEGER             :: ni_atm 
  INTEGER             :: nj_atm 
  INTEGER             :: nlev_atm
  CHARACTER(len_str)  :: init_field2D_atm 
 
 
  LOGICAL :: i_am_atm, i_am_oce, i_am_surf, i_am_server
  INTEGER :: rank, size_loc
  
   
  OPEN(unit=unit, file='param.def',status='old',iostat=ierr)
  nb_proc_atm=1
  nb_proc_oce=0  
  nb_proc_surf=0
  duration="1d"
  sypd=10000
  start_date="2018-01-01"
  proc_distribution="contiguous"
  READ (unit, nml=params_run)
  CLOSE(unit)
!!! MPI Initialization

  CALL MPI_INIT(ierr)
  CALL init_wait
  CALL MPI_COMM_RANK(MPI_COMM_WORLD,rank,ierr)
  CALL MPI_COMM_SIZE(MPI_COMM_WORLD,size_loc,ierr)
  if (size_loc < nb_proc_atm + nb_proc_oce + nb_proc_surf) then
     PRINT *,"inconsistency : size=",size_loc," nb_proc_atm=",nb_proc_atm,&
          " nb_proc_oce=",nb_proc_oce," nb_proc_surf=",nb_proc_surf
     CALL MPI_ABORT()
  endif

  i_am_atm=.FALSE. ; i_am_oce=.FALSE. ; i_am_surf=.FALSE. ; i_am_server=.FALSE. 

  IF (proc_distribution=="contiguous") THEN

   ! First ranks are dedicated to Atm, next to Ocean, next to Surf, last to Server

    IF (rank < nb_proc_atm) THEN 
      i_am_atm=.TRUE. 
    ELSE IF (rank < nb_proc_atm+nb_proc_oce) THEN 
      i_am_oce=.TRUE. 
    ELSE IF (rank < nb_proc_atm+nb_proc_oce+nb_proc_surf) THEN 
      i_am_surf=.TRUE. 
    ELSE
      i_am_server=.TRUE. 
    ENDIF ;

  ENDIF
  
  
  IF (i_am_server) THEN
    CALL xios_init_server()
  
  ELSE

    IF (i_am_atm) CALL model("atm")
  
    CALL xios_finalize()
  ENDIF

 print*, "finished Successfully"  
  CALL MPI_FINALIZE(ierr)
  
CONTAINS

  SUBROUTINE model(model_id)
  IMPLICIT NONE
    CHARACTER(LEN=*) :: model_id
    TYPE(tmodel_params) :: params, other_params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    TYPE(xios_date)  :: cdate, edate
    TYPE(xios_duration)  :: dtime
    INTEGER :: rank
    INTEGER :: size_loc
    DOUBLE PRECISION :: timestep_in_seconds, simulated_seconds_per_seconds, elapsed_per_timestep
    INTEGER :: ts

    DOUBLE PRECISION, POINTER :: lon(:)
    DOUBLE PRECISION, POINTER :: lat(:)
    DOUBLE PRECISION, POINTER :: axis_value(:)
    LOGICAL, POINTER          :: domain_mask(:)
    INTEGER, POINTER          :: domain_index(:)
    LOGICAL, POINTER          :: axis_mask(:)
    INTEGER, POINTER          :: axis_index(:)
    DOUBLE PRECISION, POINTER :: ensemble_value(:)
    
    DOUBLE PRECISION, POINTER :: X_lon(:)
    DOUBLE PRECISION, POINTER :: X_lat(:)
    LOGICAL, POINTER          :: X_mask(:)
    INTEGER, POINTER          :: X_index(:)

    DOUBLE PRECISION, POINTER :: Y_lon(:)
    DOUBLE PRECISION, POINTER :: Y_lat(:)
    LOGICAL, POINTER          :: Y_mask(:)
    INTEGER, POINTER          :: Y_index(:)
                
    DOUBLE PRECISION, POINTER :: field2D_init(:)
    DOUBLE PRECISION, POINTER :: fieldX_init(:)
    DOUBLE PRECISION, POINTER :: fieldY_init(:)
    DOUBLE PRECISION, POINTER :: fieldXY_init(:,:)

    DOUBLE PRECISION, POINTER :: field2D(:), other_field2D(:)
    DOUBLE PRECISION, POINTER :: field_X(:), other_field_X(:)
    DOUBLE PRECISION, POINTER :: field_Y(:), other_field_Y(:)
    DOUBLE PRECISION, POINTER :: field_Z(:), other_field_Z(:)
    DOUBLE PRECISION, POINTER :: field_XY(:,:), other_field_XY(:,:)
    DOUBLE PRECISION, POINTER :: field_XYZ(:,:,:), other_field_XYZ(:,:,:)
    DOUBLE PRECISION, POINTER :: field_XZ(:,:), other_field_XZ(:,:)
    DOUBLE PRECISION, POINTER :: field_YZ(:,:), other_field_YZ(:,:)
    
    DOUBLE PRECISION, POINTER :: field2D_sub(:), other_field2D_sub(:)
    DOUBLE PRECISION, POINTER :: field3D(:,:), other_field3D(:,:)
    DOUBLE PRECISION, POINTER :: field3D_sub(:,:), other_field3D_sub(:,:)
    DOUBLE PRECISION, POINTER :: field3D_recv(:,:), other_field3D_recv(:,:)
    DOUBLE PRECISION, POINTER :: pressure(:,:), other_pressure(:,:), pressure_shifted(:,:)

    DOUBLE PRECISION, POINTER :: field2D_W(:,:), other_field2D_W(:,:)
    DOUBLE PRECISION, POINTER :: field_XW(:,:), other_field_XW(:,:)
    DOUBLE PRECISION, POINTER :: field_YW(:,:), other_field_YW(:,:)
    DOUBLE PRECISION, POINTER :: field_ZW(:,:), other_field_ZW(:,:)
    DOUBLE PRECISION, POINTER :: field_XYW(:,:,:), other_field_XYW(:,:,:)
    DOUBLE PRECISION, POINTER :: field_XYZW(:,:,:,:), other_field_XYZW(:,:,:,:)
    DOUBLE PRECISION, POINTER :: field_XZW(:,:,:), other_field_XZW(:,:,:)
    DOUBLE PRECISION, POINTER :: field_YZW(:,:,:), other_field_YZW(:,:,:)
    
    DOUBLE PRECISION, POINTER :: field2D_sub_W(:,:), other_field2D_sub_W(:,:)
    DOUBLE PRECISION, POINTER :: field3D_W(:,:,:), other_field3D_W(:,:,:)
    DOUBLE PRECISION, POINTER :: field3D_sub_W(:,:,:), other_field3D_sub_W(:,:,:)
    DOUBLE PRECISION, POINTER :: field3D_recv_W(:,:,:), other_field3D_recv_W(:,:,:)
    DOUBLE PRECISION, POINTER :: pressure_W(:,:,:), other_pressure_W(:,:,:)



    
    TYPE(xios_duration) :: freq_op_recv, freq_offset_recv
    INTEGER :: ni,nj,nk
    INTEGER :: i,j,k,xy,x,y,z,w
    DOUBLE PRECISION :: scale,dist
    LOGICAL :: ok
    INTEGER :: ierr      

    LOGICAL :: ok_field2D, ok_field3D, ok_pressure_shifted, ok_pressure, ok_field2D_sub, ok_field3D_sub,ok_field3D_recv, ok_field3D_send
    LOGICAL :: ok_field_X, ok_field_Y, ok_field_XY, ok_field_Z, ok_field_XYZ, ok_field_XZ, ok_field_YZ
    LOGICAL :: ok_field2D_W, ok_field3D_W, ok_pressure_W, ok_field2D_sub_W, ok_field3D_sub_W,ok_field3D_recv_W, ok_field3D_send_W
    LOGICAL :: ok_field_XW, ok_field_YW, ok_field_XYW, ok_field_ZW, ok_field_XYZW, ok_field_XZW, ok_field_YZW

    LOGICAL :: ok_other_field2D, ok_other_field3D, ok_other_pressure, ok_other_field2D_sub, ok_other_field3D_sub, &
               ok_other_field3D_recv, ok_other_field3D_send
    LOGICAL :: ok_other_field_X, ok_other_field_Y, ok_other_field_XY, ok_other_field_Z, ok_other_field_XYZ, &
               ok_other_field_XZ, ok_other_field_YZ
    LOGICAL :: ok_other_field2D_W, ok_other_field3D_W, ok_other_pressure_W, ok_other_field2D_sub_W, ok_other_field3D_sub_W, &
               ok_other_field3D_recv_W, ok_other_field3D_send_W
    LOGICAL :: ok_other_field_XW, ok_other_field_YW, ok_other_field_XYW, ok_other_field_ZW, ok_other_field_XYZW, &
               ok_other_field_XZW, ok_other_field_YZW
    
      !! XIOS Initialization (get the local communicator)
    CALL xios_initialize(trim(model_id),return_comm=comm)
    CALL MPI_COMM_RANK(comm,rank,ierr)
    CALL MPI_COMM_SIZE(comm,size_loc,ierr)
    CALL xios_context_initialize(trim(model_id),comm)
    CALL xios_get_handle(trim(model_id),ctx_hdl)
    CALL xios_set_current_context(ctx_hdl)
    
    CALL init_model_params('',params)
    CALL init_model_params('other_',other_params)
   !!! Definition du découpage domain/axis

   
   !!! Definition de la start date et du timestep
    CALL xios_set_start_date(xios_date_convert_from_string(start_date//" 00:00:00"))
    dtime=xios_duration_convert_from_string(TRIM(params%timestep))
    CALL xios_set_timestep(timestep=dtime)

     !!! Calcul de temps elaps par seconde pour respecter le SYPD (hyp : pas de delai d'I/O)
    CALL xios_get_start_date(cdate)
    edate=cdate+xios_duration_convert_from_string(TRIM(duration))
    timestep_in_seconds=xios_date_convert_to_seconds(cdate+dtime) - xios_date_convert_to_seconds(cdate)
    simulated_seconds_per_seconds=sypd * 365 
    elapsed_per_timestep=timestep_in_seconds/simulated_seconds_per_seconds ! in seconds


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!             standard initialisation of domain, axis, grid, field                               !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    CALL init_domain("domain", comm, params, ni, nj, lon, lat, domain_mask, domain_index, &
                                                     X_lon, X_lat, X_mask, X_index,       &
                                                     Y_lon, Y_lat, Y_mask, Y_index)
                                                     
    CALL init_axis("axis", comm, params, axis_value, axis_mask, axis_index)
    CALL init_ensemble("ensemble", comm, params, ensemble_value)

    CALL set_mask3d("grid3D",params, ni, nj, lon, lat , axis_value)
     !!! Fin de la definition du contexte

    ok_field3D_recv=xios_is_valid_field("field3D_recv").AND.xios_is_valid_field("field3D_resend") ;
    IF (ok_field3D_recv) THEN
      CALL xios_is_defined_field_attr("field3D_recv",freq_op=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("field3D_recv",freq_op=freq_op_recv)
       ELSE
         freq_op_recv%timestep=1
         CALL xios_set_field_attr("field3D_recv",freq_op=freq_op_recv)
      ENDIF
      CALL xios_is_defined_field_attr("field3D_recv",freq_offset=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("field3D_recv",freq_offset=freq_offset_recv)
      ELSE
         freq_offset_recv%timestep=0
         CALL xios_set_field_attr("field3D_recv",freq_op=freq_op_recv)
      ENDIF
      CALL xios_set_field_attr("field3D_resend",freq_op=freq_op_recv,freq_offset=freq_offset_recv)
    ENDIF
    
    ok_field3D_recv_W=xios_is_valid_field("field3D_recv_W").AND.xios_is_valid_field("field3D_resend_W") ;
    IF (ok_field3D_recv_W) THEN
      CALL xios_is_defined_field_attr("field3D_recv_W",freq_op=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("field3D_recv_W",freq_op=freq_op_recv)
       ELSE
         freq_op_recv%timestep=1
         CALL xios_set_field_attr("field3D_recv_W",freq_op=freq_op_recv)
      ENDIF
      CALL xios_is_defined_field_attr("field3D_recv_W",freq_offset=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("field3D_recv_W",freq_offset=freq_offset_recv)
      ELSE
         freq_offset_recv%timestep=0
         CALL xios_set_field_attr("field3D_recv_W",freq_op=freq_op_recv)
      ENDIF
      CALL xios_set_field_attr("field3D_resend_W",freq_op=freq_op_recv,freq_offset=freq_offset_recv)
    ENDIF


    CALL init_field2D(comm, params, lon, lat, domain_mask, field2D_init, &
                      x_lon, x_lat, x_mask, fieldX_init, y_lon, y_lat, y_mask, fieldY_init, fieldXY_init)

    xy=size(domain_index)
    x=size(X_index)
    y=size(Y_index)
    z=size(axis_index)
    w=size(ensemble_value)


    ALLOCATE(field2D(0:xy-1))
    ALLOCATE(field3D(0:xy-1,0:z-1))
    ALLOCATE(pressure_shifted(0:xy-1,0:z-1))
    ALLOCATE(pressure(0:xy-1,0:z-1))
    ALLOCATE(field3D_recv(0:xy-1,0:z-1))
    ALLOCATE(field_Z(0:z-1))
    ALLOCATE(field_X(0:x-1))
    ALLOCATE(field_Y(0:y-1))
    ALLOCATE(field_XY(0:x-1,0:y-1))
    ALLOCATE(field_XYZ(0:x-1,0:y-1,0:z-1))
    ALLOCATE(field_XZ(0:x-1,0:z-1))
    ALLOCATE(field_YZ(0:y-1,0:z-1))

    ALLOCATE(field2D_W(0:xy-1,0:w-1))
    ALLOCATE(field3D_W(0:xy-1,0:z-1,0:w-1))
    ALLOCATE(pressure_W(0:xy-1,0:z-1,0:w-1))
    ALLOCATE(field3D_recv_W(0:xy-1,0:z-1,0:w-1))
    ALLOCATE(field_ZW(0:z-1,0:w-1))
    ALLOCATE(field_XW(0:x-1,0:w-1))
    ALLOCATE(field_YW(0:y-1,0:w-1))
    ALLOCATE(field_XYW(0:x-1,0:y-1,0:w-1))
    ALLOCATE(field_XYZW(0:x-1,0:y-1,0:z-1,0:w-1))
    ALLOCATE(field_XZW(0:x-1,0:z-1,0:w-1))
    ALLOCATE(field_YZW(0:y-1,0:z-1,0:w-1))
    


    DO i=0,xy-1
      IF (domain_index(i)/=-1) THEN
        field2D(i)=field2D_init(domain_index(i))
      ENDIF
    ENDDO

    DO i=0,x-1
      IF (X_index(i)/=-1) THEN
        field_X(i)=fieldX_init(X_index(i))
      ENDIF
    ENDDO

    DO i=0,y-1
      IF (Y_index(i)/=-1) THEN
        field_Y(i)=fieldY_init(Y_index(i))
      ENDIF
    ENDDO

    DO j=0,y-1
      DO i=0,x-1
        IF (Y_index(j)/=-1 .AND. X_index(i)/=-1) THEN
          field_XY(i,j)=fieldXY_init(X_index(i),Y_index(j))
        ENDIF
      ENDDO
    ENDDO

    DO i=0,z-1
      IF (axis_index(i)/=-1) THEN
        k=axis_index(i)
        IF (axis_mask(k)) THEN
          field_Z(i)=axis_value(axis_index(k))
          field3D(:,i)=field2D(:)*axis_value(axis_index(k))
          field_XYZ(:,:,i)=field_XY(:,:)*axis_value(axis_index(k))
          field_XZ(:,i)=field_X(:)*axis_value(axis_index(k))
          field_YZ(:,i)=field_Y(:)*axis_value(axis_index(k))
        ENDIF
      ENDIF
    ENDDO
         
    pressure=1e20
    DO j=0,z-1
      pressure(:,j)=axis_value(j) * 100000;
      DO i=0,xy-1
        IF (domain_index(i)/=-1) THEN
          k=domain_index(i)
          IF (domain_mask(k)) THEN
            dist=sqrt((lat(k)/90.)**2+(lon(k)/180.)**2) ;
            pressure(i,j)=pressure(i,j)*(1+params%pressure_factor*exp(-(4*dist)**2))
            pressure_shifted(i,j)=pressure(i,j)+5000
          ENDIF
        ENDIF
      ENDDO
    ENDDO
    


    field2D_W(:,0) = field2D(:)*(1+0.1*ensemble_value(0))
    field3D_W(:,:,0)= field3D(:,:)*(1+0.1*ensemble_value(0))
    pressure_W(:,:,0) = pressure(:,:)*(1+0.1*ensemble_value(0))
    field_XW(:,0) = field_X(:)*(1+0.1*ensemble_value(0))
    field_YW(:,0) = field_Y(:)*(1+0.1*ensemble_value(0))
    field_XYW(:,:,0) = field_XY(:,:)*(1+0.1*ensemble_value(0))
    field_ZW(:,0) = field_Z(:)*(1+0.1*ensemble_value(0))
    field_XYZW(:,:,:,0) = field_XYZ(:,:,:)*(1+0.1*ensemble_value(0))
    field_XZW(:,:,0) = field_XZ(:,:)*(1+0.1*ensemble_value(0))
    field_YZW(:,:,0) = field_YZ(:,:)*(1+0.1*ensemble_value(0))
    
    ok_field2D=xios_is_valid_field("field2D") ;
    ok_field3D=xios_is_valid_field("field3D") ;
    ok_pressure_shifted=xios_is_valid_field("pressure_shifted") ;    
    ok_pressure=xios_is_valid_field("pressure") ;
    ok_field2D_sub=xios_is_valid_field("field2D_sub") ;
    ok_field3D_sub=xios_is_valid_field("field3D_sub") ;
    ok_field_X=xios_is_valid_field("field_X") ;
    ok_field_Y=xios_is_valid_field("field_Y") ;
    ok_field_XY=xios_is_valid_field("field_XY") ;
    ok_field_Z=xios_is_valid_field("field_Z") ; 
    ok_field_XYZ=xios_is_valid_field("field_XYZ") ;
    ok_field_XZ=xios_is_valid_field("field_XZ") ;
    ok_field_YZ=xios_is_valid_field("field_YZ") ;

    ok_field2D_W=xios_is_valid_field("field2D_W") ;
    ok_field3D_W=xios_is_valid_field("field3D_W") ;
    ok_pressure_W=xios_is_valid_field("pressure_W") ;
    ok_field2D_sub_W=xios_is_valid_field("field2D_sub_W") ;
    ok_field3D_sub_W=xios_is_valid_field("field3D_sub_W") ;
    ok_field_XW=xios_is_valid_field("field_XW") ;
    ok_field_YW=xios_is_valid_field("field_YW") ;
    ok_field_XYW=xios_is_valid_field("field_XYW") ;
    ok_field_ZW=xios_is_valid_field("field_ZW") ; 
    ok_field_XYZW=xios_is_valid_field("field_XYZW") ;
    ok_field_XZW=xios_is_valid_field("field_XZW") ;
    ok_field_YZW=xios_is_valid_field("field_YZW") ;



    IF (ASSOCIATED(lon)) DEALLOCATE(lon)
    IF (ASSOCIATED(lat)) DEALLOCATE(lat)
    IF (ASSOCIATED(axis_value)) DEALLOCATE(axis_value)
    IF (ASSOCIATED(domain_mask)) DEALLOCATE(domain_mask)
    IF (ASSOCIATED(domain_index)) DEALLOCATE(domain_index)
    IF (ASSOCIATED(axis_mask)) DEALLOCATE(axis_mask)
    IF (ASSOCIATED(axis_index)) DEALLOCATE(axis_index)
    IF (ASSOCIATED(ensemble_value)) DEALLOCATE(ensemble_value)
    IF (ASSOCIATED(X_lon)) DEALLOCATE(X_lon)
    IF (ASSOCIATED(X_lat)) DEALLOCATE(X_lat)
    IF (ASSOCIATED(X_mask)) DEALLOCATE(X_mask)
    IF (ASSOCIATED(X_index)) DEALLOCATE(X_index)
    IF (ASSOCIATED(Y_lon)) DEALLOCATE(Y_lon)
    IF (ASSOCIATED(Y_lat)) DEALLOCATE(Y_lat)
    IF (ASSOCIATED(Y_mask)) DEALLOCATE(Y_mask)
    IF (ASSOCIATED(Y_index)) DEALLOCATE(Y_index)
    IF (ASSOCIATED(field2D_init)) DEALLOCATE(field2D_init)
    IF (ASSOCIATED(fieldX_init)) DEALLOCATE(fieldX_init)
    IF (ASSOCIATED(fieldY_init)) DEALLOCATE(fieldY_init)
    IF (ASSOCIATED(fieldXY_init)) DEALLOCATE(fieldXY_init)


!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!              duplicated section for other_                    !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    CALL init_domain("other_domain", comm, other_params, ni, nj, lon, lat, domain_mask, domain_index, &
                                                     X_lon, X_lat, X_mask, X_index,       &
                                                     Y_lon, Y_lat, Y_mask, Y_index)
                                                     
    CALL init_axis("other_axis", comm, other_params, axis_value, axis_mask, axis_index)
    CALL init_ensemble("other_ensemble", comm, other_params, ensemble_value)

    CALL set_mask3d("other_grid3D",other_params, ni, nj, lon, lat , axis_value)
     !!! Fin de la definition du contexte

    ok_other_field3D_recv=xios_is_valid_field("other_field3D_recv").AND.xios_is_valid_field("other_field3D_resend") ;
    IF (ok_other_field3D_recv) THEN
      CALL xios_is_defined_field_attr("other_field3D_recv",freq_op=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("other_field3D_recv",freq_op=freq_op_recv)
       ELSE
         freq_op_recv%timestep=1
         CALL xios_set_field_attr("other_field3D_recv",freq_op=freq_op_recv)
      ENDIF
      CALL xios_is_defined_field_attr("other_field3D_recv",freq_offset=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("other_field3D_recv",freq_offset=freq_offset_recv)
      ELSE
         freq_offset_recv%timestep=0
         CALL xios_set_field_attr("other_field3D_recv",freq_op=freq_op_recv)
      ENDIF
      CALL xios_set_field_attr("other_field3D_resend",freq_op=freq_op_recv,freq_offset=freq_offset_recv)
    ENDIF
    
    ok_other_field3D_recv_W=xios_is_valid_field("other_field3D_recv_W").AND.xios_is_valid_field("other_field3D_resend_W") ;
    IF (ok_other_field3D_recv_W) THEN
      CALL xios_is_defined_field_attr("other_field3D_recv_W",freq_op=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("other_field3D_recv_W",freq_op=freq_op_recv)
       ELSE
         freq_op_recv%timestep=1
         CALL xios_set_field_attr("other_field3D_recv_W",freq_op=freq_op_recv)
      ENDIF
      CALL xios_is_defined_field_attr("other_field3D_recv_W",freq_offset=ok)
      IF (ok) THEN
        CALL xios_get_field_attr("other_field3D_recv_W",freq_offset=freq_offset_recv)
      ELSE
         freq_offset_recv%timestep=0
         CALL xios_set_field_attr("other_field3D_recv_W",freq_op=freq_op_recv)
      ENDIF
      CALL xios_set_field_attr("other_field3D_resend_W",freq_op=freq_op_recv,freq_offset=freq_offset_recv)
    ENDIF


    CALL init_field2D(comm, other_params, lon, lat, domain_mask, field2D_init, &
                      x_lon, x_lat, x_mask, fieldX_init, y_lon, y_lat, y_mask, fieldY_init, fieldXY_init)

    xy=size(domain_index)
    x=size(X_index)
    y=size(Y_index)
    z=size(axis_index)
    w=size(ensemble_value)

    ALLOCATE(other_field2D(0:xy-1))
    ALLOCATE(other_field3D(0:xy-1,0:z-1))
    ALLOCATE(other_pressure(0:xy-1,0:z-1))
    ALLOCATE(other_field3D_recv(0:xy-1,0:z-1))
    ALLOCATE(other_field_Z(0:z-1))
    ALLOCATE(other_field_X(0:x-1))
    ALLOCATE(other_field_Y(0:y-1))
    ALLOCATE(other_field_XY(0:x-1,0:y-1))
    ALLOCATE(other_field_XYZ(0:x-1,0:y-1,0:z-1))
    ALLOCATE(other_field_XZ(0:x-1,0:z-1))
    ALLOCATE(other_field_YZ(0:y-1,0:z-1))

    ALLOCATE(other_field2D_W(0:xy-1,0:w-1))
    ALLOCATE(other_field3D_W(0:xy-1,0:z-1,0:w-1))
    ALLOCATE(other_pressure_W(0:xy-1,0:z-1,0:w-1))
    ALLOCATE(other_field3D_recv_W(0:xy-1,0:z-1,0:w-1))
    ALLOCATE(other_field_ZW(0:z-1,0:w-1))
    ALLOCATE(other_field_XW(0:x-1,0:w-1))
    ALLOCATE(other_field_YW(0:y-1,0:w-1))
    ALLOCATE(other_field_XYW(0:x-1,0:y-1,0:w-1))
    ALLOCATE(other_field_XYZW(0:x-1,0:y-1,0:z-1,0:w-1))
    ALLOCATE(other_field_XZW(0:x-1,0:z-1,0:w-1))
    ALLOCATE(other_field_YZW(0:y-1,0:z-1,0:w-1))
    


    DO i=0,xy-1
      IF (domain_index(i)/=-1) THEN
        other_field2D(i)=field2D_init(domain_index(i))
      ENDIF
    ENDDO

    DO i=0,x-1
      IF (X_index(i)/=-1) THEN
        other_field_X(i)=fieldX_init(X_index(i))
      ENDIF
    ENDDO

    DO i=0,y-1
      IF (Y_index(i)/=-1) THEN
        other_field_Y(i)=fieldY_init(Y_index(i))
      ENDIF
    ENDDO

    DO j=0,y-1
      DO i=0,x-1
        IF (Y_index(j)/=-1 .AND. X_index(i)/=-1) THEN
          other_field_XY(i,j)=fieldXY_init(X_index(i),Y_index(j))
        ENDIF
      ENDDO
    ENDDO

    DO i=0,z-1
      IF (axis_index(i)/=-1) THEN
        k=axis_index(i)
        IF (axis_mask(k)) THEN
          other_field_Z(i)=axis_value(axis_index(k))
          other_field3D(:,i)=other_field2D(:)*axis_value(axis_index(k))
          other_field_XYZ(:,:,i)=other_field_XY(:,:)*axis_value(axis_index(k))
          other_field_XZ(:,i)=other_field_X(:)*axis_value(axis_index(k))
          other_field_YZ(:,i)=other_field_Y(:)*axis_value(axis_index(k))
        ENDIF
      ENDIF
    ENDDO
         
    other_pressure=1e20
    DO j=0,z-1
      other_pressure(:,j)=axis_value(j) * 100000 ;
      DO i=0,xy-1
        IF (domain_index(i)/=-1) THEN
          k=domain_index(i)
          IF (domain_mask(k)) THEN
            dist=sqrt((lat(k)/90.)**2+(lon(k)/180.)**2) ;
            other_pressure(i,j)=other_pressure(i,j)*(1+other_params%pressure_factor*exp(-(4*dist)**2))
          ENDIF
        ENDIF
      ENDDO
    ENDDO
    


    other_field2D_W(:,0) = other_field2D(:)*(1+0.1*ensemble_value(0))
    other_field3D_W(:,:,0)= other_field3D(:,:)*(1+0.1*ensemble_value(0))
    other_pressure_W(:,:,0) = other_pressure(:,:)*(1+0.1*ensemble_value(0))
    other_field_XW(:,0) = other_field_X(:)*(1+0.1*ensemble_value(0))
    other_field_YW(:,0) = other_field_Y(:)*(1+0.1*ensemble_value(0))
    other_field_XYW(:,:,0) = other_field_XY(:,:)*(1+0.1*ensemble_value(0))
    other_field_ZW(:,0) = other_field_Z(:)*(1+0.1*ensemble_value(0))
    other_field_XYZW(:,:,:,0) = other_field_XYZ(:,:,:)*(1+0.1*ensemble_value(0))
    other_field_XZW(:,:,0) = other_field_XZ(:,:)*(1+0.1*ensemble_value(0))
    other_field_YZW(:,:,0) = other_field_YZ(:,:)*(1+0.1*ensemble_value(0))
    
    
    ok_other_field2D=xios_is_valid_field("other_field2D") ;
    ok_other_field3D=xios_is_valid_field("other_field3D") ;
    ok_other_pressure=xios_is_valid_field("other_pressure") ;
    ok_other_field2D_sub=xios_is_valid_field("other_field2D_sub") ;
    ok_other_field3D_sub=xios_is_valid_field("other_field3D_sub") ;
    ok_other_field_X=xios_is_valid_field("other_field_X") ;
    ok_other_field_Y=xios_is_valid_field("other_field_Y") ;
    ok_other_field_XY=xios_is_valid_field("other_field_XY") ;
    ok_other_field_Z=xios_is_valid_field("other_field_Z") ; 
    ok_other_field_XYZ=xios_is_valid_field("other_field_XYZ") ;
    ok_other_field_XZ=xios_is_valid_field("other_field_XZ") ;
    ok_other_field_YZ=xios_is_valid_field("other_field_YZ") ;

    ok_other_field2D_W=xios_is_valid_field("other_field2D_W") ;
    ok_other_field3D_W=xios_is_valid_field("other_field3D_W") ;
    ok_other_pressure_W=xios_is_valid_field("other_pressure_W") ;
    ok_other_field2D_sub_W=xios_is_valid_field("other_field2D_sub_W") ;
    ok_other_field3D_sub_W=xios_is_valid_field("other_field3D_sub_W") ;
    ok_other_field_XW=xios_is_valid_field("other_field_XW") ;
    ok_other_field_YW=xios_is_valid_field("other_field_YW") ;
    ok_other_field_XYZW=xios_is_valid_field("other_field_XYW") ;
    ok_other_field_ZW=xios_is_valid_field("other_field_ZW") ; 
    ok_other_field_XYZW=xios_is_valid_field("other_field_XYZW") ;
    ok_other_field_XZW=xios_is_valid_field("other_field_XZW") ;
    ok_other_field_YZW=xios_is_valid_field("other_field_YZW") ;


!!!!!!!!!!!!!!!!!!!!! end of duplicated section   !!!!!!!!!!!!!!!!!!!!!!!!!!

    ts=1
    cdate=cdate+dtime
    CALL xios_close_context_definition()
    CALL xios_set_current_context(trim(model_id))

    
    DO while ( cdate <= edate )
 
      !!! Mise a jour du pas de temps
      CALL xios_update_calendar(ts)


      IF (ok_field2D) CALL xios_send_field("field2D",field2D)
      IF (ok_field3D) CALL xios_send_field("field3D",field3D)
      IF (ok_pressure_shifted) CALL xios_send_field("pressure_shifted",pressure_shifted)
      IF (ok_pressure) CALL xios_send_field("pressure",pressure)
      IF (ok_field_X) CALL xios_send_field("field_X",field_X)
      IF (ok_field_Y) CALL xios_send_field("field_Y",field_Y)
      IF (ok_field_XY) CALL xios_send_field("field_XY",field_XY)
      IF (ok_field_Z) CALL xios_send_field("field_Z",field_Z)
      IF (ok_field_XYZ) CALL xios_send_field("field_XYZ",field_XYZ)
      IF (ok_field_XZ) CALL xios_send_field("field_XZ",field_XZ)
      IF (ok_field_YZ) CALL xios_send_field("field_YZ",field_YZ)
      
      IF ( MOD(params%field_sub_offset+ts-1,params%field_sub_freq)==0) THEN
        IF (ok_field2D_sub) CALL xios_send_field("field2D_sub",field2D*10)
        IF (ok_field3D_sub) CALL xios_send_field("field3D_sub",field3D*10)
      ENDIF

      IF (ok_field3D_recv) THEN
        IF (xios_field_is_active("field3D_resend",.TRUE.)) THEN
          CALL xios_recv_field("field3D_recv",field3D_recv)
          CALL xios_send_field("field3D_resend",field3D_recv)          
         ENDIF
      ENDIF

! ensemble
      IF (ok_field2D_W) CALL xios_send_field("field2D_W",field2D_W)
      IF (ok_field3D_W) CALL xios_send_field("field3D_W",field3D_W)
      IF (ok_pressure_W) CALL xios_send_field("pressure_W",pressure_W)
      IF (ok_field_XW) CALL xios_send_field("field_XW",field_XW)
      IF (ok_field_YW) CALL xios_send_field("field_YW",field_YW)
      IF (ok_field_XYW) CALL xios_send_field("field_XYW",field_XYW)
      IF (ok_field_ZW) CALL xios_send_field("field_ZW",field_ZW)
      IF (ok_field_XYZW) CALL xios_send_field("field_XYZW",field_XYZW)
      IF (ok_field_XZW) CALL xios_send_field("field_XZW",field_XZW)
      IF (ok_field_YZW) CALL xios_send_field("field_YZW",field_YZW)
      
      IF ( MOD(params%field_sub_offset+ts-1,params%field_sub_freq)==0) THEN
        IF (ok_field2D_sub_W) CALL xios_send_field("field2D_sub_W",field2D_W*10)
        IF (ok_field3D_sub_W) CALL xios_send_field("field3D_sub_W",field3D_W*10)
      ENDIF

      IF (ok_field3D_recv_W) THEN
        IF (xios_field_is_active("field3D_resend_W",.TRUE.)) THEN
          CALL xios_recv_field("field3D_recv_W",field3D_recv_W)
          CALL xios_send_field("field3D_resend_W",field3D_recv_W)          
         ENDIF
      ENDIF

      field2D=field2D+1
      field3D=field3D+1

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!              duplicated section for other_                    !
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


      IF (ok_other_field2D) CALL xios_send_field("other_field2D", other_field2D)
      IF (ok_other_field3D) CALL xios_send_field("other_field3D", other_field3D)
      IF (ok_other_pressure) CALL xios_send_field("other_pressure", other_pressure)
      IF (ok_other_field_X) CALL xios_send_field("other_field_X", other_field_X)
      IF (ok_other_field_Y) CALL xios_send_field("other_field_Y", other_field_Y)
      IF (ok_other_field_XY) CALL xios_send_field("other_field_XY", other_field_XY)
      IF (ok_other_field_Z) CALL xios_send_field("other_field_Z", other_field_Z)
      IF (ok_other_field_XY) CALL xios_send_field("other_field_XYZ", other_field_XYZ)
      IF (ok_other_field_XY) CALL xios_send_field("other_field_XZ", other_field_XZ)
      IF (ok_other_field_XY) CALL xios_send_field("other_field_YZ", other_field_YZ)
      
      IF ( MOD(other_params%field_sub_offset+ts-1,other_params%field_sub_freq)==0) THEN
        IF (ok_other_field2D_sub) CALL xios_send_field("other_field2D_sub",other_field2D*10)
        IF (ok_other_field3D_sub) CALL xios_send_field("other_field3D_sub",other_field3D*10)
      ENDIF

      IF (ok_other_field3D_recv) THEN
        IF (xios_field_is_active("other_field3D_resend",.TRUE.)) THEN
          CALL xios_recv_field("other_field3D_recv",other_field3D_recv)
          CALL xios_send_field("other_field3D_resend",other_field3D_recv)          
         ENDIF
      ENDIF

! ensemble
      IF (ok_other_field2D_W) CALL xios_send_field("other_field2D_W",other_field2D_W)
      IF (ok_other_field3D_W) CALL xios_send_field("other_field3D_W",other_field3D_W)
      IF (ok_other_pressure_W) CALL xios_send_field("other_pressure_W",other_pressure_W)
      IF (ok_other_field_XW) CALL xios_send_field("other_field_XW",other_field_XW)
      IF (ok_other_field_YW) CALL xios_send_field("other_field_YW",other_field_YW)
      IF (ok_other_field_XYW) CALL xios_send_field("other_field_XYW",other_field_XYW)
      IF (ok_other_field_ZW) CALL xios_send_field("other_field_ZW",other_field_ZW)
      IF (ok_other_field_XYW) CALL xios_send_field("other_field_XYZW",other_field_XYZW)
      IF (ok_other_field_XYW) CALL xios_send_field("other_field_XZW",other_field_XZW)
      IF (ok_other_field_XYW) CALL xios_send_field("other_field_YZW",other_field_YZW)
      
      IF ( MOD(other_params%field_sub_offset+ts-1,other_params%field_sub_freq)==0) THEN
        IF (ok_other_field2D_sub_W) CALL xios_send_field("other_field2D_sub_W",other_field2D_W*10)
        IF (ok_other_field3D_sub_W) CALL xios_send_field("other_field3D_sub_W",other_field3D_W*10)
      ENDIF

      IF (ok_other_field3D_recv_W) THEN
        IF (xios_field_is_active("other_field3D_resend_W",.TRUE.)) THEN
          CALL xios_recv_field("other_field3D_recv_W",other_field3D_recv_W)
          CALL xios_send_field("other_field3D_resend_W",other_field3D_recv_W)          
         ENDIF
      ENDIF

      other_field2D=other_field2D+1
      other_field3D=other_field3D+1


!!!!!!!!!!!!!!!!!!!!!! end of duplicated section !!!!!!!!!!!!!!!!!



      !! Boucle d'attente
      CALL wait_us(int(elapsed_per_timestep*1.e6))   ! micro-secondes
      cdate=cdate+dtime
      ts=ts+1
    ENDDO
   
    CALL xios_context_finalize()
    CALL MPI_COMM_FREE(comm, ierr)
    
  END SUBROUTINE model

  SUBROUTINE init_model_params(prefix,params)
  IMPLICIT NONE
    CHARACTER(LEN=*) :: prefix
    TYPE(tmodel_params) :: params


    IF (.NOT. xios_getvar(prefix//"timestep", params%timestep) )         params%timestep="1h"
    IF (.NOT. xios_getvar(prefix//"domain", params%domain) )             params%domain="lmdz"
    IF (.NOT. xios_getvar(prefix//"domain_mask", params%domain_mask) )   params%domain_mask=.FALSE.
    IF (.NOT. xios_getvar(prefix//"axis", params%axis) )                 params%axis="pressure"
    IF (.NOT. xios_getvar(prefix//"axis_mask", params%axis_mask) )       params%axis_mask=.FALSE.
    IF (.NOT. xios_getvar(prefix//"ni", params%ni) )                     params%ni=36
    IF (.NOT. xios_getvar(prefix//"nj", params%nj) )                     params%nj=18
    IF (.NOT. xios_getvar(prefix//"nlev", params%nlev) )                 params%nlev=10
    IF (.NOT. xios_getvar(prefix//"init_field2D", params%init_field2D) ) params%init_field2D="academic"
    IF (.NOT. xios_getvar(prefix//"pressure_factor", params%pressure_factor) ) params%pressure_factor=0.
    IF (.NOT. xios_getvar(prefix//"mask3d", params%mask3d) ) params%mask3d=.FALSE.
    IF (.NOT. xios_getvar(prefix//"field_sub_freq", params%field_sub_freq) ) params%field_sub_freq=1
    IF (.NOT. xios_getvar(prefix//"field_sub_offset", params%field_sub_offset) ) params%field_sub_offset=0

    IF (.NOT. xios_getvar(prefix//"domain_proc_n", params%domain_proc_n)) params%domain_proc_n=0
    IF (.NOT. xios_getvar(prefix//"axis_proc_n", params%axis_proc_n)) params%axis_proc_n=0
    IF (.NOT. xios_getvar(prefix//"ensemble_proc_n", params%ensemble_proc_n)) params%ensemble_proc_n=1
    IF ((.NOT. xios_getvar(prefix//"domain_proc_frac", params%domain_proc_frac)) .AND.  &
       (.NOT. xios_getvar("prefix//axis_proc_frac", params%axis_proc_frac))) THEN
       params%domain_proc_frac=1.0
       params%axis_proc_frac=0.0
    ELSE IF (.NOT. xios_getvar(prefix//"domain_proc_frac", params%domain_proc_frac)) THEN
      params%domain_proc_frac=0.0
    ELSE IF (.NOT. xios_getvar(prefix//"axis_proc_frac", params%axis_proc_frac)) THEN
      params%axis_proc_frac=0.0
    ENDIF
    
  END SUBROUTINE init_model_params

  
  SUBROUTINE init_domain(domain_id, comm, params, return_ni, return_nj,             &
                         return_lon, return_lat, return_mask, return_index,         &
                         return_X_lon,return_X_lat, return_X_mask, return_X_index,  &
                         return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)
  IMPLICIT NONE
    CHARACTER(LEN=*),INTENT(IN) :: domain_id
    TYPE(tmodel_params),INTENT(IN) :: params
    INTEGER,INTENT(IN) :: comm
    INTEGER,INTENT(OUT) :: return_ni
    INTEGER,INTENT(OUT) :: return_nj
    DOUBLE PRECISION, POINTER :: return_lon(:)
    DOUBLE PRECISION, POINTER :: return_lat(:)
    LOGICAL, POINTER :: return_mask(:)
    INTEGER, POINTER :: return_index(:)
    DOUBLE PRECISION, POINTER :: return_X_lon(:)
    DOUBLE PRECISION, POINTER :: return_X_lat(:)
    LOGICAL, POINTER :: return_X_mask(:)
    INTEGER, POINTER :: return_X_index(:)
    DOUBLE PRECISION, POINTER :: return_Y_lon(:)
    DOUBLE PRECISION, POINTER :: return_Y_lat(:)
    LOGICAL, POINTER :: return_Y_mask(:)
    INTEGER, POINTER :: return_Y_index(:)
       
    IF (params%domain=="lmdz") THEN
      CALL init_domain_lmdz(domain_id,comm,params, return_ni, return_nj,               &
                            return_lon, return_lat, return_mask, return_index,         &
                            return_X_lon,return_X_lat, return_X_mask, return_X_index,  &
                            return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)

    ELSE IF (params%domain=="orchidee") THEN
     CALL init_domain_orchidee(domain_id,comm,params, return_ni, return_nj,               &
                               return_lon, return_lat, return_mask, return_index,         &
                               return_X_lon,return_X_lat, return_X_mask, return_X_index,  &
                               return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)

    ELSE IF (params%domain=="nemo") THEN
       CALL init_domain_nemo(domain_id,comm,params, return_ni, return_nj,               &
                             return_lon, return_lat, return_mask, return_index,         &
                             return_X_lon,return_X_lat, return_X_mask, return_X_index,  &
                             return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)

     ELSE IF (params%domain=="dynamico") THEN
       CALL init_domain_dynamico(domain_id,comm,params, return_ni, return_nj,               &
                                 return_lon, return_lat, return_mask, return_index,         &
                                 return_X_lon,return_X_lat, return_X_mask, return_X_index,  &
                                 return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)

     ELSE IF (params%domain=="gaussian") THEN
       CALL init_domain_gaussian(domain_id,comm,params, return_ni, return_nj,               &
                                 return_lon, return_lat, return_mask, return_index,         &
                                 return_X_lon,return_X_lat, return_X_mask, return_X_index,  &
                                 return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)
    ENDIF
    
  END SUBROUTINE init_domain

  SUBROUTINE init_field2D(comm,params, lon, lat, mask, return_field,        &
                                       x_lon, x_lat, x_mask, return_fieldx, &
                                       y_lon, y_lat, y_mask, return_fieldy, return_fieldXY)
  IMPLICIT NONE
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    DOUBLE PRECISION, POINTER :: lon(:)
    DOUBLE PRECISION, POINTER :: lat(:)
    LOGICAL, POINTER :: mask(:)
    DOUBLE PRECISION, POINTER :: return_field(:)

    DOUBLE PRECISION, POINTER :: X_lon(:)
    DOUBLE PRECISION, POINTER :: X_lat(:)
    LOGICAL, POINTER :: X_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldX(:)

    DOUBLE PRECISION, POINTER :: Y_lon(:)
    DOUBLE PRECISION, POINTER :: Y_lat(:)
    LOGICAL, POINTER :: Y_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldY(:)
    DOUBLE PRECISION, POINTER :: return_fieldXY(:,:)
        
    IF (params%init_field2D=="academic") THEN
      CALL init_field2D_academic(comm,params, lon, lat, mask, return_field, X_lon, X_lat, X_mask, return_fieldX, &
                                Y_lon, Y_lat, Y_mask, return_fieldY, return_fieldXY)
    ELSE IF (params%init_field2D=="constant") THEN
      CALL init_field2D_constant(comm,params, lon, lat, mask, return_field, X_lon, X_lat, X_mask, return_fieldX, &
                                 Y_lon, Y_lat, Y_mask, return_fieldY, return_fieldXY)
    ELSE IF (params%init_field2D=="rank") THEN
      CALL init_field2D_rank(comm,params, lon, lat, mask, return_field, X_lon, X_lat, X_mask, &
                             return_fieldX, Y_lon, Y_lat, Y_mask, return_fieldY, return_fieldXY)
    ENDIF
    
  END SUBROUTINE init_field2D

  
  SUBROUTINE init_axis(axis_id,comm,params, return_value, return_mask, return_index)
  IMPLICIT NONE
    CHARACTER(LEN=*) :: axis_id
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    DOUBLE PRECISION, POINTER :: return_value(:)
    LOGICAL, POINTER          :: return_mask(:)
    INTEGER, POINTER          :: return_index(:)
    
    IF (params%axis=="pressure") THEN
      CALL init_axis_pressure(axis_id,comm,params, return_value, return_mask, return_index)
    ENDIF
    
   END SUBROUTINE init_axis
    
  SUBROUTINE init_ensemble(ensemble_id,comm,params, return_value)
  IMPLICIT NONE
    CHARACTER(LEN=*) :: ensemble_id
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    DOUBLE PRECISION, POINTER :: return_value(:)
    INTEGER :: domain_proc_rank, domain_proc_size    
    INTEGER :: axis_proc_rank, axis_proc_size
    INTEGER :: ensemble_proc_size, ensemble_proc_rank

    CALL get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                           ensemble_proc_size, ensemble_proc_rank)
    ALLOCATE(return_value(0:0))
    return_value(0)=ensemble_proc_rank

    IF (xios_is_valid_axis(TRIM(ensemble_id))) THEN
      CALL xios_set_axis_attr(ensemble_id, n_glo=ensemble_proc_size, begin=ensemble_proc_rank, n=1, value=return_value(:), &
                              unit='-')    
    ENDIF
    
   END SUBROUTINE init_ensemble
   

  SUBROUTINE init_domain_gaussian(domain_id, comm, params, return_ni, return_nj,               &
                                  return_lon,return_lat,return_mask, return_index,             &
                                  return_X_lon,return_X_lat, return_X_mask, return_X_index,    &
                                  return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)
  IMPLICIT NONE 
    CHARACTER(LEN=*) :: domain_id
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    INTEGER :: return_ni
    INTEGER :: return_nj
    DOUBLE PRECISION, POINTER :: return_lon(:)
    DOUBLE PRECISION, POINTER :: return_lat(:)
    LOGICAL, POINTER :: return_mask(:)
    INTEGER, POINTER :: return_index(:)
    DOUBLE PRECISION, POINTER :: return_X_lon(:)
    DOUBLE PRECISION, POINTER :: return_X_lat(:)
    LOGICAL, POINTER :: return_X_mask(:)
    INTEGER, POINTER :: return_X_index(:)
    DOUBLE PRECISION, POINTER :: return_Y_lon(:)
    DOUBLE PRECISION, POINTER :: return_Y_lat(:)
    LOGICAL, POINTER :: return_Y_mask(:)
    INTEGER, POINTER :: return_Y_index(:)
    INTEGER :: domain_proc_rank, domain_proc_size    
    INTEGER :: axis_proc_rank, axis_proc_size
    INTEGER :: ensemble_proc_size, ensemble_proc_rank

    INTEGER :: mpi_rank, mpi_size
    INTEGER ::  ierr
    
!  INTEGER, PARAMETER :: nlon=60
!  INTEGER, PARAMETER :: nlat=30
!  INTEGER,PARAMETER :: ni_glo=100
!  INTEGER,PARAMETER :: nj_glo=100
!  INTEGER,PARAMETER :: llm=5
!  DOUBLE PRECISION  :: lval(llm)=1
!  TYPE(xios_field) :: field_hdl
!  TYPE(xios_fieldgroup) :: fieldgroup_hdl
!  TYPE(xios_file) :: file_hdl
!  LOGICAL :: ok

!  DOUBLE PRECISION,ALLOCATABLE :: lon_glo(:),lat_glo(:)
!  DOUBLE PRECISION,ALLOCATABLE :: bounds_lon_glo(:,:),bounds_lat_glo(:,:)
!  DOUBLE PRECISION,ALLOCATABLE :: field_A_glo(:,:)
!  INTEGER,ALLOCATABLE :: i_index_glo(:)
!  INTEGER,ALLOCATABLE :: i_index(:)
!  LOGICAL,ALLOCATABLE :: mask_glo(:),mask(:)
!  INTEGER,ALLOCATABLE :: n_local(:),local_neighbor(:,:)
!  DOUBLE PRECISION,ALLOCATABLE :: lon(:),lat(:),field_A_srf(:,:), lonvalue(:) ;
!  DOUBLE PRECISION,ALLOCATABLE :: bounds_lon(:,:),bounds_lat(:,:) ;
!  INTEGER :: ni,ibegin,iend,nj,jbegin,jend
!  INTEGER :: i,j,l,ts,n, nbMax
!  INTEGER :: ncell_glo,ncell,ind
!  REAL :: ilon,ilat
!  DOUBLE PRECISION, PARAMETER :: Pi=3.14159265359
!  INTEGER :: list_ind(nlon,nlat)
!  INTEGER :: rank,j1,j2,np,ncell_x
!  INTEGER :: data_n_index
!  INTEGER,ALLOCATABLE :: data_i_index(:)
!  DOUBLE PRECISION,ALLOCATABLE :: field_A_compressed(:,:)


    INTEGER :: nlon, nlat
    DOUBLE PRECISION,ALLOCATABLE :: lon_glo(:),lat_glo(:)
    DOUBLE PRECISION,ALLOCATABLE :: bounds_lon_glo(:,:),bounds_lat_glo(:,:)
    INTEGER,ALLOCATABLE :: i_index_glo(:)
    INTEGER,ALLOCATABLE :: i_index(:)
    LOGICAL,ALLOCATABLE :: mask_glo(:),mask(:)
    DOUBLE PRECISION,ALLOCATABLE :: lon(:),lat(:),field_A_srf(:,:), lonvalue(:) ;
    DOUBLE PRECISION,ALLOCATABLE :: bounds_lon(:,:),bounds_lat(:,:) ;

    INTEGER :: ni,ibegin,iend,nj,jbegin,jend
    INTEGER :: i,j,l,ts,n, nbMax
    INTEGER :: ncell_glo,ncell,ind
    REAL :: ilon,ilat
    DOUBLE PRECISION, PARAMETER :: Pi=3.14159265359
    INTEGER,ALLOCATABLE :: list_ind(:,:)
    INTEGER :: rank,j1,j2,np,ncell_x
    INTEGER :: data_n_index
    INTEGER,ALLOCATABLE :: data_i_index(:)



    CALL MPI_COMM_RANK(comm,mpi_rank,ierr)
    CALL MPI_COMM_SIZE(comm,mpi_size,ierr)

    CALL get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                           ensemble_proc_size, ensemble_proc_rank)

    mpi_rank=domain_proc_rank
    mpi_size=domain_proc_size
    nlon=params%ni
    nlat=params%nj

    
    ncell_glo=0
    DO j=1,nlat
      n =  NINT(COS(Pi/2-(j-0.5)*PI/nlat)*nlon)
      IF (n<8) n=8
      ncell_glo=ncell_glo+n
    ENDDO

    ALLOCATE(lon_glo(ncell_glo))
    ALLOCATE(lat_glo(ncell_glo))
    ALLOCATE(bounds_lon_glo(4,ncell_glo))
    ALLOCATE(bounds_lat_glo(4,ncell_glo))
    ALLOCATE(i_index_glo(ncell_glo))
    ALLOCATE(mask_glo(ncell_glo))
    ALLOCATE(list_ind(nlon,nlat))
    
    ind=0
    DO j=1,nlat
      n = NINT(COS(Pi/2-(j-0.5)*PI/nlat)*nlon)
      if (j==1) PRINT*,"--- ",n
      if (j==nlat) PRINT*,"--- ",n
      IF (n<8) n=8

      DO i=1,n
        ind=ind+1
        list_ind(i,j)=ind
        ilon=i-0.5
        ilat=j-0.5

        lat_glo(ind)= 90-(ilat*180./nlat)
        lon_glo(ind)= (ilon*360./n)-180.


        bounds_lat_glo(1,ind)= 90-((ilat-0.5)*180./nlat)
        bounds_lon_glo(1,ind)=((ilon-0.5)*360./n)-180.

        bounds_lat_glo(2,ind)= 90-((ilat-0.5)*180./nlat)
        bounds_lon_glo(2,ind)=((ilon+0.5)*360./n)-180.

        bounds_lat_glo(3,ind)= 90-((ilat+0.5)*180./nlat)
        bounds_lon_glo(3,ind)=((ilon+0.5)*360./n)-180.

        bounds_lat_glo(4,ind)= 90-((ilat+0.5)*180./nlat)
        bounds_lon_glo(4,ind)=((ilon-0.5)*360./n)-180.

      ENDDO
    ENDDO

!  mpi_size=32
    rank=(mpi_size-1)/2
    ncell_x=sqrt(ncell_glo*1./mpi_size)

    j1=nlat/2
    DO WHILE(rank>=0)
      j2=MAX(j1-ncell_x+1,1)
      j=(j1+j2)/2
      n=NINT(COS(Pi/2-(j-0.5)*PI/nlat)*nlon)
      np = MIN(n/ncell_x,rank+1) ;
      if (j2==1) np=rank+1
 
      PRINT *,"domain ",j2,j1,rank,np ;
      DO j=j2,j1
        n=NINT(COS(Pi/2-(j-0.5)*PI/nlat)*nlon)
        IF (n<8) n=8
        DO i=1,n
          ind=list_ind(i,j)
          IF ( (i-1) < MOD(n,np)*(n/np+1)) THEN  
            i_index_glo(ind) = rank - (i-1)/(n/np+1)
          ELSE
            i_index_glo(ind) = rank-(MOD(n,np)+ (i-1-MOD(n,np)*(n/np+1))/(n/np))
          ENDIF
        ENDDO
      ENDDO
      rank=rank-np
      j1=j2-1
    ENDDO

    rank=(mpi_size-1)/2+1
    ncell_x=sqrt(ncell_glo*1./mpi_size)

    j1=nlat/2+1
    DO WHILE(rank<=mpi_size-1)
      j2=MIN(j1+ncell_x-1,nlat)
      j=(j1+j2)/2
      n=NINT(COS(Pi/2-(j-0.5)*PI/nlat)*nlon)
      np = MIN(n/ncell_x,mpi_size-rank) ;
      if (j2==nlat) np=mpi_size-rank

      PRINT *,"domain ",j2,j1,rank,np ;
      DO j=j1,j2
        n=NINT(COS(Pi/2-(j-0.5)*PI/nlat)*nlon)
        IF (n<8) n=8
        DO i=1,n
          ind=list_ind(i,j)
          IF ( (i-1) < MOD(n,np)*(n/np+1)) THEN
            i_index_glo(ind) = rank + (i-1)/(n/np+1)
          ELSE
            i_index_glo(ind) = rank+(MOD(n,np)+ (i-1-MOD(n,np)*(n/np+1))/(n/np))
          ENDIF
        ENDDO
      ENDDO
      rank=rank+np
      j1=j2+1
   ENDDO

    ncell=0
    DO ind=1,ncell_glo
      IF (i_index_glo(ind)==mpi_rank) ncell=ncell+1
    ENDDO
    ALLOCATE(i_index(ncell))
    ALLOCATE(lon(ncell))
    ALLOCATE(lat(ncell))
    ALLOCATE(bounds_lon(4,ncell))
    ALLOCATE(bounds_lat(4,ncell))
!    ALLOCATE(field_A_srf(ncell,llm))
    ALLOCATE(mask(ncell))
    ncell=0
    data_n_index=0
    DO ind=1,ncell_glo
      IF (i_index_glo(ind)==mpi_rank) THEN
        ncell=ncell+1
        i_index(ncell)=ind-1
        lon(ncell)=lon_glo(ind)
        lat(ncell)=lat_glo(ind)
        bounds_lon(:,ncell)=bounds_lon_glo(:,ind)
        bounds_lat(:,ncell)=bounds_lat_glo(:,ind)
        field_A_srf(ncell,:)=i_index_glo(ind)
        IF (MOD(ind,8)>=0 .AND. MOD(ind,8)<2) THEN
!        mask(ncell)=.FALSE.

         mask(ncell)=.TRUE.
          data_n_index=data_n_index+1
        ELSE
          mask(ncell)=.TRUE.
          data_n_index=data_n_index+1
        ENDIF
      ENDIF
    ENDDO

!    ALLOCATE(field_A_compressed(data_n_index,llm))
    ALLOCATE(data_i_index(data_n_index))
    data_n_index=0
    DO ind=1,ncell
      IF (mask(ind)) THEN
        data_n_index=data_n_index+1
        data_i_index(data_n_index)=ind-1
!        field_A_compressed(data_n_index,:)=field_A_srf(ind,:)
      ENDIF
    ENDDO

    ALLOCATE(return_lon(0:ncell-1))
    ALLOCATE(return_lat(0:ncell-1))
    ALLOCATE(return_mask(0:ncell-1))
    ALLOCATE(return_index(0:data_n_index-1))
    return_lon(0:ncell-1)=lon(1:ncell)    
    return_lat(0:ncell-1)=lat(1:ncell)
    return_index(0:data_n_index-1)= data_i_index(1:data_n_index) 
    CALL set_domain_mask(params, lon, lat, return_mask)


    ALLOCATE(return_X_lon(0:ncell-1))
    ALLOCATE(return_X_lat(0:ncell-1))
    ALLOCATE(return_X_mask(0:ncell-1))
    ALLOCATE(return_X_index(0:ncell-1))
    
    return_X_lon=return_lon
    return_X_lat=return_lat
    return_X_index=return_index
    CALL set_domain_mask(params, return_X_lon,return_X_lat, return_X_mask)


    ALLOCATE(return_Y_lon(0:0))
    ALLOCATE(return_Y_lat(0:0))
    ALLOCATE(return_Y_mask(0:0))
    ALLOCATE(return_Y_index(0:0))

    return_Y_lon(0)=lon_glo(ncell_glo/2)
    return_Y_lat(0)=lat_glo(ncell_glo/2)
    CALL set_domain_mask(params, return_Y_lon,return_Y_lat, return_Y_mask)
    return_Y_index(0)=0

    return_ni=ncell
    return_nj=1


    IF (xios_is_valid_domain(TRIM(domain_id))) THEN
      CALL xios_set_domain_attr(TRIM(domain_id), type="unstructured", ni_glo=ncell_glo, ni=ncell, ibegin=0, i_index=i_index)
      CALL xios_set_domain_attr(TRIM(domain_id), data_dim=1, data_ni=data_n_index, data_i_index=data_i_index, mask_1d=return_mask)
      CALL xios_set_domain_attr(TRIM(domain_id), lonvalue_1D=lon, latvalue_1D=lat, nvertex=4, bounds_lon_1D=bounds_lon, &
                                bounds_lat_1D=bounds_lat)
    ENDIF

    IF (xios_is_valid_axis(TRIM(domain_id)//"_X")) THEN
      CALL xios_set_axis_attr(TRIM(domain_id)//"_X", n_glo=ncell_glo, n=ncell, begin=0, index=i_index,value=return_X_lon)
      CALL xios_set_axis_attr(TRIM(domain_id)//"_X", data_n=data_n_index, data_index=data_i_index, mask=return_X_mask)
    ENDIF
    
    IF (xios_is_valid_axis(TRIM(domain_id)//"_Y")) THEN    
      CALL xios_set_axis_attr(TRIM(domain_id)//"_Y", n_glo=1, begin=0, n=1, value=return_Y_lat, mask=return_Y_mask)
    ENDIF



  END SUBROUTINE init_domain_gaussian



  SUBROUTINE init_domain_dynamico(domain_id, comm, params, return_ni, return_nj,           &
                              return_lon,return_lat,return_mask, return_index,             &
                              return_X_lon,return_X_lat, return_X_mask, return_X_index,    &
                              return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)
  IMPLICIT NONE 
    CHARACTER(LEN=*) :: domain_id
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    INTEGER :: return_ni
    INTEGER :: return_nj
    DOUBLE PRECISION, POINTER :: return_lon(:)
    DOUBLE PRECISION, POINTER :: return_lat(:)
    LOGICAL, POINTER :: return_mask(:)
    INTEGER, POINTER :: return_index(:)
    DOUBLE PRECISION, POINTER :: return_X_lon(:)
    DOUBLE PRECISION, POINTER :: return_X_lat(:)
    LOGICAL, POINTER :: return_X_mask(:)
    INTEGER, POINTER :: return_X_index(:)
    DOUBLE PRECISION, POINTER :: return_Y_lon(:)
    DOUBLE PRECISION, POINTER :: return_Y_lat(:)
    LOGICAL, POINTER :: return_Y_mask(:)
    INTEGER, POINTER :: return_Y_index(:)
    INTEGER :: domain_proc_rank, domain_proc_size    
    INTEGER :: axis_proc_rank, axis_proc_size
    INTEGER :: ensemble_proc_size, ensemble_proc_rank

    INTEGER :: mpi_rank, mpi_size
    INTEGER ::  ierr
    INTEGER :: ni,nj,ni_glo,nj_glo,nvertex
    INTEGER :: ibegin,jbegin
    INTEGER :: nbp,nbp_glo, offset
    DOUBLE PRECISION, ALLOCATABLE :: lon_glo(:), lat_glo(:), lon(:), lat(:)
    DOUBLE PRECISION, ALLOCATABLE :: bounds_lon_glo(:,:), bounds_lat_glo(:,:), bounds_lon(:,:), bounds_lat(:,:)
    LOGICAL,ALLOCATABLE :: mask(:)
    LOGICAL,ALLOCATABLE :: dom_mask(:)
    INTEGER :: i,j
    INTEGER,ALLOCATABLE :: ibegin_all(:), ni_all(:)
       
    CALL MPI_COMM_RANK(comm,mpi_rank,ierr)
    CALL MPI_COMM_SIZE(comm,mpi_size,ierr)

    CALL get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                           ensemble_proc_size, ensemble_proc_rank)

    CALL xios_get_current_context(ctx_hdl)
    
    CALL xios_context_initialize("grid_dynamico",comm)
    CALL xios_close_context_definition()
    CALL xios_get_domain_attr("domain_dynamico",ni_glo=ni_glo,nj_glo=nj_glo,ni=ni,nj=nj, ibegin=ibegin, jbegin=jbegin , &
                              nvertex=nvertex)
    ALLOCATE(lon(ni),lat(ni),bounds_lon(nvertex,ni),bounds_lat(nvertex,ni))
    CALL xios_get_domain_attr("domain_dynamico", lonvalue_1d=lon, latvalue_1d=lat, bounds_lon_1d=bounds_lon, &
                               bounds_lat_1d=bounds_lat)
    CALL xios_context_finalize

    CALL xios_set_current_context(ctx_hdl)

    
    ALLOCATE(ibegin_all(mpi_size))
    ALLOCATE(ni_all(mpi_size))
    ALLOCATE(lon_glo(0:ni_glo-1))
    ALLOCATE(lat_glo(0:ni_glo-1))
    ALLOCATE(bounds_lon_glo(nvertex,0:ni_glo-1))
    ALLOCATE(bounds_lat_glo(nvertex,0:ni_glo-1))
    
    CALL MPI_Allgather(ibegin, 1, MPI_INTEGER, ibegin_all, 1, MPI_INTEGER, comm, ierr)
    CALL MPI_Allgather(ni, 1, MPI_INTEGER, ni_all, 1, MPI_INTEGER, comm, ierr)

    CALL MPI_AllgatherV(lon, ni, MPI_REAL8, lon_glo, ni_all, ibegin_all, MPI_REAL8, comm, ierr) 
    CALL MPI_AllgatherV(lat, ni, MPI_REAL8, lat_glo, ni_all, ibegin_all, MPI_REAL8, comm, ierr) 
    CALL MPI_AllgatherV(bounds_lon, ni*nvertex, MPI_REAL8, bounds_lon_glo, ni_all*nvertex, ibegin_all*nvertex, &
                        MPI_REAL8, comm, ierr) 
    CALL MPI_AllgatherV(bounds_lat, ni*nvertex, MPI_REAL8, bounds_lat_glo, ni_all*nvertex, ibegin_all*nvertex, &
                        MPI_REAL8, comm, ierr) 

    
    nbp_glo=ni_glo
    nbp=nbp_glo/domain_proc_size
    IF (domain_proc_rank < MOD(nbp_glo,domain_proc_size) ) THEN
      nbp=nbp+1
      offset=nbp*domain_proc_rank
    ELSE
      offset=nbp*domain_proc_rank + MOD(nbp_glo, domain_proc_size)
    ENDIF

    DEALLOCATE(lat,lon,bounds_lon,bounds_lat)
    ALLOCATE(lat(0:nbp-1))
    ALLOCATE(lon(0:nbp-1))
    ALLOCATE(bounds_lon(nvertex,0:nbp-1))
    ALLOCATE(bounds_lat(nvertex,0:nbp-1))
    ALLOCATE(return_lon(0:nbp-1))
    ALLOCATE(return_lat(0:nbp-1))
    ALLOCATE(return_index(0:nbp-1))

    DO i=0,nbp-1
      lat(i)=lat_glo(i+offset)
      lon(i)=lon_glo(i+offset)
      bounds_lon(:,i) = bounds_lon_glo(:,i+offset) 
      bounds_lat(:,i) = bounds_lat_glo(:,i+offset)
      return_index(i)=i 
    ENDDO
    return_lon=lon
    return_lat=lat
    
    ALLOCATE(return_mask(0:nbp-1))
    CALL set_domain_mask(params, lon, lat, return_mask)


    ALLOCATE(return_X_lon(0:nbp-1))
    ALLOCATE(return_X_lat(0:nbp-1))
    ALLOCATE(return_X_mask(0:nbp-1))
    ALLOCATE(return_X_index(0:nbp-1))
    
    DO i=0,nbp-1
      return_X_lon(i)=lon_glo(i+offset)
      return_X_lat(i)=lat_glo(i+offset)
    ENDDO
    CALL set_domain_mask(params, return_X_lon,return_X_lat, return_X_mask)
    DO i=0,nbp-1
      return_X_index(i)=i
    ENDDO

    ALLOCATE(return_Y_lon(0:0))
    ALLOCATE(return_Y_lat(0:0))
    ALLOCATE(return_Y_mask(0:0))
    ALLOCATE(return_Y_index(0:0))

    return_Y_lon(0)=lon_glo(nbp_glo/2)
    return_Y_lat(0)=lat_glo(nbp_glo/2)
    CALL set_domain_mask(params, return_Y_lon,return_Y_lat, return_Y_mask)
    return_Y_index(0)=0
 

    
    return_ni=nbp
    return_nj=1

    IF (xios_is_valid_domain(TRIM(domain_id))) THEN
      CALL xios_set_domain_attr(TRIM(domain_id), type="unstructured", ni_glo=ni_glo, ibegin=offset, ni=nbp, nvertex=nvertex)
      CALL xios_set_domain_attr(TRIM(domain_id), data_dim=1, lonvalue_1d=lon, latvalue_1d=lat, bounds_lon_1d=bounds_lon, &
                                bounds_lat_1d=bounds_lat, mask_1d=return_mask)
    ENDIF    

    IF (xios_is_valid_axis(TRIM(domain_id)//"_X")) THEN
      CALL xios_set_axis_attr(TRIM(domain_id)//"_X", n_glo=ni_glo, begin=offset, n=nbp, value=return_X_lon)
    ENDIF

    IF (xios_is_valid_axis(TRIM(domain_id)//"_Y")) THEN    
      CALL xios_set_axis_attr(TRIM(domain_id)//"_Y", n_glo=1, begin=0, n=1, value=return_Y_lat, mask=return_Y_mask)
    ENDIF

   END SUBROUTINE init_domain_dynamico
    



  SUBROUTINE init_domain_lmdz(domain_id, comm, params, return_ni, return_nj,               &
                              return_lon,return_lat,return_mask, return_index,             &
                              return_X_lon,return_X_lat, return_X_mask, return_X_index,    &
                              return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)
  IMPLICIT NONE 
    CHARACTER(LEN=*) :: domain_id
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    INTEGER :: return_ni
    INTEGER :: return_nj
    DOUBLE PRECISION, POINTER :: return_lon(:)
    DOUBLE PRECISION, POINTER :: return_lat(:)
    LOGICAL, POINTER :: return_mask(:)
    INTEGER, POINTER :: return_index(:)
    DOUBLE PRECISION, POINTER :: return_X_lon(:)
    DOUBLE PRECISION, POINTER :: return_X_lat(:)
    LOGICAL, POINTER :: return_X_mask(:)
    INTEGER, POINTER :: return_X_index(:)
    DOUBLE PRECISION, POINTER :: return_Y_lon(:)
    DOUBLE PRECISION, POINTER :: return_Y_lat(:)
    LOGICAL, POINTER :: return_Y_mask(:)
    INTEGER, POINTER :: return_Y_index(:)
    INTEGER :: domain_proc_rank, domain_proc_size    
    INTEGER :: axis_proc_rank, axis_proc_size
    INTEGER :: ensemble_proc_size, ensemble_proc_rank

    INTEGER :: mpi_rank, mpi_size
    INTEGER ::  ierr
    INTEGER :: ni,nj,ni_glo,nj_glo
    INTEGER :: ibegin,jbegin
    INTEGER :: nbp,nbp_glo, offset
    DOUBLE PRECISION, ALLOCATABLE :: lon_glo(:), lat_glo(:), lon(:), lat(:)
    LOGICAL,ALLOCATABLE :: mask(:)
    LOGICAL,ALLOCATABLE :: dom_mask(:)
    INTEGER :: i,j
       
    CALL MPI_COMM_RANK(comm,mpi_rank,ierr)
    CALL MPI_COMM_SIZE(comm,mpi_size,ierr)

    CALL get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                           ensemble_proc_size, ensemble_proc_rank)
    ni_glo=params%ni
    nj_glo=params%nj
    nbp_glo=ni_glo*nj_glo
    nbp=nbp_glo/domain_proc_size
    IF (domain_proc_rank < MOD(nbp_glo,domain_proc_size) ) THEN
     nbp=nbp+1
     offset=nbp*domain_proc_rank
    ELSE
      offset=nbp*domain_proc_rank + MOD(nbp_glo, domain_proc_size)
    ENDIF
    
    
    ibegin=0 ; ni=ni_glo
    jbegin=offset / ni_glo
    
    nj = (offset+nbp-1) / ni_glo - jbegin + 1 
    
    offset=offset-jbegin*ni
    
    ALLOCATE(lon(0:ni-1), lat(0:nj-1), mask(0:ni*nj-1), dom_mask(0:ni*nj-1))
    mask(:)=.FALSE.
    mask(offset:offset+nbp-1)=.TRUE.
    
    ALLOCATE(lon_glo(0:ni_glo-1), lat_glo(0:nj_glo-1))
    
    DO i=0,ni_glo-1
      lon_glo(i)=-180+(i+0.5)*(360./ni_glo)
    ENDDO

    DO j=0,nj_glo-1
      lat_glo(j)=-90+(j+0.5)*(180./nj_glo)
    ENDDO
     
    lon(:)=lon_glo(:)
    lat(:)=lat_glo(jbegin:jbegin+nj-1)

    ALLOCATE(return_lon(0:ni*nj-1))
    ALLOCATE(return_lat(0:ni*nj-1))
    ALLOCATE(return_mask(0:ni*nj-1))
    ALLOCATE(return_index(0:ni*nj-1))

    ALLOCATE(return_X_lon(0:ni-1))
    ALLOCATE(return_X_lat(0:ni-1))
    ALLOCATE(return_X_mask(0:ni-1))
    ALLOCATE(return_X_index(0:ni-1))

    ALLOCATE(return_Y_lon(0:nj-1))
    ALLOCATE(return_Y_lat(0:nj-1))
    ALLOCATE(return_Y_mask(0:nj-1))
    ALLOCATE(return_Y_index(0:nj-1))

    DO j=0,nj-1
      DO i=0,ni-1
        return_lon(i+j*ni)=lon(i)
        return_lat(i+j*ni)=lat(j)
        return_index(i+j*ni)=i+j*ni
      ENDDO
    ENDDO

    CALL set_domain_mask(params, return_lon,return_lat, dom_mask)
    
    return_mask = mask .AND. dom_mask

    return_X_lat(:)=lat_glo(nj_glo/2)
    return_X_lon(:)=lon_glo(:)
    CALL set_domain_mask(params, return_X_lon,return_X_lat, return_X_mask)
    DO i=0,ni-1
      return_X_index(i)=i
    ENDDO

    return_Y_lon(:)=lon_glo(ni_glo/2)
    return_Y_lat(:)=lat_glo(jbegin:jbegin+nj-1)
    CALL set_domain_mask(params, return_Y_lon,return_Y_lat, return_Y_mask)

    DO j=0,nj-1
      return_Y_index(j)=j
    ENDDO

    return_ni=ni
    return_nj=nj

    IF (xios_is_valid_domain(TRIM(domain_id))) THEN
      CALL xios_set_domain_attr(TRIM(domain_id), type="rectilinear", ni_glo=ni_glo, ibegin=ibegin, ni=ni, nj_glo=nj_glo, &
                                jbegin=jbegin, nj=nj)
      CALL xios_set_domain_attr(TRIM(domain_id), data_dim=2, lonvalue_1d=lon, latvalue_1d=lat, mask_1d=return_mask)
    ENDIF
    
    IF (xios_is_valid_axis(TRIM(domain_id)//"_X")) THEN
      CALL xios_set_axis_attr(TRIM(domain_id)//"_X", n_glo=ni_glo, begin=ibegin, n=ni, value=return_X_lon)
    ENDIF

    IF (xios_is_valid_axis(TRIM(domain_id)//"_Y")) THEN    
      CALL xios_set_axis_attr(TRIM(domain_id)//"_Y", n_glo=nj_glo, begin=jbegin, n=nj, value=return_Y_lat)
    ENDIF

  END SUBROUTINE init_domain_lmdz


  SUBROUTINE init_domain_orchidee(domain_id, comm, params, return_ni, return_nj,               &
                                  return_lon,return_lat,return_mask, return_index,             &
                                  return_X_lon,return_X_lat, return_X_mask, return_X_index,    &
                                  return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)
  IMPLICIT NONE 
    CHARACTER(LEN=*) :: domain_id
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    INTEGER :: return_ni
    INTEGER :: return_nj
    DOUBLE PRECISION, POINTER :: return_lon(:)
    DOUBLE PRECISION, POINTER :: return_lat(:)
    LOGICAL, POINTER :: return_mask(:)
    INTEGER, POINTER :: return_index(:)
    DOUBLE PRECISION, POINTER :: return_X_lon(:)
    DOUBLE PRECISION, POINTER :: return_X_lat(:)
    LOGICAL, POINTER :: return_X_mask(:)
    INTEGER, POINTER :: return_X_index(:)
    DOUBLE PRECISION, POINTER :: return_Y_lon(:)
    DOUBLE PRECISION, POINTER :: return_Y_lat(:)
    LOGICAL, POINTER :: return_Y_mask(:)
    INTEGER, POINTER :: return_Y_index(:)
    INTEGER :: domain_proc_rank, domain_proc_size    
    INTEGER :: axis_proc_rank, axis_proc_size
    INTEGER :: ensemble_proc_size, ensemble_proc_rank

    INTEGER :: mpi_rank, mpi_size
    INTEGER ::  ierr
    INTEGER :: ni,nj,ni_glo,nj_glo
    INTEGER :: ibegin,jbegin
    INTEGER :: nbp,nbp_glo, offset
    DOUBLE PRECISION, ALLOCATABLE :: lon_glo(:), lat_glo(:), lon(:), lat(:)
    LOGICAL,ALLOCATABLE :: mask(:)
    INTEGER :: i,j, ij, pos, i_glo, j_glo, ij_begin, ij_end
       
    CALL MPI_COMM_RANK(comm,mpi_rank,ierr)
    CALL MPI_COMM_SIZE(comm,mpi_size,ierr)

    CALL get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                           ensemble_proc_size, ensemble_proc_rank)
    ni_glo=params%ni
    nj_glo=params%nj
    nbp_glo=ni_glo*nj_glo
    nbp=nbp_glo/domain_proc_size
    IF (domain_proc_rank < MOD(nbp_glo,domain_proc_size) ) THEN
     nbp=nbp+1
     offset=nbp*domain_proc_rank
    ELSE
      offset=nbp*domain_proc_rank + MOD(nbp_glo, domain_proc_size)
    ENDIF
    
    
    ibegin=0 ; ni=ni_glo
    jbegin=offset / ni_glo
    
    nj = (offset+nbp-1) / ni_glo - jbegin + 1 
    
    offset=offset-jbegin*ni

    ij_begin=offset+jbegin*ni
    ij_end=ij_begin+nbp-1
    
    ALLOCATE(lon(0:ni-1), lat(0:nj-1), mask(0:ni*nj-1))
    mask(:)=.FALSE.
    mask(offset:offset+nbp-1)=.TRUE.
    
    ALLOCATE(lon_glo(0:ni_glo-1), lat_glo(0:nj_glo-1))
    
    DO i=0,ni_glo-1
      lon_glo(i)=-180+(i+0.5)*(360./ni_glo)
    ENDDO

    DO j=0,nj_glo-1
      lat_glo(j)=-90+(j+0.5)*(180./nj_glo)
    ENDDO
     
    lon(:)=lon_glo(:)
    lat(:)=lat_glo(jbegin:jbegin+nj-1)

    ALLOCATE(return_lon(0:ni*nj-1))
    ALLOCATE(return_lat(0:ni*nj-1))
    ALLOCATE(return_mask(0:ni*nj-1))

    ALLOCATE(return_X_lon(0:ni-1))
    ALLOCATE(return_X_lat(0:ni-1))
    ALLOCATE(return_X_mask(0:ni-1))

    ALLOCATE(return_Y_lon(0:nj-1))
    ALLOCATE(return_Y_lat(0:nj-1))
    ALLOCATE(return_Y_mask(0:nj-1))


     DO j=0,nj-1
      DO i=0,ni-1
        return_lon(i+j*ni)=lon(i)
        return_lat(i+j*ni)=lat(j)
      ENDDO
    ENDDO

    pos=0
    DO j=0,nj-1
      DO i=0,ni-1
        i_glo=i
        j_glo=jbegin+j
        ij=j*ni+i
        IF ( ij>=ij_begin .AND. ij<=ij_end) THEN
           IF ((MOD(j_glo,3)==1 .OR. MOD(j_glo,3)==2) .AND. (MOD(i_glo,5)==3 .OR. MOD(i_glo,5)==4)) CYCLE
           pos=pos+1
        ENDIF
      ENDDO
   ENDDO

   ALLOCATE(return_index(0:pos-1))
   return_index(:)=-1
   pos=0
    DO j=0,nj-1
      DO i=0,ni-1
        i_glo=i
        j_glo=jbegin+j
        ij=j*ni+i
        IF ( ij>=ij_begin .AND. ij<=ij_end) THEN
           IF ((MOD(j_glo,3)==1 .OR. MOD(j_glo,3)==2) .AND. (MOD(i_glo,5)==3 .OR. MOD(i_glo,5)==4)) CYCLE
            return_index(pos)=i+j*ni
           pos=pos+1
        ENDIF
      ENDDO
   ENDDO     

    CALL set_domain_mask(params, return_lon,return_lat, mask)

    return_mask=mask

    return_X_lat(:)=lat_glo(nj_glo/2)
    return_X_lon(:)=lon_glo(:)
    CALL set_domain_mask(params, return_X_lon,return_X_lat, return_X_mask)

   pos=0
    DO i=0,ni-1
      i_glo=i
      j_glo=nj_glo/2
      IF ((MOD(j_glo,3)==1 .OR. MOD(j_glo,3)==2) .AND. (MOD(i_glo,5)==3 .OR. MOD(i_glo,5)==4)) CYCLE
      pos=pos+1
    ENDDO

    ALLOCATE(return_X_index(0:pos-1))
    return_X_index(:)=-1
    pos=0
    DO i=0,ni-1
      i_glo=i
      j_glo=nj_glo/2
      IF ((MOD(j_glo,3)==1 .OR. MOD(j_glo,3)==2) .AND. (MOD(i_glo,5)==3 .OR. MOD(i_glo,5)==4)) CYCLE
      return_X_index(pos)=i
      pos=pos+1
    ENDDO 


    
    return_Y_lon(:)=lon_glo(ni_glo/2)
    return_Y_lat(:)=lat_glo(jbegin:jbegin+nj-1)
    CALL set_domain_mask(params, return_Y_lon,return_Y_lat, return_Y_mask)

    pos=0
    DO j=0,nj-1
      i_glo=ni_glo/2
      j_glo=j+jbegin
      IF ((MOD(j_glo,3)==1 .OR. MOD(j_glo,3)==2) .AND. (MOD(i_glo,5)==3 .OR. MOD(i_glo,5)==4)) CYCLE
      pos=pos+1
    ENDDO

    ALLOCATE(return_Y_index(0:pos-1))
    return_Y_index=-1
    pos=0
    DO j=0,nj-1
      i_glo=ni_glo/2
      j_glo=j+jbegin
      IF ((MOD(j_glo,3)==1 .OR. MOD(j_glo,3)==2) .AND. (MOD(i_glo,5)==3 .OR. MOD(i_glo,5)==4)) CYCLE
      return_Y_index(pos)=j
      pos=pos+1
    ENDDO

    return_ni=ni
    return_nj=nj

    IF (xios_is_valid_domain(TRIM(domain_id))) THEN
      CALL xios_set_domain_attr(TRIM(domain_id), type="rectilinear", ni_glo=ni_glo, ibegin=ibegin, ni=ni, nj_glo=nj_glo, &
                                jbegin=jbegin, nj=nj)
      CALL xios_set_domain_attr(TRIM(domain_id), data_dim=1, data_ni=size(return_index), data_i_index=return_index)
      CALL xios_set_domain_attr(TRIM(domain_id), lonvalue_1d=lon, latvalue_1d=lat, mask_1d=mask)
    ENDIF
    
    IF (xios_is_valid_axis(TRIM(domain_id)//"_X")) THEN
      CALL xios_set_axis_attr(TRIM(domain_id)//"_X", n_glo=ni_glo, begin=ibegin, n=ni, value=return_X_lon, &
                              data_n=size(return_X_index), data_index=return_X_index)
    ENDIF

    IF (xios_is_valid_axis(TRIM(domain_id)//"_Y")) THEN    
      CALL xios_set_axis_attr(TRIM(domain_id)//"_Y", n_glo=nj_glo, begin=jbegin, n=nj, value=return_Y_lat, &
                              data_n=size(return_Y_index), data_index=return_Y_index)
    ENDIF

  END SUBROUTINE init_domain_orchidee



  SUBROUTINE init_domain_nemo(domain_id, comm, params, return_ni, return_nj,               &
                              return_lon,return_lat,return_mask, return_index,             &
                              return_X_lon,return_X_lat, return_X_mask, return_X_index,    &
                              return_Y_lon,return_Y_lat, return_Y_mask, return_Y_index)
  IMPLICIT NONE 
    CHARACTER(LEN=*) :: domain_id
    TYPE(tmodel_params) :: params
    TYPE(xios_context) :: ctx_hdl
    INTEGER :: comm
    INTEGER :: return_ni
    INTEGER :: return_nj
    DOUBLE PRECISION, POINTER :: return_lon(:)
    DOUBLE PRECISION, POINTER :: return_lat(:)
    LOGICAL, POINTER :: return_mask(:)
    INTEGER, POINTER :: return_index(:)
    DOUBLE PRECISION, POINTER :: return_X_lon(:)
    DOUBLE PRECISION, POINTER :: return_X_lat(:)
    LOGICAL, POINTER :: return_X_mask(:)
    INTEGER, POINTER :: return_X_index(:)
    DOUBLE PRECISION, POINTER :: return_Y_lon(:)
    DOUBLE PRECISION, POINTER :: return_Y_lat(:)
    LOGICAL, POINTER :: return_Y_mask(:)
    INTEGER, POINTER :: return_Y_index(:)
    INTEGER :: domain_proc_rank, domain_proc_size    
    INTEGER :: axis_proc_rank, axis_proc_size
    INTEGER :: ensemble_proc_size, ensemble_proc_rank

    INTEGER :: mpi_rank, mpi_size
    INTEGER ::  ierr
    INTEGER :: ni,nj,ni_glo,nj_glo
    INTEGER :: ibegin,jbegin
    INTEGER :: offset_i, offset_j
    DOUBLE PRECISION, ALLOCATABLE :: lon_glo(:), lat_glo(:), bounds_lon_glo(:,:), bounds_lat_glo(:,:)
    DOUBLE PRECISION, ALLOCATABLE :: lon(:,:), lat(:,:), bounds_lon(:,:,:), bounds_lat(:,:,:) 
    LOGICAL,ALLOCATABLE :: mask(:)
    INTEGER :: i,j, ij, n, rank
    INTEGER :: nproc_i, nproc_j, nholes, pos_hole
    INTEGER,ALLOCATABLE :: size_i(:), begin_i(:), size_j(:), begin_j(:)
       
    CALL MPI_COMM_RANK(comm,mpi_rank,ierr)
    CALL MPI_COMM_SIZE(comm,mpi_size,ierr)

    CALL get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                           ensemble_proc_size, ensemble_proc_rank)
    ni_glo=params%ni
    nj_glo=params%nj

    n=INT(SQRT(mpi_size*1.))
    nproc_i=n
    nproc_j=n
    IF ( n*n == mpi_size) THEN
    ! do nothing
    ELSE IF ( (n+1)*n < mpi_size) THEN
      nproc_i=nproc_i+1
      nproc_j=nproc_j+1
    ELSE 
      nproc_i=nproc_i+1
    ENDIF
    
    nholes=nproc_i*nproc_j-mpi_size

    ALLOCATE(size_i(0:nproc_i-1))
    ALLOCATE(begin_i(0:nproc_i-1))
    DO i=0,nproc_i-1
      size_i(i)=ni_glo/nproc_i
      IF (i<MOD(ni_glo,nproc_i)) size_i(i)=size_i(i)+1
      IF (i==0) THEN
        begin_i(i)=0
      ELSE
        begin_i(i)=begin_i(i-1)+size_i(i-1)
      ENDIF
    ENDDO
    
    ALLOCATE(size_j(0:nproc_j-1))
    ALLOCATE(begin_j(0:nproc_j-1))
    DO j=0,nproc_i-1
      size_j(j)=nj_glo/nproc_j
      IF (j<MOD(nj_glo,nproc_j)) size_j(j)=size_j(j)+1
      IF (j==0) THEN
        begin_j(j)=0
      ELSE
        begin_j(j)=begin_j(j-1)+size_j(j-1)
      ENDIF
    ENDDO


    pos_hole=0
    rank=0
    DO j=0,nproc_j-1
      DO i=0,nproc_i-1

        ij = j*nproc_i + i
        IF (pos_hole<nholes) THEN
          IF ( MOD(ij,(nproc_i*nproc_j/nholes)) == 0) THEN
            pos_hole=pos_hole+1
            CYCLE
          ENDIF
        ENDIF
        
        IF (mpi_rank==rank) THEN
          ibegin = begin_i(i)
          ni = size_i(i)
          jbegin = begin_j(j)
          nj = size_j(j)
        ENDIF 
        rank=rank+1
      ENDDO
    ENDDO

    ALLOCATE(lon_glo(0:ni_glo-1), lat_glo(0:nj_glo-1))
    ALLOCATE(bounds_lon_glo(4,0:ni_glo-1), bounds_lat_glo(4,0:nj_glo-1))
    
    DO i=0,ni_glo-1
      lon_glo(i)=-180+(i+0.5)*(360./ni_glo)
      bounds_lon_glo(1,i)= -180+(i)*(360./ni_glo)
      bounds_lon_glo(2,i)= -180+(i+1)*(360./ni_glo)
    ENDDO

    DO j=0,nj_glo-1
      lat_glo(j)=-90+(j+0.5)*(180./nj_glo)
      bounds_lat_glo(1,j)= -90+(j)*(180./nj_glo)
      bounds_lat_glo(2,j)= -90+(j+1)*(180./nj_glo)
    ENDDO

    offset_i=2    ! halo of 2 on i
    offset_j=1    ! halo of 1 on j

    ALLOCATE(lon(0:ni-1,0:nj-1))
    ALLOCATE(lat(0:ni-1,0:nj-1))
    ALLOCATE(bounds_lon(4,0:ni-1,0:nj-1))
    ALLOCATE(bounds_lat(4,0:ni-1,0:nj-1))
!    ALLOCATE(mask(0:ni-1,0:nj-1))
    
    ALLOCATE(return_lon(0:ni*nj-1))
    ALLOCATE(return_lat(0:ni*nj-1))
    ALLOCATE(return_mask(0:ni*nj-1))
    ALLOCATE(return_index(0:(ni+2*offset_i)*(nj+2*offset_j)-1))

    ALLOCATE(return_X_lon(0:ni-1))
    ALLOCATE(return_X_lat(0:ni-1))
    ALLOCATE(return_X_mask(0:ni-1))
    ALLOCATE(return_X_index(0:ni-1))

    ALLOCATE(return_Y_lon(0:nj-1))
    ALLOCATE(return_Y_lat(0:nj-1))
    ALLOCATE(return_Y_mask(0:nj-1))
    ALLOCATE(return_Y_index(0:nj-1))
    
    return_index=-1 
    DO j=0,nj-1
      DO i=0,ni-1
        ij=j*ni+i
        return_lon(ij)=lon_glo(ibegin+i)
        return_lat(ij)=lat_glo(jbegin+j)
        lon(i,j)=return_lon(ij)
        lat(i,j)=return_lat(ij)
        bounds_lon(1,i,j)=bounds_lon_glo(2,ibegin+i)
        bounds_lon(2,i,j)=bounds_lon_glo(1,ibegin+i)
        bounds_lon(3,i,j)=bounds_lon_glo(1,ibegin+i)
        bounds_lon(4,i,j)=bounds_lon_glo(2,ibegin+i)
        bounds_lat(1,i,j)=bounds_lat_glo(1,jbegin+j)
        bounds_lat(2,i,j)=bounds_lat_glo(1,jbegin+j)
        bounds_lat(3,i,j)=bounds_lat_glo(2,jbegin+j)
        bounds_lat(4,i,j)=bounds_lat_glo(2,jbegin+j)

        ij=(j+offset_j)*(ni+2*offset_i)+i+offset_i
        return_index(ij)=i+j*ni
      ENDDO
    ENDDO

    CALL set_domain_mask(params, return_lon,return_lat, return_mask)

    ALLOCATE(return_X_lon(0:ni-1))
    ALLOCATE(return_X_lat(0:ni-1))
    ALLOCATE(return_X_mask(0:ni-1))
    ALLOCATE(return_X_index(0:ni+2*offset_i-1))

    return_X_lat(:)=lat_glo(nj_glo/2)
    return_X_lon(:)=lon_glo(ibegin:ibegin+ni-1)
    CALL set_domain_mask(params, return_X_lon,return_X_lat, return_X_mask)

    return_X_index(:)=-1
    DO i=0,ni-1
      return_X_index(offset_i+i)=i
    ENDDO

    ALLOCATE(return_Y_lon(0:nj-1))
    ALLOCATE(return_Y_lat(0:nj-1))
    ALLOCATE(return_Y_mask(0:nj-1))
    ALLOCATE(return_Y_index(0:nj+2*offset_j-1))

    return_Y_lat(:)=lat_glo(jbegin:jbegin+nj-1)
    return_Y_lon(:)=lon_glo(ni_glo/2)
    CALL set_domain_mask(params, return_Y_lon,return_Y_lat, return_Y_mask)

    return_Y_index(:)=-1
    DO j=0,nj-1
      return_Y_index(offset_j+j)=j
    ENDDO

    return_ni=ni
    return_nj=nj

    IF (xios_is_valid_domain(TRIM(domain_id))) THEN
      CALL xios_set_domain_attr(TRIM(domain_id), type="curvilinear", data_dim=2)
      CALL xios_set_domain_attr(TRIM(domain_id), ni_glo=ni_glo, ibegin=ibegin, ni=ni, data_ibegin=-offset_i, data_ni=ni+2*offset_i)
      CALL xios_set_domain_attr(TRIM(domain_id), nj_glo=nj_glo, jbegin=jbegin, nj=nj, data_jbegin=-offset_j, data_nj=nj+2*offset_j)
      CALL xios_set_domain_attr(TRIM(domain_id), data_dim=2, lonvalue_2d=lon, latvalue_2d=lat, mask_1d=return_mask)
      CALL xios_set_domain_attr(TRIM(domain_id), bounds_lon_2d=bounds_lon, bounds_lat_2d=bounds_lat, nvertex=4)
    ENDIF

    
    IF (xios_is_valid_axis(TRIM(domain_id)//"_X")) THEN
      CALL xios_set_axis_attr(TRIM(domain_id)//"_X", n_glo=ni_glo, begin=ibegin, n=ni, data_begin=-offset_i, &
                              data_n=ni+2*offset_i, value=return_X_lon, mask=return_X_mask)
!      CALL xios_set_axis_attr(TRIM(domain_id)//"_X", n_glo=ni_glo, begin=ibegin, n=ni, data_index=return_X_index,&
!                               data_n=ni+2*offset_i,  value=return_X_lon)
    ENDIF

    IF (xios_is_valid_axis(TRIM(domain_id)//"_Y")) THEN    
      CALL xios_set_axis_attr(TRIM(domain_id)//"_Y", n_glo=nj_glo, begin=jbegin, n=nj, data_begin=-offset_j, &
                              data_n=nj+2*offset_j, value=return_Y_lat, mask=return_Y_mask)
!      CALL xios_set_axis_attr(TRIM(domain_id)//"_Y", n_glo=nj_glo, begin=jbegin, n=nj, data_index=return_Y_index, &
!                               data_n=nj+2*offset_j, value=return_Y_lat)
    ENDIF

  END SUBROUTINE init_domain_nemo




  
   SUBROUTINE set_domain_mask(params, lon,lat, mask)
   IMPLICIT NONE 
     TYPE(tmodel_params) :: params
     DOUBLE PRECISION  :: lon(:)
     DOUBLE PRECISION  :: lat(:)
     LOGICAL           :: mask(:)
     INTEGER :: i,x

     mask(:)=.TRUE.
     IF (params%domain_mask) THEN
       WHERE (lon(:)-2*lat(:)>-10 .AND. lon(:)-2*lat(:) <10) mask(:)=.FALSE.
       WHERE (2*lat(:)+lon(:)>-10 .AND. 2*lat(:)+lon(:)<10) mask(:)=.FALSE.
     ENDIF

  END SUBROUTINE set_domain_mask
     

  SUBROUTINE set_mask3d(grid_id, params, ni, nj, lon,lat, axis_value)
  IMPLICIT NONE
    CHARACTER(LEN=*) :: grid_id
    TYPE(tmodel_params) :: params
    INTEGER :: comm
    INTEGER :: ni
    INTEGER :: nj
    DOUBLE PRECISION, POINTER :: lon(:)
    DOUBLE PRECISION, POINTER :: lat(:)
    INTEGER, POINTER          :: domain_index(:)    
    DOUBLE PRECISION, POINTER :: axis_value(:)
    INTEGER, POINTER          :: axis_index(:)
    INTEGER ::i,j,ij,k,nk
    LOGICAL, ALLOCATABLE :: mask3d(:,:,:)
    DOUBLE PRECISION :: r

    nk=size(axis_value)

    ALLOCATE(mask3d(0:ni-1,0:nj-1,0:nk-1))

    mask3d=.TRUE.
    DO k=0,nk-1
      DO j=0,nj-1
        DO i=0,ni-1
          ij=j*ni+i
          r=sqrt((lon(ij)/2)**2 + lat(ij)**2) / ((nk-k)*1./nk) 
          if (r < 60) mask3d(i,j,k)=.FALSE.
        ENDDO
      ENDDO
    ENDDO

    IF (params%mask3d) CALL  xios_set_grid_attr(grid_id, mask_3d=mask3d)

  END SUBROUTINE set_mask3d
   
  SUBROUTINE init_axis_pressure(axis_id,comm,params, return_value, return_mask, return_index)
  IMPLICIT NONE
    CHARACTER(LEN=*) :: axis_id
    TYPE(tmodel_params) :: params
    INTEGER :: comm
    DOUBLE PRECISION, POINTER :: return_value(:)
    LOGICAL, POINTER          :: return_mask(:)
    INTEGER, POINTER          :: return_index(:)
    
    INTEGER :: nlev_glo
    INTEGER :: nlev, begin, end
    DOUBLE PRECISION, ALLOCATABLE :: value_glo(:) 
    DOUBLE PRECISION, ALLOCATABLE :: bounds_value_glo(:,:) 
    DOUBLE PRECISION, ALLOCATABLE :: value(:) 
    DOUBLE PRECISION, ALLOCATABLE :: bounds_value(:,:) 
    DOUBLE PRECISION :: dp
    INTEGER :: i

    INTEGER :: domain_proc_rank, domain_proc_size    
    INTEGER :: axis_proc_rank, axis_proc_size
    INTEGER :: ensemble_proc_size, ensemble_proc_rank

    CALL get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                           ensemble_proc_size, ensemble_proc_rank)     

    nlev_glo=params%nlev
    
    ALLOCATE(value_glo(0:nlev_glo-1), bounds_value_glo(2,0:nlev_glo-1) )
    
    dp=(1-0.1)/(nlev_glo-1)
    DO i=0,nlev_glo-1
     value_glo(i)=1-i*dp
    ENDDO
    
    bounds_value_glo(2,0)=value_glo(0)-(value_glo(1)-value_glo(0))/2
    DO i=1,nlev_glo-1
     bounds_value_glo(2,i)=(value_glo(i-1)+value_glo(i)) /2
    ENDDO

    DO i=0,nlev_glo-2
     bounds_value_glo(1,i)=(value_glo(i)+value_glo(i+1)) /2
    ENDDO
    bounds_value_glo(1,nlev_glo-1)=value_glo(nlev_glo-1)-(value_glo(nlev_glo-2)-value_glo(nlev_glo-1))/2

    nlev=nlev_glo/axis_proc_size
    IF (axis_proc_rank < MOD(nlev_glo,axis_proc_size)) THEN
      nlev=nlev+1
      begin= axis_proc_rank*nlev
      end=begin+nlev-1
    ELSE
      begin=MOD(nlev_glo,axis_proc_size)*(nlev+1) + (axis_proc_rank-MOD(nlev_glo,axis_proc_size))*nlev
      end=begin+nlev-1
    ENDIF

    ALLOCATE(value(0:nlev-1), bounds_value(2,0:nlev-1) )
    value(:)=value_glo(begin:end)
    bounds_value(:,:)=bounds_value_glo(:,begin:end)
    
    ALLOCATE(return_value(0:nlev-1))
    ALLOCATE(return_mask(0:nlev-1))
    return_value=value
    return_mask=.TRUE.
    CALL set_axis_mask(params,value,return_mask)    
    CALL xios_set_axis_attr(axis_id, n_glo=nlev_glo, begin=begin, n=nlev, value=value*100000, mask=return_mask, &
                            bounds=bounds_value*100000, unit='Pa', positive='up')    
   

    ALLOCATE(return_index(0:nlev-1))

    DO i=0,nlev-1
      return_index(i)=i
    ENDDO 


  END SUBROUTINE init_axis_pressure

  SUBROUTINE set_axis_mask(params, value, mask)
  IMPLICIT NONE
    TYPE(tmodel_params) :: params
     DOUBLE PRECISION  :: value(:)
     LOGICAL           :: mask(:)
     INTEGER :: i,x

     x=size(mask)
     IF (params%axis_mask) THEN
       DO i=0,x-1
         IF (MOD(i,3)==0) mask(i)=.FALSE.
         IF (MOD(i,4)==0) mask(i)=.FALSE.
       ENDDO
     ENDIF

  END SUBROUTINE set_axis_mask  

  SUBROUTINE init_field2D_academic(comm,params, lon, lat, mask, return_field,            &
                                   X_lon, X_lat, X_mask, return_fieldX,                  &
                                   Y_lon, Y_lat, Y_mask, return_fieldY, return_fieldXY)
  IMPLICIT NONE
    TYPE(tmodel_params) :: params
    INTEGER :: comm
    DOUBLE PRECISION, POINTER :: lon(:)
    DOUBLE PRECISION, POINTER :: lat(:)
    LOGICAL, POINTER :: mask(:)
    DOUBLE PRECISION, POINTER :: return_field(:)

    DOUBLE PRECISION, POINTER :: X_lon(:)
    DOUBLE PRECISION, POINTER :: X_lat(:)
    LOGICAL, POINTER :: X_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldX(:)

    DOUBLE PRECISION, POINTER :: Y_lon(:)
    DOUBLE PRECISION, POINTER :: Y_lat(:)
    LOGICAL, POINTER :: Y_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldY(:)
    DOUBLE PRECISION, POINTER :: return_fieldXY(:,:)
    
    DOUBLE PRECISION, PARAMETER :: coef=2., dp_pi=3.14159265359
    DOUBLE PRECISION :: dp_length, dp_conv
    INTEGER :: i,j,x,y,xy
    
     ! Parameters for analytical function
    dp_length= 1.2*dp_pi
    dp_conv=dp_pi/180.
    
    xy=size(mask)
    x=size(X_mask)
    y=size(Y_mask)

    ALLOCATE(return_field(0:xy-1))
    
    DO i=0,xy-1
      IF (mask(i)) THEN
         return_field(i)=(coef-SIN(dp_pi*(ACOS(COS(lat(i)*dp_conv)*&
                   COS(lon(i)*dp_conv))/dp_length)))
      ENDIF
    ENDDO        


    ALLOCATE(return_fieldX(0:x-1))
    
    DO i=0,x-1
      IF (X_mask(i)) THEN
         return_fieldX(i)=(coef-SIN(dp_pi*(ACOS(COS(X_lat(i)*dp_conv)*&
                            COS(X_lon(i)*dp_conv))/dp_length)))
      ENDIF
    ENDDO            


    ALLOCATE(return_fieldY(0:y-1))
    
    DO i=0,y-1
      IF (Y_mask(i)) THEN
         return_fieldY(i)=(coef-SIN(dp_pi*(ACOS(COS(Y_lat(i)*dp_conv)*&
                            COS(Y_lon(i)*dp_conv))/dp_length)))
      ENDIF
    ENDDO

    ALLOCATE(return_fieldXY(0:x-1,0:y-1))
    
    DO j=0,y-1
      DO i=0,x-1
        IF (Y_mask(j) .AND. X_mask(i)) THEN
           return_fieldXY(i,j)=(coef-SIN(dp_pi*(ACOS(COS(Y_lat(j)*dp_conv)*&
                                COS(X_lon(i)*dp_conv))/dp_length)))
        ENDIF
      ENDDO
    ENDDO   
        
  END SUBROUTINE init_field2D_academic


  SUBROUTINE init_field2D_constant(comm,params, lon, lat, mask, return_field,             &
                                   X_lon, X_lat, X_mask, return_fieldX,                   &
                                   Y_lon, Y_lat, Y_mask, return_fieldY, return_fieldXY)
  IMPLICIT NONE
    TYPE(tmodel_params) :: params
    INTEGER :: comm
    DOUBLE PRECISION, POINTER :: lon(:)
    DOUBLE PRECISION, POINTER :: lat(:)
    LOGICAL, POINTER :: mask(:)
    DOUBLE PRECISION, POINTER :: return_field(:)
    
    DOUBLE PRECISION, POINTER :: X_lon(:)
    DOUBLE PRECISION, POINTER :: X_lat(:)
    LOGICAL, POINTER :: X_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldX(:)

    DOUBLE PRECISION, POINTER :: Y_lon(:)
    DOUBLE PRECISION, POINTER :: Y_lat(:)
    LOGICAL, POINTER :: Y_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldY(:)
    DOUBLE PRECISION, POINTER :: return_fieldXY(:,:)
    INTEGER :: x,y,xy
   
    xy=size(mask)
    x=size(X_mask)
    y=size(Y_mask)
        
    ALLOCATE(return_field(0:xy-1))
    return_field(:)=1

    ALLOCATE(return_fieldX(0:x-1))
    return_fieldX=1

    ALLOCATE(return_fieldY(0:y-1))
    return_fieldY=1

    ALLOCATE(return_fieldXY(0:x-1,0:y-1))
    return_fieldXY=1
    
  END SUBROUTINE init_field2D_constant

  SUBROUTINE init_field2D_rank(comm,params, lon, lat, mask, return_field,         &
                               X_lon, X_lat, X_mask, return_fieldX,               &
                               Y_lon, Y_lat, Y_mask, return_fieldY, return_fieldXY)

  IMPLICIT NONE
    TYPE(tmodel_params) :: params
    INTEGER :: comm
    DOUBLE PRECISION, POINTER :: lon(:)
    DOUBLE PRECISION, POINTER :: lat(:)
    LOGICAL, POINTER :: mask(:)
    DOUBLE PRECISION, POINTER :: return_field(:)

    DOUBLE PRECISION, POINTER :: X_lon(:)
    DOUBLE PRECISION, POINTER :: X_lat(:)
    LOGICAL, POINTER :: X_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldX(:)

    DOUBLE PRECISION, POINTER :: Y_lon(:)
    DOUBLE PRECISION, POINTER :: Y_lat(:)
    LOGICAL, POINTER :: Y_mask(:)
    DOUBLE PRECISION, POINTER :: return_fieldY(:)
    DOUBLE PRECISION, POINTER :: return_fieldXY(:,:)    
    INTEGER ::  rank,ierr
    INTEGER :: x,y,xy

    CALL MPI_COMM_RANK(comm,rank,ierr)

    
   
    xy=size(mask)
    x=size(X_mask)
    y=size(Y_mask)
        
    ALLOCATE(return_field(0:xy-1))
    return_field(:)=rank

    ALLOCATE(return_fieldX(0:x-1))
    return_fieldX=rank

    ALLOCATE(return_fieldY(0:y-1))
    return_fieldY=rank

    ALLOCATE(return_fieldXY(0:x-1,0:y-1))
    return_fieldXY=rank

  END SUBROUTINE init_field2D_rank



   SUBROUTINE get_decomposition(comm, params, domain_proc_size, domain_proc_rank, axis_proc_size, axis_proc_rank, &
                                ensemble_proc_size, ensemble_proc_rank)
   IMPLICIT NONE
     INTEGER,INTENT(IN) :: comm
     TYPE(tmodel_params) :: params
     INTEGER,INTENT(OUT) :: domain_proc_size
     INTEGER,INTENT(OUT) :: domain_proc_rank
     INTEGER,INTENT(OUT) :: axis_proc_size
     INTEGER,INTENT(OUT) :: axis_proc_rank
     INTEGER,INTENT(OUT) :: ensemble_proc_size
     INTEGER,INTENT(OUT) :: ensemble_proc_rank

     INTEGER :: mpi_rank,mpi_size,rank, ensemble_number
     INTEGER :: ierr
     INTEGER :: n_domain,n_axis, n_ensemble, min_dist, new_dist, best
     INTEGER :: axis_ind, domain_ind
     LOGICAL :: axis_layer

     CALL MPI_COMM_RANK(comm,mpi_rank,ierr)
     CALL MPI_COMM_SIZE(comm,mpi_size,ierr)

     n_ensemble = params%ensemble_proc_n
     ensemble_proc_size = mpi_size / n_ensemble
     IF (  mpi_rank < MOD(mpi_size,n_ensemble) * (ensemble_proc_size+1) ) THEN
       ensemble_proc_size=ensemble_proc_size+1
       ensemble_proc_rank = MOD(mpi_rank,ensemble_proc_size)
       ensemble_number = mpi_rank / ensemble_proc_size
     ELSE
       ensemble_number = MOD(mpi_size,n_ensemble)
       rank =  mpi_rank - MOD(mpi_size,n_ensemble) * (ensemble_proc_size+1)
       ensemble_proc_rank= MOD(rank,ensemble_proc_size)
       ensemble_number = ensemble_number + rank / ensemble_proc_size
     ENDIF

     mpi_size=ensemble_proc_size
     mpi_rank=ensemble_proc_rank
     ensemble_proc_size = n_ensemble
     ensemble_proc_rank = ensemble_number

    IF (params%axis_proc_n > 0 ) THEN
      n_axis=params%axis_proc_n
      n_domain = mpi_size / n_axis
      axis_layer=.TRUE.
    ELSE IF (params%domain_proc_n > 0 ) THEN
      n_domain=params%domain_proc_n
      n_axis = mpi_size / n_domain
      axis_layer=.FALSE.
    ELSE
      IF (params%axis_proc_frac==0) THEN
         params%axis_proc_frac=1
         params%domain_proc_frac=mpi_size
      ELSE IF (params%domain_proc_frac==0) THEN
         params%domain_proc_frac=1
         params%axis_proc_frac=mpi_size
      ENDIF       
    
      n_domain = INT(sqrt(params%domain_proc_frac * mpi_size/ params%axis_proc_frac))
      n_axis =   INT(sqrt(params%axis_proc_frac * mpi_size/ params%domain_proc_frac))


      min_dist= mpi_size - n_domain*n_axis
      best=0
    
      new_dist = mpi_size -(n_domain+1)*n_axis
      IF (new_dist < min_dist .AND. new_dist >= 0 ) THEN
         min_dist=new_dist
         best=1
      ENDIF

      new_dist=mpi_size-n_domain*(n_axis+1)
      IF (new_dist < min_dist .AND. new_dist >= 0 ) THEN
         min_dist=new_dist
         best=2
      ENDIF

      IF (best==0) THEN
      ELSE IF (best==1) THEN
        n_domain=n_domain+1
      ELSE IF (best==2) THEN
        n_axis=n_axis+1
      ENDIF

      IF ( MOD(mpi_size,n_axis) <= MOD(mpi_size,n_domain)) axis_layer=.TRUE.

    ENDIF
    
    IF ( axis_layer) THEN
      !!! n_axis layer
      IF (mpi_rank < MOD(mpi_size,n_axis)*(n_domain+1)) THEN
        axis_proc_rank=mpi_rank/(n_domain+1)
        domain_proc_rank=MOD(mpi_rank,n_domain+1)
        axis_proc_size=n_axis
        domain_proc_size=n_domain+1
      ELSE
        rank=mpi_rank-MOD(mpi_size,n_axis)*(n_domain+1)
        axis_proc_size=n_axis
        axis_proc_rank=MOD(mpi_size,n_axis)+rank/n_domain
        domain_proc_rank=MOD(rank,n_domain)
        domain_proc_size=n_domain
      ENDIF
    ELSE
      !!! n_domain column
      IF (mpi_rank < MOD(mpi_size,n_domain)*(n_axis+1)) THEN
        domain_proc_rank=mpi_rank/(n_axis+1)
        axis_proc_rank=MOD(mpi_rank,n_axis+1)
        domain_proc_size=n_domain
        axis_proc_size=n_axis+1
      ELSE
        rank=mpi_rank-MOD(mpi_size,n_domain)*(n_axis+1)
        domain_proc_size=n_domain
        domain_proc_rank=MOD(mpi_size,n_domain)+rank/n_axis
        axis_proc_rank=MOD(rank,n_axis)
        axis_proc_size=n_axis
      ENDIF
    ENDIF  


  END SUBROUTINE get_decomposition

END PROGRAM generic_testcase 


