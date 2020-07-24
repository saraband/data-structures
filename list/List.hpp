#ifndef LIST_HPP
#define LIST_HPP

#include "../Test.hpp"

template<typename T>
class List
{
  TESTABLE

  public:
    List ()
      : m_head  (nullptr)
      , m_tail  (nullptr)
      , m_size  (0)
    {}

    ~List ()
    {
      deleteNode(m_head);
    }

    struct Node
    {
      Node (T v)
        : value     (v)
        , next      (nullptr)
        , previous  (nullptr)
      {}

      Node*   next;
      Node*   previous;
      T       value;
    };

    void push_back (T item)
    {
      Node* node = new Node(item);

      if (!m_size) {
        m_head = node;
        m_tail = node;
      } else {
        m_tail->next = node;
        node->previous = m_tail;
        m_tail = node;
      }

      m_size++;
    }

    // @TODO head() tail()

    void push_front (T item)
    {
      Node* node = new Node(item);

      if (!m_size) {
        m_head = node;
        m_tail = node;
      } else {
        m_head->previous = node;
        node->next = m_head;
        m_head = node;
      }

      m_size++;
    }

    void pop_front ()
    {
      if (!m_size)
        return;
      
      Node* oldHead = m_head;

      if (m_head->next == nullptr) {
        m_head = nullptr;
        m_tail = nullptr;
      } else {
        m_head = m_head->next;
        m_head->previous = nullptr;
      }

      m_size--;
      delete oldHead;
    }

    void pop_back ()
    {
      if (!m_size)
        return;
      
      Node* oldTail = m_tail;

      if (m_tail->previous == nullptr) {
        m_head = nullptr;
        m_tail = nullptr;
      } else {
        m_tail = m_tail->previous;
        m_tail->next = nullptr;
      }

      m_size--;
      delete oldTail;
    }

    Node* find (T item)
    {
      Node* node = m_head;

      while (node) {
        if (node->value == item)
          return node;
        
        node = node->next;
      }

      return nullptr;
    }

    void insertAfter (Node* node, T item)
    {
      if (!node)
        return;

      Node* oldNextNode = node->next;
      node->next = new Node(item);
      node->next->previous = node;
      node->next->next = oldNextNode;

      if (node == m_tail)
        m_tail = node->next;
      else
        oldNextNode->previous = node->next;

      m_size++;
    }

    void insertBefore (Node* node, T item)
    {
      if (!node)
        return;

      Node* oldPreviousNode = node->previous;
      node->previous = new Node(item);
      node->previous->next = node;
      node->previous->previous = oldPreviousNode;

      if (node == m_head)
        m_head = node->previous;
      else
        oldPreviousNode->next = node->previous;

      m_size++;
    }

    int size () const
    {
      return m_size;
    }

  private:
    void deleteNode (Node* node)
    {
      if (node == nullptr)
        return;

      deleteNode(node->next);
      delete node;
    }

    Node*   m_head;
    Node*   m_tail;
    int     m_size;
};

#endif