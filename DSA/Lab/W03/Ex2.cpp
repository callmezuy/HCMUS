#include <iostream>
#include <vector>

using namespace std;

void evenAscending(vector<int> &a, vector<bool> &flag) {
  int n = a.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (flag[i] && flag[j] && a[i] > a[j]) {
        swap(a[i], a[j]);
      }
    }
  }
}

void oddDescending(vector<int> &a, vector<bool> &flag) {
  int n = a.size();
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (!flag[i] && !flag[j] && a[i] < a[j]) {
        swap(a[i], a[j]);
      }
    }
  }
}

int main() {
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

  vector<int> a(n);
  vector<bool> flag(n);

  for (int i = 0; i < n; i++) {
    cout << "Enter element " << i + 1 << ": ";
    cin >> a[i];
    flag[i] = a[i] % 2 == 0;
  }

  evenAscending(a, flag);
  oddDescending(a, flag);

  cout << "The sorted array is: ";
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;

  return 0;
}