#include "HashTable.hpp"

template<typename ValueType>
HashTable<ValueType>::HashTable (int baseCapacity)
  : m_size                    { 0 }
  , m_capacity                { baseCapacity }
  , m_growCapacityThreshold   { static_cast<int>(baseCapacity * HASH_TABLE_CAPACITY_GROW_THRESHOLD) }
{
  m_buckets.resize(m_capacity);
}

template<typename ValueType>
int HashTable<ValueType>::hash (int key) const
{
  return key % m_capacity;
}

template<typename ValueType>
int HashTable<ValueType>::size () const
{
  return m_size;
}

template<typename ValueType>
const ValueType& HashTable<ValueType>::get (int key) const
{
  const auto& bucket = m_buckets[hash(key)];
  for (const auto& element : bucket) {
    if (element.key == key) {
      return element.value;
    }
  }

  throw std::runtime_error("Key " + toString(key) + " does not exist in hash table");
}

template<typename ValueType>
void HashTable<ValueType>::set (int key, const ValueType& value)
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
    m_capacity *= HASH_TABLE_CAPACITY_GROW_RATIO;
    m_growCapacityThreshold = m_capacity * HASH_TABLE_CAPACITY_GROW_THRESHOLD;

    auto tempBuckets{ std::move(m_buckets) };
    m_buckets.resize(m_capacity);

    // No need to check for key duplicate
    for (auto& bucket : tempBuckets) {
      for (auto& element : bucket) {
        m_buckets[hash(element.key)].push_back(HashElement(element));
      }
    }
  }
}

template<typename ValueType>
void HashTable<ValueType>::remove (int key)
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