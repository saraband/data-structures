#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <queue>
#include <functional>

#include "../Test.hpp"
#include "../Utils.hpp"

template<typename ValueType>
class RedBlackTree
{
  TESTABLE

  public:
    struct Node {
      enum Color {
        RED,
        BLACK
      };

      Node (int k, const ValueType& v, Color c)
        : key     (k)
        , value   (v)
        , color   (c)
        , left    (nullptr)
        , right   (nullptr)
        , parent  (nullptr)
      {}

      int         key;
      ValueType   value;
      Color       color;
      Node*       left;
      Node*       right;
      Node*       parent;
    };

    RedBlackTree ();
    ~RedBlackTree ();
    Node* find (int key);
    template<typename FunctionType>
    void recursiveDFT (const FunctionType& function, bool reversed = false) const;
    template<typename FunctionType>
    void iterativeBFT (const FunctionType& function) const;
    void insert (int key, const ValueType& value);

  private:
    void restoreSubtreeBalance (Node* node);
    void deleteNode (Node* node);

    Node* m_root;
};

#include "RedBlackTree.tpp"

#endif