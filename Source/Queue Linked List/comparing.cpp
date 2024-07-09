#include <chrono>

#include "queue.h"
#include "recursive_queue.h"

using namespace std::chrono;

#define MAX 10000

int main() {
  Queue<int> q;
  q.init();

  RecursiveQueue<int> rq;
  rq.init();

  for (int i = 0; i < MAX; i++) {
    q.enqueue(i);
    rq.enqueue(i);
  }

  // Queue<int> q1;
  // q1.init();
  // q1.copyQueue(q);
  // q1.print();

  // RecursiveQueue<int> rq1;
  // rq1.init();
  // rq1.copyQueue(rq);
  // rq1.print();
  
  // q1.release();
  // rq1.release();

  int attempts = 1000;
  auto time_copy1 = 0, time_copy2 = 0;
  auto time_release1 = 0, time_release2 = 0;

  for (int i = 0; i < attempts; i++) {
    Queue<int> q1;
    q1.init();

    auto start = high_resolution_clock::now();
    q1.copyQueue(q);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time_copy1 += duration.count();

    start = high_resolution_clock::now();
    q1.release();
    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);
    time_release1 += duration.count();
  }

  for (int i = 0; i < attempts; i++) {
    RecursiveQueue<int> rq1;
    rq1.init();

    auto start = high_resolution_clock::now();
    rq1.copyQueue(rq);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    time_copy2 += duration.count();

    start = high_resolution_clock::now();
    rq1.release();
    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);
    time_release2 += duration.count();
  }

  cout << "Time taken to copy a queue of " << MAX << " elements:\n";
  cout << "Loop version: " << time_copy1 / attempts << " microseconds\n";
  cout << "Recursive version: " << time_copy2 / attempts << " microseconds\n";

  cout << "\nTime taken to release a queue of " << MAX << " elements:\n";
  cout << "Loop version: " << time_release1 / attempts << " microseconds\n";
  cout << "Recursive version: " << time_release2 / attempts
       << " microseconds\n";

  q.release();
  rq.release();

  return 0;
}