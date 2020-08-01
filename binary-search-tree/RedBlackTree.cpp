#include "RedBlackTree.hpp"

int main ()
{
  test::registerTest("Initialize empty red black tree", []() {
    RedBlackTree<int> tree;

    test::expect(tree.m_root == nullptr);
  });

  test::registerTest("insert", []() {
    RedBlackTree<int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);

    test::expect(tree.m_root->value == 2);
    test::expect(tree.m_root->color == RedBlackTree<int>::Node::BLACK);
    test::expect(tree.m_root->left->value == 1);
    test::expect(tree.m_root->left->color == RedBlackTree<int>::Node::BLACK);
    test::expect(tree.m_root->right->value == 3);
    test::expect(tree.m_root->right->color == RedBlackTree<int>::Node::BLACK);
    test::expect(tree.m_root->right->right->value == 4);
    test::expect(tree.m_root->right->right->color == RedBlackTree<int>::Node::RED);
  });

  test::registerTest("find", []() {
    RedBlackTree<int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);

    test::expect(tree.find(3)->value == 3);
    test::expect(tree.find(17) == nullptr);
  });

  test::registerTest("Breadth first traversal", []() {
    RedBlackTree<int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);

    std::string keys;
    std::string expectedKeys = "2 1 3 4 ";

    tree.iterativeBFT([&keys](RedBlackTree<int>::Node* node) {
      keys += toString(node->value) + " ";
    });

    test::expect(keys == expectedKeys);
  });

  test::registerTest("Depth first traversal", []() {
    RedBlackTree<int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);
    tree.insert(3, 3);
    tree.insert(4, 4);

    std::string keys;
    std::string expectedKeys = "1 2 3 4 ";

    tree.recursiveDFT([&keys](RedBlackTree<int>::Node* node) {
      keys += toString(node->value) + " ";
    });

    test::expect(keys == expectedKeys);
  });

  return 0;
}