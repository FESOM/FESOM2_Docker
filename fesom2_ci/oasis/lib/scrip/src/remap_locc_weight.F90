!****
!                    ************************
!                    *     OASIS MODULE     *
!                    *     ------------     *
!                    ************************
!**** 
!**********************************************************************
!     This module belongs to the SCRIP library. It is derived from
!     remap_dist_gaus_wgt.F90 (OASIS compatible version)
!
!     Modified by         E. Maisonnave,  CERFACS           3.10.2020
!
!***********************************************************************
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!
!     This module contains necessary routines for performing an 
!     interpolation using the n nearest neighbors algorithm,
!     from the debouch (ocean) grid point to the river mouth 
!     (land) grid points. It has to be reverted, and weighted,
!     to produce an interpolation suitable for runoff exchange.
!-----------------------------------------------------------------------
!
!     Copyright (c) 1997, 1998 the Regents of the University of 
!       California.
!
!     This software and ancillary information (herein called software) 
!     called SCRIP is made available under the terms described here.  
!     The software has been approved for release with associated 
!     LA-CC Number 98-45.
!
!     Unless otherwise indicated, this software has been authored
!     by an employee or employees of the University of California,
!     operator of the Los Alamos National Laboratory under Contract
!     No. W-7405-ENG-36 with the U.S. Department of Energy.  The U.S.
!     Government has rights to use, reproduce, and distribute this
!     software.  The public may copy and use this software without
!     charge, provided that this Notice and any statement of authorship
!     are reproduced on all copies.  Neither the Government nor the
!     University makes any warranty, express or implied, or assumes
!     any liability or responsibility for the use of this software.
!
!     If software is modified to produce derivative works, such modified
!     software should be clearly marked, so as not to confuse it with 
!     the version available from Los Alamos National Laboratory.
!
!***********************************************************************

module remap_locc_weight

   !-----------------------------------------------------------------------

   use kinds_mod     ! defines common data types
   use constants     ! defines common constants
   use grids         ! module containing grid info
   use remap_vars    ! module containing remap info
   use timers
   use mod_oasis_flush
!$ use omp_lib

   implicit none

   !-----------------------------------------------------------------------
   !
   !     module variables
   !
   !-----------------------------------------------------------------------

   real (kind=dbl_kind), dimension(:), allocatable, save ::  &
      coslat, sinlat,  & ! cosine, sine of grid lats (for distance) 
      coslon, sinlon,  & ! cosine, sine of grid lons (for distance) 
      wgtstmp            ! an array to hold the link weight

   integer (kind=int_kind) :: il_nbthreads = 1

   !***********************************************************************

contains

   !***********************************************************************

   subroutine remap_locc_wgt (num_neighbors, norm_type, r_varmul, &
                              mpi_comm_map, mpi_size_map, &
                              mpi_rank_map, mpi_root_map)

      !-----------------------------------------------------------------------
      !
      !     this routine computes the inverse-distance weights for a
      !     nearest-neighbor interpolation.
      !
      !-----------------------------------------------------------------------
      !-----------------------------------------------------------------------
      !
      !     input variables
      !
      !-----------------------------------------------------------------------

      integer (kind=int_kind), INTENT(in) :: num_neighbors     ! number of neighbours

      integer (kind=int_kind), INTENT(in) :: norm_type     ! nkind of weight normalisation

      real (kind=dbl_kind), INTENT(in)    :: r_varmul   ! Gaussian variance

      integer (kind=int_kind), INTENT(in) :: mpi_comm_map, mpi_rank_map, mpi_size_map, mpi_root_map

      !-----------------------------------------------------------------------
      !
      !     local variables
      !
      !-----------------------------------------------------------------------

      logical (kind=log_kind) :: ll_debug  ! for debug outputs

      integer (kind=int_kind) :: i_n,            &
                                 dst_add        ! destination address

      integer (kind=int_kind), dimension(num_neighbors) :: nbr_add  ! source address at nearest neighbors

      real (kind=dbl_kind), dimension(num_neighbors) ::   nbr_dist  ! angular distance four nearest neighbors

      real (kind=dbl_kind) :: coslat_dst,   &  ! cos(lat) of destination grid point
                              coslon_dst,   &  ! cos(lon) of destination grid point
                              sinlat_dst,   &  ! sin(lat) of destination grid point
                              sinlon_dst       ! sin(lon) of destination grid point

      real (kind=dbl_kind) :: sum_wts
      real (kind=dbl_kind) :: rl_local_variance
      real (kind=dbl_kind) :: rl_varmul                                   ! local Gaussian variance
      real (kind=dbl_kind) :: dl_test
      real (kind=dbl_kind) :: rl_nb_distance                              ! local neighbour distance

      integer (kind=int_kind) :: il_splitsize
      integer (kind=int_kind) :: ib_proc
      integer (kind=int_kind) :: ib_thread, ib_nb
      integer (kind=int_kind) :: il_n1_add, il_n2_add
      integer (kind=int_kind) :: il_nb_pairs
      integer (kind=int_kind) :: buff_base
      integer (kind=int_kind), dimension(:), allocatable :: ila_mpi_sz
      integer (kind=int_kind), dimension(:), allocatable :: ila_mpi_mn
      integer (kind=int_kind), dimension(:), allocatable :: ila_mpi_mx
      integer (kind=int_kind), dimension(:), allocatable :: ila_thr_sz
      integer (kind=int_kind), dimension(:), allocatable :: ila_thr_mn
      integer (kind=int_kind), dimension(:), allocatable :: ila_thr_mx
      integer (kind=int_kind), dimension(:), allocatable :: ila_num_links_mpi
      integer (kind=int_kind), dimension(:,:), allocatable :: ila_req_mpi
      integer (kind=int_kind), dimension(:,:,:), allocatable :: ila_sta_mpi
      character (LEN=14) :: cl_envvar
      integer (kind=int_kind) :: il_envthreads, il_err
      logical :: l_dist_wg
