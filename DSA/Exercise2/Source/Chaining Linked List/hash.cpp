#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = vector<hashNode*>(capacity, nullptr);
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < table.size(); i++) {
    hashNode* current = table[i];
    while (current != nullptr) {
      hashNode* next = current->next;
      delete current;
      current = next;
    }
  }
}

template <typename K, typename V>
void hashTable<K, V>::display() {
  int width = 5;
  cout << "+------------------------------------------------------" << endl;
  cout << "|" << setw(width) << "Index"
       << "|" << setw(width) << "(Key, Value)" << endl;
  cout << "+------------------------------------------------------" << endl;

  for (int i = 0; i < table.size(); i++) {
    cout << "|" << i << setw(width) << "|";
    hashNode* current = table[i];
    while (current != nullptr) {
      cout << "(" << current->key << ", " << current->value << ")";
      if (current->next != nullptr) {
        cout << " -> ";
      }
      current = current->next;
    }
    cout << endl;
  }
  cout << "+------------------------------------------------------" << endl;
  cout << endl;
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(int key) {
  return key % capacity;
}

template <typename K, typename V>
unsigned int hashTable<K, V>::hashFunction(string key) {
  const int p = 31;
  const int m = 1e9 + 9;
  unsigned long long hash = 0;
  unsigned long long p_pow = 1;

  for (char c : key) {
    hash = (hash + (c * p_pow) % m) % m;
    p_pow = (p_pow * p) % m;
  }

  return hash % capacity;
}

template <typename K, typename V>
void hashTable<K, V>::add(K key, V value) {
  unsigned int index = hashFunction(key);
  hashNode* newNode = new hashNode{key, value, nullptr};

  if (table[index] == nullptr) {
    table[index] = newNode;
  } else {
    hashNode* current = table[index];
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  hashNode* current = table[index];

  while (current != nullptr) {
    if (current->key == key) {
      return &current->value;
    }
    current = current->next;
  }

  return nullptr;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  hashNode* current = table[index];
  hashNode* previous = nullptr;

  while (current != nullptr) {
    if (current->key == key) {
      if (previous == nullptr) {
        table[index] = current->next;
      } else {
        previous->next = current->next;
      }
      delete current;
      return;
    }
    previous = current;
    current = current->next;
  }
}
