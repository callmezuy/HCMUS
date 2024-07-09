#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define MAX 1000

struct Word {
  string word;
  string line;
};

struct Dictionary {
  vector<Word> words;
  int n;
};

void getInput(fstream &in, Dictionary &dict);
void makeOutput(fstream &out, Dictionary &dict, char *key[], int keyCount);

Word *search(Dictionary &dict, string key);

string trim(string &s);
string toLower(string &s);

void merge(Dictionary &dict, int left, int mid, int right);
void mergeSort(Dictionary &dict, int left, int right);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Invalid arguments" << endl;
    return 1;
  }

  fstream in, out;
  in.open("English-Vietnamese Dictionary.txt", ios::in);
  if (!in.is_open()) {
    cout << "Cannot open file" << endl;
    return 1;
  }

  Dictionary dict;
  getInput(in, dict);

  in.close();

  int keyCount = argc - 2;
  char *key[keyCount * 100];
  string outfile;
  for (int i = 1; i < argc; i++) {
    if (i == argc - 1) {
      outfile = argv[i];
      break;
    }
    key[i - 1] = argv[i];
  }

  out.open(outfile, ios::out);
  if (!out.is_open()) {
    cout << "Cannot open file" << endl;
    return 1;
  }

  makeOutput(out, dict, key, keyCount);

  out.close();

  return 0;
}

void getInput(fstream &in, Dictionary &dict) {
  dict.words.clear();
  string line;
  while (getline(in, line)) {
    Word w;
    w.line = line;
    string word;
    int i = 0;
    while (line[i] != ':') {
      word += line[i];
      i++;
    }
    w.word = trim(word);
    w.word = toLower(w.word);
    dict.words.push_back(w);
  }
  dict.n = dict.words.size();
}

string trim(string &s) {
  while (s[0] == ' ') {
    s.erase(0, 1);
  }
  while (s[s.length() - 1] == ' ') {
    s.erase(s.length() - 1, 1);
  }
  return s;
}

string toLower(string &s) {
  for (int i = 0; i < s.length(); i++) {
    s[i] = tolower(s[i]);
  }
  return s;
}

void merge(Dictionary &dict, int left, int mid, int right) {
  int i, j, k;
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<Word> L(n1), R(n2);

  for (i = 0; i < n1; i++) L[i] = dict.words[left + i];
  for (j = 0; j < n2; j++) R[j] = dict.words[mid + 1 + j];

  i = 0;
  j = 0;
  k = left;
  while (i < n1 && j < n2) {
    if (L[i].word <= R[j].word) {
      dict.words[k] = L[i];
      i++;
    } else {
      dict.words[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    dict.words[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    dict.words[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(Dictionary &dict, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;

    mergeSort(dict, left, mid);
    mergeSort(dict, mid + 1, right);

    merge(dict, left, mid, right);
  }
}

Word *search(Dictionary &dict, string key) {
  int left = 0;
  int right = dict.n - 1;
  string temp = toLower(key);
  while (left <= right) {
    int mid = (left + right) / 2;
    if (dict.words[mid].word == temp) {
      return &dict.words[mid];
    }
    if (dict.words[mid].word < temp) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return nullptr;
}

void makeOutput(fstream &out, Dictionary &dict, char *key[], int keyCount) {
  for (int i = 0; i < keyCount; i++) {
    Word *w = search(dict, key[i]);
    if (w != nullptr) {
      out << w->line << endl;
    } else {
      out << "Word \"" << key[i] << "\" not found" << endl;
    }
  }
}
