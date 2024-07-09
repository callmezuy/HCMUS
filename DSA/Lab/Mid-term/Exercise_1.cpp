#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void getInput(fstream &in, int *&a, int &n, int &x) {
  in >> n >> x;
  a = new int[n];
  for (int i = 0; i < n; i++) {
    in >> a[i];
  }
}

int main() {
  fstream in("input_1.txt", ios::in);
  if (!in) {
    cout << "Cannot open the input file" << endl;
    return 1;
  }
  fstream out("output_1.txt", ios::out);
  if (!out) {
    cout << "Cannot open the output file" << endl;
    return 1;
  }
  int n, x;
  int *a;
  getInput(in, a, n, x);
  int *p1 = new int[n];
  int *p2 = new int[n];
  int *multiple = new int[n];
  int k = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i] + a[j] == x) {
        p1[k] = a[i];
        p2[k] = a[j];
        multiple[k] = a[i] * a[j];
        k++;
      }
    }
  }
  int max = multiple[0];
  for (int i = 1; i < k; i++) {
    if (multiple[i] > max) {
      max = multiple[i];
    }
  }
  if (k == 0) {
    out << "-1";
    return 0;
  }
  for (int i = 0; i < k; i++) {
    if (multiple[i] == max) {
      out << p1[i] << " " << p2[i];
      break;
    }
  }

  return 0;
}
