#include "xios_fortran_prefix.hpp"

MODULE IDATA
   USE, INTRINSIC :: ISO_C_BINDING
   USE ICONTEXT
   USE IFIELD

   INTERFACE ! Ne pas appeler directement/Interface FORTRAN 2003 <-> C99

      SUBROUTINE  cxios_init_server() BIND(C)
      END SUBROUTINE cxios_init_server

     SUBROUTINE cxios_init_client(client_id, len_client_id, f_local_comm, f_return_comm) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: client_id
         INTEGER  (kind = C_INT)     , VALUE        :: len_client_id
         INTEGER  (kind = C_INT)                    :: f_local_comm
         INTEGER  (kind = C_INT)                    :: f_return_comm
      END SUBROUTINE cxios_init_client

      SUBROUTINE  cxios_context_initialize(context_id,len_context_id,f_comm) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: context_id
         INTEGER  (kind = C_INT)     , VALUE        :: len_context_id
         INTEGER  (kind = C_INT)                    :: f_comm
      END SUBROUTINE cxios_context_initialize

      SUBROUTINE cxios_context_is_initialized(context_id,len_context_id,initialized) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: context_id
         INTEGER  (kind = C_INT)     , VALUE        :: len_context_id
         LOGICAL  (kind = C_BOOL)                   :: initialized
      END SUBROUTINE cxios_context_is_initialized


       SUBROUTINE  cxios_context_close_definition() BIND(C)
         USE ISO_C_BINDING
      END SUBROUTINE cxios_context_close_definition


       SUBROUTINE  cxios_context_finalize() BIND(C)
         USE ISO_C_BINDING
      END SUBROUTINE cxios_context_finalize

      SUBROUTINE  cxios_oasis_enddef() BIND(C)
         USE ISO_C_BINDING
      END SUBROUTINE cxios_oasis_enddef
      
      SUBROUTINE  cxios_finalize() BIND(C)
      END SUBROUTINE cxios_finalize

      SUBROUTINE  cxios_solve_inheritance() BIND(C)
      END SUBROUTINE cxios_solve_inheritance

      SUBROUTINE cxios_write_data_k80_hdl(field_hdl, data_k8, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE)               :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_write_data_k80_hdl

      SUBROUTINE cxios_write_data_k80(fieldid, fieldid_size, data_k8, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE)               :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_write_data_k80

      SUBROUTINE cxios_write_data_k81_hdl(field_hdl, data_k8, data_Xsize, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k81_hdl

      SUBROUTINE cxios_write_data_k81(fieldid, fieldid_size, data_k8, data_Xsize, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k81

      SUBROUTINE cxios_write_data_k82_hdl(field_hdl, data_k8, data_Xsize, data_Ysize, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k82_hdl

      SUBROUTINE cxios_write_data_k82(fieldid, fieldid_size, data_k8, data_Xsize, data_Ysize, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k82

      SUBROUTINE cxios_write_data_k83_hdl(field_hdl, data_k8, data_Xsize, data_Ysize, data_Zsize, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k83_hdl

      SUBROUTINE cxios_write_data_k83(fieldid, fieldid_size, data_k8, data_Xsize, data_Ysize, data_Zsize, &
                                      tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k83

      SUBROUTINE cxios_write_data_k84_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k84_hdl

      SUBROUTINE cxios_write_data_k84(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k84

      SUBROUTINE cxios_write_data_k85_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k85_hdl

      SUBROUTINE cxios_write_data_k85(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k85

      SUBROUTINE cxios_write_data_k86_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k86_hdl

      SUBROUTINE cxios_write_data_k86(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k86

      SUBROUTINE cxios_write_data_k87_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k87_hdl

      SUBROUTINE cxios_write_data_k87(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k87

      SUBROUTINE cxios_write_data_k40_hdl(field_hdl, data_k4, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT)                :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_write_data_k40_hdl

      SUBROUTINE cxios_write_data_k40(fieldid, fieldid_size, data_k4, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT)                :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_write_data_k40

      SUBROUTINE cxios_write_data_k41_hdl(field_hdl, data_k4, data_Xsize, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k41_hdl

      SUBROUTINE cxios_write_data_k41(fieldid, fieldid_size, data_k4, data_Xsize, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k41

      SUBROUTINE cxios_write_data_k42_hdl(field_hdl, data_k4, data_Xsize, data_Ysize, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k42_hdl
 
      SUBROUTINE cxios_write_data_k42(fieldid, fieldid_size, data_k4, data_Xsize, data_Ysize, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k42

      SUBROUTINE cxios_write_data_k43_hdl(field_hdl, data_k4, data_Xsize, data_Ysize, data_Zsize, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k43_hdl

      SUBROUTINE cxios_write_data_k43(fieldid, fieldid_size, data_k4, data_Xsize, data_Ysize, data_Zsize, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k43

      SUBROUTINE cxios_write_data_k44_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k44_hdl

      SUBROUTINE cxios_write_data_k44(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k44

      SUBROUTINE cxios_write_data_k45_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k45_hdl

      SUBROUTINE cxios_write_data_k45(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k45

      SUBROUTINE cxios_write_data_k46_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k46_hdl
 
      SUBROUTINE cxios_write_data_k46(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k46

      SUBROUTINE cxios_write_data_k47_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size, tileid) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k47_hdl

      SUBROUTINE cxios_write_data_k47(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size, tileid) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
         INTEGER  (kind = C_INT)   , VALUE        :: tileid
      END SUBROUTINE cxios_write_data_k47


      ! Read data
      SUBROUTINE cxios_read_data_k80_hdl(field_hdl, data_k8, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE)               :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k80_hdl

      SUBROUTINE cxios_read_data_k80(fieldid, fieldid_size, data_k8, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE)               :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k80

      SUBROUTINE cxios_read_data_k81_hdl(field_hdl, data_k8, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k81_hdl

      SUBROUTINE cxios_read_data_k81(fieldid, fieldid_size, data_k8, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k81

      SUBROUTINE cxios_read_data_k82_hdl(field_hdl, data_k8, data_Xsize, data_Ysize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
      END SUBROUTINE cxios_read_data_k82_hdl

      SUBROUTINE cxios_read_data_k82(fieldid, fieldid_size, data_k8, data_Xsize, data_Ysize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
      END SUBROUTINE cxios_read_data_k82

      SUBROUTINE cxios_read_data_k83_hdl(field_hdl, data_k8, data_Xsize, data_Ysize, data_Zsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
      END SUBROUTINE cxios_read_data_k83_hdl

       SUBROUTINE cxios_read_data_k83(fieldid, fieldid_size, data_k8, data_Xsize, data_Ysize, data_Zsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
      END SUBROUTINE cxios_read_data_k83

     SUBROUTINE cxios_read_data_k84_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
      END SUBROUTINE cxios_read_data_k84_hdl

     SUBROUTINE cxios_read_data_k84(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
      END SUBROUTINE cxios_read_data_k84

      SUBROUTINE cxios_read_data_k85_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
      END SUBROUTINE cxios_read_data_k85_hdl

      SUBROUTINE cxios_read_data_k85(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
      END SUBROUTINE cxios_read_data_k85

      SUBROUTINE cxios_read_data_k86_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
      END SUBROUTINE cxios_read_data_k86_hdl
 
      SUBROUTINE cxios_read_data_k86(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
      END SUBROUTINE cxios_read_data_k86

      SUBROUTINE cxios_read_data_k87_hdl(field_hdl, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
      END SUBROUTINE cxios_read_data_k87_hdl

      SUBROUTINE cxios_read_data_k87(fieldid, fieldid_size, data_k8, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_DOUBLE), DIMENSION(*) :: data_k8
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
      END SUBROUTINE cxios_read_data_k87

      SUBROUTINE cxios_read_data_k40_hdl(field_hdl, data_k4, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT)                :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k40_hdl

      SUBROUTINE cxios_read_data_k40(fieldid, fieldid_size, data_k4, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT)                :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k40

      SUBROUTINE cxios_read_data_k41_hdl(field_hdl, data_k4, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k41_hdl

      SUBROUTINE cxios_read_data_k41(fieldid, fieldid_size, data_k4, data_Xsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize
      END SUBROUTINE cxios_read_data_k41

      SUBROUTINE cxios_read_data_k42_hdl(field_hdl, data_k4, data_Xsize, data_Ysize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
      END SUBROUTINE cxios_read_data_k42_hdl

      SUBROUTINE cxios_read_data_k42(fieldid, fieldid_size, data_k4, data_Xsize, data_Ysize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize
      END SUBROUTINE cxios_read_data_k42

      SUBROUTINE cxios_read_data_k43_hdl(field_hdl, data_k4, data_Xsize, data_Ysize, data_Zsize) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
      END SUBROUTINE cxios_read_data_k43_hdl

      SUBROUTINE cxios_read_data_k43(fieldid, fieldid_size, data_k4, data_Xsize, data_Ysize, data_Zsize) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_Xsize, data_Ysize, data_Zsize
      END SUBROUTINE cxios_read_data_k43

      SUBROUTINE cxios_read_data_k44_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
      END SUBROUTINE cxios_read_data_k44_hdl
 
      SUBROUTINE cxios_read_data_k44(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size
      END SUBROUTINE cxios_read_data_k44

      SUBROUTINE cxios_read_data_k45_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
      END SUBROUTINE cxios_read_data_k45_hdl

      SUBROUTINE cxios_read_data_k45(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size
      END SUBROUTINE cxios_read_data_k45

      SUBROUTINE cxios_read_data_k46_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
      END SUBROUTINE cxios_read_data_k46_hdl
 
      SUBROUTINE cxios_read_data_k46(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
      END SUBROUTINE cxios_read_data_k46

      SUBROUTINE cxios_read_data_k47_hdl(field_hdl, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE      :: field_hdl
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
      END SUBROUTINE cxios_read_data_k47_hdl

      SUBROUTINE cxios_read_data_k47(fieldid, fieldid_size, data_k4, &
                                      data_0size, data_1size, data_2size, &
                                      data_3size, data_4size, data_5size, &
                                      data_6size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: fieldid
         REAL     (kind = C_FLOAT) , DIMENSION(*) :: data_k4
         INTEGER  (kind = C_INT)   , VALUE        :: fieldid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_0size, data_1size, data_2size
         INTEGER  (kind = C_INT)   , VALUE        :: data_3size, data_4size, data_5size
         INTEGER  (kind = C_INT)   , VALUE        :: data_6size
      END SUBROUTINE cxios_read_data_k47

      ! Binding C and Fortran interface of get_variable (icdata.cpp)
      SUBROUTINE cxios_get_variable_data_k8(vardid, varid_size, data_k8, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         REAL     (kind = C_DOUBLE)               :: data_k8
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_get_variable_data_k8

      SUBROUTINE cxios_get_variable_data_k4(vardid, varid_size, data_k4, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         REAL     (kind = C_FLOAT)                :: data_k4
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_get_variable_data_k4

      SUBROUTINE cxios_get_variable_data_int(vardid, varid_size, data_int, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         INTEGER  (kind = C_INT)                  :: data_int
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_get_variable_data_int

      SUBROUTINE cxios_get_variable_data_logic(vardid, varid_size, data_logic, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         LOGICAL  (kind = C_BOOL)                 :: data_logic
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_get_variable_data_logic

      SUBROUTINE cxios_get_variable_data_char(vardid, varid_size, data_char, data_size_in, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_size_in
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: data_char
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_get_variable_data_char

      ! Binding C and Fortran interface of set_variable (icdata.cpp)
      SUBROUTINE cxios_set_variable_data_k8(vardid, varid_size, data_k8, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         REAL     (kind = C_DOUBLE), VALUE        :: data_k8
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_set_variable_data_k8

      SUBROUTINE cxios_set_variable_data_k4(vardid, varid_size, data_k4, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         REAL     (kind = C_FLOAT) , VALUE        :: data_k4
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_set_variable_data_k4

      SUBROUTINE cxios_set_variable_data_int(vardid, varid_size, data_int, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_int
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_set_variable_data_int

      SUBROUTINE cxios_set_variable_data_logic(vardid, varid_size, data_logic, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         LOGICAL  (kind = C_BOOL)       , VALUE   :: data_logic
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_set_variable_data_logic

      SUBROUTINE cxios_set_variable_data_char(vardid, varid_size, data_char, data_size_in, is_var_existed) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: vardid
         INTEGER  (kind = C_INT)   , VALUE        :: varid_size
         INTEGER  (kind = C_INT)   , VALUE        :: data_size_in
         CHARACTER(kind = C_CHAR)  , DIMENSION(*) :: data_char
         LOGICAL  (kind = C_BOOL)                 :: is_var_existed
      END SUBROUTINE cxios_set_variable_data_char

   END INTERFACE


   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE  xios(init_server)()
   IMPLICIT NONE
     CALL cxios_init_server()
   END SUBROUTINE xios(init_server)

   SUBROUTINE  xios(initialize)(client_id, local_comm, return_comm)
   IMPLICIT NONE
   INCLUDE 'mpif.h'
   CHARACTER(LEN=*),INTENT(IN) :: client_id
   INTEGER,INTENT(IN),OPTIONAL         :: local_comm
   INTEGER,INTENT(OUT),OPTIONAL        :: return_comm
   INTEGER :: f_local_comm
   INTEGER :: f_return_comm

      IF (PRESENT(local_comm)) THEN
        f_local_comm=local_comm
      ELSE
        f_local_comm = MPI_COMM_NULL
      ENDIF

      CALL cxios_init_client(client_id,LEN(client_id),f_local_comm,f_return_comm)

      IF (PRESENT(return_comm)) return_comm=f_return_comm

   END SUBROUTINE  xios(initialize)


   SUBROUTINE  xios(context_initialize)(context_id,comm)
   IMPLICIT NONE
   CHARACTER(LEN=*),INTENT(IN)  :: context_id
   INTEGER, INTENT(IN)          :: comm

      CALL cxios_context_initialize(context_id,LEN(context_id),comm)

    END SUBROUTINE  xios(context_initialize)


   LOGICAL FUNCTION  xios(context_is_initialized)(context_id)
   USE ISO_C_BINDING
   IMPLICIT NONE
   CHARACTER(LEN=*),INTENT(IN)  :: context_id
   LOGICAL(KIND=C_BOOL) :: is_init

      CALL cxios_context_is_initialized(context_id, LEN(context_id), is_init)
      xios(context_is_initialized) = is_init

    END FUNCTION xios(context_is_initialized)


   SUBROUTINE  xios(finalize)
   IMPLICIT NONE

      CALL cxios_finalize

    END SUBROUTINE  xios(finalize)

   SUBROUTINE  xios(oasis_enddef)
   IMPLICIT NONE

      CALL cxios_oasis_enddef

    END SUBROUTINE  xios(oasis_enddef)

   SUBROUTINE xios(close_context_definition)()
   IMPLICIT NONE
      CALL cxios_context_close_definition()
   END SUBROUTINE xios(close_context_definition)


   SUBROUTINE xios(context_finalize)()
   IMPLICIT NONE
      CALL cxios_context_finalize()
   END SUBROUTINE xios(context_finalize)

   SUBROUTINE xios(solve_inheritance)()
   IMPLICIT NONE
      CALL cxios_solve_inheritance()
   END SUBROUTINE xios(solve_inheritance)

   ! Send field functions
   SUBROUTINE xios(send_field_r8_0d_hdl)(field_hdl, data_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), INTENT(IN) :: data_k8
      CALL cxios_write_data_k80_hdl(field_hdl%daddr, data_k8, 1)
   END SUBROUTINE xios(send_field_r8_0d_hdl)

   SUBROUTINE xios(send_field_r8_0d)(fieldid, data_k8)
   IMPLICIT NONE
      CHARACTER(len = *) , INTENT(IN) :: fieldid
      REAL     (kind = 8), INTENT(IN) :: data_k8
      CALL cxios_write_data_k80(fieldid, len(fieldid), data_k8, 1)
   END SUBROUTINE xios(send_field_r8_0d)

   SUBROUTINE xios(send_field_r8_1d_hdl)(field_hdl, data1d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data1d_k8(:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k81_hdl(field_hdl%daddr, data1d_k8, size(data1d_k8, 1), tileid)
   END SUBROUTINE xios(send_field_r8_1d_hdl)

   SUBROUTINE xios(send_field_r8_1d)(fieldid, data1d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data1d_k8(:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k81(fieldid, len(fieldid), data1d_k8, size(data1d_k8, 1), tileid)
   END SUBROUTINE xios(send_field_r8_1d)

   SUBROUTINE xios(send_field_tiled_r8_1d)(fieldid, data1d_k8, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data1d_k8(:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k81(fieldid, len(fieldid), data1d_k8, size(data1d_k8, 1), tileid)
   END SUBROUTINE xios(send_field_tiled_r8_1d)

   SUBROUTINE  xios(send_field_r8_2d_hdl)(field_hdl, data2d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data2d_k8(:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k82_hdl(field_hdl%daddr, data2d_k8, size(data2d_k8, 1), size(data2d_k8, 2), tileid)
   END SUBROUTINE  xios(send_field_r8_2d_hdl)

   SUBROUTINE  xios(send_field_r8_2d)(fieldid, data2d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data2d_k8(:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k82(fieldid, len(fieldid), data2d_k8, size(data2d_k8, 1), &
                                size(data2d_k8, 2), tileid)
   END SUBROUTINE  xios(send_field_r8_2d)

   SUBROUTINE  xios(send_field_tiled_r8_2d)(fieldid, data2d_k8, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data2d_k8(:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k82(fieldid, len(fieldid), data2d_k8, size(data2d_k8, 1), &
                                size(data2d_k8, 2), tileid)
   END SUBROUTINE  xios(send_field_tiled_r8_2d)

   SUBROUTINE  xios(send_field_r8_3d_hdl)(field_hdl, data3d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data3d_k8(:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k83_hdl(field_hdl%daddr, data3d_k8, size(data3d_k8, 1), size(data3d_k8, 2), size(data3d_k8, 3), &
                                    tileid)
   END SUBROUTINE  xios(send_field_r8_3d_hdl)

   SUBROUTINE  xios(send_field_r8_3d)(fieldid, data3d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data3d_k8(:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k83(fieldid, len(fieldid), data3d_k8, size(data3d_k8, 1), size(data3d_k8, 2), size(data3d_k8, 3), &
                                tileid)
   END SUBROUTINE  xios(send_field_r8_3d)

   SUBROUTINE  xios(send_field_tiled_r8_3d)(fieldid, data3d_k8, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data3d_k8(:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k83(fieldid, len(fieldid), data3d_k8, size(data3d_k8, 1), &
                                      size(data3d_k8, 2), size(data3d_k8, 3), tileid)
   END SUBROUTINE  xios(send_field_tiled_r8_3d)

   SUBROUTINE  xios(send_field_r8_4d_hdl)(field_hdl, data4d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data4d_k8(:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k84_hdl(field_hdl%daddr, data4d_k8, &
                                size(data4d_k8, 1), size(data4d_k8, 2), size(data4d_k8, 3), &
                                size(data4d_k8, 4), tileid)
   END SUBROUTINE  xios(send_field_r8_4d_hdl)

   SUBROUTINE  xios(send_field_r8_4d)(fieldid, data4d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data4d_k8(:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k84(fieldid, len(fieldid), data4d_k8, &
                                size(data4d_k8, 1), size(data4d_k8, 2), size(data4d_k8, 3), &
                                size(data4d_k8, 4), tileid)
   END SUBROUTINE  xios(send_field_r8_4d)

   SUBROUTINE  xios(send_field_tiled_r8_4d)(fieldid, data4d_k8, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data4d_k8(:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k84(fieldid, len(fieldid), data4d_k8, &
                                size(data4d_k8, 1), size(data4d_k8, 2), size(data4d_k8, 3), &
                                size(data4d_k8, 4), tileid)
   END SUBROUTINE  xios(send_field_tiled_r8_4d)

   SUBROUTINE  xios(send_field_r8_5d_hdl)(field_hdl, data5d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data5d_k8(:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k85_hdl(field_hdl%daddr, data5d_k8, &
                                size(data5d_k8, 1), size(data5d_k8, 2), size(data5d_k8, 3), &
                                size(data5d_k8, 4), size(data5d_k8, 5), tileid)
   END SUBROUTINE  xios(send_field_r8_5d_hdl)

   SUBROUTINE  xios(send_field_r8_5d)(fieldid, data5d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data5d_k8(:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k85(fieldid, len(fieldid), data5d_k8, &
                                size(data5d_k8, 1), size(data5d_k8, 2), size(data5d_k8, 3), &
                                size(data5d_k8, 4), size(data5d_k8, 5), tileid)
   END SUBROUTINE  xios(send_field_r8_5d)

   SUBROUTINE  xios(send_field_tiled_r8_5d)(fieldid, data5d_k8, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data5d_k8(:,:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k85(fieldid, len(fieldid), data5d_k8, &
                                size(data5d_k8, 1), size(data5d_k8, 2), size(data5d_k8, 3), &
                                size(data5d_k8, 4), size(data5d_k8, 5), tileid)
   END SUBROUTINE  xios(send_field_tiled_r8_5d)

   SUBROUTINE  xios(send_field_r8_6d_hdl)(field_hdl, data6d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data6d_k8(:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k86_hdl(field_hdl%daddr, data6d_k8, &
                                size(data6d_k8, 1), size(data6d_k8, 2), size(data6d_k8, 3), &
                                size(data6d_k8, 4), size(data6d_k8, 5), size(data6d_k8, 6), tileid)
   END SUBROUTINE  xios(send_field_r8_6d_hdl)

   SUBROUTINE  xios(send_field_r8_6d)(fieldid, data6d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data6d_k8(:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k86(fieldid, len(fieldid), data6d_k8, &
                                size(data6d_k8, 1), size(data6d_k8, 2), size(data6d_k8, 3), &
                                size(data6d_k8, 4), size(data6d_k8, 5), size(data6d_k8, 6), tileid)
   END SUBROUTINE  xios(send_field_r8_6d)

   SUBROUTINE  xios(send_field_tiled_r8_6d)(fieldid, data6d_k8, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data6d_k8(:,:,:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k86(fieldid, len(fieldid), data6d_k8, &
                                size(data6d_k8, 1), size(data6d_k8, 2), size(data6d_k8, 3), &
                                size(data6d_k8, 4), size(data6d_k8, 5), size(data6d_k8, 6), tileid)
   END SUBROUTINE  xios(send_field_tiled_r8_6d)

   SUBROUTINE  xios(send_field_r8_7d_hdl)(field_hdl, data7d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data7d_k8(:,:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k87_hdl(field_hdl%daddr, data7d_k8, &
                                size(data7d_k8, 1), size(data7d_k8, 2), size(data7d_k8, 3), &
                                size(data7d_k8, 4), size(data7d_k8, 5), size(data7d_k8, 6), &
                                size(data7d_k8, 7), tileid)
   END SUBROUTINE  xios(send_field_r8_7d_hdl)

   SUBROUTINE  xios(send_field_r8_7d)(fieldid, data7d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data7d_k8(:,:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k87(fieldid, len(fieldid), data7d_k8, &
                                size(data7d_k8, 1), size(data7d_k8, 2), size(data7d_k8, 3), &
                                size(data7d_k8, 4), size(data7d_k8, 5), size(data7d_k8, 6), &
                                size(data7d_k8, 7), tileid)
   END SUBROUTINE  xios(send_field_r8_7d)

   SUBROUTINE  xios(send_field_tiled_r8_7d)(fieldid, data7d_k8, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(IN) :: data7d_k8(:,:,:,:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k87(fieldid, len(fieldid), data7d_k8, &
                                size(data7d_k8, 1), size(data7d_k8, 2), size(data7d_k8, 3), &
                                size(data7d_k8, 4), size(data7d_k8, 5), size(data7d_k8, 6), &
                                size(data7d_k8, 7), tileid)
   END SUBROUTINE  xios(send_field_tiled_r8_7d)

   SUBROUTINE xios(send_field_r4_0d_hdl)(field_hdl, data_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), INTENT(IN) :: data_k4
      CALL cxios_write_data_k40_hdl(field_hdl%daddr, data_k4, 1)
   END SUBROUTINE xios(send_field_r4_0d_hdl)

   SUBROUTINE xios(send_field_r4_0d)(fieldid, data_k4)
   IMPLICIT NONE
      CHARACTER(len = *) , INTENT(IN) :: fieldid
      REAL     (kind = 4), INTENT(IN) :: data_k4
      CALL cxios_write_data_k40(fieldid, len(fieldid), data_k4, 1)
   END SUBROUTINE xios(send_field_r4_0d)

   SUBROUTINE xios(send_field_r4_1d_hdl)(field_hdl, data1d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data1d_k4(:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k41_hdl(field_hdl%daddr, data1d_k4, size(data1d_k4, 1), tileid)
   END SUBROUTINE xios(send_field_r4_1d_hdl)

   SUBROUTINE xios(send_field_r4_1d)(fieldid, data1d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data1d_k4(:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k41(fieldid, len(fieldid), data1d_k4, size(data1d_k4, 1), tileid)
   END SUBROUTINE xios(send_field_r4_1d)

   SUBROUTINE xios(send_field_tiled_r4_1d)(fieldid, data1d_k4, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data1d_k4(:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k41(fieldid, len(fieldid), data1d_k4, size(data1d_k4, 1), tileid)
   END SUBROUTINE xios(send_field_tiled_r4_1d)

   SUBROUTINE xios(send_field_r4_2d_hdl)(field_hdl, data2d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data2d_k4(:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k42_hdl(field_hdl%daddr, data2d_k4, size(data2d_k4, 1), size(data2d_k4, 2), tileid)
   END SUBROUTINE xios(send_field_r4_2d_hdl)

   SUBROUTINE xios(send_field_r4_2d)(fieldid, data2d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data2d_k4(:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k42(fieldid, len(fieldid), data2d_k4, size(data2d_k4, 1), size(data2d_k4, 2), tileid)
   END SUBROUTINE xios(send_field_r4_2d)

   SUBROUTINE xios(send_field_tiled_r4_2d)(fieldid, data2d_k4, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data2d_k4(:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k42(fieldid, len(fieldid), data2d_k4, size(data2d_k4, 1), size(data2d_k4, 2), tileid)
   END SUBROUTINE xios(send_field_tiled_r4_2d)

   SUBROUTINE xios(send_field_r4_3d_hdl)(field_hdl, data3d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data3d_k4(:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k43_hdl(field_hdl%daddr, data3d_k4, size(data3d_k4, 1), size(data3d_k4, 2), size(data3d_k4, 3), &
                                    tileid)
   END SUBROUTINE xios(send_field_r4_3d_hdl)

   SUBROUTINE xios(send_field_r4_3d)(fieldid, data3d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data3d_k4(:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k43(fieldid, len(fieldid), data3d_k4, size(data3d_k4, 1), size(data3d_k4, 2), size(data3d_k4, 3), &
                                tileid)
   END SUBROUTINE xios(send_field_r4_3d)

   SUBROUTINE xios(send_field_tiled_r4_3d)(fieldid, data3d_k4, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data3d_k4(:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k43(fieldid, len(fieldid), data3d_k4, size(data3d_k4, 1), size(data3d_k4, 2), size(data3d_k4, 3), &
                                tileid)
   END SUBROUTINE xios(send_field_tiled_r4_3d)

   SUBROUTINE  xios(send_field_r4_4d_hdl)(field_hdl, data4d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data4d_k4(:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k44_hdl(field_hdl%daddr, data4d_k4, &
                                size(data4d_k4, 1), size(data4d_k4, 2), size(data4d_k4, 3), &
                                size(data4d_k4, 4), tileid)
   END SUBROUTINE  xios(send_field_r4_4d_hdl)

   SUBROUTINE  xios(send_field_r4_4d)(fieldid, data4d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data4d_k4(:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k44(fieldid, len(fieldid), data4d_k4, &
                                size(data4d_k4, 1), size(data4d_k4, 2), size(data4d_k4, 3), &
                                size(data4d_k4, 4), tileid)
   END SUBROUTINE  xios(send_field_r4_4d)

   SUBROUTINE  xios(send_field_tiled_r4_4d)(fieldid, data4d_k4, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data4d_k4(:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k44(fieldid, len(fieldid), data4d_k4, &
                                size(data4d_k4, 1), size(data4d_k4, 2), size(data4d_k4, 3), &
                                size(data4d_k4, 4), tileid)
   END SUBROUTINE  xios(send_field_tiled_r4_4d)

   SUBROUTINE  xios(send_field_r4_5d_hdl)(field_hdl, data5d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data5d_k4(:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k45_hdl(field_hdl%daddr, data5d_k4, &
                                size(data5d_k4, 1), size(data5d_k4, 2), size(data5d_k4, 3), &
                                size(data5d_k4, 4), size(data5d_k4, 5), tileid)
   END SUBROUTINE  xios(send_field_r4_5d_hdl)

   SUBROUTINE  xios(send_field_r4_5d)(fieldid, data5d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data5d_k4(:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k45(fieldid, len(fieldid), data5d_k4, &
                                size(data5d_k4, 1), size(data5d_k4, 2), size(data5d_k4, 3), &
                                size(data5d_k4, 4), size(data5d_k4, 5), tileid)
   END SUBROUTINE  xios(send_field_r4_5d)

   SUBROUTINE  xios(send_field_tiled_r4_5d)(fieldid, data5d_k4, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data5d_k4(:,:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k45(fieldid, len(fieldid), data5d_k4, &
                                size(data5d_k4, 1), size(data5d_k4, 2), size(data5d_k4, 3), &
                                size(data5d_k4, 4), size(data5d_k4, 5), tileid)
   END SUBROUTINE  xios(send_field_tiled_r4_5d)

   SUBROUTINE  xios(send_field_r4_6d_hdl)(field_hdl, data6d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data6d_k4(:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k46_hdl(field_hdl%daddr, data6d_k4, &
                                size(data6d_k4, 1), size(data6d_k4, 2), size(data6d_k4, 3), &
                                size(data6d_k4, 4), size(data6d_k4, 5), size(data6d_k4, 6), tileid)
   END SUBROUTINE  xios(send_field_r4_6d_hdl)
   
   SUBROUTINE  xios(send_field_r4_6d)(fieldid, data6d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data6d_k4(:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k46(fieldid, len(fieldid), data6d_k4, &
                                size(data6d_k4, 1), size(data6d_k4, 2), size(data6d_k4, 3), &
                                size(data6d_k4, 4), size(data6d_k4, 5), size(data6d_k4, 6), tileid)
   END SUBROUTINE  xios(send_field_r4_6d)

   SUBROUTINE  xios(send_field_tiled_r4_6d)(fieldid, data6d_k4, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data6d_k4(:,:,:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k46(fieldid, len(fieldid), data6d_k4, &
                                size(data6d_k4, 1), size(data6d_k4, 2), size(data6d_k4, 3), &
                                size(data6d_k4, 4), size(data6d_k4, 5), size(data6d_k4, 6), tileid)
   END SUBROUTINE  xios(send_field_tiled_r4_6d)

   SUBROUTINE  xios(send_field_r4_7d_hdl)(field_hdl, data7d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data7d_k4(:,:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k47_hdl(field_hdl%daddr, data7d_k4, &
                                size(data7d_k4, 1), size(data7d_k4, 2), size(data7d_k4, 3), &
                                size(data7d_k4, 4), size(data7d_k4, 5), size(data7d_k4, 6), &
                                size(data7d_k4, 7), tileid)
   END SUBROUTINE  xios(send_field_r4_7d_hdl)
   
   SUBROUTINE  xios(send_field_r4_7d)(fieldid, data7d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data7d_k4(:,:,:,:,:,:,:)
      INTEGER, PARAMETER                            :: tileid = -1
      CALL cxios_write_data_k47(fieldid, len(fieldid), data7d_k4, &
                                size(data7d_k4, 1), size(data7d_k4, 2), size(data7d_k4, 3), &
                                size(data7d_k4, 4), size(data7d_k4, 5), size(data7d_k4, 6), &
                                size(data7d_k4, 7), tileid)
   END SUBROUTINE  xios(send_field_r4_7d)

   SUBROUTINE  xios(send_field_tiled_r4_7d)(fieldid, data7d_k4, tileid)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(IN) :: data7d_k4(:,:,:,:,:,:,:)
      INTEGER                          , INTENT(IN) :: tileid
      CALL cxios_write_data_k47(fieldid, len(fieldid), data7d_k4, &
                                size(data7d_k4, 1), size(data7d_k4, 2), size(data7d_k4, 3), &
                                size(data7d_k4, 4), size(data7d_k4, 5), size(data7d_k4, 6), &
                                size(data7d_k4, 7), tileid)
   END SUBROUTINE  xios(send_field_tiled_r4_7d)

   ! Receive field functions
   SUBROUTINE xios(recv_field_r8_0d_hdl)(field_hdl, data0d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8)              , INTENT(OUT):: data0d_k8
      CALL cxios_read_data_k80_hdl(field_hdl%daddr, data0d_k8, 1)
   END SUBROUTINE xios(recv_field_r8_0d_hdl)

   SUBROUTINE xios(recv_field_r8_0d)(fieldid, data0d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8)              , INTENT(OUT):: data0d_k8
      CALL cxios_read_data_k80(fieldid, len(fieldid), data0d_k8, 1)
   END SUBROUTINE xios(recv_field_r8_0d)

   SUBROUTINE xios(recv_field_r8_1d_hdl)(field_hdl, data1d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data1d_k8(:)
      CALL cxios_read_data_k81_hdl(field_hdl%daddr, data1d_k8, size(data1d_k8, 1))
   END SUBROUTINE xios(recv_field_r8_1d_hdl)

   SUBROUTINE xios(recv_field_r8_1d)(fieldid, data1d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data1d_k8(:)
      CALL cxios_read_data_k81(fieldid, len(fieldid), data1d_k8, size(data1d_k8, 1))
   END SUBROUTINE xios(recv_field_r8_1d)

   SUBROUTINE  xios(recv_field_r8_2d_hdl)(field_hdl, data2d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data2d_k8(:,:)
      CALL cxios_read_data_k82_hdl(field_hdl%daddr, data2d_k8, size(data2d_k8, 1), size(data2d_k8, 2))
   END SUBROUTINE  xios(recv_field_r8_2d_hdl)

   SUBROUTINE  xios(recv_field_r8_2d)(fieldid, data2d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data2d_k8(:,:)
      CALL cxios_read_data_k82(fieldid, len(fieldid), data2d_k8, size(data2d_k8, 1), size(data2d_k8, 2))
   END SUBROUTINE  xios(recv_field_r8_2d)

   SUBROUTINE  xios(recv_field_r8_3d_hdl)(field_hdl, data3d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data3d_k8(:,:,:)
      CALL cxios_read_data_k83_hdl(field_hdl%daddr, data3d_k8, size(data3d_k8, 1), size(data3d_k8, 2), size(data3d_k8, 3))
   END SUBROUTINE  xios(recv_field_r8_3d_hdl)

   SUBROUTINE  xios(recv_field_r8_3d)(fieldid, data3d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data3d_k8(:,:,:)
      CALL cxios_read_data_k83(fieldid, len(fieldid), data3d_k8, size(data3d_k8, 1), size(data3d_k8, 2), size(data3d_k8, 3))
   END SUBROUTINE  xios(recv_field_r8_3d)

   SUBROUTINE  xios(recv_field_r8_4d_hdl)(field_hdl, data4d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data4d_k8(:,:,:,:)
      CALL cxios_read_data_k84_hdl(field_hdl%daddr, data4d_k8, &
                                size(data4d_k8, 1), size(data4d_k8, 2), size(data4d_k8, 3), &
                                size(data4d_k8, 4))
   END SUBROUTINE  xios(recv_field_r8_4d_hdl)

   SUBROUTINE  xios(recv_field_r8_4d)(fieldid, data4d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data4d_k8(:,:,:,:)
      CALL cxios_read_data_k84(fieldid, len(fieldid), data4d_k8, &
                                size(data4d_k8, 1), size(data4d_k8, 2), size(data4d_k8, 3), &
                                size(data4d_k8, 4))
   END SUBROUTINE  xios(recv_field_r8_4d)

   SUBROUTINE  xios(recv_field_r8_5d_hdl)(field_hdl, data5d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data5d_k8(:,:,:,:,:)
      CALL cxios_read_data_k85_hdl(field_hdl%daddr, data5d_k8, &
                                size(data5d_k8, 1), size(data5d_k8, 2), size(data5d_k8, 3), &
                                size(data5d_k8, 4), size(data5d_k8, 5))
   END SUBROUTINE  xios(recv_field_r8_5d_hdl)

   SUBROUTINE  xios(recv_field_r8_5d)(fieldid, data5d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data5d_k8(:,:,:,:,:)
      CALL cxios_read_data_k85(fieldid, len(fieldid), data5d_k8, &
                                size(data5d_k8, 1), size(data5d_k8, 2), size(data5d_k8, 3), &
                                size(data5d_k8, 4), size(data5d_k8, 5))
   END SUBROUTINE  xios(recv_field_r8_5d)

   SUBROUTINE  xios(recv_field_r8_6d_hdl)(field_hdl, data6d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data6d_k8(:,:,:,:,:,:)
      CALL cxios_read_data_k86_hdl(field_hdl%daddr, data6d_k8, &
                                size(data6d_k8, 1), size(data6d_k8, 2), size(data6d_k8, 3), &
                                size(data6d_k8, 4), size(data6d_k8, 5), size(data6d_k8, 6))
   END SUBROUTINE  xios(recv_field_r8_6d_hdl)

   SUBROUTINE  xios(recv_field_r8_6d)(fieldid, data6d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data6d_k8(:,:,:,:,:,:)
      CALL cxios_read_data_k86(fieldid, len(fieldid), data6d_k8, &
                                size(data6d_k8, 1), size(data6d_k8, 2), size(data6d_k8, 3), &
                                size(data6d_k8, 4), size(data6d_k8, 5), size(data6d_k8, 6))
   END SUBROUTINE  xios(recv_field_r8_6d)

  SUBROUTINE  xios(recv_field_r8_7d_hdl)(field_hdl, data7d_k8)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data7d_k8(:,:,:,:,:,:,:)
      CALL cxios_read_data_k87_hdl(field_hdl%daddr, data7d_k8, &
                                size(data7d_k8, 1), size(data7d_k8, 2), size(data7d_k8, 3), &
                                size(data7d_k8, 4), size(data7d_k8, 5), size(data7d_k8, 6), &
                                size(data7d_k8, 7))
   END SUBROUTINE  xios(recv_field_r8_7d_hdl)

  SUBROUTINE  xios(recv_field_r8_7d)(fieldid, data7d_k8)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 8), DIMENSION(*), INTENT(OUT) :: data7d_k8(:,:,:,:,:,:,:)
      CALL cxios_read_data_k87(fieldid, len(fieldid), data7d_k8, &
                                size(data7d_k8, 1), size(data7d_k8, 2), size(data7d_k8, 3), &
                                size(data7d_k8, 4), size(data7d_k8, 5), size(data7d_k8, 6), &
                                size(data7d_k8, 7))
   END SUBROUTINE  xios(recv_field_r8_7d)

   SUBROUTINE xios(recv_field_r4_0d_hdl)(field_hdl, data0d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4)              , INTENT(OUT):: data0d_k4
      CALL cxios_read_data_k40_hdl(field_hdl%daddr, data0d_k4, 1)
   END SUBROUTINE xios(recv_field_r4_0d_hdl)

   SUBROUTINE xios(recv_field_r4_0d)(fieldid, data0d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4)              , INTENT(OUT):: data0d_k4
      CALL cxios_read_data_k40(fieldid, len(fieldid), data0d_k4, 1)
   END SUBROUTINE xios(recv_field_r4_0d)

   SUBROUTINE xios(recv_field_r4_1d_hdl)(field_hdl, data1d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data1d_k4(:)
      CALL cxios_read_data_k41_hdl(field_hdl%daddr, data1d_k4, size(data1d_k4, 1))
   END SUBROUTINE xios(recv_field_r4_1d_hdl)

   SUBROUTINE xios(recv_field_r4_1d)(fieldid, data1d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data1d_k4(:)
      CALL cxios_read_data_k41(fieldid, len(fieldid), data1d_k4, size(data1d_k4, 1))
   END SUBROUTINE xios(recv_field_r4_1d)

   SUBROUTINE xios(recv_field_r4_2d_hdl)(field_hdl, data2d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data2d_k4(:,:)
      CALL cxios_read_data_k42_hdl(field_hdl%daddr, data2d_k4, size(data2d_k4, 1), size(data2d_k4, 2))
   END SUBROUTINE xios(recv_field_r4_2d_hdl)

   SUBROUTINE xios(recv_field_r4_2d)(fieldid, data2d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data2d_k4(:,:)
      CALL cxios_read_data_k42(fieldid, len(fieldid), data2d_k4, size(data2d_k4, 1), size(data2d_k4, 2))
   END SUBROUTINE xios(recv_field_r4_2d)

   SUBROUTINE xios(recv_field_r4_3d_hdl)(field_hdl, data3d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data3d_k4(:,:,:)
      CALL cxios_read_data_k43_hdl(field_hdl%daddr, data3d_k4, size(data3d_k4, 1), size(data3d_k4, 2), size(data3d_k4, 3))
   END SUBROUTINE xios(recv_field_r4_3d_hdl)

   SUBROUTINE xios(recv_field_r4_3d)(fieldid, data3d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data3d_k4(:,:,:)
      CALL cxios_read_data_k43(fieldid, len(fieldid), data3d_k4, size(data3d_k4, 1), size(data3d_k4, 2), size(data3d_k4, 3))
   END SUBROUTINE xios(recv_field_r4_3d)

   SUBROUTINE  xios(recv_field_r4_4d_hdl)(field_hdl, data4d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data4d_k4(:,:,:,:)
      CALL cxios_read_data_k44_hdl(field_hdl%daddr, data4d_k4, &
                                size(data4d_k4, 1), size(data4d_k4, 2), size(data4d_k4, 3), &
                                size(data4d_k4, 4))
   END SUBROUTINE  xios(recv_field_r4_4d_hdl)

   SUBROUTINE  xios(recv_field_r4_4d)(fieldid, data4d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data4d_k4(:,:,:,:)
      CALL cxios_read_data_k44(fieldid, len(fieldid), data4d_k4, &
                                size(data4d_k4, 1), size(data4d_k4, 2), size(data4d_k4, 3), &
                                size(data4d_k4, 4))
   END SUBROUTINE  xios(recv_field_r4_4d)

   SUBROUTINE  xios(recv_field_r4_5d_hdl)(field_hdl, data5d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data5d_k4(:,:,:,:,:)
      CALL cxios_read_data_k45_hdl(field_hdl%daddr, data5d_k4, &
                                size(data5d_k4, 1), size(data5d_k4, 2), size(data5d_k4, 3), &
                                size(data5d_k4, 4), size(data5d_k4, 5))
   END SUBROUTINE  xios(recv_field_r4_5d_hdl)

   SUBROUTINE  xios(recv_field_r4_5d)(fieldid, data5d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data5d_k4(:,:,:,:,:)
      CALL cxios_read_data_k45(fieldid, len(fieldid), data5d_k4, &
                                size(data5d_k4, 1), size(data5d_k4, 2), size(data5d_k4, 3), &
                                size(data5d_k4, 4), size(data5d_k4, 5))
   END SUBROUTINE  xios(recv_field_r4_5d)

   SUBROUTINE  xios(recv_field_r4_6d_hdl)(field_hdl, data6d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data6d_k4(:,:,:,:,:,:)
      CALL cxios_read_data_k46_hdl(field_hdl%daddr, data6d_k4, &
                                size(data6d_k4, 1), size(data6d_k4, 2), size(data6d_k4, 3), &
                                size(data6d_k4, 4), size(data6d_k4, 5), size(data6d_k4, 6))
   END SUBROUTINE  xios(recv_field_r4_6d_hdl)

   SUBROUTINE  xios(recv_field_r4_6d)(fieldid, data6d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data6d_k4(:,:,:,:,:,:)
      CALL cxios_read_data_k46(fieldid, len(fieldid), data6d_k4, &
                                size(data6d_k4, 1), size(data6d_k4, 2), size(data6d_k4, 3), &
                                size(data6d_k4, 4), size(data6d_k4, 5), size(data6d_k4, 6))
   END SUBROUTINE  xios(recv_field_r4_6d)

   SUBROUTINE  xios(recv_field_r4_7d_hdl)(field_hdl, data7d_k4)
   IMPLICIT NONE
      TYPE(txios(field))              :: field_hdl
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data7d_k4(:,:,:,:,:,:,:)
      CALL cxios_read_data_k47_hdl(field_hdl%daddr, data7d_k4, &
                                size(data7d_k4, 1), size(data7d_k4, 2), size(data7d_k4, 3), &
                                size(data7d_k4, 4), size(data7d_k4, 5), size(data7d_k4, 6), &
                                size(data7d_k4, 7))
   END SUBROUTINE  xios(recv_field_r4_7d_hdl)

   SUBROUTINE  xios(recv_field_r4_7d)(fieldid, data7d_k4)
   IMPLICIT NONE
      CHARACTER(len = *)               , INTENT(IN) :: fieldid
      REAL     (kind = 4), DIMENSION(*), INTENT(OUT) :: data7d_k4(:,:,:,:,:,:,:)
      CALL cxios_read_data_k47(fieldid, len(fieldid), data7d_k4, &
                                size(data7d_k4, 1), size(data7d_k4, 2), size(data7d_k4, 3), &
                                size(data7d_k4, 4), size(data7d_k4, 5), size(data7d_k4, 6), &
                                size(data7d_k4, 7))
   END SUBROUTINE  xios(recv_field_r4_7d)

   ! Get variable functions
   LOGICAL FUNCTION xios(getVar_k8)(varId, data_k8)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len = *)               , INTENT(IN) :: varId
      REAL     (kind = 8)              , INTENT(OUT):: data_k8

      CALL cxios_get_variable_data_k8(varId, len(varId), data_k8, val)

      xios(getVar_k8) = val
   END FUNCTION xios(getVar_k8)

   LOGICAL FUNCTION xios(getVar_k4)(varId, data_k4)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len = *)               , INTENT(IN) :: varId
      REAL     (kind = 4)              , INTENT(OUT):: data_k4

      CALL cxios_get_variable_data_k4(varId, len(varId), data_k4, val)

      xios(getVar_k4) = val
   END FUNCTION xios(getVar_k4)

   LOGICAL FUNCTION xios(getVar_int)(varId, data_int)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len = *)               , INTENT(IN) :: varId
      INTEGER                          , INTENT(OUT):: data_int

      CALL cxios_get_variable_data_int(varId, len(varId), data_int, val)

      xios(getVar_int) = val
   END FUNCTION xios(getVar_int)

   LOGICAL FUNCTION xios(getVar_logic)(varId, data_logic)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len  = *)              , INTENT(IN) :: varId
      LOGICAL  ,INTENT(OUT)                         :: data_logic
      LOGICAL (C_BOOL)                              :: data_tmp

      CALL cxios_get_variable_data_logic(varId, len(varId), data_tmp, val)
      xios(getVar_logic) = val
      IF (val) data_logic = data_tmp
   END FUNCTION xios(getVar_logic)

   LOGICAL FUNCTION xios(getVar_char)(varId, data_char)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len  = *)              , INTENT(IN) :: varId
      CHARACTER(len  = *)              , INTENT(OUT):: data_char

      CALL cxios_get_variable_data_char(varId, len(varId), data_char, len(data_char), val)

      xios(getVar_char) = val
   END FUNCTION xios(getVar_char)

   ! Set variable functions
   LOGICAL FUNCTION xios(setVar_k8)(varId, data_k8)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len = *)               , INTENT(IN) :: varId
      REAL     (kind = 8)              , INTENT(IN) :: data_k8

      CALL cxios_set_variable_data_k8(varId, len(varId), data_k8, val)

      xios(setVar_k8) = val
   END FUNCTION xios(setVar_k8)

   LOGICAL FUNCTION xios(setVar_k4)(varId, data_k4)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len = *)               , INTENT(IN) :: varId
      REAL     (kind = 4)              , INTENT(IN) :: data_k4

      CALL cxios_set_variable_data_k4(varId, len(varId), data_k4, val)

      xios(setVar_k4) = val
   END FUNCTION xios(setVar_k4)

   LOGICAL FUNCTION xios(setVar_int)(varId, data_int)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                           :: val
      CHARACTER(len = *)               , INTENT(IN) :: varId
      INTEGER                          , INTENT(IN) :: data_int

      CALL cxios_set_variable_data_int(varId, len(varId), data_int, val)

      xios(setVar_int) = val
   END FUNCTION xios(setVar_int)

   LOGICAL FUNCTION xios(setVar_logic)(varId, data_logic)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL(kind = C_BOOL)                        :: val
      CHARACTER(len  = *)              , INTENT(IN) :: varId
      LOGICAL                          , INTENT(IN) :: data_logic
      LOGICAL  (kind = C_BOOL)                      :: data_tmp

      data_tmp = data_logic
      CALL cxios_set_variable_data_logic(varId, len(varId), data_tmp, val)

      xios(setVar_logic) = val
   END FUNCTION xios(setVar_logic)

   LOGICAL FUNCTION xios(setVar_char)(varId, data_char)
   USE ISO_C_BINDING
   IMPLICIT NONE
      LOGICAL  (kind = C_BOOL)                      :: val
      CHARACTER(len  = *)              , INTENT(IN) :: varId
      CHARACTER(len  = *)              , INTENT(IN) :: data_char

      CALL cxios_set_variable_data_char(varId, len(varId), data_char, len(data_char), val)

      xios(setVar_char) = val
   END FUNCTION xios(setVar_char)

END MODULE IDATA
