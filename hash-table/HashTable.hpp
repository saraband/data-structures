#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <list>

#include "../Test.hpp"
#include "../Utils.hpp"

constexpr int HASH_TABLE_DEFAULT_CAPACITY = 100;
constexpr int HASH_TABLE_CAPACITY_GROW_RATIO = 2;
constexpr float HASH_TABLE_CAPACITY_GROW_THRESHOLD = 0.8f;

template<typename ValueType>
class HashTable
{
  TESTABLE

  public:
    struct HashElement
    {
      HashElement (int k, const ValueType& v)
        : key     { k }
        , value   { v }
      {}

      int         key;
      ValueType   value;
    };

    HashTable (int baseCapacity = HASH_TABLE_DEFAULT_CAPACITY);
    int size () const;
    const ValueType& get (int key) const;
    void set (int key, const ValueType& value);
    void remove (int key);

  private:
    int hash (int key) const;

    int                                     m_size;
    int                                     m_capacity;
    int                                     m_growCapacityThreshold;
    std::vector<std::list<HashElement>>     m_buckets;
};

#include "HashTable.tpp"

#endif