#ifdef REMAP_TIMING
      logical :: ll_timing = .true.
      real    (kind=8), dimension(:,:), allocatable :: dla_timer
      real    (kind=8)        :: dl_tstart, dl_tstop
      integer (kind=int_kind) :: il_mythread
#endif

      !-----------------------------------------------------------------------
      !
      if (nlogprt .ge. 2) then
         write (UNIT = nulou,FMT = *)' '
         write (UNIT = nulou,FMT = *)'Entering routine remap_locc'
         call OASIS_FLUSH_SCRIP(nulou)
      endif

      if (.not. lstore_grid1_area .or. .not. lstore_grid2_area) then
         write(nulou,*) 'ERROR: remap_locc failed with missing areas in areas.nc'
         call OASIS_FLUSH_SCRIP(nulou)
         stop
      endif
      !
      !-----------------------------------------------------------------------
      !
      !     compute mappings from grid2 to grid1
      !
      !-----------------------------------------------------------------------
#ifdef REMAP_TIMING
      if (ll_timing) call timer_start(2,'remap_locc alloc-res_ave')
#endif

      rl_varmul = 0.
      dl_test = 0.0

      if ( norm_type == norm_locc_gauswgt ) then

        ! Check that variance is not zero
        IF ( r_varmul < epsilon(1.) ) then
          write (UNIT = nulou,FMT = *) '***** ERROR *****'
          write (UNIT = nulou,FMT = *) 'Namcouple GAUSWGT variance $VAR cannot be zero'
          call OASIS_FLUSH_SCRIP(nulou)
          stop
        ENDIF

        ! if num_neighbors = 1, GAUSWGT not applicable
        IF ( num_neighbors < 2 ) then
          write (UNIT = nulou,FMT = *) '***** WARNING *****'
          write (UNIT = nulou,FMT = *) 'For GAUSWGT, $NV has to be bigger than 1'
          write (UNIT = nulou,FMT = *) 'DISTWGT performed instead of GAUSWGT'
          call OASIS_FLUSH_SCRIP(nulou)

        ELSE
          rl_varmul = r_varmul
        ENDIF

      endif

      !***
      !*** allocate wgtstmp to be consistent with store_link interface
      !***

      allocate (wgtstmp(num_wts))

      !***
      !*** compute cos, sin of lat/lon on source grid for distance
      !*** calculations
      !***

      allocate (coslat(grid2_size), coslon(grid2_size), sinlat(grid2_size), sinlon(grid2_size))
      coslat = cos(grid2_center_lat)
      coslon = cos(grid2_center_lon)
      sinlat = sin(grid2_center_lat)
      sinlon = sin(grid2_center_lon)

#ifdef REMAP_TIMING
      if (ll_timing) call timer_stop(2)
#endif

      !***
      !*** precompute best scheduling of target grid points
      !***

      allocate(ila_mpi_mn(mpi_size_map))
      allocate(ila_mpi_mx(mpi_size_map))

      if (mpi_size_map .gt. 1) then

         allocate(ila_mpi_sz(mpi_size_map))
         il_splitsize = count(grid1_mask)
         ila_mpi_sz(:) = floor(real(il_splitsize)/mpi_size_map)
         ila_mpi_sz(1:il_splitsize-sum(ila_mpi_sz)) = ila_mpi_sz(1:il_splitsize-sum(ila_mpi_sz)) + 1

         ila_mpi_mn(:) = 0
         ib_proc = 1
         il_splitsize = 0
         do dst_add = 1, grid1_size
            if (grid1_mask(dst_add)) then
               if (ila_mpi_mn(ib_proc).eq.0) &
                  ila_mpi_mn(ib_proc) = dst_add 
               il_splitsize = il_splitsize + 1
               if (il_splitsize .eq. ila_mpi_sz(ib_proc)) then
                  il_splitsize = 0
                  ila_mpi_mx(ib_proc) = dst_add
                  ib_proc = ib_proc + 1
               end if
            end if
         end do

         deallocate(ila_mpi_sz)

      else

         ila_mpi_mn(1) = 1
         ila_mpi_mx(1) = grid1_size

      endif


      call get_environment_variable(name='OASIS_OMP_NUM_THREADS', &
         & value=cl_envvar, status=il_err)
      if ( il_err .ne. 0) then
         il_envthreads = 0
      else
         read(cl_envvar,*) il_envthreads
      end if

