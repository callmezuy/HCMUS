#include "recursive_queue.h"

#include <iostream>

using namespace std;

template <typename T>
void RecursiveQueue<T>::init(unsigned int queueSize) {
  items = new T[queueSize];
  front = 0;
  rear = -1;
  count = 0;
  maxSize = queueSize;
}

template <typename T>
void RecursiveQueue<T>::copyQueue(const RecursiveQueue<T> &q) {
  items = new T[q.maxSize];
  front = q.front;
  rear = q.rear;
  count = q.count;
  maxSize = q.maxSize;

  copyQueueHelper(q, 0);
}

template <typename T>
void RecursiveQueue<T>::copyQueueHelper(const RecursiveQueue<T> &q, int index) {
  if (index == q.count) {
    return;
  }

  items[index] = q.items[index];
  copyQueueHelper(q, index + 1);
}

template <typename T>
void RecursiveQueue<T>::release() {
  delete[] items;
  front = 0;
  rear = -1;
  count = 0;
  maxSize = 0;
}

template <typename T>
bool RecursiveQueue<T>::isEmpty() {
  return count == 0;
}

template <typename T>
void RecursiveQueue<T>::enqueue(T newItem) {
  if (count == maxSize) {
    cout << "Queue is full! Can't enqueue!\n";
    return;
  }

  rear = (rear + 1) % maxSize;
  items[rear] = newItem;
  count++;
}

template <typename T>
T RecursiveQueue<T>::dequeue() {
  T item = items[front];
  front = (front + 1) % maxSize;
  count--;

  return item;
}

template <typename T>
T RecursiveQueue<T>::frontValue() {
  if (isEmpty()) {
    cout << "Queue is empty!\n";
    return T();
  }

  return items[front];
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
void RecursiveQueue<T>::printHelper(int index) {
  if (index > rear) {
    return;
  }

  cout << items[index] << " ";
  printHelper(index + 1);
}
