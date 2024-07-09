#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

void init(int **&m, int &rows, int &cols);
void print(int **m, int rows, int cols);
void free(int **&m, int rows);
void spiralSort(int **m, int rows, int cols);
void sort(int *a, int n);

int main() {
  int **m, rows, cols;
  init(m, rows, cols);
  cout << "Matrix:" << endl;
  print(m, rows, cols);
  spiralSort(m, rows, cols);
  cout << "Sorted matrix:" << endl;
  print(m, rows, cols);
  free(m, rows);
  return 0;
}

void init(int **&m, int &rows, int &cols) {
  cout << "Enter the number of rows: ";
  cin >> rows;
  cout << "Enter the number of columns: ";
  cin >> cols;
  m = new int *[rows];
  srand(time(0));
  for (int i = 0; i < rows; i++) {
    m[i] = new int[cols];
    for (int j = 0; j < cols; j++) {
      m[i][j] = rand() % 100;
    }
  }
}

void print(int **m, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << setw(5) << m[i][j] << " ";
    }
    cout << endl;
  }
}

void free(int **&m, int rows) {
  for (int i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;
}

void spiralSort(int **m, int rows, int cols) {
  int n = rows * cols;
  int *a = new int[n];
  int k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      a[k++] = m[i][j];
    }
  }

  sort(a, n);

  int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
  k = 0;

  if (cols == 1) {
    for (int i = 0; i < rows; i++) {
      m[i][0] = a[k++];
    }
    delete[] a;
    return;
  }

  if (rows == 1) {
    for (int j = 0; j < cols; j++) {
      m[0][j] = a[k++];
    }
    delete[] a;
    return;
  }

  while (k < n) {
    for (int j = left; j <= right && k < n; j++) {
      m[top][j] = a[k++];
    }
    top++;
    for (int i = top; i <= bottom && k < n; i++) {
      m[i][right] = a[k++];
    }
    right--;
    for (int j = right; j >= left && k < n; j--) {
      m[bottom][j] = a[k++];
    }
    bottom--;
    for (int i = bottom; i >= top && k < n; i--) {
      m[i][left] = a[k++];
    }
    left++;
  }

  delete[] a;
}

void sort(int *a, int n) {
  for (int i = 1; i < n; i++) {
    int key = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = key;
  }
}