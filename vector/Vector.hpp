#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstring>

#include "../Test.hpp"
#include "../Utils.hpp"

constexpr int DEFAULT_VECTOR_CAPACITY = 100;

template<typename T>
class Vector
{
  TESTABLE
  
  public:
    Vector ()
      : m_capacity  { 0 }
      , m_size      { 0 }
      , m_array     { nullptr }
    {
      reserve(DEFAULT_VECTOR_CAPACITY);
    }

    ~Vector ()
    {
      delete[] m_array;
    }

    void push_back (T item)
    {
      m_size++;
      reserve(m_size);
      m_array[m_size - 1] = item;
    }

    void push_front (T item)
    {
      m_size++;
      reserve(m_size);

      // Shift whole array to the right
      std::memmove(m_array + 1, m_array, sizeof(T) * m_size);

      m_array[0] = item;
    }

    void pop_front ()
    {
      if (!m_size)
        return;

      // Shift whole array to the left
      std::memmove(m_array, m_array + 1, sizeof(T) * m_size);

      m_size--;
    }

    void pop_back ()
    {
      if (!m_size)
        return;

      m_size--;
    }

    void reserve (int capacity)
    {
      // @TODO
      if (capacity <= m_capacity)
        return;

      m_capacity = capacity;
      T* newArray = new T[m_capacity];

      std::memcpy(newArray, m_array, sizeof(T) * m_size);

      delete[] m_array;
      m_array = newArray;
    }

    T& operator[] (int index)
    {
      return m_array[index];
    }

    int size () const
    {
      return m_size;
    }

  private:
    int   m_capacity;
    int   m_size;
    T*    m_array;
};

#endif