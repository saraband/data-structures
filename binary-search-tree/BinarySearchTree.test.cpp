#include <iostream>
#include <string>

#include "BinarySearchTree.hpp"

int main ()
{
  using namespace std;

  BinarySearchTree<RED_BLACK, int> bst;
  bst.insert(50, 50);
  bst.insert(60, 60);
  bst.insert(70, 70);
  bst.insert(80, 80);
  cout << bst << endl;
  
  return 0;
}