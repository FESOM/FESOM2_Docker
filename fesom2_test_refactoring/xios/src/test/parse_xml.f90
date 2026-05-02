PROGRAM parse_xml
  USE, INTRINSIC :: ISO_C_BINDING
  IMPLICIT NONE

  INTERFACE
    SUBROUTINE xios_init() BIND(C, name='cxios_init')
    END SUBROUTINE
  END INTERFACE

  CALL xios_init() ! This will parse the XML file and report any parsing error
  WRITE (*,*) 'Parsing finished successfully.'

END PROGRAM parse_xml
