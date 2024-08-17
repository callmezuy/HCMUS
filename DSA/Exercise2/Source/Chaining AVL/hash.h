#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename K, typename V>
struct hashTable {
  struct hashNode {
    K key;
    V value;
    hashNode* left;
    hashNode* right;
    int height;
    hashNode(K key, V value)
        : key(key), value(value), left(nullptr), right(nullptr), height(1) {}
  };

  int capacity;
  vector<hashNode*> table;

 public:
  void init(unsigned int hashSize);
  void release();
  void display();
  unsigned int hashFunction(int key);
  unsigned int hashFunction(string key);
  void add(K key, V value);
  V* searchValue(K key);
  void removeKey(K key);

  int getHeight(hashNode* node);
  int balanceFactor(hashNode* node);
  hashNode* rotateRight(hashNode* node);
  hashNode* rotateLeft(hashNode* node);
  hashNode* newNode(K key, V value);
  hashNode* insertNode(hashNode* node, K key, V value);
  hashNode* searchNode(hashNode* node, K key);
  hashNode* minValueNode(hashNode* node);
  hashNode* deleteNode(hashNode* node, K key);
  void deleteTree(hashNode* node);
  void displayTree(hashNode* node);
};

#include "hash.cpp"