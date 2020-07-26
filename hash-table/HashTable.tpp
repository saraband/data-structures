#include "HashTable.hpp"

template<typename T>
HashTable<T>::HashTable (int baseCapacity)
  : m_size                    { 0 }
  , m_capacity                { baseCapacity }
  , m_growCapacityThreshold   { static_cast<int>(baseCapacity * HASH_TABLE_CAPACITY_GROW_THRESHOLD) }
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
  static HashElement nil;
  return nil;
}

template<typename T>
typename HashTable<T>::HashElement const& HashTable<T>::get (int key) const
{
  const auto& bucket = m_buckets[hash(key)];
  for (const auto& element : bucket) {
    if (element.key() == key) {
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
    if (element.key() == key)
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
        m_buckets[hash(element.key())].push_back(HashElement(element));
      }
    }
  }
}

template<typename T>
void HashTable<T>::remove (int key)
{
  auto& bucket = m_buckets[hash(key)];
  for (auto it = bucket.begin(); it != bucket.end(); it++) {
    if (it->key() == key) {
      bucket.erase(it);
      m_size--;
      return;
    }
  }
}

template<typename T>
HashTable<T>::HashElement::HashElement ()
  : m_key     { 0 }
  , m_value   { nullptr }
{}

template<typename T>
HashTable<T>::HashElement::HashElement (int k, const T& v)
  : m_key     { k }
  , m_value   { new T(v) }
{}

template<typename T>
HashTable<T>::HashElement::HashElement (const HashElement& other)
  : m_key     { other.m_key }
  , m_value   { nullptr }
{
  if (other.m_value)
    m_value = new T(*other.m_value);
}

template<typename T>
HashTable<T>::HashElement::~HashElement ()
{
  if (m_value)
    delete m_value;
}

template<typename T>
const T& HashTable<T>::HashElement::value () const
{
  return *m_value;
}

template<typename T>
int HashTable<T>::HashElement::key () const
{
  return m_key;
}

template<typename T>
bool HashTable<T>::HashElement::operator== (const HashElement& other) const
{
  return this == &other;
}

template<typename T>
bool HashTable<T>::HashElement::operator!= (const HashElement& other) const
{
  return this != &other;
}