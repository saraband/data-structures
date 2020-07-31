#include "Heap.hpp"

template<HeapType::HeapType type, typename ValueType>
Heap<type, ValueType>::Heap ()
  : m_size  { 0 }
{}

template<HeapType::HeapType type, typename ValueType>
void Heap<type, ValueType>::insert (int key, const ValueType& value)
{
  m_size++;
  int index = m_size - 1;

  // Push new node down
  m_nodes.push_back(Node(key * type, value));

  // Restore heap property upwards starting from newly inserted element
  pushUp(index);
}

template<HeapType::HeapType type, typename ValueType>
const ValueType& Heap<type, ValueType>::peek () const
{
  if (!m_size)
    throw std::runtime_error("Cannot peek: heap is empty");
  
  return m_nodes[0].value;
}

template<HeapType::HeapType type, typename ValueType>
void Heap<type, ValueType>::pop ()
{
  if (!m_size)
    return;

  // Swap last element with root and restore the heap property downwards starting from root
  m_nodes[0] = m_nodes[m_size - 1];
  m_size--;

  pushDown(0);
}

template<HeapType::HeapType type, typename ValueType>
void Heap<type, ValueType>::swap (int indexA, int indexB)
{
  Node temp = m_nodes[indexB];
  m_nodes[indexB] = m_nodes[indexA];
  m_nodes[indexA] = temp;
}

template<HeapType::HeapType type, typename ValueType>
void Heap<type, ValueType>::pushUp (int index)
{
  // Reached top
  if (index == 0)
    return;

  // Parent key is greater than current key, heap properties restored
  int parentIndex = ceil(index / 2.f) - 1;
  if (m_nodes[parentIndex].key >= m_nodes[index].key)
    return;

  swap(index, parentIndex);
  pushUp(parentIndex);
}

template<HeapType::HeapType type, typename ValueType>
void Heap<type, ValueType>::pushDown (int index)
{
  const int maxHeapIndex = m_size - 1;
  int largestChildIndex = -1;
  int leftChildIndex = index * 2 + 1;
  int rightChildIndex = index * 2 + 2;

  // Current node is a leaf, no need to do anything
  if (leftChildIndex > maxHeapIndex && rightChildIndex > maxHeapIndex)
    return;

  // Find child with larger key
  if (leftChildIndex <= maxHeapIndex)
    largestChildIndex = leftChildIndex;
  if (rightChildIndex <= maxHeapIndex && m_nodes[rightChildIndex].key > m_nodes[leftChildIndex].key)
    largestChildIndex = rightChildIndex;

  // Current node key is larger than both its children
  if (largestChildIndex == -1)
    return;

  // Swap with the largest child
  swap(index, largestChildIndex);
  pushDown(largestChildIndex);
}