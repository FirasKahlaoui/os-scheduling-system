#include "../src/scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void multilevel_schedule(process_t processes[], int n, int quantum) {
    (void)quantum; 
    int current_time = 0;
    int completed = 0;
    int *aging_counters = calloc(n, sizeof(int)); 

    if (!aging_counters) {
        perror("Failed to allocate memory for aging counters");
        return;
    }

    printf("=== Multilevel Queue Scheduling (with Aging) ===\n");
    printf("Policy: 4 Priority Levels (Dynamic), Aging: +1 Priority every 10 ticks waiting\n");

    
    for(int i=0; i<n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].state = READY;
        aging_counters[i] = 0;
    }

    int last_running_idx = -1;
    int run_start_time = 0;

    while(completed < n) {
        int idx = -1;
        int highest_prio = INT_MIN; 

        
        for(int i=0; i<n; i++) {
            if(processes[i].arrival_time <= current_time && processes[i].state != TERMINATED) {
                if(processes[i].priority > highest_prio) {
                    highest_prio = processes[i].priority;
                    idx = i;
                } else if (processes[i].priority == highest_prio) {
                    
                    if (idx == -1 || processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        
        for (int i = 0; i < n; i++) {
            if (processes[i].state != TERMINATED && processes[i].arrival_time <= current_time) {
                if (i != idx) { 
                    aging_counters[i]++;
                    if (aging_counters[i] >= 10) {
                        processes[i].priority++;
                        aging_counters[i] = 0;
                        
                    }
                } else {
                    
                    aging_counters[i] = 0; 
                }
            }
        }

        
        if(idx != -1) {
            if(processes[idx].start_time == -1) processes[idx].start_time = current_time;
            
            
            if (last_running_idx != idx) {
                
                if (last_running_idx != -1) {
                    log_event(run_start_time, processes[last_running_idx].name, current_time - run_start_time);
                    if (processes[last_running_idx].state == RUNNING) {
                         processes[last_running_idx].state = READY;
                    }
                }
                
                processes[idx].state = RUNNING;
                run_start_time = current_time;
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
                
                update_visualization(processes, n, current_time, -1);
            }
        } else {
            
            if (last_running_idx != -1) {
                log_event(run_start_time, processes[last_running_idx].name, current_time - run_start_time);
                if (processes[last_running_idx].state == RUNNING) processes[last_running_idx].state = READY;
                last_running_idx = -1;
            }
            update_visualization(processes, n, current_time, -1);
            current_time++;
        }
    }
    
    
    if (last_running_idx != -1) {
        log_event(run_start_time, processes[last_running_idx].name, current_time - run_start_time);
    }
    
    free(aging_counters);
}
