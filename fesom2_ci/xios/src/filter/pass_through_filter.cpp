#include "pass_through_filter.hpp"
#include "workflow_graph.hpp"
#include "field.hpp"
#include "file.hpp"

namespace xios
{
  CPassThroughFilter::CPassThroughFilter(CGarbageCollector& gc)
    : CFilter(gc, 1, this)
  { 
  }

  void CPassThroughFilter::buildGraph(std::vector<CDataPacketPtr> data)
  {
    bool building_graph = this->tag ? data[0]->timestamp >= this->start_graph && data[0]->timestamp <= this->end_graph : false;
    // bool building_graph = this->tag ? data[0]->timestamp >= this->field->field_graph_start && data[0]->timestamp <= this->field->field_graph_end : false;

    if(building_graph)
    {
      // std::cout<<"CPassThroughFilter::apply field_id = "<<this->field->getId()<<" start = "<<start_graph<<" end = "<<end_graph<<std::endl;
      this->filterID = InvalidableObject::filterIdGenerator++;
      int edgeID = InvalidableObject::edgeIdGenerator++;

      CWorkflowGraph::allocNodeEdge();

      CWorkflowGraph::addNode(this->filterID, "Pass Through Filter\\n("+data[0]->field->getId()+")", 2, 1, 1, data[0]);
      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].distance = data[0]->distance+1;

      (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes = this->field->record4graphXiosAttributes();
      if(this->field->file) (*CWorkflowGraph::mapFilters_ptr_with_info)[this->filterID].attributes += "</br>file attributes : </br>" +this->field->file->record4graphXiosAttributes();

      
      if(CWorkflowGraph::build_begin)
      {
        CWorkflowGraph::addEdge(edgeID, this->filterID, data[0]);
        (*CWorkflowGraph::mapFilters_ptr_with_info)[data[0]->src_filterID].filter_filled = 0;
      }
      else CWorkflowGraph::build_begin = true;
      
      data[0]->src_filterID=this->filterID;
      data[0]->distance++;

    }

    data[0]->field = this->field;
  }

  CDataPacketPtr CPassThroughFilter::apply(std::vector<CDataPacketPtr> data)
  {
    if(CXios::isClient) buildGraph(data);
    return data[0];
  }
} // namespace xios
