/*!
   \file axis_algorithm_interpolate.cpp
   \author Ha NGUYEN
   \since 23 June 2015
   \date 02 Jul 2015

   \brief Algorithm for interpolation on an axis.
 */
#include "axis_algorithm_interpolate.hpp"
#include "axis.hpp"
#include "interpolate_axis.hpp"
#include <algorithm>
#include "context.hpp"
#include "context_client.hpp"
#include "utils.hpp"
#include "grid.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "distribution_client.hpp"
#include "timer.hpp"

namespace xios {
CGenericAlgorithmTransformation* CAxisAlgorithmInterpolate::create(CGrid* gridDst, CGrid* gridSrc,
                                                                   CTransformation<CAxis>* transformation,
                                                                   int elementPositionInGrid,
                                                                   std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                                   std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                                   std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                                   std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                                   std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                                   std::map<int, int>& elementPositionInGridDst2DomainPosition)
TRY
{
  std::vector<CAxis*> axisListDestP = gridDst->getAxis();
  std::vector<CAxis*> axisListSrcP  = gridSrc->getAxis();

  CInterpolateAxis* interpolateAxis = dynamic_cast<CInterpolateAxis*> (transformation);
  int axisDstIndex = elementPositionInGridDst2AxisPosition[elementPositionInGrid];
  int axisSrcIndex = elementPositionInGridSrc2AxisPosition[elementPositionInGrid];

  return (new CAxisAlgorithmInterpolate(axisListDestP[axisDstIndex], axisListSrcP[axisSrcIndex], interpolateAxis));
}
CATCH

bool CAxisAlgorithmInterpolate::registerTrans()
TRY
{
  return CGridTransformationFactory<CAxis>::registerTransformation(TRANS_INTERPOLATE_AXIS, create);
}
CATCH

CAxisAlgorithmInterpolate::CAxisAlgorithmInterpolate(CAxis* axisDestination, CAxis* axisSource, CInterpolateAxis* interpAxis)
: CAxisAlgorithmTransformation(axisDestination, axisSource), coordinate_(), coordinateDST_(),transPosition_()
TRY
{
  interpAxis->checkValid(axisSource);
  order_ = interpAxis->order.getValue();
  if (interpAxis->extrapolate.isEmpty()) extrapolate_=false ;
  else extrapolate_=interpAxis->extrapolate ;
  
  this->idAuxInputs_.clear();
  if (!interpAxis->coordinate.isEmpty())
  {
    coordinate_ = interpAxis->coordinate.getValue();
    this->idAuxInputs_.resize(1);
    this->idAuxInputs_[0] = coordinate_;
  }
  else if (!interpAxis->coordinate_src.isEmpty())
  {
    coordinate_ = interpAxis->coordinate_src.getValue();
    this->idAuxInputs_.resize(1);
    this->idAuxInputs_[0] = coordinate_;
  }
  if (!interpAxis->coordinate_dst.isEmpty())
  {
    coordinateDST_ = interpAxis->coordinate_dst.getValue();
    this->idAuxInputs_.resize(this->idAuxInputs_.size()+1);
    this->idAuxInputs_[this->idAuxInputs_.size()-1] = coordinateDST_;
  }
  

}
CATCH

/*!
  Compute the index mapping between axis on grid source and one on grid destination
*/
void CAxisAlgorithmInterpolate::computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  CTimer::get("CAxisAlgorithmInterpolate::computeIndexSourceMapping_").resume() ;
  
  CArray<bool,1>& axisMask = axisSrc_->mask;
  int srcSize  = axisSrc_->n_glo.getValue();
  std::vector<CArray<double,1> > vecAxisValue;

  // Fill in axis value from coordinate
  fillInAxisValue(vecAxisValue, dataAuxInputs);
  std::vector<double> valueSrc(srcSize);
  std::vector<double> recvBuff(srcSize);
  std::vector<int> indexVec(srcSize);

  for (int idx = 0; idx < vecAxisValue.size(); ++idx)
  {
    CArray<double,1>& axisValue = vecAxisValue[idx];
    retrieveAllAxisValue(axisValue, axisMask, recvBuff, indexVec);
    XIOSAlgorithms::sortWithIndex<double, CVectorStorage>(recvBuff, indexVec);
    for (int i = 0; i < srcSize; ++i) valueSrc[i] = recvBuff[indexVec[i]];
    computeInterpolantPoint(valueSrc, indexVec, dataAuxInputs, idx);
  }
  CTimer::get("CAxisAlgorithmInterpolate::computeIndexSourceMapping_").suspend() ;
}
CATCH

