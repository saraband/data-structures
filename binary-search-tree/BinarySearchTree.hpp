#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <queue>

#include "../Test.hpp"
#include "../Utils.hpp"

// @TODO unbalanced, avl
namespace BSTType
{
enum BSTType {
  UNBALANCED,
  RED_BLACK,
  AVL
};
}

// @TODO remove
// @TODO split all files into .tpp files

template<BSTType::BSTType type, typename T>
class BinarySearchTree
{
  TESTABLE

  public:
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

    BinarySearchTree ()
      : m_root (nullptr)
    {}

    ~BinarySearchTree ()
    {
      deleteNode(m_root);
    }

    Node* find (int key)
    {
      Node* node = m_root;

      while (node) {
        if (node->key == key)
          return node;
        else if (key < node->key)
          node = node->left;
        else
          node = node->right;
      }

      return node;
    }

    template<typename U>
    void recursiveDFT (const U& function, bool reversed = false) const
    {
      auto exploreNode = [reversed, &function](Node* node) {
        if (!node)
          return;

        if (reversed) {
          if (node && node->right) function(node->right);
          if (node) function(node);
          if (node && node->left) function(node->left);
        } else {
          if (node && node->left) function(node->left);
          if (node) function(node);
          if (node && node->right) function(node->right);
        }
      };

      exploreNode(m_root);
    }

    template<typename U>
    void iterativeBFT (const U& function) const
    {
      if (!m_root)
        return;

      std::queue<Node*> nodes;
      nodes.push(m_root);

      while (nodes.size()) {
        Node* node = nodes.front();

        if (node->left) nodes.push(node->left);
        if (node->right) nodes.push(node->right);

        function(node);
        
        nodes.pop();
      }
    }

    void insert (int key, T value)
    {
      if (!m_root) {
        m_root = new Node(key, value, Node::BLACK);
        return;
      }

      Node* parent = m_root;
      Node* node = new Node(key, value, Node::RED);

      // Insert in the tree
      while (parent->key != key) {
        // Key is smaller than node, find in left subtree
        if (key < parent->key) {
          if (parent->left) {
            parent = parent->left;
          } else {
            parent->left = node;
            node->parent = parent;
            break;
          }

        // Key is greater than node, find in left subtree
        } else {
          if (parent->right) {
            parent = parent->right;
          } else {
            parent->right = node;
            node->parent = parent;
            break;
          }
        }
      }

      restoreSubtreeBalance(node);
    }

  private:
    void restoreSubtreeBalance (Node* node)
    {
      if (node->color == Node::BLACK)
        return;

      // Root of the tree is red, recolor it black
      if (!node->parent) {
        node->color = Node::RED;
        return;
      }

      // Parent is black, no problem
      if (node->parent->color == Node::BLACK)
        return;

      // Double red case
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

      // Red uncle case, recolor subtree
      if (uncleColor == Node::RED) {
        uncle->color = Node::BLACK;
        parent->color = Node::BLACK;
        grandparent->color = Node::RED;

        restoreSubtreeBalance(grandparent);

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
          // Connect parent of the subtree with parent (which will be grandparent after rotation)
          if (grandparent->parent) {
            if (grandparent->parent->left->key == grandparent->key)
              grandparent->parent->left = parent;
            else
              grandparent->parent->right = parent;
          // Subtree is at the root or the tree, update the root pointer
          } else {
            m_root = parent;
          }

          // Rotate left
          if (isLeftNode) {
            Node* oldParentRight = parent->right;
            parent->parent = grandparent->parent;
            parent->right = grandparent;
            grandparent->parent = parent;
            grandparent->left = oldParentRight;

            if (oldParentRight)
              oldParentRight->parent = grandparent;
          // Rotate right
          } else {
            Node* oldParentLeft = parent->left;
            parent->parent = grandparent->parent;
            parent->left = grandparent;
            grandparent->parent = parent;
            grandparent->right = oldParentLeft;

            if (oldParentLeft)
              oldParentLeft->parent = grandparent;
          }

          // Recolor original parent and grandparent
          parent->color = Node::BLACK;
          grandparent->color = Node::RED;
        }

        restoreSubtreeBalance(parent);
      }
    }

    std::string state () const
    {
      std::string state;

      iterativeBFT([&state](Node* node) {
        char suffix = node->color == Node::BLACK ? 'b' : 'r';
        state += toString(node->key) + suffix + ' ';
      });

      return state;
    }

    void deleteNode (Node* node)
    {
      if (!node)
        return;

      deleteNode(node->right);
      deleteNode(node->left);

      delete node;
    }

    Node* m_root;
};

#endif