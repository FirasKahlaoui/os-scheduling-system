#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include "scheduler.h"
#include "display.h"

typedef void (*schedule_func_t)(process_t[], int, int);
static schedule_func_t current_policy = NULL;
static bool visual_mode = false;

void init_scheduler(const char *policy_name) {
    if (strcasecmp(policy_name, "FIFO") == 0) {
        current_policy = fifo_schedule;
    } else if (strcasecmp(policy_name, "RoundRobin") == 0) {
        current_policy = round_robin_schedule;
    } else if (strcasecmp(policy_name, "Priority") == 0) {
        current_policy = priority_schedule;
    } else if (strcasecmp(policy_name, "Multilevel") == 0) {
        current_policy = multilevel_schedule;
    } else {
        current_policy = fifo_schedule;
    }
}

void set_visual_mode(bool enable) {
    visual_mode = enable;
    if (visual_mode) {
        init_graphical_display();
    }
}

void update_visualization(process_t processes[], int n, int current_time, int running_idx) {
    if (visual_mode) {
        update_graphical_display(processes, n, current_time, running_idx);
        usleep(200000); 
    }
}

void log_event(int time, const char *process_name, int duration) {
    if (!visual_mode) {
        printf("Executing %s from time %d to %d\n", process_name, time, time + duration);
    }
}

void execute_schedule(process_t processes[], int n, int quantum) {
    if (current_policy) {
        current_policy(processes, n, quantum);
    }
    if (visual_mode) {
        close_graphical_display();
    }
}

int compare_completion_time(const void *a, const void *b) {
    process_t *p1 = *(process_t **)a;
    process_t *p2 = *(process_t **)b;
    return p1->completion_time - p2->completion_time;
}

void display_results(process_t processes[], int n) {
    
    
    printf("\n--- Scheduling Results ---\n");
    printf("Name\tArrival\tBurst\tPrio\tStart\tEnd\tWait\tTurnaround\n");
    float avg_wait = 0, avg_turnaround = 0;
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               processes[i].name,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].start_time,
               processes[i].completion_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
        avg_wait += processes[i].waiting_time;
        avg_turnaround += processes[i].turnaround_time;
    }
    if (n > 0) {
        printf("\nAverage Waiting Time: %.2f\n", avg_wait / n);
        printf("Average Turnaround Time: %.2f\n", avg_turnaround / n);

        
        process_t **sorted_procs = malloc(n * sizeof(process_t *));
        if (sorted_procs) {
            for(int i=0; i<n; i++) sorted_procs[i] = &processes[i];
            qsort(sorted_procs, n, sizeof(process_t *), compare_completion_time);

            printf("Execution Order: ");
            for(int i=0; i<n; i++) {
                printf("%s", sorted_procs[i]->name);
                if(i < n-1) printf(" -> ");
            }
            printf("\n");
            free(sorted_procs);
        }
    }
}
