PROGRAM test_xios2_cmip6

  USE xios
  USE mod_wait
  IMPLICIT NONE
  INCLUDE "mpif.h"

  INTEGER,PARAMETER :: model_timestep=600, il_unit=10
  INTEGER :: comm, rank, size_loc, ierr
  INTEGER :: ni,ibegin,iend,nj,jbegin,jend
  INTEGER :: i,j,l,ts,n, nb_pt, il_run
  CHARACTER(len=*),PARAMETER :: id="client"
  TYPE(xios_duration)  :: dtime
  TYPE(xios_context) :: ctx_hdl
  DOUBLE PRECISION,ALLOCATABLE :: lon_glo(:,:),lat_glo(:,:),lval(:)
  DOUBLE PRECISION,ALLOCATABLE :: field_A_glo (:,:,:)
  DOUBLE PRECISION,ALLOCATABLE :: lon(:,:),lat(:,:),lonvalue(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: field_atm_2D(:,:),field_atm_3D(:,:,:),field_srf_2D(:),field_srf_3D(:,:)
  DOUBLE PRECISION,ALLOCATABLE :: field_oce_2D(:,:),field_oce_3D(:,:,:)
  INTEGER, ALLOCATABLE :: kindex(:)

  INTEGER :: ni_glo, nj_glo,llm,nb_days_run,nb_run

  NAMELIST /param_toy/ ni_glo, nj_glo,llm,nb_days_run,nb_run

!!! MPI Initialization

  CALL MPI_INIT(ierr)

  CALL init_wait

!!! Lecture des parametres du run

  OPEN(unit=il_unit, file='param.def',status='old',iostat=ierr)
  READ (il_unit, nml=param_toy)
  PRINT *, ni_glo, nj_glo,llm,nb_days_run,nb_run

!!! XIOS Initialization (get the local communicator)

  CALL xios_initialize(id,return_comm=comm)

  CALL MPI_COMM_RANK(comm,rank,ierr)
  CALL MPI_COMM_SIZE(comm,size_loc,ierr)

!!! Initialisation et allocation des coordonnées globales et locales pour la grille régulière

  ALLOCATE (lon_glo(ni_glo,nj_glo),lat_glo(ni_glo,nj_glo))
  ALLOCATE (field_A_glo(ni_glo,nj_glo,llm))
  ALLOCATE (lval(llm))

  DO j=1,nj_glo
    DO i=1,ni_glo
      lon_glo(i,j)=(i-1)+(j-1)*ni_glo
      lat_glo(i,j)=1000+(i-1)+(j-1)*ni_glo
      DO l=1,llm
        field_A_glo(i,j,l)=(i-1)+(j-1)*ni_glo+10000*l
      ENDDO
    ENDDO
  ENDDO
  ni=ni_glo ; ibegin=0

  jbegin=0
  DO n=0,size_loc-1
    nj=nj_glo/size_loc
    IF (n<MOD(nj_glo,size_loc)) nj=nj+1
    IF (n==rank) exit
    jbegin=jbegin+nj
  ENDDO

  iend=ibegin+ni-1 ; jend=jbegin+nj-1

  ALLOCATE(lon(ni,nj),lat(ni,nj),lonvalue(ni,nj))
  lon(:,:)=lon_glo(ibegin+1:iend+1,jbegin+1:jend+1)
  lat(:,:)=lat_glo(ibegin+1:iend+1,jbegin+1:jend+1)

  DO i=1,llm
    lval(i)=i
  ENDDO

!###########################################################################
! Contexte ATM
!###########################################################################
  ALLOCATE(field_atm_2D(0:ni+1,-1:nj+2),field_atm_3D(0:ni+1,-1:nj+2,llm))
  field_atm_2D(1:ni,1:nj)=field_A_glo(ibegin+1:iend+1,jbegin+1:jend+1,1)
  field_atm_3D(1:ni,1:nj,:)=field_A_glo(ibegin+1:iend+1,jbegin+1:jend+1,:)

  CALL xios_context_initialize("atmosphere",comm)
  CALL xios_get_handle("atmosphere",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_set_axis_attr("axis_atm",n_glo=llm ,value=lval) ;

  CALL xios_set_domain_attr("domain_atm",ni_glo=ni_glo, nj_glo=nj_glo, ibegin=ibegin, ni=ni,jbegin=jbegin,nj=nj, type='rectilinear')
  CALL xios_set_domain_attr("domain_atm",data_dim=2, data_ibegin=-1, data_ni=ni+2, data_jbegin=-2, data_nj=nj+4)
  CALL xios_set_domain_attr("domain_atm",lonvalue_2D=lon,latvalue_2D=lat)


!!! Definition du timestep

  dtime%second=model_timestep
  CALL xios_set_timestep(timestep=dtime)

!!! Fin de la definition du contexte

  CALL xios_close_context_definition()


!###########################################################################
! Contexte SRF
!###########################################################################

!!! Initialisation des coordonnées globales et locales pour la grille indexee (1 point sur 2)

    nb_pt=ni*nj/2
    ALLOCATE(kindex(nb_pt),field_srf_2D(nb_pt),field_srf_3D(nb_pt,llm))
    DO i=1,nb_pt
      kindex(i)=2*i-1
    ENDDO
    field_srf_2D(1:nb_pt)=RESHAPE(field_A_glo(ibegin+1:iend+1:2,jbegin+1:jend+1,1),(/ nb_pt /))
    field_srf_3D(1:nb_pt,:)=RESHAPE(field_A_glo(ibegin+1:iend+1:2,jbegin+1:jend+1,:),(/ nb_pt,llm /))

  CALL xios_context_initialize("surface",comm)
  CALL xios_get_handle("surface",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_set_axis_attr("axis_srf",n_glo=llm ,value=lval)
  CALL xios_set_domain_attr("domain_srf",ni_glo=ni_glo, nj_glo=nj_glo, ibegin=ibegin, ni=ni,jbegin=jbegin,nj=nj, type='rectilinear')
  CALL xios_set_domain_attr("domain_srf",data_dim=1, data_ibegin=0, data_ni=nb_pt)
  CALL xios_set_domain_attr("domain_srf",data_i_index=kindex)
  CALL xios_set_domain_attr("domain_srf",lonvalue_2D=lon,latvalue_2D=lat)

!!! Definition du timestep

  dtime%second=model_timestep
  CALL xios_set_timestep(timestep=dtime)

!!! Fin de la definition du contexte SRF

  CALL xios_close_context_definition()

!###########################################################################
! Contexte OCE
!###########################################################################
  ALLOCATE(field_oce_2D(0:ni+1,-1:nj+2),field_oce_3D(0:ni+1,-1:nj+2,llm))
  field_oce_2D(1:ni,1:nj)=field_A_glo(ibegin+1:iend+1,jbegin+1:jend+1,1)
  field_oce_3D(1:ni,1:nj,:)=field_A_glo(ibegin+1:iend+1,jbegin+1:jend+1,:)

  CALL xios_context_initialize("nemo",comm)
  CALL xios_get_handle("nemo",ctx_hdl)
  CALL xios_set_current_context(ctx_hdl)

  CALL xios_set_axis_attr("axis_oce",n_glo=llm ,value=lval) ;

  CALL xios_set_domain_attr("domain_oce",ni_glo=ni_glo, nj_glo=nj_glo, ibegin=ibegin, ni=ni,jbegin=jbegin,nj=nj, type='curvilinear')
  CALL xios_set_domain_attr("domain_oce",data_dim=2, data_ibegin=-1, data_ni=ni+2, data_jbegin=-2, data_nj=nj+4)
  CALL xios_set_domain_attr("domain_oce",lonvalue_2D=lon,latvalue_2D=lat)


!!! Definition du timestep

  dtime%second=model_timestep
  CALL xios_set_timestep(timestep=dtime)

  CALL xios_close_context_definition()

!####################################################################################
!!! Boucle temporelle
!####################################################################################
    DO ts=1,86400/model_timestep*nb_days_run

      CALL xios_get_handle("atmosphere",ctx_hdl)
      CALL xios_set_current_context(ctx_hdl)

!!! Mise a jour du pas de temps

      CALL xios_update_calendar(ts)

!!! On donne la valeur du champ atm

      CALL xios_send_field("field_atm_2D",field_atm_2D)
      CALL xios_send_field("field_atm_3D",field_atm_3D)
      
!!! On change de contexte

      CALL xios_get_handle("surface",ctx_hdl)
      CALL xios_set_current_context(ctx_hdl)

!!! Mise a jour du pas de temps

      CALL xios_update_calendar(ts)

!!! On donne la valeur du champ srf

      CALL xios_send_field("field_srf_2D",field_srf_2D)
      CALL xios_send_field("field_srf_3D",field_srf_3D)

!!! On change de contexte

      CALL xios_get_handle("nemo",ctx_hdl)
      CALL xios_set_current_context(ctx_hdl)

!!! Mise a jour du pas de temps

      CALL xios_update_calendar(ts)

!!! On donne la valeur du champ srf

      CALL xios_send_field("field_oce_grid_2D",field_oce_2D)
      CALL xios_send_field("field_oce_grid_3D",field_oce_3D)

      CALL wait_us(5000) ;
    ENDDO

!####################################################################################
!!! Finalisation
!####################################################################################

!!! Fin des contextes

    CALL xios_context_finalize()
    CALL xios_get_handle("atmosphere",ctx_hdl)
    CALL xios_set_current_context(ctx_hdl)
    CALL xios_context_finalize()
    CALL xios_get_handle("surface",ctx_hdl)
    CALL xios_set_current_context(ctx_hdl)
    CALL xios_context_finalize()

    DEALLOCATE(lon, lat, lonvalue, field_atm_2D, field_atm_3D)
    DEALLOCATE(kindex, field_srf_2D, field_srf_3D)
    DEALLOCATE(field_oce_2D, field_oce_3D)
    DEALLOCATE(lon_glo,lat_glo,field_A_glo,lval)

!!! Fin de XIOS

    CALL MPI_COMM_FREE(comm, ierr)
      
    CALL xios_finalize()

  CALL MPI_FINALIZE(ierr)

END PROGRAM test_xios2_cmip6






