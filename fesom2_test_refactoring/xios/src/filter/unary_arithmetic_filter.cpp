#include "unary_arithmetic_filter.hpp"
#include "workflow_graph.hpp"
#include "yacc_var.hpp"
#include "file.hpp"

namespace xios
{
  CUnaryArithmeticFilter::CUnaryArithmeticFilter(CGarbageCollector& gc, const std::string& op)
    : CFilter(gc, 1, this)
    , op(operatorExpr.getOpField(op))
  { };

  std::tuple<int, int, int> CUnaryArithmeticFilter::buildGraph(std::vector<CDataPacketPtr> data)
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
        firstround=true;
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

  CDataPacketPtr CUnaryArithmeticFilter::apply(std::vector<CDataPacketPtr> data)
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
      packet->data.reference(op(data[0]->data));

    return packet;
  }
} // namespace xios
