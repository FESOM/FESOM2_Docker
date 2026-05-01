/*!
   \file grid_transformation.cpp
   \author Ha NGUYEN
   \since 14 May 2015
   \date 02 Jul 2015

   \brief Interface for all transformations.
 */
#include "grid_transformation.hpp"
#include "grid_transformation_factory_impl.hpp"
#include "algo_types.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "distribution_client.hpp"
#include "mpi_tag.hpp"
#include "grid.hpp"
#include <unordered_map>
#include "timer.hpp"

namespace xios {
CGridTransformation::CGridTransformation(CGrid* destination, CGrid* source)
 : CGridTransformationSelector(destination, source),
  tmpGridDestination_(destination), originalGridSource_(source),
  tempGridSrcs_(), tempGridDests_(),
  dynamicalTransformation_(false), timeStamp_()
{
}

CGridTransformation::~CGridTransformation()
{
}

/*!
  Select algorithm of a scalar corresponding to its transformation type and its position in each element
  \param [in] elementPositionInGrid position of element in grid. e.g: a grid has 1 domain and 1 axis, then position of domain is 0 and position of axis is 1
  \param [in] transType transformation type, for now we have
  \param [in] transformationOrder position of the transformation in an element (an element can have several transformation)
*/
void CGridTransformation::selectScalarAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder)
TRY
{
  std::vector<CScalar*> scaListDestP = gridDestination_->getScalars();
  int scalarDstIndex =  elementPositionInGridDst2ScalarPosition_[elementPositionInGrid];
  CScalar::TransMapTypes trans = scaListDestP[scalarDstIndex]->getAllTransformations();
  CScalar::TransMapTypes::const_iterator it = trans.begin();

  for (int i = 0; i < transformationOrder; ++i, ++it) {}  // Find the correct transformation
  CGenericAlgorithmTransformation* algo = 0;
  algo = CGridTransformationFactory<CScalar>::createTransformation(transType,
                                                                  gridDestination_,
                                                                  gridSource_,
                                                                  it->second,
                                                                  elementPositionInGrid,
                                                                  elementPositionInGridSrc2ScalarPosition_,
                                                                  elementPositionInGridSrc2AxisPosition_,
                                                                  elementPositionInGridSrc2DomainPosition_,
                                                                  elementPositionInGridDst2ScalarPosition_,
                                                                  elementPositionInGridDst2AxisPosition_,
                                                                  elementPositionInGridDst2DomainPosition_);
  algoTransformation_.push_back(algo);
}
CATCH

/*!
  Select algorithm of an axis corresponding to its transformation type and its position in each element
  \param [in] elementPositionInGrid position of element in grid. e.g: a grid has 1 domain and 1 axis, then position of domain is 0 and position of axis is 1
  \param [in] transType transformation type, for now we have zoom_axis, inverse_axis, interpolate_axis
  \param [in] transformationOrder position of the transformation in an element (an element can have several transformation)
*/
void CGridTransformation::selectAxisAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder)
TRY
{
  std::vector<CAxis*> axisListDestP = gridDestination_->getAxis();
  int axisDstIndex =  elementPositionInGridDst2AxisPosition_[elementPositionInGrid];
  CAxis::TransMapTypes trans = axisListDestP[axisDstIndex]->getAllTransformations();
  CAxis::TransMapTypes::const_iterator it = trans.begin();
  for (int i = 0; i < transformationOrder; ++i, ++it) {}  // Find the correct transformation

  CGenericAlgorithmTransformation* algo = 0;
  algo = CGridTransformationFactory<CAxis>::createTransformation(transType,
                                                                 gridDestination_,
                                                                 gridSource_,
                                                                 it->second,
                                                                 elementPositionInGrid,
                                                                 elementPositionInGridSrc2ScalarPosition_,
                                                                 elementPositionInGridSrc2AxisPosition_,
                                                                 elementPositionInGridSrc2DomainPosition_,
                                                                 elementPositionInGridDst2ScalarPosition_,
                                                                 elementPositionInGridDst2AxisPosition_,
                                                                 elementPositionInGridDst2DomainPosition_);
  algoTransformation_.push_back(algo);
}
CATCH