!$OMP PARALLEL NUM_THREADS(il_envthreads) DEFAULT(NONE) &
!$OMP SHARED(il_envthreads) &
!$OMP SHARED(num_neighbors) &
!$OMP SHARED(grid1_mask,grid2_mask,grid2_frac) &
!$OMP SHARED(grid1_area_in,grid2_area_in) &
!$OMP SHARED(grid1_center_lat,grid1_center_lon) &
!$OMP SHARED(bin_addr2,nulou,sga_remap,num_wts) &
!$OMP SHARED(dl_test,norm_type) &
!$OMP PRIVATE(nlogprt) &
!$OMP SHARED(coslat,coslon,sinlat,sinlon) &
!$OMP SHARED(l_dist_wg,rl_varmul) &
!$OMP PRIVATE(sum_wts) &
!$OMP PRIVATE(wgtstmp,dst_add,nbr_add,nbr_dist) &
!$OMP PRIVATE(coslat_dst,coslon_dst,sinlat_dst,sinlon_dst) &
!$OMP PRIVATE(ll_debug) &
!$OMP SHARED(il_nbthreads) &
!$OMP SHARED(mpi_rank_map,mpi_root_map,ila_mpi_mn,ila_mpi_mx) &
!$OMP SHARED(ila_thr_sz,ila_thr_mn,ila_thr_mx) &
!$OMP PRIVATE(ib_nb,i_n,rl_local_variance) &
!$OMP PRIVATE(il_n1_add,il_n2_add,rl_nb_distance,il_nb_pairs) &
#ifdef REMAP_TIMING
!$OMP PRIVATE(ib_thread,il_splitsize) &
!$OMP SHARED(ll_timing,dla_timer) &
!$OMP PRIVATE(il_mythread,dl_tstart,dl_tstop)

!$    il_mythread = OMP_GET_THREAD_NUM () + 1
#else
!$OMP PRIVATE(ib_thread,il_splitsize)
#endif

!$OMP SINGLE

      il_nbthreads = 1
!$    il_nbthreads = OMP_GET_NUM_THREADS ()

#ifdef REMAP_TIMING
      if (ll_timing) then
         if (il_nbthreads.gt.1) then
!$          dl_tstart = OMP_GET_WTIME()
         else
            call timer_start(3,'remap_locc distr')
         end if
      end if
#endif
      allocate(ila_thr_mn(il_nbthreads))
      allocate(ila_thr_mx(il_nbthreads))

      if (il_nbthreads .gt. 1) then

#ifdef REMAP_TIMING
         if (ll_timing) then
            allocate(dla_timer(il_nbthreads,4))
            dla_timer(:,:) = 0.0
         end if
#endif
         nlogprt = 0

         allocate(ila_thr_sz(il_nbthreads))
         il_splitsize = COUNT(grid1_mask(ila_mpi_mn(mpi_rank_map+1):&
            & ila_mpi_mx(mpi_rank_map+1)))
         ila_thr_sz(:) = floor(real(il_splitsize)/il_nbthreads)
         ila_thr_sz(1:il_splitsize-sum(ila_thr_sz)) = ila_thr_sz(1:il_splitsize-sum(ila_thr_sz)) + 1

         ila_thr_mn(:) = 0
         ib_thread = 1
         il_splitsize = 0
         DO dst_add = ila_mpi_mn(mpi_rank_map+1), ila_mpi_mx(mpi_rank_map+1)
            if (grid1_mask(dst_add)) then
               if (ila_thr_mn(ib_thread).eq.0) &
                  ila_thr_mn(ib_thread) = dst_add 
               il_splitsize = il_splitsize + 1
               if (il_splitsize .eq. ila_thr_sz(ib_thread)) then
                  il_splitsize = 0
                  ila_thr_mx(ib_thread) = dst_add
                  ib_thread = ib_thread + 1
               end if
            end if
         end do

         allocate(sga_remap(il_nbthreads))

         do ib_thread = 1, il_nbthreads
            il_splitsize = num_neighbors*ila_thr_sz(ib_thread)
            sga_remap(ib_thread)%max_links = il_splitsize 
            sga_remap(ib_thread)%num_links = 0 
            allocate(sga_remap(ib_thread)%grid1_add(il_splitsize))
            allocate(sga_remap(ib_thread)%grid2_add(il_splitsize))
            allocate(sga_remap(ib_thread)%wts(num_wts,il_splitsize))
         end do

         deallocate(ila_thr_sz)

      else

         ila_thr_mn(1) = ila_mpi_mn(mpi_rank_map+1)
         ila_thr_mx(1) = ila_mpi_mx(mpi_rank_map+1)

      end if
