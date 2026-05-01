/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */

#include <boost/multi_array.hpp>

#include <memory>

#include "xios.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"

#include "icutil.hpp"
#include "timer.hpp"
#include "field.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------
   
   typedef xios::CField      * XFieldPtr;
   typedef xios::CFieldGroup * XFieldGroupPtr;
   
   typedef xios::CDomain     * XDomainPtr;
   typedef xios::CAxis       * XAxisPtr;
   typedef xios::CScalar     * XScalarPtr;

// --------------------------------------------------------------------------   
// ------------------------ Création des handle -----------------------------
// --------------------------------------------------------------------------   
   
   void cxios_field_handle_create (XFieldPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id; 
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = CField::get(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK
   
   void cxios_fieldgroup_handle_create (XFieldGroupPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id; 
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = CFieldGroup::get(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   // -------------------- Vérification des identifiants -----------------------

   void cxios_field_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = CField::has(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   void cxios_fieldgroup_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;
      *_ret = CFieldGroup::has(id);
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

// -----------------------------------------------------------------------------------------------------   
// ------------------------- Other functions
// -----------------------------------------------------------------------------------------------------   

  void cxios_field_is_active (XFieldPtr field_hdl, bool at_current_timestep, bool* ret)
  TRY
  {
    CTimer::get("XIOS").resume() ;
    *ret = field_hdl->isActive(at_current_timestep);
    CTimer::get("XIOS").suspend() ;
  }
  CATCH_DUMP_STACK

// -----------------------------------------------------------------------------------------------------
// ------------------------- Retrieving information of grid associated to field
// -----------------------------------------------------------------------------------------------------
  void cxios_field_get_domain_handle(XDomainPtr * domain_hdl_ret, XFieldPtr field_hdl, int domainIndex)
  TRY
  {
     CTimer::get("XIOS").resume() ;
     *domain_hdl_ret = field_hdl->grid->getDomain(domainIndex);
     CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_field_get_axis_handle(XAxisPtr * axis_hdl_ret, XFieldPtr field_hdl, int axisIndex)
  TRY
  {
     CTimer::get("XIOS").resume() ;
     *axis_hdl_ret = field_hdl->grid->getAxis(axisIndex);
     CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK

  void cxios_field_get_scalar_handle(XScalarPtr * scalar_hdl_ret, XFieldPtr field_hdl, int scalarIndex)
  TRY
  {
     CTimer::get("XIOS").resume() ;
     *scalar_hdl_ret = field_hdl->grid->getScalar(scalarIndex);
     CTimer::get("XIOS").suspend();
  }
  CATCH_DUMP_STACK
} // extern "C"
