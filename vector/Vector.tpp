#include "Vector.hpp"

template<typename ValueType>
Vector<ValueType>::Vector ()
  : m_capacity  { 0 }
  , m_size      { 0 }
  , m_array     { nullptr }
{
  reserve(DEFAULT_VECTOR_CAPACITY);
}

template<typename ValueType>
Vector<ValueType>::~Vector ()
{
  delete[] m_array;
}

template<typename ValueType>
void Vector<ValueType>::push_back (const ValueType& item)
{
  m_size++;
  reserve(m_size);
  m_array[m_size - 1] = item;
}

template<typename ValueType>
void Vector<ValueType>::push_front (const ValueType& item)
{
  m_size++;
  reserve(m_size);

  // Shift whole array to the right
  std::memmove(m_array + 1, m_array, sizeof(ValueType) * m_size);

  m_array[0] = item;
}

template<typename ValueType>
void Vector<ValueType>::pop_front ()
{
  if (!m_size)
    return;

  // Shift whole array to the left
  std::memmove(m_array, m_array + 1, sizeof(ValueType) * m_size);

  m_size--;
}

template<typename ValueType>
void Vector<ValueType>::pop_back ()
{
  if (!m_size)
    return;

  m_size--;
}

template<typename ValueType>
void Vector<ValueType>::reserve (int capacity)
{
  if (capacity <= m_capacity)
    return;

  m_capacity = capacity;

  // Allocate enough space for the new capacity
  ValueType* newArray = static_cast<ValueType*>(malloc(sizeof(ValueType) * m_capacity));

  // Copy data to newly created space
  std::memcpy(newArray, m_array, sizeof(ValueType) * m_size);

  // Delete old space
  delete[] m_array;
  m_array = newArray;
}

template<typename ValueType>
ValueType& Vector<ValueType>::operator[] (int index)
{
  return m_array[index];
}

template<typename ValueType>
int Vector<ValueType>::size () const
{
  return m_size;
}