/*!
  Compute the interpolant points 
  Assume that we have all value of axis source, with these values, need to calculate weight (coeff) of Lagrange polynomial
  \param [in] axisValue all value of axis source
  \param [in] dataAuxInputs data for setting values of axis destination
  \param [in] tranPos position of axis on a domain
*/
void CAxisAlgorithmInterpolate::computeInterpolantPoint(const std::vector<double>& axisValue,
                                                        const std::vector<int>& indexVec,
                                                        const std::vector<CArray<double,1>* >& dataAuxInputs,
                                                        int transPos)
TRY
{
  std::vector<double>::const_iterator itb = axisValue.begin(), ite = axisValue.end();
  std::vector<double>::const_iterator itLowerBound, itUpperBound, it, iteRange, itfirst, itsecond;
  const double sfmax = NumTraits<double>::sfmax();
  const double precision = NumTraits<double>::dummy_precision();

  int ibegin = axisDest_->begin.getValue();
  CArray<double,1>& axisDestValue = axisDest_->value;
  int numValue = axisDestValue.numElements();
  if(!coordinateDST_.empty())
  {
    int dst_position_in_data = dataAuxInputs.size()-1;
    int nDomPoint = (*dataAuxInputs[dst_position_in_data]).numElements()/numValue ;
    for(int ii=0; ii<numValue; ii++)
    {
      axisDestValue(ii) = (*dataAuxInputs[dst_position_in_data])(ii*nDomPoint+transPos);
    }
  }
  
  std::map<int, std::vector<std::pair<int,double> > > interpolatingIndexValues;

  for (int idx = 0; idx < numValue; ++idx)
  {
    bool outOfRange = false;
    double destValue = axisDestValue(idx);
    if (destValue < *itb) outOfRange = true;

    itLowerBound = std::lower_bound(itb, ite, destValue);
    itUpperBound = std::upper_bound(itb, ite, destValue);
    if ((ite != itUpperBound) && (sfmax == *itUpperBound)) itUpperBound = ite;

    if ((ite == itLowerBound) || (ite == itUpperBound)) outOfRange = true;

    // We don't do extrapolation FOR NOW, maybe in the future
    if (!outOfRange)
    {
      if ((itLowerBound == itUpperBound) && (itb != itLowerBound)) --itLowerBound;
      double distanceToLower = destValue - *itLowerBound;
      double distanceToUpper = *itUpperBound - destValue;
      int order = (order_ + 1) - 2;
      bool down = (distanceToLower < distanceToUpper) ? true : false;
      for (int k = 0; k < order; ++k)
      {
        if ((itb != itLowerBound) && down)
        {
          --itLowerBound;
          distanceToLower = destValue - *itLowerBound;
          down = (distanceToLower < distanceToUpper) ? true : false;
          continue;
        }
        if ((ite != itUpperBound) && (sfmax != *itUpperBound))
        {
          ++itUpperBound;
          distanceToUpper = *itUpperBound - destValue;
          down = (distanceToLower < distanceToUpper) ? true : false;

        }
      }

      iteRange = (ite == itUpperBound) ? itUpperBound : itUpperBound + 1;
      itsecond = it = itLowerBound; ++itsecond;
      while (it < iteRange)
      {
        while ( (itsecond < ite) && ((*itsecond -*it) < precision) )
        { ++itsecond; ++it; }
        int index = std::distance(itb, it);
        interpolatingIndexValues[idx+ibegin].push_back(make_pair(indexVec[index],*it));
        ++it; ++itsecond;
      }

    }
    else
    {
      it=itb ;
      if (destValue <= *it) 
      {
        int numVal=0 ;
        while(numVal <= order_ && it!=ite)
        {
          if (*it != sfmax)
          { 
            interpolatingIndexValues[idx+ibegin].push_back(make_pair(indexVec[std::distance(itb, it)],*it));
            ++numVal ;
          }
          ++it ;
        }
      }
      
      it=ite ;
      --it ;
      if (destValue >= *it) 
      {
        int numVal=0 ;
        do
        {
          if (*it != sfmax)
          {
            interpolatingIndexValues[idx+ibegin].push_back(make_pair(indexVec[std::distance(itb, it)],*it));
            ++numVal ;
          }
          --it ;
        } while(it!=itb && numVal<=order_) ;
      }
    }
  }
  
  computeWeightedValueAndMapping(axisDestValue, interpolatingIndexValues, transPos);
}
CATCH



