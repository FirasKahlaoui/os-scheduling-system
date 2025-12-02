#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef struct{         //creates a structes that holds all the information needed for the simulation
    Process* processes; // pointer to the array of processes that are declared in config_examples 
    int processCount;   // number of processes
    int currentTime;   
} Scheduler;

Scheduler* load_processes_from_file(const char* filename);
void fifo_scheduler(Scheduler* scheduler);
void round_robin_scheduler(Scheduler* sched, int time_quantum);
void priority_preemptive_scheduler(Scheduler* scheduler);

#endif
