/*!
   \file generic_algorithm_transformation.hpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 29 June 2015

   \brief Interface for all transformation algorithms.
 */
#ifndef __XIOS_GENERIC_ALGORITHM_TRANSFORMATION_HPP__
#define __XIOS_GENERIC_ALGORITHM_TRANSFORMATION_HPP__

#include <map>
#include <set>
#include "array_new.hpp"
#include "client_client_dht_template.hpp"

namespace xios {
  class CGrid;
  class CDomain;
  class CAxis;
  class CScalar;

  /*!
  \class CGenericAlgorithmTransformation
  This class defines the interface for all other inherited algorithms class
  */
class CGenericAlgorithmTransformation
{
public:
  enum AlgoTransType {
    ELEMENT_GENERATION = 0,
    ELEMENT_MODIFICATION_WITHOUT_DATA = 1,
    ELEMENT_MODIFICATION_WITH_DATA = 2,
    ELEMENT_NO_MODIFICATION_WITH_DATA = 3,
    ELEMENT_NO_MODIFICATION_WITHOUT_DATA = 4
  } ;

public:
  // Mapping between global index map of DESTINATION and its local index with pair of global index of SOURCE and weights
  typedef std::unordered_map<int, std::unordered_map<size_t, std::vector<std::pair<size_t,double> > > > SourceDestinationIndexMap;

protected:
  typedef std::unordered_map<size_t,int> GlobalLocalMap;
protected:
  typedef std::unordered_map<int, std::vector<int> > TransformationIndexMap;
  typedef std::unordered_map<int, std::vector<double> > TransformationWeightMap;
  typedef std::unordered_map<int, std::vector<int> > TransformationPositionMap;

public:
  CGenericAlgorithmTransformation();

  virtual ~CGenericAlgorithmTransformation() {}

  bool isDistributedTransformation(int elementPositionInGrid, CGrid* gridSrc, CGrid* gridDst) ;

  void computeGlobalSourceIndex(int elementPositionInGrid,
                               CGrid* gridSrc,
                               CGrid* gridDst,
                               SourceDestinationIndexMap& globaIndexWeightFromSrcToDst);

    /*!
    Apply a operation on local data.
    \param [in] localIndex vector contains local index of local data output and the corresponding weight
    \param [in] dataInput Pointer to the first element of data input array (in form of buffer)
    \param [in/out] dataOut Array contains local data
    \param [in/out] flagInitial vector of boolean to mark the local index already initialized. True means there is a need for initalization
    \param [in] ignoreMissingValue don't count missing value in operation if this flag is true
    \param [in] firstPass indicate if it is the first time the apply funtion is called for a same transformation, in order to make a clean initialization 
  */
  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);

  virtual StdString getName() {return "Generic Transformation";}

  /*!
   * Update whole dataOut (on necessary).
   * (Example:  Impose a weight, whose value is only known after being applied an operation, on dataOut)
   * \param [in/out] dataOut dataOut
   */
  virtual void updateData(CArray<double,1>& dataOut);

  std::vector<StdString> getIdAuxInputs();
  AlgoTransType type();
  /*!
  Compute global index mapping from one element of destination grid to the corresponding element of source grid
  */
  void computeIndexSourceMapping(const std::vector<CArray<double,1>* >& dataAuxInputs = std::vector<CArray<double,1>* >());
  void computeTransformationMappingNonDistributed(int elementPositionInGrid, CGrid* gridSrc, CGrid* gridDst,
                                                  vector<int>& localSrc, vector<int>& localDst, vector<double>& weight, int& nbLocalIndexOnGridDest);
  void nonDistributedrecursiveFunct(int currentPos, bool masked, int elementPositionInGrid,  vector< CArray<bool,1>* >& maskSrc, vector< CArray<bool,1>* >& maskDst,
                                    int& srcInd, int& srcIndCompressed, vector<int>& nIndexSrc,
                                    int& t, vector<vector<vector<pair<int,double> > > >& dstIndWeight, int currentInd,
                                    vector<int>& localSrc, vector<int>& localDst, vector<double>& weight) ;

protected:
  virtual void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >&) = 0;

  /*!
  Compute proc which contains global index of an element
    \param[in] globalElementIndex demanding global index of an element of source grid
    \param[in] elementType type of source element, 2: domain, 1: axis and 0: scalar
    \param[out] globalElementIndexOnProc Proc contains the demanding global index
  */
  virtual void computeExchangeGlobalIndex(const CArray<size_t,1>& globalElementIndex,
                                          int elementType,
                                          CClientClientDHTInt::Index2VectorInfoTypeMap& globalElementIndexOnProc) = 0;

