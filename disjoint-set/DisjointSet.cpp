#include "DisjointSet.hpp"

DisjointSet::DisjointSet (const std::vector<int>& array)
{
  for (int key : array) {
    m_sets[key] = key;
  }
}

void DisjointSet::unite (int a, int b)
{
  int aRep = find(a);
  int bRep = find(b);

  if (aRep == bRep)
    return;

  int aRank = (m_ranks.find(aRep) == m_ranks.end()) || 0;
  int bRank = (m_ranks.find(bRep) == m_ranks.end()) || 0;

  if (aRank < bRank) {
    m_sets[aRep] = bRep;
  } else if (aRank > bRank) {
    m_sets[bRep] = aRep;
  } else {
    m_sets[aRep] = bRep;
    m_ranks.insert_or_assign(bRep, bRank + 1);
  }
}

int DisjointSet::find (int key)
{
  int parent = m_sets.find(key)->second;

  if (key == parent)
    return key;

  int rep = find(parent);
  m_sets[key] = rep;

  // Reset rank for this set as it has been compressed
  m_ranks[rep] = 0;

  return rep;
}