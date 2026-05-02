/*!
   \file grid_transformation.cpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 02 Jul 2015

   \brief Interface for all transformations.
 */
#include "grid_transformation_selector.hpp"
#include "grid.hpp"
#include "algo_types.hpp"

namespace xios {

/*!
  Register transformation to the framework
*/
void CGridTransformationSelector::registerTransformations()
{
  //! Scalar
  CScalarAlgorithmReduceAxis::registerTrans();
  CScalarAlgorithmExtractAxis::registerTrans();
  CScalarAlgorithmReduceDomain::registerTrans();
  CScalarAlgorithmReduceScalar::registerTrans();

  //! Axis
  CAxisAlgorithmZoom::registerTrans();
  CAxisAlgorithmExtractDomain::registerTrans();
  CAxisAlgorithmInterpolate::registerTrans();
  CAxisAlgorithmExtract::registerTrans();
  CAxisAlgorithmInverse::registerTrans();
  CAxisAlgorithmReduceDomain::registerTrans();
  CAxisAlgorithmReduceAxis::registerTrans();
  CAxisAlgorithmTemporalSplitting::registerTrans();
  CAxisAlgorithmDuplicateScalar::registerTrans();

  //! Domain
  CDomainAlgorithmComputeConnectivity::registerTrans();
  CDomainAlgorithmInterpolate::registerTrans();
  CDomainAlgorithmZoom::registerTrans();
  CDomainAlgorithmExpand::registerTrans();
  CDomainAlgorithmReorder::registerTrans();
  CDomainAlgorithmExtract::registerTrans();
}

CGridTransformationSelector::CGridTransformationSelector(CGrid* destination, CGrid* source, TransformationType type)
 : gridSource_(source), gridDestination_(destination), isSameGrid_(false),
  listAlgos_(), algoTypes_(), nbNormalAlgos_(0), nbSpecialAlgos_(0), auxInputs_()
TRY
{
  if (0 == source)
  {  gridSource_ = gridDestination_; }
  if (gridSource_ == gridDestination_) isSameGrid_ = true;

  //Verify the compatibity between two grids
  int numElement = gridDestination_->axis_domain_order.numElements();
  if (numElement != gridSource_->axis_domain_order.numElements())
    ERROR("CGridTransformationSelector::CGridTransformationSelector(CGrid* destination, CGrid* source)",
       << "Two grids have different number of elements"
       << "Number of elements of grid source " <<gridSource_->getId() << " is " << gridSource_->axis_domain_order.numElements()  << std::endl
       << "Number of elements of grid destination " <<gridDestination_->getId() << " is " << numElement);
  registerTransformations();
  initializeTransformations(type);
}
CATCH

/*!
  Initialize the mapping between the first grid source and the original one
  In a series of transformation, for each step, there is a need to "create" a new grid that plays a role of "temporary" source.
Because at the end of the series, we need to know about the index mapping between the final grid destination and original grid source,
for each transformation, we need to make sure that the current "temporary source" maps its global index correctly to the original one.
*/
void CGridTransformationSelector::initializeTransformations(TransformationType type)
TRY
{
  // Initialize algorithms
  initializeAlgorithms();
  ListAlgoType::iterator itb = listAlgos_.begin(),
                         ite = listAlgos_.end(), it;

  for (it = itb; it != ite; ++it)
  {
    ETranformationType transType = (it->second).first;
    if (!isSpecialTransformation(transType))
    {
      ++nbNormalAlgos_;
      if (special == type)
      {
        it = listAlgos_.erase(it);
        --it;
      }
    }
    else
    {
      ++nbSpecialAlgos_;
      if (normal == type)
      {
        it = listAlgos_.erase(it);
        --it;
      }
    }

  }
}
CATCH

CGridTransformationSelector::~CGridTransformationSelector()
TRY
{
  std::vector<CGenericAlgorithmTransformation*>::const_iterator itb = algoTransformation_.begin(), it,
                                                                ite = algoTransformation_.end();
  for (it = itb; it != ite; ++it) delete (*it);
}
CATCH

/*!
  Update position of elements in grid source and grid destination as well as their positions in element list
*/
void CGridTransformationSelector::updateElementPosition()
TRY
{
  int idxScalar = 0, idxAxis = 0, idxDomain = 0;
  CArray<int,1> axisDomainOrderDst = gridDestination_->axis_domain_order;
  std::map<int, int>().swap(elementPositionInGridDst2DomainPosition_);
  std::map<int, int>().swap(elementPositionInGridDst2AxisPosition_);
  std::map<int, int>().swap(elementPositionInGridDst2ScalarPosition_);
  for (int i = 0; i < axisDomainOrderDst.numElements(); ++i)
  {
    int dimElement = axisDomainOrderDst(i);
    if (2 == dimElement)
    {
      elementPositionInGridDst2DomainPosition_[i] = idxDomain;
      ++idxDomain;
    }
    else if (1 == dimElement)
    {
      elementPositionInGridDst2AxisPosition_[i] = idxAxis;
      ++idxAxis;
    }
    else
    {
      elementPositionInGridDst2ScalarPosition_[i] = idxScalar;
      ++idxScalar;
    }
  }

  idxScalar = idxAxis = idxDomain = 0;
  CArray<int,1> axisDomainOrderSrc = gridSource_->axis_domain_order;
  std::map<int, int>().swap(elementPositionInGridSrc2DomainPosition_);
  std::map<int, int>().swap(elementPositionInGridSrc2AxisPosition_);
  std::map<int, int>().swap(elementPositionInGridSrc2ScalarPosition_);
  for (int i = 0; i < axisDomainOrderSrc.numElements(); ++i)
  {
    int dimElement = axisDomainOrderSrc(i);
    if (2 == dimElement)
    {
      elementPositionInGridSrc2DomainPosition_[i] = idxDomain;
      ++idxDomain;
    }
    else if (1 == dimElement)
    {
      elementPositionInGridSrc2AxisPosition_[i] = idxAxis;
      ++idxAxis;
    }
    else
    {
      elementPositionInGridSrc2ScalarPosition_[i] = idxScalar;
      ++idxScalar;
    }
  }
}
CATCH

/*!
  Initialize the algorithms (transformations)
*/
void CGridTransformationSelector::initializeAlgorithms()
TRY
{
  updateElementPosition();
  CArray<int,1> axisDomainOrderDst = gridDestination_->axis_domain_order;
  for (int i = 0; i < axisDomainOrderDst.numElements(); ++i)
  {
    int dimElement = axisDomainOrderDst(i);
    if (2 == dimElement)
    {
      initializeDomainAlgorithms(i);
    }
    else if (1 == dimElement)
    {
      initializeAxisAlgorithms(i);
    }
    else
    {
      initializeScalarAlgorithms(i);
    }
  }
}
CATCH

/*!
  Initialize the algorithms corresponding to transformation info contained in each scalar.
If an scalar has transformations, these transformations will be represented in form of vector of CTransformation pointers
In general, each scalar can have several transformations performed on itself. However, should they be done seperately or combinely (of course in order)?
For now, one approach is to do these combinely but maybe this needs changing.
\param [in] axisPositionInGrid position of an axis in grid. (for example: a grid with one domain and one scalar, position of domain is 0, position of axis is 1)
*/
void CGridTransformationSelector::initializeScalarAlgorithms(int scalarPositionInGrid)
TRY
{
  std::vector<CScalar*> scalarListDestP = gridDestination_->getScalars();
  std::vector<CScalar*> scalarListSrcP = gridSource_->getScalars();
  if (!scalarListDestP.empty())
  {
    int scalarDstPos = -1, scalarSrcPos = -1;
    if (0 < elementPositionInGridDst2ScalarPosition_.count(scalarPositionInGrid))
      scalarDstPos = elementPositionInGridDst2ScalarPosition_[scalarPositionInGrid];
    if (0 < elementPositionInGridSrc2ScalarPosition_.count(scalarPositionInGrid))
      scalarSrcPos = elementPositionInGridSrc2ScalarPosition_[scalarPositionInGrid];

    // If source and destination grid share the same scalar
    if ((-1 != scalarDstPos) && (-1 != scalarSrcPos)  && !isSameGrid_ &&
        ((scalarListDestP[scalarDstPos] == scalarListSrcP[scalarSrcPos]) ||
         (scalarListDestP[scalarDstPos]->isEqual(scalarListSrcP[scalarSrcPos])))) return;

    if (scalarListDestP[scalarDstPos]->hasTransformation())
    {
      CScalar::TransMapTypes trans = scalarListDestP[scalarDstPos]->getAllTransformations();
      CScalar::TransMapTypes::const_iterator itb = trans.begin(), it,
                                           ite = trans.end();
      int transformationOrder = 0;
      for (it = itb; it != ite; ++it)
      {
        listAlgos_.push_back(std::make_pair(scalarPositionInGrid, std::make_pair(it->first, std::make_pair(transformationOrder,0))));        
        ++transformationOrder;
        std::vector<StdString> auxInput = (it->second)->checkAuxInputs();
        for (int idx = 0; idx < auxInput.size(); ++idx) auxInputs_.push_back(auxInput[idx]);
      }
    }
  }
}
CATCH

/*!
  Initialize the algorithms corresponding to transformation info contained in each axis.
If an axis has transformations, these transformations will be represented in form of vector of CTransformation pointers
In general, each axis can have several transformations performed on itself. However, should they be done seperately or combinely (of course in order)?
For now, one approach is to do these combinely but maybe this needs changing.
\param [in] axisPositionInGrid position of an axis in grid. (for example: a grid with one domain and one axis, position of domain is 1, position of axis is 2)
*/
void CGridTransformationSelector::initializeAxisAlgorithms(int axisPositionInGrid)
TRY
{
  std::vector<CAxis*> axisListDestP = gridDestination_->getAxis();
  std::vector<CAxis*> axisListSrcP = gridSource_->getAxis();
  if (!axisListDestP.empty())
  {
    int axisDstPos = -1, axisSrcPos = -1;
    if (0 < elementPositionInGridDst2AxisPosition_.count(axisPositionInGrid))
      axisDstPos = elementPositionInGridDst2AxisPosition_[axisPositionInGrid];
    if (0 < elementPositionInGridSrc2AxisPosition_.count(axisPositionInGrid))
      axisSrcPos = elementPositionInGridSrc2AxisPosition_[axisPositionInGrid];

    // If source and destination grid share the same axis
    if ((-1 != axisDstPos) && (-1 != axisSrcPos) && !isSameGrid_ &&
        ((axisListDestP[axisDstPos] == axisListSrcP[axisSrcPos]) ||
         (axisListDestP[axisDstPos]->isEqual(axisListSrcP[axisSrcPos]))) ) return;

    if (axisListDestP[axisDstPos]->hasTransformation())
    {
      CAxis::TransMapTypes trans = axisListDestP[axisDstPos]->getAllTransformations();
      CAxis::TransMapTypes::const_iterator itb = trans.begin(), it,
                                           ite = trans.end();
      int transformationOrder = 0;
      for (it = itb; it != ite; ++it)
      {
        listAlgos_.push_back(std::make_pair(axisPositionInGrid, std::make_pair(it->first, std::make_pair(transformationOrder,1))));        
        ++transformationOrder;
        std::vector<StdString> auxInput = (it->second)->checkAuxInputs();
        for (int idx = 0; idx < auxInput.size(); ++idx) auxInputs_.push_back(auxInput[idx]);
      }
    }
  }
}
CATCH

/*!
  Initialize the algorithms corresponding to transformation info contained in each domain.
If a domain has transformations, they will be represented in form of vector of CTransformation pointers
In general, each domain can have several transformations performed on itself.
\param [in] domPositionInGrid position of a domain in grid. (for example: a grid with one domain and one axis, position of domain is 1, position of axis is 2)
*/
void CGridTransformationSelector::initializeDomainAlgorithms(int domPositionInGrid)
TRY
{
  std::vector<CDomain*> domListDestP = gridDestination_->getDomains();
  std::vector<CDomain*> domListSrcP = gridSource_->getDomains();
  if (!domListDestP.empty())
  {
    int domDstPos = -1, domSrcPos = -1;
    if (0 < elementPositionInGridDst2DomainPosition_.count(domPositionInGrid))
      domDstPos = elementPositionInGridDst2DomainPosition_[domPositionInGrid];
    if (0 < elementPositionInGridSrc2DomainPosition_.count(domPositionInGrid))
      domSrcPos = elementPositionInGridSrc2DomainPosition_[domPositionInGrid];

    // If source and destination grid share the same domain
    if ((-1 != domDstPos) && (-1 != domSrcPos) && !isSameGrid_ &&
        ((domListDestP[domDstPos] == domListSrcP[domSrcPos]) ||
         (domListDestP[domDstPos]->isEqual(domListSrcP[domSrcPos])))) return;

    if (domListDestP[domDstPos]->hasTransformation())
    {
      CDomain::TransMapTypes trans = domListDestP[domDstPos]->getAllTransformations();
      CDomain::TransMapTypes::const_iterator itb = trans.begin(), it,
                                             ite = trans.end();
      int transformationOrder = 0;
      for (it = itb; it != ite; ++it)
      {
        listAlgos_.push_back(std::make_pair(domPositionInGrid, std::make_pair(it->first, std::make_pair(transformationOrder,2))));        
        ++transformationOrder;
        std::vector<StdString> auxInput = (it->second)->checkAuxInputs();
        for (int idx = 0; idx < auxInput.size(); ++idx) auxInputs_.push_back(auxInput[idx]);
      }
    }
  }
}
CATCH

/*!
  Select algorithm correspoding to its transformation type and its position in each element
  \param [in] elementPositionInGrid position of element in grid. e.g: a grid has 1 domain and 1 axis, then position of domain is 1 (because it contains 2 basic elements)
                                             and position of axis is 2
  \param [in] transType transformation type, for now we have Zoom_axis, inverse_axis
  \param [in] transformationOrder position of the transformation in an element (an element can have several transformation)
  \param [in] algoType flag to specify type of algorithm (2 for domain, 1 for axis and 0 for scalar) 
*/
void CGridTransformationSelector::selectAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder, int algoType)
TRY
{
  updateElementPosition();
  switch (algoType)
  {
  case 0:
    selectScalarAlgo(elementPositionInGrid, transType, transformationOrder);
    break;
  case 1:
    selectAxisAlgo(elementPositionInGrid, transType, transformationOrder);
    break;
  case 2:
    selectDomainAlgo(elementPositionInGrid, transType, transformationOrder);
    break;
  default:
    break;
  }
}
CATCH

bool CGridTransformationSelector::isSpecialTransformation(ETranformationType transType)
TRY
{
  bool res = false;
  switch (transType)
  {
    case TRANS_GENERATE_RECTILINEAR_DOMAIN:
     res = true;
     break;
    default:
     break;
  }

  return res;
}
CATCH

}
