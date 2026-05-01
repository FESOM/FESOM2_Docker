/*!
   \file grid_transformation.hpp
   \author Ha NGUYEN
   \since 23 June 2016
   \date 23 June 2016

   \brief Helper class to select different transformations.
 */
#ifndef __XIOS_GRID_TRANSFORMATION_SELECTOR_HPP__
#define __XIOS_GRID_TRANSFORMATION_SELECTOR_HPP__

#include <map>
#include <vector>
#include "generic_algorithm_transformation.hpp"
#include "transformation_enum.hpp"
#include "duration.hpp"

namespace xios {

class CGrid;

/*!
  \class CGridTransformationSelector
  This class is a helper class to chose a algorithm (transformation) from the algorithm list of
specific grid.
*/
class CGridTransformationSelector
{
public:
  // Stupid C++98, should be replaced with tuple.
  // List of algorithm to process. Order of element in this list
  // <Position of element in grid, <transformationType, <transformation order, alogrithm type> > >
  typedef std::list<std::pair<int,std::pair<ETranformationType,std::pair<int,int> > > > ListAlgoType;
protected:
  enum AlgoType {
    scalarType = 0, axisType = 1, domainType = 2
  };

protected:
  enum TransformationType {
    special = 0, normal = 1
  };

public:
  /** Default constructor */
  CGridTransformationSelector(CGrid* destination, CGrid* source, TransformationType type = normal);
  virtual ~CGridTransformationSelector();

  ListAlgoType getAlgoList() const { return listAlgos_; }
  int getNbAlgo() { return nbNormalAlgos_; }
  const std::vector<StdString>& getAuxInputs() const { return auxInputs_; }
  const std::vector<CGenericAlgorithmTransformation*>& getAlgos() const { return algoTransformation_; }
  const std::map<int, int> getElementPositionInGridSrc2AxisPosition() const { return elementPositionInGridSrc2AxisPosition_ ;}
  const std::map<int, int> getElementPositionInGridSrc2DomainPosition() const { return elementPositionInGridSrc2DomainPosition_ ;}
  const std::map<int, int> getElementPositionInGridSrc2ScalarPosition() const { return elementPositionInGridSrc2ScalarPosition_ ;}
  const std::map<int, int> getElementPositionInGridDst2AxisPosition() const { return elementPositionInGridDst2AxisPosition_ ;}
  const std::map<int, int> getElementPositionInGridDst2DomainPosition() const { return elementPositionInGridDst2DomainPosition_ ;}
  const std::map<int, int> getElementPositionInGridDst2ScalarPosition() const { return elementPositionInGridDst2ScalarPosition_ ;}


protected:
  void updateElementPosition();
  void initializeAlgorithms();
  void initializeDomainAlgorithms(int domPositionInGrid);
  void initializeAxisAlgorithms(int axisPositionInGrid);
  void initializeScalarAlgorithms(int scalarPositionInGrid);
  void initializeTransformations(TransformationType type);
  void selectAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder, int algo);
  bool isSpecialTransformation(ETranformationType transType);
  void registerTransformations();

protected:
  virtual void selectScalarAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder) = 0;
  virtual void selectAxisAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder) = 0;
  virtual void selectDomainAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder) = 0;

protected:
  //! Grid source on transformation
  CGrid* gridSource_;

  //! Grid destination on transformation
  CGrid* gridDestination_;

  //! Grid source and grid destination it's the same
  bool isSameGrid_;

protected:
  //! List of algorithm types and their order
  ListAlgoType listAlgos_;

  //! Number of normal algorithm
  int nbNormalAlgos_;

  //! Number of special algorithms (such as generate_rectilinear_grid)
  int nbSpecialAlgos_;

  // true if domain algorithm and false if axis algorithm (can be replaced by tuple with listAlgos_
  std::vector<AlgoType> algoTypes_;

  // Mapping between position of an element in grid and its transformation (if any)
  std::vector<CGenericAlgorithmTransformation*> algoTransformation_;

  //! Position of scalar, axis and domain in grid
  std::map<int, int> elementPositionInGridSrc2AxisPosition_, elementPositionInGridSrc2DomainPosition_, elementPositionInGridSrc2ScalarPosition_;
  std::map<int, int> elementPositionInGridDst2AxisPosition_, elementPositionInGridDst2DomainPosition_, elementPositionInGridDst2ScalarPosition_;

  std::vector<StdString> auxInputs_;
  std::set<Time> timeStamp_; //! Time stamps for auxillary inputs
};

}
#endif // __XIOS_GRID_TRANSFORMATION_SELECTOR_HPP__
