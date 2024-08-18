#include <time.h>

#include <chrono>
#include <fstream>

#include "hash.h"

using namespace std::chrono;

#define N 300000

struct Book {
  string title;
  string author;
};

void getInput(fstream &f, hashTable<string, string> &hashTable,
              vector<Book> &books);
string searchBookInHashTable(hashTable<string, string> &hashTable,
                             string title);
string searchBookInVector(vector<Book> &books, string title);

int main() {
  fstream f;
  hashTable<string, string> hashTable;
  hashTable.init(N);
  vector<Book> books;

  getInput(f, hashTable, books);

  cout << "Searching for author name of the first book:" << endl;
  string key = books[0].title;
  auto start = high_resolution_clock::now();
  string author = searchBookInHashTable(hashTable, key);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Hash Table: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  author = searchBookInVector(books, key);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Vector: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  cout << "---------------------------------------------" << endl;

  cout << "Searching for author name of the middle book:" << endl;
  key = books[books.size() / 2].title;
  start = high_resolution_clock::now();
  author = searchBookInHashTable(hashTable, key);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Hash Table: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  author = searchBookInVector(books, key);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Vector: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  cout << "---------------------------------------------" << endl;

  cout << "Searching for author name of the last book:" << endl;
  key = books[books.size() - 1].title;
  start = high_resolution_clock::now();
  author = searchBookInHashTable(hashTable, key);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Hash Table: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  author = searchBookInVector(books, key);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Vector: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  cout << "---------------------------------------------" << endl;

  cout << "Searching for key not exist:" << endl;
  key = "NULL";
  start = high_resolution_clock::now();
  author = searchBookInHashTable(hashTable, key);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Hash Table: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  start = high_resolution_clock::now();
  author = searchBookInVector(books, key);
  stop = high_resolution_clock::now();
  duration = duration_cast<microseconds>(stop - start);
  cout << "Vector: " << author << endl;
  cout << "Time taken: " << duration.count() << " microseconds" << endl;

  hashTable.release();
  f.close();
  return 0;
}

void getInput(fstream &f, hashTable<string, string> &hashTable,
              vector<Book> &books) {
  f.open("../../books.txt", ios::in);
  if (!f.is_open()) {
    cout << "Cannot open file" << endl;
    return;
  }
  string line;
  getline(f, line);
  while (getline(f, line)) {
    int pos = line.find('|');
    string title = line.substr(0, pos);
    string author = line.substr(pos + 1);
    Book book = {title, author};
    books.push_back(book);
    hashTable.add(title, author);
  }
}

string searchBookInHashTable(hashTable<string, string> &hashTable,
                             string title) {
  string *author = hashTable.searchValue(title);
  return author == nullptr ? "Not found" : *author;
}

string searchBookInVector(vector<Book> &books, string title) {
  for (Book book : books) {
    if (book.title == title) {
      return book.author;
    }
  }
  return "Not found";
}