#include "HashTable.hpp"

int main ()
{
  TEST("Empty HashTable", {
    HashTable<int> map;

    ASSERT_EQ(map.m_size, 0);
    ASSERT_EQ(map.m_capacity, map.m_buckets.capacity());
  });

  TEST("set", {
    HashTable<int> map;
    map.set(5, 5);
    map.set(10, 10);

    ASSERT_EQ(map.m_size, 2);
    ASSERT_EQ(map.m_buckets[5].size(), 1);
    ASSERT_EQ(map.m_buckets[10].size(), 1);
  });

  TEST("set multiple time the same key", {
    HashTable<int> map;
    map.set(5, 5);
    map.set(5, 5);

    ASSERT_EQ(map.m_size, 1);
    ASSERT_EQ(map.m_buckets[5].size(), 1);
  });

  TEST("get", {
    HashTable<int> map;
    map.set(5, 50);
    map.set(10, 100);

    ASSERT_EQ(map.get(5).value, 50);
    ASSERT_EQ(map.get(10).value, 100);
  });

  TEST("get a key that does not exist", {
    HashTable<int> map;
    map.set(5, 5);

    ASSERT_EQ(map.get(10) == map.nil(), true);// @TODO pas bon, changer ça
  });

  TEST("remove", {
    HashTable<int> map;
    map.set(5, 5);
    map.set(10, 10);
    map.remove(10);

    ASSERT_EQ(map.m_size, 1);
    ASSERT_EQ(map.get(10) == map.nil(), true); // @TODO pas bon, changer ça
  });

  // @TODO test grow capacity

  return 0;
}