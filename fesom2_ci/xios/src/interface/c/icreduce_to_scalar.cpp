/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */

#include <boost/multi_array.hpp>

#include "xios.hpp"

#include "object_template.hpp"
#include "group_template.hpp"
#include "attribute_template.hpp"

#include "icutil.hpp"
#include "timer.hpp"
#include "reduce_axis_to_scalar.hpp"
#include "reduce_domain_to_scalar.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------

   typedef xios::CReduceAxisToScalar      * XReduceAxisToScalarPtr;
   typedef xios::CReduceDomainToScalar    * XReduceDomainToScalarPtr;

   // ------------------------ Création des handle -----------------------------
   void cxios_reduce_axis_to_scalar_handle_create(XReduceAxisToScalarPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CReduceAxisToScalar::get(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   // -------------------- Vérification des identifiants -----------------------
   void cxios_reduce_axis_to_scalar_valid_id(bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CReduceAxisToScalar::has(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   void cxios_reduce_domain_to_scalar_handle_create(XReduceDomainToScalarPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = xios::CReduceDomainToScalar::get(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   // -------------------- Vérification des identifiants -----------------------
   void cxios_reduce_domain_to_scalar_valid_id(bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume() ;
      *_ret = xios::CReduceDomainToScalar::has(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

} // extern "C"
