#include "ternary_arithmetic_filter.hpp"
#include "workflow_graph.hpp"
#include "yacc_var.hpp"
#include "file.hpp"

namespace xios
{
  CScalarScalarFieldArithmeticFilter::CScalarScalarFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value1, double value2)
    : CFilter(gc, 1, this)
    , op(operatorExpr.getOpScalarScalarField(op))
    , value1(value1)
    , value2(value2)
  { 
    /* Nothing to do */ 
  };

  std::tuple<int, int, int> CScalarScalarFieldArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    int unique_filter_id;
    bool firstround;

    if(building_graph)
    {
      CWorkflowGraph::allocNodeEdge();

      size_t filterhash = std::hash<StdString>{}(this->field->content+to_string(data[0]->timestamp)+this->field->getId());

      // first round
      if(CWorkflowGraph::mapHashFilterID_ptr->find(filterhash) == CWorkflowGraph::mapHashFilterID_ptr->end())
      {
        firstround = true;
        this->filterID = InvalidableObject::filterIdGenerator++;
        int edgeID = InvalidableObject::edgeIdGenerator++;

        CWorkflowGraph::addNode(this->filterID, "Arithmetic Filter\\n("+this->field->content+")", 3, 1, 0, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].filter_tag = this->tag;
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;


        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
      

        if(CWorkflowGraph::build_begin)
        {
          CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
        }
        else CWorkflowGraph::build_begin = true;

        (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash] = this->filterID; 
        unique_filter_id = this->filterID;
      }
      // not first round
      else 
      {
        firstround=false;
        unique_filter_id = (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash];
        if(data[0]->src_filterID != unique_filter_id)
        {
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[0]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ; 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
      }  
    }

    return std::make_tuple(building_graph, firstround, unique_filter_id);
  }

  CDataPacketPtr CScalarScalarFieldArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;
    
    std::tuple<int, int, int> graph = buildGraph(data);

    if(std::get<0>(graph)) packet->src_filterID = std::get<2>(graph);
    if(std::get<0>(graph) && std::get<1>(graph)) packet->distance = data[0]->distance+1;
    if(std::get<0>(graph) && !std::get<1>(graph)) packet->distance = data[0]->distance;

    packet->field = this->field;

    if (packet->status == CDataPacket::NO_ERROR)
      packet->data.reference(op(value1,value2, data[0]->data));

    return packet;
  }

  CScalarFieldScalarArithmeticFilter::CScalarFieldScalarArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value1, double value2)
    : CFilter(gc, 1, this)
    , op(operatorExpr.getOpScalarFieldScalar(op))
    , value1(value1)
    , value2(value2)
  { 
    /* Nothing to do */ 
  };

  std::tuple<int, int, int> CScalarFieldScalarArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    int unique_filter_id;
    bool firstround;

    if(building_graph)
    {
      CWorkflowGraph::allocNodeEdge();

      size_t filterhash = std::hash<StdString>{}(this->field->content+to_string(data[0]->timestamp)+this->field->getId());

      // first round
      if(CWorkflowGraph::mapHashFilterID_ptr->find(filterhash) == CWorkflowGraph::mapHashFilterID_ptr->end())
      {
        firstround = true;
        this->filterID = InvalidableObject::filterIdGenerator++;
        int edgeID = InvalidableObject::edgeIdGenerator++;

        CWorkflowGraph::addNode(this->filterID, "Arithmetic Filter\\n("+this->field->content+")", 3, 1, 0, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].filter_tag = this->tag;
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;


        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
      

        if(CWorkflowGraph::build_begin)
        {
          CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
        }
        else CWorkflowGraph::build_begin = true;

        (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash] = this->filterID; 
        unique_filter_id = this->filterID;
      }
      // not first round
      else 
      {
        firstround=false;
        unique_filter_id = (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash];
        if(data[0]->src_filterID != unique_filter_id)
        {
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[0]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ; 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
      }  
    }

    return std::make_tuple(building_graph, firstround, unique_filter_id);
  }

  CDataPacketPtr CScalarFieldScalarArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;
    
    std::tuple<int, int, int> graph = buildGraph(data);

    if(std::get<0>(graph)) packet->src_filterID = std::get<2>(graph);
    if(std::get<0>(graph) && std::get<1>(graph)) packet->distance = data[0]->distance+1;
    if(std::get<0>(graph) && !std::get<1>(graph)) packet->distance = data[0]->distance;

    packet->field = this->field;

    if (packet->status == CDataPacket::NO_ERROR)
      packet->data.reference(op(value1, data[0]->data,value2));

    return packet;
  }

  CScalarFieldFieldArithmeticFilter::CScalarFieldFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value)
    : CFilter(gc, 2, this)
    , op(operatorExpr.getOpScalarFieldField(op))
    , value(value)
  { 
    /* Nothing to do */ 
  };

  std::tuple<int, int, int> CScalarFieldFieldArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    int unique_filter_id;

    bool firstround;

    if(building_graph)
    {  
      CWorkflowGraph::allocNodeEdge();

      size_t filterhash = std::hash<StdString>{}(this->field->content+to_string(data[0]->timestamp)+this->field->getId());

      // first round
      if(CWorkflowGraph::mapHashFilterID_ptr->find(filterhash) == CWorkflowGraph::mapHashFilterID_ptr->end())
      {
        firstround = true;
        this->filterID = InvalidableObject::filterIdGenerator++;
        int edgeID = InvalidableObject::edgeIdGenerator++;
    
        CWorkflowGraph::addNode(this->filterID, "Arithmetic Filter\\n("+this->field->content+")", 3, 1, 0, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;

        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
    
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].filter_tag = this->tag;
        if(CWorkflowGraph::build_begin)
        {

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          edgeID = InvalidableObject::edgeIdGenerator++;

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[1]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
        }
        CWorkflowGraph::build_begin = true;

        (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash] = this->filterID; 
        unique_filter_id = this->filterID;
 
      }
      // not first round
      else 
      {
        firstround = false;
        unique_filter_id = (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash];
        if(data[0]->src_filterID != unique_filter_id)
        {
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[0]); 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ; 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        if(data[1]->src_filterID != unique_filter_id)
        { 
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[1]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        
      }  
    }

    return std::make_tuple(building_graph, firstround, unique_filter_id);
  }

  CDataPacketPtr CScalarFieldFieldArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;
    
    std::tuple<int, int, int> graph = buildGraph(data);

    if(std::get<0>(graph)) packet->src_filterID = std::get<2>(graph);
    if(std::get<0>(graph) && std::get<1>(graph)) packet->distance = data[0]->distance+1;
    if(std::get<0>(graph) && !std::get<1>(graph)) packet->distance = data[0]->distance;

    packet->field = this->field;

    if (data[0]->status != CDataPacket::NO_ERROR)
      packet->status = data[0]->status;
    else if (data[1]->status != CDataPacket::NO_ERROR)
      packet->status = data[1]->status;
    else
    { 
      packet->status = CDataPacket::NO_ERROR;
      packet->data.reference(op(value, data[0]->data, data[1]->data));
    }
    return packet;

  }


  CFieldScalarScalarArithmeticFilter::CFieldScalarScalarArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value1, double value2)
    : CFilter(gc, 1, this)
    , op(operatorExpr.getOpFieldScalarScalar(op))
    , value1(value1)
    , value2(value2)
  { 
    /* Nothing to do */ 
  };

  std::tuple<int, int, int> CFieldScalarScalarArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    int unique_filter_id;
    bool firstround;

    if(building_graph)
    {
      CWorkflowGraph::allocNodeEdge();

      size_t filterhash = std::hash<StdString>{}(this->field->content+to_string(data[0]->timestamp)+this->field->getId());

      // first round
      if(CWorkflowGraph::mapHashFilterID_ptr->find(filterhash) == CWorkflowGraph::mapHashFilterID_ptr->end())
      {
        firstround = true;
        this->filterID = InvalidableObject::filterIdGenerator++;
        int edgeID = InvalidableObject::edgeIdGenerator++;

        CWorkflowGraph::addNode(this->filterID, "Arithmetic Filter\\n("+this->field->content+")", 3, 1, 0, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].filter_tag = this->tag;
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;


        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
      

        if(CWorkflowGraph::build_begin)
        {
          CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
        }
        else CWorkflowGraph::build_begin = true;

        (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash] = this->filterID; 
        unique_filter_id = this->filterID;
      }
      // not first round
      else 
      {
        firstround=false;
        unique_filter_id = (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash];
        if(data[0]->src_filterID != unique_filter_id)
        {
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[0]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ; 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
      }  
    }

    return std::make_tuple(building_graph, firstround, unique_filter_id);
  }

  CDataPacketPtr CFieldScalarScalarArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;

    std::tuple<int, int, int> graph = buildGraph(data);

    if(std::get<0>(graph)) packet->src_filterID = std::get<2>(graph);
    if(std::get<0>(graph) && std::get<1>(graph)) packet->distance = data[0]->distance+1;
    if(std::get<0>(graph) && !std::get<1>(graph)) packet->distance = data[0]->distance;

    packet->field = this->field;

    if (packet->status == CDataPacket::NO_ERROR)
      packet->data.reference(op(data[0]->data, value1, value2));

    return packet;
  }


  CFieldScalarFieldArithmeticFilter::CFieldScalarFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value)
    : CFilter(gc, 2, this)
    , op(operatorExpr.getOpFieldScalarField(op))
    , value(value)
  { 
    /* Nothing to do */ 
  };

  std::tuple<int, int, int> CFieldScalarFieldArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    int unique_filter_id;

    bool firstround;

    if(building_graph)
    {  
      CWorkflowGraph::allocNodeEdge();

      size_t filterhash = std::hash<StdString>{}(this->field->content+to_string(data[0]->timestamp)+this->field->getId());

      // first round
      if(CWorkflowGraph::mapHashFilterID_ptr->find(filterhash) == CWorkflowGraph::mapHashFilterID_ptr->end())
      {
        firstround = true;
        this->filterID = InvalidableObject::filterIdGenerator++;
        int edgeID = InvalidableObject::edgeIdGenerator++;
    
        CWorkflowGraph::addNode(this->filterID, "Arithmetic Filter\\n("+this->field->content+")", 3, 1, 0, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;

        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
    
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].filter_tag = this->tag;
        if(CWorkflowGraph::build_begin)
        {

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          edgeID = InvalidableObject::edgeIdGenerator++;

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[1]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
        }
        CWorkflowGraph::build_begin = true;

        (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash] = this->filterID; 
        unique_filter_id = this->filterID;
 
      }
      // not first round
      else 
      {
        firstround = false;
        unique_filter_id = (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash];
        if(data[0]->src_filterID != unique_filter_id)
        {
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[0]); 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ; 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        if(data[1]->src_filterID != unique_filter_id)
        { 
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[1]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        
      }  
    }

    return std::make_tuple(building_graph, firstround, unique_filter_id);
  }

  CDataPacketPtr CFieldScalarFieldArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;
    
    std::tuple<int, int, int> graph = buildGraph(data);

    if(std::get<0>(graph)) packet->src_filterID = std::get<2>(graph);
    if(std::get<0>(graph) && std::get<1>(graph)) packet->distance = data[0]->distance+1;
    if(std::get<0>(graph) && !std::get<1>(graph)) packet->distance = data[0]->distance;

    packet->field = this->field;

    if (data[0]->status != CDataPacket::NO_ERROR)
      packet->status = data[0]->status;
    else if (data[1]->status != CDataPacket::NO_ERROR)
      packet->status = data[1]->status;
    else
    { 
      packet->status = CDataPacket::NO_ERROR;
      packet->data.reference(op(data[0]->data, value, data[1]->data));
    }
    return packet;
  }
  
   CFieldFieldScalarArithmeticFilter::CFieldFieldScalarArithmeticFilter(CGarbageCollector& gc, const std::string& op, double value)
    : CFilter(gc, 2, this)
    , op(operatorExpr.getOpFieldFieldScalar(op))
    , value(value)
  { 
    /* Nothing to do */ 
  };

  std::tuple<int, int, int> CFieldFieldScalarArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    int unique_filter_id;

    bool firstround;

    if(building_graph)
    {  
      CWorkflowGraph::allocNodeEdge();

      size_t filterhash = std::hash<StdString>{}(this->field->content+to_string(data[0]->timestamp)+this->field->getId());

      // first round
      if(CWorkflowGraph::mapHashFilterID_ptr->find(filterhash) == CWorkflowGraph::mapHashFilterID_ptr->end())
      {
        firstround = true;
        this->filterID = InvalidableObject::filterIdGenerator++;
        int edgeID = InvalidableObject::edgeIdGenerator++;
    
        CWorkflowGraph::addNode(this->filterID, "Arithmetic Filter\\n("+this->field->content+")", 3, 1, 0, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;

        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
    
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].filter_tag = this->tag;
        if(CWorkflowGraph::build_begin)
        {

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          edgeID = InvalidableObject::edgeIdGenerator++;

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[1]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
        }
        CWorkflowGraph::build_begin = true;

        (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash] = this->filterID; 
        unique_filter_id = this->filterID;
 
      }
      // not first round
      else 
      {
        firstround = false;
        unique_filter_id = (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash];
        if(data[0]->src_filterID != unique_filter_id)
        {
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[0]); 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ; 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        if(data[1]->src_filterID != unique_filter_id)
        { 
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[1]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        
      }  
    }

    return std::make_tuple(building_graph, firstround, unique_filter_id);
  }

  CDataPacketPtr CFieldFieldScalarArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;
    
    std::tuple<int, int, int> graph = buildGraph(data);

    if(std::get<0>(graph)) packet->src_filterID = std::get<2>(graph);
    if(std::get<0>(graph) && std::get<1>(graph)) packet->distance = data[0]->distance+1;
    if(std::get<0>(graph) && !std::get<1>(graph)) packet->distance = data[0]->distance;

    packet->field = this->field;

    if (data[0]->status != CDataPacket::NO_ERROR)
      packet->status = data[0]->status;
    else if (data[1]->status != CDataPacket::NO_ERROR)
      packet->status = data[1]->status;
    else
    { 
      packet->status = CDataPacket::NO_ERROR;
      packet->data.reference(op(data[0]->data, data[1]->data, value));
    }
    return packet;
  } 
  
 
  CFieldFieldFieldArithmeticFilter::CFieldFieldFieldArithmeticFilter(CGarbageCollector& gc, const std::string& op)
    : CFilter(gc, 3, this)
    , op(operatorExpr.getOpFieldFieldField(op))
  { 
    /* Nothing to do */ 
  };

  std::tuple<int, int, int> CFieldFieldFieldArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    int unique_filter_id;

    bool firstround;

    if(building_graph)
    {  
      CWorkflowGraph::allocNodeEdge();

      size_t filterhash = std::hash<StdString>{}(this->field->content+to_string(data[0]->timestamp)+this->field->getId());

      // first round
      if(CWorkflowGraph::mapHashFilterID_ptr->find(filterhash) == CWorkflowGraph::mapHashFilterID_ptr->end())
      {
        firstround = true;
        this->filterID = InvalidableObject::filterIdGenerator++;
        int edgeID = InvalidableObject::edgeIdGenerator++;
    
        CWorkflowGraph::addNode(this->filterID, "Arithmetic Filter\\n("+this->field->content+")", 3, 1, 0, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;

        if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();
    
        (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].filter_tag = this->tag;
        if(CWorkflowGraph::build_begin)
        {

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          edgeID = InvalidableObject::edgeIdGenerator++;

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[1]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          edgeID = InvalidableObject::edgeIdGenerator++;

          CWorkflowGraph::addEdge(edgeID, this->filterID, data[2]);
          (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].expected_entry_nb ++;

          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[2]->src_filterID].filter_filled = 0 ;
        }
        CWorkflowGraph::build_begin = true;

        (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash] = this->filterID; 
        unique_filter_id = this->filterID;
 
      }
      // not first round
      else 
      {
        firstround = false;
        unique_filter_id = (*CWorkflowGraph::mapHashFilterID_ptr)[filterhash];
        if(data[0]->src_filterID != unique_filter_id)
        {
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[0]); 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0 ; 
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        if(data[1]->src_filterID != unique_filter_id)
        { 
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[1]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[1]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        if(data[2]->src_filterID != unique_filter_id)
        { 
          int edgeID = InvalidableObject::edgeIdGenerator++;
          CWorkflowGraph::addEdge(edgeID, unique_filter_id, data[2]);  
          (*CWorkflowGraph::mapFilters_ptr_with_info)[data[2]->src_filterID].filter_filled = 0 ;
          (*CWorkflowGraph::mapFilters_ptr_with_info)[unique_filter_id].expected_entry_nb ++;
        }
        
      }  
    }

    return std::make_tuple(building_graph, firstround, unique_filter_id);
  }

  CDataPacketPtr CFieldFieldFieldArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
  {
    CDataPacketPtr packet(new CDataPacket);
    packet->date = data[0]->date;
    packet->timestamp = data[0]->timestamp;
    packet->status = data[0]->status;
    
    std::tuple<int, int, int> graph = buildGraph(data);

    if(std::get<0>(graph)) packet->src_filterID = std::get<2>(graph);
    if(std::get<0>(graph) && std::get<1>(graph)) packet->distance = data[0]->distance+1;
    if(std::get<0>(graph) && !std::get<1>(graph)) packet->distance = data[0]->distance;

    packet->field = this->field;

    if (data[0]->status != CDataPacket::NO_ERROR)
      packet->status = data[0]->status;
    else if (data[1]->status != CDataPacket::NO_ERROR)
      packet->status = data[1]->status;
    else if (data[2]->status != CDataPacket::NO_ERROR)
      packet->status = data[2]->status;
    else
    { 
      packet->status = CDataPacket::NO_ERROR;
      packet->data.reference(op(data[0]->data, data[1]->data, data[2]->data));
    }
    return packet;
  } 
  
} // namespace xios

