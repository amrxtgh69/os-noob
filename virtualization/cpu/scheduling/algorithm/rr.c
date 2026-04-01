#include "../process.h"
#include <stddef.h>

#define MAX_PROCESS 10

Process* queue[MAX_PROCESS];
int count = 0;
int rear = 0;
int front = 0;

void enqueue(Process* p) {
  if (count == MAX_PROCESS) { return; }
  queue[rear] = p;
  rear = (rear + 1) % MAX_PROCESS;
  count++;
}

Process* dequeue() {
  if (count == 0) {
    return NULL;
  }
  Process* p = queue[front];
  front = (front + 1) % MAX_PROCESS;
  count--;
  return p;
}

void rr_init() {}

void rr_add_process(Process* p) {}

Process* rr_tick(Process* p, int tick, int global_time) {}

void rr_finished(Process* p) {

}
