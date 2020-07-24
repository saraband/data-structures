#include "List.hpp"

int main ()
{
  TEST("Initialize empty list", {
    List<int> list;

    ASSERT_EQ(list.m_size, 0);
    ASSERT_EQ(list.state(), "");
    ASSERT_EQ(list.m_head, nullptr);
    ASSERT_EQ(list.m_tail, nullptr);
  })

  TEST("push_back", {
    List<int> list;
    list.push_back(10);
    list.push_back(20);

    ASSERT_EQ(list.m_size, 2);
    ASSERT_EQ(list.state(), "10 20");
    ASSERT_EQ(list.head(), 10);
    ASSERT_EQ(list.tail(), 20);
  })

  TEST("push_front", {
    List<int> list;
    list.push_front(10);
    list.push_front(20);

    ASSERT_EQ(list.m_size, 2);
    ASSERT_EQ(list.state(), "20 10");
    ASSERT_EQ(list.head(), 20);
    ASSERT_EQ(list.tail(), 10);
  });

  TEST("pop_back", {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();

    ASSERT_EQ(list.m_size, 1);
    ASSERT_EQ(list.state(), "10");
    ASSERT_EQ(list.head(), 10);
    ASSERT_EQ(list.tail(), 10);
  });

  TEST("pop_back when list is empty", {
    List<int> list;
    list.pop_back();

    ASSERT_EQ(list.m_size, 0);
    ASSERT_EQ(list.state(), "");
    ASSERT_EQ(list.m_head, nullptr);
    ASSERT_EQ(list.m_tail, nullptr);
  });

  TEST("pop_front", {
    List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.pop_front();

    ASSERT_EQ(list.m_size, 1);
    ASSERT_EQ(list.state(), "10");
    ASSERT_EQ(list.head(), 10);
    ASSERT_EQ(list.tail(), 10);
  });

  TEST("pop_front when list is empty", {
    List<int> list;
    list.pop_front();

    ASSERT_EQ(list.m_size, 0);
    ASSERT_EQ(list.state(), "");
    ASSERT_EQ(list.m_head, nullptr);
    ASSERT_EQ(list.m_tail, nullptr);
  });

  TEST("find", {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(40);
    list.push_back(80);
    auto node = list.find(40);

    ASSERT_EQ(node->value, 40);
    ASSERT_EQ(node->previous->value, 20);
    ASSERT_EQ(node->next->value, 80);
  });

  TEST("find when the element does not exists", {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    auto node = list.find(40);

    ASSERT_EQ(node, nullptr);
  });

  TEST("insertAfter", {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    auto node = list.find(20);
    list.insertAfter(node, 40);

    ASSERT_EQ(list.m_size, 3);
    ASSERT_EQ(list.state(), "10 20 40");
  });

  TEST("insertBefore", {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    auto node = list.find(10);
    list.insertBefore(node, 5);

    ASSERT_EQ(list.m_size, 3);
    ASSERT_EQ(list.state(), "5 10 20");
  });

  return 0;
}