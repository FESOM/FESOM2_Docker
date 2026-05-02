PROGRAM test_diurnal_cycle

  USE xios
  USE mod_wait
  IMPLICIT NONE
  INCLUDE "mpif.h"
  INTEGER :: rank
  INTEGER :: size
  INTEGER :: ierr

  CHARACTER(len=*),PARAMETER :: id="client"
  INTEGER :: comm
  TYPE(xios_duration) :: dtime
  TYPE(xios_context) :: ctx_hdl
  INTEGER,PARAMETER :: llm=10
  DOUBLE PRECISION  :: value_glo(0:llm-1)
  DOUBLE PRECISION,ALLOCATABLE :: axisValue(:)
  DOUBLE PRECISION,ALLOCATABLE :: field_A(:,:)
  INTEGER :: i,j,l,ts,nl,begin

!!! MPI Initialization

  CALL MPI_INIT(ierr)
  CALL MPI_COMM_RANK(MPI_COMM_WORLD,rank,ierr)
  
  IF (rank>3) THEN 
    CALL xios_init_server
  ELSE
  
  CALL init_wait

!!! XIOS Initialization (get the local communicator)

  CALL xios_initialize(id,return_comm=comm)

  CALL MPI_COMM_RANK(comm,rank,ierr)
  CALL MPI_COMM_SIZE(comm,size,ierr)

  CALL xios_context_initialize("test",comm)
  CALL xios_get_handle("test",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  nl=llm/size
  
  IF (rank<MOD(llm,size)) THEN 
    nl=nl+1
    begin=rank*nl
  ELSE
    begin=(nl+1)*MOD(llm,size) + nl*(rank-MOD(llm,size))
  ENDIF
  DO i=0,llm-1
    value_glo(i)=i
  ENDDO


  IF (rank==0) THEN
    begin=0 ; nl=6
  ELSE IF (rank==1) THEN
    begin=0 ; nl=6
  ELSE IF (rank==2) THEN
    begin=0 ; nl=6
  ELSE IF (rank==3) THEN
    begin=6 ; nl=4
  ENDIF

  ALLOCATE(axisValue(0:nl-1))
  ALLOCATE(field_A(0:nl-1,0:llm-1))
  axisValue(:)=value_glo(begin:begin+nl-1)
  DO i=0,llm-1
    field_A(:,i)=10*i+value_glo(begin:begin+nl-1)
  ENDDO
  
  CALL xios_set_axis_attr("axis_A",n_glo=llm , begin=begin, n=nl,value=axisValue) ;

  dtime%second = 3600
  CALL xios_set_timestep(dtime)
  CALL xios_close_context_definition()
 
  DO ts=1,8
    CALL xios_update_calendar(ts)
    CALL xios_send_field("field_A",field_A(:,:))
    field_A=field_A+100
    CALL wait_us(5000) ;
  ENDDO

  CALL xios_context_finalize()

  CALL MPI_COMM_FREE(comm, ierr)

  CALL xios_finalize()
  
  ENDIF
  
  CALL MPI_FINALIZE(ierr)

END PROGRAM test_diurnal_cycle





