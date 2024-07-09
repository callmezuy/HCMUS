#include <chrono>

#include "recursive_stack.h"
#include "stack.h"

using namespace std::chrono;

#define MAX 10000

int main() {
  Stack<int> stack;
  stack.init();

  RecursiveStack<int> recursiveStack;
  recursiveStack.init();

  for (int i = 0; i < MAX; i++) {
    stack.push(i);
    recursiveStack.push(i);
  }

  // Stack<int> stack1;
  // stack1.init();

  // stack1.copyStack(stack);
  // stack1.print();

  // RecursiveStack<int> recursiveStack1;
  // recursiveStack1.init();

  // recursiveStack1.copyStack(recursiveStack);
  // recursiveStack1.print();

  // stack1.release();
  // recursiveStack1.release();

  int attempts = 1000;
  auto time_copy1 = 0, time_copy2 = 0;
  auto time_release1 = 0, time_release2 = 0;

  for (int i = 0; i < attempts; i++) {
    Stack<int> stack1;
    stack1.init();

    auto start = high_resolution_clock::now();
    stack1.copyStack(stack);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time_copy1 += duration.count();

    start = high_resolution_clock::now();
    stack1.release();
    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);
    time_release1 += duration.count();
  }

  for (int i = 0; i < attempts; i++) {
    RecursiveStack<int> stack1;
    stack1.init();

    auto start = high_resolution_clock::now();
    stack1.copyStack(recursiveStack);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time_copy2 += duration.count();

    start = high_resolution_clock::now();
    stack1.release();
    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);
    time_release2 += duration.count();
  }

  cout << "Time taken to copy stack of " << MAX << " elements:\n";
  cout << "Loop version: " << time_copy1 / attempts << " microseconds\n";
  cout << "Recursive version: " << time_copy2 / attempts << " microseconds\n";

  cout << "\nTime taken to release stack of " << MAX << " elements:\n";
  cout << "Loop version: " << time_release1 / attempts << " microseconds\n";
  cout << "Recursive version: " << time_release2 / attempts
       << " microseconds\n";

  stack.release();
  recursiveStack.release();

  return 0;
}