#include "Vector.hpp"

int main ()
{
  test::registerTest("Initialize empty vector", []() {
    Vector<int> vector;

    test::expect(vector.m_size == 0);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
  });

  test::registerTest("push_back", []() {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(40);

    test::expect(vector.m_size == 3);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
    test::expect(vector.m_array[0] == 10);
    test::expect(vector.m_array[1] == 20);
    test::expect(vector.m_array[2] == 40);
  });

  test::registerTest("push_front", []() {
    Vector<int> vector;
    vector.push_front(10);
    vector.push_front(20);
    vector.push_front(40);

    test::expect(vector.m_size == 3);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
    test::expect(vector.m_array[0] == 40);
    test::expect(vector.m_array[1] == 20);
    test::expect(vector.m_array[2] == 10);
  });

  test::registerTest("pop_back", []() {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.pop_back();

    test::expect(vector.m_size == 1);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
    test::expect(vector.m_array[0] == 10);
  });

  test::registerTest("pop_back vector is empty", []() {
    Vector<int> vector;
    vector.pop_back();

    test::expect(vector.m_size == 0);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
  });

  test::registerTest("pop_front", []() {
    Vector<int> vector;
    vector.push_front(10);
    vector.push_front(20);
    vector.pop_front();

    test::expect(vector.m_size == 1);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
    test::expect(vector.m_array[0] == 10);
  });

  test::registerTest("pop_front when vector is empty", []() {
    Vector<int> vector;
    vector.pop_front();

    test::expect(vector.m_size == 0);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
  });

  test::registerTest("reserve", []() {
    Vector<int> vector;
    vector.reserve(200);

    test::expect(vector.m_size == 0);
    test::expect(vector.m_capacity == 200);
  });
  
  test::registerTest("reserve to a smaller capacity", []() {
    Vector<int> vector;
    vector.reserve(10);

    test::expect(vector.m_size == 0);
    test::expect(vector.m_capacity == DEFAULT_VECTOR_CAPACITY);
  });

  test::registerTest("operator[]", []() {
    Vector<int> vector;
    vector.push_back(10);
    vector.push_back(20);
    vector.push_back(40);

    test::expect(vector[0] == 10);
    test::expect(vector[2] == 40);
  });
  
  return 0;
}