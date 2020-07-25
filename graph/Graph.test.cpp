#include "Graph.hpp"

int main ()
{
    typedef Graph<GraphType::UNDIRECTED, int> UndirectedGraph;
    typedef Graph<GraphType::DIRECTED, int> DirectedGraph;

    TEST("Initialize graph", {
      UndirectedGraph uGraph;
      DirectedGraph dGraph;

      ASSERT_EQ(uGraph.state(), "");
      ASSERT_EQ(uGraph.m_nodes.size(), 0);
      ASSERT_EQ(dGraph.state(), "");
      ASSERT_EQ(dGraph.m_nodes.size(), 0);
    })
  return 0;
}