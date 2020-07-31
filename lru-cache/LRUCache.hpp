#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <unordered_map>
#include <list>

#include "../Test.hpp"
#include "../Utils.hpp"

constexpr int DEFAULT_LRU_CACHE_CAPACITY = 100;

using LRUIterator = std::list<int>::iterator;

template<typename KeyType, typename ValueType>
class LRUCache
{
  TESTABLE
  
  public:
    struct Node
    {
      Node (const KeyType& k, const ValueType& v, LRUIterator i)
        : key       { k }
        , value     { v }
        , lruItem   { i }
      {}

      KeyType         key;
      ValueType       value;
      LRUIterator     lruItem;
    };

    LRUCache (int capacity = DEFAULT_LRU_CACHE_CAPACITY);
    const ValueType& get (const KeyType& key);
    void checkSize ();
    void set (const KeyType& key, const ValueType& value);
    int size () const;

  private:
    int                                   m_capacity;
    std::unordered_map<KeyType, Node>     m_cache;
    std::list<KeyType>                    m_lru;
};

#include "LRUCache.tpp"

#endif