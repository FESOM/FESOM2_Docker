#ifndef __XIOS_GENERATE_INTERFACE_IMPL_HPP__
#define __XIOS_GENERATE_INTERFACE_IMPL_HPP__

#include "xios_spl.hpp"
#include "generate_interface.hpp"
#include "type_util.hpp"
#include "indent.hpp"
#include "enum.hpp"
#include "array_new.hpp"
#include "date.hpp"

namespace xios
{
  template<> string CInterface::getStrFortranType<int>(void) { return string("INTEGER"); }
  template<> string CInterface::getStrFortranType<bool>(void) { return string("LOGICAL"); }
  template<> string CInterface::getStrFortranType<double>(void) { return string("REAL"); }
  template<> string CInterface::getStrFortranType<float>(void) { return string("REAL"); }
  template<> string CInterface::getStrFortranType<CDate>(void) { return string("TYPE(txios(date))"); }
  template<> string CInterface::getStrFortranType<CDuration>(void) { return string("TYPE(txios(duration))"); }

  template<> string CInterface::getStrFortranKind<int>(void) { return string(""); }
  template<> string CInterface::getStrFortranKind<bool>(void) { return string(""); }
  template<> string CInterface::getStrFortranKind<double>(void) { return string("(KIND=8)"); }
  template<> string CInterface::getStrFortranKind<float>(void) { return string("(KIND=4)"); }
  template<> string CInterface::getStrFortranKind<CDate>(void) { return string(""); }
  template<> string CInterface::getStrFortranKind<CDuration>(void) { return string(""); }

  template<> string CInterface::getStrFortranKindC<int>(void) { return string("(KIND=C_INT)"); }
  template<> string CInterface::getStrFortranKindC<bool>(void) { return string("(KIND=C_BOOL)"); }
  template<> string CInterface::getStrFortranKindC<double>(void) { return string("(KIND=C_DOUBLE)"); }
  template<> string CInterface::getStrFortranKindC<float>(void) { return string("(KIND=C_FLOAT)"); }
  template<> string CInterface::getStrFortranKindC<CDate>(void) { return string(""); }
  template<> string CInterface::getStrFortranKindC<CDuration>(void) { return string(""); }

  template<> bool CInterface::matchingTypeCFortran<int>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<bool>(void) { return false; }
  template<> bool CInterface::matchingTypeCFortran<double>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<float>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<CDate>(void) { return true; }
  template<> bool CInterface::matchingTypeCFortran<CDuration>(void) { return true; }

// /////////////////////////////////////////////////
// //                 C Interface                 //
// /////////////////////////////////////////////////

  void CInterface::AttributeIsDefinedCInterface(ostream& oss, const string& className, const string& name)
  {
    oss << "bool cxios_is_defined_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl)" << iendl;
    oss << "{" << iendl;
    oss << "   CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "   bool isDefined = " << className << "_hdl->" << name << ".hasInheritedValue();" << iendl;
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "   return isDefined;" << iendl;
    oss << "}" << std::endl;
  }

