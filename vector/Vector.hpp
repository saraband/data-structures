#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstring>
#include <stdexcept>

// @TODO swap, binary_search

const int VECTOR_DEFAULT_CAPACITY = 100;

template<typename T>
class Vector
{
  public:
    Vector ()
      : m_capacity  (VECTOR_DEFAULT_CAPACITY)
      , m_size      (0)
      , m_array     (nullptr)
    {
      m_array = new T[m_capacity];
    }

    ~Vector ()
    {
      delete[] m_array;
    }

    void push_back (T item)
    {
      if (m_size + 1 > m_capacity) {
        reserve(m_size + 1);
      }

      m_array[m_size] = item;
      m_size++;
    }

    void push_front (T item)
    {
      if (m_size + 1 > m_capacity) {
        reserve(m_size + 1);
      }

      // Shift whole array
      std::memmove(m_array + 1, m_array, sizeof(T) * m_size);

      m_array[0] = item;
      m_size++;
    }

    void pop_front ()
    {
      if (!m_size)
        return;

      // Shift whole array
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
      if (capacity <= m_capacity)
        return;

      m_capacity = capacity;
      T* newArray = new T[m_capacity];

      std::memcpy(newArray, m_array, sizeof(T) * m_size);

      delete m_array;
      m_array = newArray;
    }

    T& operator[] (int index)
    {
      if (index < 0 || index + 1 > m_size)
        throw std::runtime_error( "Vector: Out of bounds" );

      return m_array[index];
    }

    int size () const
    {
      return m_size;
    }

    template <typename U>
    friend std::ostream& operator<< (std::ostream&, const Vector<U>&);

  private:
    int m_capacity;
    int m_size;
    T*  m_array;
};

template <typename T>
std::ostream& operator<< (std::ostream& os, const Vector<T>& vector)
{
  for (int i = 0; i < vector.m_size; i++) {
    os << vector.m_array[i];

    if (i < vector.m_size - 1)
      os << " ";
  }

  return os;
}

#endif