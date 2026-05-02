PROGRAM test_remap

  USE xios
  USE mod_wait
  USE netcdf

  IMPLICIT NONE
  INCLUDE "mpif.h"
  INTEGER :: rank
  INTEGER :: size
  INTEGER :: ierr

  CHARACTER(len=*),PARAMETER :: id="client"
  INTEGER :: comm
  TYPE(xios_duration) :: dtime
  TYPE(xios_context) :: ctx_hdl

  DOUBLE PRECISION,ALLOCATABLE :: src_lon(:), dst_lon(:)
  DOUBLE PRECISION,ALLOCATABLE :: src_lat(:), dst_lat(:)
  DOUBLE PRECISION,ALLOCATABLE :: src_boundslon(:,:), dst_boundslon(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: src_boundslat(:,:), dst_boundslat(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: src_field_2D(:)
  DOUBLE PRECISION,ALLOCATABLE :: tmp_field_0(:), tmp_field_1(:), tmp_field_2(:)
  DOUBLE PRECISION,ALLOCATABLE :: src_field_3D(:,:), src_field_4D(:,:,:), lval(:), lval1(:), lval2(:), src_field_pression(:,:)
  LOGICAL,ALLOCATABLE :: src_mask_2D(:)
  INTEGER :: src_ni_glo, dst_ni_glo;
  INTEGER :: src_nvertex, dst_nvertex;
  INTEGER :: src_ibegin, dst_ibegin;
  INTEGER :: src_ni, dst_ni;
  INTEGER :: src_tmp_ni, src_tmp_nj, src_tmp_n;
  CHARACTER(LEN=*),PARAMETER :: src_file="h14.nc"
  CHARACTER(LEN=*),PARAMETER :: dst_file="r180x90.nc"
  INTEGER :: ncid
  INTEGER :: dimids(2)
  INTEGER :: div,remain
  INTEGER :: varid
  INTEGER :: ts
  INTEGER :: i
  INTEGER,PARAMETER :: llm=5, interpolatedLlm = 4, llm2 = 6

  CALL MPI_INIT(ierr)
  CALL init_wait

!!! XIOS Initialization (get the local communicator)

  CALL xios_initialize(id,return_comm=comm)
  CALL MPI_COMM_RANK(comm,rank,ierr)
  CALL MPI_COMM_SIZE(comm,size,ierr)

  ierr=NF90_OPEN(src_file, NF90_NOWRITE, ncid)
  ierr=NF90_INQ_VARID(ncid,"bounds_lon",varid)
  ierr=NF90_INQUIRE_VARIABLE(ncid, varid,dimids=dimids)
  ierr=NF90_INQUIRE_DIMENSION(ncid, dimids(1), len=src_nvertex)
  ierr=NF90_INQUIRE_DIMENSION(ncid, dimids(2), len=src_ni_glo)

  div    = src_ni_glo/size
  remain = MOD( src_ni_glo, size )
  IF (rank < remain) THEN
    src_ni=div+1 ;
    src_ibegin=rank*(div+1) ;
  ELSE
    src_ni=div ;
    src_ibegin= remain * (div+1) + (rank-remain) * div ;
  ENDIF

  ALLOCATE(src_lon(src_ni))
  ALLOCATE(src_lat(src_ni))
  ALLOCATE(src_boundslon(src_nvertex,src_ni))
  ALLOCATE(src_boundslat(src_nvertex,src_ni))
  ALLOCATE(src_field_2D(src_ni))
  ALLOCATE(src_field_3D(src_ni,llm))
  ALLOCATE(src_field_4D(src_ni,llm,llm2))
  ALLOCATE(src_mask_2D(src_ni))
  ALLOCATE(src_field_pression(src_ni,llm))
  ALLOCATE(lval(llm))
  ALLOCATE(lval1(interpolatedLlm))
  ALLOCATE(lval2(llm2))

  ierr=NF90_INQ_VARID(ncid,"lon",varid)
  ierr=NF90_GET_VAR(ncid,varid, src_lon, start=(/src_ibegin+1/),count=(/src_ni/))
  ierr=NF90_INQ_VARID(ncid,"lat",varid)
  ierr=NF90_GET_VAR(ncid,varid, src_lat, start=(/src_ibegin+1/),count=(/src_ni/))
  ierr=NF90_INQ_VARID(ncid,"bounds_lon",varid)
  ierr=NF90_GET_VAR(ncid,varid,src_boundslon, start=(/1,src_ibegin+1/),count=(/src_nvertex,src_ni/))
  ierr=NF90_INQ_VARID(ncid,"bounds_lat",varid)
  ierr=NF90_GET_VAR(ncid,varid, src_boundslat, start=(/1,src_ibegin+1/),count=(/src_nvertex,src_ni/))
  ierr=NF90_INQ_VARID(ncid,"val",varid)
  ierr=NF90_GET_VAR(ncid,varid, src_field_2D, start=(/src_ibegin+1/),count=(/src_ni/))
  DO i=1,src_ni
    src_field_3D(i,:) = src_field_2D(i)
    IF (MOD(i,10)==0) THEN
      src_mask_2D(i)=.FALSE.
    ELSE
      src_mask_2D(i)=.TRUE.
    ENDIF
  ENDDO

  DO i=1,llm
    lval(i) = i*100
    src_field_pression(:,i) = i * 100
    src_field_3D(:,i) = src_field_3D(:,i) + i * 10    
  ENDDO

  DO i=1,llm2
    src_field_4D(:,:,i) = src_field_3D(:,:)
  ENDDO

  DO i=1,interpolatedLlm
    lval2(i) = i*10
    lval1(i) = i*10 + 2
  ENDDO

  ierr=NF90_OPEN(dst_file, NF90_NOWRITE, ncid)
  ierr=NF90_INQ_VARID(ncid,"bounds_lon",varid)
  ierr=NF90_INQUIRE_VARIABLE(ncid, varid,dimids=dimids)
  ierr=NF90_INQUIRE_DIMENSION(ncid, dimids(1), len=dst_nvertex)
  ierr=NF90_INQUIRE_DIMENSION(ncid, dimids(2), len=dst_ni_glo)

  div    = dst_ni_glo/size
  remain = MOD( dst_ni_glo, size )
  IF (rank < remain) THEN
    dst_ni=div+1 ;
    dst_ibegin=rank*(div+1) ;
  ELSE
    dst_ni=div ;
    dst_ibegin= remain * (div+1) + (rank-remain) * div ;
  ENDIF

  ALLOCATE(dst_lon(dst_ni))
  ALLOCATE(dst_lat(dst_ni))
  ALLOCATE(dst_boundslon(dst_nvertex,dst_ni))
  ALLOCATE(dst_boundslat(dst_nvertex,dst_ni))

  ierr=NF90_INQ_VARID(ncid,"lon",varid)
  ierr=NF90_GET_VAR(ncid,varid, dst_lon, start=(/dst_ibegin+1/),count=(/dst_ni/))
  ierr=NF90_INQ_VARID(ncid,"lat",varid)
  ierr=NF90_GET_VAR(ncid,varid, dst_lat, start=(/dst_ibegin+1/),count=(/dst_ni/))
  ierr=NF90_INQ_VARID(ncid,"bounds_lon",varid)
  ierr=NF90_GET_VAR(ncid,varid,dst_boundslon, start=(/1,dst_ibegin+1/),count=(/dst_nvertex,dst_ni/))
  ierr=NF90_INQ_VARID(ncid,"bounds_lat",varid)
  ierr=NF90_GET_VAR(ncid,varid, dst_boundslat, start=(/1,dst_ibegin+1/),count=(/dst_nvertex,dst_ni/))


  CALL xios_context_initialize("test",comm)
  CALL xios_get_handle("test",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_set_domain_attr("src_domain", ni_glo=src_ni_glo, ibegin=src_ibegin, ni=src_ni, type="unstructured")
  CALL xios_set_domain_attr("src_domain", lonvalue_1D=src_lon, latvalue_1D=src_lat, &
                            bounds_lon_1D=src_boundslon, bounds_lat_1D=src_boundslat, nvertex=src_nvertex)

  CALL xios_set_domain_attr("src_domain_clone", ni_glo=src_ni_glo, ibegin=src_ibegin, ni=src_ni, type="unstructured")
  CALL xios_set_domain_attr("src_domain_clone", lonvalue_1D=src_lon, latvalue_1D=src_lat, &
                            bounds_lon_1D=src_boundslon, bounds_lat_1D=src_boundslat, nvertex=src_nvertex, &
                            mask_1d=src_mask_2D)

  CALL xios_set_axis_attr("src_axis", n_glo=llm, value=lval)
  CALL xios_set_axis_attr("nq", n_glo=llm2, value=lval2)

  CALL xios_set_domain_attr("dst_domain", ni_glo=dst_ni_glo, ibegin=dst_ibegin, ni=dst_ni, type="unstructured")
  CALL xios_set_domain_attr("dst_domain", lonvalue_1D=dst_lon, latvalue_1D=dst_lat, &
                            bounds_lon_1D=dst_boundslon, bounds_lat_1D=dst_boundslat, nvertex=dst_nvertex)

  dtime%second = 3600
  CALL xios_set_timestep(dtime)

  CALL xios_close_context_definition()
  CALL xios_get_domain_attr("src_domain_regular_read", ni=src_tmp_ni, nj=src_tmp_nj)
  ALLOCATE(tmp_field_0(src_tmp_ni*src_tmp_nj))

  ! CALL xios_get_axis_attr("src_axis_curvilinear_read", n=src_tmp_n)
  ! CALL xios_get_domain_attr("src_domain_curvilinear_read", ni=src_tmp_ni, nj=src_tmp_nj)
  ! ALLOCATE(tmp_field_1(src_tmp_ni*src_tmp_nj*src_tmp_n))

  ! CALL xios_get_domain_attr("src_domain_unstructured_read", ni=src_tmp_ni, nj=src_tmp_nj)
  ! ALLOCATE(tmp_field_2(src_tmp_ni*src_tmp_nj))

  DO ts=1,1
    CALL xios_recv_field("src_field_regular", tmp_field_0)
    ! CALL xios_recv_field("src_field_curvilinear", tmp_field_1)
    ! CALL xios_recv_field("src_field_unstructured", tmp_field_2)
    CALL xios_update_calendar(ts)
    CALL xios_send_field("src_field_2D",src_field_2D)
    CALL xios_send_field("src_field_2D_clone",src_field_2D)
    CALL xios_send_field("src_field_3D",src_field_3D)
    ! CALL xios_send_field("src_field_4D",src_field_4D)
    ! CALL xios_send_field("src_field_3D_pression",src_field_pression)
    CALL xios_send_field("tmp_field_0",tmp_field_0)
    ! CALL xios_send_field("tmp_field_1",tmp_field_1)
    ! CALL xios_send_field("tmp_field_2",tmp_field_2)
    CALL wait_us(5000) ;
   ENDDO

  CALL xios_context_finalize()

  DEALLOCATE(src_lon, src_lat, src_boundslon,src_boundslat, src_field_2D)
  DEALLOCATE(dst_lon, dst_lat, dst_boundslon,dst_boundslat)
  ! DEALLOCATE(tmp_field_0, tmp_field_1, tmp_field_2)

  CALL MPI_COMM_FREE(comm, ierr)

  CALL xios_finalize()

  CALL MPI_FINALIZE(ierr)

END PROGRAM test_remap





