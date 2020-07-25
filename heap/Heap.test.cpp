#include "Heap.hpp"

int main ()
{
  test::registerTest("Initialize an empty heap", [](){
    Heap<HeapType::MAX, int> heap;

    test::assertEq(heap.m_size, 0);
    test::assertEq(heap.state(), "");
  });

  test::registerTest("MaxHeap: insert", [](){
    Heap<HeapType::MAX, int> heap;
    heap.insert(10, 10);
    heap.insert(20, 20);
    heap.insert(5, 5);
    heap.insert(40, 40);

    test::assertEq(heap.m_size, 4);
    test::assertEq(heap.state(), "40 20 5 10");
    test::assertEq(heap.peek(), 40);
  });

  test::registerTest("MinHeap: insert", [](){
    Heap<HeapType::MIN, int> heap;
    heap.insert(10, 10);
    heap.insert(20, 20);
    heap.insert(5, 5);
    heap.insert(40, 40);

    test::assertEq(heap.m_size, 4);
    test::assertEq(heap.state(), "5 20 10 40");
    test::assertEq(heap.peek(), 5);
  });

  test::registerTest("MaxHeap: pop", [](){
    Heap<HeapType::MAX, int> heap;
    heap.insert(-100, -100);
    heap.insert(42, 42);
    heap.insert(5, 5);
    heap.insert(-50, -50);
    heap.pop();

    test::assertEq(heap.m_size, 3);
    test::assertEq(heap.state(), "5 -50 -100");
    test::assertEq(heap.peek(), 5);
  });

  test::registerTest("MaxHeap: pop when empty", [](){
    Heap<HeapType::MAX, int> heap;
    heap.pop();

    test::assertEq(heap.m_size, 0);
    test::assertEq(heap.state(), "");
  });

  test::registerTest("MinHeap: pop", [](){
    Heap<HeapType::MIN, int> heap;
    heap.insert(-100, -100);
    heap.insert(42, 42);
    heap.insert(5, 5);
    heap.insert(-50, -50);
    heap.pop();

    test::assertEq(heap.m_size, 3);
    test::assertEq(heap.peek(), -50);
    test::assertEq(heap.state(), "-50 42 5");
  });

  test::registerTest("MinHeap: pop when empty", [](){
    Heap<HeapType::MIN, int> heap;
    heap.pop();

    test::assertEq(heap.m_size, 0);
    test::assertEq(heap.state(), "");
  });

  return 0;
}