#include "spatial_transform_filter.hpp"
#include "grid_transformation.hpp"
#include "context.hpp"
#include "context_client.hpp"
#include "timer.hpp"
#include "workflow_graph.hpp"
#include "file.hpp"

namespace xios
{
  CSpatialTransformFilter::CSpatialTransformFilter(CGarbageCollector& gc, CSpatialTransformFilterEngine* engine, double outputValue, size_t inputSlotsCount)
    : CFilter(gc, inputSlotsCount, engine), outputDefaultValue(outputValue)
  { /* Nothing to do */ }

  std::pair<std::shared_ptr<CSpatialTransformFilter>, std::shared_ptr<CSpatialTransformFilter> >
  CSpatialTransformFilter::buildFilterGraph(CGarbageCollector& gc, CGrid* srcGrid, CGrid* destGrid, bool hasMissingValue, double missingValue)
  {
    if (!srcGrid || !destGrid)
      ERROR("std::pair<std::shared_ptr<CSpatialTransformFilter>, std::shared_ptr<CSpatialTransformFilter> >"
            "buildFilterGraph(CGarbageCollector& gc, CGrid* srcGrid, CGrid* destGrid)",
            "Impossible to build the filter graph if either the source or the destination grid are null.");

    std::shared_ptr<CSpatialTransformFilter> firstFilter, lastFilter;
    // Note that this loop goes from the last transformation to the first transformation
    do
    {
      CGridTransformation* gridTransformation = destGrid->getTransformations();
      CSpatialTransformFilterEngine* engine = CSpatialTransformFilterEngine::get(destGrid->getTransformations());
      const std::vector<StdString>& auxInputs = gridTransformation->getAuxInputs();
      size_t inputCount = 1 + (auxInputs.empty() ? 0 : auxInputs.size());
      double defaultValue  = (hasMissingValue) ? std::numeric_limits<double>::quiet_NaN() : 0.0;


      const CGridTransformationSelector::ListAlgoType& algoList = gridTransformation->getAlgoList() ;
      CGridTransformationSelector::ListAlgoType::const_iterator it  ;

      bool isSpatialTemporal=false ;
      for (it=algoList.begin();it!=algoList.end();++it)  if (it->second.first == TRANS_TEMPORAL_SPLITTING) isSpatialTemporal=true ;

      std::shared_ptr<CSpatialTransformFilter> filter ;
      if( isSpatialTemporal) filter = std::shared_ptr<CSpatialTransformFilter>(new CSpatialTemporalFilter(gc, engine, gridTransformation, defaultValue, inputCount));
      else filter = std::shared_ptr<CSpatialTransformFilter>(new CSpatialTransformFilter(gc, engine, defaultValue, inputCount));

      
      if (!lastFilter)
        lastFilter = filter;
      else
        filter->connectOutput(firstFilter, 0);

      firstFilter = filter;
      for (size_t idx = 0; idx < auxInputs.size(); ++idx)
      {
        CField* fieldAuxInput = CField::get(auxInputs[idx]);
        fieldAuxInput->buildFilterGraph(gc, false);
        fieldAuxInput->getInstantDataFilter()->connectOutput(firstFilter,idx+1);
      }

      destGrid = gridTransformation->getGridSource();
    }
    while (destGrid != srcGrid);

    return std::make_pair(firstFilter, lastFilter);
  }

  void CSpatialTransformFilter::onInputReady(std::vector<CDataPacketPtr> data)
  {
    CSpatialTransformFilterEngine* spaceFilter = static_cast<CSpatialTransformFilterEngine*>(engine);
    CDataPacketPtr outputPacket = spaceFilter->applyFilter(data, outputDefaultValue, this->tag, this->start_graph, this->end_graph, this->field);
    if (outputPacket)
      onOutputReady(outputPacket);
  }

