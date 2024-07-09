#pragma once

template <typename T>
struct RecursiveStack {
  T* items;
  int top;
  unsigned int maxSize;

  void init(unsigned int size);
  void copyStack(const RecursiveStack<T>& s);
  void recursive_copyStack(const RecursiveStack<T>& s, int currentTop);
  void release();

  bool isEmpty();
  void push(T newItem);
  T pop();
  T topValue();

  void print(int currentTop);
};

#include "recursive_stack.cpp"