#ifdef REMAP_TIMING
      if (ll_timing) then
         if (il_nbthreads.gt.1) then
!$          dl_tstop = OMP_GET_WTIME() 
            dla_timer(il_mythread,1)=dla_timer(il_mythread,1) + dl_tstop - dl_tstart
         else
            call timer_stop(3)
         end if
      end if
#endif
!$OMP END SINGLE


      !***
      !*** loop over destination grid 
      !***
!$OMP DO SCHEDULE(STATIC,1)
      thread_loop: do ib_thread = 1, il_nbthreads

         grid_loop1: do dst_add =ila_thr_mn(ib_thread), ila_thr_mx(ib_thread)

            if (.not. grid1_mask(dst_add)) cycle grid_loop1

#ifdef REMAP_TIMING
            if (ll_timing) then
               if (il_nbthreads.gt.1) then
!$                dl_tstart = OMP_GET_WTIME()
               else
                  call timer_start(4,'remap_locc search')
               end if
            end if
#endif
            coslat_dst = cos(grid1_center_lat(dst_add))
            coslon_dst = cos(grid1_center_lon(dst_add))
            sinlat_dst = sin(grid1_center_lat(dst_add))
            sinlon_dst = sin(grid1_center_lon(dst_add))

            !***
            !*** find nearest grid points on target grid
            !*** and distances to each point
            !***

            call grid_search_nbr(nbr_add, nbr_dist,                   &
                                 coslat_dst, coslon_dst, sinlat_dst, sinlon_dst, &
                                 bin_addr2, num_neighbors)

#ifdef REMAP_TIMING
            if (ll_timing) then
               if (il_nbthreads.gt.1) then
!$                dl_tstop = OMP_GET_WTIME() 
                  dla_timer(ib_thread,2) = dla_timer(ib_thread,2) + dl_tstop - dl_tstart
               else
                  call timer_stop(4)
               end if
            end if
#endif

            !***
            !*** store distance in the weight link
            !***

#ifdef REMAP_TIMING
            if (ll_timing) then
               if (il_nbthreads.gt.1) then
!$                dl_tstart = OMP_GET_WTIME()
               else
                  call timer_start(5,'remap_locc store_link')
               end if
            end if
#endif
            ! now , if gaussian weights, compute local variance in parallel
            if ( norm_type == norm_locc_gauswgt ) THEN
               rl_local_variance = 0.
               il_nb_pairs = 0
               do i_n = 1, num_neighbors-1
                  do ib_nb = i_n+1, num_neighbors
                     il_n1_add = nbr_add(i_n)
                     il_n2_add = nbr_add(ib_nb)
                     rl_nb_distance = sinlat(il_n2_add)*sinlat(il_n1_add) +  &
                                      coslat(il_n2_add)*coslat(il_n1_add)*    &
                                      ( coslon(il_n2_add)*coslon(il_n1_add) + &
                                        sinlon(il_n2_add)*sinlon(il_n1_add) )
                     rl_nb_distance = MAX ( MIN ( rl_nb_distance, 1.d0), -1.d0)
                     rl_nb_distance = acos ( rl_nb_distance )
                     rl_local_variance = rl_local_variance + rl_nb_distance
                     il_nb_pairs = il_nb_pairs + 1
                  enddo
               enddo
               ! if less than two neighbours, DISTWGT with one neighbour will be performed
               ! if not, average distance and calculate variance
               if ( il_nb_pairs > 0 .AND. MAXVAL(nbr_dist**2) < .0001 ) THEN

                  rl_local_variance = rl_varmul * ( rl_local_variance / dble(il_nb_pairs) ) ** 2
                  ! EM : here, a check of the target/source distance is missing
                  !      If this distance is too big, the exponential leads to 
                  !      NaN values 
                  nbr_dist(1:num_neighbors) = exp(.5 * nbr_dist(1:num_neighbors) * &
                                                  nbr_dist(1:num_neighbors) / rl_local_variance)
               end if
            end if

            ! Total contributions (inverse values)
            if ( norm_type == norm_locc_distwgt .or. &
                 norm_type == norm_locc_gauswgt ) &
               sum_wts = SUM( one / (nbr_dist(1:num_neighbors) + epsilon(dl_test)))

            ! Normalisationns
            do i_n=1,num_neighbors
               if ( norm_type == norm_locc_uniform ) then
                  ! Weighted by the number of neighbours 
                  wgtstmp(1) = one / DBLE ( num_neighbors ) 
               else
                  ! Weighted by the inverse of the distance src/dst
                  wgtstmp(1) = one / ( nbr_dist(i_n) * sum_wts )
               endif

               ! Normalisation by surface (conservativeness)
               wgtstmp(1) =  wgtstmp(1) * grid1_area_in(dst_add) / &
                                          grid2_area_in(nbr_add(i_n))

               call store_inv_link_nbr(nbr_add(i_n), dst_add, wgtstmp, ib_thread)

               grid2_frac(nbr_add(i_n)) = one
            end do

