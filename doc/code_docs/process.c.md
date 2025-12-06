# Documentation: process.c

## Overview
`process.c` defines the fundamental unit of the simulation: the **Process**. It handles the initialization and state management of individual process entities.

## Data Structure
The `process_t` structure (defined in `process.h`) contains:
- `name`: Identifier (e.g., "P1").
- `arrival_time`, `burst_time`, `priority`: Static attributes from config.
- `remaining_time`: Dynamic counter for execution.
- `state`: Current status (READY, RUNNING, WAITING, TERMINATED).
- `waiting_time`, `turnaround_time`: Metrics calculated at the end.

## Functions
- `void init_process(...)`: Constructor-like function to populate a `process_t` struct.
- `void print_process(...)`: Helper to dump process state to console (useful for debugging).
