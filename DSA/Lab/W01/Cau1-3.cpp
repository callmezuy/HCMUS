#include <fstream>
#include <iostream>

using namespace std;

#define COLS 12

struct Day {
  double averageTemp;
  double highTemp;
  double lowTemp;
};

void getInput(fstream &in, double **&a, int &n) {
  in >> n;
  a = new double *[n];
  for (int i = 0; i < n; i++) {
    a[i] = new double[COLS];
    for (int j = 0; j < COLS; j++) {
      in >> a[i][j];
    }
  }
}

void findAverageTemp(double **a, Day *&d, int n) {
  for (int i = 0; i < n; i++) {
    double daySum = 0;
    for (int j = 0; j < COLS; j++) {
      daySum += a[i][j];
    }
    d[i].averageTemp = daySum / COLS;
  }
}

void findHighTemp(double **a, Day *&d, int n) {
  for (int i = 0; i < n; i++) {
    double maxTemp = a[i][0];
    for (int j = 1; j < COLS; j++) {
      if (a[i][j] > maxTemp) {
        maxTemp = a[i][j];
      }
    }
    d[i].highTemp = maxTemp;
  }
}

void findLowTemp(double **a, Day *&d, int n) {
  for (int i = 0; i < n; i++) {
    double minTemp = a[i][0];
    for (int j = 1; j < COLS; j++) {
      if (a[i][j] < minTemp) {
        minTemp = a[i][j];
      }
    }
    d[i].lowTemp = minTemp;
  }
}

void makeOutput(fstream &out, double **a, Day *d, int n) {
  for (int i = 0; i < n; i++) {
    out << "Day " << i + 1 << ": " << endl;
    out << "Average Temperature: " << d[i].averageTemp << endl;
    out << "High Temperature: " << d[i].highTemp << endl;
    out << "Low Temperature: " << d[i].lowTemp << endl;
  }
}

int main() {
  double **a;
  int n;
  Day *d = new Day[n];
  fstream in, out;
  in.open("input1.3.txt", ios::in);
  getInput(in, a, n);
  in.close();
  findAverageTemp(a, d, n);
  findHighTemp(a, d, n);
  findLowTemp(a, d, n);
  out.open("output1.3.txt", ios::out);
  makeOutput(out, a, d, n);
  out.close();
  return 0;
}