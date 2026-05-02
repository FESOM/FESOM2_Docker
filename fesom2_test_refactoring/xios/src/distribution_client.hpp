/*!
   \file distribution_client.hpp
   \author Ha NGUYEN
   \since 13 Jan 2015
   \date 09 Mars 2015

   \brief Index distribution on client side.
 */
#ifndef __XIOS_DISTRIBUTIONCLIENT_HPP__
#define __XIOS_DISTRIBUTIONCLIENT_HPP__

#include <distribution.hpp>
#include "axis.hpp"
#include "domain.hpp"
#include "grid.hpp"

namespace xios {

class CGrid;
class CDomain;
class CAxis;
class CScalar;

/*!
  \class CDistributionClient
  This class bases on the knowledge of distribution on client side (decided by users)
to calculate the global index of its local data.
*/
class CDistributionClient : public CDistribution
{
public:
  typedef CDistribution::GlobalLocalMap GlobalLocalDataMap;

  public:
    /** Default constructor */
    CDistributionClient(int rank, CGrid* grid, bool isTiled = false);

    void createGlobalIndexSendToServer();

    /** Default destructor */
    virtual ~CDistributionClient();

    virtual const std::vector<int>& getLocalDataIndexOnClient();
    GlobalLocalDataMap& getGlobalLocalDataSendToServer();
    GlobalLocalDataMap& getGlobalDataIndexOnClient();
    const std::vector<bool>& getLocalMaskIndexOnClient();
    const std::vector<int>& getLocalMaskedDataIndexOnClient();

    std::vector<int> getNGlob() { return nGlob_; }
    std::vector<int> getDataNIndex() { return dataNIndex_; }

    bool isDataDistributed() { return isDataDistributed_; }

    static int getDomainIndex(const int& dataIIndex, const int& dataJIndex,
                                     const int& dataIBegin, const int& dataJBegin,
                                     const int& dataDim, const int& ni, int& j);
    static int getAxisIndex(const int& dataIndex, const int& dataBegin, const int& ni);

    void partialClear(void) ;  //! clear heavy sized attibutes

  protected:
    void createGlobalIndex();
    void readDistributionInfo(CGrid* grid, bool isTiled);
    void readDistributionInfo(const std::vector<CDomain*>& domList,
                              const std::vector<CAxis*>& axisList,
                              const std::vector<CScalar*>& scalarList,
                              const CArray<int,1>& axisDomainOrder,
                              bool isTiled);
  private:
    //! Create local index of a domain
    void createLocalDomainDataIndex();

    //! Create local index of an axis
    void createLocalAxisDataIndex();

    //! Create local index of a scalar
    void createLocalScalarDataIndex();

    template<int N>
    void readGridMaskInfo(const CArray<bool,N>& gridMask);

  private:
    //!< LocalData index on client
    GlobalLocalDataMap globalLocalDataSendToServerMap_;
    GlobalLocalDataMap globalDataIndex_;

    /*! Array holding masked data indexes.
     * It includes:
     *  masking on data (data_i/j_index or data_ni/nj and data_ibegin)
     *  masking on grid elements (domains, axes or scalars)
     * It DOES NOT include grid mask.
     * The array size defines the data size entering the workflow. It is used by source filter of client or server1.
    */
    std::vector<int> localDataIndex_;

    /*! Array holding grid mask. If grid mask is not defined, its size is zero.
     * It is used by source filter of client for replacing unmasked data by NaN.
    */
    std::vector<bool> localMaskIndex_;

    std::vector<int> localMaskedDataIndex_;

  private:
    /*! Domains and axis are considered elements.
     * A grid composed of 1 domain and 1 axis has 2 elements */
    int numElement_;
    CArray<int,1> axisDomainOrder_; //!< Order of axis and domain of a grid

    std::vector<int> nLocal_; //!< Local size of each dimension (ni, nj, etc, ...)
    std::vector<int> nGlob_; //!< Global size of each dimension (e.x: ni_glo, nj_glo, etc, ...)
    std::vector<int> nBeginLocal_;//!< Begin index of each dimension (e.x: for domain, it's always 0, for axis, it's zoom_begin, ...)
    std::vector<int> nBeginGlobal_; //!< Begin index of each dimension (e.x: ibegin, jbegin, ...)

    // Data_n_index of domain or axis (For now, axis uses its size as data_n_index
    std::vector<int> dataNIndex_; //!< Data_n_index in case of domain
    std::vector<int> dataDims_; //!< Data_dim, domain can have data_dim == 1 or 2
    std::vector<int> dataBegin_; //!< Data begin (data_ibegin, data_jbegin, etc)
    std::vector<CArray<int,1> > dataIndex_; //!< Data index
    std::vector<CArray<int,1> > infoIndex_; //!< i_index, j_index

    std::vector<int> indexMap_; //!< Mapping element index to dimension index
    std::vector<CArray<int,1> > elementLocalIndex_;  //!< Local index of each element
    std::vector<CArray<size_t,1> > elementGlobalIndex_; //!< Global index of each element
    std::vector<CArray<bool,1> > elementIndexData_; //!< // The correct index of a domain has true value, the ghost one has false value
    std::vector<size_t> elementNLocal_;
    std::vector<size_t> elementNGlobal_;

    //!< (Only for grid with one axis or scalar)Flag to determine whether data is distributed or not
    bool isDataDistributed_;
    int axisNum_;
    int domainNum_;
    bool isComputed_;

  private:
    // Just suppose that grid mask has 3 dimension. Need change
    CArray<bool,1> gridMask_; //!< Mask of grid

  private:
    CDistributionClient(const CDistributionClient& distClient); //! Not implement
};

/*!
  A grid can have multiple dimension, so can its mask in the form of multi-dimension array.
It's not a good idea to store all multi-dimension arrays corresponding to each mask.
One of the ways is to convert this array into 1-dimension one and every process is taken place on it.
  \param [in] multi-dimension array grid mask
*/
template<int N>
void CDistributionClient::readGridMaskInfo(const CArray<bool,N>& gridMask)
{
  int dim = gridMask.dimensions();
  std::vector<int> dimensionSizes(dim);
  for (int i = 0; i < dim; ++i) dimensionSizes[i] = gridMask.extent(i);

  std::vector<int> idxLoop(dim,0);
  int ssize = gridMask.numElements(), idx = 0;
  gridMask_.resize(ssize);
  while (idx < ssize)
  {
    for (int i = 0; i < dim-1; ++i)
    {
      if (idxLoop[i] == dimensionSizes[i])
      {
        idxLoop[i] = 0;
        ++idxLoop[i+1];
      }
    }

    int maskIndex = idxLoop[0];
    int mulDim = 1;
    for (int k = 1; k < dim; ++k)
    {
      mulDim *= dimensionSizes[k-1];
      maskIndex += idxLoop[k]*mulDim;
    }
    gridMask_(maskIndex) = *(gridMask.dataFirst()+maskIndex);

    ++idxLoop[0];
    ++idx;
  }
}

} // namespace xios
#endif // __XIOS_DISTRIBUTIONCLIENT_HPP__
