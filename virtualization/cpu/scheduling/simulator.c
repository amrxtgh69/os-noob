#include <stdio.h>
#include "process.h"
#include "scheduler.h"


#include "algorithm/sjf.c"  

#define MAX_PROCESSES 10

Process processes[MAX_PROCESSES];
int process_count = 0; // set this before simulation

int main(void) {
    int time = 0;
    int finished = 0;
    Process* current = NULL;

    // Set up scheduler interface
    Scheduler scheduler = {
        .init = sjf_init,
        .add_process = sjf_add_process,
        .process_ticked = sjf_tick,
        .finished_process = sjf_finished
    };

    scheduler.init();

    for (int i = 0; i < process_count; i++) {
        processes[i].state = CREATED;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].completion_time = -1;
    }

    while (finished < process_count) {
        // Move arriving processes to READY and add to scheduler
        for (int i = 0; i < process_count; i++) {
            Process* p = &processes[i];
            if (p->arrival_time == time && p->state == CREATED) {
                p->state = READY;
                scheduler.add_process(p);
            }
        }

        // Scheduler decides which process runs
        current = scheduler.process_ticked(current, 1, time);

        // Execute tick and check for completion
        if (current != NULL && current->remaining_time <= 0) {
            current->completion_time = time + 1;
            scheduler.finished_process(current);
            finished++;
            current = NULL;
        }

        time++;
    }

    printf("PID\tArrival\tBurst\tStart\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < process_count; i++) {
        Process* p = &processes[i];
        int turnaround = p->completion_time - p->arrival_time;
        int waiting = turnaround - p->burst_time;
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p->pid, p->arrival_time, p->burst_time,
               p->start_time, p->completion_time, turnaround, waiting);
    }
    return 0;
}
