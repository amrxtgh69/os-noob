#include "../process.h"

#define MAX 10
#define LEVELS 3

typedef struct {
  Process* arr[MAX];
  int front;
  int rear;
  int count;
} Queue;

Queue mlfq[LEVELS];

void mlfq_init(void) {
  for (int i = 0; i < LEVELS; i++) {
    mlfq[i].front = 0;
    mlfq[i].rear = -1;
    mlfq[i].count = 0;
  }
}

void mlfq_add_process(Process* p) {
  // Add to highest priority queue (Q0)
  if (mlfq[0].count < MAX) {
    mlfq[0].arr[++mlfq[0].rear % MAX] = p;
    mlfq[0].count++;
  }
}

Process* mlfq_tick(Process* current, int tick, int global_time) {
  return current;
}

void mlfq_finished(Process* p) {
  p->state = TERMINATED;
}