  template <class T>
  void CInterface::AttributeCInterface(ostream& oss, const string& className, const string& name)
  {
    string typeName = getStrType<T>();

    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << " " << name << ")" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".setValue(" << name << ");" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ")" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  *" << name << " = " << className << "_hdl->" << name << ".getInheritedValue();" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, const char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  std::string " << name << "_str;" << iendl;
    oss << "  if (!cstr2string(" << name << ", " << name << "_size, " << name << "_str)) return;" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".setValue(" << name << "_str);" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  if (!string_copy(" << className << "_hdl->" << name << ".getInheritedValue(), " << name << ", " << name << "_size))" << iendl;
    oss << "    ERROR(\"void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int "
        << name << "_size)\", << \"Input string is too short\");" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<CEnumBase>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, const char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  std::string " << name << "_str;" << iendl;
    oss << "  if (!cstr2string(" << name << ", " << name << "_size, " << name << "_str)) return;" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".fromString(" << name << "_str);" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int " << name << "_size)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  if (!string_copy(" << className << "_hdl->" << name << ".getInheritedStringValue(), " << name << ", " << name << "_size))" << iendl;
    oss << "    ERROR(\"void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, char * " << name << ", int "
        << name << "_size)\", << \"Input string is too short\");" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<CDate>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_date " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".allocate();" << iendl;
    oss << "  CDate& " << name << " = " << className << "_hdl->" << name << ".get();" << iendl;
    oss << "  " << name << ".setDate(" << name << "_c.year," << iendl;
    oss << "                         " << name << "_c.month," << iendl;
    oss << "                         " << name << "_c.day," << iendl;
    oss << "                         " << name << "_c.hour," << iendl;
    oss << "                         " << name << "_c.minute," << iendl;
    oss << "                         " << name << "_c.second);" << iendl;
    oss << "  if (" << name << ".hasRelCalendar())" << iendl;
    oss << "    " << name << ".checkDate();" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_date* " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  CDate " << name << " = " << className << "_hdl->" << name << ".getInheritedValue();" << iendl;
    oss << "  " << name << "_c->year = " << name << ".getYear();" << iendl;
    oss << "  " << name << "_c->month = " << name << ".getMonth();" << iendl;
    oss << "  " << name << "_c->day = " << name << ".getDay();" << iendl;
    oss << "  " << name << "_c->hour = " << name << ".getHour();" << iendl;
    oss << "  " << name << "_c->minute = " << name << ".getMinute();" << iendl;
    oss << "  " << name << "_c->second = " << name << ".getSecond();" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

  template<>
  void CInterface::AttributeCInterface<CDuration>(ostream& oss, const string& className, const string& name)
  {
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_duration " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  " << className << "_hdl->" << name << ".allocate();" << iendl;
    oss << "  CDuration& " << name << " = " << className << "_hdl->" << name << ".get();" << iendl;
    oss << "  " << name << ".year = " << name << "_c.year;" << iendl;
    oss << "  " << name << ".month = " << name << "_c.month;" << iendl;
    oss << "  " << name << ".day = " << name << "_c.day;" << iendl;
    oss << "  " << name << ".hour = " << name << "_c.hour;" << iendl;
    oss << "  " << name << ".minute = " << name << "_c.minute;" << iendl;
    oss << "  " << name << ".second = " << name << "_c.second;" << iendl;
    oss << "  " << name << ".timestep = " << name << "_c.timestep;" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;

    oss << iendl;

    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, cxios_duration* " << name << "_c)" << iendl;
    oss << "{" << iendl;
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl;
    oss << "  CDuration " << name << " = " << className << "_hdl->" << name << ".getInheritedValue();" << iendl;
    oss << "  " << name << "_c->year = " << name << ".year;" << iendl;
    oss << "  " << name << "_c->month = " << name << ".month;" << iendl;
    oss << "  " << name << "_c->day = " << name << ".day;" << iendl;
    oss << "  " << name << "_c->hour = " << name << ".hour;" << iendl;
    oss << "  " << name << "_c->minute = " << name << ".minute;" << iendl;
    oss << "  " << name << "_c->second = " << name << ".second;" << iendl;
    oss << "  " << name << "_c->timestep = " << name << ".timestep;" << iendl;
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl;
    oss << "}" << std::endl;
  }

#undef macro

