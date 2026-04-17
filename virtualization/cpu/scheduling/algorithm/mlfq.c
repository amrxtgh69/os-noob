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

void enqueue(Queue *q, Process *p) {
  if (q->count == MAX) {
    return;
  }
  q->rear = (q->rear + 1) % MAX;

  q->arr[q->rear] = p;
  q->count++;
}

Process* dequeue(Queue *q) {
  if (q->count == 0) {
    return 0;
  }
  Process *p = q->arr[q->front];
  q->front = (q->front + 1) % MAX;
  q->count--;
  return p;
}

void mlfq_add_process(Process* p) {
  enqueue(&mlfq[0], p);
}

Process* mlfq_tick(Process* current, int tick, int global_time) {
  return current;
}

void mlfq_finished(Process* p) {
  p->state = TERMINATED;
}