/*!
  Compute weight (coeff) of Lagrange's polynomial
  \param [in] interpolatingIndexValues the necessary axis value to calculate the coeffs
*/
void CAxisAlgorithmInterpolate::computeWeightedValueAndMapping(CArray<double,1>& axisDestValue, const std::map<int, std::vector<std::pair<int,double> > >& interpolatingIndexValues, int transPos)
TRY
{
  TransformationIndexMap& transMap = this->transformationMapping_[transPos];
  TransformationWeightMap& transWeight = this->transformationWeight_[transPos];
  std::map<int, std::vector<std::pair<int,double> > >::const_iterator itb = interpolatingIndexValues.begin(), it,
                                                                      ite = interpolatingIndexValues.end();
  int ibegin = axisDest_->begin.getValue();
  for (it = itb; it != ite; ++it)
  {
    int globalIndexDest = it->first;
//    double localValue = axisDest_->value(globalIndexDest - ibegin);
    double localValue = axisDestValue(globalIndexDest - ibegin);
    const std::vector<std::pair<int,double> >& interpVal = it->second;
    int interpSize = interpVal.size();
    transMap[globalIndexDest].resize(interpSize);
    transWeight[globalIndexDest].resize(interpSize);
    for (int idx = 0; idx < interpSize; ++idx)
    {
      int index = interpVal[idx].first;
      double weight = 1.0;

      for (int k = 0; k < interpSize; ++k)
      {
        if (k == idx) continue;
        weight *= (localValue - interpVal[k].second);
        weight /= (interpVal[idx].second - interpVal[k].second);
      }
      transMap[globalIndexDest][idx] = index;
      transWeight[globalIndexDest][idx] = weight;
      if (!transPosition_.empty())
      {
        (this->transformationPosition_[transPos])[globalIndexDest] = transPosition_[transPos];
      }
    }
  }
  if (!transPosition_.empty() && this->transformationPosition_[transPos].empty())
    (this->transformationPosition_[transPos])[0] = transPosition_[transPos];

}
CATCH

/*!
  Each client retrieves all values of an axis
  \param [in/out] recvBuff buffer for receiving values (already allocated)
  \param [in/out] indexVec mapping between values and global index of axis
*/
void CAxisAlgorithmInterpolate::retrieveAllAxisValue(const CArray<double,1>& axisValue, const CArray<bool,1>& axisMask,
                                                     std::vector<double>& recvBuff, std::vector<int>& indexVec)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client=context->client;
  int nbClient = client->clientSize;

  int srcSize  = axisSrc_->n_glo.getValue();
  int numValue = axisValue.numElements();


  if (srcSize == numValue)  // Only one client or axis not distributed
  {
    for (int idx = 0; idx < srcSize; ++idx)
    {
      if (axisMask(idx))
      {
        recvBuff[idx] = axisValue(idx);
        indexVec[idx] = idx;
      }
      else
      {
        recvBuff[idx] = NumTraits<double>::sfmax();
        indexVec[idx] = -1;
      }
    }
  }
  else // Axis distributed
  {
    double* sendValueBuff = new double [numValue];
    int* sendIndexBuff = new int [numValue];
    int* recvIndexBuff = new int [srcSize];

    int ibegin = axisSrc_->begin.getValue();
    for (int idx = 0; idx < numValue; ++idx)
    {
      if (axisMask(idx))
      {
        sendValueBuff[idx] = axisValue(idx);
        sendIndexBuff[idx] = idx + ibegin;
      }
      else
      {
        sendValueBuff[idx] = NumTraits<double>::sfmax();
        sendIndexBuff[idx] = -1;
      }
    }

    int* recvCount=new int[nbClient];
    MPI_Allgather(&numValue,1,MPI_INT,recvCount,1,MPI_INT,client->intraComm);

    int* displ=new int[nbClient];
    displ[0]=0 ;
    for(int n=1;n<nbClient;n++) displ[n]=displ[n-1]+recvCount[n-1];

    // Each client have enough global info of axis
    MPI_Allgatherv(sendIndexBuff,numValue,MPI_INT,recvIndexBuff,recvCount,displ,MPI_INT,client->intraComm);
    MPI_Allgatherv(sendValueBuff,numValue,MPI_DOUBLE,&(recvBuff[0]),recvCount,displ,MPI_DOUBLE,client->intraComm);

    for (int idx = 0; idx < srcSize; ++idx)
    {
      indexVec[idx] = recvIndexBuff[idx];
    }

    delete [] displ;
    delete [] recvCount;
    delete [] recvIndexBuff;
    delete [] sendIndexBuff;
    delete [] sendValueBuff;
  }
}
CATCH