// /////////////////////////////////////////////////
// //          Fortran 2003 Interface             //
// /////////////////////////////////////////////////

  void CInterface::AttributeIsDefinedFortran2003Interface(ostream& oss, const string& className, const string& name)
  {
    oss << "FUNCTION cxios_is_defined_" << className << "_" << name << "(" << className << "_hdl) BIND(C)" << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  LOGICAL(kind=C_BOOL) :: cxios_is_defined_" << className << "_" << name << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "END FUNCTION cxios_is_defined_" << className << "_" << name << std::endl;
  }

  template <class T>
  void CInterface::AttributeFortran2003Interface(ostream& oss, const string& className, const string& name)
  {
    string fortranType=getStrFortranType<T>();
    string fortranKindC=getStrFortranKindC<T>();

//    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    int indent = oss.iword(iendl.index);
    string str = "SUBROUTINE cxios_set_" + className + "_" + name + "(" + className + "_hdl, " + name + ") BIND(C)";
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  " << fortranType << " " << fortranKindC << "      , VALUE :: " << name << iendl;
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl;
    oss << iendl;
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  " << fortranType << " " << fortranKindC << "             :: " << name << iendl;
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl;
  }

  template <>
  void CInterface::AttributeFortran2003Interface<string>(ostream& oss, const string& className, const string& name)
  {
//    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", " << name << "_size) BIND(C)" << iendl;
    int indent = oss.iword(iendl.index);
    string str ="SUBROUTINE cxios_set_" + className + "_" + name + "(" + className + "_hdl, " + name + ", " + name + "_size) BIND(C)";
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: " << name << iendl;
    oss << "  INTEGER  (kind = C_INT)     , VALUE        :: " << name << "_size" << iendl;
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl;
    oss << iendl;
//    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", " << name << "_size) BIND(C)" << iendl;
    str = "SUBROUTINE cxios_get_" + className + "_" + name + "(" + className + "_hdl, " + name + ", " + name + "_size) BIND(C)";
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  CHARACTER(kind = C_CHAR)    , DIMENSION(*) :: " << name << iendl;
    oss << "  INTEGER  (kind = C_INT)     , VALUE        :: " << name << "_size" << iendl;
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl;
  }

  template <>
  void CInterface::AttributeFortran2003Interface<CDuration>(ostream& oss, const string& className, const string& name)
  {
//    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    string str = "SUBROUTINE cxios_set_" + className + "_" + name + "(" + className + "_hdl, " + name + ") BIND(C)";
    int indent = oss.iword(iendl.index);
    if ((str.length() + indent) >132)
    {
      oss << str.substr(0,130-indent) ;
      oss << "&" << endl;
      oss << "&" << str.substr(130-indent,str.length()) ;
    }
    else
    {
      oss << str;
    }
    oss << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  USE IDURATION" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  TYPE(txios(duration)), VALUE :: " << name << iendl;
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl;
    oss << iendl;
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ") BIND(C)" << iendl;
    oss << "  USE ISO_C_BINDING" << iendl;
    oss << "  USE IDURATION" << iendl;
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE :: " << className << "_hdl" << iendl;
    oss << "  TYPE(txios(duration)) :: " << name << iendl;
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl;
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceDeclaration(ostream& oss, const string& className, const string& name)
  {
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name;
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " :: " << name << "_tmp";
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceGetDeclaration(ostream& oss, const string& className, const string& name)
  {
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name;
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " :: " << name << "_tmp";
  }

  void CInterface::AttributeFortranInterfaceIsDefinedDeclaration(ostream& oss, const string& className, const string& name)
  {
    oss << "LOGICAL, OPTIONAL, INTENT(OUT) :: " << name << iendl;
    oss << "LOGICAL(KIND=C_BOOL) :: " << name << "_tmp";
  }

  template <>
  void CInterface::AttributeFortranInterfaceDeclaration<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "CHARACTER(len = *) , OPTIONAL, INTENT(IN) :: " << name;
  }

  template <>
  void CInterface::AttributeFortranInterfaceGetDeclaration<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "CHARACTER(len = *) , OPTIONAL, INTENT(OUT) :: " << name;
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceBody(ostream& oss, const string& className, const string& name)
  {
    string name_tmp=name+"__tmp";

    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    if (!matchingTypeCFortran<T>())
    {
      oss << "  " << name_tmp << " = " << name << "_" << iendl;
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl;
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ")" << iendl;
    }
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl;
           oss << "(" << className << "_hdl%daddr, " << name << "_)" << iendl; }
    oss << "ENDIF";
  }

  template <class T>
  void CInterface::AttributeFortranInterfaceGetBody(ostream& oss, const string& className, const string& name)
  {
    string name_tmp=name+"__tmp";

    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    if (!matchingTypeCFortran<T>())
    {
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl;
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ")" << iendl;
      oss << "  " << name << "_ = " << name_tmp << iendl;
    }
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl;
           oss << "(" << className << "_hdl%daddr, " << name << "_)" << iendl; }
    oss << "ENDIF";
  }

  void CInterface::AttributeFortranInterfaceIsDefinedBody(ostream& oss, const string& className, const string& name)
  {
    string name_tmp=name+"__tmp";

    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    oss << "  " << name << "__tmp = cxios_is_defined_" << className << "_" << name << " &" << iendl;
    oss << "(" << className << "_hdl%daddr)" << iendl;
    oss << "  " << name << "_ = " << name_tmp << iendl;
    oss << "ENDIF";
  }

  template <>
  void CInterface::AttributeFortranInterfaceBody<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl;
    oss << "(" << className << "_hdl%daddr, " << name << "_, len(" << name << "_))" << iendl;
    oss << "ENDIF";
  }

  template <>
  void CInterface::AttributeFortranInterfaceGetBody<string>(ostream& oss, const string& className, const string& name)
  {
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl;
    oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl;
    oss << "(" << className << "_hdl%daddr, " << name << "_, len(" << name << "_))" << iendl;
    oss << "ENDIF";
  }

