#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <iostream>
#include <unordered_map>
#include <list>

constexpr int DEFAULT_LRU_CACHE_CAPACITY = 100;

template<typename T, typename U>
class LRUCache
{
  public:
    struct Node
    {
      Node (U* v, std::list<T>::iterator it);
      Node (const Node& other);
      ~Node ();

      U*                      m_value;
      std::list<T>::iterator  m_iterator;
    };

    LRUCache (int capacity = DEFAULT_LRU_CACHE_CAPACITY);
    ~LRUCache ();
    const T* get (T key) const;
    void set (T key, const U& value);
    int size () const;

  private:
    int                             m_capacity;
    std::unordered_map<T, Node*>    m_map;
    std::list<T>                    m_lru;
};

#include "LRUCache.tpp"

#endif