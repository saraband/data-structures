#ifndef HEAP_HPP
#define HEAP_HPP

#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

enum HeapType {
  MAX = 1,
  MIN = -1
};

template<HeapType type, typename T>
class Heap
{
  public:
    Heap ()
      : m_size    (0)
    {}

    void insert (int key, T value)
    {
      int index = m_size;

      // Push new node down
      m_nodes.push_back(Node(key * type, value));

      // Restore heap property upwards
      pushUp(index);

      m_size++;
    }

    int parentIndex (int index) const
    {
      return floor(index / 2);
    }

    void swap (int indexA, int indexB)
    {
      Node temp = m_nodes[indexB];
      m_nodes[indexB] = m_nodes[indexA];
      m_nodes[indexA] = temp;
    }

    const T& peek () const
    {
      if (!m_size)
        throw std::runtime_error( "Heap: Cannot peek if heap is empty" );
      
      return m_nodes[0].value;
    }

    void pop ()
    {
      if (!m_size)
        return;

      m_nodes[0] = m_nodes[m_size - 1];
      pushDown(0);

      m_size--;
    }

    template <HeapType U, typename V>
    friend std::ostream& operator<< (std::ostream&, const Heap<U, V>&);

  private:
    void pushUp (int index)
    {

      // Reached top
      if (index == 0)
        return;

      // Parent is greater than current
      if (m_nodes[parentIndex(index)].key >= m_nodes[index].key)
        return;

      swap(index, parentIndex(index));
      pushUp(parentIndex(index));
    }

    void pushDown (int index)
    {
      int value = m_nodes[index].value;
      int maxIndex = m_size - 1;
      int greatestChildIndex = -1;
      int leftChildIndex = index * 2 + 1;
      int rightChildIndex = index * 2 + 2;

      // Current node has no children => leaf
      if (leftChildIndex > maxIndex && rightChildIndex > maxIndex)
        return;

      if (leftChildIndex <= maxIndex)
        greatestChildIndex = leftChildIndex;
      if (rightChildIndex <= maxIndex && m_nodes[rightChildIndex].value > m_nodes[leftChildIndex].value)
        greatestChildIndex = rightChildIndex;

      // Current node is greater than both its children
      if (greatestChildIndex == -1)
        return;

      // Swap with the greatest child
      swap(index, greatestChildIndex);
      pushDown(greatestChildIndex);
    }

    struct Node {
      Node (int k, T v)
        : key     (k)
        , value   (v)
      {}

      int   key;
      T     value;
    };

    int                  m_size;
    std::vector<Node>    m_nodes;
};

template <HeapType type, typename T>
std::ostream& operator<< (std::ostream& os, const Heap<type, T>& heap)
{
  for (int i = 0; i < heap.m_size; i++) {
    os << heap.m_nodes[i].value << " ";
  }

  return os;
}

#endif