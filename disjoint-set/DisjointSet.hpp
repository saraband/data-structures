#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

template<typename T>
class DisjointSet
{
  public:
    DisjointSet (const std::vector<T>& array);
    void unite (T a, T b);
    int find (T key);

  private:
    std::unordered_map<T, T>    m_sets;
    std::unordered_map<T, int>  m_ranks;
};

#include "DisjointSet.tpp"

#endif