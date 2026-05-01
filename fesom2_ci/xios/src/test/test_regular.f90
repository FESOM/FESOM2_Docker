PROGRAM test_regular

  USE xios
  IMPLICIT NONE
  INCLUDE "mpif.h"

  INTEGER, PARAMETER :: ntime=1

  CHARACTER(len=*),PARAMETER :: id="client"
  TYPE(xios_duration)  :: dtime
  TYPE(xios_context) :: ctx_hdl
  TYPE(xios_field) :: field_hdl
  TYPE(xios_fieldgroup) :: fieldgroup_hdl
  TYPE(xios_file) :: file_hdl
  LOGICAL :: ok
  CHARACTER(len=256) :: crname
  INTEGER :: ts
  INTEGER :: comm  
  INTEGER :: ierr
  INTEGER :: sizeComm, rank    ! SIZE is a fortran function

  INTEGER :: nlon = 100 
  INTEGER :: nlat = 100
  INTEGER :: ncell 
  INTEGER :: ilat, ilon, ind
  DOUBLE PRECISION :: lon1, lon2, lat1, lat2
  INTEGER :: ni, ibegin

  DOUBLE PRECISION,ALLOCATABLE :: lon_glo(:)
  DOUBLE PRECISION,ALLOCATABLE :: lat_glo(:)
  DOUBLE PRECISION,ALLOCATABLE :: bounds_lon_glo(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: bounds_lat_glo(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: field_temp_glo(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: lon(:)
  DOUBLE PRECISION,ALLOCATABLE :: lat(:)
  DOUBLE PRECISION,ALLOCATABLE :: bounds_lon(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: bounds_lat(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: field_temp(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: field_temp1(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: field_temp2(:,:)

!!! MPI Initialization
  CALL MPI_INIT(ierr)

!!! XIOS Initialization (get the local communicator)
  CALL xios_initialize(id,return_comm=comm)

!###########################################################################
! Contexte ATM
!###########################################################################

!!! Initialisation des coordonnées globales et locales pour la grille régulière

! Regions around the poles are not included into the grid
! The whole grid is rectangular (nvertex=4)

  ncell = nlon * (nlat-1)
  ALLOCATE(lon_glo(ncell))
  ALLOCATE(lat_glo(ncell))
  ALLOCATE(bounds_lon_glo(4,ncell))
  ALLOCATE(bounds_lat_glo(4,ncell))
  ALLOCATE(field_temp_glo(ncell,ntime))


  ind = 0
  DO ilat = 1, nlat-1
   DO ilon = 1, nlon

      ind=ind+1

      lon1 = 360./DBLE(nlon) * DBLE(ilon-1)
      lon2 = lon1 + 360./DBLE(nlon)

      lat1 = (90. + 90./DBLE(nlat)) - 180./DBLE(nlat)*DBLE(ilat)
      lat2 = lat1 - 180./DBLE(nlat)

      lon_glo(ind) = (lon1+lon2)*0.5
      lat_glo(ind) = (lat1+lat2)*0.5 

      bounds_lon_glo(1,ind) = lon1
      bounds_lon_glo(2,ind) = lon2
      bounds_lon_glo(3,ind) = lon2
      bounds_lon_glo(4,ind) = lon1

      bounds_lat_glo(1,ind) = lat1
      bounds_lat_glo(2,ind) = lat1
      bounds_lat_glo(3,ind) = lat2      
      bounds_lat_glo(4,ind) = lat2     

      field_temp_glo(ind,1) = DBLE(ind)

    ENDDO
  ENDDO

! Initialization of local variables

  CALL MPI_COMM_RANK(comm,rank,ierr)
  CALL MPI_COMM_SIZE(comm,size,ierr)

  IF (MOD(ncell, size) == 0) THEN
    ni = ncell/size
    ibegin = rank*ni
  ELSE
    IF (rank < MOD(ncell, size)) THEN
      ni = ncell/size + 1
      ibegin = rank*(ncell/size + 1)
    ELSE
      ni = ncell/size
      IF (rank == MOD(ncell, size)) THEN
        ibegin = rank*(ncell/size + 1)
      ELSE
        ibegin = MOD(ncell,size)*(ncell/size + 1) + (rank-MOD(ncell,size))*ncell/size
      END IF
    END IF
  END IF

  ALLOCATE(lon(ni))
  ALLOCATE(lat(ni))
  ALLOCATE(bounds_lon(4,ni))
  ALLOCATE(bounds_lat(4,ni))
  ALLOCATE(field_temp(ni,ntime)) 
  ALLOCATE(field_temp1(ni,ntime))
  ALLOCATE(field_temp2(ni,ntime))
  lon = lon_glo(ibegin:1+ibegin+ni)
  lat = lat_glo(ibegin:1+ibegin+ni)
  bounds_lon(:,:) = bounds_lon_glo(:,ibegin:1+ibegin+ni)
  bounds_lat(:,:) = bounds_lat_glo(:,ibegin:1+ibegin+ni)

  field_temp(:,:) = rank
  field_temp1(:,:) = rank
  field_temp2(:,:) = rank + 10


!!! Context ATMOSPHERE

  CALL xios_context_initialize("atmosphere",comm)
  CALL xios_get_handle("atmosphere",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_define_calendar(type="Gregorian", &
                            start_date=xios_date(2000, 01, 01, 00, 00, 00), &
                            time_origin=xios_date(1999, 01, 01, 15, 00, 00))

  CALL xios_set_domain_attr("face1", ni_glo=ncell, ibegin=ibegin, ni=ni, type='unstructured')
  CALL xios_set_domain_attr("face1", lonvalue_1d=lon, latvalue_1d=lat)
  CALL xios_set_domain_attr("face1", bounds_lon_1d=bounds_lon, bounds_lat_1d=bounds_lat)

  CALL xios_set_domain_attr("face2", ni_glo=ncell, ibegin=ibegin, ni=ni, type='unstructured')
  CALL xios_set_domain_attr("face2", lonvalue_1d=lon, latvalue_1d=lat)
  CALL xios_set_domain_attr("face2", bounds_lon_1d=bounds_lon, bounds_lat_1d=bounds_lat)
   
!!! Definition du timestep

  dtime%second=3600
  CALL xios_set_timestep(timestep=dtime)

!!! Fin de la definition du contexte

  CALL xios_close_context_definition()


!####################################################################################
!!! Boucle temporelle
!####################################################################################
    
    DO ts=1,1

!!! Mise a jour du pas de temps
      CALL xios_update_calendar(ts)

!!! On donne la valeur du champ atm
     CALL xios_send_field("temp1",field_temp1(:,1))
     CALL xios_send_field("temp2",field_temp2(:,1))

    ENDDO

!####################################################################################
!!! Finalisation
!####################################################################################

!!! Fin des contextes

    CALL xios_context_finalize()

    DEALLOCATE(lon_glo, lat_glo)
    DEALLOCATE(bounds_lon_glo, bounds_lat_glo)
    DEALLOCATE(field_temp_glo)
    DEALLOCATE(lon, lat)
    DEALLOCATE(bounds_lon, bounds_lat)
    DEALLOCATE(field_temp)
    DEALLOCATE(field_temp1, field_temp2)

!!! Fin de XIOS

    CALL MPI_COMM_FREE(comm, ierr)

    CALL xios_finalize()

    CALL MPI_FINALIZE(ierr)

  END PROGRAM test_regular






