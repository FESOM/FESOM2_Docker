#include "field.hpp"

#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"

#include "node_type.hpp"
#include "calendar_util.hpp"
#include "message.hpp"
#include "xios_spl.hpp"
#include "type.hpp"
#include "timer.hpp"
#include "context_client.hpp"
#include "context_server.hpp"
#include <set>
#include "garbage_collector.hpp"
#include "source_filter.hpp"
#include "store_filter.hpp"
#include "file_writer_filter.hpp"
#include "pass_through_filter.hpp"
#include "filter_expr_node.hpp"
#include "lex_parser.hpp"
#include "temporal_filter.hpp"
#include "spatial_transform_filter.hpp"
#include "file_server_writer_filter.hpp"
#include "workflow_graph.hpp"

#include "yacc_var.hpp"
namespace xios{

   /// ////////////////////// Définitions ////////////////////// ///

   CField::CField(void)
      : CObjectTemplate<CField>(), CFieldAttributes()
      , grid(), file()
      , written(false)
      , nstep(0), nstepMax(0)
      , hasOutputFile(false)
      , domAxisScalarIds_(vector<StdString>(3,""))
      , areAllReferenceSolved(false), isReferenceSolved(false), isReferenceSolvedAndTransformed(false)
      , isGridChecked(false)
      , useCompressedOutput(false)
      , hasTimeInstant(false)
      , hasTimeCentered(false)
      , wasDataRequestedFromServer(false)
      , wasDataAlreadyReceivedFromServer(false)
      , mustAutoTrigger(false)
      , isEOF(false), nstepMaxRead(false)
   { setVirtualVariableGroup(CVariableGroup::create(getId() + "_virtual_variable_group")); 
     field_graph_start = -2;
     field_graph_end = -2;
   }

   CField::CField(const StdString& id)
      : CObjectTemplate<CField>(id), CFieldAttributes()
      , grid(), file()
      , written(false)
      , nstep(0), nstepMax(0)
      , hasOutputFile(false)
      , domAxisScalarIds_(vector<StdString>(3,""))
      , areAllReferenceSolved(false), isReferenceSolved(false), isReferenceSolvedAndTransformed(false)
      , isGridChecked(false)
      , useCompressedOutput(false)
      , hasTimeInstant(false)
      , hasTimeCentered(false)
      , wasDataRequestedFromServer(false)
      , wasDataAlreadyReceivedFromServer(false)
      , mustAutoTrigger(false)
      , isEOF(false), nstepMaxRead(false)
   { setVirtualVariableGroup(CVariableGroup::create(getId() + "_virtual_variable_group")); 
     field_graph_start = -2;
     field_graph_end = -2;
   }


   CField::~CField(void)
   {}

  //----------------------------------------------------------------

   void CField::setVirtualVariableGroup(CVariableGroup* newVVariableGroup)
   TRY
   {
      this->vVariableGroup = newVVariableGroup;
   }
   CATCH

   CVariableGroup* CField::getVirtualVariableGroup(void) const
   TRY
   {
      return this->vVariableGroup;
   }
   CATCH

   std::vector<CVariable*> CField::getAllVariables(void) const
   TRY
   {
      return this->vVariableGroup->getAllChildren();
   }
   CATCH

   void CField::solveDescInheritance(bool apply, const CAttributeMap* const parent)
   TRY
   {
      SuperClassAttribute::setAttributes(parent, apply);
      this->getVirtualVariableGroup()->solveDescInheritance(apply, NULL);
   }
   CATCH_DUMP_ATTR

  //----------------------------------------------------------------

  bool CField::dispatchEvent(CEventServer& event)
  TRY
  {
    if (SuperClass::dispatchEvent(event)) return true;
    else
    {
      switch(event.type)
      {
        case EVENT_ID_UPDATE_DATA :
          recvUpdateData(event);
          return true;
          break;

        case EVENT_ID_READ_DATA :
          recvReadDataRequest(event);
          return true;
          break;

        case EVENT_ID_READ_DATA_READY :
          recvReadDataReady(event);
          return true;
          break;

        case EVENT_ID_ADD_VARIABLE :
          recvAddVariable(event);
          return true;
          break;

        case EVENT_ID_ADD_VARIABLE_GROUP :
          recvAddVariableGroup(event);
          return true;
          break;

        default :
          ERROR("bool CField::dispatchEvent(CEventServer& event)", << "Unknown Event");
          return false;
      }
    }
  }
  CATCH

  // byte counters for perf diagnostics (tier-1/client-side send and server-side recv)
  size_t CField::totalSendBytes = 0;
  size_t CField::totalRecvBytes = 0;

  void CField::sendUpdateData(const CArray<double,1>& data)
  TRY
  {
    CTimer::get("Field : send data").resume();

    CContext* context = CContext::getCurrent();
    CContextClient* client = (!context->hasServer) ? context->client : this->file->getContextClient();
    int receiverSize = client->serverSize;

    CEventClient event(getType(), EVENT_ID_UPDATE_DATA);

    map<int, CArray<int,1> >::iterator it;
    list<CMessage> list_msg;
    list<CArray<double,1> > list_data;

    if (!grid->doGridHaveDataDistributed(client))
    {
       if (client->isServerLeader())
       {
          for (it = grid->storeIndex_toSrv[client].begin(); it != grid->storeIndex_toSrv[client].end(); it++)
          {
            int rank = it->first;
            CArray<int,1>& index = it->second;

            list_msg.push_back(CMessage());
            list_data.push_back(CArray<double,1>(index.numElements()));

            CArray<double,1>& data_tmp = list_data.back();
            for (int n = 0; n < data_tmp.numElements(); n++) data_tmp(n) = data(index(n));

            list_msg.back() << getId() << data_tmp;
            event.push(rank, 1, list_msg.back());
            CField::totalSendBytes += static_cast<size_t>(index.numElements()) * sizeof(double);
          }
          client->sendEvent(event);
        }
      else client->sendEvent(event);
    }
    else
    {
      for (it = grid->storeIndex_toSrv[client].begin(); it != grid->storeIndex_toSrv[client].end(); it++)
      {
        int rank = it->first;
        CArray<int,1>& index = it->second;

        list_msg.push_back(CMessage());
        list_data.push_back(CArray<double,1>(index.numElements()));

        CArray<double,1>& data_tmp = list_data.back();
        for (int n = 0; n < data_tmp.numElements(); n++) data_tmp(n) = data(index(n));

        list_msg.back() << getId() << data_tmp;
        event.push(rank, grid->nbSenders[receiverSize][rank], list_msg.back());
        CField::totalSendBytes += static_cast<size_t>(index.numElements()) * sizeof(double);
      }
      client->sendEvent(event);
    }

    CTimer::get("Field : send data").suspend();
  }
  CATCH_DUMP_ATTR

  void CField::recvUpdateData(CEventServer& event)
  TRY
  {
    std::map<int,CBufferIn*> rankBuffers;

    list<CEventServer::SSubEvent>::iterator it;
    string fieldId;
    CTimer::get("Field : recv data").resume();
    for (it = event.subEvents.begin(); it != event.subEvents.end(); ++it)
    {
      int rank = it->rank;
      CBufferIn* buffer = it->buffer;
      *buffer >> fieldId;
      rankBuffers[rank] = buffer;
    }
    get(fieldId)->recvUpdateData(rankBuffers);
    CTimer::get("Field : recv data").suspend();
  }
  CATCH

  void  CField::recvUpdateData(std::map<int,CBufferIn*>& rankBuffers)
  TRY
  {
    CContext* context = CContext::getCurrent();

    size_t sizeData = 0;
    if (0 == recvDataSrv.numElements())
    {            
      CArray<int,1>& storeClient = grid->storeIndex_client;

      // Gather all data from different clients      
      recvDataSrv.resize(storeClient.numElements());
      recvFoperationSrv = std::shared_ptr<func::CFunctor>(new func::CInstant(recvDataSrv));
    }

    CArray<double,1> recv_data_tmp(recvDataSrv.numElements());    
    const CDate& currDate = context->getCalendar()->getCurrentDate();
    CDuration offsetAllButMonth (freq_offset.getValue().year, 0 , freq_offset.getValue().day,
                                   freq_offset.getValue().hour, freq_offset.getValue().minute,
                                   freq_offset.getValue().second, freq_offset.getValue().timestep);
    const CDate opeDate   = (last_operation_srv - offsetAllButMonth + context->getCalendar()->getTimeStep())
                              + freq_op + freq_operation_srv - freq_op - context->getCalendar()->getTimeStep() + offsetAllButMonth;

    if (opeDate <= currDate)
    {
      for (map<int, CArray<size_t, 1> >::iterator it = grid->outLocalIndexStoreOnClient.begin(); it != grid->outLocalIndexStoreOnClient.end(); ++it)
      {
        CArray<double,1> tmp;
        CArray<size_t,1>& indexTmp = it->second;
        *(rankBuffers[it->first]) >> tmp;
        CField::totalRecvBytes += static_cast<size_t>(tmp.numElements()) * sizeof(double);
        for (int idx = 0; idx < indexTmp.numElements(); ++idx)
        {
          recv_data_tmp(indexTmp(idx)) = tmp(idx);
        }
      }
    }

    this->setData(recv_data_tmp);
    // delete incomming flux for server only
    recvFoperationSrv.reset() ;
    recvDataSrv.reset() ;
  }
  CATCH_DUMP_ATTR

