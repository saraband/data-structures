#ifndef HEAP_HPP
#define HEAP_HPP

#include <cmath>
#include <stdexcept>
#include <vector>

#include "../Test.hpp"
#include "../Utils.hpp"

namespace HeapType {
enum HeapType {
  MAX = 1,
  MIN = -1
};
}

template<HeapType::HeapType type, typename ValueType>
class Heap
{
  TESTABLE
  
  public:
    struct Node {
      Node (int k, const ValueType& v)
        : key     { k }
        , value   { v }
      {}

      int         key;
      ValueType   value;
    };

    Heap ();
    void insert (int key, const ValueType& value);
    const ValueType& peek () const;
    void pop ();

  private:
    void swap (int indexA, int indexB);
    void pushUp (int index);
    void pushDown (int index);

    int                  m_size;
    std::vector<Node>    m_nodes;
};

#include "Heap.tpp"

#endif