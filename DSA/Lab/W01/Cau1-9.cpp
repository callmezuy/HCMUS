#include <stdint.h>
#include <stdio.h>

#include <cstring>
#include <iostream>

#define MAX 100

using namespace std;

struct Birthdate {
  uint32_t day;
  uint32_t month;
  uint32_t year;
};

struct Student {
  char *fullname;
  Birthdate birthdate;
  char *address;
  char *className;
  char *ID;
};

struct sizeInfo {
  uint32_t size_name;
  uint32_t size_address;
  uint32_t size_className;
  uint32_t size_ID;
};

void getInfo(Student &student, sizeInfo &size);
void writeToFile(FILE *f, Student student, sizeInfo size);
void release(Student &student);
void menu();

int main() {
  FILE *f = fopen("output1.9.bin", "wb");
  if (f == NULL) {
    cout << "Cannot open file" << endl;
    return 1;
  }

  Student student;
  sizeInfo size;
  int choice;
  do {
    menu();
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
      case 1:
        getInfo(student, size);
        writeToFile(f, student, size);
        release(student);
        break;
      case 2:
        fclose(f);
        return 0;
      default:
        cout << "Invalid choice" << endl;
        break;
    }
  } while (choice != 2);
  return 0;
}

void getInfo(Student &student, sizeInfo &size) {
  cout << "Enter full name: ";
  student.fullname = new char[MAX];
  cin.getline(student.fullname, MAX);
  size.size_name = strlen(student.fullname);

  cout << "Enter birthdate (dd mm yyyy): ";
  cin >> student.birthdate.day;
  cin >> student.birthdate.month;
  cin >> student.birthdate.year;

  cout << "Enter address: ";
  student.address = new char[MAX];
  cin.ignore();
  cin.getline(student.address, MAX);
  size.size_address = strlen(student.address);

  cout << "Enter class: ";
  student.className = new char[MAX];
  cin.getline(student.className, MAX);
  size.size_className = strlen(student.className);

  cout << "Enter student ID: ";
  student.ID = new char[MAX];
  cin.getline(student.ID, MAX);
  size.size_ID = strlen(student.ID);
}

void writeToFile(FILE *f, Student student, sizeInfo size) {
  fwrite(&size.size_name, sizeof(uint32_t), 1, f);
  fwrite(student.fullname, sizeof(char), size.size_name, f);

  fwrite(&student.birthdate, sizeof(Birthdate), 1, f);

  fwrite(&size.size_address, sizeof(uint32_t), 1, f);
  fwrite(student.address, sizeof(char), size.size_address, f);

  fwrite(&size.size_className, sizeof(uint32_t), 1, f);
  fwrite(student.className, sizeof(char), size.size_className, f);

  fwrite(&size.size_ID, sizeof(uint32_t), 1, f);
  fwrite(student.ID, sizeof(char), size.size_ID, f);
}

void release(Student &student) {
  delete[] student.fullname;
  delete[] student.address;
  delete[] student.className;
  delete[] student.ID;
}

void menu() {
  cout << "1. Enter student information" << endl;
  cout << "2. Exit" << endl;
}