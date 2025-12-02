#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <config_file>\n", argv[0]);
        return 1;
    }

    Scheduler* scheduler = load_processes_from_file(argv[1]);

    if (scheduler == NULL) {
        printf("Failed to load %s\n", argv[1]);
        return 1;
    }

    printf("Successfully loaded %d processes\n", scheduler->processCount);
    for (int i = 0; i < scheduler->processCount; i++) {
        printf("  Process %d: %s (Arrive at: %d, Eexecution_time: %d, Priority: %d)\n",
               i + 1,
               scheduler->processes[i].name,
               scheduler->processes[i].arrivalTime,
               scheduler->processes[i].executionTime,
               scheduler->processes[i].priority);
    }

    // Menu to choose algorithm
    printf("\nChoose scheduling algorithm:\n");
    printf("  1) FIFO (First-In-First-Out)\n");
    printf("  2) Round-Robin\n");
    printf("Enter choice (1 or 2): ");

    int choice = 0;
    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid input\n");
        /* fall through to cleanup below */
    } else if (choice == 1) {
        fifo_scheduler(scheduler);
    } else if (choice == 2) {
        printf("Enter time quantum (positive integer): ");
        int quantum = 0;
        if (scanf("%d", &quantum) != 1 || quantum <= 0) {
            fprintf(stderr, "Invalid quantum\n");
        } else {
            round_robin_scheduler(scheduler, quantum);
        }
    } else {
        fprintf(stderr, "Unknown choice\n");
    }

    /* proper cleanup: free each process name, the array, then the Scheduler */
    for (int i = 0; i < scheduler->processCount; ++i) {
        free(scheduler->processes[i].name);
    }
    free(scheduler->processes);
    free(scheduler);

    return 0;
}