// declaration for CArray

#define macro(T) \
  template <> \
  void CInterface::AttributeCInterface<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",1> tmp(" << name << ", shape(extent[0]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",1> tmp(" << name << ", shape(extent[0]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",2> tmp(" << name << ", shape(extent[0], extent[1]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",2> tmp(" << name << ", shape(extent[0], extent[1]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",3> tmp(" << name << ", shape(extent[0], extent[1], extent[2]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",3> tmp(" << name << ", shape(extent[0], extent[1], extent[2]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",4> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",4> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",5> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",5> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  } \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",6> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",6> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  }  \
\
  template <> \
  void CInterface::AttributeCInterface<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    string typeName=getStrType<T>(); \
\
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",7> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);" << iendl; \
    oss << "  " << className << "_hdl->" << name << ".reference(tmp.copy());" << iendl; \
    /*oss << "  " << className << "_hdl->sendAttributToServer(" << className << "_hdl->" << name << ");" << iendl;*/ \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << typeName << "* " << name << ", int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  CArray<" << typeName << ",7> tmp(" << name << ", shape(extent[0], extent[1], extent[2], extent[3], extent[4], extent[5], extent[6]), neverDeleteData);" << iendl; \
    oss << "  tmp=" << className << "_hdl->" << name << ".getInheritedValue();" << iendl; \
    oss << "   CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  }

macro(bool)
macro(double)
macro(int)

#undef macro

#define macro(N,EXTENT)\
  template <>\
  void CInterface::AttributeCInterface<CArray<StdString,N> >(ostream& oss, const string& className, const string& name)\
  { \
    oss << "void cxios_set_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << "char* " << name <<", int str_len, int* str_size, int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  "<<className<<"_hdl->"<<name<<".resize(shape("<<EXTENT<<"));"<<iendl;\
    oss << "  Array<StdString,"<<#N<<">::iterator it, itb="<<className<<"_hdl->"<<name<<".begin(), ite="<<className<<"_hdl->"<<name<<".end() ;"<<iendl ;\
    oss << "  int i, n ;"<< iendl; \
    oss << "  for(it=itb, i=0, n=0 ; it!=ite ; ++it,n+=str_len,++i) *it=StdString(&"<<name<<"[n],str_size[i]) ;"<<iendl ;\
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
    oss << iendl; \
    oss << "void cxios_get_" << className << "_" << name << "(" << className << "_Ptr " << className << "_hdl, " << "char* " << name << ", int str_size, int* extent)" << iendl; \
    oss << "{" << iendl; \
    oss << "  CTimer::get(\"XIOS\").resume();" << iendl; \
    oss << "  Array<StdString,"<<#N<<">::const_iterator it, itb="<<className<<"_hdl->"<<name<<".getInheritedValue().begin(), ite="<<className<<"_hdl->"<<name<<".getInheritedValue().end() ;" << iendl; \
    oss << "  int n ;"<< iendl; \
    oss << "  for(it=itb, n=0 ; it!=ite ; ++it, n+=str_size) it->copy(&"<<name<<"[n],it->size()) ; "<< iendl; \
    oss << "  CTimer::get(\"XIOS\").suspend();" << iendl; \
    oss << "}" << std::endl; \
  }

macro(1,"extent[0]")
macro(2,"extent[0],extent[1]")
macro(3,"extent[0],extent[1],extent[2]")
macro(4,"extent[0],extent[1],extent[2],extent[3]")
macro(5,"extent[0],extent[1],extent[2],extent[3],extent[4]")
macro(6,"extent[0],extent[1],extent[2],extent[3],extent[4],extent[5]")
macro(7,"extent[0],extent[1],extent[2],extent[3],extent[4],extent[5],extent[6]")
#undef macro
// /////////////////////////////////////////////////
// //          Fortran 2003 Interface             //
// /////////////////////////////////////////////////

#define macro(T) \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  } \
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  } \
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }  \
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }\
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }\
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }\
 \
  template <> \
  void CInterface::AttributeFortran2003Interface<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    string fortranType=getStrFortranType<T>(); \
    string fortranKindC=getStrFortranKindC<T>(); \
      \
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  " << fortranType << " " << fortranKindC << "     , DIMENSION(*) :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }

  macro(bool)
  macro(double)
  macro(int)

  #undef macro

