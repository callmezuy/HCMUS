#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void process(fstream &in, int type, int n) {
  if (type == 0) {
    while (n > 0 && !in.eof()) {
      string line;
      getline(in, line);
      cout << line << endl;
      n--;
    }
    return;
  }
  if (type == 1) {
    deque<string> dq;
    while (!in.eof()) {
      string line;
      getline(in, line);
      dq.push_back(line);
      if (dq.size() > n) {
        dq.pop_front();
      }
    }
    while (!dq.empty()) {
      cout << dq.front() << endl;
      dq.pop_front();
    }
    return;
  }
}

int main(int agrc, char *argv[]) {
  if (agrc != 4) {
    cout << "Invalid arguments" << endl;
    return 1;
  }
  int type = stoi(argv[1]);
  int n = stoi(argv[2]);
  string filename = argv[3];
  fstream in;
  in.open(filename, ios::in);
  process(in, type, n);
  in.close();
  return 0;
}