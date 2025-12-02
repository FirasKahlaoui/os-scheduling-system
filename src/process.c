#include <stdio.h>
#include <string.h>
#include "process.h"

void init_process(process_t *p, const char *name, int arrival, int burst, int priority) {
    strncpy(p->name, name, sizeof(p->name) - 1);
    p->name[sizeof(p->name) - 1] = '\0';
    p->arrival_time = arrival;
    p->burst_time = burst;
    p->priority = priority;
    p->remaining_time = burst;
    p->waiting_time = 0;
    p->turnaround_time = 0;
    p->completion_time = 0;
    p->start_time = -1;
    p->queue_level = 0;
    p->state = READY;
}

void print_process(const process_t *p) {
    printf("Process %s: Arrival=%d, Burst=%d, Priority=%d, State=%d\n",
           p->name, p->arrival_time, p->burst_time, p->priority, p->state);
}