/*!
  Fill in axis value dynamically from a field whose grid is composed of a domain and an axis
  \param [in/out] vecAxisValue vector axis value filled in from input field
*/
void CAxisAlgorithmInterpolate::fillInAxisValue(std::vector<CArray<double,1> >& vecAxisValue,
                                                const std::vector<CArray<double,1>* >& dataAuxInputs)
TRY
{
  bool has_src = !coordinate_.empty();
  bool has_dst = !coordinateDST_.empty();
  
  int nb_inputs=dataAuxInputs.size();
  
  
  if (!has_src && !has_dst)
  {
    vecAxisValue.resize(1);
    vecAxisValue[0].resize(axisSrc_->value.numElements());
    vecAxisValue[0] = axisSrc_->value;
    this->transformationMapping_.resize(1);
    this->transformationWeight_.resize(1);
  }
  else 
  {
    CField* field ;
    if (has_src) field = CField::get(coordinate_);
    else field = CField::get(coordinateDST_);
    CGrid* grid = field->grid;

    std::vector<CDomain*> domListP = grid->getDomains();
    std::vector<CAxis*> axisListP = grid->getAxis();
    if (domListP.empty() || axisListP.empty() || (1 < domListP.size()) || (1 < axisListP.size()))
      ERROR("CAxisAlgorithmInterpolate::fillInAxisValue(std::vector<CArray<double,1> >& vecAxisValue)",
             << "XIOS only supports dynamic interpolation with coordinate (field) associated with grid composed of a domain and an axis"
             << "Coordinate (field) id = " <<field->getId() << std::endl
             << "Associated grid id = " << grid->getId());

    CDomain* dom = domListP[0];
    size_t vecAxisValueSize = dom->i_index.numElements();
    size_t vecAxisValueSizeWithMask = 0;
    for (size_t idx = 0; idx < vecAxisValueSize; ++idx)
    {
      if (dom->domainMask(idx)) ++vecAxisValueSizeWithMask;
    }

    int niGlobDom = dom->ni_glo.getValue();
    vecAxisValue.resize(vecAxisValueSizeWithMask);
    if (transPosition_.empty())
    {
      size_t indexMask = 0;
      transPosition_.resize(vecAxisValueSizeWithMask);
      for (size_t idx = 0; idx < vecAxisValueSize; ++idx)
      {
        if (dom->domainMask(idx))
        {
          transPosition_[indexMask].resize(1);
          transPosition_[indexMask][0] = (dom->i_index)(idx) + niGlobDom * (dom->j_index)(idx);
          ++indexMask;
        }

      }
    }
    this->transformationMapping_.resize(vecAxisValueSizeWithMask);
    this->transformationWeight_.resize(vecAxisValueSizeWithMask);
    this->transformationPosition_.resize(vecAxisValueSizeWithMask);

    const CDistributionClient::GlobalLocalDataMap& globalLocalIndexSendToServer = grid->getDistributionClient()->getGlobalLocalDataSendToServer();
    CDistributionClient::GlobalLocalDataMap::const_iterator itIndex, iteIndex = globalLocalIndexSendToServer.end();
    size_t axisSrcSize = axisSrc_->index.numElements();
    std::vector<int> globalDimension = grid->getGlobalDimension();

    size_t indexMask = 0;
    for (size_t idx = 0; idx < vecAxisValueSize; ++idx)
    {
      if (dom->domainMask(idx))
      {
        size_t axisValueSize = 0;
        for (size_t jdx = 0; jdx < axisSrcSize; ++jdx)
        {
          size_t globalIndex = ((dom->i_index)(idx) + (dom->j_index)(idx)*globalDimension[0]) + (axisSrc_->index)(jdx)*globalDimension[0]*globalDimension[1];
          if (iteIndex != globalLocalIndexSendToServer.find(globalIndex))
          {
            ++axisValueSize;
          }
        }

        vecAxisValue[indexMask].resize(axisValueSize);
        axisValueSize = 0;
        for (size_t jdx = 0; jdx < axisSrcSize; ++jdx)
        {
          size_t globalIndex = ((dom->i_index)(idx) + (dom->j_index)(idx)*globalDimension[0]) + (axisSrc_->index)(jdx)*globalDimension[0]*globalDimension[1];
          itIndex = globalLocalIndexSendToServer.find(globalIndex);
          if (iteIndex != itIndex)
          {
            if (has_src)
            {
              vecAxisValue[indexMask](axisValueSize) = (*dataAuxInputs[0])(itIndex->second);
            }
            else
            {
              vecAxisValue[indexMask](axisValueSize) = axisSrc_-> value(axisValueSize) ;
            }
            ++axisValueSize;
          }
        }
        ++indexMask;
      }
    }
  }
}
CATCH

}
