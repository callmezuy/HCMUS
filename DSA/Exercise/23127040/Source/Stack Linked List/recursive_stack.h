#pragma once

template <typename T>
struct RecursiveStack {
  struct Node {
    T data;
    Node *next;
  };

  Node *top;

  void init();
  void copyStack(const RecursiveStack<T> &s);
  void copyStackHelper(Node *node);
  void release();

  bool isEmpty();
  void push(T newItem);
  T pop();
  T topValue();

  void print();
  void printHelper(Node *node);
};

#include "recursive_stack.cpp"