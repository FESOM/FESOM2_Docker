#ifndef __GRAPHVIZ_HPP__
#define __GRAPHVIZ_HPP__

#include <algorithm>
#include <boost/utility.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

namespace xios
{

  class CGraphviz
  {

    public:

      CGraphviz();
      static void buildWorkflowGraphDot();
      static void buildWorkflowGraphVisjs_with_info();
      static void showStaticWorkflowGraph();

    private:
      template <class Graph> struct exercise_vertex;

  }; // class CGraphviz

  template <class Graph> struct CGraphviz::exercise_vertex {
    exercise_vertex(Graph& g_) : g(g_) { }
    typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;
    void operator()(const Vertex& v) const { } Graph& g;
  };

} // namespace xios

#endif
