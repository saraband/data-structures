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

  priority_queue<
    pair<int, pair<int, int>>,
    vector<pair<int, pair<int, int>>>,
    greater<pair<int, pair<int, int>>>
  > pq;

  for (auto& node : m_nodes) {
    for (auto& edge : )
  }

  return path;
}