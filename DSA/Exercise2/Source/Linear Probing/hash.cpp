#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = vector<hashNode*>(capacity, nullptr);
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < capacity; i++) {
    if (table[i] != nullptr) {
      delete table[i];
      table[i] = nullptr;
    }
  }
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(int key) {
  return key % capacity;
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(string key) {
  const int p = 31;
  const int m = 1e9 + 9;
  long long hash = 0;
  long long pPow = 1;

  for (char c : key) {
    hash = (hash + (c - 'a' + 1) * pPow) % m;
    pPow = (pPow * p) % m;
  }
  return hash % capacity;
}

template <typename K, typename V>
void hashTable<K, V>::add(K key, V value) {
  if (table.empty()) {
    throw runtime_error("Hash table is not initialized.");
  }

  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;
  while (table[index] != nullptr) {
    index = (index + 1) % capacity;
    if (index == startIndex) {
      throw runtime_error("Hash table is full.");
    }
  }
  table[index] = new hashNode{key, value};
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  if (table.empty()) {
    return nullptr;
  }

  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;
  while (table[index] != nullptr && table[index]->key != key) {
    index = (index + 1) % capacity;
    if (index == startIndex) {
      return nullptr;
    }
  }
  if (table[index] == nullptr) {
    return nullptr;
  }
  return &table[index]->value;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  if (table.empty()) {
    return;
  }

  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;
  while (table[index] != nullptr && table[index]->key != key) {
    index = (index + 1) % capacity;
    if (index == startIndex) {
      return;
    }
  }
  if (table[index] == nullptr) {
    return;
  }
  delete table[index];
  table[index] = nullptr;
}