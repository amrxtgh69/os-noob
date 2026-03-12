#ifndef PROC_H
#define PROC_H

#define NPROC 64 // number of processes

enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE}; // STATE OF THE PROCESS 

// to caputure the snapshot of the process's cpu state at the particular time
struct context {
  int eip;
  int esp;
  int ebx, ecx, edx, esi, edi, ebp;
};

struct proc {
  int pid;
  struct proc *parent;
  struct context context;
  char *kstack;
  enum procstate state;
  void *pgdir;
  int exit_status;
  void *program;
};

//extern means the actual memory for these is represented in proc.c
extern struct proc ptable[NPROC];
extern int nextpid;;
extern struct proc* current_proc;

extern struct proc* allocproc(void);

extern struct proc* vfork(struct proc *parent);
extern struct proc* exec(struct proc *p, void *program);
extern struct proc* wait(struct proc *parent, int *status);
#endif // !PROC_H
