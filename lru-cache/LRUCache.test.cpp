#include "LRUCache.hpp"

int main ()
{
  LRUCache cache;
  cache.set(5, 'a');
  cache.set(5, 'a');
  
  return 0;
}