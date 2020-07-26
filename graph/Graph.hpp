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
    Graph ();
    ~Graph ();
    void addNode (int key, T value);
    void addEdge(int keyA, int keyB, int weight = 1);
    Node* getNode (int key) const
    {
      auto found = m_nodes.find(key);

      if (found == m_nodes.end())
        return nullptr;
      
      return found->second;
    }

    int size () const
    {
      return m_nodes.size();
    }

    std::string dijkstra (int a, int b) const;

  private:

    struct Edge
    {
      Edge (Node* d, int w = 1)
        : destination   { d }
        , weight        { w }
      {}

      int       weight;
      Node*     destination;
    };

    struct Node
    {
      Node (int k, T v)
        : key     { k }
        , value   { v }
      {}

      Edge* getEdge (int key) const
      {
        auto found = edges.find(key);

        if (found == edges.end())
          return nullptr;
        
        return found->second;
      }

      int                             key;
      T                               value;
      std::unordered_map<int, Edge*>  edges;
    };

    // For testing @TODO is this necessary ?
    std::string state () const
    {
      std::string state;

      for (auto& node : m_nodes) {
        int nodeKey = node.first;
        auto nodeEdges = node.second->edges;

        state += toString(nodeKey) + "[ ";
        
        for (auto& edge : nodeEdges) {
          state += toString(edge.second->destination) + ':' + toString(edge.second->weight) + ' ';
        }

        state += "] ";
      }

      return state;
    }

    std::unordered_map<int, Node*>   m_nodes;
};

#include "Graph.tpp"
#include "Dijkstra.tpp"

#endif