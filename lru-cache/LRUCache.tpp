#include "LRUCache.hpp"

template<typename KeyType, typename ValueType>
LRUCache<KeyType, ValueType>::LRUCache (int capacity)
  : m_capacity { capacity }
{
  
}

template<typename KeyType, typename ValueType>
const ValueType& LRUCache<KeyType, ValueType>::get (const KeyType& key)
{
  auto node = m_cache.find(key);

  if (node == m_cache.end()) {
    throw std::runtime_error("Key " + toString(key) + " does not exist");
  }
  
  m_lru.erase(node->second.lruItem);
  m_lru.push_front(key);

  return node->second.value;
}

template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::checkSize ()
{
  while (m_lru.size() > m_capacity) {
    m_cache.erase(m_lru.back());
    m_lru.pop_back();
  }
}

template<typename KeyType, typename ValueType>
void LRUCache<KeyType, ValueType>::set (const KeyType& key, const ValueType& value)
{
  auto node = m_cache.find(key);

  // Already exists, erase in lru list
  if (node != m_cache.end()) {
    m_lru.erase(node->second.lruItem);
  }

  // Push front in lru
  m_lru.push_front(key);
  m_cache.insert_or_assign(key, Node(key, value, m_lru.begin()));

  checkSize();
}

template<typename KeyType, typename ValueType>
int LRUCache<KeyType, ValueType>::size () const
{
  return m_lru.size();
}