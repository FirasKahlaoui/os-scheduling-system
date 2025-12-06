# Documentation: scheduler.h

## Overview
Source file for the scheduler project.

## Functions & Structures
The following prototypes are defined:

- `void init_scheduler(const char *policy_name);`
- `void execute_schedule(process_t processes[], int n, int quantum);`
- `void display_results(process_t processes[], int n);`
- `void set_visual_mode(bool enable);`
- `void update_visualization(process_t processes[], int n, int current_time, int running_idx);`
- `void log_event(int time, const char *process_name, int duration);`
- `void fifo_schedule(process_t processes[], int n, int quantum);`
- `void round_robin_schedule(process_t processes[], int n, int quantum);`
- `void priority_schedule(process_t processes[], int n, int quantum);`
- `void multilevel_schedule(process_t processes[], int n, int quantum);`
