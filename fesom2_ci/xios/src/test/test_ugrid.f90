PROGRAM test_ugrid

  USE xios
  USE mod_wait
  IMPLICIT NONE
  INCLUDE "mpif.h"
  INTEGER :: comm_rank
  INTEGER :: comm_size
  INTEGER :: ierr

  CHARACTER(len=*),PARAMETER :: id="client"
  INTEGER :: comm
  TYPE(xios_duration) :: dtime
  CHARACTER(len=20) :: dtime_str
  TYPE(xios_date) :: date
  CHARACTER(len=20) :: date_str
  CHARACTER(len=15) :: calendar_type
  TYPE(xios_context) :: ctx_hdl
  INTEGER,PARAMETER :: ni_glo=100
  INTEGER,PARAMETER :: nj_glo=100
  INTEGER,PARAMETER :: llm=5
  DOUBLE PRECISION  :: lval(llm)=1, scalar = 5
  TYPE(xios_field) :: field_hdl
  TYPE(xios_fieldgroup) :: fieldgroup_hdl
  TYPE(xios_file) :: file_hdl
  LOGICAL :: ok

  DOUBLE PRECISION,DIMENSION(ni_glo,nj_glo) :: lon_glo,lat_glo
  DOUBLE PRECISION :: field_A_glo(ni_glo,nj_glo,llm)
  DOUBLE PRECISION,ALLOCATABLE :: lon(:,:),lat(:,:),field_A(:,:,:), lonvalue(:,:), axisValue(:), field_domain(:,:) ;
  INTEGER :: ni,ibegin,iend,nj,jbegin,jend
  INTEGER :: i,j,l,ts,n

  REAL,PARAMETER    :: Pi = 4.*atan(1.)

  INTEGER,PARAMETER :: ncells=6
  REAL :: cellx(ncells),celly(ncells),cellz(ncells)
  REAL :: cellx_bounds(4,ncells),celly_bounds(4,ncells),cellz_bounds(4,ncells)
  REAL :: cell_lon(ncells), cell_lat(ncells)
  REAL :: cell_bounds_lon(4,ncells), cell_bounds_lat(4,ncells)
  REAL :: field_cell(ncells) = (/1,2,3,4,5,6/)

  INTEGER,PARAMETER :: nedges=12
  REAL :: edgex(nedges),edgey(nedges),edgez(nedges)
  REAL :: edgex_bounds(2,nedges),edgey_bounds(2,nedges),edgez_bounds(2,nedges)
  REAL :: edge_lon(nedges), edge_lat(nedges)
  REAL :: edge_bounds_lon(2,nedges), edge_bounds_lat(2,nedges)
  REAL :: field_edge(nedges) = (/1,2,3,4,5,6,7,8,9,10,11,12/)

  INTEGER,PARAMETER :: nnodes=8
  REAL :: nodex(nnodes),nodey(nnodes),nodez(nnodes)
  REAL :: node_lon(nnodes), node_lat(nnodes)
  REAL :: field_node(nnodes) = (/1,2,3,4,5,6,7,8/)
  
    
  cellx(1) = 1
  celly(1) = 0  
  cellz(1) = 0 
  cellx_bounds(1,1)=  1 ; cellx_bounds(2,1)=  1 ; cellx_bounds(3,1)=  1  ; cellx_bounds(4,1)=  1
  celly_bounds(1,1)= -1 ; celly_bounds(2,1)=  1 ; celly_bounds(3,1)=  1  ; celly_bounds(4,1)= -1
  cellz_bounds(1,1)= -1 ; cellz_bounds(2,1)= -1 ; cellz_bounds(3,1)=  1  ; cellz_bounds(4,1)=  1
  
  cellx(2) = 0
  celly(2) = 1  
  cellz(2) = 0 
  cellx_bounds(1,2)= -1 ; cellx_bounds(2,2)=  1 ; cellx_bounds(3,2)=  1  ; cellx_bounds(4,2)= -1
  celly_bounds(1,2)=  1 ; celly_bounds(2,2)=  1 ; celly_bounds(3,2)=  1  ; celly_bounds(4,2)=  1
  cellz_bounds(1,2)= -1 ; cellz_bounds(2,2)= -1 ; cellz_bounds(3,2)=  1  ; cellz_bounds(4,2)=  1
    
  cellx(3) = -1
  celly(3) = 0  
  cellz(3) = 0 
  cellx_bounds(1,3)= -1 ; cellx_bounds(2,3)= -1 ; cellx_bounds(3,3)= -1  ; cellx_bounds(4,3)= -1
  celly_bounds(1,3)= -1 ; celly_bounds(2,3)=  1 ; celly_bounds(3,3)=  1  ; celly_bounds(4,3)= -1
  cellz_bounds(1,3)= -1 ; cellz_bounds(2,3)= -1 ; cellz_bounds(3,3)=  1  ; cellz_bounds(4,3)=  1
  
  cellx(4) = 0
  celly(4) = -1  
  cellz(4) = 0 
  cellx_bounds(1,4)= -1 ; cellx_bounds(2,4)=  1 ; cellx_bounds(3,4)=  1  ; cellx_bounds(4,4)= -1
  celly_bounds(1,4)= -1 ; celly_bounds(2,4)= -1 ; celly_bounds(3,4)= -1  ; celly_bounds(4,4)= -1
  cellz_bounds(1,4)= -1 ; cellz_bounds(2,4)= -1 ; cellz_bounds(3,4)=  1  ; cellz_bounds(4,4)=  1
    
  cellx(5) = 0
  celly(5) = 0  
  cellz(5) = 1 
  cellx_bounds(1,5)= -1 ; cellx_bounds(2,5)=  1 ; cellx_bounds(3,5)=  1  ; cellx_bounds(4,5)= -1
  celly_bounds(1,5)= -1 ; celly_bounds(2,5)= -1 ; celly_bounds(3,5)=  1  ; celly_bounds(4,5)=  1
  cellz_bounds(1,5)=  1 ; cellz_bounds(2,5)=  1 ; cellz_bounds(3,5)=  1  ; cellz_bounds(4,5)=  1
  
  cellx(6) = 0
  celly(6) = 0  
  cellz(6) = -1 
  cellx_bounds(1,6)= -1 ; cellx_bounds(2,6)=  1 ; cellx_bounds(3,6)=  1  ; cellx_bounds(4,6)= -1
  celly_bounds(1,6)= -1 ; celly_bounds(2,6)= -1 ; celly_bounds(3,6)=  1  ; celly_bounds(4,6)=  1
  cellz_bounds(1,6)= -1 ; cellz_bounds(2,6)= -1 ; cellz_bounds(3,6)= -1  ; cellz_bounds(4,6)= -1

  CALL cube2lonlat_1(cellx,celly,cellz,cell_lon,cell_lat)
  CALL cube2lonlat_2(cellx_bounds,celly_bounds,cellz_bounds,cell_bounds_lon,cell_bounds_lat)

  
  edgex(1) =  1
  edgey(1) =  0
  edgez(1) =  1
  edgex_bounds(1,1) =  1 ; edgex_bounds(2,1) =  1
  edgey_bounds(1,1) = -1 ; edgey_bounds(2,1) =  1
  edgez_bounds(1,1) =  1 ; edgez_bounds(2,1) =  1
  
  edgex(2) = -1
  edgey(2) =  0
  edgez(2) =  1
  edgex_bounds(1,2) = -1 ; edgex_bounds(2,2) = -1
  edgey_bounds(1,2) = -1 ; edgey_bounds(2,2) =  1
  edgez_bounds(1,2) =  1 ; edgez_bounds(2,2) =  1
  
  edgex(3) =  0
  edgey(3) =  1
  edgez(3) =  1
  edgex_bounds(1,3) = -1 ; edgex_bounds(2,3) =  1
  edgey_bounds(1,3) =  1 ; edgey_bounds(2,3) =  1
  edgez_bounds(1,3) =  1 ; edgez_bounds(2,3) =  1
  
  edgex(4) =  0
  edgey(4) = -1
  edgez(4) =  1
  edgex_bounds(1,4) = -1 ; edgex_bounds(2,4) =  1
  edgey_bounds(1,4) = -1 ; edgey_bounds(2,4) = -1
  edgez_bounds(1,4) =  1 ; edgez_bounds(2,4) =  1

  edgex(5) =  1
  edgey(5) =  0
  edgez(5) = -1
  edgex_bounds(1,5) =  1 ; edgex_bounds(2,5) =  1
  edgey_bounds(1,5) = -1 ; edgey_bounds(2,5) =  1
  edgez_bounds(1,5) = -1 ; edgez_bounds(2,5) = -1
  
  edgex(6) = -1
  edgey(6) =  0
  edgez(6) =  -1
  edgex_bounds(1,6) = -1 ; edgex_bounds(2,6) = -1
  edgey_bounds(1,6) = -1 ; edgey_bounds(2,6) =  1
  edgez_bounds(1,6) = -1 ; edgez_bounds(2,6) = -1
  
  edgex(7) =  0
  edgey(7) =  1
  edgez(7) =  -1
  edgex_bounds(1,7) = -1 ; edgex_bounds(2,7) =  1
  edgey_bounds(1,7) =  1 ; edgey_bounds(2,7) =  1
  edgez_bounds(1,7) = -1 ; edgez_bounds(2,7) = -1
  
  edgex(8) =  0
  edgey(8) = -1
  edgez(8) =  -1
  edgex_bounds(1,8) = -1 ; edgex_bounds(2,8) =  1
  edgey_bounds(1,8) = -1 ; edgey_bounds(2,8) = -1
  edgez_bounds(1,8) = -1 ; edgez_bounds(2,8) = -1
 
  edgex(9) =  1
  edgey(9) =  1
  edgez(9) =  0
  edgex_bounds(1,9) =  1 ; edgex_bounds(2,9) =  1
  edgey_bounds(1,9) =  1 ; edgey_bounds(2,9) =  1
  edgez_bounds(1,9) = -1 ; edgez_bounds(2,9) =  1

  edgex(10) = -1
  edgey(10) =  1
  edgez(10) =  0
  edgex_bounds(1,10) = -1 ; edgex_bounds(2,10) = -1
  edgey_bounds(1,10) =  1 ; edgey_bounds(2,10) =  1
  edgez_bounds(1,10) = -1 ; edgez_bounds(2,10) =  1

  edgex(11) = -1
  edgey(11) = -1
  edgez(11) =  0
  edgex_bounds(1,11) = -1 ; edgex_bounds(2,11) = -1
  edgey_bounds(1,11) = -1 ; edgey_bounds(2,11) = -1
  edgez_bounds(1,11) = -1 ; edgez_bounds(2,11) =  1

  edgex(12) =  1
  edgey(12) = -1
  edgez(12) =  0
  edgex_bounds(1,12) =  1 ; edgex_bounds(2,12) =  1
  edgey_bounds(1,12) = -1 ; edgey_bounds(2,12) = -1
  edgez_bounds(1,12) = -1 ; edgez_bounds(2,12) =  1

  CALL cube2lonlat_1(edgex, edgey, edgez, edge_lon, edge_lat)
  CALL cube2lonlat_2(edgex_bounds, edgey_bounds, edgez_bounds, edge_bounds_lon, edge_bounds_lat)

  nodex(1) = -1
  nodey(1) = -1
  nodez(1) = -1

  nodex(2) = 1
  nodey(2) = -1
  nodez(2) = -1

  nodex(3) = 1
  nodey(3) = 1
  nodez(3) = -1

  nodex(4) = -1
  nodey(4) = 1
  nodez(4) = -1

  nodex(5) = -1
  nodey(5) = -1
  nodez(5) =  1

  nodex(6) =  1
  nodey(6) = -1
  nodez(6) =  1

  nodex(7) =  1
  nodey(7) =  1
  nodez(7) =  1

  nodex(8) = -1
  nodey(8) =  1
  nodez(8) =  1

  CALL cube2lonlat_1(nodex,nodey,nodez,node_lon,node_lat)
    
