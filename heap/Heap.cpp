#include "Heap.hpp"

int main ()
{
  test::registerTest("Initialize an empty heap", []() {
    Heap<HeapType::MAX, int> heap;

    test::expect(heap.m_size == 0);
  });

  test::registerTest("MaxHeap: insert", []() {
    Heap<HeapType::MAX, int> heap;
    heap.insert(10, 10);
    heap.insert(20, 20);
    heap.insert(5, 5);
    heap.insert(40, 40);

    test::expect(heap.m_size == 4);
    test::expect(heap.peek() == 40);
    test::expect(heap.m_nodes[0].value == 40);
    test::expect(heap.m_nodes[1].value == 20);
    test::expect(heap.m_nodes[2].value == 5);
    test::expect(heap.m_nodes[3].value == 10);
  });

  test::registerTest("MinHeap: insert", []() {
    Heap<HeapType::MIN, int> heap;
    heap.insert(10, 10);
    heap.insert(20, 20);
    heap.insert(5, 5);
    heap.insert(40, 40);

    test::expect(heap.m_size == 4);
    test::expect(heap.peek() == 5);
    test::expect(heap.m_nodes[0].value == 5);
    test::expect(heap.m_nodes[1].value == 20);
    test::expect(heap.m_nodes[2].value == 10);
    test::expect(heap.m_nodes[3].value == 40);
  });

  test::registerTest("MaxHeap: pop", []() {
    Heap<HeapType::MAX, int> heap;
    heap.insert(-100, -100);
    heap.insert(42, 42);
    heap.insert(5, 5);
    heap.insert(-50, -50);
    heap.pop();

    test::expect(heap.m_size == 3);
    test::expect(heap.peek() == 5);
    test::expect(heap.m_nodes[0].value == 5);
    test::expect(heap.m_nodes[1].value == -50);
    test::expect(heap.m_nodes[2].value == -100);
  });

  test::registerTest("MaxHeap: pop when empty", []() {
    Heap<HeapType::MAX, int> heap;
    heap.pop();

    test::expect(heap.m_size == 0);
  });

  test::registerTest("MinHeap: pop", []() {
    Heap<HeapType::MIN, int> heap;
    heap.insert(-100, -100);
    heap.insert(42, 42);
    heap.insert(5, 5);
    heap.insert(-50, -50);
    heap.pop();

    test::expect(heap.m_size == 3);
    test::expect(heap.peek() == -50);
    test::expect(heap.m_nodes[0].value == -50);
    test::expect(heap.m_nodes[1].value == 42);
    test::expect(heap.m_nodes[2].value == 5);
  });

  test::registerTest("MinHeap: pop when empty", []() {
    Heap<HeapType::MIN, int> heap;
    heap.pop();

    test::expect(heap.m_size == 0);
  });

  return 0;
}