/*!
  Select algorithm of a domain corresponding to its transformation type and its position in each element
  \param [in] elementPositionInGrid position of element in grid. e.g: a grid has 1 domain and 1 axis, then position of domain is 0 and position of axis is 1
  \param [in] transType transformation type, for now we have zoom_domain, interpolate_domain
  \param [in] transformationOrder position of the transformation in an element (an element can have several transformation)
*/
void CGridTransformation::selectDomainAlgo(int elementPositionInGrid, ETranformationType transType, int transformationOrder)
TRY
{
  std::vector<CDomain*> domainListDestP = gridDestination_->getDomains();
  int domainIndex =  elementPositionInGridDst2DomainPosition_[elementPositionInGrid];
  CDomain::TransMapTypes trans = domainListDestP[domainIndex]->getAllTransformations();
  CDomain::TransMapTypes::const_iterator it = trans.begin();
  for (int i = 0; i < transformationOrder; ++i, ++it) {}  // Find the correct transformation  

  CGenericAlgorithmTransformation* algo = 0;
  algo = CGridTransformationFactory<CDomain>::createTransformation(transType,
                                                                   gridDestination_,
                                                                   gridSource_,
                                                                   it->second,
                                                                   elementPositionInGrid,
                                                                   elementPositionInGridSrc2ScalarPosition_,
                                                                   elementPositionInGridSrc2AxisPosition_,
                                                                   elementPositionInGridSrc2DomainPosition_,
                                                                   elementPositionInGridDst2ScalarPosition_,
                                                                   elementPositionInGridDst2AxisPosition_,
                                                                   elementPositionInGridDst2DomainPosition_);
  algoTransformation_.push_back(algo);
}
CATCH

/*!
  Find position of element in a grid as well as its type (domain, axis, scalar) and position in its own element list
  \return element position: map<int,<int,int> > corresponds to <element position in grid, <element type, element position in element list> >
*/
std::map<int,std::pair<int,int> > CGridTransformation::getElementPosition(CGrid* grid)
TRY
{
  std::vector<CScalar*> scalarListP = grid->getScalars(); 
  std::vector<CAxis*> axisListP = grid->getAxis();
  std::vector<CDomain*> domListP = grid->getDomains();  
  CArray<int,1> axisDomainOrder = grid->axis_domain_order;
  int scalarIndex = 0, axisIndex = 0, domainIndex = 0;
  int nbElement = axisDomainOrder.numElements(), elementDim;
  std::map<int,std::pair<int,int> > elementPosition;
  for (int idx = 0; idx < nbElement; ++idx)
  {
    elementDim = axisDomainOrder(idx);
    switch (elementDim)
    {
      case 2:
        elementPosition[idx] = std::make_pair(elementDim, domainIndex);
        ++domainIndex;
        break;
      case 1:
        elementPosition[idx] = std::make_pair(elementDim, axisIndex);
        ++axisIndex;
        break;
      case 0:
        elementPosition[idx] = std::make_pair(elementDim, scalarIndex);
        ++scalarIndex;
        break;
      default:
        break;        
    }
  }

  return elementPosition;  
}
CATCH