!!! MPI Initialization

  CALL MPI_INIT(ierr)

  CALL init_wait

!!! XIOS Initialization (get the local communicator)

  CALL xios_initialize(id,return_comm=comm)
  CALL xios_context_initialize(id, comm)
  
  CALL MPI_COMM_RANK(comm,comm_rank,ierr)
  CALL MPI_COMM_SIZE(comm,comm_size,ierr)

  CALL xios_set_domain_attr("cells",ni_glo=ncells, ibegin=0, ni=ncells, nvertex=4 , type='unstructured')
  CALL xios_set_domain_attr("cells",lonvalue_1d=cell_lon, latvalue_1d=cell_lat, bounds_lon_1d=cell_bounds_lon, bounds_lat_1d= cell_bounds_lat)
 
  CALL xios_set_domain_attr("edges",ni_glo=nedges, ibegin=0, ni=nedges, nvertex=2 , type='unstructured')
  CALL xios_set_domain_attr("edges",lonvalue_1d=edge_lon, latvalue_1d=edge_lat, bounds_lon_1d=edge_bounds_lon, bounds_lat_1d= edge_bounds_lat)
 
  CALL xios_set_domain_attr("nodes",ni_glo=nnodes, ibegin=0, ni=nnodes, nvertex=1 , type='unstructured')
  CALL xios_set_domain_attr("nodes",lonvalue_1d=node_lon, latvalue_1d=node_lat)

  dtime%second = 3600
  CALL xios_set_timestep(dtime)
  CALL xios_close_context_definition
  
  DO ts=1,1
    CALL xios_update_calendar(ts)
    CALL xios_send_field("field_node",field_node) 
    CALL xios_send_field("field_edge",field_edge) 
    CALL xios_send_field("field_cell",field_cell) 
    CALL wait_us(5000) ;
  ENDDO

  CALL xios_context_finalize()
  CALL xios_finalize()

  CALL MPI_FINALIZE(ierr)

