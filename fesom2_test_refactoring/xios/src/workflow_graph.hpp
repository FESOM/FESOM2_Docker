#ifndef __WORKFLOW_GRAPH_HPP__
#define __WORKFLOW_GRAPH_HPP__

#include "xios_spl.hpp"
#include "field.hpp"
#include "grid.hpp"
#include "garbage_collector.hpp"
#include "date.hpp"
#include "duration.hpp"
#include "context.hpp"

namespace xios
{
  class CField;

  struct graph_info_box_node
  {

    StdString filter_name;
    int filter_class;
    bool filter_filled;
    int expected_entry_nb;
    CDate date;
    Time timestamp;
    StdString transform_type;
    StdString attributes;
    StdString field_id;
    bool inputs_complete;
    int filter_tag;
    int clusterID;
    int distance;
    StdString node_context_id;
  };

  struct graph_info_box_edge
  {
    int from;
    int to;
    StdString field_id;
    StdString field_name;
    StdString grid_id;
    CDate date;
    Time timestamp;
    CField *field;
    StdString attributes;
    StdString edge_context_id;
  };

  class CWorkflowGraph
  {

    friend class CGraphviz;

    public:

      CWorkflowGraph();

      /*! Map between fields identified by its id and their filters identified by an integer.
       * It is filled up during reconstruction of a workflow (in function CField::buildFilterGraph()).
      */
      // static std::unordered_map <StdString, vector <int> > *mapFieldToFilters_ptr;
      // #pragma omp threadprivate(mapFieldToFilters_ptr)



      static std::unordered_map <int, graph_info_box_node> *mapFilters_ptr_with_info;

      static std::unordered_map <int, graph_info_box_edge> *mapFieldToFilters_ptr_with_info;

      static std::unordered_map <size_t, int> *mapHashFilterID_ptr;
      
      static std::unordered_map <StdString, int> *mapContext_ptr;


      static bool build_begin;

      static void addNode(int nodeID, StdString filterName, int filter_class, bool filter_filled, int entry_nb, CDataPacketPtr packet);
      static void addEdge(int edgeID, int toID, CDataPacketPtr packet);
      static void allocNodeEdge();

    private:

      //! List of fields marked for visualizing of their workflow
      static vector <StdString> fields;

      //! List of connected filters for fields for visualizing of their workflow
      static vector <StdString> filters;

      //! Fields to filters connectivity
      static vector <pair<int, int> > fieldsToFilters;

      static void buildStaticWorkflow();
      static void buildStaticWorkflow_with_info();
      static void showStaticWorkflow();

      


  };
}

#endif
