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
      : m_root (nullptr)
    {}

    void insert (int key, T value)
    {

    }

    // @TODO find, dfs, remove

    template <BSTType U, typename V>
    friend std::ostream& operator<< (std::ostream&, const BinarySearchTree<U, V>&);

  private:
    struct Node {
      enum Color {
        RED,
        BLACK
      };

      Node (int k, T v, Color c)
        : key     (k)
        , value   (v)
        , Color   (c)
      {}

      int     key;
      T       value;
      Color   color;
    };

    Node* m_root;
};

template <BSTType type, typename T>
std::ostream& operator<< (std::ostream& os, const BinarySearchTree<type, T>& bst)
{
  // @TODO

  return os;
}

#endif