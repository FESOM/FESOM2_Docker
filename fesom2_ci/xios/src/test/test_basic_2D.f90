PROGRAM test_basic_2D
  USE xios
  USE mod_wait
  IMPLICIT NONE
  INCLUDE "mpif.h"

  TYPE(xios_duration)  :: dtime
  TYPE(xios_context) :: ctx_hdl
  INTEGER,PARAMETER :: ni_glo=100
  INTEGER,PARAMETER :: nj_glo=100

  INTEGER :: i,j,n,ts
  INTEGER :: ibegin,jbegin,ni,nj,nbi,nbj,iend,jend
  INTEGER :: ierr, rank, size
  INTEGER :: comm

  DOUBLE PRECISION,DIMENSION(ni_glo,nj_glo) :: lon_glo,lat_glo
  DOUBLE PRECISION :: field_glo(ni_glo,nj_glo)
  DOUBLE PRECISION,ALLOCATABLE :: lon(:,:),lat(:,:),field_domain(:,:), field_axis(:,:)

  ! Initialize MPI
  CALL MPI_INIT(ierr)

  CALL init_wait

  ! Initialize XIOS
  CALL xios_initialize('client', return_comm=comm)

  CALL MPI_COMM_SIZE(comm, size, ierr)
  CALL MPI_COMM_RANK(comm, rank, ierr)

  ! Initialize all global values
  DO j=1,nj_glo
    DO i=1,ni_glo
      lon_glo(i,j)=(i-1)+(j-1)*ni_glo
      lat_glo(i,j)=1000+(i-1)+(j-1)*ni_glo
      field_glo(i,j)=(i-1)+(j-1)*ni_glo
    ENDDO
  ENDDO
  ni=ni_glo ; ibegin=0

  nbi = 1
  ! Specify how we distributed domain
  DO i=1,int(sqrt(real(size)))+1
    IF (0 == MOD(size,i)) nbi = i
  ENDDO
  nbj = size/nbi

  jbegin=0;
  LOOP1: DO j=1,nbj
    nj=nj_glo/nbj
    if (nj<MOD(nj_glo,nbj)) nj=nj+1
    ibegin=0
    DO i=1,nbi
      n=(j-1)*nbi+i-1
      ni=ni_glo/nbi
      if (ni<MOD(ni_glo,nbi)) ni=ni+1
      IF (n==rank) exit LOOP1
      IF (i/=nbi) ibegin=ibegin+ni
    ENDDO
    IF (j/=nbj) jbegin=jbegin+nj
  ENDDO LOOP1
  iend=ibegin+ni-1; jend=jbegin+nj-1

!  if (rank == 0) print *, ni_glo, ni, nj_glo, nj
  print *, ni, nj, ibegin, jbegin, iend, jend

  ALLOCATE(lon(ni,nj),lat(ni,nj),field_domain(0:ni+1,-1:nj+2),field_axis(ni,nj))
  lon(:,:)=lon_glo(ibegin+1:iend+1,jbegin+1:jend+1)
  lat(:,:)=lat_glo(ibegin+1:iend+1,jbegin+1:jend+1)
  field_domain(1:ni,1:nj)=field_glo(ibegin+1:iend+1,jbegin+1:jend+1)
  field_axis(1:ni,1:nj)=field_glo(ibegin+1:iend+1,jbegin+1:jend+1)

  ! Test 2-dimension domain
  ! Initialize the context
  CALL xios_context_initialize('test_domain', comm)
  CALL xios_get_handle('test_domain', ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_define_calendar(type="Gregorian", &
                            start_date=xios_date(2000, 01, 01, 00, 00, 00), &
                            time_origin=xios_date(1999, 01, 01, 15, 00, 00))

  CALL xios_set_domain_attr("domain",ni_glo=ni_glo, nj_glo=nj_glo, ibegin=ibegin, ni=ni,jbegin=jbegin,nj=nj, type='curvilinear')
  CALL xios_set_domain_attr("domain",data_dim=2, data_ibegin=-1, data_ni=ni+2, data_jbegin=-2, data_nj=nj+4)
  CALL xios_set_domain_attr("domain",lonvalue_2D=lon,latvalue_2D=lat)

  CALL xios_get_domain_attr("domain",lonvalue_2D=lon)
!  PRINT *,"lonvalue",lon

  dtime%second=3600
  CALL xios_set_timestep(timestep=dtime)
  ! Close domain context
  CALL xios_close_context_definition()

  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  ! Test 2-dimension grid composed of 2 distributed axis
  ! Initialize the context
  CALL xios_context_initialize('test_axis', comm)
  CALL xios_get_handle('test_axis', ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_define_calendar(type="Gregorian", &
                            start_date=xios_date(2000, 01, 01, 00, 00, 00), &
                            time_origin=xios_date(1999, 01, 01, 15, 00, 00))

  CALL xios_set_axis_attr("x", n_glo=ni_glo, n=ni, begin=ibegin, value=(/(real(i,kind=8), i=ibegin,ibegin+ni-1)/))
  CALL xios_set_axis_attr("y", n_glo=nj_glo, n=nj, begin=jbegin, value=(/(real(i,kind=8), i=jbegin,jbegin+nj-1)/))

  dtime%second=3600
  CALL xios_set_timestep(timestep=dtime)

  ! Close axis context
  CALL xios_close_context_definition()

  DO ts=1,24*10
    ! Domain context
    CALL xios_get_handle("test_domain",ctx_hdl)
    CALL xios_set_current_context(ctx_hdl)
    CALL xios_update_calendar(ts)
    CALL xios_send_field("field_domain_1",field_domain)
    CALL xios_send_field("field_domain_2",field_domain)

    ! Switch to axis context
    CALL xios_get_handle("test_axis",ctx_hdl)
    CALL xios_set_current_context(ctx_hdl)
    CALL xios_update_calendar(ts)
    CALL xios_send_field("field_axis",field_axis)

    CALL wait_us(500) ;
  ENDDO

  ! Clean-ups
  CALL xios_get_handle("test_domain",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)
  CALL xios_context_finalize()
  CALL xios_get_handle("test_axis",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)
  CALL xios_context_finalize()

  DEALLOCATE(lon, lat, field_domain, field_axis)

  CALL MPI_COMM_FREE(comm, ierr)
  CALL xios_finalize()
  CALL MPI_FINALIZE(ierr)

END PROGRAM test_basic_2D