/*!
  If there are more than one transformation, a new temporary grid will be created and it will play the role of grid destination.
This new created one keeps a pointer to the real transformed element of grid destination and generate new copies of other elements from grid source.
  \param [in] elementPositionInGrid position of element in grid
  \param [in] transType transformation type
*/
void CGridTransformation::setUpGridDestination(int elementPositionInGrid, ETranformationType transType)
TRY
{
  if (isSpecialTransformation(transType)) return;

  if (!tempGridDests_.empty() && (getNbAlgo() == tempGridDests_.size()))
  {
    tempGridDests_.resize(0);
  }

  if (1 == getNbAlgo()) 
  {
    tmpGridDestination_ = gridDestination_;
    return;
  }

  std::vector<CScalar*> scalarListDestP = gridDestination_->getScalars();
  std::vector<CScalar*> scalarListSrcP = gridSource_->getScalars(), scalarDst;

  std::vector<CAxis*> axisListDestP = gridDestination_->getAxis();
  std::vector<CAxis*> axisListSrcP = gridSource_->getAxis(), axisDst;

  std::vector<CDomain*> domListDestP = gridDestination_->getDomains();
  std::vector<CDomain*> domListSrcP = gridSource_->getDomains(), domainDst;

  CArray<int,1> axisDomainOrderSrc = gridSource_->axis_domain_order;
  CArray<int,1> axisDomainOrderDst = gridDestination_->axis_domain_order;

  std::map<int,std::pair<int,int> > elementPositionSrc = getElementPosition(gridSource_);
  std::map<int,std::pair<int,int> > elementPositionDst = getElementPosition(gridDestination_);

  CArray<int,1> elementOrder(axisDomainOrderDst.numElements());
  for (int idx = 0; idx < axisDomainOrderDst.numElements(); ++idx)
  {
    if (elementPositionInGrid == idx)
    {
      int dimElementDst = elementPositionDst[idx].first;
      int elementIndex  = elementPositionDst[idx].second;
      switch (dimElementDst) 
      {
        case 2:
          domainDst.push_back(domListDestP[elementIndex]);
          break;
        case 1:
          axisDst.push_back(axisListDestP[elementIndex]);
          break;
        case 0:
          scalarDst.push_back(scalarListDestP[elementIndex]);
          break;
        default:
          break;
      }
      elementOrder(idx) = dimElementDst;
    }
    else
    {      
      int dimElementSrc = elementPositionSrc[idx].first;
      int elementIndex  = elementPositionSrc[idx].second;
      switch (dimElementSrc)
      {
        case 2:
          domainDst.push_back(domListSrcP[elementIndex]);
          break;
        case 1:
          axisDst.push_back(axisListSrcP[elementIndex]);
          break;
        case 0:
          scalarDst.push_back(scalarListSrcP[elementIndex]);
          break;
        default:
          break;
      }
      elementOrder(idx) = dimElementSrc;
    }
  }

  tmpGridDestination_ = CGrid::createGrid(domainDst, axisDst, scalarDst, elementOrder);  
  tempGridDests_.push_back(tmpGridDestination_);
}
CATCH

/*!
  Assign the current grid destination to the grid source in the new transformation.
The current grid destination plays the role of grid source in next transformation (if any).
Only element on which the transformation is performed is modified
  \param [in] elementPositionInGrid position of element in grid
  \param [in] transType transformation type
*/
void CGridTransformation::setUpGridSource(int elementPositionInGrid)
TRY
{
  if (!tempGridSrcs_.empty() && (getNbAlgo()-1) == tempGridSrcs_.size())
  {
    tempGridSrcs_.resize(0);
  }

  std::vector<CScalar*> scalarListDestP = tmpGridDestination_->getScalars();
  std::vector<CScalar*> scalarListSrcP = gridSource_->getScalars(), scalarSrc;

  std::vector<CAxis*> axisListDestP = tmpGridDestination_->getAxis();
  std::vector<CAxis*> axisListSrcP = gridSource_->getAxis(), axisSrc;

  std::vector<CDomain*> domListDestP = tmpGridDestination_->getDomains();
  std::vector<CDomain*> domListSrcP = gridSource_->getDomains(), domainSrc;

  CArray<int,1> axisDomainOrderSrc = gridSource_->axis_domain_order;
  CArray<int,1> axisDomainOrderDst = tmpGridDestination_->axis_domain_order;

  std::map<int,std::pair<int,int> > elementPositionSrc = getElementPosition(gridSource_);
  std::map<int,std::pair<int,int> > elementPositionDst = getElementPosition(tmpGridDestination_);

  for (int idx = 0; idx < axisDomainOrderDst.numElements(); ++idx)
  {   
    if (elementPositionInGrid == idx)
    {
      int dimElementDst = elementPositionDst[idx].first;
      int elementIndex  = elementPositionDst[idx].second;
      if (2 == dimElementDst)
      {
        CDomain* domain = CDomain::createDomain();
        domain->domain_ref.setValue(domListDestP[elementIndex]->getId());
        domain->solveRefInheritance(true);
        domain->checkAttributesOnClient();
        domainSrc.push_back(domain);
      }
      else if (1 == dimElementDst)
      {
        CAxis* axis = CAxis::createAxis();
        axis->axis_ref.setValue(axisListDestP[elementIndex]->getId());
        axis->solveRefInheritance(true);
        axis->checkAttributesOnClient();
        axisSrc.push_back(axis); 
      }
      else
      {
        CScalar* scalar = CScalar::createScalar();
        scalar->scalar_ref.setValue(scalarListDestP[elementIndex]->getId());
        scalar->solveRefInheritance(true);
        scalar->checkAttributesOnClient();
        scalarSrc.push_back(scalar);
      }
    }
    else
    {      
      int dimElementDst = elementPositionDst[idx].first;
      int elementIndex  = elementPositionDst[idx].second;
      switch (dimElementDst)
      {
        case 2:
          domainSrc.push_back(domListDestP[elementIndex]);
          break;
        case 1:
          axisSrc.push_back(axisListDestP[elementIndex]);
          break;
        case 0:
          scalarSrc.push_back(scalarListDestP[elementIndex]);
          break;
        default:
          break;
      }
    }
  }

  gridSource_ = CGrid::createGrid(domainSrc, axisSrc, scalarSrc, tmpGridDestination_->axis_domain_order);  

  tempGridSrcs_.push_back(gridSource_);
}
CATCH