#define macro(T)\
  template <>\
  void CInterface::AttributeFortran2003Interface<CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "SUBROUTINE cxios_set_" << className << "_" << name << "(" << className << "_hdl, " << name << ", str_len, str_size, extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  CHARACTER (KIND=C_CHAR), DIMENSION(*)    :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), VALUE            :: str_len" << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: str_size" << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_set_" << className << "_" << name << std::endl; \
    oss << iendl; \
    oss << "SUBROUTINE cxios_get_" << className << "_" << name << "(" << className << "_hdl, " << name << ", str_size, extent) BIND(C)" << iendl; \
    oss << "  USE ISO_C_BINDING" << iendl; \
    oss << "  INTEGER (kind = C_INTPTR_T), VALUE       :: " << className << "_hdl" << iendl; \
    oss << "  CHARACTER (KIND=C_CHAR), DIMENSION(*)    :: " << name << iendl; \
    oss << "  INTEGER (kind = C_INT), VALUE            :: str_size" << iendl; \
    oss << "  INTEGER (kind = C_INT), DIMENSION(*)     :: extent" << iendl; \
    oss << "END SUBROUTINE cxios_get_" << className << "_" << name << std::endl; \
  }
  macro(1)
  macro(2)
  macro(3)
  macro(4)
  macro(5)
  macro(6)
  macro(7)

#undef macro

#define macro(T) \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:)"; \
  } \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:)"; \
  }\
 \
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(IN) :: " << name << "(:,:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:,:)"; \
  } \
 \
  template <> \
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  { \
    oss << getStrFortranType<T>() << " " << getStrFortranKind<T>() << " , OPTIONAL, INTENT(OUT) :: " << name << "(:,:,:,:,:,:,:)"; \
    if (!matchingTypeCFortran<T>()) oss << iendl << getStrFortranType<T>() << " " << getStrFortranKindC<T>() << " , ALLOCATABLE :: " << name << "_tmp(:,:,:,:,:,:,:)"; \
  }

  macro(bool)
  macro(double)
  macro(int)

