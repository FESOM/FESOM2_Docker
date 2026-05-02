/*!
   \brief Algorithm for reordering domain.
 */
#ifndef __XIOS_DOMAIN_ALGORITHM_REORDER_HPP__
#define __XIOS_DOMAIN_ALGORITHM_REORDER_HPP__

#include "domain_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {

class CDomain;
class CReorderDomain;

/*!
  \class CDomainAlgorithmReorder
  Reordering data on domain
*/
class CDomainAlgorithmReorder : public CDomainAlgorithmTransformation
{
public:
  CDomainAlgorithmReorder(CDomain* domainDestination, CDomain* domainSource, CReorderDomain* reorderDomain);

  virtual ~CDomainAlgorithmReorder() {}

  static bool registerTrans();

  virtual StdString getName() {return "reorder_domain";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);


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
#endif // __XIOS_DOMAIN_ALGORITHM_REORDER_HPP__
