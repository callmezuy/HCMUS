#include "hash.h"

template <typename K, typename V>
void hashTable<K, V>::init(unsigned int hashSize) {
  capacity = hashSize;
  table = vector<hashNode*>(capacity, nullptr);
}

template <typename K, typename V>
void hashTable<K, V>::release() {
  for (int i = 0; i < table.size(); i++) {
    deleteTree(table[i]);
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
    displayTree(table[i]);
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
  unsigned int index = hashFunction(key);
  table[index] = insertNode(table[index], key, value);
}

template <typename K, typename V>
V* hashTable<K, V>::searchValue(K key) {
  unsigned int index = hashFunction(key);
  hashNode* node = searchNode(table[index], key);

  return node == nullptr ? nullptr : &node->value;
}

template <typename K, typename V>
void hashTable<K, V>::removeKey(K key) {
  unsigned int index = hashFunction(key);
  table[index] = deleteNode(table[index], key);
}

template <typename K, typename V>
int hashTable<K, V>::getHeight(hashNode* node) {
  return node == nullptr ? 0 : node->height;
}

template <typename K, typename V>
int hashTable<K, V>::balanceFactor(hashNode* node) {
  return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::rotateRight(
    hashNode* node) {
  hashNode* leftChild = node->left;
  hashNode* rightChild = leftChild->right;

  leftChild->right = node;
  node->left = rightChild;

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  leftChild->height =
      1 + max(getHeight(leftChild->left), getHeight(leftChild->right));

  return leftChild;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::rotateLeft(
    hashNode* node) {
  hashNode* rightChild = node->right;
  hashNode* leftChild = rightChild->left;

  rightChild->left = node;
  node->right = leftChild;

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  rightChild->height =
      1 + max(getHeight(rightChild->left), getHeight(rightChild->right));

  return rightChild;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::newNode(K key, V value) {
  return new hashNode(key, value);
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::insertNode(hashNode* node,
                                                                K key,
                                                                V value) {
  if (node == nullptr) {
    return newNode(key, value);
  }

  if (key < node->key) {
    node->left = insertNode(node->left, key, value);
  } else if (key > node->key) {
    node->right = insertNode(node->right, key, value);
  } else {
    node->value = value;
    return node;
  }

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  int bf = balanceFactor(node);

  if (bf > 1 && key < node->left->key) {
    return rotateRight(node);
  }
  if (bf < -1 && key > node->right->key) {
    return rotateLeft(node);
  }
  if (bf > 1 && key > node->left->key) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (bf < -1 && key < node->right->key) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::searchNode(hashNode* node,
                                                                K key) {
  if (node == nullptr || node->key == key) {
    return node;
  }

  return key < node->key ? searchNode(node->left, key)
                         : searchNode(node->right, key);
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::minValueNode(
    hashNode* node) {
  hashNode* current = node;

  while (current->left != nullptr) {
    current = current->left;
  }

  return current;
}

template <typename K, typename V>
typename hashTable<K, V>::hashNode* hashTable<K, V>::deleteNode(hashNode* node,
                                                                K key) {
  if (node == nullptr) {
    cout << "Key not found" << endl;
    return node;
  }

  if (key < node->key) {
    node->left = deleteNode(node->left, key);
  } else if (key > node->key) {
    node->right = deleteNode(node->right, key);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      hashNode* temp = node->left ? node->left : node->right;

      if (temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
      }

      delete temp;
    } else {
      hashNode* temp = minValueNode(node->right);
      node->key = temp->key;
      node->value = temp->value;
      node->right = deleteNode(node->right, temp->key);
    }
  }

  if (node == nullptr) {
    return node;
  }

  node->height = 1 + max(getHeight(node->left), getHeight(node->right));
  int bf = balanceFactor(node);

  if (bf > 1 && balanceFactor(node->left) >= 0) {
    return rotateRight(node);
  }
  if (bf > 1 && balanceFactor(node->left) < 0) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  if (bf < -1 && balanceFactor(node->right) <= 0) {
    return rotateLeft(node);
  }
  if (bf < -1 && balanceFactor(node->right) > 0) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}

template <typename K, typename V>
void hashTable<K, V>::deleteTree(hashNode* node) {
  if (node == nullptr) {
    return;
  }

  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

template <typename K, typename V>
void hashTable<K, V>::displayTree(hashNode* node) {
  if (node == nullptr) {
    return;
  }

  displayTree(node->left);
  cout << "(" << node->key << ", " << node->value << ") ";
  displayTree(node->right);
}