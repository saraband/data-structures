#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <unordered_map>
#include <list>

// @TODO  clean + template

constexpr int DEFAULT_LRU_CACHE_CAPACITY = 100;

using LRUIterator = std::list<int>::iterator;

class LRUCache
{
  public:
    struct Node
    {
      Node (int k, char v, LRUIterator i)
        : key       { k }
        , value     { v }
        , lruItem   { i }
      {}

      int           key;
      char          value;
      LRUIterator   lruItem;
    };

    LRUCache (int capacity = DEFAULT_LRU_CACHE_CAPACITY)
      : m_capacity { capacity }
    {}

/*     char get (int key) const
    {
      auto node = m_cache.find(key);

      if (node == m_cache.end()) {
        std::cout << "Cannot get key " << key << std::endl; // @TODO
        return 'z';
      }
      
      std::iter_swap(m_lru.begin(), node->second.lruItem);

      checkSize(); // @TODO better name

      return node->second.value;
    }

    void checkSize ()
    {
      while (m_lru.size() > m_capacity) {
        m_cache.erase(m_lru.begin()->key);
        m_lru.pop_back();
      }
    } */

    void set (int key, char value)
    {
      auto node = m_cache.find(key);

      // Already exists, erase in lru list
      if (node != m_cache.end()) {
        m_lru.erase(node->second.lruItem);
        // @TODO this swaps the values
      }

      // Push front in lru
      // m_lru.push_front(key);
      // m_cache.insert_or_assign({ key, Node(key, value, m_lru.begin()) });

      // checkSize();
    }

    int size () const
    {
      return m_lru.size();
    }

  private:
    int                               m_capacity;
    std::unordered_map<int, Node>     m_cache;
    std::list<int>                    m_lru;
};

#endif