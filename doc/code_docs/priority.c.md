# Documentation: priority.c

## Overview
`priority.c` implements **Preemptive Priority Scheduling**. It ensures that critical tasks are executed as soon as possible.

## Algorithm Logic
1.  **Selection**: At every time tick, the scheduler scans all available processes (`arrival <= current_time`).
2.  **Comparison**: It selects the process with the **highest priority value**.
3.  **Preemption**: Because the check happens at every tick, if a new process arrives with a higher priority than the currently running one, the current process is immediately paused (context switch).
4.  **Starvation Risk**: Unlike Multilevel, this basic implementation does *not* include aging, so low-priority processes may starve if high-priority ones keep arriving.

## Implementation Details
- Similar structure to Multilevel but without the aging loop.
- Finds `idx` of the highest priority process.
- Executes for 1 tick, then repeats the selection process.

## Functions
- `void priority_schedule(process_t processes[], int n, int quantum)`: Executes the Priority logic.
