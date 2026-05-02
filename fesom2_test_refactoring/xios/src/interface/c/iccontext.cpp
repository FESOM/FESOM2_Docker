/* ************************************************************************** *
 *      Copyright © IPSL/LSCE, xios, Avril 2010 - Octobre 2011         *
 * ************************************************************************** */

#include <boost/multi_array.hpp>

#include <memory>

#include "xios.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"

#include "calendar_type.hpp"

#include "icutil.hpp"
#include "timer.hpp"
#include "context.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------

   typedef enum { D360 = 0 , ALLLEAP, NOLEAP, JULIAN, GREGORIAN } XCalendarType ;

   typedef xios::CContext * XContextPtr;

   // ------------------------ Création des handle -----------------------------

   void cxios_context_handle_create (XContextPtr * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;
      CTimer::get("XIOS").resume() ;

      std::vector<xios::CContext*> def_vector =
            xios::CContext::getRoot()->getChildList();

      for (std::size_t i = 0; i < def_vector.size(); i++)
      {
          if (def_vector[i]->getId().compare(id) == 0)
          {
            *_ret = def_vector[i];
             CTimer::get("XIOS").suspend() ;
            return;
          }
      }
       CTimer::get("XIOS").suspend() ;
       ERROR("void cxios_context_handle_create (XContextPtr * _ret, const char * _id, int _id_len)",
             << "Context "<<id<<"  unknown");
      // Lever une exeception ici
   }
   CATCH_DUMP_STACK

   // ------------------------ Changements de contextes ------------------------

   void cxios_context_get_current(XContextPtr* context)
   TRY
   {
      CTimer::get("XIOS").resume();
      *context = CContext::getCurrent();
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK

   void cxios_context_get_id(XContextPtr context, char * _id, int _id_len)
   TRY
   {
      string_copy(context->getId(),_id,_id_len);
   }
   CATCH_DUMP_STACK
   
   void cxios_context_set_current(XContextPtr context, bool withswap)
   TRY
   {
      CTimer::get("XIOS").resume() ;
      CContext::setCurrent(context->getId());
      CTimer::get("XIOS").suspend() ;
   }
   CATCH_DUMP_STACK

   // -------------------- Vérification des identifiants -----------------------

   void cxios_context_valid_id (bool * _ret, const char * _id, int _id_len)
   TRY
   {
      std::string id;
      if (!cstr2string(_id, _id_len, id)) return;

      CTimer::get("XIOS").resume();
      std::vector<xios::CContext*> def_vector =
            xios::CContext::getRoot()->getChildList();

      *_ret = false;
      for (std::size_t i = 0; i < def_vector.size(); i++)
      {
        if (def_vector[i]->getId().compare(id) == 0)
        {
          *_ret = true;
          break;
        }
      }
      CTimer::get("XIOS").suspend();
   }
   CATCH_DUMP_STACK
} // extern "C"
