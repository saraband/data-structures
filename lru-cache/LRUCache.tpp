#include "LRUCache.hpp"

template<typename T, typename U>
LRUCache<T, U>::LRUCache (int capacity)
  : m_capacity    { capacity }
{

}

template<typename T, typename U>
LRUCache<T, U>::~LRUCache ()
{
  for (auto& value : m_map)
    delete value->second;
}

template<typename T, typename U>
const T* LRUCache<T, U>::get (T key) const
{
  auto found = m_map.find(key);

  if (found == m_map.end())
    return nullptr;

  return found->second->value;
}

template<typename T, typename U>
void LRUCache<T, U>::set (T key, const U& value)
{
/*   auto found = m_map.find(key);

  if (found == m_map.end()) {
    
  } */
}

template<typename T, typename U>
int LRUCache<T, U>::size () const
{
  return m_lru.size();
}

template<typename T, typename U>
LRUCache<T, U>::Node::Node (U* v, std::list<T>::iterator it)
  : m_value     { v }
  , m_iterator  { it }
{

}

template<typename T, typename U>
LRUCache<T, U>::Node::Node (const LRUCache<T, U>::Node& other)
  : m_value     { other.m_value }
  , m_iterator  { other.m_iterator }
{

}

template<typename T, typename U>
LRUCache<T, U>::Node::~Node ()
{
  delete m_value;
}