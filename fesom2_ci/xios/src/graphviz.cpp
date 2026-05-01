#include "graphviz.hpp"
#include "workflow_graph.hpp"

namespace xios
{

  CGraphviz::CGraphviz()
  { }

  /*!
   *
   */
  void CGraphviz::buildWorkflowGraphDot()
  TRY
  {
    if (CWorkflowGraph::mapFieldToFilters_ptr_with_info !=0 && !CWorkflowGraph::mapFieldToFilters_ptr_with_info->empty())
    {
      CWorkflowGraph::buildStaticWorkflow();
    
      typedef boost::property<boost::edge_name_t, std::string> EdgeProperty;
      typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, EdgeProperty> Graph;

      // Input 1: nodes (=filters)
      vector<StdString>& nodes = CWorkflowGraph::filters;
      const int nbNodes = nodes.size();

      // Input 2: edges (=fields)
      vector<StdString>& edges = CWorkflowGraph::fields;

      // Input 3: nodes to edges connectivity
      vector<pair<int, int> >& nodesToEdges = CWorkflowGraph::fieldsToFilters;
      const int nbEdges = nodesToEdges.size();

      // Declare a graph object, adding the edges and edge properties
      Graph g(nbNodes);
      for (int j = 0; j < nbEdges; ++j)
      {
        graph_traits<Graph>::edge_descriptor e;
        bool inserted;
        boost::tie(e, inserted) = boost::add_edge(nodesToEdges[j].first, nodesToEdges[j].second, edges[j], g);
      }

      std::for_each(vertices(g).first, vertices(g).second, exercise_vertex<Graph>(g));

      std::map<std::string,std::string> graph_attr, vertex_attr, edge_attr;
      graph_attr["size"] = "5,5";
      graph_attr["rankdir"] = "LR";
      graph_attr["ratio"] = "fill";
      vertex_attr["shape"] = "record";
      vertex_attr["width"] = "2.2";
      vertex_attr["fontsize"] = "16";

      const std::string filename = "graph.dot";
      std::ofstream file (filename.c_str());

      boost::write_graphviz(file, g,
      boost::make_label_writer(&nodes[0]),
      boost::make_label_writer(get(edge_name, g)),
      boost::make_graph_attributes_writer(graph_attr, vertex_attr, edge_attr));
         
    }
  }
  CATCH




  void CGraphviz::buildWorkflowGraphVisjs_with_info()
  TRY
  {
    if (CWorkflowGraph::mapFilters_ptr_with_info !=0 && !CWorkflowGraph::mapFilters_ptr_with_info->empty())
    {
      CWorkflowGraph::buildStaticWorkflow_with_info();
      int nbGraphContext = CWorkflowGraph::mapContext_ptr->size();

      StdString color_table[7] = {"black", "red", "blue", "green", "purple", "yellow", "gray"};
    
      std::ofstream fs_json[nbGraphContext];
      
      for (std::unordered_map<StdString, int>::const_iterator it = CWorkflowGraph::mapContext_ptr->begin(); it != CWorkflowGraph::mapContext_ptr->end(); ++it) 
      {
        fs_json[it->second].open ("graph_data_"+it->first+".json", std::fstream::out);
        fs_json[it->second] << "{\"nodes\":["<<std::endl<<"      ";
      }

      static bool firstnodes[5];
      static bool firstedges[5];

      for(int i=0; i<nbGraphContext; i++)
      {
        firstnodes[i]=true;
        firstedges[i]=true;
      }

      for (auto it=CWorkflowGraph::mapFilters_ptr_with_info->begin(); it != CWorkflowGraph::mapFilters_ptr_with_info->end(); it++)
      {
        int index = (*CWorkflowGraph::mapContext_ptr)[it->second.node_context_id];
        if(firstnodes[index]) 
        {
          fs_json[index] << "{\"id\": "<<it->first +1<<", "<<std::endl;
          firstnodes[index] = false;
        }
        else
        {
          fs_json[index] << ",{\"id\": "<<it->first +1<<", "<<std::endl;
        }
        if(it->second.filter_class == 1) // source filter
          fs_json[index] << "       \"label\": \""<<it->second.filter_name<<"\\n("<<it->second.field_id<<")\", "<<std::endl;
        else
          fs_json[index] << "       \"label\": \""<<it->second.filter_name<<"\", "<<std::endl;
        fs_json[index] << "       \"class\": "<<it->second.filter_class<<", "<<std::endl;
        fs_json[index] << "       \"filled\": "<<it->second.filter_filled<<", "<<std::endl;
        fs_json[index] << "       \"type\": \""<<it->second.transform_type<<"\", "<<std::endl;
        fs_json[index] << "       \"entry\": "<<it->second.expected_entry_nb<<", "<<std::endl;
        fs_json[index] << "       \"inputs\": "<<it->second.inputs_complete<<", "<<std::endl;
        fs_json[index] << "       \"tag\": "<<it->second.filter_tag<<", "<<std::endl;
        fs_json[index] << "       \"cid\": "<<it->second.clusterID<<", "<<std::endl;
        fs_json[index] << "       \"distance\": "<<it->second.distance<<", "<<std::endl;
        fs_json[index] << "       \"context\": \""<<it->second.node_context_id<<"\", "<<std::endl;
        fs_json[index] << "       \"attributes\": \""<<it->second.attributes<<"\"}"<<std::endl<<"       ";
      }
      for(int i=0; i<nbGraphContext; i++) 
      {
        fs_json[i] << "    ],"<<std::endl;
        fs_json[i] << " \"edges\" : ["<<std::endl<<"      ";
      }

      for (auto it=CWorkflowGraph::mapFieldToFilters_ptr_with_info->begin(); it != CWorkflowGraph::mapFieldToFilters_ptr_with_info->end(); it++)
      {
        int index = (*CWorkflowGraph::mapContext_ptr)[it->second.edge_context_id];
        if(firstedges[index])
        {
          fs_json[index] << "{\"id\": "<<it->first +1<<", "<<std::endl;
          firstedges[index] = false;
        }
        else
        {
          fs_json[index] << ",{\"id\": "<<it->first +1<<", "<<std::endl;
        }
        fs_json[index] << "       \"from\": "<<it->second.from+1<<", "<<std::endl;
        fs_json[index] << "       \"to\": "<<it->second.to+1<<", "<<std::endl;
        fs_json[index] << "       \"label\": \""<<it->second.field_id<<"\\n"<<it->second.date<<"\", "<<std::endl;
        // fs_json << "       \"title\": \""<<"Show more information about this field"<<"\", "<<std::endl;
        // fs_json << "       \"fid\": \""<<it->second.field_id<<"\", "<<std::endl;
        // fs_json << "       \"fname\": \""<<it->second.field_name<<"\", "<<std::endl;
        // fs_json << "       \"gid\": \""<<it->second.grid_id<<"\", "<<std::endl;
        fs_json[index] << "       \"date\": \""<<it->second.date<<"\", "<<std::endl;
        fs_json[index] << "       \"context\": \""<<it->second.edge_context_id<<"\", "<<std::endl;
        fs_json[index] << "       \"attributes\": \"id = "<<it->second.field_id<<"</br>"<<it->second.attributes<<"\"}"<<std::endl<<"       ";
      }
      for(int i=0; i<nbGraphContext; i++)
      {
        fs_json[i] << "    ]}"<<std::endl;
        fs_json[i].close();
      }
    }
  }
  CATCH



  void CGraphviz::showStaticWorkflowGraph()
  TRY
  {
    CWorkflowGraph::showStaticWorkflow();
  }
  CATCH
}
