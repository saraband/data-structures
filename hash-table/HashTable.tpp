#include "HashTable.hpp"

template<typename T>
HashTable<T>::HashTable ()
  : m_size                    { 0 }
  , m_capacity                { HASH_TABLE_DEFAULT_CAPACITY }
  , m_growCapacityThreshold   { static_cast<int>(HASH_TABLE_DEFAULT_CAPACITY * HASH_TABLE_GROW_THRESHOLD) }
{
  m_buckets.resize(m_capacity);
}

template<typename T>
int HashTable<T>::hash (int key) const
{
  return key % m_capacity;
}

template<typename T>
int HashTable<T>::size () const
{
  return m_size;
}

template<typename T>
typename HashTable<T>::HashElement const& HashTable<T>::nil () const
{
  static HashElement nil(0, 0);
  return nil;
}

template<typename T>
typename HashTable<T>::HashElement const& HashTable<T>::get (int key) const
{
  const auto& bucket = m_buckets[hash(key)];
  for (const auto& element : bucket) {
    if (element.key == key) {
      return element;
    }
  }

  return nil();
}

template<typename T>
void HashTable<T>::set (int key, T value)
{
  auto& bucket = m_buckets[hash(key)];
  for (const auto& element : bucket) {
    // Element is already set, abort
    if (element.key == key)
      return;
  }

  // Push it into the right bucket
  bucket.push_back(HashElement(key, value));
  m_size++;

  // Hashtable has reached 80% capacity
  // Double the buckets and re-hash everything
  if (m_size >= m_growCapacityThreshold) {
    return;
    m_capacity *= HASH_TABLE_GROW_RATIO;
    m_growCapacityThreshold = m_capacity * HASH_TABLE_GROW_THRESHOLD;

    // @TODO hash everything again
  }
}

template<typename T>
void HashTable<T>::remove (int key)
{
  auto& bucket = m_buckets[hash(key)];
  for (auto it = bucket.begin(); it != bucket.end(); it++) {
    if (it->key == key) {
      bucket.erase(it);
      m_size--;
      return;
    }
  }
}