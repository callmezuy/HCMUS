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

void readFromFile(FILE *f, Student &student, sizeInfo &size);
void printInfo(Student student, sizeInfo size);
void release(Student &student);

int main() {
  FILE *f = fopen("output1.9.bin", "rb");
  if (f == NULL) {
    cout << "Cannot open file" << endl;
    return 1;
  }
  Student student;
  sizeInfo size;
  readFromFile(f, student, size);
  fclose(f);
  return 0;
}

void readFromFile(FILE *f, Student &student, sizeInfo &size) {
  fseek(f, 0, SEEK_SET);
  while (fread(&size.size_name, sizeof(uint32_t), 1, f) == 1) {
    student.fullname = new char[size.size_name + 1];
    fread(student.fullname, sizeof(char), size.size_name, f);
    student.fullname[size.size_name] = '\0';  // Add null terminator

    fread(&student.birthdate, sizeof(Birthdate), 1, f);

    fread(&size.size_address, sizeof(uint32_t), 1, f);
    student.address = new char[size.size_address + 1];
    fread(student.address, sizeof(char), size.size_address, f);
    student.address[size.size_address] = '\0';

    fread(&size.size_className, sizeof(uint32_t), 1, f);
    student.className = new char[size.size_className + 1];
    fread(student.className, sizeof(char), size.size_className, f);
    student.className[size.size_className] = '\0';

    fread(&size.size_ID, sizeof(uint32_t), 1, f);
    student.ID = new char[size.size_ID + 1];
    fread(student.ID, sizeof(char), size.size_ID, f);
    student.ID[size.size_ID] = '\0';

    printInfo(student, size);
    release(student);
  }
}

void printInfo(Student student, sizeInfo size) {
  cout << "Full name: " << student.fullname << endl;
  cout << "Birthdate: " << student.birthdate.day << "/"
       << student.birthdate.month << "/" << student.birthdate.year << endl;
  cout << "Address: " << student.address << endl;
  cout << "Class: " << student.className << endl;
  cout << "Student ID: " << student.ID << endl;
  cout << "--------------------------------" << endl;
}

void release(Student &student) {
  delete[] student.fullname;
  delete[] student.address;
  delete[] student.className;
  delete[] student.ID;
}