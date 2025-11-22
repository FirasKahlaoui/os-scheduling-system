#include <stdio.h>
#include "../include/scheduler.h" // Include the main scheduler header to access Scheduler and Process

// FIFO Scheduler
void fifo_scheduler(Scheduler* scheduler) {
    printf("=== FIFO Scheduling ===\n");
    
    // Sort processes by arrival time only once
    for (int i = 0; i < scheduler->processCount - 1; i++) {
        for (int j = i + 1; j < scheduler->processCount; j++) {
            if (scheduler->processes[i].arrivalTime > scheduler->processes[j].arrivalTime) {
                Process temp = scheduler->processes[i];
                scheduler->processes[i] = scheduler->processes[j];
                scheduler->processes[j] = temp;
            }
        }
    }

    // Execute processes in the sorted order
    int currentTime = 0;
    for (int i = 0; i < scheduler->processCount; i++) {
        // Wait for the process to arrive if necessary
        if (currentTime < scheduler->processes[i].arrivalTime) {
            currentTime = scheduler->processes[i].arrivalTime;
        }
        
        // Execute the process
        scheduler->processes[i].startTime = currentTime;
        currentTime += scheduler->processes[i].executionTime;
        scheduler->processes[i].finishTime = currentTime;
        
        printf("Executing %s from time %d to %d\n", 
               scheduler->processes[i].name, 
               scheduler->processes[i].startTime, 
               scheduler->processes[i].finishTime);
    }
}
