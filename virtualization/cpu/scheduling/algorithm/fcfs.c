/*
Implementation of the First IN, First OUT(FIFO) (most simple algorithm)

lets say 3 jobs arrive at the scheduling system:
A, B and C
the Tarrival = 0

both arrived at the same time in the scheduler within the splitsecond
lets say each jobs run for 10 sec A -> 10 , B -> 20 and C -> 30 

Executing order: A -> B -> C

Now the avg turn-around time for this job is:
(10+(20+10)+(30+20+10)) / 3 = 100/3 = 33.3 

If the long job arrives before the short ones all the short jobs must wait
  A = 100
  B = 20 
  C = 10
short jobs suffer from the long wait because the scheduler doesnot preempt.

this problem is generally referred as the CONVOY effect.
*/

#include "../process.h"
#include "../scheduler.h"


/* 
What is FIFO queue ?
-> data structure that follows the first come first serve
Order in which the process arrives is the order in which they are executed
*/

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