#include "LRUCache.hpp"

int main ()
{
  test::registerTest("Get a key that does not exist in cache", []() {
    LRUCache<int, int> cache;

    test::expectThrow([&cache]() {
      cache.get(42);
    });
  });

  test::registerTest("Set a key in cache", []() {
    LRUCache<int, int> cache;
    cache.set(5, 5);

    test::expect(cache.get(5) == 5);
    test::expect(cache.m_lru.front() == 5);
  });

  test::registerTest("Set a key that already exists", []() {
    LRUCache<int, int> cache;
    cache.set(5, 5);
    cache.set(5, 5);

    test::expect(cache.get(5) == 5);
    test::expect(cache.m_lru.front() == 5);
    test::expect(cache.m_cache.size() == 1);
    test::expect(cache.m_lru.size() == 1);
  });

  test::registerTest("LRU order", []() {
    LRUCache<int, int> cache;
    cache.set(5, 5);
    cache.set(6, 6);
    cache.set(7, 7);

    test::expect(cache.m_lru.front() == 7);
    test::expect(cache.m_lru.back() == 5);

    cache.set(5, 5);

    test::expect(cache.m_lru.front() == 5);
    test::expect(cache.m_lru.back() == 6);
  });

  test::registerTest("LRU deletion when reaching max capacity", []() {
    LRUCache<int, int> cache{ 2 };
    cache.set(5, 5);
    cache.set(6, 6);
    cache.set(7, 7);

    test::expect(cache.m_lru.front() == 7);
    test::expect(cache.m_lru.back() == 6);
    test::expectThrow([&cache]() {
      cache.get(5);
    });
  });

  return 0;
}