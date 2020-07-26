#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

class DisjointSet
{
  public:
    DisjointSet (const std::vector<int>& array);
    void unite (int a, int b);
    int find (int key);

  private:
    std::unordered_map<int, int>    m_sets;
    std::unordered_map<int, int>    m_ranks;
};

#endif