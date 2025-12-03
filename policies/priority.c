#include "../src/scheduler.h"
#include <stdio.h>
#include <limits.h>

void priority_schedule(process_t processes[], int n, int quantum) {
    (void)quantum;
    int current_time = 0;
    int completed = 0;
    
    printf("=== Preemptive Priority Scheduling ===\n");

    for(int i=0; i<n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].state = READY;
    }

    int last_running_idx = -1;

    while(completed < n) {
        int idx = -1;
        int highest_prio = -1; 

        for(int i=0; i<n; i++) {
            if(processes[i].arrival_time <= current_time && processes[i].state != TERMINATED) {
                if(processes[i].priority > highest_prio) {
                    highest_prio = processes[i].priority;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            if(processes[idx].start_time == -1) processes[idx].start_time = current_time;
            
            if (last_running_idx != idx) {
                
                if (last_running_idx != -1 && processes[last_running_idx].state == RUNNING) {
                     processes[last_running_idx].state = READY;
                }
                processes[idx].state = RUNNING;
                log_event(current_time, processes[idx].name, 1); 
                last_running_idx = idx;
            }

            update_visualization(processes, n, current_time, idx);
            processes[idx].remaining_time--;
            current_time++;
            
            if(processes[idx].remaining_time == 0) {
                processes[idx].state = TERMINATED;
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                completed++;
                last_running_idx = -1;
            }
        } else {
            update_visualization(processes, n, current_time, -1);
            current_time++;
        }
    }
}
