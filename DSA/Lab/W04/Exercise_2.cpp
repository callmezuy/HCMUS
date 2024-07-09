#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

void init(int *&a, int &n);
void print(int *a, int n);
void countingSort(int *a, int n);
void radixSort(int *a, int n);

int main() {
  int *a;
  int n;
  init(a, n);
  int *b = new int[n];
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
  }

  high_resolution_clock::time_point start, end;
  start = high_resolution_clock::now();
  countingSort(b, n);
  end = high_resolution_clock::now();

  duration<double> countingTime = duration_cast<duration<double>>(end - start);
  cout << "Counting Sort: " << countingTime.count() << " seconds" << endl;

  start = high_resolution_clock::now();
  radixSort(a, n);
  end = high_resolution_clock::now();

  duration<double> radixTime = duration_cast<duration<double>>(end - start);
  cout << "Radix Sort: " << radixTime.count() << " seconds" << endl;

  if (radixTime.count() < countingTime.count()) {
    cout << "The faster algorithm: Radix Sort" << endl;
    cout << "The slower algorithm: Counting Sort" << endl;
  } else {
    cout << "The faster algorithm: Counting Sort" << endl;
    cout << "The slower algorithm: Radix Sort" << endl;
  }

  // print(a, n);
  // print(b, n);

  delete[] a;
  delete[] b;

  return 0;
}

void init(int *&a, int &n) {
  cout << "Enter the number of elements (>=100000): ";
  cin >> n;
  a = new int[n];
  srand(time(0));
  for (int i = 0; i < n; i++) {
    a[i] = rand();
  }
}

void print(int *a, int n) {
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

void countingSort(int *a, int n) {
  int max = a[0];
  for (int i = 1; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }

  int *count = new int[max + 1];
  for (int i = 0; i <= max; i++) {
    count[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    count[a[i]]++;
  }

  int index = 0;
  for (int i = 0; i <= max; i++) {
    while (count[i] > 0) {
      a[index++] = i;
      count[i]--;
    }
  }

  delete[] count;
}

void radixSort(int *a, int n) {
  int max = a[0];
  for (int i = 1; i < n; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }

  for (int exp = 1; max / exp > 0; exp *= 10) {
    int *output = new int[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++) count[(a[i] / exp) % 10]++;

    for (i = 1; i < 10; i++) count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
      output[count[(a[i] / exp) % 10] - 1] = a[i];
      count[(a[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++) a[i] = output[i];

    delete[] output;
  }
}
