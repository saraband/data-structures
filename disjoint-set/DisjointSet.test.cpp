#include "DisjointSet.hpp"

#include <iostream>

int main ()
{
  // @TODO tester tout ça, pas sur de l'implementation...
  DisjointSet set{ std::vector<int>{ 0, 1, 2, 3, 4, 5 } };
  set.unite(0, 1);
  set.unite(1, 2);
  set.unite(2, 3);
  set.unite(3, 4);

  return 0;
}