/*!
  Perform all transformations
  For each transformation, there are some things to do:
  -) Chose the correct algorithm by transformation type and position of element
  -) Calculate the mapping of global index between the current grid source and grid destination
  -) Calculate the mapping of global index between current grid DESTINATION and grid SOURCE
  -) Make current grid destination become grid source in the next transformation
*/
void CGridTransformation::computeAll(const std::vector<CArray<double,1>* >& dataAuxInputs, Time timeStamp)
TRY
{
  if (nbNormalAlgos_ < 1) return;
  if (!auxInputs_.empty() && !dynamicalTransformation_) { dynamicalTransformation_ = true; return; }
  if (dynamicalTransformation_)
  {
    if (timeStamp_.insert(timeStamp).second)   //Reset map
    {
      std::list<SendingIndexGridSourceMap>().swap(localIndexToSendFromGridSource_);
      std::list<RecvIndexGridDestinationMap>().swap(localIndexToReceiveOnGridDest_);
      std::list<size_t>().swap(nbLocalIndexOnGridDest_);
    }
    else
      return;
  }

  CContext* context = CContext::getCurrent();
  CContextClient* client = context->client;

  ListAlgoType::const_iterator itb = listAlgos_.begin(),
                               ite = listAlgos_.end(), it;

  CGenericAlgorithmTransformation* algo = 0;
  int nbAgloTransformation = 0; // Only count for executed transformation. Generate domain is a special one, not executed in the list
  for (it = itb; it != ite; ++it)
  {
    int elementPositionInGrid = it->first;
    ETranformationType transType = (it->second).first;
    int transformationOrder = (it->second).second.first;
    int algoType = ((it->second).second.second); //algoTypes_[std::distance(itb, it)];
    SourceDestinationIndexMap globaIndexWeightFromSrcToDst;
    

    // Create a temporary grid destination which contains transformed element of grid destination and
    // non-transformed elements to grid source
    setUpGridDestination(elementPositionInGrid, transType);

    // First of all, select an algorithm
    if (!dynamicalTransformation_ || (algoTransformation_.size() < listAlgos_.size()))
    {
      selectAlgo(elementPositionInGrid, transType, transformationOrder, algoType);
      algo = algoTransformation_.back();
    }
    else
      algo = algoTransformation_[std::distance(itb, it)];

    if ((0 != algo) &&
        ((CGenericAlgorithmTransformation::ELEMENT_NO_MODIFICATION_WITH_DATA == algo->type()) ||
        (CGenericAlgorithmTransformation::ELEMENT_MODIFICATION_WITH_DATA == algo->type()))) // Only registered transformation can be executed
    {
      CTimer::get("computeIndexSourceMapping").resume() ;
      algo->computeIndexSourceMapping(dataAuxInputs);
      CTimer::get("computeIndexSourceMapping").suspend() ;
      
      // ComputeTransformation of global index of each element
      int elementPosition = it->first;
      bool nonDistributedActivated = CXios::getin<bool>("activate_non_distributed_transformation",false);
      
      if (nonDistributedActivated && !algo->isDistributedTransformation(elementPositionInGrid, gridSource_, tmpGridDestination_) )
      {
        vector<int> localSrc ;
        vector<int> localDst ;
        vector<double> weight ;
        int nbLocalIndexOnGridDest;
        CTimer::get("computeTransformationMappingNonDistributed").resume();  
        algo->computeTransformationMappingNonDistributed(elementPosition, gridSource_, tmpGridDestination_, 
                                                         localSrc, localDst, weight, nbLocalIndexOnGridDest) ;
        CTimer::get("computeTransformationMappingNonDistributed").suspend();  

        CTimer::get("computeTransformationMappingConvert").resume();  
        nbLocalIndexOnGridDest_.push_back(nbLocalIndexOnGridDest) ;
        int clientRank=client->clientRank ;
        {
          SendingIndexGridSourceMap tmp;
          localIndexToSendFromGridSource_.push_back(tmp) ;
          SendingIndexGridSourceMap& src=localIndexToSendFromGridSource_.back() ;
          CArray<int,1> arrayTmp ;
          src.insert( pair<int,CArray<int,1> >(clientRank,arrayTmp)) ;
          CArray<int,1>& array=src[clientRank] ;
          array.resize(localSrc.size()) ;
          for(int i=0;i< localSrc.size();++i) array(i)=localSrc[i]  ;    
        }
        {
          RecvIndexGridDestinationMap tmp;
          localIndexToReceiveOnGridDest_.push_back(tmp) ;
          RecvIndexGridDestinationMap& dst=localIndexToReceiveOnGridDest_.back() ;
          vector<pair<int,double> > vectTmp ;
          dst.insert( pair<int,vector<pair<int,double> >  >(clientRank,vectTmp)) ;
          vector<pair<int,double> >& vect=dst[clientRank] ;
          vect.resize(localDst.size()) ;
          for(int i=0;i< localDst.size();++i) vect[i]=pair<int,double>(localDst[i],weight[i])  ;      
        }
        CTimer::get("computeTransformationMappingConvert").suspend();  
      }
      else
      {
        CTimer::get("computeGlobalSourceIndex").resume();           
        algo->computeGlobalSourceIndex(elementPosition,
                                       gridSource_,
                                       tmpGridDestination_,
                                       globaIndexWeightFromSrcToDst);
                                     
        CTimer::get("computeGlobalSourceIndex").suspend();           
        CTimer::get("computeTransformationMapping").resume();     
        // Compute transformation of global indexes among grids
        computeTransformationMapping(globaIndexWeightFromSrcToDst);
        CTimer::get("computeTransformationMapping").suspend(); 
      } 
      if (1 < nbNormalAlgos_)
      {
        // Now grid destination becomes grid source in a new transformation
        if (nbAgloTransformation != (nbNormalAlgos_-1)) setUpGridSource(elementPositionInGrid);
      }
      ++nbAgloTransformation;
    }
  }
}
CATCH