#ifdef REMAP_TIMING
            if (ll_timing) then
               if (il_nbthreads.gt.1) then
!$                dl_tstop = OMP_GET_WTIME() 
                  dla_timer(ib_thread,3) = dla_timer(ib_thread,3) + dl_tstop - dl_tstart
               else
                  call timer_stop(5)
               end if
            end if
#endif
         end do grid_loop1

      end do thread_loop
!$OMP END DO

!$OMP END PARALLEL

      if (il_nbthreads .gt. 1) then
#ifdef REMAP_TIMING
         if (ll_timing) call timer_start(3,'remap_locc gather_lk')
#endif
         sga_remap(1)%start_pos = 1
         il_splitsize = sga_remap(1)%num_links
         do ib_thread = 2, il_nbthreads
            il_splitsize = il_splitsize + sga_remap(ib_thread)%num_links
            sga_remap(ib_thread)%start_pos = sga_remap(ib_thread-1)%start_pos + &
               sga_remap(ib_thread-1)%num_links
         end do

         num_links_map1 = il_splitsize
         if (num_links_map1 > max_links_map1) &
            call resize_remap_vars(1,num_links_map1-max_links_map1)

         do ib_thread = 1, il_nbthreads
            grid1_add_map1(sga_remap(ib_thread)%start_pos: &
               sga_remap(ib_thread)%start_pos+             &
               sga_remap(ib_thread)%num_links-1) =         &
               sga_remap(ib_thread)%grid1_add
            grid2_add_map1(sga_remap(ib_thread)%start_pos: &
               sga_remap(ib_thread)%start_pos+             &
               sga_remap(ib_thread)%num_links-1) =         &
               sga_remap(ib_thread)%grid2_add
            wts_map1     (:,sga_remap(ib_thread)%start_pos: &
               sga_remap(ib_thread)%start_pos+            &
               sga_remap(ib_thread)%num_links-1) =        &
               sga_remap(ib_thread)%wts

         end do

#ifdef REMAP_TIMING
         if (ll_timing) call timer_stop(3)
#endif
         if (nlogprt.ge.2) then

            do ib_thread = 1, il_nbthreads
               if (sga_remap(ib_thread)%nb_resize.gt.0) then
                  write(nulou,*) ' Number of thread_resize_remap_vars on thread ',&
                     ib_thread, ' = ', sga_remap(ib_thread)%nb_resize
               end if
            end do

         end if

#ifdef REMAP_TIMING
         if (ll_timing.and.nlogprt.ge.2) then
            write(nulou,*) ' On master thread '
            call timer_print(2)
            call timer_clear(2)
            do ib_thread = 1,il_nbthreads
               write(nulou,*) ' On thread ',ib_thread
               write(nulou,"(' Elapsed time for timer ',A24,':',1x,f10.4)")&
                  & 'remap_locc distr     ',dla_timer(ib_thread,1)
               write(nulou,"(' Elapsed time for timer ',A24,':',1x,f10.4)")&
                  & 'remap_locc search    ',dla_timer(ib_thread,2)
               write(nulou,"(' Elapsed time for timer ',A24,':',1x,f10.4)")&
                  & 'remap_locc store_link',dla_timer(ib_thread,3)
            end do
            deallocate(dla_timer)
            write(nulou,*) ' On master thread '
            call timer_print(3)
            call timer_clear(3)
         end if

      else

         if (ll_timing.and.nlogprt.ge.2) then
            do i_n = 2, 5
               call timer_print(i_n)
               call timer_clear(i_n)
            end do
         end if
