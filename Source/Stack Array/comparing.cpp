#include <chrono>

#include "recursive_stack.h"
#include "stack.h"

using namespace std::chrono;

#define MAX 10000

int main() {
  Stack<int> stack;
  stack.init(MAX);

  RecursiveStack<int> recursiveStack;
  recursiveStack.init(MAX);

  for (int i = 0; i < MAX; i++) {
    stack.push(i);
    recursiveStack.push(i);
  }

  // Stack<int> stack1;
  // stack1.init(MAX);

  // stack1.copyStack(stack);
  // stack1.print();

  // RecursiveStack<int> recursiveStack1;
  // recursiveStack1.init(MAX);
  
  // recursiveStack1.copyStack(recursiveStack);
  // recursiveStack1.print(recursiveStack1.top);

  // stack1.release();
  // recursiveStack1.release();

  cout << "Time taken to copy stack of " << MAX << " elements:\n";

  int attempts = 1000;
  auto time = 0;

  for (int i = 0; i < attempts; i++) {
    Stack<int> stack1;
    stack1.init(MAX);

    auto start = high_resolution_clock::now();
    stack1.copyStack(stack);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time += duration.count();

    stack1.release();
  }

  cout << "Loop version: " << time / attempts << " microseconds\n";

  time = 0;

  for (int i = 0; i < attempts; i++) {
    RecursiveStack<int> stack1;
    stack1.init(MAX);

    auto start = high_resolution_clock::now();
    stack1.copyStack(recursiveStack);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time += duration.count();

    stack1.release();
  }

  cout << "Recursive version: " << time / attempts << " microseconds\n";

  stack.release();
  recursiveStack.release();

  return 0;
}