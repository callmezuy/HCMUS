#include "queue.h"

#include <iostream>

using namespace std;

template <typename T>
void Queue<T>::init() {
  front = nullptr;
  rear = nullptr;
}

template <typename T>
void Queue<T>::copyQueue(const Queue<T> &q) {
  Node *current = q.front;
  while (current != nullptr) {
    enqueue(current->data);
    current = current->next;
  }
}

template <typename T>
void Queue<T>::release() {
  Node *temp;
  while (front != nullptr) {
    temp = front;
    front = front->next;
    delete temp;
  }
  rear = nullptr;
}

template <typename T>
bool Queue<T>::isEmpty() {
  return front == nullptr;
}

template <typename T>
void Queue<T>::enqueue(T newItem) {
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
T Queue<T>::dequeue() {
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
T Queue<T>::frontValue() {
  if (isEmpty()) {
    cout << "Queue is empty!\n";
    return T();
  }
  return front->data;
}

template <typename T>
void Queue<T>::print() {
  if (isEmpty()) {
    cout << "Queue is empty! Can't print!\n";
    return;
  }

  Node *current = front;
  cout << "Queue: ";
  while (current != nullptr) {
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;
}
