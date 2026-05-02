/*!
   \file server_distribution_description.hpp
   \author Ha NGUYEN
   \since 04 Jan 2015
   \date 11 Jan 2016

   \brief Description of index distribution on server(s).
 */

#ifndef __XIOS_SERVER_DISTRIBUTION_DESCRIPTION_HPP
#define __XIOS_SERVER_DISTRIBUTION_DESCRIPTION_HPP

#include "xios_spl.hpp"
#include "array_new.hpp"
#include <unordered_map>

namespace xios
{
/*!
   \class CServerDistributionDescription
   This class contains information that describe distribution of servers.
*/
class CServerDistributionDescription
{
  public:
    enum ServerDistributionType
    {
      BAND_DISTRIBUTION, PLAN_DISTRIBUTION, ROOT_DISTRIBUTION
    };

    /** Default constructor */
    CServerDistributionDescription(const std::vector<int>& globalDimensionSize,
                                   int nServer,
                                   ServerDistributionType serType=BAND_DISTRIBUTION);

    /** Default destructor */
    virtual ~CServerDistributionDescription();

    void computeServerDistribution(bool doComputeGlobalIndex = false, int positionDimensionDistributed = 1);
    std::vector<int> computeServerGlobalIndexInRange(const std::pair<size_t, size_t>& indexBeginEnd, int positionDimensionDistributed = 1);
    std::vector<int> computeServerGlobalByElement(std::vector<std::unordered_map<size_t,std::vector<int> > >& indexServerOnElement,
                                                  int rank,
                                                  int clientSize,
                                                  const CArray<int,1>& axisDomainOrder,
                                                  int positionDimensionDistributed = 1);

    std::vector<std::vector<int> > getServerIndexBegin() const;
    std::vector<std::vector<int> > getServerDimensionSizes() const;
    const std::vector<CArray<size_t,1> >& getGlobalIndex() const;
    const std::unordered_map<size_t,int>& getGlobalIndexRange() const;
    int getDimensionDistributed();

    static int defaultDistributedDimension(int gridDimension,                                   
                                           ServerDistributionType serType=BAND_DISTRIBUTION);

  protected:
    int computeBandDistribution(int nServer, int positionDimensionDistributed = 1);
    int computeRootDistribution(int nServer, int positionDimensionDistributed = 1);
    void computePlanDistribution(int nServer);
    void computeRangeProcIndex(int clientRank,
                               int clientSize,
                               int rangeProcSize,
                               int& rangeBegin,
                               int& rangeSize);

  private:
    std::vector<std::vector<int> > indexBegin_;     //!< Begin index of each dimension
    std::vector<std::vector<int> > dimensionSizes_; //!< Size of each dimension
    std::vector<int> nGlobal_; //!< Global size of each dimension

    //!< General case, index describes distribution of each server (rarely use)
    std::vector<CArray<size_t,1> > vecGlobalIndex_;

    //!< In case we need only global index of one server with specific rank
    std::unordered_map<size_t,int> globalIndex_;

    //!< Type of distribution on server side
    ServerDistributionType serverType_;

    //!< Number of server
    int nServer_;

    //!< Position of dimension distributed on server side (by default, the second dimension)
    int positionDimensionDistributed_;
};

} // namespace xios
#endif // __XIOS_SERVER_DISTRIBUTION_DESCRIPTION_HPP
