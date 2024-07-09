#include "queue.h"
#include "recursive_queue.h"

int main() {
  Queue<int> q;
  cout << "Enter the size of the queue: ";
  int size;
  cin >> size;
  q.init(size);

  int choice;
  do {
    cout << "[1]. Enqueue\n[2]. Dequeue\n[3]. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;
    switch (choice) {
      case 1:
        cout << "Enter value: ";
        int item;
        cin >> item;
        q.enqueue(item);
        q.print();
        break;
      case 2:
        if (!q.isEmpty()) {
          int item = q.dequeue();
          cout << "Dequeued item: " << item << endl;
          q.print();
        } else {
          cout << "Queue is empty! Can't dequeue.\n";
        }
        break;
      case 3:
        q.release();
        break;
      default:
        cout << "Invalid choice!\n";
    }
    cout << "------------------------------------\n";
  } while (choice != 3);

  // RecursiveQueue<int> rq;
  // cout << "Enter the size of the queue: ";
  // int size;
  // cin >> size;
  // rq.init(size);

  // int choice;
  // do {
  //   cout << "[1]. Enqueue\n[2]. Dequeue\n[3]. Exit\n";
  //   cout << "Enter choice: ";
  //   cin >> choice;
  //   switch (choice) {
  //     case 1:
  //       cout << "Enter value: ";
  //       int item;
  //       cin >> item;
  //       rq.enqueue(item);
  //       rq.print();
  //       break;
  //     case 2:
  //       if (!rq.isEmpty()) {
  //         int item = rq.dequeue();
  //         cout << "Dequeued item: " << item << endl;
  //         rq.print();
  //       } else {
  //         cout << "Queue is empty! Can't dequeue.\n";
  //       }
  //       break;
  //     case 3:
  //       rq.release();
  //       break;
  //     default:
  //       cout << "Invalid choice!\n";
  //   }
  //   cout << "------------------------------------\n";
  // } while (choice != 3);

  return 0;
}