#include "recursive_stack.h"

#include <iostream>

using namespace std;

template <typename T>
void RecursiveStack<T>::init(unsigned int stackSize) {
  items = new T[stackSize];
  top = -1;
  maxSize = stackSize;
}

template <typename T>
void RecursiveStack<T>::copyStack(const RecursiveStack<T>& s) {
  maxSize = s.maxSize;
  top = s.top;
  recursive_copyStack(s, top);
}

template <typename T>
void RecursiveStack<T>::recursive_copyStack(const RecursiveStack<T>& s,
                                            int currentTop) {
  if (currentTop == -1) return;
  recursive_copyStack(s, currentTop - 1);
  items[currentTop] = s.items[currentTop];
}

template <typename T>
void RecursiveStack<T>::release() {
  delete[] items;
  top = -1;
  maxSize = 0;
}

template <typename T>
bool RecursiveStack<T>::isEmpty() {
  return top == -1;
}

template <typename T>
void RecursiveStack<T>::push(T newItem) {
  if (top == maxSize - 1) {
    cout << "Stack is full! Can't push!" << endl;
    return;
  }

  items[++top] = newItem;
}

template <typename T>
T RecursiveStack<T>::pop() {
  return items[top--];
}

template <typename T>
T RecursiveStack<T>::topValue() {
  if (isEmpty()) {
    cout << "Stack is empty!" << endl;
    return T();
  }
  return items[top];
}

template <typename T>
void RecursiveStack<T>::print(int currentTop) {
  if (isEmpty()) {
    cout << "Stack is empty! Can't print!" << endl;
    return;
  }
  if (currentTop == top) cout << "Stack: ";
  if (currentTop == -1) {
    cout << endl;
    return;
  }
  cout << items[currentTop] << " ";
  print(currentTop - 1);
}
