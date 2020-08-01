#include "HashTable.hpp"

int main ()
{
  test::registerTest("Empty HashTable", []() {
    HashTable<int> map;

    test::expect(map.m_size == 0);
    test::expect(map.m_capacity == map.m_buckets.capacity());
  });

  test::registerTest("set", []() {
    HashTable<int> map;
    map.set(5, 5);
    map.set(105, 105);
    map.set(10, 10);

    test::expect(map.m_size == 3);
    test::expect(map.m_buckets[5].size() == 2);
    test::expect(map.m_buckets[5].front().value == 5);
    test::expect(map.m_buckets[5].back().value == 105);
    test::expect(map.m_buckets[10].size() == 1);
    test::expect(map.m_buckets[10].front().value == 10);
  });

  test::registerTest("set multiple time the same key", []() {
    HashTable<int> map;
    map.set(5, 5);
    map.set(5, 5);

    test::expect(map.m_size == 1);
    test::expect(map.m_buckets[5].size() == 1);
  });

  test::registerTest("get", []() {
    HashTable<int> map;
    map.set(5, 50);
    map.set(10, 100);

    test::expect(map.get(5) == 50);
    test::expect(map.get(10) == 100);
  });

  test::registerTest("get a key that does not exist", []() {
    HashTable<int> map;
    map.set(5, 5);

    test::expectThrow([&map]() {
      map.get(10);
    });
  });

  test::registerTest("remove", []() {
    HashTable<int> map;
    map.set(5, 5);
    map.set(10, 10);
    map.remove(10);

    test::expect(map.m_size == 1);
    test::expectThrow([&map]() {
      map.get(10);
    });
  });

  test::registerTest("grow capacity", []() {
    HashTable<int> map(10);

    // Reach 60% capacity
    map.set(3, 3);
    map.set(13, 13);
    map.set(4, 4);
    map.set(14, 14);
    map.set(47, 47);
    map.set(12, 12);

    test::expect(map.m_capacity == 10);
    test::expect(map.m_growCapacityThreshold == 8);

    // Keys 3 and 13 in the same bucket
    test::expect(map.m_buckets[3].size() == 2);
    test::expect(map.m_buckets[3].front().value == 3);
    test::expect(map.m_buckets[3].back().value == 13);

    // Reach 80%
    map.set(48, 48);
    map.set(11, 11);

    test::expect(map.m_capacity == 20);
    test::expect(map.m_growCapacityThreshold == 16);

    // Since the whole table has been re-hashed,
    // Keys 3 and 13 should be in separate buckets now
    test::expect(map.m_buckets[3].size() == 1);
    test::expect(map.m_buckets[3].front().value == 3);
    test::expect(map.m_buckets[13].size() == 1);
    test::expect(map.m_buckets[13].front().value == 13);
  });

  return 0;
}