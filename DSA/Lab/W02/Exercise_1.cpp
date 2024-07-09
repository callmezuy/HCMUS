#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void getInput(fstream &in, int *&a, int &n);
void makeOutput(fstream &out, int *a, int n);
int linearSearch(int *a, int n, int key);
int linearSearchWithSentinel(int *a, int n, int key);
void sort(int *&a, int *&pos, int n);
int binarySearch(int *a, int *pos, int n, int key);

int main(int argc, char *argv[]) {
  if (argc != 5) {
    cout << "Invalid arguments" << endl;
    return 1;
  }

  int option = stoi(argv[1]);
  int key = stoi(argv[2]);

  string infile = argv[3];
  string outfile = argv[4];

  fstream in, out;
  in.open(infile, ios::in);
  out.open(outfile, ios::out);

  int *a, n;
  getInput(in, a, n);

  int result;

  switch (option) {
    case 1:
      result = linearSearch(a, n, key);
      break;
    case 2:
      result = linearSearchWithSentinel(a, n, key);
      break;
    case 3: {
      int *pos = new int[n];
      for (int i = 0; i < n; i++) {
        pos[i] = i;
      }
      sort(a, pos, n);
      result = binarySearch(a, pos, n, key);
      break;
    }
    default:
      cout << "Invalid option" << endl;
      return 1;
  }

  out << result;

  in.close();
  out.close();

  delete[] a;
  return 0;
}

void getInput(fstream &in, int *&a, int &n) {
  in >> n;
  a = new int[n];
  for (int i = 0; i < n; i++) {
    in >> a[i];
  }
}

void makeOutput(fstream &out, int *a, int n) {
  for (int i = 0; i < n; i++) {
    out << a[i] << " ";
  }
  out << endl;
}

int linearSearch(int *a, int n, int key) {
  for (int i = 0; i < n; i++) {
    if (a[i] == key) return i;
  }
  return -1;
}

int linearSearchWithSentinel(int *a, int n, int key) {
  int last = a[n - 1];
  a[n - 1] = key;
  int i = 0;
  while (a[i] != key) i++;
  a[n - 1] = last;
  if (i < n - 1 || a[n - 1] == key) return i;
  return -1;
}

void sort(int *&a, int *&pos, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (a[i] > a[j]) {
        swap(a[i], a[j]);
        swap(pos[i], pos[j]);
      }
    }
  }
}

int binarySearch(int *a, int *pos, int n, int key) {
  int left = 0, right = n - 1;
  while (left <= right) {
    int mid = (right + left) / 2;
    if (a[mid] == key) return pos[mid];
    if (a[mid] < key)
      left = mid + 1;
    else
      right = mid - 1;
  }
  return -1;
}