#endif
      end if

      ! Gather the complete results on master proc

      if (mpi_size_map .gt. 1) then

         IF (mpi_rank_map == mpi_root_map) THEN
            ALLOCATE(ila_num_links_mpi(mpi_size_map))
         ELSE
            ALLOCATE(ila_num_links_mpi(1))
         END IF

         CALL MPI_Gather (num_links_map1,   1,MPI_INT,&
            &             ila_num_links_mpi,1,MPI_INT,&
            &             mpi_root_map,mpi_comm_map,il_err)

         
         IF (mpi_rank_map == mpi_root_map) THEN
            num_links_map1 = SUM(ila_num_links_mpi)
            if (num_links_map1 > max_links_map1) &
                  call resize_remap_vars(1,num_links_map1-max_links_map1)
            
            ALLOCATE(ila_req_mpi(4,mpi_size_map-1))
            ALLOCATE(ila_sta_mpi(MPI_STATUS_SIZE,4,mpi_size_map-1))

            DO i_n = 1, mpi_size_map-1
               buff_base = SUM(ila_num_links_mpi(1:i_n))+1
               CALL MPI_IRecv(grid1_add_map1(buff_base),&
                  & ila_num_links_mpi(i_n+1),MPI_INT,i_n,1,mpi_comm_map,&
                  & ila_req_mpi(1,i_n),il_err)

               CALL MPI_IRecv(grid2_add_map1(buff_base),&
                  & ila_num_links_mpi(i_n+1),MPI_INT,i_n,2,mpi_comm_map,&
                  & ila_req_mpi(2,i_n),il_err)

               CALL MPI_IRecv(wts_map1(1,buff_base),&
                  & num_wts*ila_num_links_mpi(i_n+1),MPI_DOUBLE,i_n,0,mpi_comm_map,&
                  & ila_req_mpi(3,i_n),il_err)

               CALL MPI_IRecv(grid2_frac(ila_mpi_mn(i_n+1)),&
                  & ila_mpi_mx(i_n+1)-ila_mpi_mn(i_n+1)+1,MPI_DOUBLE,i_n,0,mpi_comm_map,&
                  & ila_req_mpi(4,i_n),il_err)

            END DO

            DO i_n=1,4
               CALL MPI_Waitall(mpi_size_map-1,ila_req_mpi(i_n,:),ila_sta_mpi(1,i_n,1),il_err)
            END DO

            DEALLOCATE(ila_req_mpi)
            DEALLOCATE(ila_sta_mpi)

         ELSE

            CALL MPI_Send(grid1_add_map1,num_links_map1,MPI_INT,&
               & mpi_root_map,1,mpi_comm_map,il_err)

            CALL MPI_Send(grid2_add_map1,num_links_map1,MPI_INT,&
               & mpi_root_map,2,mpi_comm_map,il_err)

            CALL MPI_Send(wts_map1,num_wts*num_links_map1,MPI_DOUBLE,&
               & mpi_root_map,0,mpi_comm_map,il_err)

            CALL MPI_Send(grid2_frac(ila_mpi_mn(mpi_rank_map+1)),&
               & ila_mpi_mx(mpi_rank_map+1)-ila_mpi_mn(mpi_rank_map+1)+1,MPI_DOUBLE,&
               & mpi_root_map,0,mpi_comm_map,il_err)


         END IF

         deallocate(ila_num_links_mpi)

      end if

      deallocate (coslat, coslon, sinlat, sinlon)
      deallocate(wgtstmp)
      deallocate(ila_mpi_mn)
      deallocate(ila_mpi_mx)
      deallocate(ila_thr_mn)
      deallocate(ila_thr_mx)
      if (il_nbthreads .gt. 1) then
         do ib_thread = 1, il_nbthreads
            deallocate(sga_remap(ib_thread)%grid1_add)
            deallocate(sga_remap(ib_thread)%grid2_add)
            deallocate(sga_remap(ib_thread)%wts)
         end do
         deallocate(sga_remap)
      end if
      !
      if (nlogprt .ge. 2) then
         write (UNIT = nulou,FMT = *)' '
         write (UNIT = nulou,FMT = *)'Leaving routine remap_locc'
         call OASIS_FLUSH_SCRIP(nulou)
      endif
      !
      !-----------------------------------------------------------------------

   end subroutine remap_locc_wgt

   !***********************************************************************

   subroutine grid_search_nbr(nbr_add, nbr_dist,               &
                              coslat_dst, coslon_dst, sinlat_dst, sinlon_dst,         &
                              src_bin_add, num_neighbors )

      !-----------------------------------------------------------------------
      !
      !     this routine finds the closest num_neighbor points to a search 
      !     point and computes a distance to each of the neighbors.
      !     it excludes redundant points as specified by the tolerance
      !     defined by dist_chk.
      !
      !-----------------------------------------------------------------------

      !-----------------------------------------------------------------------
      !
      !     input variables
      !
      !-----------------------------------------------------------------------

      integer (kind=int_kind), dimension(:,:), intent(in) :: src_bin_add ! search bins for restricting search

      real (kind=dbl_kind), intent(in) :: coslat_dst,  & ! cos(lat)  of the search point
                                          coslon_dst,  & ! cos(lon)  of the search point
                                          sinlat_dst,  & ! sin(lat)  of the search point
                                          sinlon_dst     ! sin(lon)  of the search point

      integer (kind=int_kind) ::  num_neighbors     ! number of neighbours

      logical :: ll_debug


      !-----------------------------------------------------------------------
      !
      !     output variables
      !
      !-----------------------------------------------------------------------

      integer (kind=int_kind), dimension(num_neighbors), intent(out) :: nbr_add  ! address of each of the closest points

      real (kind=dbl_kind), dimension(num_neighbors), intent(out) :: nbr_dist    ! distance to each of the closest points

      !-----------------------------------------------------------------------
      !
      !     local variables
      !
      !-----------------------------------------------------------------------

      integer (kind=int_kind) :: n, nmax, nadd, nchk, & ! dummy indices
                                 nm1, np1, i, j, ip1, im1, jp1, jm1, &
                                 min_add, max_add,                   &
                                 nbr_count

      real (kind=dbl_kind) :: distance, rl_dist,             &   ! angular distance
                              dist1, dist2                       ! temporary dist calcs

      real (kind=dbl_kind), dimension(num_neighbors) :: &
           nbr_coslat, nbr_sinlat, nbr_coslon, nbr_sinlon        ! stored nbr lon/lat

      real (kind=dbl_kind), parameter :: dist_chk = 1.0e-7       ! delta distance limit radians

      logical (kind=log_kind) :: nchkflag                        ! flag for nchk
 
      !-----------------------------------------------------------------------
      !
      !     loop over source grid and find nearest neighbors
      !
      !-----------------------------------------------------------------------

      !***
      !*** bin restriction disabled
      !***

      min_add = MINVAL(src_bin_add(:,:)) 
      max_add = MAXVAL(src_bin_add(:,:)) 

      !***
      !*** initialize distance and address arrays
      !***

      nbr_count = 0
      nbr_add = 0
      nbr_dist = bignum
      nbr_coslat = bignum
      nbr_sinlat = bignum
      nbr_coslon = bignum
      nbr_sinlon = bignum

      do nadd=min_add,max_add

         if ( .not. grid2_mask(nadd) ) cycle

         !***
         !*** find distance to this point
         !***
         rl_dist = sinlat_dst*sinlat(nadd) +  &
                   coslat_dst*coslat(nadd)*   &
                   (coslon_dst*coslon(nadd) + &
                    sinlon_dst*sinlon(nadd))

         if (rl_dist < -1.0d0) then
            rl_dist = -1.0d0
         else if (rl_dist > 1.0d0) then
            rl_dist = 1.0d0
         end if

         distance = acos(rl_dist)

         !*** store the address and distance if this is one of the
         !*** smallest four so far
         !***

         if (distance .lt. nbr_dist(num_neighbors)) then
            ! compute nchk, the first neighbor with ge distance than nadd
            nchk = num_neighbors
            nchkflag = .true.
            do while (nchkflag)
               if (distance .lt. nbr_dist(nchk-1)) then
                   nchk = nchk - 1
               else
                   nchkflag = .false.
               endif
               if (nchk == 1) nchkflag = .false.
            enddo

            ! check that points are not the same, need to compare nchk-1 and nchk
            ! only compare against neighbors that have been initialized (nchk <= nbr_count)
            ! nchk-1 should always be an initialized point if nchk > 1
            ! nchk may be initialized or not
            if (nchk > 1) then
               dist1 = nbr_sinlat(nchk-1)*sinlat(nadd) +  &
                       nbr_coslat(nchk-1)*coslat(nadd)*   &
                      (nbr_coslon(nchk-1)*coslon(nadd) + &
                       nbr_sinlon(nchk-1)*sinlon(nadd))
               dist1 = MAX ( MIN ( dist1, 1.d0), -1.d0)
               !dist1 = acos(dist1)
               ! avoid cost of acos above since we're comparing to a small number
               ! use cos(x) = 1-x^2/2, x = sqrt(2 * (1 - cos(x)))
               dist1 = sqrt(2.0d0*(1.0d0-abs(dist1)))
            else
               dist1 = bignum
            endif

            if (dist1 > dist_chk) then
               if (nchk <= nbr_count) then
                  dist2 = nbr_sinlat(nchk)*sinlat(nadd) +  &
                          nbr_coslat(nchk)*coslat(nadd)*   &
                         (nbr_coslon(nchk)*coslon(nadd) + &
                          nbr_sinlon(nchk)*sinlon(nadd))
                  dist2 = MAX ( MIN ( dist2, 1.d0), -1.d0)
                  !dist2 = acos(dist2)
                  ! avoid cost of acos above since we're comparing to a small number
                  ! use cos(x) = 1-x^2/2, x = sqrt(2 * (1 - cos(x)))
                  dist2 = sqrt(2.0d0*(1.0d0-abs(dist2)))
               else
                  dist2 = bignum
               endif

               if (dist2 > dist_chk) then
                  nbr_count = min(nbr_count + 1, num_neighbors)
                  do n=num_neighbors,nchk+1,-1
                     nbr_add(n) = nbr_add(n-1)
                     nbr_dist(n) = nbr_dist(n-1)
                     nbr_coslat(n) = nbr_coslat(n-1)
                     nbr_sinlat(n) = nbr_sinlat(n-1)
                     nbr_coslon(n) = nbr_coslon(n-1)
                     nbr_sinlon(n) = nbr_sinlon(n-1)
                  end do
                  nbr_add(nchk) = nadd
                  nbr_dist(nchk) = distance
                  nbr_coslat(nchk) = coslat(nadd)
                  nbr_sinlat(nchk) = sinlat(nadd)
                  nbr_coslon(nchk) = coslon(nadd)
                  nbr_sinlon(nchk) = sinlon(nadd)
               else  ! dist2
