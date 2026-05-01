/*!
   \file distribution_server.hpp
   \author Ha NGUYEN
   \since 13 Jan 2015
   \date 04 Feb 2015

   \brief Index distribution on server side.
 */

#ifndef __XIOS_DISTRIBUTION_SERVER_HPP__
#define __XIOS_DISTRIBUTION_SERVER_HPP__

#include "distribution.hpp"

namespace xios {

/*!
  \class CDistributionServer
  The class, for now, plays a role of computing local index for writing data on server
*/
class CDistributionServer : public CDistribution
{
  public:
    /** Default constructor */
    CDistributionServer(int rank, int dims, const CArray<size_t,1>& globalIndex = CArray<size_t,1>());
    CDistributionServer(int rank, const std::vector<int>& nBeginServer,
                        const std::vector<int>& nSizeServer, const std::vector<int>& nGlobal);
    CDistributionServer(int rank, const std::vector<int>& nBeginServer,
                        const std::vector<int>& nSizeServer,
                        const std::vector<int>& nBeginGlobal,
                        const std::vector<int>& nGlobal);

    CDistributionServer(int rank,
                        const std::vector<CArray<int,1> >& globalIndexElements,
                        const CArray<int,1>& elementOrder,
                        const std::vector<int>& nBeginServer,
                        const std::vector<int>& nSizeServer,
                        const std::vector<int>& nBeginGlobal,
                        const std::vector<int>& nGlobal);

    /** Default destructor */
    virtual ~CDistributionServer();

    const GlobalLocalMap& getGlobalLocalIndex() const { return globalLocalIndexMap_; }    
    int getGridSize() const;
    
    virtual void computeLocalIndex(CArray<size_t,1>& globalIndex);
    virtual void computeGlobalIndex(CArray<int,1>& indexes) const;
    virtual void partialClear(void); //! clear heavy sized attibutes

  protected:
    virtual void createGlobalIndex();
    void createGlobalIndex(const std::vector<CArray<int,1> >& globalIndexElements,
                           const CArray<int,1>& elementOrder);
    
  protected:
    GlobalLocalMap globalLocalIndexMap_;

  private:
    std::vector<int> nGlobal_;
    std::vector<int> nBeginGlobal_;
    std::vector<int> nSize_;
    std::vector<int> nBegin_;

};

} // namespace xios
#endif // __XIOS_DISTRIBUTION_SERVER_HPP__
