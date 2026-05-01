PROGRAM test_tiled_domain

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
  CHARACTER(len=20) :: dtime_str
  TYPE(xios_date) :: date
  CHARACTER(len=20) :: date_str
  CHARACTER(len=15) :: calendar_type
  TYPE(xios_context) :: ctx_hdl
  INTEGER,PARAMETER :: ni_glo=10!100
  INTEGER,PARAMETER :: nj_glo=10!100
  INTEGER,PARAMETER :: llm=5
  DOUBLE PRECISION  :: lval(llm)=1, scalar = 5

  integer, parameter :: ntiles=2
  integer, dimension (ntiles) :: tile_ni, tile_nj, tile_ibegin, tile_jbegin
  integer, dimension (ntiles) :: tile_data_ni, tile_data_nj, tile_data_ibegin, tile_data_jbegin  

  TYPE(xios_field) :: field_hdl
  TYPE(xios_fieldgroup) :: fieldgroup_hdl
  TYPE(xios_file) :: file_hdl
  LOGICAL :: ok

  DOUBLE PRECISION,DIMENSION(ni_glo,nj_glo) :: lon_glo,lat_glo
  DOUBLE PRECISION :: field_3d_glo(ni_glo,nj_glo,llm)
  DOUBLE PRECISION,ALLOCATABLE :: field_3d(:,:,:)
  DOUBLE PRECISION,ALLOCATABLE :: field_3d_tile(:,:,:)
  INTEGER :: ni,ibegin,iend,nj,jbegin,jend
  INTEGER :: i,j,l,ts,n
  INTEGER :: ioffset, joffset

  namelist /tile_data_def/ ioffset, joffset

!!! MPI Initialization

  CALL MPI_INIT(ierr)

  CALL init_wait

!!! XIOS Initialization (get the local communicator)

  CALL xios_initialize(id,return_comm=comm)

  CALL MPI_COMM_RANK(comm,rank,ierr)
  CALL MPI_COMM_SIZE(comm,size,ierr)

!!! Fill in global data array

  DO l=1,llm
    DO j=1,nj_glo
      DO i=1,ni_glo
        field_3d_glo(i,j,l)=(l-1)*ni_glo*nj_glo+(j-1)*ni_glo+(i-1)
      ENDDO
    ENDDO
  ENDDO
  ni=ni_glo ; ibegin=0

!!! MPI domain decomposition

  jbegin=0
  DO n=0,size-1
    nj=nj_glo/size
    IF (n<MOD(nj_glo,size)) nj=nj+1
    IF (n==rank) exit
    jbegin=jbegin+nj
  ENDDO

  iend=ibegin+ni-1 ; jend=jbegin+nj-1

!!! Fill in local data array

  ALLOCATE(field_3d(ni,nj,llm))
  field_3d(1:ni,1:nj,:)=field_3d_glo(ibegin+1:iend+1,jbegin+1:jend+1,:)

!!! Tile domain decomposition
  tile_ni(:)=ni
  tile_ibegin(:)=0
  tile_jbegin(1)=0
  do n=0,ntiles-1
    tile_nj(n+1)=nj/ntiles
    if (n<MOD(nj,ntiles)) tile_nj(n+1)=tile_nj(n+1)+1
  enddo

  do n=2,ntiles
    tile_jbegin(n)=tile_jbegin(n-1)+tile_nj(n-1)
  enddo

!!! Define tile data size

  open(10,file='tile_data_def.nml')
  read(10,nml=tile_data_def)
  close(10)

  ! Option 1: data correspond in size to a tile
  if (ioffset == 0) then
    tile_data_ni(:)=tile_ni(:)
    tile_data_nj(:)=tile_nj(:)
    tile_data_ibegin(:)=0
    tile_data_jbegin(:)=0
  
  ! Option 2: masked data
  else if (ioffset > 0) then
    do n=1,ntiles
      tile_data_ni(n)=tile_ni(n)-ioffset*2
      tile_data_nj(n)=tile_nj(n)-joffset*2
    enddo
    tile_data_ibegin(:)=ioffset
    tile_data_jbegin(:)=joffset

  ! Option 3: data contain ghost zones
  else
    do n=1,ntiles
      tile_data_ni(n)=tile_ni(n)+abs(ioffset)*2
      tile_data_nj(n)=tile_nj(n)+abs(joffset)*2
    enddo
    tile_data_ibegin(:)=ioffset
    tile_data_jbegin(:)=joffset
  endif

  CALL xios_context_initialize("test",comm)
  CALL xios_get_handle("test",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_set_axis_attr("axis",n_glo=llm ,value=lval) ;
  CALL xios_set_domain_attr("domain",ni_glo=ni_glo, nj_glo=nj_glo, ibegin=ibegin, ni=ni,jbegin=jbegin,nj=nj,type='curvilinear')
  CALL xios_set_domain_attr("domain",ntiles=ntiles, tile_ni=tile_ni, tile_nj=tile_nj, tile_ibegin=tile_ibegin, tile_jbegin=tile_jbegin)
  CALL xios_set_domain_attr("domain",tile_data_ni=tile_data_ni,tile_data_nj=tile_data_nj)
  CALL xios_set_domain_attr("domain",tile_data_ibegin=tile_data_ibegin,tile_data_jbegin=tile_data_jbegin)

  dtime%second = 3600
  CALL xios_set_timestep(dtime)

  ! The calendar is created as soon as the calendar type is defined. This way
  ! calendar operations can be used before the context definition is closed
  dtime%timestep = 1
  dtime = 0.5 * dtime
  
  CALL xios_close_context_definition()
  PRINT *,"close context definition: ok "

  DO ts=1,10
    CALL xios_update_calendar(ts)

    do n=1,ntiles
      ALLOCATE(field_3d_tile(tile_data_ibegin(n):tile_data_ibegin(n)+tile_data_ni(n)-1,&
                             tile_data_jbegin(n):tile_data_jbegin(n)+tile_data_nj(n)-1,llm))
      
      if (ioffset == 0) then
      ! Option 1: data correspond in size to a tile 
      field_3d_tile(:,:,:)=field_3d(tile_ibegin(n)+1:tile_ibegin(n)+1+tile_ni(n),&
                                  tile_jbegin(n)+1:tile_jbegin(n)+1+tile_nj(n),:)
      
      else if (ioffset > 0) then
      ! Option 2: masked data
      field_3d_tile(:,:,:)=field_3d(tile_ibegin(n)+1:tile_ibegin(n)+1+tile_ni(n),&
                                  tile_jbegin(n)+1:tile_jbegin(n)+1+tile_nj(n),:)

      else
      ! Option 3: data contain ghost zones
      field_3d_tile(:,:,:)=2.0
      field_3d_tile(0:tile_ni(n)-1, 0:tile_nj(n)-1,:)=&
                    field_3d(tile_ibegin(n)+1:tile_ibegin(n)+tile_ni(n),&
                             tile_jbegin(n)+1:tile_jbegin(n)+tile_nj(n),:)
      end if

      CALL xios_send_field("field_3d",field_3d_tile,n-1)
      DEALLOCATE(field_3d_tile)
    enddo

    CALL wait_us(5000) ;
  ENDDO

  CALL xios_context_finalize()

  DEALLOCATE(field_3d)

  CALL MPI_COMM_FREE(comm, ierr)

  CALL xios_finalize()

  CALL MPI_FINALIZE(ierr)

END PROGRAM test_tiled_domain





