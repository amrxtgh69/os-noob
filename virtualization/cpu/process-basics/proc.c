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
  p->parent = current_proc; // set parent if this is very first process(init) 
                           // `current_proc` might be NULL
  
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
  p->context.eip = (int)start_process; //sets the instruction pointer to the 
                                       //function where the process should
                                       //start executing
  p->context.esp = (int)(p->kstack + 4096); //sets the stack pointer to the top
                                            //of the allocated stack

  p->state = RUNNABLE;


  return p;
}


int main(int argc, char *argv[])
{
  return 0;
}
