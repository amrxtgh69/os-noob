/*
Process's burst time is already known using the various algorithms 
*/
#include "../process.h"
#include "../scheduler.h"
#include <stdlib.h>

#define MAX_PROCESS 10

Process* queue[MAX_PROCESS];
int front = 0;
int rear = 0;
int count = 0; //count the number of the process in the queue

void enqueue(Process *p) {
    if (count == MAX_PROCESS) { return; }
    queue[rear] = p;
    rear = (rear + 1) % MAX_PROCESS; //circular buffer
    count++; 
}

Process* dequeue() {
    if (count == 0) { return NULL; }
    Process* p = queue[front];
    front = (front + 1) % MAX_PROCESS; // use circular buffer thats why study dsa
    count --;
    return p;
}
int empty() { return count == 0; }


void scheduler_add_process(Process* p) {
    enqueue(p);
}