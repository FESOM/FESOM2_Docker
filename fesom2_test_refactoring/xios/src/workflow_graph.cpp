#include "workflow_graph.hpp"

namespace xios
{

  std::unordered_map <int, graph_info_box_node> *CWorkflowGraph::mapFilters_ptr_with_info = 0;

  std::unordered_map <int, graph_info_box_edge > *CWorkflowGraph::mapFieldToFilters_ptr_with_info = 0;

  std::unordered_map <size_t, int> *CWorkflowGraph::mapHashFilterID_ptr = 0;
  
  std::unordered_map <StdString, int > *CWorkflowGraph::mapContext_ptr = 0;


  vector <StdString> CWorkflowGraph::filters;
  vector <StdString> CWorkflowGraph::fields;
  vector <pair<int, int> > CWorkflowGraph::fieldsToFilters;

  bool CWorkflowGraph::build_begin = false;

  CWorkflowGraph::CWorkflowGraph()
  { }

  /*!
   * Reorganize information collected by XIOS for visualization.
   */
  void CWorkflowGraph::buildStaticWorkflow()
  TRY
  {
    
    if(mapFilters_ptr_with_info==0 || mapFieldToFilters_ptr_with_info==0) 
      std::cout<<"No graph information provided"<<std::endl;

    else // Create a list of filters (graph nodes)
    {
      size_t filterIdx = 0;
      filters.resize(mapFilters_ptr_with_info->size());
      fieldsToFilters.clear();
      fields.clear();
      for (auto it=mapFilters_ptr_with_info->begin(); it != mapFilters_ptr_with_info->end(); it++)
      {
        filters[it->first]=it->second.filter_name;
      }

      // Create a list of fields and their filter connectivity (graph edges and edge-to-node connectivity)
      for (auto it=mapFieldToFilters_ptr_with_info->begin(); it != mapFieldToFilters_ptr_with_info->end(); it++)
      {
        fieldsToFilters.push_back(make_pair(it->second.from,it->second.to));
        fields.push_back(it->second.field_id + " "+it->second.date.toString());
      }
    }
  }
  CATCH




/*!
   * Reorganize information collected by XIOS for visualization.
   */
  void CWorkflowGraph::buildStaticWorkflow_with_info()
  TRY
  {
    // showStaticWorkflow();
    
    if(mapFilters_ptr_with_info==0 || mapFieldToFilters_ptr_with_info==0) 
      std::cout<<"No graph information provided"<<std::endl;

    else // Create a list of filters (graph nodes)
    {
      size_t filterIdx = 0;
      filters.resize(mapFilters_ptr_with_info->size());
      fieldsToFilters.clear();
      fields.clear();
      for (auto it=mapFilters_ptr_with_info->begin(); it != mapFilters_ptr_with_info->end(); it++)
      {
        // std::cout<<"it->first = "<<it->first<<std::endl;
        filters[it->first]=it->second.filter_name;
      }

      // Create a list of fields and their filter connectivity (graph edges and edge-to-node connectivity)
      for (auto it=mapFieldToFilters_ptr_with_info->begin(); it != mapFieldToFilters_ptr_with_info->end(); it++)
      {
        fieldsToFilters.push_back(make_pair(it->second.from,it->second.to));
        fields.push_back(it->second.field_id + " "+it->second.date.toString());
      }
    }
  }
  CATCH



