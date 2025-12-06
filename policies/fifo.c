#include "../src/scheduler.h"
#include <stdio.h>

void fifo_schedule(process_t processes[], int n, int quantum) {
    (void)quantum;
    int current_time = 0;
    
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                process_t temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    if (!n) return;

    printf("=== FIFO Scheduling ===\n");

    for (int i = 0; i < n; i++) {
        
        while (current_time < processes[i].arrival_time) {
            update_visualization(processes, n, current_time, -1);
            current_time++;
        }
        
        processes[i].start_time = current_time;
        processes[i].waiting_time = processes[i].start_time - processes[i].arrival_time;
        processes[i].state = RUNNING;

        log_event(current_time, processes[i].name, processes[i].burst_time);

        
        for (int t = 0; t < processes[i].burst_time; t++) {
            update_visualization(processes, n, current_time, i);
            processes[i].remaining_time--;
            current_time++;
        }

        processes[i].completion_time = current_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].state = TERMINATED;
        update_visualization(processes, n, current_time, -1);
    }
}
