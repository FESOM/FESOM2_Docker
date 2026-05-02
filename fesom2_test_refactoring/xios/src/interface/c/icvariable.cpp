/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */

#include <boost/multi_array.hpp>

#include <memory>

#include "xios.hpp"

#include "object_template.hpp"
#include "group_template.hpp"
#include "attribute_template.hpp"

#include "icutil.hpp"
#include "timer.hpp"
#include "variable.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------
   
   typedef xios::CVariable      * XVariablePtr;
   typedef xios::CVariableGroup * XVariableGroupPtr;

   // ------------------------ Création des handle -----------------------------
   
   void cxios_variable_handle_create (XVariablePtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id; 
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CVariable::get(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK
   
   void cxios_variablegroup_handle_create (XVariableGroupPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id; 
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CVariableGroup::get(id);
      CTimer::get("XIOS").suspend() ;
    }
   CATCH_DUMP_STACK

   // -------------------- Vérification des identifiants -----------------------

   void cxios_variable_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CVariable::has(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   void cxios_variablegroup_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CVariableGroup::has(id);
      CTimer::get("XIOS").suspend() ;

   }
   CATCH_DUMP_STACK
   
} // extern "C"

