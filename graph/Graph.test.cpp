#include "Graph.hpp"

int main ()
{
  test::registerTest("Initialize graph", []() {
    Graph<GraphType::UNDIRECTED, int> uGraph;
    Graph<GraphType::DIRECTED, int> dGraph;

    test::assertEq(uGraph.state(), "");
    test::assertEq(uGraph.m_nodes.size(), 0);
    test::assertEq(dGraph.state(), "");
    test::assertEq(dGraph.m_nodes.size(), 0);
  });

  test::registerTest("Add nodes", []() {
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);

    test::assertEq(graph.m_nodes.size(), 2);
    test::assertEq(graph.m_nodes.find(5) != graph.m_nodes.end(), true);
    test::assertEq(graph.m_nodes.find(7) != graph.m_nodes.end(), true);
  });

  test::registerTest("Undirected: Add edges", []() {
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);
    graph.addNode(15, 15);
    graph.addEdge(5, 7);
    graph.addEdge(5, 15);

    test::assertEq(graph.getNode(5)->edges.size(), 2);
    test::assertEq(graph.getNode(5)->getEdge(7) != nullptr, true);
    test::assertEq(graph.getNode(5)->getEdge(15) != nullptr, true);

    test::assertEq(graph.getNode(7)->edges.size(), 1);
    test::assertEq(graph.getNode(7)->getEdge(5) != nullptr, true);
  
    test::assertEq(graph.getNode(15)->edges.size(), 1);
    test::assertEq(graph.getNode(15)->getEdge(5) != nullptr, true);
  });

  test::registerTest("Directed: Add edges", []() {
    Graph<GraphType::DIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);
    graph.addNode(15, 15);
    graph.addEdge(5, 7);
    graph.addEdge(5, 15);

    test::assertEq(graph.getNode(5)->edges.size(), 2);
    test::assertEq(graph.getNode(5)->getEdge(7) != nullptr, true);
    test::assertEq(graph.getNode(5)->getEdge(15) != nullptr, true);

    test::assertEq(graph.getNode(7)->edges.size(), 0);
    test::assertEq(graph.getNode(7)->getEdge(5), nullptr); // @TODO assertNotEq ?
  
    test::assertEq(graph.getNode(15)->edges.size(), 0);
    test::assertEq(graph.getNode(15)->getEdge(5), nullptr);
  });

  return 0;
}