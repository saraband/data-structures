#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

#include "../Test.hpp"
#include "../Utils.hpp"

template<typename T>
class DisjointSet
{
  TESTABLE

  public:
    DisjointSet ();
    DisjointSet (const std::vector<T>& array);
    void add (T key);
    void unite (T a, T b);
    T find (T key);

  private:
    std::unordered_map<T, T>    m_parents;
    std::unordered_map<T, int>  m_ranks;
};

#include "DisjointSet.tpp"

#endif