!                  if (nlogprt .ge. 2) then
!                     write(nulou,*) 'remap_locc nbr_search skip point2: ',dist2
!                     write(nulou,*) '  ',nadd,nbr_add(nchk)
!                     write(nulou,*) '  ',nbr_coslat(nchk),coslat(nadd)
!                     write(nulou,*) '  ',nbr_sinlat(nchk),sinlat(nadd)
!                     write(nulou,*) '  ',nbr_coslon(nchk),coslon(nadd)
!                     write(nulou,*) '  ',nbr_sinlon(nchk),sinlon(nadd)
!                  endif
               endif  ! dist2
            else  ! dist1
!               if (nlogprt .ge. 2) then
!                  write(nulou,*) 'remap_locc nbr_search skip point1: ',dist1
!                  write(nulou,*) '  ',nadd,nbr_add(nchk-1)
!                  write(nulou,*) '  ',nbr_coslat(nchk-1),coslat(nadd)
!                  write(nulou,*) '  ',nbr_sinlat(nchk-1),sinlat(nadd)
!                  write(nulou,*) '  ',nbr_coslon(nchk-1),coslon(nadd)
!                  write(nulou,*) '  ',nbr_sinlon(nchk-1),sinlon(nadd)
!               endif
            endif  ! dist1
         endif  ! distance

      end do

