#if !defined(SCHEDULAR_H)
#define SCHEDULAR_H
#include "process.h"

/* init scheduler at the simulation start */ 
void scheduler_init();
/* add a process to scheduler when it becomes READY */ 
void scheduler_add_process(Process* p);
/* Update scheduler state after the process ran for tick_elapsed */ 
Process* scheduler_process_ticked(Process* p, int tick_elapsed, int global_time);
/* cleanup or the keeping of the state when the process finished */ 
void scheduler_finished_process(Process* p);

#endif // SCHEDULAR_H


