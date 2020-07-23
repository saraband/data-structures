#ifndef BST_HPP
#define BST_HPP

#include <iostream>

enum BSTType {
  RED_BLACK
};

template<BSTType type, typename T>
class BinarySearchTree
{
  public:
    BinarySearchTree ()
    {}

    template <BSTType U, typename V>
    friend std::ostream& operator<< (std::ostream&, const BinarySearchTree<U, V>&);

  private:
    struct Node {
      Node (int k, T v)
        : key     (k)
        , value   (v)
      {}

      int   key;
      T     value;
    };
};

template <BSTType type, typename T>
std::ostream& operator<< (std::ostream& os, const BinarySearchTree<type, T>& bst)
{
  // @TODO

  return os;
}

#endif