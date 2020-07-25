#include "HashTable.hpp"

int main ()
{
  test::registerTest("Empty HashTable", [](){
    HashTable<int> map;

    test::assertEq(map.m_size, 0);
    test::assertEq(map.m_capacity, map.m_buckets.capacity());
  });

  test::registerTest("set", [](){
    HashTable<int> map;
    map.set(5, 5);
    map.set(10, 10);

    test::assertEq(map.m_size, 2);
    test::assertEq(map.m_buckets[5].size(), 1);
    test::assertEq(map.m_buckets[10].size(), 1);
  });

  test::registerTest("set multiple time the same key", [](){
    HashTable<int> map;
    map.set(5, 5);
    map.set(5, 5);

    test::assertEq(map.m_size, 1);
    test::assertEq(map.m_buckets[5].size(), 1);
  });

  test::registerTest("get", [](){
    HashTable<int> map;
    map.set(5, 50);
    map.set(10, 100);

    test::assertEq(map.get(5).value, 50);
    test::assertEq(map.get(10).value, 100);
  });

  test::registerTest("get a key that does not exist", [](){
    HashTable<int> map;
    map.set(5, 5);

    test::assertEq(map.get(10) == map.nil(), true);// @TODO pas bon, changer ça
  });

  test::registerTest("remove", [](){
    HashTable<int> map;
    map.set(5, 5);
    map.set(10, 10);
    map.remove(10);

    test::assertEq(map.m_size, 1);
    test::assertEq(map.get(10) == map.nil(), true); // @TODO pas bon, changer ça
  });

  // @TODO test grow capacity

  return 0;
}