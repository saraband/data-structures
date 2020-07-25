#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <list>

#include "../Test.hpp"
#include "../Utils.hpp"

constexpr int HASH_TABLE_DEFAULT_CAPACITY = 100;
constexpr int HASH_TABLE_GROW_RATIO = 2;
constexpr float HASH_TABLE_GROW_THRESHOLD = 0.8f;

template<typename T>
class HashTable
{
  TESTABLE

  public:
    struct HashElement
    {
      HashElement (int k, T v)
        : key     { k }
        , value   { v }
      {}

      bool operator== (const HashElement& other) const
      {
        return this == &other;
      }

      bool operator!= (const HashElement& other) const
      {
        return this != &other;
      }

      int key;
      T value;
    };

    HashTable ();

    int size () const;
    const HashElement& nil () const;
    const HashElement& get (int key) const;
    void set (int key, T value);
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