protected:
  void computeGlobalGridIndexMapping(int elementPositionInGrid,
                                     const std::vector<int>& srcRank,
                                     std::unordered_map<int, std::vector<std::pair<int,double> > >& src2DstMap,
                                     CGrid* gridDst,
                                     CGrid* gridSrc,
                                     std::vector<std::unordered_map<int,std::vector<size_t> > >& globalElementIndexOnProc,
                                     SourceDestinationIndexMap& globaIndexWeightFromSrcToDst);

  void computeExchangeDomainIndex(CDomain* domainDst,
                                  CDomain* domainSrc,
                                  CArray<size_t,1>& destGlobalIndexPositionInGrid,
                                  std::unordered_map<int,std::vector<size_t> >& globalDomainIndexOnProc);

  void computeExchangeAxisIndex(CAxis* axisDst,
                                CAxis* axisSrc,
                                CArray<size_t,1>& destGlobalIndexPositionInGrid,
                                std::unordered_map<int,std::vector<size_t> >& globalAxisIndexOnProc);

  void computeExchangeScalarIndex(CScalar* scalarDst,
                                  CScalar* scalarSrc,
                                  CArray<size_t,1>& destGlobalIndexPositionInGrid,
                                  std::unordered_map<int,std::vector<size_t> >& globalScalarIndexOnProc);

  void computePositionElements(CGrid* dst, CGrid* src);

protected:
  //! indicate if the transformation is performed on a distributed element
  bool isDistributed_ ;
  //! indicate if the method  isDistributedTransformation has been called before
  bool isDistributedComputed_ ;
  
  //! Map between global index of destination element and source element
  std::vector<TransformationIndexMap> transformationMapping_;
  //! Weight corresponding of source to destination
  std::vector<TransformationWeightMap> transformationWeight_;
  //! Map of global index of destination element and corresponding global index of other elements in the same grid
  //! By default, one index of an element corresponds to all index of remaining element in the grid. So it's empty
  std::vector<TransformationPositionMap> transformationPosition_;

  //! Id of auxillary inputs which helps doing transformation dynamically
  std::vector<StdString> idAuxInputs_;
  AlgoTransType type_;

  std::set<StdSize> indexElementSrc_;

  std::vector<std::unordered_map<int,std::vector<size_t> > > globalElementIndexOnProc_;

  std::vector<int> procContainSrcElementIdx_;  // List of processes containing source index of transformed elements
//  std::set<int> procOfNonTransformedElements_; // Processes contain the source index of non-transformed elements
  std::set<int> commonProc_;
  std::vector< set<int> > procElementList_ ; // List of processes containing source index of elements

  CClientClientDHTInt::Index2VectorInfoTypeMap globalIndexOfTransformedElementOnProc_;
  
  bool computedProcSrcNonTransformedElement_; // Flag to indicate whether we computed proc containing non transformed elements

  std::map<int, int> elementPositionInGridSrc2AxisPosition_, elementPositionInGridSrc2DomainPosition_, elementPositionInGridSrc2ScalarPosition_;
  std::map<int, int> elementPositionInGridDst2AxisPosition_, elementPositionInGridDst2DomainPosition_, elementPositionInGridDst2ScalarPosition_;

  bool eliminateRedondantSrc_ ; // flag to indicate if the transformation must select only one global source point for all proc.
                               // In this case it will choose preferentially the current process 
};

}
#endif // __XIOS_GENERIC_ALGORITHM_TRANSFORMATION_HPP__
