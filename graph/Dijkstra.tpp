#include <vector>
#include <queue>

#include "Graph.hpp"
#include "../Utils.hpp"

template<GraphType::GraphType graphType, typename T>
std::pair<int, std::vector<int> > Graph<graphType, T>::dijkstra (int keySource, int keyDestination) const
{
  using namespace std;
  using Distance = pair<int, int>; // [ distance, parent ]

  if (!getNode(keySource) || !getNode(keyDestination) || keySource == keyDestination)
    throw std::runtime_error("Invalid arguments: node source/dest does not exist or source is already the destination");
  
  constexpr int INFINITY = INT_MAX;
  unordered_map<int, pair<int, int>> distances;

  // Set all distances from source to every node to infinity
  for (auto& node : m_nodes) {
    distances.insert({ node.first, make_pair(INFINITY, -1) });
  }

  // Utility function to quickly get a distance for a node
  auto getDistance = [&distances](int key) {
    return distances.find(key)->second.first;
  };

  // To access minimum distance first
  priority_queue<Distance, vector<Distance>, greater<Distance>> pq;

  // Add the source node to the pq
  pq.push(make_pair(0, keySource));
  distances.insert_or_assign(keySource, make_pair(0, -1));

  // While there are still nodes we can access
  while (!pq.empty()) {
    // Process node with minimum distance to source node
    int key = pq.top().second;
    pq.pop();
    int distance = getDistance(key);
    auto node = getNode(key);

    // Process all of its edges
    for (auto& edge : node->edges) {
      int edgeWeight = edge.second->weight;
      int edgeDestinationKey = edge.second->destination->key;

      // If that edge allows you to take a shorter path to its destination node
      // Update the distance for destination node and add it to the pq
      if (distance + edgeWeight < getDistance(edgeDestinationKey)) {
        distances.insert_or_assign(edgeDestinationKey, make_pair(distance + edgeWeight, key));
        pq.push(make_pair(distance + edgeWeight, edgeDestinationKey));
      }
    }
  }


  // Go through the distances parents to backtrack our resulting path
  std::vector<int> resultPath;
  int parent = distances.find(keyDestination)->second.second;
  int current = keyDestination;

  // While we are not back at the source node
  while (parent != -1) {
    // Add the current node to the result path
    resultPath.insert(resultPath.begin(), current);

    // Backtrack to parent node
    current = parent;
    parent = distances.find(parent)->second.second;
  }

  if (!resultPath.empty())
    resultPath.insert(resultPath.begin(), keySource);

  return make_pair(getDistance(keyDestination), resultPath);
}