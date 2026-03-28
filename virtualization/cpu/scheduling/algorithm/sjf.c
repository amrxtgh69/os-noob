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
#include "../scheduler.h"
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

/*
 * Remaining time: In the context of operating systems, remaining time (or residual time) 
 * refers to the amount of CPU time a process still requires to complete its execution. 
 * It is a critical metric used by the CPU scheduler to decide which task should run next.
*/
Process* get_shortest_job() {
    if (count == 0) { return NULL; }
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
    
    int next = (shortest_index + 1) % MAX_PROCESS;
    
    return shortest;
}
int empty() { return count == 0; }


void scheduler_add_process(Process* p) {
    enqueue(p);
}