  void CWorkflowGraph::showStaticWorkflow()
  TRY
  {
    if(mapFilters_ptr_with_info!=0 && !mapFilters_ptr_with_info->empty())
    for (auto it=mapFilters_ptr_with_info->begin(); it != mapFilters_ptr_with_info->end(); it++)
    {
      std::cout<<"mapFilters_ptr_with_info["<<it->first<<"].filter_name="<<it->second.filter_name<<std::endl;
      std::cout<<"mapFilters_ptr_with_info["<<it->first<<"].filter_class="<<it->second.filter_class<<std::endl;
      std::cout<<"mapFilters_ptr_with_info["<<it->first<<"].filter_fillled="<<it->second.filter_filled<<std::endl;
      std::cout<<"mapFilters_ptr_with_info["<<it->first<<"].expected_entry_nb="<<it->second.expected_entry_nb<<std::endl;
      std::cout<<"mapFilters_ptr_with_info["<<it->first<<"].date="<<it->second.date<<std::endl;
      std::cout<<"mapFilters_ptr_with_info["<<it->first<<"].timestamp="<<it->second.timestamp<<std::endl;
      std::cout<<"mapFilters_ptr_with_info["<<it->first<<"].transform_type="<<it->second.transform_type<<std::endl;
    }
    else std::cout<<"mapFilters_ptr_with_info empty"<<std::endl;

    if(mapFieldToFilters_ptr_with_info!=0 && !mapFieldToFilters_ptr_with_info->empty())
    for (auto it=mapFieldToFilters_ptr_with_info->begin(); it != mapFieldToFilters_ptr_with_info->end(); it++)
    {
      std::cout<<"mapFieldToFilters_ptr_with_info["<<it->first<<"].from = "<<it->second.from<<std::endl;
      std::cout<<"mapFieldToFilters_ptr_with_info["<<it->first<<"].to = "<<it->second.to<<std::endl;
      std::cout<<"mapFieldToFilters_ptr_with_info["<<it->first<<"].field_id = "<<it->second.field_id<<std::endl;
      std::cout<<"mapFieldToFilters_ptr_with_info["<<it->first<<"].field_name = "<<it->second.field_name<<std::endl;
      std::cout<<"mapFieldToFilters_ptr_with_info["<<it->first<<"].date = "<<it->second.date<<std::endl;
      
    }
    else std::cout<<"mapFieldToFilters_ptr_with_info empty"<<std::endl;


  }
  CATCH


  void CWorkflowGraph::addNode(int nodeID, StdString filterName, int filterClass, bool filterFilled, int entry_nb, CDataPacketPtr packet)
  TRY
  {
    if(!mapContext_ptr) mapContext_ptr = new std::unordered_map<StdString, int>;
    std::string current_context_id = CContext::getCurrent()->getId();
    std::unordered_map<StdString,int>::const_iterator found = mapContext_ptr->find(current_context_id);
    if (found == mapContext_ptr->end())
    {
      std::pair<StdString, int> mypair (current_context_id, mapContext_ptr->size());
      mapContext_ptr->insert(mypair);
    }

    (*mapFilters_ptr_with_info)[nodeID].filter_name = filterName;
    (*mapFilters_ptr_with_info)[nodeID].filter_class = filterClass;
    (*mapFilters_ptr_with_info)[nodeID].filter_filled = filterFilled;
    (*mapFilters_ptr_with_info)[nodeID].expected_entry_nb = entry_nb;
    (*mapFilters_ptr_with_info)[nodeID].date = packet->date;
    (*mapFilters_ptr_with_info)[nodeID].timestamp = packet->timestamp;
    (*mapFilters_ptr_with_info)[nodeID].node_context_id = CContext::getCurrent()->getId();
  }
  CATCH



  void CWorkflowGraph::addEdge(int edgeID, int toID, CDataPacketPtr packet)
  TRY
  {
    std::string current_context_id = CContext::getCurrent()->getId();
    (*mapFieldToFilters_ptr_with_info)[edgeID].from = packet->src_filterID;
    (*mapFieldToFilters_ptr_with_info)[edgeID].to = toID;
    (*mapFieldToFilters_ptr_with_info)[edgeID].field_id = packet->field->getId();
    (*mapFieldToFilters_ptr_with_info)[edgeID].field_name = packet->field->name;
    (*mapFieldToFilters_ptr_with_info)[edgeID].grid_id = packet->field->grid->getId();
    (*mapFieldToFilters_ptr_with_info)[edgeID].date = packet->date;
    (*mapFieldToFilters_ptr_with_info)[edgeID].timestamp = packet->timestamp;
    (*mapFieldToFilters_ptr_with_info)[edgeID].field = packet->field;
    (*mapFieldToFilters_ptr_with_info)[edgeID].attributes = packet->field->record4graphXiosAttributes();
    (*mapFieldToFilters_ptr_with_info)[edgeID].edge_context_id = CContext::getCurrent()->getId();
  }
  CATCH


  void CWorkflowGraph::allocNodeEdge()
  TRY
  {
    if(mapFilters_ptr_with_info==0) mapFilters_ptr_with_info = new std::unordered_map <int, graph_info_box_node>;
    if(mapFieldToFilters_ptr_with_info==0) mapFieldToFilters_ptr_with_info = new std::unordered_map <int, graph_info_box_edge >;
    if(mapHashFilterID_ptr==0) mapHashFilterID_ptr = new std::unordered_map <size_t, int >;
  }
  CATCH

}
