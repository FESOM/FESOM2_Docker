/*!
   \file axis_algorithm_zoom.hpp
   \brief Algorithm for zooming an axis.
 */
#ifndef __XIOS_AXIS_ALGORITHM_ZOOM_HPP__
#define __XIOS_AXIS_ALGORITHM_ZOOM_HPP__

#include "axis_algorithm_transformation.hpp"
#include "transformation.hpp"

namespace xios {
class CAxis;
class CZoomAxis;

/*!
  \class CAxisAlgorithmZoom
  Implementing zoom on axis
  A zoomed region can be considered as region that isn't masked.
  Only this zoomed region is zoomed to write on Netcdf.
*/
class CAxisAlgorithmZoom : public CAxisAlgorithmTransformation
{
public:
  CAxisAlgorithmZoom(CAxis* axisDestination, CAxis* axisSource, CZoomAxis* zoomAxis);

  virtual ~CAxisAlgorithmZoom() {}

  static bool registerTrans();

  virtual StdString getName() {return "zoom_axis";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

private:

private:
  //! Global zoom begin on axis
  StdSize zoomBegin_;

  //! Global zoom end on axis
  StdSize zoomEnd_;

  //! Global zoom size on axis
  StdSize zoomN_;

  std::vector<int> zoomIndex_;

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
#endif // __XIOS_AXIS_ALGORITHM_ZOOM_HPP__
