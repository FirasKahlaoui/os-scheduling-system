#ifndef PROCESS_H
#define PROCESS_H

typedef enum {
    READY,
    RUNNING,
    WAITING,
    TERMINATED
} process_state_t;

typedef struct {
    char name[32];
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int start_time;
    int queue_level;
    process_state_t state;
} process_t;

void init_process(process_t *p, const char *name, int arrival, int burst, int priority);
void print_process(const process_t *p);

#endif