  CSpatialTemporalFilter::CSpatialTemporalFilter(CGarbageCollector& gc, CSpatialTransformFilterEngine* engine, CGridTransformation* gridTransformation, double outputValue, size_t inputSlotsCount)
    : CSpatialTransformFilter(gc, engine, outputValue, inputSlotsCount), record(0)
  {
      const CGridTransformationSelector::ListAlgoType& algoList = gridTransformation->getAlgoList() ;
      CGridTransformationSelector::ListAlgoType::const_iterator it  ;

      int pos ;
      for (it=algoList.begin();it!=algoList.end();++it) 
        if (it->second.first == TRANS_TEMPORAL_SPLITTING)
        {
          pos=it->first ;
          if (pos < algoList.size()-1)
            ERROR("SpatialTemporalFilter::CSpatialTemporalFilter(CGarbageCollector& gc, CSpatialTransformFilterEngine* engine, CGridTransformation* gridTransformation, double outputValue, size_t inputSlotsCount))",
                  "temporal splitting operation must be the last of whole transformation on same grid") ;
        }
          
      CGrid* grid=gridTransformation->getGridDestination() ;

      CAxis* axis = grid->getAxis(gridTransformation->getElementPositionInGridDst2AxisPosition().find(pos)->second) ;

      nrecords = axis->index.numElements() ;
  }


  void CSpatialTemporalFilter::onInputReady(std::vector<CDataPacketPtr> data)
  {
    CSpatialTransformFilterEngine* spaceFilter = static_cast<CSpatialTransformFilterEngine*>(engine);
    CDataPacketPtr outputPacket = spaceFilter->applyFilter(data, outputDefaultValue, this->tag, this->start_graph, this->end_graph, this->field);

    if (outputPacket)
    {
      size_t nelements=outputPacket->data.numElements() ;
      if (!tmpData.numElements())
      {
        tmpData.resize(nelements);
        tmpData=outputDefaultValue ;
      }

      nelements/=nrecords ;
      size_t offset=nelements*record ;
      for(size_t i=0;i<nelements;++i)  tmpData(i+offset) = outputPacket->data(i) ;
    
      record ++ ;
      if (record==nrecords)
      {
        record=0 ;
        CDataPacketPtr packet = CDataPacketPtr(new CDataPacket);
        packet->date = data[0]->date;
        packet->timestamp = data[0]->timestamp;
        packet->status = data[0]->status;
        packet->data.resize(tmpData.numElements());
        packet->data = tmpData;
        packet->field = this->field;
        onOutputReady(packet);
        tmpData.resize(0) ;
      }
    }
  }


  CSpatialTransformFilterEngine::CSpatialTransformFilterEngine(CGridTransformation* gridTransformation)
    : gridTransformation(gridTransformation)
  {
    if (!gridTransformation)
      ERROR("CSpatialTransformFilterEngine::CSpatialTransformFilterEngine(CGridTransformation* gridTransformation)",
            "Impossible to construct a spatial transform filter engine without a valid grid transformation.");
  }

  std::map<CGridTransformation*, std::shared_ptr<CSpatialTransformFilterEngine> > CSpatialTransformFilterEngine::engines;

  CSpatialTransformFilterEngine* CSpatialTransformFilterEngine::get(CGridTransformation* gridTransformation)
  {
    if (!gridTransformation)
      ERROR("CSpatialTransformFilterEngine& CSpatialTransformFilterEngine::get(CGridTransformation* gridTransformation)",
            "Impossible to get the requested engine, the grid transformation is invalid.");

    std::map<CGridTransformation*, std::shared_ptr<CSpatialTransformFilterEngine> >::iterator it = engines.find(gridTransformation);
    if (it == engines.end())
    {
      std::shared_ptr<CSpatialTransformFilterEngine> engine(new CSpatialTransformFilterEngine(gridTransformation));
      it = engines.insert(std::make_pair(gridTransformation, engine)).first;
    }

    return it->second.get();
  }

  CDataPacketPtr CSpatialTransformFilterEngine::apply(std::vector<CDataPacketPtr> data)
  {
    /* Nothing to do */
  }

