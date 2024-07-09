#include <chrono>

#include "queue.h"
#include "recursive_queue.h"

using namespace std::chrono;

#define MAX 10000

int main() {
  Queue<int> q;
  q.init(MAX);

  RecursiveQueue<int> rq;
  rq.init(MAX);

  for (int i = 0; i < MAX; i++) {
    q.enqueue(i);
    rq.enqueue(i);
  }

  // Queue<int> q1;
  // q1.init(MAX);

  // q1.copyQueue(q);
  // q1.print();

  // RecursiveQueue<int> rq1;
  // rq1.init(MAX);

  // rq1.copyQueue(rq);
  // rq1.print();

  // q1.release();
  // rq1.release();

  int attempts = 1000;
  auto time = 0;

  cout << "Time taken to copy a queue of " << MAX << " elements:\n";

  for (int i = 0; i < attempts; i++) {
    Queue<int> q1;
    q1.init(MAX);

    auto start = high_resolution_clock::now();
    q1.copyQueue(q);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time += duration.count();

    q1.release();
  }

  cout << "Loop version: " << time / attempts << " microseconds\n";

  time = 0;

  for (int i = 0; i < attempts; i++) {
    RecursiveQueue<int> rq1;
    rq1.init(MAX);

    auto start = high_resolution_clock::now();
    rq1.copyQueue(rq);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time += duration.count();

    rq1.release();
  }

  cout << "Recursive version: " << time / attempts << " microseconds\n";

  q.release();
  rq.release();

  return 0;
}