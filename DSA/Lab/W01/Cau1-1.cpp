#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

void getInput(fstream &in, string &s) {
  string temp;
  while (!in.eof()) {
    getline(in, temp);
    s += temp + "\n";
  }
}

void display(string s) { cout << s; }

string toLowerCase(string &s) {
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  return s;
}

int countDistinctWords(string &s) {
  s = toLowerCase(s);
  set<string> distinctWords;
  stringstream ss(s);
  string word;

  while (ss >> word) {
    distinctWords.insert(word);
  }

  return distinctWords.size();
}

int countSentences(string s) {
  int count = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == '.' || s[i] == '?' || s[i] == '!') {
      count++;
    }
  }
  return count;
}

int main() {
  fstream in;
  in.open("input1.1.txt", ios::in);
  string s;
  getInput(in, s);
  in.close();
  display(s);
  cout << "Number of distinct words: " << countDistinctWords(s) << endl;
  cout << "Number of sentences: " << countSentences(s);
  return 0;
}