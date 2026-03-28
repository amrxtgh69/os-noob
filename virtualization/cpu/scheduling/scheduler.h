#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef void (*SchedulerInitFn)(void);
typedef void (*SchedulerAddFn)(Process*);
typedef Process* (*SchedulerTickFn)(Process*, int, int);
typedef void (*SchedulerFinishedFn)(Process*);

typedef struct Scheduler {
    SchedulerInitFn init;
    SchedulerAddFn add_process;
    SchedulerTickFn process_ticked;
    SchedulerFinishedFn finished_process;
} Scheduler;

#endif
