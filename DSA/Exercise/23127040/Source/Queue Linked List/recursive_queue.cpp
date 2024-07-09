#include "recursive_queue.h"

#include <iostream>

using namespace std;

template <typename T>
void RecursiveQueue<T>::init() {
  front = nullptr;
  rear = nullptr;
}

template <typename T>
void RecursiveQueue<T>::copyNode(Node *node) {
  if (node != nullptr) {
    enqueue(node->data);
    copyNode(node->next);
  }
}

template <typename T>
void RecursiveQueue<T>::copyQueue(const RecursiveQueue<T> &q) {
  if (q.front != nullptr) {
    copyNode(q.front);
  }
}

template <typename T>
void RecursiveQueue<T>::release() {
  if (front != nullptr) {
    Node *temp = front;
    front = front->next;
    delete temp;
    release();
  } else {
    rear = nullptr;
  }
}

template <typename T>
bool RecursiveQueue<T>::isEmpty() {
  return front == nullptr;
}

template <typename T>
void RecursiveQueue<T>::enqueue(T newItem) {
  Node *newNode = new Node;
  newNode->data = newItem;
  newNode->next = nullptr;
  if (isEmpty()) {
    front = newNode;
  } else {
    rear->next = newNode;
  }
  rear = newNode;
}

template <typename T>
T RecursiveQueue<T>::dequeue() {
  Node *temp = front;
  T item = temp->data;
  front = front->next;
  delete temp;

  if (front == nullptr) {
    rear = nullptr;
  }
  return item;
}

template <typename T>
T RecursiveQueue<T>::frontValue() {
  if (isEmpty()) {
    cout << "Queue is empty!\n";
    return T();
  }
  return front->data;
}

template <typename T>
void RecursiveQueue<T>::print() {
  if (isEmpty()) {
    cout << "Queue is empty! Can't print!\n";
    return;
  }
  cout << "Queue: ";
  printHelper(front);
  cout << endl;
}

template <typename T>
void RecursiveQueue<T>::printHelper(Node *current) {
  if (current != nullptr) {
    cout << current->data << " ";
    printHelper(current->next);
  }
}