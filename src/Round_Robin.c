#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"
#include "../include/process.h" // Assuming this has your Queue, Enqueue, Dequeue

void round_robin_scheduler(Scheduler* scheduler, int time_quantum) {
    printf("=== Round Robin Scheduling (Quantum: %d) ===\n", time_quantum);

    // 1. Sort processes by arrival time first (Standard setup)
    for (int i = 0; i < scheduler->processCount - 1; i++) {
        for (int j = i + 1; j < scheduler->processCount; j++) {
            if (scheduler->processes[i].arrivalTime > scheduler->processes[j].arrivalTime) {
                Process temp = scheduler->processes[i];
                scheduler->processes[i] = scheduler->processes[j];
                scheduler->processes[j] = temp;
            }
        }
    }

    // 2. Initialization
    Queue* readyQueue = createQueue();
    int currentTime = 0;
    int completedProcesses = 0;
    int index = 0; // Tracks which process from the sorted list we are considering next

    // Initialize remainingTime for all processes
    for (int i = 0; i < scheduler->processCount; i++) {
        scheduler->processes[i].remainingTime = scheduler->processes[i].executionTime;
    }

    // 3. Main Scheduler Loop
    while (completedProcesses < scheduler->processCount) {
        
        // A. Add newly arrived processes to the Queue
        // We check if processes have arrived by the current time
        while (index < scheduler->processCount && scheduler->processes[index].arrivalTime <= currentTime) {
            enqueue(readyQueue, &scheduler->processes[index]);
            index++;
        }

        // B. If Queue is empty (CPU Idle)
        if (readyQueue->head == NULL) {
            // If we still have processes left to arrive, jump time to the next arrival
            if (index < scheduler->processCount) {
                currentTime = scheduler->processes[index].arrivalTime;
            }
            continue; // Restart loop to enqueue the new process
        }

        // C. Get the next process from Queue
        Process* currentProcess = dequeue(readyQueue);

        // D. Determine execution time (Slice)
        // Run for Quantum OR run for remaining time (whichever is smaller)
        int timeSlice = time_quantum;
        if (currentProcess->remainingTime < time_quantum) {
            timeSlice = currentProcess->remainingTime;
        }

        // Set Start Time (only if it's the first time this process runs)
        if (currentProcess->remainingTime == currentProcess->executionTime) {
            currentProcess->startTime = currentTime;
        }

        printf("Executing %s from time %d to %d\n", 
               currentProcess->name, currentTime, currentTime + timeSlice);

        // E. Update Counters
        currentTime += timeSlice;
        currentProcess->remainingTime -= timeSlice;

        // F. Critical Step: Check for new arrivals AGAIN 
        // (Processes might have arrived while the CPU was busy)
        while (index < scheduler->processCount && scheduler->processes[index].arrivalTime <= currentTime) {
            enqueue(readyQueue, &scheduler->processes[index]);
            index++;
        }

        // G. Decide fate of current process
        if (currentProcess->remainingTime > 0) {
            // Process not done: Put it back at the END of the queue
            enqueue(readyQueue, currentProcess);
        } else {
            // Process done: Record finish time
            currentProcess->finishTime = currentTime;
            completedProcesses++;
            printf("-> Process %s COMPLETED at time %d\n", currentProcess->name, currentTime);
        }
    }

    // Clean up (Optional, depending on your Queue implementation)
    free(readyQueue);
}