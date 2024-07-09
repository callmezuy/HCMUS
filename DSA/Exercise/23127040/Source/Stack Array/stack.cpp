#include "stack.h"

#include <iostream>

using namespace std;

template <typename T>
void Stack<T>::init(unsigned int stackSize) {
  items = new T[stackSize];
  top = -1;
  maxSize = stackSize;
}

template <typename T>
void Stack<T>::copyStack(const Stack<T> &s) {
  maxSize = s.maxSize;
  top = s.top;
  for (int i = 0; i <= top; i++) items[i] = s.items[i];
}

template <typename T>
void Stack<T>::release() {
  delete[] items;
  top = -1;
  maxSize = 0;
}

template <typename T>
bool Stack<T>::isEmpty() {
  return top == -1;
}

template <typename T>
void Stack<T>::push(T newItem) {
  if (top == maxSize - 1) {
    cout << "Stack is full! Can't push!" << endl;
    return;
  }
  items[++top] = newItem;
}

template <typename T>
T Stack<T>::pop() {
  return items[top--];
}

template <typename T>
T Stack<T>::topValue() {
  if (isEmpty()) {
    cout << "Stack is empty!" << endl;
    return T();
  }
  return items[top];
}

template <typename T>
void Stack<T>::print() {
  if (isEmpty()) {
    cout << "Stack is empty! Can't print!" << endl;
    return;
  }
  cout << "Stack: ";
  for (int i = 0; i <= top; i++) cout << items[i] << " ";
  cout << endl;
}
