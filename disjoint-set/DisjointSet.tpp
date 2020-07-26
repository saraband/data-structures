#include "DisjointSet.hpp"

template<typename T>
DisjointSet<T>::DisjointSet (const std::vector<T>& array)
{
  for (T key : array) {
    m_sets[key] = key;
  }
}

template<typename T>
void DisjointSet<T>::unite (T a, T b)
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

template<typename T>
int DisjointSet<T>::find (T key)
{
  T parent = m_sets.find(key)->second;

  if (key == parent)
    return key;

  T rep = find(parent);
  m_sets[key] = rep;

  // Reset rank for this set as it has been compressed
  m_ranks[rep] = 0;

  return rep;
}