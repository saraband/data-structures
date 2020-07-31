#ifndef LIST_HPP
#define LIST_HPP

#include "../Test.hpp"
#include "../Utils.hpp"

template<typename ValueType>
class List
{
  TESTABLE

  public:
    struct Node
    {
      Node (const ValueType& v)
        : value     { v }
        , next      { nullptr }
        , previous  { nullptr }
      {}
      
      ValueType   value;
      Node*       next;
      Node*       previous;
    };

    List ();
    ~List ();
    void push_back (const ValueType& item);
    void push_front (const ValueType& item);
    void pop_front ();
    void pop_back ();
    Node* find (const ValueType& item);
    void insertAfter (Node* node, const ValueType& item);
    void insertBefore (Node* node, const ValueType& item);
    void swap (Node* a, Node* b);
    const ValueType& head () const;
    const ValueType& tail () const;
    int size () const;

  private:
    void deleteNode (Node* node);

    Node*   m_head;
    Node*   m_tail;
    int     m_size;
};

#include "List.tpp"

#endif