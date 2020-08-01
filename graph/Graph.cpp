#include "Graph.hpp"

int main ()
{
  test::registerTest("Initialize graph", []() {
    Graph<GraphType::UNDIRECTED, int> uGraph;
    Graph<GraphType::DIRECTED, int> dGraph;

    test::expect(uGraph.m_nodes.size() == 0);
    test::expect(dGraph.m_nodes.size() == 0);
  });

  test::registerTest("Add nodes", []() {
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);

    test::expect(graph.m_nodes.size() == 2);
    test::expect(graph.getNode(5)->key == 5);
  });

  test::registerTest("Undirected: Add edges", []() {
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);
    graph.addNode(15, 15);
    graph.addEdge(5, 7);
    graph.addEdge(5, 15);

    test::expect(graph.getNode(5)->edges.size() == 2);
    test::expect(graph.getNode(5)->getEdge(7) != nullptr);
    test::expect(graph.getNode(5)->getEdge(15) != nullptr);

    test::expect(graph.getNode(7)->edges.size() == 1);
    test::expect(graph.getNode(7)->getEdge(5) != nullptr);
  
    test::expect(graph.getNode(15)->edges.size() == 1);
    test::expect(graph.getNode(15)->getEdge(5) != nullptr);
  });

  test::registerTest("Directed: Add edges", []() {
    Graph<GraphType::DIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);
    graph.addNode(15, 15);
    graph.addEdge(5, 7);
    graph.addEdge(5, 15);

    test::expect(graph.getNode(5)->edges.size() == 2);
    test::expect(graph.getNode(5)->getEdge(7) != nullptr);
    test::expect(graph.getNode(5)->getEdge(15) != nullptr);

    test::expect(graph.getNode(7)->edges.size() == 0);
    test::expect(graph.getNode(7)->getEdge(5) == nullptr);
  
    test::expect(graph.getNode(15)->edges.size() == 0);
    test::expect(graph.getNode(15)->getEdge(5) == nullptr);
  });

  test::registerTest("Unweighted graph", []() {
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);
    graph.addEdge(5, 7);

    test::expect(graph.getNode(5)->getEdge(7)->weight == 1);
    test::expect(graph.getNode(7)->getEdge(5)->weight == 1);
  });

  test::registerTest("Weighted graph", []() {
    Graph<GraphType::DIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);
    graph.addEdge(5, 7, 50);
    graph.addEdge(7, 5, 10);

    test::expect(graph.getNode(5)->getEdge(7)->weight == 50);
    test::expect(graph.getNode(7)->getEdge(5)->weight == 10);
  });

  test::registerTest("Dijkstra", []() {
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(0, 0);
    graph.addNode(1, 1);
    graph.addNode(2, 2);
    graph.addNode(3, 3);
    graph.addNode(4, 4);
    graph.addEdge(0, 1, 5);
    graph.addEdge(0, 2, 10);
    graph.addEdge(2, 3, 30);
    graph.addEdge(2, 4, 20);
    graph.addEdge(3, 4, 5);
    

    auto result = graph.dijkstra(0, 3);
    auto distance = result.first;
    auto path = result.second;
    std::vector<int> expectedPath{ 0, 2, 4, 3 };
    int expectedDistance = 35;

    test::expect(distance == expectedDistance);
    test::expect(path.size() == expectedPath.size());

    auto comparePaths = [&path, &expectedPath]() {
      for (int i = 0; i < path.size(); ++i) {
        if (path[i] != expectedPath[i]) {
          throw std::runtime_error("Path does not follow expected path");
        }
      }
    };

    test::expectNoThrow(comparePaths);
  });

  test::registerTest("Kruskal", []() {
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(0, 0);
    graph.addNode(1, 1);
    graph.addNode(2, 2);
    graph.addNode(3, 3);
    graph.addNode(4, 4);
    graph.addNode(5, 5);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 4, 5);
    graph.addEdge(1, 3, 10);
    graph.addEdge(4, 5, 40);
    graph.addEdge(3, 4, 1);
    graph.addEdge(2, 3, 20);

    auto edges = graph.kruskal();
    std::vector<std::pair<int, int>> expectedEdges{ { 3, 4 }, { 1, 4 }, { 0, 1 }, { 2, 3 }, { 4, 5 } };
    test::expect(edges.size() == expectedEdges.size());

    auto compareEdges = [&edges, &expectedEdges]() {
      for (int i = 0; i < edges.size(); ++i) {
        if (
          (edges[i].first == expectedEdges[i].first && edges[i].second == expectedEdges[i].second) ||
          (edges[i].first == expectedEdges[i].second && edges[i].second == expectedEdges[i].first)
        ) {
          continue;
        }

        throw std::runtime_error("Different edges");
      }
    };

    test::expectNoThrow(compareEdges);
  });

  return 0;
}