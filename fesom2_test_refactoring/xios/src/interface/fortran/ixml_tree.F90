#include "xios_fortran_prefix.hpp"

MODULE IXML_TREE
   USE, INTRINSIC :: ISO_C_BINDING
   USE ISCALAR
   USE IAXIS
   USE IFILE
   USE IFIELD
   USE IGRID
   USE IDOMAIN
   USE IVARIABLE
   
   USE IZOOM_DOMAIN
   USE IINTERPOLATE_DOMAIN
   USE IGENERATE_RECTILINEAR_DOMAIN
   USE ICOMPUTE_CONNECTIVITY_DOMAIN
   USE IEXPAND_DOMAIN

   USE IZOOM_AXIS
   USE IINTERPOLATE_AXIS
   USE IINVERSE_AXIS
   USE IREDUCE_DOMAIN_TO_AXIS
   USE IEXTRACT_DOMAIN_TO_AXIS

   USE IREDUCE_AXIS_TO_SCALAR
   USE IEXTRACT_AXIS_TO_SCALAR
   USE IREDUCE_DOMAIN_TO_SCALAR

   INTERFACE ! Ne pas appeler directement/Interface FORTRAN 2003 <-> C99

      SUBROUTINE cxios_xml_tree_add_field(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_field

      SUBROUTINE cxios_xml_tree_add_grid(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_grid

      SUBROUTINE cxios_xml_tree_add_file(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_file

      SUBROUTINE cxios_xml_tree_add_scalar(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_scalar

      SUBROUTINE cxios_xml_tree_add_axis(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_axis

      SUBROUTINE cxios_xml_tree_add_domain(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_domain

      SUBROUTINE cxios_xml_tree_add_fieldtofile(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_fieldtofile

      SUBROUTINE cxios_xml_tree_add_variabletofile(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_variabletofile


      SUBROUTINE cxios_xml_tree_add_variabletofield(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_variabletofield


      SUBROUTINE cxios_xml_tree_add_fieldgroup(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_fieldgroup

      SUBROUTINE cxios_xml_tree_add_gridgroup(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_gridgroup

      SUBROUTINE cxios_xml_tree_add_filegroup(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_filegroup

      SUBROUTINE cxios_xml_tree_add_scalargroup(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_scalargroup

      SUBROUTINE cxios_xml_tree_add_axisgroup(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_axisgroup

      SUBROUTINE cxios_xml_tree_add_domaingroup(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_domaingroup

      SUBROUTINE cxios_xml_tree_add_fieldgrouptofile(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_fieldgrouptofile

      SUBROUTINE cxios_xml_tree_add_variablegrouptofile(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_variablegrouptofile

      SUBROUTINE cxios_xml_tree_add_variablegrouptofield(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_variablegrouptofield

      SUBROUTINE cxios_xml_tree_add_scalartogrid(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_scalartogrid

      SUBROUTINE cxios_xml_tree_add_axistogrid(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_axistogrid

      SUBROUTINE cxios_xml_tree_add_domaintogrid(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_domaintogrid

      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      !!!   TRANSFORMATIONS 
      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      !!! DOMAIN
      SUBROUTINE cxios_xml_tree_add_zoomdomaintodomain(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_zoomdomaintodomain

      SUBROUTINE cxios_xml_tree_add_interpolatedomaintodomain(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_interpolatedomaintodomain

      SUBROUTINE cxios_xml_tree_add_generatedomaintodomain(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_generatedomaintodomain

      SUBROUTINE cxios_xml_tree_add_computeconnectivitydomaintodomain(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_computeconnectivitydomaintodomain

      SUBROUTINE cxios_xml_tree_add_expanddomaintodomain(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_expanddomaintodomain

      !!!! AXIS
      SUBROUTINE cxios_xml_tree_add_zoomaxistoaxis(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_zoomaxistoaxis

      SUBROUTINE cxios_xml_tree_add_interpolateaxistoaxis(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_interpolateaxistoaxis

      SUBROUTINE cxios_xml_tree_add_inverseaxistoaxis(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_inverseaxistoaxis

      SUBROUTINE cxios_xml_tree_add_reducedomaintoaxistoaxis(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_reducedomaintoaxistoaxis

      SUBROUTINE cxios_xml_tree_add_extractdomaintoaxistoaxis(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_extractdomaintoaxistoaxis

      !!! SCALAR
      SUBROUTINE cxios_xml_tree_add_reduceaxistoscalartoscalar(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_reduceaxistoscalartoscalar

      SUBROUTINE cxios_xml_tree_add_extractaxistoscalartoscalar(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_extractaxistoscalartoscalar

      SUBROUTINE cxios_xml_tree_add_reducedomaintoscalartoscalar(parent_, child_, child_id, child_id_size) BIND(C)
         USE ISO_C_BINDING
         INTEGER  (kind = C_INTPTR_T), VALUE        :: parent_
         INTEGER  (kind = C_INTPTR_T)               :: child_
         CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: child_id
         INTEGER  (kind = C_INT)     , VALUE        :: child_id_size
      END SUBROUTINE cxios_xml_tree_add_reducedomaintoscalartoscalar

      SUBROUTINE cxios_xml_tree_show(filename, filename_size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR), DIMENSION(*) :: filename
         INTEGER  (kind = C_INT) , VALUE        :: filename_size
      END SUBROUTINE cxios_xml_tree_show

      SUBROUTINE cxios_xml_parse_file(filename, filename_size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR), DIMENSION(*) :: filename
         INTEGER  (kind = C_INT) , VALUE        :: filename_size
      END SUBROUTINE cxios_xml_parse_file

      SUBROUTINE cxios_xml_parse_string(xmlcontent, xmlcontent_size) BIND(C)
         USE ISO_C_BINDING
         CHARACTER(kind = C_CHAR), DIMENSION(*) :: xmlcontent
         INTEGER  (kind = C_INT) , VALUE        :: xmlcontent_size
      END SUBROUTINE cxios_xml_parse_string

   END INTERFACE


   CONTAINS ! Fonctions disponibles pour les utilisateurs.

   SUBROUTINE xios(add_scalar)(parent_hdl, child_hdl, child_id)
      TYPE(txios(scalargroup))     , INTENT(IN) :: parent_hdl
      TYPE(txios(scalar))          , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_scalar(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_scalar(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_scalar)

   SUBROUTINE xios(add_axis)(parent_hdl, child_hdl, child_id)
      TYPE(txios(axisgroup))     , INTENT(IN) :: parent_hdl
      TYPE(txios(axis))          , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_axis(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_axis(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_axis)

   SUBROUTINE xios(add_file)(parent_hdl, child_hdl, child_id)
      TYPE(txios(filegroup))      , INTENT(IN) :: parent_hdl
      TYPE(txios(file))           , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN)  :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_file(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_file(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_file)

   SUBROUTINE xios(add_grid)(parent_hdl, child_hdl, child_id)
      TYPE(txios(gridgroup))     , INTENT(IN) :: parent_hdl
      TYPE(txios(grid))          , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id
      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_grid(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_grid(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_grid)


   SUBROUTINE xios(add_field)(parent_hdl, child_hdl, child_id)
      TYPE(txios(fieldgroup))     , INTENT(IN) :: parent_hdl
      TYPE(txios(field))          , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_field(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_field(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_field)


   SUBROUTINE xios(add_domain)(parent_hdl, child_hdl, child_id)
      TYPE(txios(domaingroup))     , INTENT(IN) :: parent_hdl
      TYPE(txios(domain))     , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_domain(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_domain(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_domain)

   SUBROUTINE xios(add_fieldtofile)(parent_hdl, child_hdl, child_id)
      TYPE(txios(file))            , INTENT(IN) :: parent_hdl
      TYPE(txios(field))           , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_fieldtofile(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_fieldtofile(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_fieldtofile)

   SUBROUTINE xios(add_variabletofile)(parent_hdl, child_hdl, child_id)
      TYPE(txios(file))            , INTENT(IN) :: parent_hdl
      TYPE(txios(variable))        , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_variabletofile(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_variabletofile(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_variabletofile)

   SUBROUTINE xios(add_variabletofield)(parent_hdl, child_hdl, child_id)
      TYPE(txios(field))            , INTENT(IN) :: parent_hdl
      TYPE(txios(variable))         , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL  , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_variabletofield(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_variabletofield(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_variabletofield)

   SUBROUTINE xios(add_scalargroup)(parent_hdl, child_hdl, child_id)
      TYPE(txios(scalargroup))      , INTENT(IN) :: parent_hdl
      TYPE(txios(scalargroup))      , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_scalargroup(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_scalargroup(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_scalargroup)

   SUBROUTINE xios(add_axisgroup)(parent_hdl, child_hdl, child_id)
      TYPE(txios(axisgroup))      , INTENT(IN) :: parent_hdl
      TYPE(txios(axisgroup))      , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_axisgroup(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_axisgroup(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_axisgroup)


   SUBROUTINE xios(add_filegroup)(parent_hdl, child_hdl, child_id)
      TYPE(txios(filegroup))      , INTENT(IN) :: parent_hdl
      TYPE(txios(filegroup))      , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_filegroup(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_filegroup(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_filegroup)

   SUBROUTINE xios(add_gridgroup)(parent_hdl, child_hdl, child_id)
      TYPE(txios(gridgroup))      , INTENT(IN) :: parent_hdl
      TYPE(txios(gridgroup))      , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_gridgroup(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_gridgroup(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_gridgroup)


   SUBROUTINE xios(add_fieldgroup)(parent_hdl, child_hdl, child_id)
      TYPE(txios(fieldgroup))     , INTENT(IN) :: parent_hdl
      TYPE(txios(fieldgroup))     , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL, INTENT(IN) :: child_id
      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_fieldgroup(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_fieldgroup(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF
   END SUBROUTINE xios(add_fieldgroup)

   SUBROUTINE xios(add_domaingroup)(parent_hdl, child_hdl, child_id)
      TYPE(txios(domaingroup))     , INTENT(IN) :: parent_hdl
      TYPE(txios(domaingroup))     , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_domaingroup(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_domaingroup(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_domaingroup)

   SUBROUTINE xios(add_fieldgrouptofile)(parent_hdl, child_hdl, child_id)
      TYPE(txios(file))            , INTENT(IN) :: parent_hdl
      TYPE(txios(fieldgroup))      , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_fieldgrouptofile(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_fieldgrouptofile(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_fieldgrouptofile)

   SUBROUTINE xios(add_variablegrouptofile)(parent_hdl, child_hdl, child_id)
      TYPE(txios(file))            , INTENT(IN) :: parent_hdl
      TYPE(txios(variablegroup))   , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_variablegrouptofile(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_variablegrouptofile(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_variablegrouptofile)

   SUBROUTINE xios(add_variablegrouptofield)(parent_hdl, child_hdl, child_id)
      TYPE(txios(field))            , INTENT(IN) :: parent_hdl
      TYPE(txios(variablegroup))    , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL  , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_variablegrouptofield(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_variablegrouptofield(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_variablegrouptofield)

   SUBROUTINE xios(add_scalartogrid)(parent_hdl, child_hdl, child_id)
      TYPE(txios(grid))             , INTENT(IN) :: parent_hdl
      TYPE(txios(scalar))           , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL  , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_scalartogrid(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_scalartogrid(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_scalartogrid)

   SUBROUTINE xios(add_axistogrid)(parent_hdl, child_hdl, child_id)
      TYPE(txios(grid))             , INTENT(IN) :: parent_hdl
      TYPE(txios(axis))             , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL  , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_axistogrid(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_axistogrid(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_axistogrid)

   SUBROUTINE xios(add_domaintogrid)(parent_hdl, child_hdl, child_id)
      TYPE(txios(grid))             , INTENT(IN) :: parent_hdl
      TYPE(txios(domain))           , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL  , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_domaintogrid(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_domaintogrid(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_domaintogrid)

   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!!         TRANSFORMATIONS
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   !!!         DOAMIN
   SUBROUTINE xios(add_zoomdomaintodomain)(parent_hdl, child_hdl, child_id)
      TYPE(txios(domain))           , INTENT(IN) :: parent_hdl
      TYPE(txios(zoom_domain))      , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL  , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_zoomdomaintodomain(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_zoomdomaintodomain(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_zoomdomaintodomain)

   SUBROUTINE xios(add_interpolatedomaintodomain)(parent_hdl, child_hdl, child_id)
      TYPE(txios(domain))             , INTENT(IN) :: parent_hdl
      TYPE(txios(interpolate_domain)) , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL    , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_interpolatedomaintodomain(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_interpolatedomaintodomain(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_interpolatedomaintodomain)

   SUBROUTINE xios(add_generatedomaintodomain)(parent_hdl, child_hdl, child_id)
      TYPE(txios(domain))                      , INTENT(IN) :: parent_hdl
      TYPE(txios(generate_rectilinear_domain)) , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL             , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_generatedomaintodomain(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_generatedomaintodomain(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_generatedomaintodomain)

   SUBROUTINE xios(add_computeconnectivitydomaintodomain)(parent_hdl, child_hdl, child_id)
      TYPE(txios(domain))                      , INTENT(IN) :: parent_hdl
      TYPE(txios(compute_connectivity_domain)) , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL             , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_computeconnectivitydomaintodomain(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_computeconnectivitydomaintodomain(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_computeconnectivitydomaintodomain)

   SUBROUTINE xios(add_expanddomaintodomain)(parent_hdl, child_hdl, child_id)
      TYPE(txios(domain))                      , INTENT(IN) :: parent_hdl
      TYPE(txios(expand_domain))               , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL             , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_expanddomaintodomain(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_expanddomaintodomain(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_expanddomaintodomain)

   !!!  AXIS
   SUBROUTINE xios(add_zoomaxistoaxis)(parent_hdl, child_hdl, child_id)
      TYPE(txios(axis))                      , INTENT(IN) :: parent_hdl
      TYPE(txios(zoom_axis))                 , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL           , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_zoomaxistoaxis(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_zoomaxistoaxis(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_zoomaxistoaxis)

   SUBROUTINE xios(add_interpolateaxistoaxis)(parent_hdl, child_hdl, child_id)
      TYPE(txios(axis))                      , INTENT(IN) :: parent_hdl
      TYPE(txios(interpolate_axis))          , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL           , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_interpolateaxistoaxis(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_interpolateaxistoaxis(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_interpolateaxistoaxis)

   SUBROUTINE xios(add_inverseaxistoaxis)(parent_hdl, child_hdl, child_id)
      TYPE(txios(axis))                      , INTENT(IN) :: parent_hdl
      TYPE(txios(inverse_axis))              , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL           , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_inverseaxistoaxis(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_inverseaxistoaxis(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_inverseaxistoaxis)

   SUBROUTINE xios(add_reducedomaintoaxistoaxis)(parent_hdl, child_hdl, child_id)
      TYPE(txios(axis))                        , INTENT(IN) :: parent_hdl
      TYPE(txios(reduce_domain_to_axis))       , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL             , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_reducedomaintoaxistoaxis(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_reducedomaintoaxistoaxis(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_reducedomaintoaxistoaxis)

   SUBROUTINE xios(add_extractdomaintoaxistoaxis)(parent_hdl, child_hdl, child_id)
      TYPE(txios(axis))                        , INTENT(IN) :: parent_hdl
      TYPE(txios(extract_domain_to_axis))      , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL             , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_extractdomaintoaxistoaxis(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_extractdomaintoaxistoaxis(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_extractdomaintoaxistoaxis)

   !!! SCALAR
   SUBROUTINE xios(add_reduceaxistoscalartoscalar)(parent_hdl, child_hdl, child_id)
      TYPE(txios(scalar))                    , INTENT(IN) :: parent_hdl
      TYPE(txios(reduce_axis_to_scalar))     , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL           , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_reduceaxistoscalartoscalar(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_reduceaxistoscalartoscalar(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_reduceaxistoscalartoscalar)

   SUBROUTINE xios(add_extractaxistoscalartoscalar)(parent_hdl, child_hdl, child_id)
      TYPE(txios(scalar))                    , INTENT(IN) :: parent_hdl
      TYPE(txios(extract_axis_to_scalar))    , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL           , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_extractaxistoscalartoscalar(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_extractaxistoscalartoscalar(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_extractaxistoscalartoscalar)

   SUBROUTINE xios(add_reducedomaintoscalartoscalar)(parent_hdl, child_hdl, child_id)
      TYPE(txios(scalar))                      , INTENT(IN) :: parent_hdl
      TYPE(txios(reduce_domain_to_scalar))     , INTENT(OUT):: child_hdl
      CHARACTER(len = *), OPTIONAL             , INTENT(IN) :: child_id

      IF (PRESENT(child_id)) THEN
         CALL cxios_xml_tree_add_reducedomaintoscalartoscalar(parent_hdl%daddr, child_hdl%daddr, child_id, len(child_id))
      ELSE
         CALL cxios_xml_tree_add_reducedomaintoscalartoscalar(parent_hdl%daddr, child_hdl%daddr, "NONE", -1)
      END IF

   END SUBROUTINE xios(add_reducedomaintoscalartoscalar)

END MODULE IXML_TREE
