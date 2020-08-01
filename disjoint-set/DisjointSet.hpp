#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

#include "../Test.hpp"
#include "../Utils.hpp"

template<typename KeyType>
class DisjointSet
{
  TESTABLE

  public:
    DisjointSet ();
    DisjointSet (const std::vector<KeyType>& array);
    void add (KeyType key);
    void unite (KeyType a, KeyType b);
    KeyType find (KeyType key);

  private:
    std::unordered_map<KeyType, KeyType>    m_parents;
    std::unordered_map<KeyType, int>        m_ranks;
};

#include "DisjointSet.tpp"

#endif