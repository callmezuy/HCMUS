#include <iostream>

using namespace std;

struct Queue {
  int* array;
  int size;
  int head;
  int tail;
};

void init(Queue& queue, int& n);
bool isEmpty(Queue queue);
bool isFull(Queue queue);
void enqueue(Queue& queue, int& data);
void dequeue(Queue& queue);
void printQueue(Queue queue);
void menu();

int main() {
  Queue queue;
  int n;
  int choice;
  int data;
  do {
    menu();
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
      case 1:
        init(queue, n);
        break;
      case 2:
        enqueue(queue, data);
        break;
      case 3:
        dequeue(queue);
        break;
      case 4:
        printQueue(queue);
        break;
      case 5:
        break;
      default:
        cout << "Invalid choice." << endl;
        break;
    }
  } while (choice != 5);
  delete[] queue.array;
  return 0;
}

void init(Queue& queue, int& n) {
  cout << "Enter the size of the queue: ";
  cin >> n;
  queue.array = new int[n];
  queue.head = -1;
  queue.tail = -1;
  queue.size = n;
}

bool isEmpty(Queue queue) { return queue.head == -1; }

bool isFull(Queue queue) {
  return queue.tail == queue.size - 1 && queue.head == 0;
}

void enqueue(Queue& queue, int& data) {
  if (isFull(queue)) {
    cout << "Queue is full! Cannot enqueue." << endl;
    return;
  }
  cout << "Enter the data: ";
  cin >> data;
  if (isEmpty(queue)) {
    queue.head = 0;
  }
  queue.tail++;
  queue.array[queue.tail] = data;
}

void dequeue(Queue& queue) {
  if (isEmpty(queue)) {
    cout << "Queue is empty! Cannot dequeue." << endl;
    return;
  }
  if (queue.head == queue.tail) {
    queue.head = -1;
    queue.tail = -1;
    return;
  }
  queue.head++;
}

void printQueue(Queue queue) {
  if (isEmpty(queue)) {
    cout << "Queue is empty!" << endl;
    return;
  }
  cout << "Queue: ";
  for (int i = queue.head; i <= queue.tail; i++) {
    cout << queue.array[i] << " ";
  }
  cout << endl;
}

void menu() {
  cout << "1. Initialize the queue." << endl;
  cout << "2. Enqueue." << endl;
  cout << "3. Dequeue." << endl;
  cout << "4. Print the queue." << endl;
  cout << "5. Exit." << endl;
}
