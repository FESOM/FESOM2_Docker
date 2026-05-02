
#ifndef __XIOS_DOMAIN_ALGORITHM_EXTRACT_HPP__
#define __XIOS_DOMAIN_ALGORITHM_EXTRACT_HPP__

#include "domain_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CDomain;
class CExtractDomain;

/*!
  \class CDomainAlgorithmExtract
  Implementing extract (alternative zoom) on domain
*/
class CDomainAlgorithmExtract : public CDomainAlgorithmTransformation
{
public:
  CDomainAlgorithmExtract(CDomain* domainDestination, CDomain* domainSource, CExtractDomain* extractDomain);

  virtual ~CDomainAlgorithmExtract() {}

  static bool registerTrans();

  virtual StdString getName() {return "extract_domain";}
protected:
  void updateDomainAttributes();
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

private:
  void updateExtract();

private:
  //! Global extract begin on domain
  int extractIBegin_;
  int extractJBegin_;

  //! Global extract end on domain
  int extractIEnd_;
  int extractJEnd_;

  //! Global extract size on domain
  int extractNi_;
  int extractNj_;

private:

  static CGenericAlgorithmTransformation* create(CGrid* gridDst, CGrid* gridSrc,
                                                CTransformation<CDomain>* transformation,
                                                int elementPositionInGrid,
                                                std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                std::map<int, int>& elementPositionInGridDst2DomainPosition);
};

}
#endif // __XIOS_DOMAIN_ALGORITHM_EXTRACT_HPP__
