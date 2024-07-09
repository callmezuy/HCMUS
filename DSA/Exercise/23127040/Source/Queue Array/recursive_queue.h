#pragma once

template <typename T>
struct RecursiveQueue {
  T *items;
  int front;
  int rear;
  unsigned int count;
  unsigned int maxSize;

  void init(unsigned int queueSize);
  void copyQueue(const RecursiveQueue<T> &q);
  void copyQueueHelper(const RecursiveQueue<T> &q, int index);
  void release();

  bool isEmpty();
  void enqueue(T newItem);
  T dequeue();
  T frontValue();

  void print();
  void printHelper(int index);
};

#include "recursive_queue.cpp"