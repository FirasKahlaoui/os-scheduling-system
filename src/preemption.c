#include <stdio.h>
#include <limits.h>
#include "../include/scheduler.h"

/*
 * Preemptive Priority Scheduling
 * Lower numerical priority value = higher actual priority
 */
void priority_preemptive_scheduler(Scheduler* sched) {
    if (!sched || sched->processCount <= 0) {
        printf("Nothing to schedule.\n");
        return;
    }

    int n = sched->processCount;
    int completed = 0;
    int time = 0;

    sched->currentTime = 0;  // reset scheduler clock

    while (completed < n) {
        int highestIndex = -1;
        int bestPriority = INT_MAX;

        // Find ready process with highest priority (lowest numerical value)
        for (int i = 0; i < n; i++) {
            Process* p = &sched->processes[i];

            if (p->arrivalTime <= time && p->remainingTime > 0) {
                if (p->priority < bestPriority) {
                    bestPriority = p->priority;
                    highestIndex = i;
                }
            }
        }

        // CPU Idle
        if (highestIndex == -1) {
            time++;
            continue;
        }

        Process* current = &sched->processes[highestIndex];

        // First time the process starts
        if (current->startTime == -1)
            current->startTime = time;

        printf("Time %d: Running %s (Priority=%d, Remaining=%d)\n",
               time, current->name, current->priority, current->remainingTime);

        // Execute for 1 time unit
        current->remainingTime--;
        time++;

        // Check if finished
        if (current->remainingTime == 0) {
            current->finishTime = time;
            completed++;

            printf("Process %s finished at time %d\n",
                   current->name, current->finishTime);
        }
    }

    sched->currentTime = time;

    // Print Summary
    printf("\n=== Preemptive Priority Scheduling Summary ===\n");
    for (int i = 0; i < n; i++) {
        Process* p = &sched->processes[i];

        int turnaround = p->finishTime - p->arrivalTime;
        int waiting = turnaround - p->executionTime;
        if (waiting < 0) waiting = 0;

        printf("%s: Arrival=%d Exec=%d Priority=%d Start=%d Finish=%d Wait=%d Turnaround=%d\n",
               p->name, p->arrivalTime, p->executionTime, p->priority,
               p->startTime, p->finishTime, waiting, turnaround);
    }
}
