#include "recursive_stack.h"

#include <iostream>

using namespace std;

template <typename T>
void RecursiveStack<T>::init() {
  top = nullptr;
}

template <typename T>
void RecursiveStack<T>::copyStack(const RecursiveStack<T> &s) {
  copyStackHelper(s.top);
}

template <typename T>
void RecursiveStack<T>::copyStackHelper(Node *node) {
  if (node == nullptr) return;
  copyStackHelper(node->next);
  push(node->data);
}

template <typename T>
void RecursiveStack<T>::release() {
  if (top) {
    Node *temp = top;
    top = top->next;
    delete temp;
    release();
  }
}

template <typename T>
bool RecursiveStack<T>::isEmpty() {
  return top == nullptr;
}

template <typename T>
void RecursiveStack<T>::push(T newItem) {
  Node *newNode = new Node;
  newNode->data = newItem;
  newNode->next = top;
  top = newNode;
}

template <typename T>
T RecursiveStack<T>::pop() {
  Node *temp = top;
  T data = top->data;
  top = top->next;
  delete temp;
  return data;
}

template <typename T>
T RecursiveStack<T>::topValue() {
  if (isEmpty()) {
    cout << "Stack is empty!" << endl;
    return T();
  }
  return top->data;
}

template <typename T>
void RecursiveStack<T>::print() {
  if (isEmpty()) {
    cout << "Stack is empty! Can't print!" << endl;
    return;
  }
  cout << "Stack: ";
  printHelper(top);
  cout << endl;
}

template <typename T>
void RecursiveStack<T>::printHelper(Node *node) {
  if (node == nullptr) return;
  cout << node->data << " ";
  printHelper(node->next);
}
