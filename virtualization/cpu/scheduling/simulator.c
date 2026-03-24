#include <stdio.h>
#include "process.h"
#include "scheduler.h"

#define MAX_PROCESSES 10

Process processes[MAX_PROCESSES];
int process_count;


Process* get_ready_process() {
    for (int i = 0; i < process_count; i++) {
        Process *p = &processes[i];
        if (p->state == READY) { return p; }   
    }
    return NULL;
}

int main(void) {
    int time = 0;
    int finished = 0;
    Process* current = NULL;
    scheduler_init();
    
    while (finished < process_count) {
      /* Move the arriving processes to READY */
      for (int i = 0; i < process_count; i++) {
        Process *p = &processes[i];
        if (p->arrival_time == time && p->state == CREATED) {
          p->state = READY;
        }
      }
      /* Call the get_ready_process */
      Process *ready = get_ready_process();
      if (ready != NULL) { scheduler_add_process(ready); }
      /* Scheduler decides that run this tick */
      current = scheduler_process_ticked(current, 1, time);
      /* Execute tick */
      if (current != NULL) { 
        current->remaining_time--;

        /* Check if the process finished */
        if (current->remaining_time <= 0) {
          scheduler_finished_process(current);
          current = NULL;
        }
      }
      time++;
    } 
}
