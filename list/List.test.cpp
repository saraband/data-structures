#include <iostream>
#include "List.hpp"

int main ()
{
  using namespace std;

  List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(40);
  cout << list << endl;

  list.pop_back();
  cout << list << endl;

  list.push_front(8);
  list.push_front(4);
  cout << list << endl;

  list.pop_front();
  list.pop_front();
  list.pop_front();
  cout << list << endl;

  list.push_back(40);
  list.push_back(80);
  list.push_back(160);
  cout << list << endl;

  auto node = list.find(80);
  cout << node->previous->value << endl;

  list.insertBefore(node, 70);
  list.insertAfter(node, 90);
  cout << list << endl;

  return 0;
}