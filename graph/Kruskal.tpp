#include <vector>

#include "Graph.hpp"
#include "../disjoint-set/DisjointSet.hpp"

template<GraphType::GraphType graphType, typename T>
std::vector<std::pair<int, int>> Graph<graphType, T>::kruskal () const
{
  using namespace std;
  using Edge = pair<int, pair<int, int>>; // [ weight, [ keyA, keyB ] ]

  // Edges forming the result graph
  std::vector<std::pair<int, int>> result;

  if (!m_numEdges)
    return result;

  // All possible edges ordered by min weight
  priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

  // Used to detect cycle in the resulting graph
  DisjointSet<int> set;

  // Add all edges to the min priority queue
  // And all nodes to initialize the disjoint set
  for (const auto& node : m_nodes) {
    for (const auto& edge : node.second->edges) {
      int source = node.second->key;
      int destination = edge.second->destination->key;
      int weight = edge.second->weight;

      pq.push(make_pair(weight, make_pair(source, destination)));
      set.add(source);
      set.add(destination);
    }
  }

  // Priorize edges by min weight
  while (!pq.empty()) {
    auto edge = pq.top();
    int source = edge.second.first;
    int destination = edge.second.second;

    // Edge does not form a cycle in the resulting graph
    // Add it to the result
    if (set.find(source) != set.find(destination)) {
      set.unite(source, destination);
      result.push_back(make_pair(source, destination));
    }

    pq.pop();
  }

  return result;
}