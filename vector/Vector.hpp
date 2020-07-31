#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstring>

#include "../Test.hpp"
#include "../Utils.hpp"

constexpr int DEFAULT_VECTOR_CAPACITY = 100;

template<typename ValueType>
class Vector
{
  TESTABLE
  
  public:
    Vector ();
    ~Vector ();
    void push_back (const ValueType& item);
    void push_front (const ValueType& item);
    void pop_front ();
    void pop_back ();
    void reserve (int capacity);
    ValueType& operator[] (int index);
    int size () const;

  private:
    int           m_capacity;
    int           m_size;
    ValueType*    m_array;
};

#include "Vector.tpp"

#endif