  bool CSpatialTransformFilterEngine::buildGraph(std::vector<CDataPacketPtr> data, int tag, Time start_graph, Time end_graph, CField *field)
  {
    bool building_graph = tag ? data[0]->timestamp >= start_graph && data[0]->timestamp <= end_graph : false;
    if(building_graph)
    {
      this->filterID = InvalidableObject::filterIdGenerator++;
      int edgeID = InvalidableObject::edgeIdGenerator++;    

      CWorkflowGraph::allocNodeEdge();

      CWorkflowGraph::addNode(this->filterID, "Spatial Transform Filter", 4, 1, 1, data[0]);
      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;
      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = field->record4graphXiosAttributes();
      if(field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +field->file->record4graphXiosAttributes();


      if(CWorkflowGraph::build_begin)
      {
        CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);

        (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0;
      }
      else CWorkflowGraph::build_begin = true;
    }

    return building_graph;
  }

  CDataPacketPtr CSpatialTransformFilterEngine::applyFilter(std::vector<CDataPacketPtr> data, double defaultValue, int tag, Time start_graph, Time end_graph, CField *field)
  {
    
    bool BG = buildGraph(data, tag, start_graph, end_graph, field);

    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;

    if (packet->status == CDataPacket::NO_ERROR)
    {
      if (1 < data.size())  // Dynamical transformations
      {
        std::vector<CArray<double,1>* > dataAuxInputs(data.size()-1);
        for (size_t idx = 0; idx < dataAuxInputs.size(); ++idx) dataAuxInputs[idx] = &(data[idx+1]->data);
        gridTransformation->computeAll(dataAuxInputs, packet->timestamp);
      }
      packet->data.resize(gridTransformation->getGridDestination()->storeIndex_client.numElements());
      if (0 != packet->data.numElements())
        (packet->data)(0) = defaultValue;
      if(BG) apply(data[0]->data, packet->data, this->filterID);
      else apply(data[0]->data, packet->data);
    }

    if(BG) packet->src_filterID=this->filterID;
    if(BG) packet->distance=data[0]->distance+1;
    packet->field = field;

    return packet;
  }

  void CSpatialTransformFilterEngine::apply(const CArray<double, 1>& dataSrc, CArray<double,1>& dataDest, int filterID)
  {
    CTimer::get("CSpatialTransformFilterEngine::apply").resume(); 
    
    CContextClient* client = CContext::getCurrent()->client;
    int rank;
    MPI_Comm_rank (client->intraComm, &rank);

    // Get default value for output data
    bool ignoreMissingValue = false; 
    double defaultValue = std::numeric_limits<double>::quiet_NaN();
    if (0 != dataDest.numElements()) ignoreMissingValue = NumTraits<double>::isNan(dataDest(0));

    const std::list<CGridTransformation::SendingIndexGridSourceMap>& listLocalIndexSend = gridTransformation->getLocalIndexToSendFromGridSource();
    const std::list<CGridTransformation::RecvIndexGridDestinationMap>& listLocalIndexToReceive = gridTransformation->getLocalIndexToReceiveOnGridDest();
    const std::list<size_t>& listNbLocalIndexToReceive = gridTransformation->getNbLocalIndexToReceiveOnGridDest();
    const std::vector<CGenericAlgorithmTransformation*>& listAlgos = gridTransformation->getAlgos();

    CArray<double,1> dataCurrentDest(dataSrc.copy());

    std::list<CGridTransformation::SendingIndexGridSourceMap>::const_iterator itListSend  = listLocalIndexSend.begin(),
                                                                              iteListSend = listLocalIndexSend.end();
    std::list<CGridTransformation::RecvIndexGridDestinationMap>::const_iterator itListRecv = listLocalIndexToReceive.begin();
    std::list<size_t>::const_iterator itNbListRecv = listNbLocalIndexToReceive.begin();
    std::vector<CGenericAlgorithmTransformation*>::const_iterator itAlgo = listAlgos.begin();

    for (; itListSend != iteListSend; ++itListSend, ++itListRecv, ++itNbListRecv, ++itAlgo)
    {
      CArray<double,1> dataCurrentSrc(dataCurrentDest);
      const CGridTransformation::SendingIndexGridSourceMap& localIndexToSend = *itListSend;

      // Sending data from field sources to do transformations
      std::map<int, CArray<int,1> >::const_iterator itbSend = localIndexToSend.begin(), itSend,
                                                    iteSend = localIndexToSend.end();
      int idxSendBuff = 0;
      std::vector<double*> sendBuff(localIndexToSend.size());
      double* sendBuffRank;
      for (itSend = itbSend; itSend != iteSend; ++itSend, ++idxSendBuff)
      {
        int destRank = itSend->first;
        if (0 != itSend->second.numElements())
        {
          if (rank != itSend->first)
            sendBuff[idxSendBuff] = new double[itSend->second.numElements()];
          else
            sendBuffRank = new double[itSend->second.numElements()];
        }
      }

      idxSendBuff = 0;
      std::vector<MPI_Request> sendRecvRequest;
      for (itSend = itbSend; itSend != iteSend; ++itSend, ++idxSendBuff)
      {
        int destRank = itSend->first;
        const CArray<int,1>& localIndex_p = itSend->second;
        int countSize = localIndex_p.numElements();
        if (destRank != rank)
        {
          for (int idx = 0; idx < countSize; ++idx)
          {
            sendBuff[idxSendBuff][idx] = dataCurrentSrc(localIndex_p(idx));
          }
          sendRecvRequest.push_back(MPI_Request());
          MPI_Isend(sendBuff[idxSendBuff], countSize, MPI_DOUBLE, destRank, 12, client->intraComm, &sendRecvRequest.back());
        }
        else
        {
          for (int idx = 0; idx < countSize; ++idx)
          {
            sendBuffRank[idx] = dataCurrentSrc(localIndex_p(idx));
          }
        }
      }

      // Receiving data on destination fields
      const CGridTransformation::RecvIndexGridDestinationMap& localIndexToReceive = *itListRecv;
      CGridTransformation::RecvIndexGridDestinationMap::const_iterator itbRecv = localIndexToReceive.begin(), itRecv,
                                                                       iteRecv = localIndexToReceive.end();
      int recvBuffSize = 0;
      for (itRecv = itbRecv; itRecv != iteRecv; ++itRecv)
      {
        if (itRecv->first != rank )
          recvBuffSize += itRecv->second.size();
      }
      //(recvBuffSize < itRecv->second.size()) ? itRecv->second.size() : recvBuffSize;
      double* recvBuff;

      if (0 != recvBuffSize) recvBuff = new double[recvBuffSize];
      int currentBuff = 0;
      for (itRecv = itbRecv; itRecv != iteRecv; ++itRecv)
      {
        int srcRank = itRecv->first;
        if (srcRank != rank)
        {
          int countSize = itRecv->second.size();
          sendRecvRequest.push_back(MPI_Request());
          MPI_Irecv(recvBuff + currentBuff, countSize, MPI_DOUBLE, srcRank, 12, client->intraComm, &sendRecvRequest.back());
          currentBuff += countSize;
        }
      }
      std::vector<MPI_Status> status(sendRecvRequest.size());
      MPI_Waitall(sendRecvRequest.size(), &sendRecvRequest[0], &status[0]);

      dataCurrentDest.resize(*itNbListRecv);
      dataCurrentDest = 0.0;

      std::vector<bool> localInitFlag(dataCurrentDest.numElements(), true);
      currentBuff = 0;
      bool firstPass=true; 
      
      if(filterID >=0) // building_graph
      {
        (*CWorkflowGraph::mapFilters_ptr_with_info)[filterID].filter_name += ("\\n"+(*itAlgo)->getName());
      } 
        
      for (itRecv = itbRecv; itRecv != iteRecv; ++itRecv)
      {
        const std::vector<std::pair<int,double> >& localIndex_p = itRecv->second;
        int srcRank = itRecv->first;

        
        if (srcRank != rank)
        {
          int countSize = itRecv->second.size();
          (*itAlgo)->apply(localIndex_p,
                           recvBuff+currentBuff,
                           dataCurrentDest,
                           localInitFlag,
                           ignoreMissingValue,firstPass);
          currentBuff += countSize;
        }
        else
        {
          (*itAlgo)->apply(localIndex_p,
                           sendBuffRank,
                           dataCurrentDest,
                           localInitFlag,
                           ignoreMissingValue,firstPass);
        }

        firstPass=false ;
      }

      (*itAlgo)->updateData(dataCurrentDest);

      idxSendBuff = 0;
      for (itSend = itbSend; itSend != iteSend; ++itSend, ++idxSendBuff)
      {
        if (0 != itSend->second.numElements())
        {
          if (rank != itSend->first)
            delete [] sendBuff[idxSendBuff];
          else
            delete [] sendBuffRank;
        }
      }
      if (0 != recvBuffSize) delete [] recvBuff;
    }
    if (dataCurrentDest.numElements() != dataDest.numElements())
    ERROR("CSpatialTransformFilterEngine::apply(const CArray<double, 1>& dataSrc, CArray<double,1>& dataDest)",
          "Incoherent between the received size and expected size. " << std::endl 
          << "Expected size: " << dataDest.numElements() << std::endl 
          << "Received size: " << dataCurrentDest.numElements());

    dataDest = dataCurrentDest;

    CTimer::get("CSpatialTransformFilterEngine::apply").suspend() ;
  }
} // namespace xios
