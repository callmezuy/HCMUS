#include <iostream>

#include "hash.h"

int main() {
  HashTable<int, string> hashTable;
  hashTable.init(10);

  hashTable.add(1, "one");
  hashTable.add(2, "two");
  hashTable.add(3, "three");
  hashTable.add(4, "four");
  hashTable.add(5, "five");

  cout << *hashTable.searchValue(1) << endl;
  cout << *hashTable.searchValue(2) << endl;
  cout << *hashTable.searchValue(3) << endl;
  cout << *hashTable.searchValue(4) << endl;
  cout << *hashTable.searchValue(5) << endl;

  hashTable.removeKey(3);
  if (hashTable.searchValue(3) != nullptr) {
    cout << *hashTable.searchValue(3) << endl;
  } else {
    cout << "Key 3 not found" << endl;
  }

  hashTable.release();
  return 0;
}