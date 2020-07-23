#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <queue>

enum BSTType {
  RED_BLACK,
  AVL
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
      if (!m_root) {
        m_root = new Node(key, value, Node::BLACK);
        return;
      }

      Node* parent = m_root;
      Node* node = new Node(key, value, Node::RED);

      // Insert in the tree
      for (;;) {
        // Key already exists
        if (parent->key == key)
          return;

        if (key < parent->key) {
          if (parent->left) {
            parent = parent->left;
          } else {
            parent->left = node;
            node->parent = parent;
          }
        } else if (key > parent->key) {
          if (parent->right) {
            parent = parent->right;
          } else {
            parent->right = node;
            node->parent = parent;
          }
        }
      }

      restoreTreeBalance(node);
    }

    // @TODO find, dft, remove

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
        , color   (c)
        , left    (nullptr)
        , right   (nullptr)
        , parent  (nullptr)
      {}

      int     key;
      T       value;
      Color   color;
      Node*   left;
      Node*   right;
      Node*   parent;
    };

    void restoreTreeBalance (Node* node)
    {
      if (node->color == Node::BLACK)
        return;

      // Root of the tree is red, recolor it black
      if (!node->parent) {
        node->color = Node::RED;
        return;
      }
      
      // Double red case
      if (node->parent->color == Node::RED) {
        Node* parent = node->parent;
        bool isRightNode = parent->right && parent->right->key == node->key;
        bool isLeftNode = !isRightNode;
        Node* grandparent = parent->parent;
        bool isParentRightNode = grandparent->right && grandparent->right->key == parent->key;
        bool isParentLeftNode = !isParentRightNode;
        Node* uncle = isParentRightNode
          ? grandparent->left
          : grandparent->right;
        int uncleColor = uncle // @TODO why cant i use Node::Color
          ? uncle->color
          : Node::BLACK;

        // Red uncle case, simple recoloring
        if (uncleColor == Node::RED) {
          uncle->color = Node::BLACK;
          parent->color = Node::BLACK;
          grandparent->color = Node::RED;

          restoreTreeBalance(grandparent);
        // Black uncle
        } else {
          // Red triangle case
          if (isLeftNode && isParentRightNode) {
            grandparent->right = node;
            node->parent = grandparent;
            node->right = parent;
            parent->parent = node;
            parent->left = nullptr;
          } else if (isRightNode && isParentLeftNode) {
            grandparent->left = node;
            node->parent = grandparent;
            node->left = parent;
            parent->parent = node;
            parent->right = nullptr;
          // Red line case
          } else {
            // New grandparent is the root
            if (!grandparent->parent) {
              m_root = parent;
            // Connect great-grandparent with new grandparent
            } else {
              if (grandparent->parent->left->key == grandparent->key)
                grandparent->parent->left = parent;
              else
                grandparent->parent->right = parent;
            }

            // Rotate left
            if (isLeftNode) {
              parent->parent = grandparent->parent;
              parent->right = grandparent;
              grandparent->parent = parent;
              grandparent->left = parent->right;
              parent->right->parent = grandparent;
            // Rotate right
            } else {
              parent->parent = grandparent->parent;
              parent->left = grandparent;
              grandparent->parent = parent;
              grandparent->right = parent->left;
              parent->left->parent = grandparent;
            }
          }

          restoreTreeBalance(parent);
        }
      }
    }

    Node* m_root;
};

template <BSTType type, typename T>
std::ostream& operator<< (std::ostream& os, const BinarySearchTree<type, T>& tree)
{
  // @TODO

  return os;
}

#endif