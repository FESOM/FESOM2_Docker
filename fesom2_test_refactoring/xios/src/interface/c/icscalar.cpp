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
#include "scalar.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------

   typedef xios::CScalar      * XScalarPtr;
   typedef xios::CScalarGroup * XScalarGroupPtr;

   // ------------------------ Création des handle -----------------------------

   void cxios_scalar_handle_create (XScalarPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CScalar::get(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   void cxios_scalargroup_handle_create (XScalarGroupPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CScalarGroup::get(id);
      CTimer::get("XIOS").suspend() ;
    }
   CATCH_DUMP_STACK

   // -------------------- Vérification des identifiants -----------------------

   void cxios_scalar_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CScalar::has(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   void cxios_scalargroup_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CScalarGroup::has(id);
      CTimer::get("XIOS").suspend() ;

   }
   CATCH_DUMP_STACK

} // extern "C"
