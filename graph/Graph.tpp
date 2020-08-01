#include "Graph.hpp"

template<GraphType::GraphType graphType, typename ValueType>
Graph<graphType, ValueType>::Graph ()
  : m_numEdges { 0 }
{

}

template<GraphType::GraphType graphType, typename ValueType>
Graph<graphType, ValueType>::~Graph ()
{
  // Delete all nodes and edges
  for (auto& node : m_nodes) {
    for (auto& edge : node.second->edges)
      delete edge.second;
    delete node.second;
  }
}

template<GraphType::GraphType graphType, typename ValueType>
void Graph<graphType, ValueType>::addNode (int key, const ValueType& value)
{
  // Duplicate node key
  if (getNode(key) != nullptr) {
    return;
  }

  m_nodes.insert({ key, new Node(key, value) });
}

template<GraphType::GraphType graphType, typename ValueType>
void Graph<graphType, ValueType>::addEdge(int keyA, int keyB, int weight)
{
  auto nodeA = getNode(keyA);
  auto nodeB = getNode(keyB);

  if (!nodeA || !nodeB) {
    throw std::runtime_error("Cannot add edge between node " + toString(keyA) + " and " + toString(keyB) + ": One of the node does not exist");
  }

  nodeA->edges.insert({ keyB, new Edge(nodeB, weight) });

  if (graphType == GraphType::UNDIRECTED)
    nodeB->edges.insert({ keyA, new Edge(nodeA, weight) });
  
  m_numEdges++;
}

template<GraphType::GraphType graphType, typename ValueType>
typename Graph<graphType, ValueType>::Node* Graph<graphType, ValueType>::getNode (int key) const
{
  auto found = m_nodes.find(key);

  if (found == m_nodes.end())
    return nullptr;
  
  return found->second;
}

template<GraphType::GraphType graphType, typename ValueType>
int Graph<graphType, ValueType>::size () const
{
  return m_nodes.size();
}