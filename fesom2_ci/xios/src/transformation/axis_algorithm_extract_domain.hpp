/*!
   \file axis_algorithm_reduce_domain.hpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Algorithm for reduce an axis to a axis
 */
#ifndef __XIOS_AXIS_ALGORITHM_EXTRACT_DOMAIN_HPP__
#define __XIOS_AXIS_ALGORITHM_EXTRACT_DOMAIN_HPP__

#include "axis_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CAxis;
class CDomain;
class CExtractDomainToAxis;
class CReductionAlgorithm;


/*!
  \class CAxisAlgorithmExtractDomain
  Extract a domain to an axis
*/
class CAxisAlgorithmExtractDomain : public CAxisAlgorithmTransformation
{
public:
  CAxisAlgorithmExtractDomain(CAxis* axisDestination, CDomain* domainSource, CExtractDomainToAxis* algo);

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);

  virtual ~CAxisAlgorithmExtractDomain();

  static bool registerTrans();

  virtual StdString getName() {return "extract_domain";}

protected:
  enum ExtractDirection {
    undefined = 0,
    iDir = 1,
    jDir = 2
  };

  ExtractDirection dir_;
  int pos_; //! Position to extract
protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

protected:
  CReductionAlgorithm* reduction_;

private:
  static CGenericAlgorithmTransformation* create(CGrid* gridDst, CGrid* gridSrc,
                                                CTransformation<CAxis>* transformation,
                                                int elementPositionInGrid,
                                                std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                std::map<int, int>& elementPositionInGridDst2DomainPosition);
};

}
#endif // __XIOS_AXIS_ALGORITHM_EXTRACT_DOMAIN_HPP__
