/*!
   \file grid_transformation.hpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 26 Aug 2015

   \brief Interface for all transformations.
 */
#ifndef __XIOS_GRID_TRANSFORMATION_HPP__
#define __XIOS_GRID_TRANSFORMATION_HPP__

#include <map>
#include <vector>
#include "generic_algorithm_transformation.hpp"
#include "transformation_enum.hpp"
#include "duration.hpp"
#include "grid_transformation_selector.hpp"

namespace xios {

class CGrid;

/*!
  \class CGridTransformation
  This class is an interface for all transformations to interact with the rest of XIOS.
The class, firstly, tries to get all information relating to requested transformations by retrieving directly from grid.
Secondly, with all these information, all necessary transformations will be created by generic class \class CGenericAlgorithmTransformation.
Then this class accomplishes the transformations by exchanging information among clients (e.g: some index need retrieving index from other clients),
For each transformation, a new temporary grid source is created.
For a consequential transformations (e.g: inversing -> zoom -> inversing -> ...),
the grid destination of current transformation will be grid source of the next transformation
*/
class CGridTransformation : public CGridTransformationSelector
{
public:
  typedef std::map<int, CArray<int,1> > SendingIndexGridSourceMap;
  typedef std::map<int,std::vector<std::pair<int,double> > > RecvIndexGridDestinationMap;
  typedef CGenericAlgorithmTransformation::SourceDestinationIndexMap SourceDestinationIndexMap;
  typedef CGenericAlgorithmTransformation::AlgoTransType AlgoTransType;

public:
  /** Default constructor */
  CGridTransformation(CGrid* destination, CGrid* source);
  ~CGridTransformation();

  void computeAll(const std::vector<CArray<double,1>* >& dataAuxInput=std::vector<CArray<double,1>* >(), Time timeStamp = 0);

  const std::list<SendingIndexGridSourceMap>& getLocalIndexToSendFromGridSource() const;
  const std::list<RecvIndexGridDestinationMap>& getLocalIndexToReceiveOnGridDest() const;
  const std::list<size_t>& getNbLocalIndexToReceiveOnGridDest() const;

  CGrid* getGridSource() { return originalGridSource_; }
  CGrid* getGridDestination() { return gridDestination_; }

protected:
  void computeTransformation();

  virtual void selectScalarAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder);
  virtual void selectAxisAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder);
  virtual void selectDomainAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder);

  void setUpGridSource(int elementPositionInGrid);
  void setUpGridDestination(int elementPositionInGrid, ETranformationType);
  void computeTransformationMapping(const SourceDestinationIndexMap& globalIndexWeightFromSrcToDest);
  std::map<int,std::pair<int,int> > getElementPosition(CGrid* grid);

protected:
  //! The grid source of the first transformation (original grid source)
  CGrid* tmpGridDestination_;
  CGrid* originalGridSource_;
  std::vector<CGrid*> tempGridSrcs_, tempGridDests_;

protected:
  //! Mapping of (grid) global index representing transformation.
  std::map<size_t, std::set<size_t> > globaIndexMapFromDestToSource_;

  //! Local index of data to send from grid source
  std::list<SendingIndexGridSourceMap> localIndexToSendFromGridSource_;

  //! Local index of data to receive on grid destination
  std::list<RecvIndexGridDestinationMap> localIndexToReceiveOnGridDest_;

  //! Number of local index of data to receive on grid destination
  std::list<size_t> nbLocalIndexOnGridDest_;

  bool dynamicalTransformation_;
  std::set<Time> timeStamp_; //! Time stamps for auxillary inputs
};

}
#endif // __XIOS_GRID_TRANSFORMATION_HPP__
