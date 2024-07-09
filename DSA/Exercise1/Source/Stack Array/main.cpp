#include <ctime>

#include "recursive_stack.h"
#include "stack.h"

int main() {
  Stack<int> stack;
  cout << "Enter the size of the stack: ";
  int size;
  cin >> size;
  stack.init(size);

  int choice = 0;
  do {
    cout << "[1] Push\n[2] Pop\n[3] Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
      case 1:
        int value;
        cout << "Enter value: ";
        cin >> value;

        stack.push(value);
        stack.print();
        break;
      case 2:
        if (!stack.isEmpty()) {
          int poppedValue = stack.pop();
          cout << "Popped value: " << poppedValue << endl;
          stack.print();
        } else {
          cout << "Stack is empty! Can't pop!" << endl;
        }
        break;
      case 3:
        stack.release();
        break;
      default:
        cout << "Invalid choice!\n";
        break;
    }
    cout << "------------------------------------\n";
  } while (choice != 3);

  // recursion ver

  // RecursiveStack<int> recursiveStack;
  // cout << "Enter the size of the stack: ";
  // int size;
  // cin >> size;
  // recursiveStack.init(size);

  // int choice = 0;
  // do {
  //   cout << "[1] Push\n[2] Pop\n[3] Exit\n";
  //   cout << "Enter choice: ";
  //   cin >> choice;

  //   switch (choice) {
  //     case 1:
  //       int value;
  //       cout << "Enter value: ";
  //       cin >> value;

  //       recursiveStack.push(value);
  //       recursiveStack.print(recursiveStack.top);
  //       break;
  //     case 2:
  //       if (!recursiveStack.isEmpty()) {
  //         int poppedValue = recursiveStack.pop();
  //         cout << "Popped value: " << poppedValue << endl;
  //         recursiveStack.print(recursiveStack.top);
  //       } else {
  //         cout << "Stack is empty! Can't pop!" << endl;
  //       }
  //       break;
  //     case 3:
  //       recursiveStack.release();
  //       break;
  //     default:
  //       cout << "Invalid choice!\n";
  //       break;
  //   }
  //   cout << "------------------------------------\n";
  // } while (choice != 3);

  return 0;
}