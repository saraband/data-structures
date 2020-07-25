#include "Graph.hpp"

int main ()
{
    Graph<GraphType::UNDIRECTED, int> graph;
    graph.addNode(5, 5);
    graph.addNode(7, 7);
    graph.addEdge(5, 7, 20);

    std::cout << graph.state() << std::endl;
  return 0;
}