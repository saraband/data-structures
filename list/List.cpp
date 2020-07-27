#include "List.hpp"

int main ()
{
  test::registerTest("Initialize empty list", []() {
    List<int> list;

    test::assertEq(list.m_size, 0);
    test::assertEq(list.state(), "");
    test::assertEq(list.m_head, nullptr);
    test::assertEq(list.m_tail, nullptr);
  });

  test::registerTest("push_back", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    test::assertEq(list.m_size, 2);
    test::assertEq(list.state(), "10 20");
    test::assertEq(list.head(), 10);
    test::assertEq(list.tail(), 20);
  });

  test::registerTest("push_front", []() {
    List<int> list;
    list.push_front(10);
    list.push_front(20);

    test::assertEq(list.m_size, 2);
    test::assertEq(list.state(), "20 10");
    test::assertEq(list.head(), 20);
    test::assertEq(list.tail(), 10);
  });

  test::registerTest("pop_back", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();

    test::assertEq(list.m_size, 1);
    test::assertEq(list.state(), "10");
    test::assertEq(list.head(), 10);
    test::assertEq(list.tail(), 10);
  });

  test::registerTest("pop_back when list is empty", []() {
    List<int> list;
    list.pop_back();

    test::assertEq(list.m_size, 0);
    test::assertEq(list.state(), "");
    test::assertEq(list.m_head, nullptr);
    test::assertEq(list.m_tail, nullptr);
  });

  test::registerTest("pop_front", []() {
    List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.pop_front();

    test::assertEq(list.m_size, 1);
    test::assertEq(list.state(), "10");
    test::assertEq(list.head(), 10);
    test::assertEq(list.tail(), 10);
  });

  test::registerTest("pop_front when list is empty", []() {
    List<int> list;
    list.pop_front();

    test::assertEq(list.m_size, 0);
    test::assertEq(list.state(), "");
    test::assertEq(list.m_head, nullptr);
    test::assertEq(list.m_tail, nullptr);
  });

  test::registerTest("find", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(40);
    list.push_back(80);
    auto node = list.find(40);

    test::assertEq(node->value, 40);
    test::assertEq(node->previous->value, 20);
    test::assertEq(node->next->value, 80);
  });

  test::registerTest("find when the element does not exists", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    auto node = list.find(40);

    test::assertEq(node, nullptr);
  });

  test::registerTest("insertAfter", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    auto node = list.find(20);
    list.insertAfter(node, 40);

    test::assertEq(list.m_size, 3);
    test::assertEq(list.state(), "10 20 40");
  });

  test::registerTest("insertBefore", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    auto node = list.find(10);
    list.insertBefore(node, 5);

    test::assertEq(list.m_size, 3);
    test::assertEq(list.state(), "5 10 20");
  });

  test::registerTest("swap", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(40);
    list.push_back(80);
    auto nodeA = list.find(10);
    auto nodeB = list.find(40);
    list.swap(nodeA, nodeB);

    test::assertEq(list.state(), "40 20 10 80");
  });

  test::registerTest("swap adjacent nodes", []() {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(40);
    auto nodeA = list.find(10);
    auto nodeB = list.find(20);
    list.swap(nodeA, nodeB);

    test::assertEq(list.state(), "20 10 40");
  });

  return 0;
}