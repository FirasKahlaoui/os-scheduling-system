#include "../src/scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void round_robin_schedule(process_t processes[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;
    
    printf("=== Round-Robin Scheduling (Quantum %d) ===\n", quantum);

    for(int i=0; i<n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].start_time = -1;
        processes[i].state = READY;
    }

    while(completed < n) {
        bool progress = false;
        for(int i=0; i<n; i++) {
            if(processes[i].state != TERMINATED && processes[i].arrival_time <= current_time) {
                progress = true;
                if(processes[i].start_time == -1) processes[i].start_time = current_time;
                
                processes[i].state = RUNNING;
                int time_slice = (processes[i].remaining_time > quantum) ? quantum : processes[i].remaining_time;
                
                log_event(current_time, processes[i].name, time_slice);

                for(int t=0; t<time_slice; t++) {
                    update_visualization(processes, n, current_time, i);
                    processes[i].remaining_time--;
                    current_time++;
                }

                if(processes[i].remaining_time == 0) {
                    processes[i].waiting_time = current_time - processes[i].burst_time - processes[i].arrival_time;
                    processes[i].completion_time = current_time;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].state = TERMINATED;
                    completed++;
                } else {
                    processes[i].state = READY;
                }
                update_visualization(processes, n, current_time, -1);
            }
        }
        if(!progress) {
            update_visualization(processes, n, current_time, -1);
            current_time++;
        }
    }
}
