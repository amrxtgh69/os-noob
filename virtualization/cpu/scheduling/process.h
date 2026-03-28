#if !defined(PROCESS_H)
#define PROCESS_H

// the state of the process
typedef enum { CREATED, READY, RUNNING, BLOCKED, TERMINATED } State;

// the attribute of the process
typedef struct Process {
    int pid;              // The unique id of the process
    int arrival_time;
    int burst_time;       // The total amount of CPU time a process need to complete its execution.
    int remaining_time;   // How much CPU time still needed for a process to complete its execution
                          // This decreases as the process executed: at the start remaining_time = burst_time.
    int start_time;       // It is the exact time(tick) when a process first gets CPU time. 
    int completion_time;  // Tick when process finishes execution
    State state;
} Process;


#endif // PROCESS_H


