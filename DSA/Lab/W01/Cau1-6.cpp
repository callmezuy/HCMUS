#include <iostream>

using namespace std;

struct Stack {
  char* array;
  int top;
  int size;
};

void init(Stack& stack, int& n);
bool isEmpty(Stack stack);
bool isFull(Stack stack);
void push(Stack& stack, char& data);
void pop(Stack& stack);
void printStack(Stack stack);
void menu();

int main() {
  Stack stack;
  int choice;
  int size;
  char data;
  do {
    menu();
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
      case 1:
        init(stack, size);
        break;
      case 2:
        push(stack, data);
        break;
      case 3:
        pop(stack);
        break;
      case 4:
        printStack(stack);
        break;
      case 5:
        break;
      default:
        cout << "Invalid choice." << endl;
        break;
    }
  } while (choice != 5);
  delete[] stack.array;
  return 0;
}

void init(Stack& stack, int& n) {
  cout << "Enter size of stack: ";
  cin >> n;
  stack.array = new char[n];
  stack.top = -1;
  stack.size = n;
}

bool isEmpty(Stack stack) { return stack.top == -1; }

bool isFull(Stack stack) { return stack.top == stack.size - 1; }

void push(Stack& stack, char& data) {
  if (isFull(stack)) {
    cout << "Stack is full! Cannot push." << endl;
    return;
  }
  cout << "Enter data: ";
  cin >> data;
  stack.top++;
  stack.array[stack.top] = data;
}

void pop(Stack& stack) {
  if (isEmpty(stack)) {
    cout << "Stack is empty! Cannot pop." << endl;
    return;
  }
  stack.top--;
}

void printStack(Stack stack) {
  if (isEmpty(stack)) {
    cout << "Stack is empty." << endl;
    return;
  }
  cout << "Stack: ";
  for (int i = 0; i <= stack.top; i++) {
    cout << stack.array[i];
  }
  cout << endl;
}

void menu() {
  cout << "1. Initialize stack" << endl;
  cout << "2. Push" << endl;
  cout << "3. Pop" << endl;
  cout << "4. Print stack" << endl;
  cout << "5. Exit" << endl;
}