  void CField::writeUpdateData(const CArray<double,1>& data)
  TRY
  {
    CContext* context = CContext::getCurrent();

    const CDate& currDate = context->getCalendar()->getCurrentDate();
    CDuration offsetAllButMonth (freq_offset.getValue().year, 0 , freq_offset.getValue().day,
                                   freq_offset.getValue().hour, freq_offset.getValue().minute,
                                   freq_offset.getValue().second, freq_offset.getValue().timestep);
    const CDate opeDate   = (last_operation_srv - offsetAllButMonth + context->getCalendar()->getTimeStep())
                              + freq_op + freq_operation_srv - freq_op - context->getCalendar()->getTimeStep() + offsetAllButMonth;
    const CDate writeDate = last_Write_srv + freq_write_srv;

    if (opeDate <= currDate)
    {
      (*recvFoperationSrv)(data);
      last_operation_srv = currDate;
    }

    if (writeDate < (currDate + freq_operation_srv))
    {
      recvFoperationSrv->final();
      last_Write_srv = writeDate;
      grid->computeWrittenIndex();
      writeField();
      lastlast_Write_srv = last_Write_srv;
    }
  }
  CATCH_DUMP_ATTR

  void CField::writeField(void)
  TRY
  {
    if (!getRelFile()->isEmptyZone())
    {
      if (grid->doGridHaveDataToWrite() || getRelFile()->type == CFile::type_attr::one_file)
      {
        getRelFile()->checkWriteFile();
        this->incrementNStep();
        getRelFile()->getDataOutput()->writeFieldData(CField::get(this));
      }
    }
  }
  CATCH_DUMP_ATTR

  /*
    Send a request for reading data.
    Client sends a request to server for demanding server to read data and send back to it.
    For now, this function is called only by client
    In the future, it can be called by level-1 servers
    \param [in] tsDataRequested timestamp when the call is made
  */
  bool CField::sendReadDataRequest(const CDate& tsDataRequested)
  TRY
  {
    CContext* context = CContext::getCurrent();
    // CContextClient* client = context->client;

    // This code is for future: If we want to read file with level-2 servers
    CContextClient* client = (!context->hasServer) ? context->client : this->file->getContextClient();

    lastDataRequestedFromServer = tsDataRequested;

    // No need to send the request if we are sure that we are already at EOF
    if (!isEOF || context->getCalendar()->getCurrentDate() <= dateEOF)
    {
      CEventClient event(getType(), EVENT_ID_READ_DATA);
      if (client->isServerLeader())
      {
        CMessage msg;
        msg << getId();
        const std::list<int>& ranks = client->getRanksServerLeader();
        for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
          event.push(*itRank, 1, msg);
        client->sendEvent(event);
      }
      else client->sendEvent(event);
    }
    else
      serverSourceFilter->signalEndOfStream(tsDataRequested);

    wasDataRequestedFromServer = true;

    return !isEOF;
  }
  CATCH_DUMP_ATTR

  /*!
  Send request new data read from file if need be, that is the current data is out-of-date.
  \return true if and only if some data was requested
  */
  bool CField::sendReadDataRequestIfNeeded(void)
  TRY
  {
    const CDate& currentDate = CContext::getCurrent()->getCalendar()->getCurrentDate();

    bool dataRequested = false;

    while (currentDate >= lastDataRequestedFromServer)
    {
      info(20) << "currentDate : " << currentDate << endl ;
      info(20) << "lastDataRequestedFromServer : " << lastDataRequestedFromServer << endl ;
      info(20) << "file->output_freq.getValue() : " << file->output_freq.getValue() << endl ;
      info(20) << "lastDataRequestedFromServer + file->output_freq.getValue() : " << lastDataRequestedFromServer + file->output_freq << endl ;

      dataRequested |= sendReadDataRequest(lastDataRequestedFromServer + file->output_freq);
    }

    return dataRequested;
  }
  CATCH_DUMP_ATTR

  void CField::recvReadDataRequest(CEventServer& event)
  TRY
  {
    CBufferIn* buffer = event.subEvents.begin()->buffer;
    StdString fieldId;
    *buffer >> fieldId;
    get(fieldId)->recvReadDataRequest();
  }
  CATCH

  /*!
    Receive data request sent from client and process it
    Every time server receives this request, it will try to read data and sent read data back to client
    At the moment, this function is called by server level 1
    In the future, this should (only) be done by the last level servers.
  */
  void CField::recvReadDataRequest(void)
  TRY
  {
    CContext* context = CContext::getCurrent();
    CContextClient* client = context->client;

    CEventClient event(getType(), EVENT_ID_READ_DATA_READY);
    std::list<CMessage> msgs;

    EReadField hasData = readField();

    map<int, CArray<double,1> >::iterator it;
    if (!grid->doGridHaveDataDistributed(client))
    {
       if (client->isServerLeader())
       {
          if (0 != recvDataSrv.numElements())
          {            
            const std::list<int>& ranks = client->getRanksServerLeader();
            for (std::list<int>::const_iterator itRank = ranks.begin(), itRankEnd = ranks.end(); itRank != itRankEnd; ++itRank)
            {
              msgs.push_back(CMessage());
              CMessage& msg = msgs.back();
              msg << getId();
              switch (hasData)
              {
                case RF_DATA:
                  msg << getNStep() - 1 << recvDataSrv;
                  break;
                case RF_NODATA:
                  msg << int(-2) << recvDataSrv;
                  break;
                case RF_EOF:                  
                default:
                  msg << int(-1);
                  break;
              }

              event.push(*itRank, 1, msg);
            }
          }
          client->sendEvent(event);
       }
       else
       {
          client->sendEvent(event);
       }
    }
    else
    {
      for (map<int, CArray<size_t, 1> >::iterator it = grid->outLocalIndexStoreOnClient.begin(); 
                                                  it != grid->outLocalIndexStoreOnClient.end(); ++it)
      {
        CArray<size_t,1>& indexTmp = it->second;
        CArray<double,1> tmp(indexTmp.numElements());
        for (int idx = 0; idx < indexTmp.numElements(); ++idx)
        {
          tmp(idx) = recvDataSrv(indexTmp(idx));
        } 

        msgs.push_back(CMessage());
        CMessage& msg = msgs.back();
        msg << getId();
        switch (hasData)
        {
          case RF_DATA:
            msg << getNStep() - 1 << tmp;
            break;
          case RF_NODATA:
            msg << int(-2) << tmp;
            break;
          case RF_EOF:                  
          default:
            msg << int(-1);
            break;
        }

        event.push(it->first, grid->nbReadSenders[client][it->first], msg);
      }
      client->sendEvent(event);
    }
  }
  CATCH_DUMP_ATTR

  /*!
    Read field from a file.
    A field is read with the distribution of data on the server side
    \return State of field can be read from a file
  */
  CField::EReadField CField::readField(void)
  TRY
  {
    CContext* context = CContext::getCurrent();
    grid->computeWrittenIndex();
    getRelFile()->initRead();
    EReadField readState = RF_DATA;

    if (!getRelFile()->isEmptyZone())
    {      
      if (grid->doGridHaveDataToWrite() || getRelFile()->type == CFile::type_attr::one_file)      
      {
        if (0 == recvDataSrv.numElements())
        {            
          CArray<int,1>& storeClient = grid->storeIndex_client;          
          recvDataSrv.resize(storeClient.numElements());          
        }
        
        getRelFile()->checkReadFile();

        if (!nstepMax)
        {
          nstepMax = getRelFile()->getDataInput()->getFieldNbRecords(CField::get(this));
        }

        this->incrementNStep();

        if (getNStep() > nstepMax && (getRelFile()->cyclic.isEmpty() || !getRelFile()->cyclic) )
          readState = RF_EOF;

        if (RF_EOF != readState)
          getRelFile()->getDataInput()->readFieldData(CField::get(this));
      }
    }
    else
    {
      this->incrementNStep();
      if (getNStep() > nstepMax && (getRelFile()->cyclic.isEmpty() || !getRelFile()->cyclic) )
        readState = RF_EOF;
      else
        readState = RF_NODATA;

      if (!nstepMaxRead) // This can be a bug if we try to read field from zero time record
        readState = RF_NODATA;
    }

    if (!nstepMaxRead)
    {
       MPI_Allreduce(MPI_IN_PLACE, &nstepMax, 1, MPI_INT, MPI_MAX, context->server->intraComm);
       nstepMaxRead = true;
    }

    return readState;
  }
  CATCH_DUMP_ATTR

