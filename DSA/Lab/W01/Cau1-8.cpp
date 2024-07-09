#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(string s) {
  int n = s.length();
  for (int i = 0; i < n / 2; i++)
    if (s[i] != s[n - i - 1]) return false;
  return true;
}

void preProcess(string &s) {
  int n = s.length();
  for (int i = 0; i < n; i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
    if (!isdigit(s[i]) && (s[i] < 'a' || s[i] > 'z')) {
      s.erase(i, 1);
      i--;
      n--;
    }
  }
}

int main() {
  fstream in;
  in.open("input1.8.1.txt", ios::in);
  string line;
  while (getline(in, line)) {
    string temp = line;
    preProcess(temp);
    if (isPalindrome(temp)) cout << line << endl;
  }
  in.close();
  return 0;
}