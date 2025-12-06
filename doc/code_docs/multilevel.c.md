# Documentation: multilevel.c

## Overview

`multilevel.c` implements a **Preemptive Multilevel Queue Scheduling** algorithm with **Aging**. This is the most complex policy in the project, designed to balance system responsiveness with fairness.

## Algorithm Logic

### 1. Priority Queues

The system conceptually maintains multiple priority levels (though implemented as a single array with a `priority` attribute).

- **Selection Rule**: At any time `t`, the scheduler selects the process with the **highest priority** that has arrived (`arrival_time <= t`).
- **Tie-Breaking**: If multiple processes have the same highest priority, **FIFO** (First-In-First-Out) is used based on arrival time.

### 2. Preemption

The scheduler checks for the highest priority process **at every time tick**.

- If a new process arrives with a higher priority than the currently running one, the current process is preempted (paused), and the new one takes over immediately.

### 3. Aging Mechanism (Starvation Prevention)

To prevent low-priority processes from waiting indefinitely (starvation):

- **Tracking**: An `aging_counters` array tracks how long each process has been waiting in the READY state.
- **Rule**: For every **10 ticks** a process waits, its priority is incremented by **+1**.
- **Reset**: When a process starts running, its aging counter is reset to 0.

### 4. Execution Loop

The `multilevel_schedule` function runs a simulation loop:

1. **Select**: Find the highest priority ready process.
2. **Age**: Update counters for all other waiting processes.
3. **Run**: Execute the selected process for 1 tick.
4. **Log**: If the running process changes (Context Switch), log the event.
5. **Update**: Decrement remaining time; if 0, mark as TERMINATED.

## Functions

- `void multilevel_schedule(process_t processes[], int n, int quantum)`: The main entry point for this policy.
