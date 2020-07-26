#include "DisjointSet.hpp"

#include <iostream>

int main ()
{
  // @TODO remove template everywhere
  DisjointSet set{ std::vector<int>{ 0, 1, 2, 3, 4, 5 } };
  set.unite(0, 1);
  set.unite(1, 2);
  set.unite(2, 3);
  set.unite(3, 4);

  return 0;
}