#include "queue.h"

#include <iostream>

using namespace std;

template <typename T>
void Queue<T>::init(unsigned int queueSize) {
  items = new T[queueSize];
  front = 0;
  rear = -1;
  count = 0;
  maxSize = queueSize;
}

template <typename T>
void Queue<T>::copyQueue(const Queue<T> &q) {
  items = new T[q.maxSize];
  front = q.front;
  rear = q.rear;
  count = q.count;
  maxSize = q.maxSize;

  for (int i = 0; i < count; i++) {
    items[i] = q.items[i];
  }
}

template <typename T>
void Queue<T>::release() {
  delete[] items;
  front = 0;
  rear = -1;
  count = 0;
  maxSize = 0;
}

template <typename T>
bool Queue<T>::isEmpty() {
  return count == 0;
}

template <typename T>
void Queue<T>::enqueue(T newItem) {
  if (count == maxSize) {
    cout << "Queue is full! Can't enqueue!\n";
    return;
  }

  rear = (rear + 1) % maxSize;
  items[rear] = newItem;
  count++;
}

template <typename T>
T Queue<T>::dequeue() {
  T item = items[front];
  front = (front + 1) % maxSize;
  count--;

  return item;
}

template <typename T>
T Queue<T>::frontValue() {
  if (isEmpty()) {
    cout << "Queue is empty!\n";
    return T();
  }

  return items[front];
}

template <typename T>
void Queue<T>::print() {
  if (isEmpty()) {
    cout << "Queue is empty! Can't print!\n";
    return;
  }

  int i = front;
  cout << "Queue: ";
  while (i != rear) {
    cout << items[i] << " ";
    i = (i + 1) % maxSize;
  }
  cout << items[rear] << endl;
}
