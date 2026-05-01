/*!
   \file scalar_algorithm_reduce_domain.cpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for reduce a domain to a scalar
 */
#include "scalar_algorithm_reduce_domain.hpp"
#include "domain.hpp"
#include "scalar.hpp"
#include "reduce_domain_to_scalar.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"

#include "reduction.hpp"

namespace xios {
CGenericAlgorithmTransformation* CScalarAlgorithmReduceDomain::create(CGrid* gridDst, CGrid* gridSrc,
                                                                     CTransformation<CScalar>* transformation,
                                                                     int elementPositionInGrid,
                                                                     std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                                     std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CScalar*> scalarListDestP = gridDst->getScalars();
  std::vector<CDomain*> domainListSrcP  = gridSrc->getDomains();

  CReduceDomainToScalar* reduceDomain = dynamic_cast<CReduceDomainToScalar*> (transformation);
  int scalarDstIndex = elementPositionInGridDst2ScalarPosition[elementPositionInGrid];
  int domainSrcIndex = elementPositionInGridSrc2DomainPosition[elementPositionInGrid];

  return (new CScalarAlgorithmReduceDomain(scalarListDestP[scalarDstIndex], domainListSrcP[domainSrcIndex], reduceDomain));
}
CATCH

bool CScalarAlgorithmReduceDomain::registerTrans()
TRY
{
  return CGridTransformationFactory<CScalar>::registerTransformation(TRANS_REDUCE_DOMAIN_TO_SCALAR, create);
}
CATCH

CScalarAlgorithmReduceDomain::CScalarAlgorithmReduceDomain(CScalar* scalarDestination, CDomain* domainSource, CReduceDomainToScalar* algo)
 : CScalarAlgorithmTransformation(scalarDestination, domainSource),
   reduction_(0)
TRY
{
  algo->checkValid(scalarDestination, domainSource);
  
  StdString op;
  switch (algo->operation)
  {
    case CReduceDomainToScalar::operation_attr::sum:
      op = "sum";
      break;
    case CReduceDomainToScalar::operation_attr::min:
      op = "min";
      break;
    case CReduceDomainToScalar::operation_attr::max:
      op = "max";
      break;
    case CReduceDomainToScalar::operation_attr::average:
      op = "average";
      break;
    default:
        ERROR("CScalarAlgorithmReduceDomain::CScalarAlgorithmReduceDomain(CDomain* domainDestination, CDomain* domainSource, CReduceDomainToScalar* algo)",
         << "Operation must be defined."
         << "Domain source " <<domainSource->getId() << std::endl
         << "Scalar destination " << scalarDestination->getId());

  }
  
  if (CReductionAlgorithm::ReductionOperations.end() == CReductionAlgorithm::ReductionOperations.find(op))
    ERROR("CScalarAlgorithmReduceDomain::CScalarAlgorithmReduceDomain(CDomain* domainDestination, CDomain* domainSource, CReduceDomainToScalar* algo)",
       << "Operation '" << op << "' not found. Please make sure to use a supported one"
       << "Domain source " <<domainSource->getId() << std::endl
       << "Scalar destination " << scalarDestination->getId());

  reduction_ = CReductionAlgorithm::createOperation(CReductionAlgorithm::ReductionOperations[op]);
  local = algo->local ;
}
CATCH

void CScalarAlgorithmReduceDomain::apply(const std::vector<std::pair<int,double> >& localIndex,
                                         const double* dataInput,
                                         CArray<double,1>& dataOut,
                                         std::vector<bool>& flagInitial,                     
                                         bool ignoreMissingValue, bool firstPass)
TRY
{
  reduction_->apply(localIndex, dataInput, dataOut, flagInitial, ignoreMissingValue, firstPass);
}
CATCH

void CScalarAlgorithmReduceDomain::updateData(CArray<double,1>& dataOut)
TRY
{
  reduction_->updateData(dataOut);
}
CATCH

CScalarAlgorithmReduceDomain::~CScalarAlgorithmReduceDomain()
TRY
{
  if (0 != reduction_) delete reduction_;
}
CATCH

void CScalarAlgorithmReduceDomain::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  this->transformationMapping_.resize(1);
  this->transformationWeight_.resize(1);

  TransformationIndexMap& transMap = this->transformationMapping_[0];
  TransformationWeightMap& transWeight = this->transformationWeight_[0];

  int ni_glo = domainSrc_->ni_glo ;
  int nj_glo = domainSrc_->nj_glo ;
  int nbDomainIdx ;
  
  if (local)
  {
      const CArray<int, 1>& i_index = domainSrc_-> i_index.getValue() ;
      const CArray<int, 1>& j_index = domainSrc_-> j_index.getValue() ;
      const CArray<bool,1>& localMask = domainSrc_-> localMask ;
      int nbDomainIdx = i_index.numElements();

      for (int idxDomain = 0; idxDomain < nbDomainIdx; ++idxDomain)
      {
        if (localMask(idxDomain))
        { 
          transMap[0].push_back(j_index(idxDomain)* ni_glo + i_index(idxDomain));
          transWeight[0].push_back(1.0) ;
        }
      }
  }
  else
  {  
    nbDomainIdx = ni_glo * nj_glo;
    transMap[0].resize(nbDomainIdx);
    transWeight[0].resize(nbDomainIdx, 1.0);
    for (int idxDomain = 0; idxDomain < nbDomainIdx; ++idxDomain) transMap[0][idxDomain] = idxDomain;    
  }
  
}
CATCH

}