1009  format (1X, 'nadd0 =', 1X, I6, 2X, 'distance0 =', 1X, F18.16)
1010  format (1X, 'nadd1 =', 1X, I6, 2X, 'distance0 =', 1X, F18.16)
1011  format (1X, 'nadd2 =', 1X, I6, 2X, 'distance2 =', 1X, F18.16)

      !-----------------------------------------------------------------------

   end subroutine grid_search_nbr

   !***********************************************************************

   subroutine store_inv_link_nbr(add1, add2, weights, id_thread)

      !-----------------------------------------------------------------------
      !
      !     this routine stores the address and weight for this link in
      !     the appropriate address and weight arrays and resizes those
      !     arrays if necessary.
      !
      !-----------------------------------------------------------------------

      !-----------------------------------------------------------------------
      !
      !     input variables
      !
      !-----------------------------------------------------------------------

      integer (kind=int_kind), intent(in) :: add1,  &   ! address on grid1
                                             add2,  &   ! address on grid2
                                             id_thread  ! local threaded task

      real (kind=dbl_kind), dimension(:), intent(in) :: weights ! array of remapping weights for this link

      !-----------------------------------------------------------------------
      !
      !     increment number of links and check to see if remap arrays need
      !     to be increased to accomodate the new link.  then store the
      !     link.
      !
      !-----------------------------------------------------------------------

      if (il_nbthreads .eq. 1) then

         num_links_map1  = num_links_map1 + 1

         if (num_links_map1 > max_links_map1)  &
            call resize_remap_vars(1,resize_increment)

         ! for locally conservative inteprolation, switch here source and target grid
         grid1_add_map1(num_links_map1) = add2
         grid2_add_map1(num_links_map1) = add1
         wts_map1    (:,num_links_map1) = weights

      else

         sga_remap(id_thread)%num_links = sga_remap(id_thread)%num_links + 1

         if (sga_remap(id_thread)%num_links > sga_remap(id_thread)%max_links) &
            call sga_remap(id_thread)%resize(int(0.2*real(sga_remap(id_thread)%max_links)))

         ! for locally conservative inteprolation, switch here source and target grid
         sga_remap(id_thread)%grid1_add(sga_remap(id_thread)%num_links) = add2
         sga_remap(id_thread)%grid2_add(sga_remap(id_thread)%num_links) = add1
         sga_remap(id_thread)%wts(:,sga_remap(id_thread)%num_links)     = weights

      endif

      !-----------------------------------------------------------------------

   end subroutine store_inv_link_nbr

   !***********************************************************************

end module remap_locc_weight

!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



