#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

struct Employee {
  string id;
  string name;
  int birth;
};

void getInput(fstream &in, Employee *&e, int &n);
bool isFront(Employee e1, Employee e2);
void insertionSort(Employee *e, int n);
void selectionSort(Employee *e, int n);
void interchangeSort(Employee *e, int n);
void makeOutput(fstream &out, Employee *e, int n);
void menu();

int main() {
  fstream in("employee.txt", ios::in);
  if (!in) {
    cout << "Cannot open the input file." << endl;
    return 1;
  }
  fstream out;

  Employee *e;
  int n = 0;

  getInput(in, e, n);
  in.close();
  int choice;

  do {
    menu();
    cin >> choice;
    switch (choice) {
      case 1:
        insertionSort(e, n);
        makeOutput(out, e, n);
        break;
      case 2:
        selectionSort(e, n);
        makeOutput(out, e, n);
        break;
      case 3:
        interchangeSort(e, n);
        makeOutput(out, e, n);
        break;
      case 4:
        break;
      default:
        cout << "Invalid choice. Please try again." << endl;
    }
    cout << "------------------------------------------" << endl;
  } while (choice != 4);

  delete[] e;

  return 0;
}

void getInput(fstream &in, Employee *&e, int &n) {
  string line;
  getline(in, line);
  while (getline(in, line)) {
    n++;
  }

  in.clear();
  in.seekg(0, ios::beg);

  e = new Employee[n];

  time_t now = time(0);
  tm *ltm = localtime(&now);
  int currentYear = 1900 + ltm->tm_year;

  getline(in, line);

  for (int i = 0; i < n; i++) {
    getline(in, e[i].id, ',');
    getline(in, e[i].name, ',');
    in >> e[i].birth;
    in.ignore(100, '\n');
    if (e[i].birth > currentYear) {
      int temp = e[i].birth % 100;
      if (temp <= currentYear - 2000) {
        e[i].birth = 2000 + temp;
      } else {
        e[i].birth = 1900 + temp;
      }
    }
  }
}

bool isFront(Employee e1, Employee e2) {
  if (e1.birth < e2.birth) {
    return true;
  } else if (e1.birth == e2.birth) {
    if (e1.name < e2.name) {
      return true;
    }
  }
  return false;
}

void insertionSort(Employee *e, int n) {
  for (int i = 1; i < n; i++) {
    Employee key = e[i];
    int j = i - 1;
    while (j >= 0 && isFront(key, e[j])) {
      e[j + 1] = e[j];
      j--;
    }
    e[j + 1] = key;
  }
}

void selectionSort(Employee *e, int n) {
  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < n; j++) {
      if (isFront(e[j], e[minIndex])) {
        minIndex = j;
      }
    }
    Employee temp = e[i];
    e[i] = e[minIndex];
    e[minIndex] = temp;
  }
}

void interchangeSort(Employee *e, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (isFront(e[j], e[i])) {
        Employee temp = e[i];
        e[i] = e[j];
        e[j] = temp;
      }
    }
  }
}

void makeOutput(fstream &out, Employee *e, int n) {
  out.open("sortedemponage.txt", ios::out);
  if (!out) {
    cout << "Cannot open the output file." << endl;
    return;
  }

  for (int i = 0; i < n; i++) {
    out << e[i].id << "," << e[i].name << "," << e[i].birth << endl;
  }

  out.close();
}

void menu() {
  cout << "1. Insertion sort" << endl;
  cout << "2. Selection sort" << endl;
  cout << "3. Interchange sort" << endl;
  cout << "4. Exit" << endl;
  cout << "Enter your choice: ";
}