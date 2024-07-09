#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Fraction {
  int numerator;
  int denominator = 1;
};

void getInput(fstream &in, Fraction **&a, int &m, int &n) {
  in >> m >> n;
  a = new Fraction *[m];
  for (int i = 0; i < m; i++) {
    a[i] = new Fraction[n];
  }
  string str, temp;
  int count = 0;
  bool check = false;
  getline(in, str);
  for (int i = 0; i < m; i++) {
    getline(in, str);
    count = 0;
    for (int j = 0; j < str.length(); j++) {
      if (str[j] == ' ' || j == str.length() - 1) {
        if (j == str.length() - 1) {
          temp += str[j];
        }
        if (check) {
          a[i][count].denominator = stoi(temp);
        } else {
          a[i][count].numerator = stoi(temp);
        }
        count++;
        check = false;
        temp = "";
      } else {
        if (str[j] == '/') {
          a[i][count].numerator = stoi(temp);
          temp = "";
          check = true;
        } else
          temp += str[j];
      }
    }
  }
}

void reduceFraction(Fraction &f) {
  int a = f.numerator;
  int b = f.denominator;
  while (a != b) {
    if (a > b) {
      a -= b;
    } else {
      b -= a;
    }
  }
  f.numerator /= a;
  f.denominator /= a;
}

void makeOutput(fstream &out, Fraction **a, int m, int n) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      reduceFraction(a[i][j]);
      if (a[i][j].denominator != 1) {
        out << a[i][j].numerator << "/" << a[i][j].denominator << " ";
      } else {
        out << a[i][j].numerator << " ";
      }
    }
    out << endl;
  }
}

int main() {
  fstream in, out;
  in.open("input1.2.txt", ios::in);
  out.open("output1.2.txt", ios::out);
  Fraction **a;
  int m, n;
  getInput(in, a, m, n);
  makeOutput(out, a, m, n);
  in.close();
  out.close();
  return 0;
}