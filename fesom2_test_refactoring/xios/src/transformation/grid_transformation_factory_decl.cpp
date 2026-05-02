/*!
   \file grid_transformation.cpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 02 Jul 2015

   \brief Interface for all transformations.
 */
#include "grid_transformation_factory_impl.hpp"
#include "scalar.hpp"
#include "axis.hpp"
#include "domain.hpp"

namespace xios
{

template class CGridTransformationFactory<CScalar>;
template class CGridTransformationFactory<CAxis>;
template class CGridTransformationFactory<CDomain>;

}


