#pragma once

template <typename T>
struct RecursiveQueue {
  struct Node {
    T data;
    Node *next;
  };

  Node *front;
  Node *rear;

  void init();
  void copyNode(Node *node);
  void copyQueue(const RecursiveQueue<T> &q);
  void release();

  bool isEmpty();
  void enqueue(T newItem);
  T dequeue();
  T frontValue();

  void print();
  void printHelper(Node *current);
};

#include "recursive_queue.cpp"