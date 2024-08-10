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
  if (table[index] == nullptr) {
    table[index] = new hashNode{key, value, nullptr};
  } else {
    hashNode* temp = table[index];
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = new hashNode{key, value, nullptr};
  }
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  if (table.empty()) {
    return nullptr;
  }
  unsigned int index = hashFunction(key);
  hashNode* temp = table[index];
  while (temp != nullptr) {
    if (temp->key == key) {
      return &temp->value;
    }
    temp = temp->next;
  }
  return nullptr;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  if (table.empty()) {
    return;
  }
  unsigned int index = hashFunction(key);
  hashNode* temp = table[index];
  if (temp == nullptr) {
    return;
  }
  if (temp->key == key) {
    table[index] = temp->next;
    delete temp;
    return;
  }
  while (temp->next != nullptr) {
    if (temp->next->key == key) {
      hashNode* toDelete = temp->next;
      temp->next = temp->next->next;
      delete toDelete;
      return;
    }
    temp = temp->next;
  }
}
