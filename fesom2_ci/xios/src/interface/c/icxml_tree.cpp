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
#include "context.hpp"
#include "node_type.hpp"

extern "C"
{
// /////////////////////////////// Définitions ////////////////////////////// //

   // ----------------------- Redéfinition de types ----------------------------

   typedef xios::CContext * XContextPtr;

   typedef xios::CGrid      * XGridPtr;
   typedef xios::CGridGroup * XGridGroupPtr;

   typedef xios::CFile      * XFilePtr;
   typedef xios::CFileGroup * XFileGroupPtr;

   typedef xios::CField      * XFieldPtr;
   typedef xios::CFieldGroup * XFieldGroupPtr;

   typedef xios::CDomain      * XDomainPtr;
   typedef xios::CDomainGroup * XDomainGroupPtr;

   typedef xios::CScalar      * XScalarPtr;
   typedef xios::CScalarGroup * XScalarGroupPtr;

   typedef xios::CAxis      * XAxisPtr;
   typedef xios::CAxisGroup * XAxisGroupPtr;

   typedef xios::CVariable      *  XVariablePtr;
   typedef xios::CVariableGroup *  XVariableGroupPtr;

   typedef xios::CTransformation<CDomain>   *  XTransformationDomainPtr;
   typedef xios::CZoomDomain                *  XZoomDomainPtr;
   typedef xios::CInterpolateDomain         *  XInterpolateDomainPtr;
   typedef xios::CGenerateRectilinearDomain *  XGenerateRectilinearDomainPtr;
   typedef xios::CComputeConnectivityDomain *  XComputeConnectivityDomainPtr;
   typedef xios::CExpandDomain              *  XExpandDomainPtr;

   typedef xios::CTransformation<CAxis>     *  XTransformationAxisPtr;
   typedef xios::CZoomAxis                  *  XZoomAxisPtr;
   typedef xios::CInterpolateAxis           *  XInterpolateAxisPtr;
   typedef xios::CInverseAxis               *  XInverseAxisPtr;
   typedef xios::CExtractDomainToAxis       *  XExtractDomainToAxisPtr;
   typedef xios::CReduceDomainToAxis        *  XReduceDomainToAxisPtr;

   typedef xios::CTransformation<CScalar>   *  XTransformationScalarPtr;
   typedef xios::CReduceAxisToScalar        *  XReduceAxisToScalarPtr;
   typedef xios::CReduceDomainToScalar      *  XReduceDomainToScalarPtr;
   typedef xios::CExtractAxisToScalar       *  XExtractAxisToScalarPtr;


   // ----------------------- Ajout d'enfant à un parent -----------------------

   void cxios_xml_tree_add_field
      (XFieldGroupPtr  parent_, XFieldPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChild(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChild() ;
      }
      CTimer::get("XIOS").suspend() ;
  }

   void cxios_xml_tree_add_grid
      (XGridGroupPtr   parent_, XGridPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChild(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChild() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_file
      (XFileGroupPtr parent_, XFilePtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChild(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChild() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_axis
      (XAxisGroupPtr parent_, XAxisPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChild(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChild() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_scalar
      (XScalarGroupPtr parent_, XScalarPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChild(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChild() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_domain
      (XDomainGroupPtr parent_, XDomainPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChild(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChild() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_fieldtofile
      (XFilePtr parent_, XFieldPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;

      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addField(child_id_str);
      }
      else
      {
         *child_ = parent_->addField();
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_variabletofile
      (XFilePtr parent_, XVariablePtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;

      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addVariable(child_id_str);
      }
      else
      {
         *child_ = parent_->addVariable();
      }
      CTimer::get("XIOS").suspend() ;
   }

    void cxios_xml_tree_add_variabletofield
      (XFieldPtr parent_, XVariablePtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;

      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addVariable(child_id_str);
      }
      else
      {
         *child_ = parent_->addVariable();
      }
      CTimer::get("XIOS").suspend() ;
   }
   // ----------------------- Ajout de groupe à un parent ----------------------

   void cxios_xml_tree_add_fieldgroup
      (XFieldGroupPtr  parent_, XFieldGroupPtr * child_, const char * child_id, int child_id_size)
   {
     std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChildGroup(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChildGroup() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_gridgroup
      (XGridGroupPtr   parent_, XGridGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChildGroup(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChildGroup() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_filegroup
      (XFileGroupPtr parent_, XFileGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChildGroup(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChildGroup() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_scalargroup
      (XScalarGroupPtr parent_, XScalarGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChildGroup(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChildGroup() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_axisgroup
      (XAxisGroupPtr parent_, XAxisGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChildGroup(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChildGroup() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_domaingroup
      (XDomainGroupPtr parent_, XDomainGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->createChildGroup(child_id_str) ;
      }
      else
      {
         *child_ = parent_->createChildGroup() ;
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_fieldgrouptofile
      (XFilePtr parent_, XFieldGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addFieldGroup(child_id_str);
      }
      else
      {
         *child_ = parent_->addFieldGroup();
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_variablegrouptofile
      (XFilePtr parent_, XVariableGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addVariableGroup(child_id_str);
      }
      else
      {
         *child_ = parent_->addVariableGroup();
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_variablegrouptofield
      (XFieldPtr parent_, XVariableGroupPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addVariableGroup(child_id_str);
      }
      else
      {
         *child_ = parent_->addVariableGroup();
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_scalartogrid
      (XGridPtr parent_, XScalarPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addScalar(child_id_str);
      }
      else
      {
         *child_ = parent_->addScalar();
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_axistogrid
      (XGridPtr parent_, XAxisPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addAxis(child_id_str);
      }
      else
      {
         *child_ = parent_->addAxis();
      }
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_domaintogrid
      (XGridPtr parent_, XDomainPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         *child_ = parent_->addDomain(child_id_str);
      }
      else
      {
         *child_ = parent_->addDomain();
      }
      CTimer::get("XIOS").suspend() ;
   }

   //---------------------------------------------------------------------------
   //-------------------------Transformations -----------------------------------
   //---------------------------------------------------------------------------
   void cxios_xml_tree_add_zoomdomaintodomain
      (XDomainPtr parent_, XZoomDomainPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationDomainPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_ZOOM_DOMAIN, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_ZOOM_DOMAIN);
      }
      *child_ = static_cast<XZoomDomainPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_interpolatedomaintodomain
      (XDomainPtr parent_, XInterpolateDomainPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationDomainPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_INTERPOLATE_DOMAIN, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_INTERPOLATE_DOMAIN);
      }
      *child_ = static_cast<XInterpolateDomainPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_generatedomaintodomain
      (XDomainPtr parent_, XGenerateRectilinearDomainPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationDomainPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_GENERATE_RECTILINEAR_DOMAIN, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_GENERATE_RECTILINEAR_DOMAIN);
      }
      *child_ = static_cast<XGenerateRectilinearDomainPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_computeconnectivitydomaintodomain
      (XDomainPtr parent_, XComputeConnectivityDomainPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationDomainPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_EXPAND_DOMAIN, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_EXPAND_DOMAIN);
      }
      *child_ = static_cast<XComputeConnectivityDomainPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_expanddomaintodomain
      (XDomainPtr parent_, XExpandDomainPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationDomainPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_COMPUTE_CONNECTIVITY_DOMAIN, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_COMPUTE_CONNECTIVITY_DOMAIN);
      }
      *child_ = static_cast<XExpandDomainPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   // -----------------------Axis transformation--------------------------------
   void cxios_xml_tree_add_zoomaxistoaxis
      (XAxisPtr parent_, XZoomAxisPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationAxisPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_ZOOM_AXIS, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_ZOOM_AXIS);
      }
      *child_ = static_cast<XZoomAxisPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_interpolateaxistoaxis
      (XAxisPtr parent_, XInterpolateAxisPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationAxisPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_INTERPOLATE_AXIS, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_INTERPOLATE_AXIS);
      }
      *child_ = static_cast<XInterpolateAxisPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_inverseaxistoaxis
      (XAxisPtr parent_, XInverseAxisPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationAxisPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_INVERSE_AXIS, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_INVERSE_AXIS);
      }
      *child_ = static_cast<XInverseAxisPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_extractdomaintoaxistoaxis
      (XAxisPtr parent_, XExtractDomainToAxisPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationAxisPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_EXTRACT_DOMAIN_TO_AXIS, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_EXTRACT_DOMAIN_TO_AXIS);
      }
      *child_ = static_cast<XExtractDomainToAxisPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_reducedomaintoaxistoaxis
      (XAxisPtr parent_, XReduceDomainToAxisPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationAxisPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_REDUCE_DOMAIN_TO_AXIS, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_REDUCE_DOMAIN_TO_AXIS);
      }
      *child_ = static_cast<XReduceDomainToAxisPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }


   void cxios_xml_tree_add_reduceaxistoscalartoscalar
      (XScalarPtr parent_, XReduceAxisToScalarPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationScalarPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_REDUCE_AXIS_TO_SCALAR, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_REDUCE_AXIS_TO_SCALAR);
      }
      *child_ = static_cast<XReduceAxisToScalarPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_reducedomaintoscalartoscalar
      (XScalarPtr parent_, XReduceDomainToScalarPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationScalarPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_REDUCE_DOMAIN_TO_SCALAR, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_REDUCE_DOMAIN_TO_SCALAR);
      }
      *child_ = static_cast<XReduceDomainToScalarPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   void cxios_xml_tree_add_extractaxistoscalartoscalar
      (XScalarPtr parent_, XExtractAxisToScalarPtr * child_, const char * child_id, int child_id_size)
   {
      std::string child_id_str;
      XTransformationScalarPtr tmpChild_;
      CTimer::get("XIOS").resume() ;
      if (cstr2string(child_id, child_id_size, child_id_str))
      {
         tmpChild_ = parent_->addTransformation(TRANS_EXTRACT_AXIS_TO_SCALAR, child_id_str);
      }
      else
      {
         tmpChild_ = parent_->addTransformation(TRANS_EXTRACT_AXIS_TO_SCALAR);
      }
      *child_ = static_cast<XExtractAxisToScalarPtr>(tmpChild_);
      CTimer::get("XIOS").suspend() ;
   }

   // ----------------------- Affichage de l'arborescence ----------------------

//   void cxios_xml_tree_show   (const char * filename, int filename_size)
//   {
//      std::string filename_str;
//      try
//      {
//         if (cstr2string(filename, filename_size, filename_str))
//            xios::CTreeManager::PrintTreeToFile(filename_str);
//         else
//            xios::CTreeManager::PrintTreeToStream(std::clog);
//      }
//      catch (xios::CException & exc)
//      {
//         std::cerr << exc.getMessage() << std::endl;
//         exit (EXIT_FAILURE);
//      }
//  }


   // ----------------------- Parsing de document xml --------------------------

//   void cxios_xml_parse_file  (const char * filename  , int filename_size)//
//   {
//      std::string filename_str;
//      if (!cstr2string(filename, filename_size, filename_str)) return;
//
//      try
//      {
//         xios::CTreeManager::ParseFile(filename_str);
//      }
//      catch (xios::CException & exc)
//      {
//         std::cerr << exc.getMessage() << std::endl;
//         exit (EXIT_FAILURE);
//      }
//   }

//   void cxios_xml_parse_string(const char * xmlcontent, int xmlcontent_size)
//   {
//      std::string xmlcontent_str;
//      if (!cstr2string(xmlcontent, xmlcontent_size, xmlcontent_str)) return;
//
//      try
//      {
//         xios::CTreeManager::ParseString(xmlcontent_str);
//      }
//      catch (xios::CException & exc)
//      {
//         std::cerr << exc.getMessage() << std::endl;
//         exit (EXIT_FAILURE);
//      }
//   }



} // extern "C"
