#ifndef LIST_HPP
#define LIST_HPP

#include "../Test.hpp"
#include "../Utils.hpp"

template<typename T>
class List
{
  TESTABLE

  public:
    struct Node
    {
      Node (T v)
        : value     { v }
        , next      { nullptr }
        , previous  { nullptr }
      {}

      Node*   next;
      Node*   previous;
      T       value;
    };

    List ();
    ~List ();
    void push_back (T item);
    void push_front (T item);
    void pop_front ();
    void pop_back ();
    Node* find (T item);
    void insertAfter (Node* node, T item);
    void insertBefore (Node* node, T item);
    void swap (Node* a, Node* b);
    T head () const;
    T tail () const;
    int size () const;

  private:
    std::string state () const;
    void deleteNode (Node* node);

    Node*   m_head;
    Node*   m_tail;
    int     m_size;
};

#include "List.tpp"

#endif