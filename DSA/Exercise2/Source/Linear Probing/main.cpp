#include "hash.h"

int main() {
  hashTable<int, string> hash;
  hash.init(10);

  hash.add(1, "One");
  hash.add(2, "Two");
  hash.add(3, "Three");
  hash.add(4, "Four");
  hash.add(5, "Five");
  hash.add(6, "Six");
  hash.add(7, "Seven");
  hash.add(8, "Eight");
  hash.add(9, "Nine");
  hash.add(10, "Ten");

  cout << "Hash table" << endl;
  hash.display();

  cout << "Remove key 5" << endl;
  hash.removeKey(5);
  cout << "Search key 5" << endl;
  if (hash.searchValue(5) == nullptr) {
    cout << "Key 5 not found" << endl;
  }

  hash.display();

  hash.release();

  return 0;
}