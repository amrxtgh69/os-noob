#include "proc.h"
#include "proc.c"
#include <stdio.h>

int main(void) {

  printf("test\n");

  struct proc *p1 = allocproc();

  if (!p1) {
    printf("allocproc failed\n");
    return 1;
  }

  printf("Process 1: pid=%d, state=%d\n", p1->pid, p1->state);

  struct proc *child = vfork(p1);
  if (!child) {
    printf("vfork failed\n");
    return 1;
  }
  printf("Child process: pid=%d, state=%d\n", child->pid, child->state);  
}
