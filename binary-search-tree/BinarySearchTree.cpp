#include <iostream>
#include <string>

#include "BinarySearchTree.hpp"

// @TODO  b+tree, b-tree

int main ()
{
  BinarySearchTree<BSTType::RED_BLACK, int> tree;
  tree.insert(52, 52);
  tree.insert(10, 10);
  tree.insert(15, 15);
  tree.insert(27, 27);

  std::cout << tree.state() << std::endl;
  
  return 0;
}