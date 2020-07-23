#include <iostream>
#include <string>

#include "Heap.hpp"

int main ()
{
  using namespace std;

  Heap<MAX, int> heap;
  heap.insert(10, 10);
  heap.insert(5, 5);
  heap.insert(33, 33);
  heap.insert(206, 206);
  cout << heap << endl;

  cout << heap.peek() << endl;
  heap.pop();
  cout << heap.peek() << endl;
  
  return 0;
}