  /*
    Receive read data from server.
    At the moment, this function is called in the client side.
    In the future, this function can be called hiearachically (server n-1, server n -2, ..., client)
    \param event event containing read data
  */
  void CField::recvReadDataReady(CEventServer& event)
  TRY
  {
    string fieldId;
    vector<int> ranks;
    vector<CBufferIn*> buffers;

    list<CEventServer::SSubEvent>::iterator it;
    for (it = event.subEvents.begin(); it != event.subEvents.end(); ++it)
    {
      ranks.push_back(it->rank);
      CBufferIn* buffer = it->buffer;
      *buffer >> fieldId;
      buffers.push_back(buffer);
    }
    get(fieldId)->recvReadDataReady(ranks, buffers);
  }
  CATCH

  /*!
    Receive read data from server
    \param [in] ranks Ranks of sending processes
    \param [in] buffers buffers containing read data
  */
  void CField::recvReadDataReady(vector<int> ranks, vector<CBufferIn*> buffers)
  TRY
  {
    CContext* context = CContext::getCurrent();
    std::map<int, CArray<double,1> > data;
    const bool wasEOF = isEOF;

    for (int i = 0; i < ranks.size(); i++)
    {
      int rank = ranks[i];
      int record;
      *buffers[i] >> record;
      isEOF = (record == int(-1));

      if (!isEOF)
        *buffers[i] >> data[rank];
      else
        break;
    }

    if (wasDataAlreadyReceivedFromServer)
      lastDataReceivedFromServer = lastDataReceivedFromServer + file->output_freq;
    else
    {
      lastDataReceivedFromServer = context->getCalendar()->getInitDate();
      wasDataAlreadyReceivedFromServer = true;
    }

    if (isEOF)
    {
      if (!wasEOF)
        dateEOF = lastDataReceivedFromServer;

      serverSourceFilter->signalEndOfStream(lastDataReceivedFromServer);
    }
    else
      serverSourceFilter->streamDataFromServer(lastDataReceivedFromServer, data);
  }
  CATCH_DUMP_ATTR

  void CField::checkForLateDataFromServer(void)
  TRY
  {
    CContext* context = CContext::getCurrent();
    const CDate& currentDate = context->getCalendar()->getCurrentDate();

    // Check if data previously requested has been received as expected
    if (wasDataRequestedFromServer && !isEOF)
    {
      CTimer timer("CField::checkForLateDataFromServer");

      bool isDataLate;
      do
      {
        const CDate nextDataDue = wasDataAlreadyReceivedFromServer ? (lastDataReceivedFromServer + file->output_freq) : context->getCalendar()->getInitDate();
        isDataLate = (nextDataDue <= currentDate);

        if (isDataLate)
        {
          timer.resume();

          context->checkBuffersAndListen();

          timer.suspend();
        }
      }
      while (isDataLate && timer.getCumulatedTime() < CXios::recvFieldTimeout);

      if (isDataLate)
        ERROR("void CField::checkForLateDataFromServer(void)",
              << "Late data at timestep = " << currentDate);
    }
  }
  CATCH_DUMP_ATTR

  void CField::checkIfMustAutoTrigger(void)
  TRY
  {
    mustAutoTrigger = serverSourceFilter ? serverSourceFilter->mustAutoTrigger() : false;
  }
  CATCH_DUMP_ATTR

