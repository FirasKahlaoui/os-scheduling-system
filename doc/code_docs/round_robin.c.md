# Documentation: round_robin.c

## Overview
`round_robin.c` implements the **Round-Robin (RR)** scheduling algorithm. This is a preemptive policy designed for time-sharing systems, ensuring that no single process monopolizes the CPU.

## Algorithm Logic
1.  **Time Quantum**: Each process is given a fixed slice of time (`quantum`) to execute.
2.  **Circular Queue**: Processes are treated as a circular queue. The scheduler picks the next available process that has arrived.
3.  **Preemption**:
    - If a process finishes within its quantum, it terminates.
    - If it exceeds the quantum, it is paused (preempted), and the scheduler moves to the next process in the queue.
4.  **Cycle**: The loop continues until all processes are `TERMINATED`.

## Implementation Details
- Uses a `while(completed < n)` loop.
- Iterates through the process array `i = (i + 1) % n` to simulate the circular queue.
- Checks if `processes[i]` is ready (`arrival <= current_time` and `remaining > 0`).
- Runs for `min(quantum, remaining_time)`.
- Updates `current_time` and visualization after each slice.

## Functions
- `void round_robin_schedule(process_t processes[], int n, int quantum)`: Executes the RR logic.
