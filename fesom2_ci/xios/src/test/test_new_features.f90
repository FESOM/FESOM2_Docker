PROGRAM test_new_features

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
  TYPE(xios_date) :: date
  CHARACTER(len=15) :: calendar_type
  TYPE(xios_context) :: ctx_hdl
  INTEGER,PARAMETER :: ni_glo=100
  INTEGER,PARAMETER :: nj_glo=100
  INTEGER,PARAMETER :: llm=10
  INTEGER,PARAMETER :: llmInterPolated=4
  DOUBLE PRECISION  :: lval(llm)=1, tsTemp, lvalInterPolated(llmInterPolated)=1, nlev(nj_glo)=10
  TYPE(xios_field) :: field_hdl
  TYPE(xios_fieldgroup) :: fieldgroup_hdl
  TYPE(xios_file) :: file_hdl
  LOGICAL :: ok
  LOGICAL,ALLOCATABLE :: mask_glo(:),mask(:)

  DOUBLE PRECISION,DIMENSION(ni_glo,nj_glo) :: lon_glo,lat_glo
  DOUBLE PRECISION,DIMENSION(4,ni_glo,nj_glo) :: bnds_lon_glo, bnds_lat_glo
  DOUBLE PRECISION :: field_A_glo(ni_glo,nj_glo,llm), lval_ni_glo(ni_glo), lval_nj_glo(nj_glo), field_Value_glo(ni_glo,nj_glo,llm)
  DOUBLE PRECISION,ALLOCATABLE :: lon(:,:),lat(:,:),field_A(:,:,:), field_A_2D(:,:), field_All_Axis(:,:,:), lonvalue(:) , &
                                  field_Axis(:), lvaln(:), lval_ni(:), lval_nj(:), field_Two_Axis(:,:), lvalnInterp(:), &
                                  lontransformed(:,:), lattransformed(:,:), lon_glotransformed(:,:), lat_glotransformed(:,:), &
                                  bnds_lon(:,:,:), bnds_lat(:,:,:), field_value(:,:,:)
  INTEGER :: ni,ibegin,iend,nj,jbegin,jend, nAxis, axisBegin, axisEnd
  INTEGER :: axisterpBegin, nAxisinterp, axisinterpEnd
  INTEGER :: niDomInterp,ibeginDomInterp,iendDomInterp,njDomInterp,jbeginDomInterp,jendDomInterp, niDomGlo, njDomGlo
  INTEGER :: i,j,k,l,ts,n

!!! MPI Initialization

  CALL MPI_INIT(ierr)

  CALL init_wait

!!! XIOS Initialization (get the local communicator)
  CALL xios_initialize(id,return_comm=comm)

  CALL MPI_COMM_RANK(comm,rank,ierr)
  CALL MPI_COMM_SIZE(comm,size,ierr)

  DO j=1,nj_glo
    DO i=1,ni_glo
      lon_glo(i,j)=(i-1)+(j-1)*ni_glo
      lat_glo(i,j)=1000+(i-1)+(j-1)*ni_glo
      DO k = 1,4
        bnds_lon_glo(1,i,j) = lon_glo(i,j)
        bnds_lon_glo(2,i,j) = lon_glo(i,j)-10
        bnds_lon_glo(3,i,j) = lon_glo(i,j)
        bnds_lon_glo(4,i,j) = lon_glo(i,j)+10

        bnds_lat_glo(1,i,j) = lat_glo(i,j) -10
        bnds_lat_glo(2,i,j) = lat_glo(i,j)
        bnds_lat_glo(3,i,j) = lat_glo(i,j) -10
        bnds_lat_glo(4,i,j) = lat_glo(i,j)
      ENDDO
      lval_ni_glo(i) = i-1
      DO l=1,llm
        field_A_glo(i,j,l)=(i-1)+(j-1)*ni_glo+10000*l
        field_Value_glo(i,j,l)=l*100
      ENDDO
    ENDDO
    lval_nj_glo(j) = j-1
  ENDDO
  ni = ni_glo
  ibegin = 0
  iend = ibegin + ni - 1

  jbegin=0
  CALL Distribute_index(jbegin, jend, nj, nj_glo, rank, size)

  DO j=1,llm
    lval(j) = j *100
  ENDDO
  axisBegin = 0
  CALL Distribute_index(axisBegin, axisEnd, nAxis, llm, rank, size)

  DO j=1,llmInterPolated
    lvalInterPolated(j) = j * 12
  ENDDO
  axisterpBegin = 0
  CALL Distribute_index(axisterpBegin, axisinterpEnd, nAxisinterp, llmInterPolated, rank, size)

  niDomGlo = ni_glo - 4
  njDomGlo = nj_glo - 4
  ALLOCATE(lon_glotransformed(niDomGlo,njDomGlo), lat_glotransformed(niDomGlo,njDomGlo))
  DO j=1,njDomGlo
    DO i=1,niDomGlo
      lon_glotransformed(i,j)=(i-1)+(j-1)*niDomGlo
      lat_glotransformed(i,j)=1000+(i-1)+(j-1)*niDomGlo
    ENDDO
  ENDDO

  niDomInterp = niDomGlo; ibeginDomInterp = 0
  jbeginDomInterp = 0
  CALL Distribute_index(jbeginDomInterp, jendDomInterp, njDomInterp, njDomGlo, rank, size)

  ALLOCATE(field_A(0:ni+1,-1:nj+2,llm), field_A_2D(0:ni+1,-1:nj+2), &
          field_Two_Axis(ni_glo,1:nj), field_Axis(nAxis), field_All_Axis(1:ni,1:nj,llm), &
          lon(ni,nj),lat(ni,nj), lonvalue(ni*nj), &
          lvaln(nAxis), lval_ni(ni), lval_nj(nj), lvalnInterp(nAxisinterp), &
          lontransformed(niDomInterp, njDomInterp), lattransformed(niDomInterp, njDomInterp), &
          bnds_lon(4,ni,nj), bnds_lat(4,ni,nj), field_value(0:ni+1,-1:nj+2,llm))

  ALLOCATE(mask(nj))
  DO i = 1, nj