CONTAINS 
  
  SUBROUTINE cube2sphere(xc,yc,zc,xs,ys,zs)
  IMPLICIT NONE
  REAL,INTENT(IN)  :: xc, yc, zc
  REAL,INTENT(OUT) :: xs, ys, zs
  
    xs=xc/sqrt(1-yc*yc/2-zc*zc/2+yc*yc*zc*zc/3)
    ys=yc/sqrt(1-xc*xc/2-zc*zc/2+xc*xc*zc*zc/3)
    zs=zc/sqrt(1-xc*xc/2-yc*yc/2+xc*xc*yc*yc/3)
  END SUBROUTINE cube2sphere
  
  SUBROUTINE xyz2lonlat(x,y,z,lon,lat)
  IMPLICIT NONE
  REAL,INTENT(IN)  :: x,y,z
  REAL,INTENT(OUT) :: lon,lat
  REAL             :: norm
  
    norm=sqrt(x*x+y*y+z*z)
  
    lat=asin(z/norm)*180./Pi
    lon=atan2(y/norm,x/norm)*180/Pi
  END SUBROUTINE xyz2lonlat
  
  SUBROUTINE cube2lonlat_0(xc,yc,zc,lon,lat)
  IMPLICIT NONE
    REAL,INTENT(IN)  :: xc,yc,zc
    REAL,INTENT(OUT) :: lon,lat
    REAL             :: xs,ys,zs
    CALL cube2sphere(xc,yc,zc,xs,ys,zs)
    CALL xyz2lonlat(xs,ys,zs,lon,lat)
  END SUBROUTINE  cube2lonlat_0

  SUBROUTINE cube2lonlat_1(xc,yc,zc,lon,lat)
  IMPLICIT NONE
  REAL,INTENT(IN),DIMENSION(:)  :: xc,yc,zc
  REAL,INTENT(OUT),DIMENSION(:) :: lon,lat
  INTEGER :: i
    DO i=1,SIZE(xc,1)
      CALL cube2lonlat_0(xc(i),yc(i),zc(i),lon(i),lat(i))
    ENDDO
  END SUBROUTINE cube2lonlat_1
 
  SUBROUTINE cube2lonlat_2(xc,yc,zc,lon,lat)
  IMPLICIT NONE
  REAL,INTENT(IN),DIMENSION(:,:)  :: xc,yc,zc
  REAL,INTENT(OUT),DIMENSION(:,:) :: lon,lat
  INTEGER :: i,j
  
    DO j=1,SIZE(xc,2)
      DO i=1,SIZE(xc,1)
        CALL cube2lonlat_0(xc(i,j),yc(i,j),zc(i,j),lon(i,j),lat(i,j))
      ENDDO
    ENDDO

  END SUBROUTINE cube2lonlat_2

END PROGRAM test_ugrid





