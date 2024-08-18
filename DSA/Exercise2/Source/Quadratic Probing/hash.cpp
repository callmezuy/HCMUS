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
    }
  }
}

template <typename K, typename V>
void hashTable<K, V>::display() {
  const int indexWidth = 7;
  const int keyWidth = 20;
  const int valueWidth = 20;
  const int totalWidth = indexWidth + keyWidth + valueWidth + 4;

  cout << "+" << string(totalWidth - 2, '-') << "+" << endl;

  cout << "|" << left << setw(indexWidth) << "Index"
       << "|" << left << setw(keyWidth) << "Key"
       << "|" << left << setw(valueWidth) << "Value"
       << "|" << endl;

  cout << "+" << string(totalWidth - 2, '-') << "+" << endl;

  for (int i = 0; i < capacity; i++) {
    if (table[i] != nullptr) {
      cout << "|" << left << setw(indexWidth) << i << "|" << left
           << setw(keyWidth) << table[i]->key << "|" << left << setw(valueWidth)
           << table[i]->value << "|" << endl;
    }
  }

  cout << "+" << string(totalWidth - 2, '-') << "+" << endl;
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
  if (table.empty()) {
    throw runtime_error("Hash table is not initialized.");
  }

  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;
  int i = 1;

  while (table[index] != nullptr) {
    if (table[index]->key == key) {
      table[index]->value = value;
      return;
    }
    index = (startIndex + i * i) % capacity;
    i++;
    if (index == startIndex) {
      rehash();
      add(key, value);
      return;
    }
  }

  table[index] = new hashNode{key, value};
}

template <typename K, typename V>
void hashTable<K, V>::rehash() {
  vector<hashNode*> oldTable = table;
  table = vector<hashNode*>(capacity * 2, nullptr);
  capacity *= 2;

  for (int i = 0; i < oldTable.size(); i++) {
    if (oldTable[i] != nullptr) {
      unsigned int index = hashFunction(oldTable[i]->key);
      unsigned int startIndex = index;
      int j = 1;
      while (table[index] != nullptr) {
        index = (startIndex + j * j) % capacity;
        j++;
      }
      table[index] = oldTable[i];
    }
  }
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  if (table.empty()) {
    return nullptr;
  }

  unsigned int index = hashFunction(key);
  unsigned int startIndex = index;
  int i = 1;
  while (table[index] != nullptr && table[index]->key != key) {
    index = (startIndex + i * i) % capacity;
    i++;
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
  int i = 1;
  while (table[index] != nullptr && table[index]->key != key) {
    index = (startIndex + i * i) % capacity;
    i++;
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