!    IF (MOD(i,2)>=0) THEN
!      mask(i)=.FALSE.
!    ELSE
      mask(i)=.TRUE.
!    ENDIF
  ENDDO
  lon(:,:)=lon_glo(ibegin+1:iend+1,jbegin+1:jend+1)
  lat(:,:)=lat_glo(ibegin+1:iend+1,jbegin+1:jend+1)
  bnds_lon(:,:,:) = bnds_lon_glo(:,ibegin+1:iend+1,jbegin+1:jend+1)
  bnds_lat(:,:,:) = bnds_lat_glo(:,ibegin+1:iend+1,jbegin+1:jend+1)
  lontransformed(:,:) = lon_glotransformed(ibeginDomInterp+1:iendDomInterp+1,jbeginDomInterp+1:jendDomInterp+1)
  lattransformed(:,:) = lat_glotransformed(ibeginDomInterp+1:iendDomInterp+1,jbeginDomInterp+1:jendDomInterp+1)
  field_A(1:ni,1:nj,:) = field_A_glo(ibegin+1:iend+1,jbegin+1:jend+1,:)
  field_A_2D(1:ni,1:nj) = field_A_glo(ibegin+1:iend+1,jbegin+1:jend+1,1)
  field_value(1:ni,1:nj,:) = field_Value_glo(ibegin+1:iend+1,jbegin+1:jend+1,:)
  field_Axis(1:nAxis)  = field_A_glo(1,1,axisBegin+1:axisEnd+1)
  field_Two_Axis(:,1:nj)  = field_A_glo(:,jbegin+1:jend+1,1)
  field_All_Axis(1:ni,1:nj,:) = field_A_glo(ibegin+1:iend+1,jbegin+1:jend+1,:)

  lvaln(1:nAxis) = lval(axisBegin+1:axisEnd+1)
  lval_nj(1:nj) = lval_nj_glo(jbegin+1:jend+1);
  lval_ni(1:ni) = lval_ni_glo(ibegin+1:iend+1);
  lvalnInterp(1:nAxisinterp) = lvalInterPolated(axisterpBegin+1:axisinterpEnd+1)

  CALL xios_context_initialize("test",comm)
  CALL xios_get_handle("test",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_get_calendar_type(calendar_type)
  PRINT *, "calendar_type = ", calendar_type

  CALL xios_set_axis_attr("axis_A", n_glo=ni_glo, begin=ibegin, n=ni, value=lval_ni)
  CALL xios_set_axis_attr("axis_B", n_glo=nj_glo, begin=jbegin, n=nj, value=lval_nj, mask=mask)
  CALL xios_set_axis_attr("axis_C", n_glo=llm, value=lval)
  CALL xios_set_axis_attr("axis_D", n_glo=llm, begin=axisBegin, n=nAxis, value=lvaln)
  CALL xios_set_axis_attr("axis_E", n_glo=llmInterPolated, value=lvalnInterp, begin=axisterpBegin, n=nAxisinterp)
  CALL xios_set_axis_attr("axis_G", n_glo=nj_glo, value=nlev)

  CALL xios_set_domain_attr("domain_A",ni_glo=ni_glo, nj_glo=nj_glo, ibegin=ibegin, ni=ni,jbegin=jbegin,nj=nj)
  CALL xios_set_domain_attr("domain_A",data_dim=2, data_ibegin=-1, data_ni=ni+2, data_jbegin=-2, data_nj=nj+4)
  CALL xios_set_domain_attr("domain_A",lonvalue_2D=lon,latvalue_2D=lat, type='curvilinear')
  CALL xios_set_domain_attr("domain_A",bounds_lon_2d=bnds_lon,bounds_lat_2d=bnds_lat, nvertex=4, type='curvilinear')

  CALL xios_set_domain_attr("domain_A_transformed", ni_glo=niDomGlo, nj_glo=njDomGlo, &
                            type='rectilinear')
!                                                    ibegin=ibeginDomInterp, ni=niDomInterp, jbegin=jbeginDomInterp, nj=njDomInterp)
!  CALL xios_set_domain_attr("domain_A_transformed", lonvalue_2D=lontransformed, &
!                                                    latvalue_2D=lattransformed)

  CALL xios_set_fieldgroup_attr("field_definition",enabled=.TRUE.)

