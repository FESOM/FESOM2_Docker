#include "interpolate_axis.hpp"
#include "type.hpp"
#include "field.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CInterpolateAxis::CInterpolateAxis(void)
    : CObjectTemplate<CInterpolateAxis>(), CInterpolateAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CInterpolateAxis::CInterpolateAxis(const StdString & id)
    : CObjectTemplate<CInterpolateAxis>(id), CInterpolateAxisAttributes(), CTransformation<CAxis>()
  { /* Ne rien faire de plus */ }

  CInterpolateAxis::~CInterpolateAxis(void)
  {}

  CTransformation<CAxis>* CInterpolateAxis::create(const StdString& id, xml::CXMLNode* node)
  {
    CInterpolateAxis* interpAxis = CInterpolateAxisGroup::get("interpolate_axis_definition")->createChild(id);
    if (node) interpAxis->parse(*node);
    return static_cast<CTransformation<CAxis>*>(interpAxis);
  }

  bool CInterpolateAxis::registerTrans()
  {
    return registerTransformation(TRANS_INTERPOLATE_AXIS, CInterpolateAxis::create);
  }

  bool CInterpolateAxis::_dummyRegistered = CInterpolateAxis::registerTrans();

  //----------------------------------------------------------------

  StdString CInterpolateAxis::GetName(void)    { return StdString("interpolate_axis"); }
  StdString CInterpolateAxis::GetDefName(void) { return StdString("interpolate_axis"); }
  ENodeType CInterpolateAxis::GetType(void)    { return eInterpolateAxis; }

  void CInterpolateAxis::checkValid(CAxis* axisSrc)
  {
    if (this->order.isEmpty()) this->order.setValue(1);
    if (this->coordinate.isEmpty() && !this->coordinate_src.isEmpty()) this->coordinate.setValue(this->coordinate_src.getValue());
    if (this->coordinate_src.isEmpty() && !this->coordinate.isEmpty()) this->coordinate_src.setValue(this->coordinate.getValue());
    int order = this->order.getValue();
    if (order >= axisSrc->n_glo.getValue())
    {
      ERROR("CInterpolateAxis::checkValid(CAxis* axisSrc)",
             << "Order of interpolation is greater than global size of axis source"
             << "Size of axis source " <<axisSrc->getId() << " is " << axisSrc->n_glo.getValue()  << std::endl
             << "Order of interpolation is " << order );
    }

    if (order < 1)
    {
      ERROR("CInterpolateAxis::checkValid(CAxis* axisSrc)",
             << "Order of interpolation is smaller than 1"
             << "Size of axis source " <<axisSrc->getId() << " is " << axisSrc->n_glo.getValue()  << std::endl
             << "Order of interpolation is " << order );
    }


    if (!this->coordinate.isEmpty())
    {
      StdString coordinate = this->coordinate.getValue();
      if (!CField::has(coordinate))
        ERROR("CInterpolateAxis::checkValid(CAxis* axisSrc)",
               << "Coordinate field whose id " << coordinate << "does not exist "
               << "Please define one");
    }
    
    if (!this->coordinate_dst.isEmpty())
    {
      StdString coordinate = this->coordinate_dst.getValue();
      if (!CField::has(coordinate))
        ERROR("CInterpolateAxis::checkValid(CAxis* axisSrc)",
               << "Coordinate field whose id " << coordinate << "does not exist "
               << "Please define one");
    }
   
  }

  std::vector<StdString> CInterpolateAxis::checkAuxInputs_()
  {
    std::vector<StdString> auxInputs;
    if (!this->coordinate.isEmpty() && this->coordinate_src.isEmpty())
    {
      StdString coordinate = this->coordinate.getValue();
      this->coordinate_src.setValue(coordinate);
      if (!CField::has(coordinate))
        ERROR("CInterpolateAxis::checkValid(CAxis* axisSrc)",
               << "Coordinate field whose id " << coordinate << "does not exist "
               << "Please define one");
      auxInputs.push_back(coordinate);
    }
    if (!this->coordinate_src.isEmpty() || !this->coordinate.isEmpty())
    {
      StdString coordinate = !this->coordinate.isEmpty()? this->coordinate.getValue():this->coordinate_src.getValue();
      this->coordinate.setValue(coordinate);
      if (!CField::has(coordinate))
        ERROR("CInterpolateAxis::checkValid(CAxis* axisSrc)",
               << "Coordinate field whose id " << coordinate << "does not exist "
               << "Please define one");
      auxInputs.push_back(coordinate);
    }
    
    if (!this->coordinate_dst.isEmpty())
    {
      StdString coordinate = this->coordinate_dst.getValue();
      if (!CField::has(coordinate))
        ERROR("CInterpolateAxis::checkValid(CAxis* axisSrc)",
               << "Coordinate field whose id " << coordinate << "does not exist "
               << "Please define one");
      auxInputs.push_back(coordinate);
    }

    return auxInputs;
  }
}
