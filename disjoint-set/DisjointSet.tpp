#include "DisjointSet.hpp"

template<typename KeyType>
DisjointSet<KeyType>::DisjointSet ()
{
  
}

template<typename KeyType>
DisjointSet<KeyType>::DisjointSet (const std::vector<KeyType>& array)
{
  for (KeyType key : array) {
    add(key);
  }
}


template<typename KeyType>
void DisjointSet<KeyType>::add (KeyType key)
{
  m_parents[key] = key;
}

template<typename KeyType>
void DisjointSet<KeyType>::unite (KeyType a, KeyType b)
{
  // Find a and b representatives
  KeyType aRep = find(a);
  KeyType bRep = find(b);

  // a and b already in the same set
  if (aRep == bRep)
    return;

  // Find ranks for a and b sets
  auto aRankValue = m_ranks.find(aRep);
  auto bRankValue = m_ranks.find(bRep);
  int aRank = aRankValue == m_ranks.end()
    ? 0
    : aRankValue->second;
  int bRank = bRankValue == m_ranks.end()
    ? 0
    : bRankValue->second;

  // Append the tree with the lowest rank to the highest
  if (aRank < bRank) {
    m_parents[aRep] = bRep;
  } else if (aRank > bRank) {
    m_parents[bRep] = aRep;

  // Same rank, append arbitrarily
  } else {
    m_parents[aRep] = bRep;
    m_ranks.insert_or_assign(bRep, bRank + 1);
  }
}

template<typename KeyType>
KeyType DisjointSet<KeyType>::find (KeyType key)
{
  // Find direct parent of element
  KeyType parent = m_parents.find(key)->second;

  // Direct parent is the representative
  if (key == parent)
    return key;

  // Search recursively in the parents which is the representative
  KeyType rep = find(parent);

  // Compress the path to the representative by making it the direct parent
  m_parents[key] = rep;

  return rep;
}