/*!
  Compute exchange index between grid source and grid destination
  \param [in] globalIndexWeightFromDestToSource global index mapping between grid destination and grid source
*/
void CGridTransformation::computeTransformationMapping(const SourceDestinationIndexMap& globaIndexWeightFromSrcToDst)
TRY
{
  CContext* context = CContext::getCurrent();
  CContextClient* client = context->client;
  int nbClient = client->clientSize;
  int clientRank = client->clientRank;

  // Recalculate the distribution of grid destination
  CDistributionClient distributionClientDest(client->clientRank, tmpGridDestination_);
  CDistributionClient::GlobalLocalDataMap& globalLocalIndexGridDestSendToServer = distributionClientDest.getGlobalLocalDataSendToServer();

  // Update number of local index on each transformation
  size_t nbLocalIndex = globalLocalIndexGridDestSendToServer.size();
  nbLocalIndexOnGridDest_.push_back(nbLocalIndex);
//  localMaskOnGridDest_.push_back(std::vector<bool>());
//  std::vector<bool>& tmpMask = localMaskOnGridDest_.back();
//  tmpMask.resize(nbLocalIndex,false);

  // Find out number of index sent from grid source and number of index received on grid destination
  SourceDestinationIndexMap::const_iterator itbIndex = globaIndexWeightFromSrcToDst.begin(),
                                            iteIndex = globaIndexWeightFromSrcToDst.end(), itIndex;
  typedef std::unordered_map<size_t, std::vector<std::pair<size_t,double> > > SendIndexMap;
  std::map<int,int> sendRankSizeMap,recvRankSizeMap;
  int connectedClient = globaIndexWeightFromSrcToDst.size();
  int* recvCount=new int[nbClient];
  int* displ=new int[nbClient];
  int* sendRankBuff=new int[connectedClient];
  int* sendSizeBuff=new int[connectedClient];
  int n = 0;
  for (itIndex = itbIndex; itIndex != iteIndex; ++itIndex, ++n)
  {
    sendRankBuff[n] = itIndex->first;
    const SendIndexMap& sendIndexMap = itIndex->second;
    SendIndexMap::const_iterator itbSend = sendIndexMap.begin(), iteSend = sendIndexMap.end(), itSend;
    int sendSize = 0;
    for (itSend = itbSend; itSend != iteSend; ++itSend)
    {
      sendSize += itSend->second.size();
    }
    sendSizeBuff[n] = sendSize;
    sendRankSizeMap[itIndex->first] = sendSize;
  }
  MPI_Allgather(&connectedClient,1,MPI_INT,recvCount,1,MPI_INT,client->intraComm);

  displ[0]=0 ;
  for(int n=1;n<nbClient;n++) displ[n]=displ[n-1]+recvCount[n-1];
  int recvSize=displ[nbClient-1]+recvCount[nbClient-1];
  int* recvRankBuff=new int[recvSize];
  int* recvSizeBuff=new int[recvSize];
  MPI_Allgatherv(sendRankBuff,connectedClient,MPI_INT,recvRankBuff,recvCount,displ,MPI_INT,client->intraComm);
  MPI_Allgatherv(sendSizeBuff,connectedClient,MPI_INT,recvSizeBuff,recvCount,displ,MPI_INT,client->intraComm);
  for (int i = 0; i < nbClient; ++i)
  {
    int currentPos = displ[i];
    for (int j = 0; j < recvCount[i]; ++j)
      if (recvRankBuff[currentPos+j] == clientRank)
      {
        recvRankSizeMap[i] = recvSizeBuff[currentPos+j];
      }
  }

  // Sending global index of grid source to corresponding process as well as the corresponding mask
  std::vector<MPI_Request> requests;
  std::vector<MPI_Status> status;
  std::unordered_map<int, unsigned char* > recvMaskDst;
  std::unordered_map<int, unsigned long* > recvGlobalIndexSrc;
  for (std::map<int,int>::const_iterator itRecv = recvRankSizeMap.begin(); itRecv != recvRankSizeMap.end(); ++itRecv)
  {
    int recvRank = itRecv->first;
    int recvSize = itRecv->second;
    recvMaskDst[recvRank] = new unsigned char [recvSize];
    recvGlobalIndexSrc[recvRank] = new unsigned long [recvSize];

    requests.push_back(MPI_Request());
    MPI_Irecv(recvGlobalIndexSrc[recvRank], recvSize, MPI_UNSIGNED_LONG, recvRank, 46, client->intraComm, &requests.back());
    requests.push_back(MPI_Request());
    MPI_Irecv(recvMaskDst[recvRank], recvSize, MPI_UNSIGNED_CHAR, recvRank, 47, client->intraComm, &requests.back());
  }

  std::unordered_map<int, CArray<size_t,1> > globalIndexDst;
  std::unordered_map<int, CArray<double,1> > weightDst;
  std::unordered_map<int, unsigned char* > sendMaskDst;
  std::unordered_map<int, unsigned long* > sendGlobalIndexSrc;
  for (itIndex = itbIndex; itIndex != iteIndex; ++itIndex)
  {
    int sendRank = itIndex->first;
    int sendSize = sendRankSizeMap[sendRank];
    const SendIndexMap& sendIndexMap = itIndex->second;
    SendIndexMap::const_iterator itbSend = sendIndexMap.begin(), iteSend = sendIndexMap.end(), itSend;
    globalIndexDst[sendRank].resize(sendSize);
    weightDst[sendRank].resize(sendSize);
    sendMaskDst[sendRank] = new unsigned char [sendSize];
    sendGlobalIndexSrc[sendRank] = new unsigned long [sendSize];
    int countIndex = 0;
    for (itSend = itbSend; itSend != iteSend; ++itSend)
    {
      const std::vector<std::pair<size_t,double> >& dstWeight = itSend->second;
      for (int idx = 0; idx < dstWeight.size(); ++idx)
      {
        globalIndexDst[sendRank](countIndex) = dstWeight[idx].first;
        weightDst[sendRank](countIndex) = dstWeight[idx].second;
        if (0 < globalLocalIndexGridDestSendToServer.count(dstWeight[idx].first))
          sendMaskDst[sendRank][countIndex] = 1;
        else
          sendMaskDst[sendRank][countIndex] = 0;
        sendGlobalIndexSrc[sendRank][countIndex] = itSend->first;
        ++countIndex;
      }
    }

    // Send global index source and mask
    requests.push_back(MPI_Request());
    MPI_Isend(sendGlobalIndexSrc[sendRank], sendSize, MPI_UNSIGNED_LONG, sendRank, 46, client->intraComm, &requests.back());
    requests.push_back(MPI_Request());
    MPI_Isend(sendMaskDst[sendRank], sendSize, MPI_UNSIGNED_CHAR, sendRank, 47, client->intraComm, &requests.back());
  }

  status.resize(requests.size());
  MPI_Waitall(requests.size(), &requests[0], &status[0]);

  // Okie, now use the mask to identify which index source we need to send, then also signal the destination which masked index we will return
  std::vector<MPI_Request>().swap(requests);
  std::vector<MPI_Status>().swap(status);
  // Okie, on destination side, we will wait for information of masked index of source
  for (std::map<int,int>::const_iterator itSend = sendRankSizeMap.begin(); itSend != sendRankSizeMap.end(); ++itSend)
  {
    int recvRank = itSend->first;
    int recvSize = itSend->second;

    requests.push_back(MPI_Request());
    MPI_Irecv(sendMaskDst[recvRank], recvSize, MPI_UNSIGNED_CHAR, recvRank, 48, client->intraComm, &requests.back());
  }

  // Ok, now we fill in local index of grid source (we even count for masked index)
  CDistributionClient distributionClientSrc(client->clientRank, gridSource_);
  CDistributionClient::GlobalLocalDataMap& globalLocalIndexGridSrcSendToServer = distributionClientSrc.getGlobalLocalDataSendToServer();
  localIndexToSendFromGridSource_.push_back(SendingIndexGridSourceMap());
  SendingIndexGridSourceMap& tmpSend = localIndexToSendFromGridSource_.back();
  for (std::map<int,int>::const_iterator itRecv = recvRankSizeMap.begin(); itRecv != recvRankSizeMap.end(); ++itRecv)
  {
    int recvRank = itRecv->first;
    int recvSize = itRecv->second;
    unsigned char* recvMask = recvMaskDst[recvRank];
    unsigned long* recvIndexSrc = recvGlobalIndexSrc[recvRank];
    int realSendSize = 0;
    for (int idx = 0; idx < recvSize; ++idx)
    {
      if (0 != (*(recvMask+idx))) // OKie, now we have a demand from non-masked index destination
        if (0 < globalLocalIndexGridSrcSendToServer.count(*(recvIndexSrc+idx))) // check whether index source is masked
         ++realSendSize;
        else // inform the destination that this index is masked
         *(recvMask+idx) = 0;
    }

    tmpSend[recvRank].resize(realSendSize);
    realSendSize = 0;
    for (int idx = 0; idx < recvSize; ++idx)
    {
      if (0 != (*(recvMask+idx))) // OKie, now we have a demand from non-masked index destination
      {
        tmpSend[recvRank](realSendSize) = globalLocalIndexGridSrcSendToServer[*(recvIndexSrc+idx)];
         ++realSendSize;
      }
    }

    // Okie, now inform the destination which source index are masked
    requests.push_back(MPI_Request());
    MPI_Isend(recvMaskDst[recvRank], recvSize, MPI_UNSIGNED_CHAR, recvRank, 48, client->intraComm, &requests.back());
  }
  status.resize(requests.size());
  MPI_Waitall(requests.size(), &requests[0], &status[0]);

  // Cool, now we can fill in local index of grid destination (counted for masked index)
  localIndexToReceiveOnGridDest_.push_back(RecvIndexGridDestinationMap());
  RecvIndexGridDestinationMap& recvTmp = localIndexToReceiveOnGridDest_.back();
  for (std::map<int,int>::const_iterator itSend = sendRankSizeMap.begin(); itSend != sendRankSizeMap.end(); ++itSend)
  {
    int recvRank = itSend->first;
    int recvSize = itSend->second;
    unsigned char* recvMask = sendMaskDst[recvRank];

    CArray<size_t,1>& recvIndexDst = globalIndexDst[recvRank];
    CArray<double,1>& recvWeightDst = weightDst[recvRank];
    int realRecvSize = 0;
    for (int idx = 0; idx < recvSize; ++idx)
    {
      if (0 != *(recvMask+idx)) // OKie, now we have a non-masked index destination
         ++realRecvSize;
    }

    int localIndexDst;
    recvTmp[recvRank].resize(realRecvSize);
    realRecvSize = 0;
    for (int idx = 0; idx < recvSize; ++idx)
    {
      if (0 != *(recvMask+idx)) // OKie, now we have a demand from non-masked index destination
      {
        recvTmp[recvRank][realRecvSize].first = globalLocalIndexGridDestSendToServer[recvIndexDst(idx)];
        recvTmp[recvRank][realRecvSize].second = recvWeightDst(idx);
         ++realRecvSize;
      }
    }
  }

  delete [] recvCount;
  delete [] displ;
  delete [] sendRankBuff;
  delete [] recvRankBuff;
  delete [] sendSizeBuff;
  delete [] recvSizeBuff;

  std::unordered_map<int, unsigned char* >::const_iterator itChar;
  for (itChar = sendMaskDst.begin(); itChar != sendMaskDst.end(); ++itChar)
    delete [] itChar->second;
  for (itChar = recvMaskDst.begin(); itChar != recvMaskDst.end(); ++itChar)
    delete [] itChar->second;
  std::unordered_map<int, unsigned long* >::const_iterator itLong;
  for (itLong = sendGlobalIndexSrc.begin(); itLong != sendGlobalIndexSrc.end(); ++itLong)
    delete [] itLong->second;
  for (itLong = recvGlobalIndexSrc.begin(); itLong != recvGlobalIndexSrc.end(); ++itLong)
    delete [] itLong->second;

}
CATCH

/*!
  Local index of data which need sending from the grid source
  \return local index of data
*/
const std::list<CGridTransformation::SendingIndexGridSourceMap>& CGridTransformation::getLocalIndexToSendFromGridSource() const
TRY
{
  return localIndexToSendFromGridSource_;
}
CATCH

/*!
  Local index of data which will be received on the grid destination
  \return local index of data
*/
const std::list<CGridTransformation::RecvIndexGridDestinationMap>& CGridTransformation::getLocalIndexToReceiveOnGridDest() const
TRY
{
  return localIndexToReceiveOnGridDest_;
}
CATCH

/*!
 Number of index will be received on the grid destination
  \return number of index of data
*/
const std::list<size_t>& CGridTransformation::getNbLocalIndexToReceiveOnGridDest() const
TRY
{
  return nbLocalIndexOnGridDest_;
}
CATCH

}
