/*
 * Shortest Job First(SJF) scheduling - Non preemptive
 * - The scheduler selects the process with the smallest remaining_time
 *  ONLY when the CPU becomes idle.
 
 * - Once the process starts execution, it is not preempted.
 * It runs until completion.
 * 
 * - The ready queue is scanned to find the shortest job.
*/
#include "../process.h"
#include <stdlib.h>

#define MAX_PROCESS 10

Process* queue[MAX_PROCESS];
int front = 0;
int rear = 0;
int count = 0; //count the number of the process in the queue

/*
 * in sjf enqueue means just add the process no matter where unlike fcfs
*/
void enqueue(Process *p) {
    if (count == MAX_PROCESS) { return; }
    queue[rear] = p;
    rear = (rear + 1) % MAX_PROCESS; //circular buffer
    count++; 
}

int empty() { return count == 0; }
/*
 * Remaining time: In the context of operating systems, remaining time (or residual time) 
 * refers to the amount of CPU time a process still requires to complete its execution. 
 * It is a critical metric used by the CPU scheduler to decide which task should run next.
*/
void clear_gap(int idx) {
  int next = (idx + 1) % MAX_PROCESS;
  while (next != (front + count) % MAX_PROCESS) {
    queue[idx] = queue[next];
    idx = next;
    next = (next + 1) % MAX_PROCESS;
  }
  count--;
  rear = (rear - 1 + MAX_PROCESS) % MAX_PROCESS;
}

Process* get_shortest_job() {
    if (empty()) { return NULL; }
    int shortest_index = front;
    int idx = front;

    /* Getting the index of the shortest job*/
    for (int i = 0; i < count; i++) {
        if (queue[idx]->remaining_time < queue[shortest_index]-> remaining_time) {
            shortest_index = idx;
        }
        idx = (idx + 1) % MAX_PROCESS;
    }
    /* extract that process */
    Process* shortest = queue[shortest_index];

    clear_gap(shortest_index);
    return shortest;
}

void sjf_init() {
  front = 0;
  rear = 0;
  count = 0;
}

void sjf_add_process(Process* p) {
    enqueue(p);
}

Process* sjf_tick(Process* p, int tick, int global_time) {
    if (p == NULL) return get_shortest_job();

    // Decrease remaining time
    p->remaining_time -= tick;

    if (p->remaining_time <= 0) return get_shortest_job();

    return p; // keep running same process
}

void sjf_finished(Process* p) {
    p->state = TERMINATED;;
}
