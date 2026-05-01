#ifndef __XIOS_CTransformation__
#define __XIOS_CTransformation__

#include "xios_spl.hpp"
#include "xml_node.hpp"
#include "transformation_enum.hpp"

namespace xios {

  ///--------------------------------------------------------------
  /*!
    \class CTransformation
    This class describes inverse_axis in xml file.
  */
  template<typename T>
  class CTransformation
  {
  public:
    typedef typename std::list<std::pair<ETranformationType, CTransformation<T>* > > TransformationMapTypes;
    typedef TransformationMapTypes TransMapTypes;

    public :
      /// Constructeurs ///
      CTransformation(void) {}
      virtual void checkValid(T* dest) {}

      std::vector<StdString> checkAuxInputs() { return checkAuxInputs_(); }
      static CTransformation<T>* createTransformation(ETranformationType transType, const StdString& id, xml::CXMLNode* node=0);

      /// Destructeur ///
      virtual ~CTransformation(void) {}

    protected:
      typedef CTransformation<T>* (*CreateTransformationCallBack)(const StdString&, xml::CXMLNode*);
      typedef std::map<ETranformationType, CreateTransformationCallBack> CallBackMap;
      static CallBackMap* transformationCreationCallBacks_;

      static bool registerTransformation(ETranformationType transType, CreateTransformationCallBack createFn);
      static bool unregisterTransformation(ETranformationType transType);

    protected:
      virtual std::vector<StdString> checkAuxInputs_() { return std::vector<StdString>(); }
  }; // class CTransformation

  template<typename T>
  typename CTransformation<T>::CallBackMap* CTransformation<T>::transformationCreationCallBacks_ = 0; //CTransformation<T>::CallBackMap();

  template<typename T>
  CTransformation<T>* CTransformation<T>::createTransformation(ETranformationType transType, const StdString& id, xml::CXMLNode* node)
  {
    int transTypeInt = transType;
    typename CallBackMap::const_iterator it = (*transformationCreationCallBacks_).find(transType);
    if ((*transformationCreationCallBacks_).end() == it)
    {
       ERROR("CTransformation<T>::createTransformation(ETranformationType transType)",
             << "Transformation type " << transType
             << "doesn't exist. Please define.");
    }
    return (it->second)(id,node);
  }

  template<typename T>
  bool CTransformation<T>::registerTransformation(ETranformationType transType, CreateTransformationCallBack createFn)
  {
    if (0 == transformationCreationCallBacks_)
      transformationCreationCallBacks_ = new CallBackMap();

    return (*transformationCreationCallBacks_).insert(make_pair(transType, createFn)).second;
  }

  template<typename T>
  bool CTransformation<T>::unregisterTransformation(ETranformationType transType)
  {
    int transTypeInt = transType;
    return (1 == (*transformationCreationCallBacks_).erase(transType));
  }

} // namespace xios

#endif // __XIOS_CTransformation__
