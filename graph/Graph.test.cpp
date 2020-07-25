#include "Graph.hpp"

int main ()
{
  // @TODO
  test::registerTest("Initialize graph", [](){
    Graph<GraphType::UNDIRECTED, int> uGraph;
    Graph<GraphType::DIRECTED, int> dGraph;

    test::assertEq(uGraph.state(), "");
    test::assertEq(uGraph.m_nodes.size(), 0);
    test::assertEq(dGraph.state(), "");
    test::assertEq(dGraph.m_nodes.size(), 0);
  });

  return 0;
}