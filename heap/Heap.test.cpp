#include "Heap.hpp"

int main ()
{
  typedef Heap<HeapType::MAX, int> MaxHeap;
  typedef Heap<HeapType::MIN, int> MinHeap;

  TEST("Initialize an empty heap", {
    MaxHeap heap;

    ASSERT_EQ(heap.m_size, 0);
    ASSERT_EQ(heap.state(), "");
  });

  TEST("MaxHeap: insert", {
    MaxHeap heap;
    heap.insert(10, 10);
    heap.insert(20, 20);
    heap.insert(5, 5);
    heap.insert(40, 40);

    ASSERT_EQ(heap.m_size, 4);
    ASSERT_EQ(heap.state(), "40 20 5 10");
    ASSERT_EQ(heap.peek(), 40);
  });

  TEST("MinHeap: insert", {
    MinHeap heap;
    heap.insert(10, 10);
    heap.insert(20, 20);
    heap.insert(5, 5);
    heap.insert(40, 40);

    ASSERT_EQ(heap.m_size, 4);
    ASSERT_EQ(heap.state(), "5 20 10 40");
    ASSERT_EQ(heap.peek(), 5);
  });

  TEST("MaxHeap: pop", {
    MaxHeap heap;
    heap.insert(-100, -100);
    heap.insert(42, 42);
    heap.insert(5, 5);
    heap.insert(-50, -50);
    heap.pop();

    ASSERT_EQ(heap.m_size, 3);
    ASSERT_EQ(heap.state(), "5 -50 -100");
    ASSERT_EQ(heap.peek(), 5);
  });

  TEST("MaxHeap: pop when empty", {
    MaxHeap heap;
    heap.pop();

    ASSERT_EQ(heap.m_size, 0);
    ASSERT_EQ(heap.state(), "");
  });

  TEST("MinHeap: pop", {
    MinHeap heap;
    heap.insert(-100, -100);
    heap.insert(42, 42);
    heap.insert(5, 5);
    heap.insert(-50, -50);
    heap.pop();

    ASSERT_EQ(heap.m_size, 3);
    ASSERT_EQ(heap.peek(), -50);
    ASSERT_EQ(heap.state(), "-50 42 5");
  });

  TEST("MinHeap: pop when empty", {
    MinHeap heap;
    heap.pop();

    ASSERT_EQ(heap.m_size, 0);
    ASSERT_EQ(heap.state(), "");
  });

  return 0;
}