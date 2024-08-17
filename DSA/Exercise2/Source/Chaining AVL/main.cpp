#include "hash.h"

using namespace std;

int main() {
  hashTable<int, string> hash;
  hash.init(5);

  hash.add(7, "Seven");
  hash.add(13, "Thirteen");
  hash.add(5, "Five");
  hash.add(18, "Eighteen");

  cout << "Hash table" << endl;
  hash.display();

  cout << "Add key 2" << endl;
  hash.add(2, "Two");
  hash.display();

  cout << "Add key 17" << endl;
  hash.add(17, "Seventeen");
  hash.display();

  cout << "Remove key 13" << endl;
  hash.removeKey(13);
  hash.display();

  cout << "Search for key 13" << endl;
  string *value = hash.searchValue(4);
  if (value != nullptr) {
    cout << "Value for key 13: " << *value << endl;
  } else {
    cout << "Key 13 not found" << endl;
  }

  cout << "Search for key 5" << endl;
  value = hash.searchValue(5);
  if (value != nullptr) {
    cout << "Value for key 5: " << *value << endl;
  } else {
    cout << "Key 5 not found" << endl;
  }

  hash.release();

  return 0;
}
