#include "Graph.hpp"
#include "../Utils.hpp"

#include <queue>
#include <vector>
#include <string>

// @TODO pour dijkstra et kruskal trouver un moyen de checker si les conditions pour l'algorithme sont bien présente
// i.e. pour dijkstra => ponderation non négative et pour kruskal aussi
template<GraphType::GraphType graphType, typename T>
std::string Graph<graphType, T>::kruskal () const
{
  using namespace std;

  if (!m_numEdges)
    return "";
  
  constexpr int INFINITY = INT_MAX;
  unordered_map<int, pair<int, int>> distances;

  for (auto& node : m_nodes) {
    distances.insert({ node.first, make_pair(INFINITY, -1) });
  }

  auto getDistance = [&distances](int key) {
    return distances.find(key)->second.first;
  };

  priority_queue<
    pair<int, int>,
    vector<pair<int, int>>,
    greater<pair<int, int>>
  > pq;

  pq.push(make_pair(0, keySource));
  distances.insert_or_assign(keySource, make_pair(0, -1));

  while (!pq.empty()) {
    int key = pq.top().second;
    pq.pop();
    int distance = getDistance(key);
    auto node = getNode(key);

    for (auto& edge : node->edges) {
      int edgeWeight = edge.second->weight;
      int edgeDestinationKey = edge.second->destination->key;

      if (distance + edgeWeight < getDistance(edgeDestinationKey)) {
        distances.insert_or_assign(edgeDestinationKey, make_pair(distance + edgeWeight, key));
        pq.push(make_pair(distance + edgeWeight, edgeDestinationKey));
      }
    }
  }

  // @TODO clean
  std::string path;
  int parent = distances.find(keyDestination)->second.second;
  int current = keyDestination;

  while (parent != -1) {
    path = toString(current) + ' ' + path;
    current = parent;
    parent = distances.find(parent)->second.second;
  }

  if (!path.empty()) {
    path = "[" + toString(getDistance(keyDestination)) + "] " + toString(keySource) + ' ' + path;
  }

  return path;
}