#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

/* Round-Robin scheduler implementation moved to its own file */
void round_robin_scheduler(Scheduler* sched, int time_quantum) {
    if (sched == NULL || sched->processCount <= 0 || time_quantum <= 0) {
        printf("Nothing to schedule or invalid quantum\n");
        return;
    }

    int n = sched->processCount;
    int *remaining = malloc(sizeof(int) * n);
    int *original = malloc(sizeof(int) * n);
    int *completion = malloc(sizeof(int) * n);
    int *waiting = malloc(sizeof(int) * n);
    int *turnaround = malloc(sizeof(int) * n);
    int *in_queue = malloc(sizeof(int) * n);
    if (!remaining || !original || !completion || !waiting || !turnaround || !in_queue) {
        perror("malloc");
        exit(1);
    }

    for (int i = 0; i < n; ++i) {
        remaining[i] = sched->processes[i].executionTime;
        original[i] = sched->processes[i].executionTime;
        completion[i] = 0;
        waiting[i] = 0;
        turnaround[i] = 0;
        in_queue[i] = 0;
    }

    int qcap = n * 4 + 10;
    int *queue = malloc(sizeof(int) * qcap);
    int qhead = 0, qtail = 0;
    if (!queue) { perror("malloc"); exit(1); }

    int completed = 0;
    int time = 0;

    for (int i = 0; i < n; ++i) {
        if (sched->processes[i].arrivalTime <= time && remaining[i] > 0 && !in_queue[i]) {
            queue[qtail++] = i;
            if (qtail >= qcap) qtail = 0;
            in_queue[i] = 1;
        }
    }

    while (completed < n) {
        if (qhead == qtail) {
            int nextArrival = -1;
            for (int i = 0; i < n; ++i) {
                if (remaining[i] > 0) {
                    if (nextArrival == -1 || sched->processes[i].arrivalTime < nextArrival) {
                        nextArrival = sched->processes[i].arrivalTime;
                    }
                }
            }
            if (nextArrival == -1) break;
            time = (nextArrival > time) ? nextArrival : time;
            for (int i = 0; i < n; ++i) {
                if (sched->processes[i].arrivalTime <= time && remaining[i] > 0 && !in_queue[i]) {
                    queue[qtail++] = i;
                    if (qtail >= qcap) qtail = 0;
                    in_queue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[qhead++];
        if (qhead >= qcap) qhead = 0;
        in_queue[idx] = 0;

        int run = (remaining[idx] < time_quantum) ? remaining[idx] : time_quantum;
        printf("Time %d -> %d : Process %s ran for %d (remaining before run: %d)\n",
               time, time + run,
               sched->processes[idx].name,
               run,
               remaining[idx]);

        time += run;
        remaining[idx] -= run;

        for (int i = 0; i < n; ++i) {
            if (sched->processes[i].arrivalTime <= time && remaining[i] > 0 && !in_queue[i]) {
                queue[qtail++] = i;
                if (qtail >= qcap) qtail = 0;
                in_queue[i] = 1;
            }
        }

        if (remaining[idx] > 0) {
            queue[qtail++] = idx;
            if (qtail >= qcap) qtail = 0;
            in_queue[idx] = 1;
        } else {
            completed++;
            completion[idx] = time;
            turnaround[idx] = completion[idx] - sched->processes[idx].arrivalTime;
            waiting[idx] = turnaround[idx] - original[idx];
            if (waiting[idx] < 0) waiting[idx] = 0;
            printf("Process %s finished at time %d\n", sched->processes[idx].name, completion[idx]);
        }
    }

    double total_wait = 0.0;
    double total_turn = 0.0;
    printf("\nRound-Robin Scheduling (quantum=%d) summary:\n", time_quantum);
    for (int i = 0; i < n; ++i) {
        printf("  %s: Arrival=%d, Execution=%d, Completion=%d, Turnaround=%d, Waiting=%d\n",
               sched->processes[i].name,
               sched->processes[i].arrivalTime,
               original[i],
               completion[i],
               turnaround[i],
               waiting[i]);
        total_wait += waiting[i];
        total_turn += turnaround[i];
    }
    printf("Average waiting time: %.2f\n", total_wait / n);
    printf("Average turnaround time: %.2f\n", total_turn / n);

    free(remaining);
    free(original);
    free(completion);
    free(waiting);
    free(turnaround);
    free(in_queue);
    free(queue);
}