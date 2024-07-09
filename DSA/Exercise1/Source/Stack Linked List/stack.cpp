#include "stack.h"

#include <iostream>

using namespace std;

template <typename T>
void Stack<T>::init() {
  top = nullptr;
}

template <typename T>
void Stack<T>::copyStack(const Stack<T> &s) {
  init();
  Node *temp = s.top;
  while (temp) {
    push(temp->data);
    temp = temp->next;
  }
}

template <typename T>
void Stack<T>::release() {
  Node *temp = top;
  while (top) {
    top = top->next;
    delete temp;
    temp = top;
  }
}

template <typename T>
bool Stack<T>::isEmpty() {
  return top == nullptr;
}

template <typename T>
void Stack<T>::push(T newItem) {
  Node *newNode = new Node;
  newNode->data = newItem;
  newNode->next = top;
  top = newNode;
}

template <typename T>
T Stack<T>::pop() {
  if (isEmpty()) {
    cout << "Stack is empty!" << endl;
    return T();
  }
  Node *temp = top;
  T data = top->data;
  top = top->next;
  delete temp;
  return data;
}

template <typename T>
T Stack<T>::topValue() {
  if (isEmpty()) {
    cout << "Stack is empty!" << endl;
    return T();
  }
  return top->data;
}

template <typename T>
void Stack<T>::print() {
  if (isEmpty()) {
    cout << "Stack is empty! Can't print!" << endl;
    return;
  }
  cout << "Stack: ";
  Node *temp = top;
  while (temp) {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << endl;
}
