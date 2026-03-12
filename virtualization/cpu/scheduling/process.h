#if !defined(PROCESS_H)
#define PROCESS_H

// the state of the process
typedef enum { CREATED, READY, RUNNING, BLOCKED, TERMINATED } State;

// the attribute of the process
typedef struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
    State state;
} Process;


#endif // PROCESS_H


