# Documentation: fifo.c

## Overview
`fifo.c` implements the **First-In-First-Out (FIFO)** scheduling algorithm, also known as First-Come-First-Served (FCFS). It is the simplest non-preemptive scheduling policy.

## Algorithm Logic
1.  **Sorting**: The processes are conceptually sorted by their `arrival_time`.
2.  **Non-Preemptive**: Once a process starts execution, it runs until its `burst_time` is fully consumed. No other process can interrupt it.
3.  **Idle Time**: If no process has arrived by the current time, the CPU remains idle until the next arrival.

## Implementation Details
- The function iterates through the process list.
- It tracks `current_time`.
- If `current_time < process.arrival_time`, it jumps (idles) to the arrival time.
- It runs the process to completion in one go, updating `start_time`, `completion_time`, etc.
- Calls `update_visualization` periodically to animate the progress bar in the UI.

## Functions
- `void fifo_schedule(process_t processes[], int n, int quantum)`: Executes the FIFO logic. (Note: `quantum` is ignored in this policy).
