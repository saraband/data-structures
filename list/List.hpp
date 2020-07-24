#ifndef LIST_HPP
#define LIST_HPP

#include "../Test.hpp"
#include "../Utils.hpp"

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
      // Recursively delete all nodes starting from the head
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

      // Empty list
      if (!m_size) {
        m_head = node;
        m_tail = node;

      // Other cases
      } else {
        m_tail->next = node;
        node->previous = m_tail;
        m_tail = node;
      }

      m_size++;
    }

    void push_front (T item)
    {
      Node* node = new Node(item);

      // Empty list
      if (!m_size) {
        m_head = node;
        m_tail = node;

      // Other cases
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

      // Only one element case, resets to empty list
      if (m_head->next == nullptr) {
        m_head = nullptr;
        m_tail = nullptr;

      // Other cases
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

      // Only one element case, resets to empty list
      if (m_tail->previous == nullptr) {
        m_head = nullptr;
        m_tail = nullptr;

      // Other cases
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

      // Insert after the tail, reconnect to the new tail
      if (node == m_tail)
        m_tail = node->next;
      // Other cases, reconnect with the following elements
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

      // Insert before the head, reconnect to the new head
      if (node == m_head)
        m_head = node->previous;
      // Other cases, reconnect with the preceding elements
      else
        oldPreviousNode->next = node->previous;

      m_size++;
    }

    void swap (Node* a, Node* b)
    {
      // Swapping requires at least 2 nodes
      if (m_size < 2)
        return;

      // Same node, do nothing
      if (a == b)
        return;

      Node* aNextTemp = a->next;
      Node* aPreviousTemp = a->previous;
      Node* bNextTemp = b->next;
      Node* bPreviousTemp = b->previous;

      // Change next/previous pointers of nodes connected to the nodes to swap
      // Or if a node to swap has no neighbor, then it must be the head/tail
      // Update it
      if (a->next)
        a->next->previous = b;
      else
        m_tail = b;
      if (a->previous)
        a->previous->next = b;
      else
        m_head = b;
      if (b->next)
        b->next->previous = a;
      else
        m_tail = a;
      if (b->previous)
        b->previous->next = a;
      else
        m_head = a;

      // Swap next/previous pointers of the nodes to swap
      a->next = bNextTemp;
      a->previous = bPreviousTemp;
      b->next = aNextTemp;
      b->previous = aPreviousTemp;

      // a and b are neighbors case case
      if (aNextTemp == b) {
        a->previous = b;
        b->next = a;
      } else if (bNextTemp == a) {
        b->previous = a;
        a->next = b;
      }
    }

    T head () const
    {
      return m_head->value;
    }

    T tail () const
    {
      return m_tail->value;
    }

    int size () const
    {
      return m_size;
    }

  private:
    // For testing
    std::string state () const
    {
      std::string state;
      Node* current = m_head;

      while (current) {
        state += toString(current->value);

        if (current->next)
          state += " ";

        current = current->next;
      }

      return state;
    }

    // Deletes a node and all the next nodes recursively
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