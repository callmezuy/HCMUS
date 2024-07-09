#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

void getInput(fstream &in, int **&m, int &row, int &col) {
  in >> row >> col;
  m = new int *[row];
  for (int i = 0; i < row; i++) {
    m[i] = new int[row];
    for (int j = 0; j < col; j++) {
      in >> m[i][j];
    }
  }
}

void sort(int **m, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      int min = m[i][j];
      int minIndex = j;
      for (int k = i + 1; k < row; k++) {
        for (int l = 0; l < col; l++) {
          if (k - i == l - j && m[k][l] < min) {
            min = m[k][l];
            minIndex = l;
          }
        }
      }
      if (minIndex != j) {
        int temp = m[i][j];
        m[i][j] = m[i + minIndex - j][minIndex];
        m[i + minIndex - j][minIndex] = temp;
      }
    }
  }
}

int main() {
  fstream in("input_2.txt", ios::in);
  if (!in) {
    cout << "Cannot open the input file" << endl;
    return 1;
  }
  fstream out("output_2.txt", ios::out);
  if (!out) {
    cout << "Cannot open the output file" << endl;
    return 1;
  }

  int **m;
  int row, col;
  getInput(in, m, row, col);
  sort(m, row, col);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      out << m[i][j] << " ";
    }
    out << endl;
  }
  return 0;
}
