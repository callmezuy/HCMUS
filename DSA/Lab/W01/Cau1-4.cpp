#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void lineDiff(fstream &in1, fstream &in2) {
  string temp1;
  string temp2;
  int line = 0;
  while (getline(in1, temp1) && getline(in2, temp2)) {
    line++;
    if (temp1 != temp2) {
      cout << line << "// " << temp1 << endl;
      cout << line << "\\\\ " << temp2 << endl;
    }
  }
}

int main() {
  fstream in1("input1.4.1.txt", ios::in);
  fstream in2("input1.4.2.txt", ios::in);
  lineDiff(in1, in2);
  in1.close();
  in2.close();
  return 0;
}