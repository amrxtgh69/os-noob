/*
 * Any time a new job enters the system, it determines the remaining jobs and new jobs
 * which has the least time left, and it schedules that one.
 * imagine 
 * job A -> time needed 10
 * job B -> time needed 1
 * if scheduler run A first then B waits for 10 units: which is bad
 * if scheduler run B first then A is delayed by 1 units.
 *
 * running short job first reduces total waiting time for everyone.
 *
 * now lets suppose
 * job          time
 * A            10s
 * B            1s
 *
 * user run A(big program)
 * then run small command(B)
 * (STCF) : if B arrives runs immediately(ok?)
 * but if many small job keep coming then user might feel system is slow.
 *
 * this leads to the new metric system which is response time:
 * Response Time = first time cpu responds - arrival time
 * 
 * */
#include "../process.h"
#include <stdlib.h>

#define MAX_PROCESS 10

Process* queue[MAX_PROCESS];
int count = 0;

void stcf_init() { count = 0; }

void stcf_add_process(Process* p) {
  if (count < MAX_PROCESS) {
    queue[count++] = p;
  }
}

Process* get_shortest() {
  if (count == 0) { return NULL; }
  Process* shortest = NULL;
  
  // Get process with less remaining time
  for (int i = 0; i < count; i++) {
    Process* p = queue[i];

    if (p->remaining_time > 0) {
      if (shortest == NULL || p->remaining_time < shortest->remaining_time) {
        shortest = p;
      }
    }
  }
  return shortest;
}

Process* stcf_tick(Process* p, int tick, int global_time) {
  if (p != NULL) {
    p->remaining_time -= tick;

    if (p->remaining_time <= 0) {
      p->completion_time = global_time;
    }
  }
  // now the shortest job
  Process* next = get_shortest();

  if (next != NULL && next->start_time == -1) {
    next->start_time = global_time;
  }
  return next;
}

void stcf_finished() {
  count = 0;
}
