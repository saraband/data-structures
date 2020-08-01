#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>
#include <unordered_map>
#include <string>
#include <vector>

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

template<GraphType::GraphType graphType, typename ValueType>
class Graph
{
  TESTABLE

  public:
    struct Node;
    struct Edge
    {
      Edge (Node* d, int w = 1)
        : destination   { d }
        , weight        { w }
      {}

      Node*     destination;
      int       weight;
    };

    struct Node
    {
      Node (int k, const ValueType& v)
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
      ValueType                       value;
      std::unordered_map<int, Edge*>  edges;
    };

    Graph ();
    ~Graph ();
    void addNode (int key, const ValueType& value);
    void addEdge(int keyA, int keyB, int weight = 1);
    Node* getNode (int key) const;
    int size () const;
    std::pair<int, std::vector<int>> dijkstra (int a, int b) const;
    std::vector<std::pair<int, int>> kruskal () const;

  private:
    std::unordered_map<int, Node*>   m_nodes;
    int                              m_numEdges;
};

#include "Graph.tpp"
#include "Dijkstra.tpp"
#include "Kruskal.tpp"

#endif