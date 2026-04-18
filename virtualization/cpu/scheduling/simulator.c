#include <stdio.h>
#include "process.h"
#include "scheduler.h"

#include "algorithm/fcfs.c"  

#define MAX_PROCESSES 10

Process processes[MAX_PROCESSES];
int process_count = 3;

void setup_test_processes(void) {
    processes[0].pid = 1; processes[0].arrival_time = 0; processes[0].burst_time = 100;
    processes[1].pid = 2; processes[1].arrival_time = 0; processes[1].burst_time = 10;
    processes[2].pid = 3; processes[2].arrival_time = 0; processes[2].burst_time = 10;
}

int main(void) {
    setup_test_processes();
    int global_time = 0;
    int finished = 0;
    Process* current = NULL;

    Scheduler scheduler = {
        .init = fcfs_init,
        .add_process = fcfs_add_process,
        .process_ticked = fcfs_tick,
        .finished_process = fcfs_finished
    };

    scheduler.init();

    for (int i = 0; i < process_count; i++) {
        processes[i].state = CREATED;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].completion_time = -1;
    }

    while (finished < process_count) {
        for (int i = 0; i < process_count; i++) {
            Process* p = &processes[i];
            if (p->arrival_time == global_time && p->state == CREATED) {
                p->state = READY;
                scheduler.add_process(p);
            }
        }

        current = scheduler.process_ticked(current, 1, global_time);

        if (current != NULL) {
            current->remaining_time--;
        }

        if (current != NULL && current->remaining_time <= 0) {
            current->completion_time = global_time + 1;
            scheduler.finished_process(current);
            finished++;
            current = NULL;
        }

        global_time++;
    }

    int total_turnaround = 0;
    printf("PID\tArrival\tBurst\tStart\tCompletion\tTurnaround\n");
    for (int i = 0; i < process_count; i++) {
        Process* p = &processes[i];
        int turnaround = p->completion_time - p->arrival_time;
        total_turnaround += turnaround;
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n",
               p->pid, p->arrival_time, p->burst_time,
               p->start_time, p->completion_time, turnaround);
    }

    double avg_turnaround = (double)total_turnaround / process_count;
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround);

    return 0;
}
