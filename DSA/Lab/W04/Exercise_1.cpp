#include <ctime>
#include <iostream>

using namespace std;

void init(int *&a, int &n);
void print(int *a, int n);
void heapSort(int *a, int n);
void heapify(int *a, int n, int i);
void quickSort(int *a, int first, int last);
void mergeSort(int *a, int l, int r);
void merge(int *a, int l, int m, int r);

int main() {
  int *a;
  int n;
  init(a, n);
  int *b = new int[n];
  int *c = new int[n];
  for (int i = 0; i < n; i++) {
    b[i] = a[i];
    c[i] = a[i];
  }

  clock_t start, end;
  start = clock();
  heapSort(a, n);
  end = clock();
  double heapTime = (double)(end - start) / CLOCKS_PER_SEC;
  cout << "Heap Sort: " << heapTime << " seconds" << endl;

  start = clock();
  quickSort(b, 0, n - 1);
  end = clock();
  double quickTime = (double)(end - start) / CLOCKS_PER_SEC;
  cout << "Quick Sort: " << quickTime << " seconds" << endl;

  start = clock();
  mergeSort(c, 0, n - 1);
  end = clock();
  double mergeTime = (double)(end - start) / CLOCKS_PER_SEC;
  cout << "Merge Sort: " << mergeTime << " seconds" << endl;

  if (heapTime < quickTime && heapTime < mergeTime) {
    cout << "The fastest algorithm: Heap Sort" << endl;
  } else if (quickTime < heapTime && quickTime < mergeTime) {
    cout << "The fastest algorithm: Quick Sort" << endl;
  } else {
    cout << "The fastest algorithm: Merge Sort" << endl;
  }

  if (heapTime > quickTime && heapTime > mergeTime) {
    cout << "The slowest algorithm: Heap Sort" << endl;
  } else if (quickTime > heapTime && quickTime > mergeTime) {
    cout << "The slowest algorithm: Quick Sort" << endl;
  } else {
    cout << "The slowest algorithm: Merge Sort" << endl;
  }

  delete[] a;
  delete[] b;
  delete[] c;

  return 0;
}

void init(int *&a, int &n) {
  cout << "Enter the number of elements (>= 100000): ";
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

void heapSort(int *a, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(a, n, i);
  }
  for (int i = n - 1; i >= 0; i--) {
    swap(a[0], a[i]);
    heapify(a, i, 0);
  }
}

void heapify(int *a, int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  if (l < n && a[l] > a[largest]) {
    largest = l;
  }
  if (r < n && a[r] > a[largest]) {
    largest = r;
  }
  if (largest != i) {
    swap(a[i], a[largest]);
    heapify(a, n, largest);
  }
}

void quickSort(int *a, int first, int last) {
  int i = first;
  int j = last;
  int pivot = a[(first + last) / 2];
  while (i <= j) {
    while (a[i] < pivot) {
      i++;
    }
    while (a[j] > pivot) {
      j--;
    }
    if (i <= j) {
      swap(a[i], a[j]);
      i++;
      j--;
    }
  }
  if (first < j) {
    quickSort(a, first, j);
  }
  if (i < last) {
    quickSort(a, i, last);
  }
}

void mergeSort(int *a, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    merge(a, l, m, r);
  }
}

void merge(int *a, int l, int m, int r) {
  int n1 = m - l + 1;
  int n2 = r - m;
  int *L = new int[n1];
  int *R = new int[n2];
  for (int i = 0; i < n1; i++) {
    L[i] = a[l + i];
  }
  for (int i = 0; i < n2; i++) {
    R[i] = a[m + 1 + i];
  }
  int i = 0;
  int j = 0;
  int k = l;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      a[k] = L[i];
      i++;
    } else {
      a[k] = R[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    a[k] = L[i];
    i++;
    k++;
  }
  while (j < n2) {
    a[k] = R[j];
    j++;
    k++;
  }

  delete[] L;
  delete[] R;
}
