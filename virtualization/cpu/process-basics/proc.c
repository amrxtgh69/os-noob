#include <stdlib.h>
#include <string.h>
#include "proc.h"


struct proc ptable[NPROC];
int nextpid = 1;
struct proc* current_proc = 0;

// creating the process state in the table
struct proc* allocproc(void) {
  struct proc* p = 0; //null pointer 
  
  for (int i = 0; i < NPROC; i++) {
    if (ptable[i].state == UNUSED) {
      p = &ptable[i];
      break;
    }
  }
  if (!p) { return 0; } //if no free slots then return null pointer
  
  p->state = EMBRYO; //marks as EMBRYO
  p->pid = nextpid++; // assign pid
  p->parent = current_proc; // set parent if this is very first process(init) `current_proc` might be NULL
  
  // allocate kernel stack
  // allocated 4 KB of memory for the stack
  p->kstack = (char*)malloc(4096);
  // if allocation failed then we rollback by marking the process 
  // as UNUSED again and return null
  if (!p->kstack) {
    p->state = UNUSED;
    return 0;
  }
  memset(&p->context, 0, sizeof(p->context));
  p->context.eip = (int)start_process; //sets the instruction pointer to the function where the process should start executing
  p->context.esp = (long)(p->kstack + 4096); //sets the stack pointer to the top of the allocated stack
  p->state = RUNNABLE;
  return p;
}

struct proc* vfork(struct proc *parent) {
  // Allocate thenew process
  struct proc *child = allocproc();
  if (!child)  return NULL;  // allocation failed
  // Copy context (CPU registers)
  memcpy(&child->context, &parent->context, sizeof(struct context));
  //child ko parent parent
  child->parent = parent;

  child->program = parent->program;
  child->state = RUNNABLE;
  // child is runnabke
  return child;
}
struct proc* vexec(struct proc *p, void *program) {
  if (!p) return NULL;

  //reset CPU context
  p->context.esp = (long)(p->kstack + 4096);

  //setting instruction pointer to the program entry
  p->context.eip = (long)program;

  //making sure process is runnable
  p->state = RUNNABLE;
  return p;
}
struct proc* vwait(struct proc *parent, int *status) {}
void start_process(void) {}

int main(int argc, char *argv[])
{
  return 0;
}
