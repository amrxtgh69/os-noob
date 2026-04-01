#include "../process.h"

#define MAX_PROCESS 10

Process* queue[MAX_PROCESS];
int count = 0;

void rr_init() {}

void rr_add_process(Process* p) {}

Process* rr_tick(Process* p, int tick, int global_time) {}

void rr_finished(Process* p) {

}
