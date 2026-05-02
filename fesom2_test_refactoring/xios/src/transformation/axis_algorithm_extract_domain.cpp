/*!
   \file axis_algorithm_reduce_domain.cpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for extract a domain to an axis
 */
#include "axis_algorithm_extract_domain.hpp"
#include "extract_domain_to_axis.hpp"
#include "axis.hpp"
#include "domain.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "reduction.hpp"

namespace xios {
CGenericAlgorithmTransformation* CAxisAlgorithmExtractDomain::create(CGrid* gridDst, CGrid* gridSrc,
                                                                     CTransformation<CAxis>* transformation,
                                                                     int elementPositionInGrid,
                                                                     std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CAxis*> axisListDestP = gridDst->getAxis();
  std::vector<CDomain*> domainListSrcP = gridSrc->getDomains();

  CExtractDomainToAxis* extractDomain = dynamic_cast<CExtractDomainToAxis*> (transformation);
  int axisDstIndex = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int domainSrcIndex = elementPositionInGridSrc2DomainPosition[elementPositionInGrid];

  return (new CAxisAlgorithmExtractDomain(axisListDestP[axisDstIndex], domainListSrcP[domainSrcIndex], extractDomain));
}
CATCH

//bool CAxisAlgorithmExtractDomain::_dummyRegistered = CAxisAlgorithmExtractDomain::registerTrans();
bool CAxisAlgorithmExtractDomain::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_EXTRACT_DOMAIN_TO_AXIS, create);
}
CATCH


CAxisAlgorithmExtractDomain::CAxisAlgorithmExtractDomain(CAxis* axisDestination, CDomain* domainSource, CExtractDomainToAxis* algo)
 : CAxisAlgorithmTransformation(axisDestination, domainSource), pos_(-1), reduction_(0)
TRY
{
  algo->checkValid(axisDestination, domainSource);
  StdString op = "extract";

  switch (algo->direction)
  {
    case CExtractDomainToAxis::direction_attr::jDir:
      dir_ = jDir;
      break;
    case CExtractDomainToAxis::direction_attr::iDir:
      dir_ = iDir;
      break;
    default:
      break;
  }

  pos_ = algo->position;
  reduction_ = CReductionAlgorithm::createOperation(CReductionAlgorithm::ReductionOperations[op]);
}
CATCH

void CAxisAlgorithmExtractDomain::apply(const std::vector<std::pair<int,double> >& localIndex,
                                        const double* dataInput,
                                        CArray<double,1>& dataOut,
                                        std::vector<bool>& flagInitial,                     
                                        bool ignoreMissingValue, bool firstPass)
TRY
{
  double defaultValue = std::numeric_limits<double>::quiet_NaN();
  if(firstPass) dataOut = defaultValue;
  reduction_->apply(localIndex, dataInput, dataOut, flagInitial, ignoreMissingValue, firstPass);
}
CATCH

CAxisAlgorithmExtractDomain::~CAxisAlgorithmExtractDomain()
TRY
{
  if (0 != reduction_) delete reduction_;
}
CATCH

void CAxisAlgorithmExtractDomain::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  CArray<int,1>& axisDstIndex = axisDest_->index;
  int ni_glo = domainSrc_->ni_glo, nj_glo = domainSrc_->nj_glo;
  if (jDir == dir_)
  {
    int nbAxisIdx = axisDstIndex.numElements();
    for (int idxAxis = 0; idxAxis < nbAxisIdx; ++idxAxis)
    {
      int globalAxisIdx = axisDstIndex(idxAxis);
      transMap[globalAxisIdx].resize(1);
      transWeight[globalAxisIdx].resize(1);
      transMap[globalAxisIdx][0] = globalAxisIdx * ni_glo + pos_;
      transWeight[globalAxisIdx][0] = 1.0;

    }
  }
  else if (iDir == dir_)
  {
    int nbAxisIdx = axisDstIndex.numElements();
    for (int idxAxis = 0; idxAxis < nbAxisIdx; ++idxAxis)
    {
      int globalAxisIdx = axisDstIndex(idxAxis);
      transMap[globalAxisIdx].resize(1);
      transWeight[globalAxisIdx].resize(1);
      transMap[globalAxisIdx][0] = globalAxisIdx + ni_glo * pos_;
      transWeight[globalAxisIdx][0] = 1.0;
    }
  }
  else
  {}
}
CATCH
}
