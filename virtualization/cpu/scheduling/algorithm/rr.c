#include "../process.h"
#include <stddef.h>

#define MAX_PROCESS 10
#define QUANTUM 2

static int time_used = 0;

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

void rr_init() {
  front = 0;
  rear = 0;
  count = 0;
}

void rr_add_process(Process* p) {
  enqueue(p);
}

Process* rr_tick(Process* p, int tick, int global_time) {
  if (p == NULL) {
    p = dequeue();
    time_used = 0;
  }

  if (p == NULL) return NULL;
  p->remaining_time--;
  time_used++;

  if (p->remaining_time == 0) {
    time_used = 0;
    return NULL;
  }
  if (time_used >= QUANTUM) {
    enqueue(p);
    time_used = 0;
    return NULL;
  }
  return p;
}

void rr_finished(Process* p) {
  // NO ACTION
}
