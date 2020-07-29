#include "Graph.hpp"

template<GraphType::GraphType graphType, typename T>
Graph<graphType, T>::Graph ()
  : m_numEdges { 0 }
{

}

template<GraphType::GraphType graphType, typename T>
Graph<graphType, T>::~Graph ()
{
  for (auto& node : m_nodes) {
    for (auto& edge : node.second->edges)
      delete edge.second;

    delete node.second;
  }
}

template<GraphType::GraphType graphType, typename T>
void Graph<graphType, T>::addNode (int key, T value)
{
  if (getNode(key) != nullptr) {
    // @TODO throw ? or not ?
    std::cout << "Error: Duplicate key '" + toString(key) + "' in graph." << std::endl;
    return;
  }

  m_nodes.insert({ key, new Node(key, value) });
}

template<GraphType::GraphType graphType, typename T>
void Graph<graphType, T>::addEdge(int keyA, int keyB, int weight)
{
  auto nodeA = getNode(keyA);
  auto nodeB = getNode(keyB);

  if (!nodeA || !nodeB) {
    // @TODO better error handling
    std::cout << "Error: Unable to create edge between keys '" + toString(keyA);
    std::cout << "' and '"  + toString(keyB) + "' in graph.";
    return;
  }

  nodeA->edges.insert({ keyB, new Edge(nodeB, weight) });

  if (graphType == GraphType::UNDIRECTED)
    nodeB->edges.insert({ keyA, new Edge(nodeA, weight) });
  
  m_numEdges++;
}