#include "Vector.hpp"

int main ()
{
  TEST("Initialize empty vector", {
    Vector<int> vector;

    ASSERT_EQ(vector.m_size, 0);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
  });

  TEST("push_back", {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(40);

    ASSERT_EQ(vector.m_size, 3);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
    ASSERT_EQ(vector.state(), "10 20 40");
  });

  TEST("push_front", {
    Vector<int> vector;
    vector.push_front(10);
    vector.push_front(20);
    vector.push_front(40);

    ASSERT_EQ(vector.m_size, 3);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
    ASSERT_EQ(vector.state(), "40 20 10");
  });

  TEST("pop_back", {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.pop_back();

    ASSERT_EQ(vector.m_size, 1);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
    ASSERT_EQ(vector.state(), "10");
  });

  TEST("pop_back vector is empty", {
    Vector<int> vector;
    vector.pop_back();

    ASSERT_EQ(vector.m_size, 0);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
    ASSERT_EQ(vector.state(), "");
  });

  TEST("pop_front", {
    Vector<int> vector;
    vector.push_front(10);
    vector.push_front(20);
    vector.pop_front();

    ASSERT_EQ(vector.m_size, 1);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
    ASSERT_EQ(vector.state(), "10");
  });

  TEST("pop_front when vector is empty", {
    Vector<int> vector;
    vector.pop_front();

    ASSERT_EQ(vector.m_size, 0);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
    ASSERT_EQ(vector.state(), "");
  });

  TEST("reserve", {
    Vector<int> vector;
    vector.reserve(200);

    ASSERT_EQ(vector.m_size, 0);
    ASSERT_EQ(vector.m_capacity, 200);
    ASSERT_EQ(vector.state(), "");
  });
  
  TEST("reserve to a smaller capacity", {
    Vector<int> vector;
    vector.reserve(10);

    ASSERT_EQ(vector.m_size, 0);
    ASSERT_EQ(vector.m_capacity, DEFAULT_VECTOR_CAPACITY);
    ASSERT_EQ(vector.state(), "");
  });

  TEST("operator[]", {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(40);

    ASSERT_EQ(vector[0], 10);
    ASSERT_EQ(vector[2], 40);
  });

  TEST("operator[]", {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(40);

    ASSERT_EQ(vector[0], 10);
    ASSERT_EQ(vector[2], 40);
  });
  
  return 0;
}