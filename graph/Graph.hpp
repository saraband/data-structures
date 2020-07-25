#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <unordered_map>
#include <string>

#include "../Test.hpp"
#include "../Utils.hpp"

namespace GraphType
{
enum GraphType
{
  DIRECTED,
  UNDIRECTED
};
}

template<GraphType::GraphType graphType, typename T>
class Graph
{
  TESTABLE
  struct Node;

  public:
    Graph () {}
    ~Graph ()
    {
      for (auto& node : m_nodes)
        delete node.second;
    }

    void addNode (int key, T value)
    {
      if (m_nodes.find(key) != m_nodes.end()) {
        // @TODO throw ? or not ?
        std::cout << "Error: Duplicate key '" + toString(key) + "' in graph." << std::endl;
        return;
      }

      m_nodes.insert({ key, new Node(key, value) });
    }

    void addEdge(int keyA, int keyB, int weight = 1)
    {
      auto nodeA = m_nodes.find(keyA);
      auto nodeB = m_nodes.find(keyB);

      if (nodeA == m_nodes.end() || nodeB == m_nodes.end()) {
        // @TODO better error handling
        std::cout << "Error: Unable to create edge between keys '" + toString(keyA);
        std::cout << "' and '"  + toString(keyB) + "' in graph.";
        return;
      }

      nodeA->second->edges.insert({ keyB, weight });

      if (graphType == GraphType::UNDIRECTED)
        nodeB->second->edges.insert({ keyA, weight });
    }

  private:
    struct Node
    {
      Node (int k, T v)
        : key     { k }
        , value   { v }
      {}

      int                             key;
      T                               value;
      std::unordered_map<int, int>    edges;
    };

    // For testing
    std::string state () const
    {
      std::string state;

      for (auto& node : m_nodes) {
        int nodeKey = node.first;
        auto nodeEdges = node.second->edges;

        state += toString(nodeKey) + "[ ";
        
        for (auto& edge : nodeEdges) {
          int destination = edge.first;
          int weight = edge.second;

          state += toString(destination) + ':' + toString(weight) + ' ';
        }

        state += "] ";
      }

      return state;
    }

    std::unordered_map<int, Node*>   m_nodes;
};

#endif