  void CField::autoTriggerIfNeeded(void)
  TRY
  {
    if (mustAutoTrigger)
      serverSourceFilter->trigger(CContext::getCurrent()->getCalendar()->getCurrentDate());
  }
  CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   void CField::setRelFile(CFile* _file)
   TRY
   {
      this->file = _file;
      hasOutputFile = true;
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   StdString CField::GetName(void)    { return StdString("field"); }
   StdString CField::GetDefName(void) { return CField::GetName(); }
   ENodeType CField::GetType(void)    { return eField; }

   //----------------------------------------------------------------

   CGrid* CField::getRelGrid(void) const
   TRY
   {
      return this->grid;
   }
   CATCH

   //----------------------------------------------------------------

   CFile* CField::getRelFile(void) const
   TRY
   {
      return this->file;
   }
   CATCH

   int CField::getNStep(void) const
   TRY
   {
      return this->nstep;
   }
   CATCH

   func::CFunctor::ETimeType CField::getOperationTimeType() const
   TRY
   {
     return operationTimeType;
   }
   CATCH

   //----------------------------------------------------------------

   void CField::incrementNStep(void)
   TRY
   {
      this->nstep++;
   }
   CATCH_DUMP_ATTR

   void CField::resetNStep(int nstep /*= 0*/)
   TRY
   {
      this->nstep = nstep;
   }
   CATCH_DUMP_ATTR

   void CField::resetNStepMax(void)
   TRY
   {
      this->nstepMax = 0;
      nstepMaxRead = false;
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   bool CField::isActive(bool atCurrentTimestep /*= false*/) const
   TRY
   {
      if (clientSourceFilter)
        return atCurrentTimestep ? clientSourceFilter->isDataExpected(CContext::getCurrent()->getCalendar()->getCurrentDate()) : true;
      else if (storeFilter)
        return true;
      else if (instantDataFilter)
        ERROR("bool CField::isActive(bool atCurrentTimestep)",
              << "Impossible to check if field [ id = " << getId() << " ] is active as it cannot be used to receive nor send data.");

      return false;
   }
   CATCH

   //----------------------------------------------------------------

   bool CField::wasWritten() const
   TRY
   {
     return written;
   }
   CATCH

   void CField::setWritten()
   TRY
   {
     written = true;
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   bool CField::getUseCompressedOutput() const
   TRY
   {
     return useCompressedOutput;
   }
   CATCH

   void CField::setUseCompressedOutput()
   TRY
   {
     useCompressedOutput = true;
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   std::shared_ptr<COutputPin> CField::getInstantDataFilter()
   TRY
   {
     return instantDataFilter;
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   /*!
     Build up graph of grids which plays role of destination and source in grid transformation
     This function should be called before \func solveGridReference()
   */
   void CField::buildGridTransformationGraph()
   TRY
   {
     CContext* context = CContext::getCurrent();
     if (context->hasClient && !context->hasServer)
     {
       if (grid && !grid->isTransformed() && hasDirectFieldReference() && grid != getDirectFieldReference()->grid)
       {
         grid->addTransGridSource(getDirectFieldReference()->grid);
       }
     }
   }
   CATCH_DUMP_ATTR

   /*!
     Generate a new grid destination if there are more than one grid source pointing to a same grid destination
   */
   void CField::generateNewTransformationGridDest()
   TRY
   {
     CContext* context = CContext::getCurrent();
     if (context->hasClient && !context->hasServer)
     {
       std::map<CGrid*,std::pair<bool,StdString> >& gridSrcMap = grid->getTransGridSource();
       if (1 < gridSrcMap.size())
       {
         // Search for grid source
         CGrid* gridSrc = grid;
         CField* currField = this;
         std::vector<CField*> hieraField;

         while (currField->hasDirectFieldReference() && (gridSrc == grid))
         {
           hieraField.push_back(currField);
           CField* tmp = currField->getDirectFieldReference();
           currField = tmp;
           gridSrc = currField->grid;
         }

         if (gridSrcMap.end() != gridSrcMap.find(gridSrc))
         {
           CGrid* gridTmp;
           std::pair<bool,StdString> newGridDest = gridSrcMap[gridSrc];
           if (newGridDest.first)
           {
             StdString newIdGridDest = newGridDest.second;
             if (!CGrid::has(newIdGridDest))
             {
                ERROR("CGrid* CGrid::generateNewTransformationGridDest()",
                  << " Something wrong happened! Grid whose id " << newIdGridDest
                  << "should exist ");
             }
             gridTmp = CGrid::get(newIdGridDest);
           }
           else
           {
             StdString newIdGridDest = CGrid::generateId(gridSrc, grid);
             gridTmp = CGrid::cloneGrid(newIdGridDest, grid);

             (gridSrcMap[gridSrc]).first = true;
             (gridSrcMap[gridSrc]).second = newIdGridDest;
           }

           // Update all descendants
           for (std::vector<CField*>::iterator it = hieraField.begin(); it != hieraField.end(); ++it)
           {
             (*it)->grid = gridTmp;
             (*it)->updateRef((*it)->grid);
           }
         }
       }
     }
   }
   CATCH_DUMP_ATTR

   void CField::updateRef(CGrid* grid)
   TRY
   {
     if (!grid_ref.isEmpty()) grid_ref.setValue(grid->getId());
     else
     {
       std::vector<CAxis*> axisTmp = grid->getAxis();
       std::vector<CDomain*> domainTmp = grid->getDomains();
       if ((1<axisTmp.size()) || (1<domainTmp.size()))
         ERROR("void CField::updateRef(CGrid* grid)",
           << "More than one domain or axis is available for domain_ref/axis_ref of field " << this->getId());

       if ((!domain_ref.isEmpty()) && (domainTmp.empty()))
         ERROR("void CField::updateRef(CGrid* grid)",
           << "Incoherent between available domain and domain_ref of field " << this->getId());
       if ((!axis_ref.isEmpty()) && (axisTmp.empty()))
         ERROR("void CField::updateRef(CGrid* grid)",
           << "Incoherent between available axis and axis_ref of field " << this->getId());

       if (!domain_ref.isEmpty()) domain_ref.setValue(domainTmp[0]->getId());
       if (!axis_ref.isEmpty()) axis_ref.setValue(axisTmp[0]->getId());
     }
   }
   CATCH_DUMP_ATTR
   
   /*!
     Solve reference of all enabled fields even the source fields .
     In this step, we do transformations.
   */
   void CField::solveAllEnabledFieldsAndTransform()
   TRY
   {
     CContext* context = CContext::getCurrent();
     bool hasClient = context->hasClient;
     bool hasServer = context->hasServer;

     if (!isReferenceSolvedAndTransformed)
     {
        isReferenceSolvedAndTransformed = true;

        if (hasClient && !hasServer)
        {
          solveRefInheritance(true);
          if (hasDirectFieldReference()) getDirectFieldReference()->solveAllEnabledFieldsAndTransform();
        }

        if (hasServer)
          solveServerOperation();

        solveGridReference();

        if (hasClient && !hasServer)
       {
         solveGenerateGrid();
         buildGridTransformationGraph();
       }

       solveGridDomainAxisRef(false);

       if (hasClient && !hasServer)
       {
         solveTransformedGrid();
       }

       solveGridDomainAxisRef(false);
     }
   }
   CATCH_DUMP_ATTR

   void CField::checkGridOfEnabledFields()
   TRY
   {
     if (!isGridChecked)
     {
       isGridChecked = true;
       solveCheckMaskIndex(false);
     }
   }
   CATCH_DUMP_ATTR

   void CField::sendGridComponentOfEnabledFields()
   TRY
   {
      solveGridDomainAxisRef(true);
      // solveCheckMaskIndex(true);
   }
   CATCH_DUMP_ATTR

   void CField::sendGridOfEnabledFields()
   TRY
   {
      // solveGridDomainAxisRef(true);
      solveCheckMaskIndex(true);
   }   
   CATCH_DUMP_ATTR

   void CField::solveOnlyReferenceEnabledField(bool doSending2Server)
   TRY
   {
     CContext* context = CContext::getCurrent();
     if (!isReferenceSolved)
     {
        isReferenceSolved = true;

        if (context->hasClient && !context->hasServer)
        {
          solveRefInheritance(true);
          if (hasDirectFieldReference()) getDirectFieldReference()->solveOnlyReferenceEnabledField(false);
        }

        if (context->hasServer)
          solveServerOperation();

        solveGridReference();
        grid->solveDomainAxisRefInheritance(true); // make it again to solve grid reading from file

        if (context->hasClient && !context->hasServer)
       {
         solveGenerateGrid();
         buildGridTransformationGraph();
       }
     }
   }
   CATCH_DUMP_ATTR

   void CField::solveAllReferenceEnabledField(bool doSending2Server)
   TRY
   {
     CContext* context = CContext::getCurrent();
     solveOnlyReferenceEnabledField(doSending2Server);

     if (!areAllReferenceSolved)
     {
        areAllReferenceSolved = true;
       
        if (context->hasClient && !context->hasServer)
        {
          solveRefInheritance(true);
          if (hasDirectFieldReference()) getDirectFieldReference()->solveAllReferenceEnabledField(false);
        }
        else if (context->hasServer)
          solveServerOperation();

        solveGridReference();
     }

     solveGridDomainAxisRef(doSending2Server);

     if (context->hasClient && !context->hasServer)
     {
       solveTransformedGrid();
     }

     solveCheckMaskIndex(doSending2Server);
   }
   CATCH_DUMP_ATTR

   std::map<int, StdSize> CField::getGridAttributesBufferSize(CContextClient* client, bool bufferForWriting /*= "false"*/)
   TRY
   {
     return grid->getAttributesBufferSize(client, bufferForWriting);
   }
   CATCH_DUMP_ATTR

   std::map<int, StdSize> CField::getGridDataBufferSize(CContextClient* client, bool bufferForWriting /*= "false"*/)
   TRY
   {
     return grid->getDataBufferSize(client, getId(), bufferForWriting);
   }
   CATCH_DUMP_ATTR

   size_t CField::getGlobalWrittenSize()
   TRY
   {
     return grid->getGlobalWrittenSize();
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   void CField::solveServerOperation(void)
   TRY
   {
      CContext* context = CContext::getCurrent();

      if (!context->hasServer || !hasOutputFile) return;

      if (freq_op.isEmpty())
        freq_op.setValue(TimeStep);

      if (freq_offset.isEmpty())
        freq_offset.setValue(NoneDu);

      freq_operation_srv = file->output_freq.getValue();
      freq_write_srv     = file->output_freq.getValue();

      lastlast_Write_srv = context->getCalendar()->getInitDate();
      last_Write_srv     = context->getCalendar()->getInitDate();
      last_operation_srv = context->getCalendar()->getInitDate();

      const CDuration toffset = freq_operation_srv - freq_offset.getValue() - context->getCalendar()->getTimeStep();
      last_operation_srv     = last_operation_srv - toffset;

      if (operation.isEmpty())
        ERROR("void CField::solveServerOperation(void)",
              << "An operation must be defined for field \"" << getId() << "\".");

      std::shared_ptr<func::CFunctor> functor;
      CArray<double, 1> dummyData;

#define DECLARE_FUNCTOR(MType, mtype) \
      if (operation.getValue().compare(#mtype) == 0) \
      { \
        functor.reset(new func::C##MType(dummyData)); \
      }

#include "functor_type.conf"

      if (!functor)
        ERROR("void CField::solveServerOperation(void)",
              << "\"" << operation << "\" is not a valid operation.");

      operationTimeType = functor->timeType();
   }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------

   /*!
    * Constructs the graph filter for the field, enabling or not the data output.
    * This method should not be called more than once with enableOutput equal to true.
    *
    * \param gc the garbage collector to use when building the filter graph
    * \param enableOutput must be true when the field data is to be
    *                     read by the client or/and written to a file
    */
   void CField::buildFilterGraph(CGarbageCollector& gc, bool enableOutput, Time start_graph, Time end_graph)
   TRY
   {     
     if (!isReferenceSolvedAndTransformed) solveAllEnabledFieldsAndTransform();
     if (!isGridChecked) checkGridOfEnabledFields();

     const bool detectMissingValues = (!detect_missing_value.isEmpty() && !default_value.isEmpty() && detect_missing_value == true);
     
     const bool buildWorkflowGraph = (!build_workflow_graph.isEmpty() && build_workflow_graph == true);
     if(buildWorkflowGraph && this->operation.getValue()=="once") 
     {
       CDuration tmp_dur = 0;
       tmp_dur.timestep = 1;
       this->build_workflow_graph_start.setValue(tmp_dur) ;
       this->build_workflow_graph_end.setValue(tmp_dur) ;
     }
     
     const double defaultValue  = detectMissingValues ? default_value : (!default_value.isEmpty() ? default_value : 0.0);

     CContext* context = CContext::getCurrent();
     
     Time filter_start;
     if(!build_workflow_graph_start.isEmpty() && buildWorkflowGraph) filter_start = context->calendar->getInitDate()+build_workflow_graph_start;
     else if(build_workflow_graph_start.isEmpty() && buildWorkflowGraph) filter_start = 0;
     else filter_start = -1;

     Time filter_end;
     if(!build_workflow_graph_end.isEmpty() && buildWorkflowGraph) filter_end = context->calendar->getInitDate()+build_workflow_graph_end;
     else if(build_workflow_graph_end.isEmpty() && buildWorkflowGraph) filter_end = 9223372036854775807;
     else filter_end = -1;

     if(this->field_graph_start==-2) this->field_graph_start = filter_start;
     if(this->field_graph_end==-2) this->field_graph_end = filter_end;         // init


     if(start_graph == -1)
     {
       //nothing
     }
     else //if(start_graph != -1)
     {
       if(this->field_graph_start == -1) this->field_graph_start = start_graph;
       else this->field_graph_start = min(this->field_graph_start, start_graph);
     }


     if(end_graph == -1)
     {
       //nothing
     }
     else
     {
       if(this->field_graph_end == -1) this->field_graph_end = end_graph;
       else this->field_graph_end = max(this->field_graph_end, end_graph);

     }
    

     filter_start = this->field_graph_start;
     filter_end = this->field_graph_end;

     

     bool hasWriterServer = context->hasServer && !context->hasClient;
     bool hasIntermediateServer = context->hasServer && context->hasClient;

     if (hasWriterServer)
     {
        if (!instantDataFilter)
          instantDataFilter = clientSourceFilter = std::shared_ptr<CSourceFilter>(new CSourceFilter(gc, grid, true, false));


       // If the field data is to be read by the client or/and written to a file
       if (enableOutput && !storeFilter && !fileWriterFilter)
       {
         if (file && (file->mode.isEmpty() || file->mode == CFile::mode_attr::write))
         {
           fileServerWriterFilter = std::shared_ptr<CFileServerWriterFilter>(new CFileServerWriterFilter(gc, this));
           instantDataFilter->connectOutput(fileServerWriterFilter, 0);
         }
       }
     }
     else if (hasIntermediateServer)
     {
       if (!instantDataFilter)
         instantDataFilter = clientSourceFilter = std::shared_ptr<CSourceFilter>(new CSourceFilter(gc, grid, false, false));

             // If the field data is to be read by the client or/and written to a file
       if (enableOutput && !storeFilter && !fileWriterFilter)
       {
         if (file && (file->mode.isEmpty() || file->mode == CFile::mode_attr::write))
         {
           fileWriterFilter = std::shared_ptr<CFileWriterFilter>(new CFileWriterFilter(gc, this));
           instantDataFilter->connectOutput(fileWriterFilter, 0);
         }
       }
     }
     else
     {
       // Start by building a filter which can provide the field's instant data
       if (!instantDataFilter)
       {
         // Check if we have an expression to parse
         if (hasExpression())
         {
           boost::scoped_ptr<IFilterExprNode> expr(parseExpr(getExpression() + '\0'));
           std::shared_ptr<COutputPin> filter = expr->reduce(gc, *this, filter_start, filter_end);

           // Check if a spatial transformation is needed
           if (!field_ref.isEmpty())
           {
             CGrid* gridRef = CField::get(field_ref)->grid;

             if (grid && grid != gridRef && grid->hasTransform())
             {
               std::pair<std::shared_ptr<CFilter>, std::shared_ptr<CFilter> > filters = CSpatialTransformFilter::buildFilterGraph(gc, gridRef, grid, detectMissingValues, defaultValue);

               filter->connectOutput(filters.first, 0);
               filter = filters.second;
             }
           }

           instantDataFilter = filter;
           instantDataFilter->field = this;
           filter->tag = buildWorkflowGraph;
           
           filter->start_graph = filter_start;
           filter->end_graph = filter_end;

           for(int i=0; i<filter->parent_filters.size(); i++)
           {
             filter->tag = filter->tag || filter->parent_filters[i]->tag;
           }
         }
         // Check if we have a reference on another field
         else if (!field_ref.isEmpty())
         {
           instantDataFilter = getFieldReference(gc, filter_start, filter_end);
           instantDataFilter->tag = buildWorkflowGraph;
           instantDataFilter->start_graph = filter_start;
           instantDataFilter->end_graph = filter_end;
         }
         // Check if the data is to be read from a file
         else if (file && !file->mode.isEmpty() && file->mode == CFile::mode_attr::read)
         {
           checkTimeAttributes();
           instantDataFilter = serverSourceFilter = std::shared_ptr<CSourceFilter>(new CSourceFilter(gc, grid, true, false, freq_offset, true,
                                                                                                       detectMissingValues, defaultValue));
           instantDataFilter->tag = buildWorkflowGraph;
           instantDataFilter->start_graph = filter_start;
           instantDataFilter->end_graph = filter_end;
           instantDataFilter->field = this;

         }
         else // The data might be passed from the model
         {
            if (check_if_active.isEmpty()) check_if_active = false; 
            instantDataFilter = clientSourceFilter = std::shared_ptr<CSourceFilter>(new CSourceFilter(gc, grid, false, true, NoneDu, false,
                                                                                                      detectMissingValues, defaultValue)); 
            instantDataFilter->tag = buildWorkflowGraph;
            instantDataFilter->start_graph = filter_start;
            instantDataFilter->end_graph = filter_end;
            instantDataFilter->field = this;
         }
       }

       // If the field data is to be read by the client or/and written to a file
       if (enableOutput && !storeFilter && !fileWriterFilter)
       {
         if (!read_access.isEmpty() && read_access)
         {
           storeFilter = std::shared_ptr<CStoreFilter>(new CStoreFilter(gc, CContext::getCurrent(), grid,
                                                                          detectMissingValues, defaultValue));
           instantDataFilter->connectOutput(storeFilter, 0);

           storeFilter->tag = (instantDataFilter->tag || buildWorkflowGraph);
           instantDataFilter->start_graph = filter_start;
           instantDataFilter->end_graph = filter_end;

           instantDataFilter->setParentFiltersTag();
           storeFilter->start_graph = filter_start;
           storeFilter->end_graph = filter_end;
           storeFilter->field = this;
           storeFilter->distance = instantDataFilter->distance+1;
         }

         if (file && (file->mode.isEmpty() || file->mode == CFile::mode_attr::write))
         {
           fileWriterFilter = std::shared_ptr<CFileWriterFilter>(new CFileWriterFilter(gc, this));
           getTemporalDataFilter(gc, file->output_freq)->connectOutput(fileWriterFilter, 0);
           
           fileWriterFilter->tag = (getTemporalDataFilter(gc, file->output_freq)->tag || buildWorkflowGraph);
           getTemporalDataFilter(gc, file->output_freq)->start_graph = filter_start;
           getTemporalDataFilter(gc, file->output_freq)->end_graph = filter_end;
           getTemporalDataFilter(gc, file->output_freq)->tag = buildWorkflowGraph;
           getTemporalDataFilter(gc, file->output_freq)->setParentFiltersTag();
           fileWriterFilter->start_graph = filter_start;
           fileWriterFilter->end_graph = filter_end;
           fileWriterFilter->distance = getTemporalDataFilter(gc, file->output_freq)->distance+1;


         }
       }
     }
   }
   CATCH_DUMP_ATTR

   /*!
    * Returns the filter needed to handle the field reference.
    * This method should only be called when building the filter graph corresponding to the field.
    *
    * \param gc the garbage collector to use
    * \return the output pin corresponding to the field reference
    */
   std::shared_ptr<COutputPin> CField::getFieldReference(CGarbageCollector& gc, Time start_graph, Time end_graph)
   TRY
   {
     if (instantDataFilter || field_ref.isEmpty())
       ERROR("COutputPin* CField::getFieldReference(CGarbageCollector& gc)",
             "Impossible to get the field reference for a field which has already been parsed or which does not have a field_ref.");

     CField* fieldRef = CField::get(field_ref);
     fieldRef->buildFilterGraph(gc, false, start_graph, end_graph);
     const bool buildWorkflowGraph = (!build_workflow_graph.isEmpty() && build_workflow_graph == true);

     CContext* context = CContext::getCurrent();

     Time filter_start;
     if(!build_workflow_graph_start.isEmpty() && buildWorkflowGraph) filter_start = context->calendar->getInitDate()+build_workflow_graph_start;
     else if(build_workflow_graph_start.isEmpty() && buildWorkflowGraph) filter_start = 0;
     else filter_start = -1;

     Time filter_end;
     if(!build_workflow_graph_end.isEmpty() && buildWorkflowGraph) filter_end = context->calendar->getInitDate()+build_workflow_graph_end;
     else if(build_workflow_graph_end.isEmpty() && buildWorkflowGraph) filter_end = 9223372036854775807;
     else filter_end = -1;

     if(this->field_graph_start==-2) this->field_graph_start = filter_start;
     if(this->field_graph_end==-2) this->field_graph_end = filter_end;         // init


     if(start_graph == -1)
     {
       //nothing
     }
     else //if(start_graph != -1)
     {
       if(this->field_graph_start == -1) this->field_graph_start = start_graph;
       else this->field_graph_start = min(this->field_graph_start, start_graph);
     }

     if(end_graph == -1)
     {
       //nothing
     }
     else
     {
       if(this->field_graph_end == -1) this->field_graph_end = end_graph;
       else this->field_graph_end = max(this->field_graph_end, end_graph);
     }

     filter_start = this->field_graph_start;
     filter_end = this->field_graph_end;


     std::pair<std::shared_ptr<CFilter>, std::shared_ptr<CFilter> > filters;
     // Check if a spatial transformation is needed
     if (grid && grid != fieldRef->grid && grid->hasTransform())
     {       
       bool hasMissingValue = (!detect_missing_value.isEmpty() && !default_value.isEmpty() && detect_missing_value == true);
       double defaultValue  = hasMissingValue ? default_value : (!default_value.isEmpty() ? default_value : 0.0);                                
       filters = CSpatialTransformFilter::buildFilterGraph(gc, fieldRef->grid, grid, hasMissingValue, defaultValue);

       fieldRef->getInstantDataFilter()->connectOutput(filters.first, 0);

     

       filters.second->parent_filters.resize(1);
       filters.second->parent_filters[0]= fieldRef->getInstantDataFilter();

       filters.second->tag = (buildWorkflowGraph || filters.second->parent_filters[0]->tag);
       
       filters.second->start_graph = filter_start;
       filters.second->end_graph = filter_end;
       filters.second->field = this;
       
     }
     else
     {
       filters.first = filters.second = std::shared_ptr<CFilter>(new CPassThroughFilter(gc));

       fieldRef->getInstantDataFilter()->connectOutput(filters.first, 0);
     

       filters.second->parent_filters.resize(1);
       filters.second->parent_filters[0]= fieldRef->getInstantDataFilter();

       filters.second->tag = (buildWorkflowGraph || filters.second->parent_filters[0]->tag);

       filters.second->start_graph = filter_start;
       filters.second->end_graph = filter_end;
       filters.second->field = this;

     }

     return filters.second;
   }
   CATCH_DUMP_ATTR

   /*!
    * Returns the filter needed to handle a self reference in the field's expression.
    * If the needed filter does not exist, it is created, otherwise it is reused.
    * This method should only be called when building the filter graph corresponding
    * to the field's expression.
    *
    * \param gc the garbage collector to use
    * \return the output pin corresponding to a self reference
    */
   std::shared_ptr<COutputPin> CField::getSelfReference(CGarbageCollector& gc, Time start_graph, Time end_graph)
   TRY
   {

     if (instantDataFilter || !hasExpression())
       ERROR("COutputPin* CField::getSelfReference(CGarbageCollector& gc)",
             "Impossible to add a self reference to a field which has already been parsed or which does not have an expression.");
     
     bool buildWorkflowGraph = (!build_workflow_graph.isEmpty() && build_workflow_graph == true);

     if (!selfReferenceFilter)
     {
       const bool detectMissingValues = (!detect_missing_value.isEmpty() && !default_value.isEmpty() && detect_missing_value == true);
       const double defaultValue  = detectMissingValues ? default_value : (!default_value.isEmpty() ? default_value : 0.0);

       if (file && !file->mode.isEmpty() && file->mode == CFile::mode_attr::read)
       {
         if (!serverSourceFilter)
         {
           checkTimeAttributes();
           serverSourceFilter = std::shared_ptr<CSourceFilter>(new CSourceFilter(gc, grid, true, false, freq_offset, true,
                                                                                   detectMissingValues, defaultValue));
         }

         selfReferenceFilter = serverSourceFilter;
       }
       else if (!field_ref.isEmpty())
       {
         CField* fieldRef = CField::get(field_ref);
         fieldRef->buildFilterGraph(gc, false);
         selfReferenceFilter = fieldRef->getInstantDataFilter();
       }
       else
       {
         if (!clientSourceFilter)
         {
           if (check_if_active.isEmpty()) check_if_active = false;
           clientSourceFilter = std::shared_ptr<CSourceFilter>(new CSourceFilter(gc, grid, true, true, NoneDu, false,
                                                                                   detectMissingValues, defaultValue));
         }

         selfReferenceFilter = clientSourceFilter;
       }
     }

     selfReferenceFilter->tag = buildWorkflowGraph;
     selfReferenceFilter->field = this;
     return selfReferenceFilter;
   }
   CATCH_DUMP_ATTR

   /*!
    * Returns the temporal filter corresponding to the field's temporal operation
    * for the specified operation frequency. The filter is created if it does not
    * exist, otherwise it is reused.
    *
    * \param gc the garbage collector to use
    * \param outFreq the operation frequency, i.e. the frequency at which the output data will be computed
    * \return the output pin corresponding to the requested temporal filter
    */
   std::shared_ptr<COutputPin> CField::getTemporalDataFilter(CGarbageCollector& gc, CDuration outFreq)
   TRY
   {
     std::map<CDuration, std::shared_ptr<COutputPin> >::iterator it = temporalDataFilters.find(outFreq);
     const bool buildWorkflowGraph = (!build_workflow_graph.isEmpty() && build_workflow_graph == true);

     CContext* context = CContext::getCurrent();


     if (it == temporalDataFilters.end())
     {
       if (operation.isEmpty())
         ERROR("void CField::getTemporalDataFilter(CGarbageCollector& gc, CDuration outFreq)",
               << "An operation must be defined for field \"" << getId() << "\".");

       checkTimeAttributes(&outFreq);

       const bool detectMissingValues = (!detect_missing_value.isEmpty()  && detect_missing_value == true);
       std::shared_ptr<CTemporalFilter> temporalFilter(new CTemporalFilter(gc, operation,
                                                                             CContext::getCurrent()->getCalendar()->getInitDate(),
                                                                             freq_op, freq_offset, outFreq, detectMissingValues));

       instantDataFilter->connectOutput(temporalFilter, 0);
       
       temporalFilter->parent_filters.resize(1);
       temporalFilter->parent_filters[0] = instantDataFilter;
       

       temporalFilter->tag = temporalFilter->parent_filters[0]->tag;
       temporalFilter->start_graph = temporalFilter->parent_filters[0]->start_graph;
       temporalFilter->end_graph = temporalFilter->parent_filters[0]->end_graph;

       temporalFilter->field = this;

       it = temporalDataFilters.insert(std::make_pair(outFreq, temporalFilter)).first;
     }

     return it->second;
   }
   CATCH_DUMP_ATTR

  /*!
    * Returns the temporal filter corresponding to the field's temporal operation
    * for the specified operation frequency.
    *
    * \param gc the garbage collector to use
    * \param outFreq the operation frequency, i.e. the frequency at which the output data will be computed
    * \return the output pin corresponding to the requested temporal filter
    */
   
   std::shared_ptr<COutputPin> CField::getSelfTemporalDataFilter(CGarbageCollector& gc, CDuration outFreq)
   TRY
   {
     if (instantDataFilter || !hasExpression())
       ERROR("COutputPin* CField::getSelfTemporalDataFilter(CGarbageCollector& gc)",
             "Impossible to add a self reference to a field which has already been parsed or which does not have an expression.");

     if (!selfReferenceFilter) getSelfReference(gc) ;

     if (serverSourceFilter || clientSourceFilter)
     {
       if (operation.isEmpty())
         ERROR("void CField::getSelfTemporalDataFilter(CGarbageCollector& gc, CDuration outFreq)",
               << "An operation must be defined for field \"" << getId() << "\".");

       checkTimeAttributes(&outFreq);

       const bool detectMissingValues = (!detect_missing_value.isEmpty() && detect_missing_value == true);
       bool buildWorkflowGraph = (!build_workflow_graph.isEmpty() && build_workflow_graph == true);
       std::shared_ptr<CTemporalFilter> temporalFilter(new CTemporalFilter(gc, operation,
                                                                           CContext::getCurrent()->getCalendar()->getInitDate(),
                                                                           freq_op, freq_offset, outFreq, detectMissingValues));

       selfReferenceFilter->connectOutput(temporalFilter, 0);
       temporalFilter->tag = buildWorkflowGraph;
       temporalFilter->field = this;

       return temporalFilter ;
     }
     else if (!field_ref.isEmpty())
     {
       CField* fieldRef = CField::get(field_ref);
       fieldRef->buildFilterGraph(gc, false); 
       return fieldRef->getTemporalDataFilter(gc, outFreq) ;
     }
  }
   CATCH_DUMP_ATTR

   //----------------------------------------------------------------
/*
   void CField::fromBinary(StdIStream& is)
   {
      SuperClass::fromBinary(is);
#define CLEAR_ATT(name_)\
      SuperClassAttribute::operator[](#name_)->reset()

         CLEAR_ATT(domain_ref);
         CLEAR_ATT(axis_ref);
#undef CLEAR_ATT

   }
*/
   //----------------------------------------------------------------

   void CField::solveGridReference(void)
   TRY
   {
      if (grid_ref.isEmpty() && domain_ref.isEmpty() && axis_ref.isEmpty() && scalar_ref.isEmpty())
      {
        ERROR("CField::solveGridReference(void)",
              << "A grid must be defined for field '" << getFieldOutputName() << "' .");
      }
      else if (!grid_ref.isEmpty() && (!domain_ref.isEmpty() || !axis_ref.isEmpty() || !scalar_ref.isEmpty()))
      {
        ERROR("CField::solveGridReference(void)",
              << "Field '" << getFieldOutputName() << "' has both a grid and a domain/axis/scalar." << std::endl
              << "Please define either 'grid_ref' or 'domain_ref'/'axis_ref'/'scalar_ref'.");
      }

      if (grid_ref.isEmpty())
      {
        std::vector<CDomain*> vecDom;
        std::vector<CAxis*> vecAxis;
        std::vector<CScalar*> vecScalar;
        std::vector<int> axisDomainOrderTmp;

        std::vector<CDomain*> vecDomRef;
        std::vector<CAxis*> vecAxisRef;
        std::vector<CScalar*> vecScalarRef;

        
        if (!domain_ref.isEmpty())
        {
          StdString tmp = domain_ref.getValue();
          if (CDomain::has(domain_ref))
          {
            vecDom.push_back(CDomain::get(domain_ref));
            vecDomRef.push_back(CDomain::createDomain());
            vecDomRef.back()->domain_ref=domain_ref;
            axisDomainOrderTmp.push_back(2);
          }
          else  ERROR("CField::solveGridReference(void)",
                      << "Invalid reference to domain '" << domain_ref.getValue() << "'.");
        }

        if (!axis_ref.isEmpty())
        {
          if (CAxis::has(axis_ref))
          {
            vecAxis.push_back(CAxis::get(axis_ref));
            vecAxisRef.push_back(CAxis::createAxis());
            vecAxisRef.back()->axis_ref=axis_ref;
            axisDomainOrderTmp.push_back(1);
          }
          else  ERROR("CField::solveGridReference(void)",
                      << "Invalid reference to axis '" << axis_ref.getValue() << "'.");
        }

        if (!scalar_ref.isEmpty())
        {
          if (CScalar::has(scalar_ref))
          {
            vecScalar.push_back(CScalar::get(scalar_ref));
            vecScalarRef.push_back(CScalar::createScalar());
            vecScalarRef.back()->scalar_ref=scalar_ref;
            axisDomainOrderTmp.push_back(0);
          }
          else ERROR("CField::solveGridReference(void)",
                     << "Invalid reference to scalar '" << scalar_ref.getValue() << "'.");
        }
        
        CArray<int,1> axisDomainOrder(axisDomainOrderTmp.size());
        for (int idx = 0; idx < axisDomainOrderTmp.size(); ++idx)
        {
          axisDomainOrder(idx) = axisDomainOrderTmp[idx];
        }

        // Warning: the gridId shouldn't be set as the grid_ref since it could be inherited
        StdString gridId = CGrid::generateId(vecDom, vecAxis, vecScalar,axisDomainOrder);
        if (CGrid::has(gridId)) this->grid = CGrid::get(gridId);
        else  this->grid = CGrid::createGrid(gridId, vecDomRef, vecAxisRef, vecScalarRef,axisDomainOrder);
      }
      else
      {
        if (CGrid::has(grid_ref)) this->grid = CGrid::get(grid_ref);
        else  ERROR("CField::solveGridReference(void)",
                     << "Invalid reference to grid '" << grid_ref.getValue() << "'.");
      }
   }
   CATCH_DUMP_ATTR

   void CField::solveGridDomainAxisRef(bool checkAtt)
   TRY
   {
     grid->solveDomainAxisRef(checkAtt);
   }
   CATCH_DUMP_ATTR

   void CField::solveCheckMaskIndex(bool doSendingIndex)
   TRY
   {
     grid->checkMaskIndex(doSendingIndex);
   }
   CATCH_DUMP_ATTR

   void CField::solveTransformedGrid()
   TRY
   {
     if (grid && !grid->isTransformed() && hasDirectFieldReference() && grid != getDirectFieldReference()->grid)
     {
       std::vector<CGrid*> grids;
       // Source grid
       grids.push_back(getDirectFieldReference()->grid);
       // Intermediate grids
       if (!grid_path.isEmpty())
       {
         std::string gridId;
         size_t start = 0, end;

         do
         {
           end = grid_path.getValue().find(',', start);
           if (end != std::string::npos)
           {
             gridId = grid_path.getValue().substr(start, end - start);
             start = end + 1;
           }
           else
             gridId = grid_path.getValue().substr(start);

           if (!CGrid::has(gridId))
             ERROR("void CField::solveTransformedGrid()",
                   << "Invalid grid_path, the grid '" << gridId << "' does not exist.");

           grids.push_back(CGrid::get(gridId));
         }
         while (end != std::string::npos);
       }
       // Destination grid
       grids.push_back(grid);

       for (size_t i = 0, count = grids.size() - 1; i < count; ++i)
       {
         CGrid *gridSrc  = grids[i];
         CGrid *gridDest = grids[i + 1];
         if (!gridDest->isTransformed())
           gridDest->transformGrid(gridSrc);
       }
     }
     else if (grid && grid->hasTransform() && !grid->isTransformed())
     {
       // Temporarily deactivate the self-transformation of grid
       // grid->transformGrid(grid);
     }
   }
   CATCH_DUMP_ATTR

   void CField::solveGenerateGrid()
   TRY
   {
     if (grid && !grid->isTransformed() && hasDirectFieldReference() && grid != getDirectFieldReference()->grid)
       grid->completeGrid(getDirectFieldReference()->grid);
     else
       grid->completeGrid();
   }
   CATCH_DUMP_ATTR

   void CField::solveGridDomainAxisBaseRef()
   TRY
   {
     grid->solveDomainAxisRef(false);
     grid->solveDomainAxisBaseRef();
   }
   CATCH_DUMP_ATTR

   ///-------------------------------------------------------------------

   template <>
   void CGroupTemplate<CField, CFieldGroup, CFieldAttributes>::solveRefInheritance(void)
   TRY
   {
      if (this->group_ref.isEmpty()) return;
      StdString gref = this->group_ref.getValue();

      if (!CFieldGroup::has(gref))
         ERROR("CGroupTemplate<CField, CFieldGroup, CFieldAttributes>::solveRefInheritance(void)",
               << "[ gref = " << gref << "]"
               << " invalid group name !");

      CFieldGroup* group = CFieldGroup::get(gref);
      CFieldGroup* owner = CFieldGroup::get(boost::polymorphic_downcast<CFieldGroup*>(this));
      owner->setAttributes(group); // inherite of attributes of group reference
      
      std::vector<CField*> allChildren  = group->getAllChildren();
      std::vector<CField*>::iterator it = allChildren.begin(), end = allChildren.end();

      for (; it != end; it++)
      {
         CField* child = *it;
         if (child->hasId()) owner->createChild()->field_ref.setValue(child->getId());

      }
   }
   CATCH_DUMP_ATTR

   void CField::scaleFactorAddOffset(double scaleFactor, double addOffset)
   TRY
   {
     recvDataSrv = (recvDataSrv - addOffset) / scaleFactor;
   }
   CATCH_DUMP_ATTR

   void CField::invertScaleFactorAddOffset(double scaleFactor, double addOffset)
   TRY
   {
     recvDataSrv = recvDataSrv * scaleFactor + addOffset;
   }
   CATCH_DUMP_ATTR

   void CField::outputField(CArray<double,1>& fieldOut)
   TRY
   { 
      CArray<size_t,1>& outIndexClient = grid->localIndexToWriteOnClient;
      CArray<size_t,1>& outIndexServer = grid->localIndexToWriteOnServer;
      for (size_t idx = 0; idx < outIndexServer.numElements(); ++idx)
      {
        fieldOut(outIndexServer(idx)) = recvDataSrv(outIndexClient(idx));
      }
   }
   CATCH_DUMP_ATTR

   void CField::inputField(CArray<double,1>& fieldIn)
   TRY
   {
      CArray<size_t,1>& outIndexClient = grid->localIndexToWriteOnClient;
      CArray<size_t,1>& outIndexServer = grid->localIndexToWriteOnServer;
      for (size_t idx = 0; idx < outIndexServer.numElements(); ++idx)
      {
        recvDataSrv(outIndexClient(idx)) = fieldIn(outIndexServer(idx));
      }
   }
   CATCH_DUMP_ATTR

   void CField::outputCompressedField(CArray<double,1>& fieldOut)
   TRY
   {
      CArray<size_t,1>& outIndexClient = grid->localIndexToWriteOnClient;
      CArray<size_t,1>& outIndexServer = grid->localIndexToWriteOnServer;
      for (size_t idx = 0; idx < outIndexServer.numElements(); ++idx)
      {
        fieldOut((idx)) = recvDataSrv(outIndexClient(idx));
      }
   }
   CATCH_DUMP_ATTR

   ///-------------------------------------------------------------------

   void CField::parse(xml::CXMLNode& node)
   TRY
   {
      string newContent ;
      SuperClass::parse(node);
      if (node.goToChildElement())
      {
        do
        {
          if (node.getElementName() == "variable" || node.getElementName() == "variable_group") this->getVirtualVariableGroup()->parseChild(node);
          else if (node.getElementName() == "expr") if (node.getContent(newContent)) content+=newContent ;
        } while (node.goToNextElement());
        node.goToParentElement();
      }
      if (node.getContent(newContent)) content=newContent ;
    }
   CATCH_DUMP_ATTR

   /*!
     This function retrieves Id of corresponding domain_ref and axis_ref (if any)
   of a field. In some cases, only domain exists but axis doesn't
   \return pair of Domain and Axis id
   */
   const std::vector<StdString>& CField::getRefDomainAxisIds()
   TRY
   {
     CGrid* cgPtr = getRelGrid();
     if (NULL != cgPtr)
     {
       std::vector<StdString>::iterator it;
       if (!domain_ref.isEmpty())
       {
         std::vector<StdString> domainList = cgPtr->getDomainList();
         it = std::find(domainList.begin(), domainList.end(), domain_ref.getValue());
         if (domainList.end() != it) domAxisScalarIds_[0] = *it;
       }

       if (!axis_ref.isEmpty())
       {
         std::vector<StdString> axisList = cgPtr->getAxisList();
         it = std::find(axisList.begin(), axisList.end(), axis_ref.getValue());
         if (axisList.end() != it) domAxisScalarIds_[1] = *it;
       }

       if (!scalar_ref.isEmpty())
       {
         std::vector<StdString> scalarList = cgPtr->getScalarList();
         it = std::find(scalarList.begin(), scalarList.end(), scalar_ref.getValue());
         if (scalarList.end() != it) domAxisScalarIds_[2] = *it;
       }
     }
     return (domAxisScalarIds_);
   }
   CATCH_DUMP_ATTR

   CVariable* CField::addVariable(const string& id)
   TRY
   {
     return vVariableGroup->createChild(id);
   }
   CATCH

   CVariableGroup* CField::addVariableGroup(const string& id)
   TRY
   {
     return vVariableGroup->createChildGroup(id);
   }
   CATCH

   void CField::setContextClient(CContextClient* contextClient)
   TRY
   {
     CContext* context = CContext::getCurrent();
     client = contextClient;
     if (context->hasClient)
     {
       // A grid is sent by a client (both for read or write) or by primary server (write only)
       if (context->hasServer)
       {
         if (file->mode.isEmpty() || (!file->mode.isEmpty() && file->mode == CFile::mode_attr::write))
           grid->setContextClient(contextClient);
       }
       else
           grid->setContextClient(contextClient);
     }
   }
   CATCH_DUMP_ATTR

   CContextClient* CField::getContextClient()
   TRY
   {
     return client;
   }
   CATCH

   void CField::sendAddAllVariables(CContextClient* client)
   TRY
   {
     std::vector<CVariable*> allVar = getAllVariables();
     std::vector<CVariable*>::const_iterator it = allVar.begin();
     std::vector<CVariable*>::const_iterator itE = allVar.end();

     for (; it != itE; ++it)
     {
       this->sendAddVariable((*it)->getId(), client);
       (*it)->sendAllAttributesToServer(client);
       (*it)->sendValue(client);
     }
   }
   CATCH_DUMP_ATTR

   /*!
    * Send all Attributes to server. This method is overloaded, since only grid_ref attribute
    * must be sent to server and not domain_ref/axis_ref/scalar_ref. 
    */
    
   void CField::sendAllAttributesToServer(CContextClient* client)
   TRY
   {
     if (grid_ref.isEmpty())
     {
       grid_ref=grid->getId() ;
       SuperClass::sendAllAttributesToServer(client) ;
       grid_ref.reset();
     }
     else SuperClass::sendAllAttributesToServer(client) ;
   }
   CATCH_DUMP_ATTR
    
   void CField::sendAddVariable(const string& id, CContextClient* client)
   TRY
   {
      sendAddItem(id, (int)EVENT_ID_ADD_VARIABLE, client);
   }
   CATCH_DUMP_ATTR

   void CField::sendAddVariableGroup(const string& id, CContextClient* client)
   TRY
   {
      sendAddItem(id, (int)EVENT_ID_ADD_VARIABLE_GROUP, client);
   }
   CATCH_DUMP_ATTR

   void CField::recvAddVariable(CEventServer& event)
   TRY
   {

      CBufferIn* buffer = event.subEvents.begin()->buffer;
      string id;
      *buffer >> id;
      get(id)->recvAddVariable(*buffer);
   }
   CATCH

   void CField::recvAddVariable(CBufferIn& buffer)
   TRY
   {
      string id;
      buffer >> id;
      addVariable(id);
   }
   CATCH_DUMP_ATTR

   void CField::recvAddVariableGroup(CEventServer& event)
   TRY
   {

      CBufferIn* buffer = event.subEvents.begin()->buffer;
      string id;
      *buffer >> id;
      get(id)->recvAddVariableGroup(*buffer);
   }
   CATCH

   void CField::recvAddVariableGroup(CBufferIn& buffer)
   TRY
   {
      string id;
      buffer >> id;
      addVariableGroup(id);
   }
   CATCH_DUMP_ATTR

   /*!
    * Check on freq_off and freq_op attributes.
    */
   void CField::checkTimeAttributes(CDuration* freqOp)
   TRY
   {
     bool isFieldRead  = file && !file->mode.isEmpty() && file->mode == CFile::mode_attr::read;
     bool isFieldWrite = file && ( file->mode.isEmpty() ||  file->mode == CFile::mode_attr::write);
     if (isFieldRead && !(operation.getValue() == "instant" || operation.getValue() == "once") )     
       ERROR("void CField::checkTimeAttributes(void)",
             << "Unsupported operation for field '" << getFieldOutputName() << "'." << std::endl
             << "Currently only \"instant\" is supported for fields read from file.")

     if (freq_op.isEmpty())
     {
       if (operation.getValue() == "instant")
       {
         if (isFieldRead || isFieldWrite) freq_op.setValue(file->output_freq.getValue());
         else freq_op=*freqOp ;
       }
       else
         freq_op.setValue(TimeStep);
     }
     else
     {
       //if(file->output_freq.getValue() < freq_op.getValue())
       if((isFieldRead || isFieldWrite) && (file!=nullptr) && (freq_op.getValue() > file->output_freq.getValue() ))
       {
         ERROR("void CField::checkTimeAttributes(void)",
               << "output file has output_freq < freq_op" << std::endl
               << "field_id = "<< getId() << std::endl
               << "file_id = "<< file->getId() << std::endl
               << "output_freq = "<< file->output_freq.getValue() << std::endl
               << "freq_op = "<< freq_op.getValue() << std::endl)
       }
     }
     if (freq_offset.isEmpty())
       freq_offset.setValue(isFieldRead ? NoneDu : (freq_op.getValue() - TimeStep));
   }
   CATCH_DUMP_ATTR

   /*!
    * Returns string arithmetic expression associated to the field.
    * \return if content is defined return content string, otherwise, if "expr" attribute is defined, return expr string.
    */
   const string& CField::getExpression(void)
   TRY
   {
     if (!expr.isEmpty() && content.empty())
     {
       content = expr;
       expr.reset();
     }

     return content;
   }
   CATCH_DUMP_ATTR

   bool CField::hasExpression(void) const
   TRY
   {
     return (!expr.isEmpty() || !content.empty());
   }
   CATCH

   bool CField::hasGridMask(void) const
   TRY
   {
     return (this->grid->hasMask());
   }
   CATCH

   DEFINE_REF_FUNC(Field,field)
} // namespace xios
