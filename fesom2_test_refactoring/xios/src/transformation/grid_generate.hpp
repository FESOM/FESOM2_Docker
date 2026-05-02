/*!
   \file grid_generate.hpp
   \author Ha NGUYEN
   \since 28 Aug 2015
   \date 28 Aug 2015

   \brief A special transformation to generate a grid.
 */
#ifndef __XIOS_GRID_GENERATE_HPP__
#define __XIOS_GRID_GENERATE_HPP__

#include "xios_spl.hpp"
#include "transformation_enum.hpp"
#include "grid_transformation_selector.hpp"

namespace xios {

class CGrid;

/*!
  \class CGridGenerate
  This class creates a grid from scratch, e.g: only global dimension of grid and its type are provided,
then the generated grid plays the destination in a transformation. Not only some attributes of grid and its subcomponents are filled in
automatically but it also have a distribution which might be different from one of grid source.
This class only plays a role of interface between XIOS and specific algorithm of auto filling-in and auto distributing on sub-component
*/
class CGridGenerate : public CGridTransformationSelector
{
public:
  /** Default constructor */
  CGridGenerate(CGrid* destination, CGrid* source = 0);
  ~CGridGenerate();

  void completeGrid();

protected:
  virtual void selectScalarAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder);
  virtual void selectAxisAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder);
  virtual void selectDomainAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder);
};

}
#endif // __XIOS_GRID_GENERATE_HPP__
