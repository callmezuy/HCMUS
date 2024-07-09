#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int> &a) {
  for (int i = 1; i < a.size(); i++) {
    int temp = a[i];
    int j = i - 1;
    while (j >= 0 && a[j] > temp) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = temp;
  }
}

void selectionSort(vector<int> &a) {
  for (int i = 0; i < a.size() - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < a.size(); j++) {
      if (a[j] < a[minIndex]) {
        minIndex = j;
      }
    }
    swap(a[i], a[minIndex]);
  }
}

void interchangeSort(vector<int> &a) {
  for (int i = 0; i < a.size() - 1; i++) {
    for (int j = i + 1; j < a.size(); j++) {
      if (a[i] > a[j]) {
        swap(a[i], a[j]);
      }
    }
  }
}

int main() {
  int n;
  cout << "Enter the number of elements (>= 10000): ";
  cin >> n;

  vector<int> a(n), b(n), c(n);

  srand(time(0));
  for (int i = 0; i < n; i++) {
    a[i] = rand();
    b[i] = a[i];
    c[i] = a[i];
  }

  clock_t start, end;
  start = clock();
  insertionSort(a);
  end = clock();
  double time1 = double(end - start) / CLOCKS_PER_SEC;
  cout << "Insertion Sort Time: " << time1 << " seconds" << endl;

  start = clock();
  selectionSort(b);
  end = clock();
  double time2 = double(end - start) / CLOCKS_PER_SEC;
  cout << "Selection Sort Time: " << time2 << " seconds" << endl;

  start = clock();
  interchangeSort(c);
  end = clock();
  double time3 = double(end - start) / CLOCKS_PER_SEC;
  cout << "Interchange Sort Time: " << time3 << " seconds" << endl;

  if (time1 < time2 && time1 < time3) {
    cout << "The fastest algorithm: Insertion Sort\n";
  } else if (time2 < time1 && time2 < time3) {
    cout << "The fastest algorithm: Selection Sort\n";
  } else {
    cout << "The fastest algorithm: Interchange Sort\n";
  }

  if (time1 > time2 && time1 > time3) {
    cout << "The slowest algorithm: Insertion Sort\n";
  } else if (time2 > time1 && time2 > time3) {
    cout << "The slowest algorithm: Selection Sort\n";
  } else {
    cout << "The slowest algorithm: Interchange Sort\n";
  }

  return 0;
}