#undef macro

#define macro(T,EXTENT)\
  template <> \
  void CInterface::AttributeFortranInterfaceDeclaration<CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "CHARACTER(len=*) , OPTIONAL, INTENT(IN) :: " << name << "("<<EXTENT<<")"; \
  }\
\
  template <>\ 
  void CInterface::AttributeFortranInterfaceGetDeclaration<CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "CHARACTER(len=*) , OPTIONAL, INTENT(OUT) :: " << name << "("<<EXTENT<<")"; \
  }
  macro(1,":")
  macro(2,":,:")
  macro(3,":,:,:")
  macro(4,":,:,:,:")
  macro(5,":,:,:,:,:")
  macro(6,":,:,:,:,:,:")
  macro(7,":,:,:,:,:,:,:")

#undef macro




  

#define macro(T) \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
  \
  template <>  \
  void CInterface::AttributeFortranInterfaceBody< CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6), &" << iendl; \
      oss << " SIZE(" << name << "_,7)))" << iendl; \
      oss << "  " << name_tmp << " = " << name << "_" << iendl; \
      oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
    } \
    else { oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }

  macro(bool)
  macro(double)
  macro(int)

#undef macro

#define macro(T)\
  template <>\
  void CInterface::AttributeFortranInterfaceBody< CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
     oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
     oss << "  CALL cxios_set_" << className << "_" << name << " &" << iendl; \
     oss << "(" << className << "_hdl%daddr, " << name <<"_, LEN("<<name<<"_), LEN_TRIM("<<name<< "_), SHAPE(" << name << "_))" << iendl; \
     oss << "ENDIF"; \
  }

  macro(1)
  macro(2)
#undef macro

#define macro(T) \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,1> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
    } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,2> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
    } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,3> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,4> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; }\
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,5> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }\
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,6> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  } \
 \
  template <>  \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<T,7> >(ostream& oss, const string& className, const string& name) \
  {  \
    string name_tmp=name+"__tmp"; \
      \
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    if (!matchingTypeCFortran<T>())  \
    { \
      oss << "  ALLOCATE(" << name_tmp << "(SIZE(" << name << "_,1), SIZE(" << name << "_,2), SIZE(" << name << "_,3), &" << iendl; \
      oss << " SIZE(" << name << "_,4), SIZE(" << name << "_,5), SIZE(" << name << "_,6), &" << iendl; \
      oss << " SIZE(" << name << "_,7)))" << iendl; \
      oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
      oss << "(" << className << "_hdl%daddr, " << name_tmp << ", SHAPE(" << name << "_))" << iendl; \
      oss << "  " << name << "_ = " << name_tmp << iendl; \
      } \
    else { oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
           oss << "(" << className << "_hdl%daddr, " << name << "_, SHAPE(" << name << "_))" << iendl; } \
    oss << "ENDIF"; \
  }

  macro(bool)
  macro(double)
  macro(int)

#undef macro

#define macro(T)\
  template <> \
  void CInterface::AttributeFortranInterfaceGetBody< CArray<StdString,T> >(ostream& oss, const string& className, const string& name)\
  {\
    oss << "IF (PRESENT(" << name << "_)) THEN" << iendl; \
    oss << "  CALL cxios_get_" << className << "_" << name << " &" << iendl; \
    oss << "(" << className << "_hdl%daddr, " << name << "_, LEN("<<name<<"_), SHAPE(" << name << "_))" << iendl; \
    oss << "ENDIF"; \
  }
  macro(1)
  macro(2)
  macro(3)
  macro(4)
  macro(5)
  macro(6)
  macro(7)

#undef macro
  
}
#endif