!  CALL xios_get_handle("field_definition",fieldgroup_hdl)
!  CALL xios_add_child(fieldgroup_hdl,field_hdl,"field_B")
!  CALL xios_set_attr(field_hdl,field_ref="field_A",name="field_B")
!
!  CALL xios_get_handle("output",file_hdl)
!  CALL xios_add_child(file_hdl,field_hdl)
!  CALL xios_set_attr(field_hdl,field_ref="field_A",name="field_C")

  dtime%second = 3600
  CALL xios_set_timestep(dtime)

  ! The calendar is created as soon as the calendar type is defined. This way
  ! calendar operations can be used before the context definition is closed
  CALL xios_get_time_origin(date)
  PRINT *, "--> year length = ", xios_get_year_length_in_seconds(date%year)
  PRINT *, "--> day length = ", xios_get_day_length_in_seconds()
  PRINT *, "time_origin = ", date
  PRINT *, "xios_date_get_second_of_year(time_origin) = ", xios_date_get_second_of_year(date)
  PRINT *, "xios_date_get_day_of_year(time_origin) = ", xios_date_get_day_of_year(date)
  PRINT *, "xios_date_get_fraction_of_year(time_origin) = ", xios_date_get_fraction_of_year(date)
  PRINT *, "xios_date_get_second_of_day(time_origin) = ", xios_date_get_second_of_day(date)
  PRINT *, "xios_date_get_fraction_of_day(time_origin) = ", xios_date_get_fraction_of_day(date)
  dtime%timestep = 1
  dtime = 0.5 * dtime
  PRINT *, "duration = ", dtime
  date = date + 3 * (dtime + dtime)
  PRINT *, "date = time_origin + 3 * (duration + duration) = ", date
  PRINT *, "xios_date_convert_to_seconds(date) = ", xios_date_convert_to_seconds(date)
  PRINT *, "xios_date_convert_to_seconds(date - 2.5h) = ", xios_date_convert_to_seconds(date - 2.5 * xios_hour)

  ni=0 ; lonvalue(:)=0
!  CALL xios_get_domain_attr("domain_A",ni=ni,lonvalue_1D=lonvalue)

!  print *,"ni",ni
!  print *,"lonvalue",lonvalue ;

  CALL xios_is_defined_field_attr("field_A",enabled=ok)
  PRINT *,"field_A : attribute enabled is defined ? ",ok
  CALL xios_close_context_definition()

  PRINT*,"field field_A is active ? ",xios_field_is_active("field_A")
  DO ts=1,24*1
    CALL xios_update_calendar(ts)
    CALL xios_send_field("field_A",field_A)
    CALL xios_send_field("field_A_2D",field_A_2D)
    CALL xios_send_field("field_Value",field_value)
    CALL xios_send_field("field_Axis",field_Axis)
    CALL xios_send_field("field_Two_Axis",field_Two_Axis)
    CALL xios_send_field("field_All_Axis",field_All_Axis)
    tsTemp = ts
    CALL xios_send_field("field_Scalar", tsTemp)
    CALL wait_us(5000) ;
  ENDDO

  CALL xios_context_finalize()

  DEALLOCATE(field_A, field_Two_Axis, field_Axis, field_All_Axis, &
             lon, lat, lonvalue, &
             lvaln, lval_ni, lval_nj, lvalnInterp, &
             bnds_lon, bnds_lat)

  DEALLOCATE(mask)

  CALL MPI_COMM_FREE(comm, ierr)

  CALL xios_finalize()

  CALL MPI_FINALIZE(ierr)

CONTAINS
  SUBROUTINE Distribute_index(ibegin, iend, ni, nglob, rank, size)
    INTEGER, INTENT(INOUT) :: ibegin, iend, ni
    INTEGER, INTENT(IN)    :: nglob, rank, size
    DO n=0,size-1
      ni=nglob/size
      IF (n<MOD(nglob,size)) ni=ni+1
      IF (n==rank) exit
      ibegin=ibegin+ni
    ENDDO
    iend=ibegin+ni-1
  END SUBROUTINE Distribute_index
END PROGRAM test_new_features
