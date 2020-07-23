#ifndef HEAP_HPP
#define HEAP_HPP

#include <cmath>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

//@ TODO REMOVE
const int DEFAULT_HEAP_MAX_SIZE(100);
enum HeapType {
  MAX = 1,
  MIN = -1
};

template<HeapType type, typename T>
class Heap
{
  public:
    Heap (int maxSize = DEFAULT_HEAP_MAX_SIZE)
      : m_size    (0)
      , m_maxSize (maxSize)
    {
      m_nodes.reserve(m_maxSize);
    }

    // @TODO add remove() method

    void insert (int key, T value)
    {
      int index = m_size;

      // Push new node down
      m_nodes[index] = Node(key * type, value);

      // Rebalance with parents
      //@TODO refacto in pushUp
      while (index != 0 && m_nodes[index].key > m_nodes[parentIndex(index)].key) {
        swap(index, parentIndex(index));
        index = parentIndex(index);
      }

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
      // @TODO
    }

    template <HeapType U, typename V>
    friend std::ostream& operator<< (std::ostream&, const Heap<U, V>&);

  private:
    struct Node {
      Node (int k, T v)
        : key     (k)
        , value   (v)
      {}

      int   key;
      T     value;
    };

    int                  m_size;
    int                  m_maxSize;
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