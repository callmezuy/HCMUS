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
    hashNode* next;
  };

  int capacity;
  vector<hashNode*> table;

  void init(unsigned int hashSize);
  void release();
  void display();
  unsigned int hashFunction(int key);
  unsigned int hashFunction(string key);
  void add(K key, V value);
  V* searchValue(K key);
  void removeKey(K key);
};

#include "hash.cpp"