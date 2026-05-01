/*!
   \file grid_generate.cpp
   \author Ha NGUYEN
   \since 28 Aug 2015
   \date 23 June 2016

   \brief A special transformation to generate a grid.
 */
#include "grid_generate.hpp"
#include "grid.hpp"
#include "domain_algorithm_generate_rectilinear.hpp"
#include "generate_rectilinear_domain.hpp"

namespace xios {
CGridGenerate::CGridGenerate(CGrid* destination, CGrid* source)
  : CGridTransformationSelector(destination, source, special)
{
}

CGridGenerate::~CGridGenerate()
{
}

/*!
  Select algorithm of an axis correspoding to its transformation type and its position in each element
  \param [in] elementPositionInGrid position of element in grid. e.g: a grid has 1 domain and 1 axis, then position of domain is 1 (because it contains 2 basic elements)
                                             and position of axis is 2
  \param [in] transType transformation type, for now we have Zoom_axis, inverse_axis
  \param [in] transformationOrder position of the transformation in an element (an element can have several transformation)
*/
void CGridGenerate::selectScalarAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder)
TRY
{
  CGenericAlgorithmTransformation* algo = 0;
  algoTransformation_.push_back(algo);
}
CATCH

/*!
  Select algorithm of an axis correspoding to its transformation type and its position in each element
  \param [in] elementPositionInGrid position of element in grid. e.g: a grid has 1 domain and 1 axis, then position of domain is 1 (because it contains 2 basic elements)
                                             and position of axis is 2
  \param [in] transType transformation type, for now we have Zoom_axis, inverse_axis
  \param [in] transformationOrder position of the transformation in an element (an element can have several transformation)
*/
void CGridGenerate::selectAxisAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder)
TRY
{
  CGenericAlgorithmTransformation* algo = 0;
  algoTransformation_.push_back(algo);
}
CATCH

/*!
  Select algorithm of a domain correspoding to its transformation type and its position in each element
  \param [in] elementPositionInGrid position of element in grid. e.g: a grid has 1 domain and 1 axis, then position of domain is 1 (because it contains 2 basic elements)
                                             and position of axis is 2
  \param [in] transType transformation type, for now we have Zoom_axis, inverse_axis
  \param [in] transformationOrder position of the transformation in an element (an element can have several transformation)
*/
void CGridGenerate::selectDomainAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder)
TRY
{
  std::vector<CDomain*> domainListDestP = gridDestination_->getDomains();
  std::vector<CDomain*> domainListSrcP(domainListDestP.size());
  if (0 != gridSource_) domainListSrcP = gridSource_->getDomains();

  int domainIndex =  elementPositionInGridDst2DomainPosition_[elementPositionInGrid];
  CDomain::TransMapTypes trans = domainListDestP[domainIndex]->getAllTransformations();
  CDomain::TransMapTypes::const_iterator it = trans.begin();

  for (int i = 0; i < transformationOrder; ++i, ++it) {}  // Find the correct transformation

  CGenerateRectilinearDomain* genRectDomain = 0;
  CGenericAlgorithmTransformation* algo = 0;
  switch (transType)
  {
    case TRANS_GENERATE_RECTILINEAR_DOMAIN:
      if (0 == transformationOrder)
      {
        genRectDomain = dynamic_cast<CGenerateRectilinearDomain*> (it->second);
        algo = new CDomainAlgorithmGenerateRectilinear(domainListDestP[domainIndex], domainListSrcP[domainIndex],
                                                       gridDestination_, gridSource_, genRectDomain);
      }
      else
      {
         ERROR("CGridGenerate::selectDomainAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder)",
           << "Generate rectilinear domain must be the first transformation");
      }
      break;
    default:
      break;
  }
  algoTransformation_.push_back(algo);
}
CATCH

/*!

*/
void CGridGenerate::completeGrid()
TRY
{
  ListAlgoType::const_iterator itb = listAlgos_.begin(),
                               ite = listAlgos_.end(), it;
  CGenericAlgorithmTransformation* algo = 0;

  for (it = itb; it != ite; ++it)
  {
    int elementPositionInGrid = it->first;
    ETranformationType transType = (it->second).first;
    int transformationOrder = (it->second).second.first;
    int algoType = (it->second).second.second;

    // First of all, select an algorithm
    selectAlgo(elementPositionInGrid, transType, transformationOrder, algoType);
  }
}
CATCH

}
