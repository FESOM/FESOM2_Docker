#include "scalar.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "object_factory.hpp"
#include "xios_spl.hpp"
#include "type.hpp"

namespace xios {

   /// ////////////////////// Définitions ////////////////////// ///

   CScalar::CScalar(void)
      : CObjectTemplate<CScalar>()
      , CScalarAttributes()
      , relFiles()
   { /* Ne rien faire de plus */ }

   CScalar::CScalar(const StdString & id)
      : CObjectTemplate<CScalar>(id)
      , CScalarAttributes()
      , relFiles()
   { /* Ne rien faire de plus */ }

   CScalar::~CScalar(void)
   { /* Ne rien faire de plus */ }

   std::map<StdString, ETranformationType> CScalar::transformationMapList_ = std::map<StdString, ETranformationType>();
   bool CScalar::dummyTransformationMapList_ = CScalar::initializeTransformationMap(CScalar::transformationMapList_);
   bool CScalar::initializeTransformationMap(std::map<StdString, ETranformationType>& m)
   {
     m["reduce_axis"]   = TRANS_REDUCE_AXIS_TO_SCALAR;
     m["extract_axis"]  = TRANS_EXTRACT_AXIS_TO_SCALAR;
     m["reduce_domain"] = TRANS_REDUCE_DOMAIN_TO_SCALAR;
     m["reduce_scalar"] = TRANS_REDUCE_SCALAR_TO_SCALAR;

     return true ;
   }

   StdString CScalar::GetName(void)   { return (StdString("scalar")); }
   StdString CScalar::GetDefName(void){ return (CScalar::GetName()); }
   ENodeType CScalar::GetType(void)   { return (eScalar); }

   CScalar* CScalar::createScalar()
   {
     CScalar* scalar = CScalarGroup::get("scalar_definition")->createChild();
     return scalar;
   }

   bool CScalar::IsWritten(const StdString & filename) const
   {
      return (this->relFiles.find(filename) != this->relFiles.end());
   }

   void CScalar::addRelFile(const StdString& filename)
   {
      this->relFiles.insert(filename);
   }

   void CScalar::checkAttributes(void)
   {
   }

  void CScalar::checkAttributesOnClient()
  {

  }

  /*!
    Compare two scalar objects. 
    They are equal if only if they have identical attributes as well as their values.
    Moreover, they must have the same transformations.
  \param [in] scalar Compared scalar
  \return result of the comparison
  */
  bool CScalar::isEqual(CScalar* obj)
  {
    vector<StdString> excludedAttr;
    excludedAttr.push_back("scalar_ref");
    bool objEqual = SuperClass::isEqual(obj, excludedAttr);
    if (!objEqual) return objEqual;

    TransMapTypes thisTrans = this->getAllTransformations();
    TransMapTypes objTrans  = obj->getAllTransformations();

    TransMapTypes::const_iterator it, itb, ite;
    std::vector<ETranformationType> thisTransType, objTransType;
    for (it = thisTrans.begin(); it != thisTrans.end(); ++it)
      thisTransType.push_back(it->first);
    for (it = objTrans.begin(); it != objTrans.end(); ++it)
      objTransType.push_back(it->first);

    if (thisTransType.size() != objTransType.size()) return false;
    for (int idx = 0; idx < thisTransType.size(); ++idx)
      objEqual &= (thisTransType[idx] == objTransType[idx]);

    return objEqual;
  }

  CTransformation<CScalar>* CScalar::addTransformation(ETranformationType transType, const StdString& id)
  {
    transformationMap_.push_back(std::make_pair(transType, CTransformation<CScalar>::createTransformation(transType,id)));
    return transformationMap_.back().second;
  }

  bool CScalar::hasTransformation()
  {
    return (!transformationMap_.empty());
  }

  void CScalar::setTransformations(const TransMapTypes& scalarTrans)
  {
    transformationMap_ = scalarTrans;
  }

  CScalar::TransMapTypes CScalar::getAllTransformations(void)
  {
    return transformationMap_;
  }

  void CScalar::duplicateTransformation(CScalar* src)
  {
    if (src->hasTransformation())
    {
      this->setTransformations(src->getAllTransformations());
    }
  }

  /*!
   * Go through the hierarchy to find the scalar from which the transformations must be inherited
   */
  void CScalar::solveInheritanceTransformation()
  {
    if (hasTransformation() || !hasDirectScalarReference())
      return;

    CScalar* scalar = this;
    std::vector<CScalar*> refScalar;
    while (!scalar->hasTransformation() && scalar->hasDirectScalarReference())
    {
      refScalar.push_back(scalar);
      scalar = scalar->getDirectScalarReference();
    }

    if (scalar->hasTransformation())
      for (size_t i = 0; i < refScalar.size(); ++i)
        refScalar[i]->setTransformations(scalar->getAllTransformations());
  }

  /*!
    Parse children nodes of a scalar in xml file.
    \param node child node to process
  */
  void CScalar::parse(xml::CXMLNode & node)
  {
    SuperClass::parse(node);

    if (node.goToChildElement())
    {
      StdString nodeElementName;
      do
      {
        StdString nodeId("");
        if (node.getAttributes().end() != node.getAttributes().find("id"))
        { nodeId = node.getAttributes()["id"]; }

        nodeElementName = node.getElementName();
        std::map<StdString, ETranformationType>::const_iterator ite = transformationMapList_.end(), it;
        it = transformationMapList_.find(nodeElementName);
        if (ite != it)
        {
          transformationMap_.push_back(std::make_pair(it->second, CTransformation<CScalar>::createTransformation(it->second,
                                                                                                                 nodeId,
                                                                                                                 &node)));
        }
        else
        {
          ERROR("void CScalar::parse(xml::CXMLNode & node)",
                << "The transformation " << nodeElementName << " has not been supported yet.");
        }
      } while (node.goToNextElement()) ;
      node.goToParentElement();
    }
  }

  // Definition of some macros
  DEFINE_REF_FUNC(Scalar,scalar)

} // namespace xios
