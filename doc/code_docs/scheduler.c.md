# Documentation: scheduler.c

## Overview
`scheduler.c` is the core engine of the application. It manages the lifecycle of the simulation, handles the selection of the active scheduling policy, and coordinates between the logic layer and the visualization layer. It also calculates and displays the final performance metrics.

## Key Functionality

### 1. Policy Management (Strategy Pattern)
The scheduler uses a function pointer `current_policy` to switch between different algorithms dynamically.
- `init_scheduler(const char *policy_name)`: Sets `current_policy` to point to the requested function (e.g., `fifo_schedule`, `multilevel_schedule`).

### 2. Visualization & Logging
- **Visual Mode**: If enabled, `update_visualization` is called every tick to refresh the Ncurses UI. It introduces a small delay (`usleep`) to make the animation visible.
- **Text Logging**: If visual mode is off, `log_event` prints execution intervals (e.g., "Executing P1 from time 0 to 3") to the console.

### 3. Metrics Calculation
After the simulation completes, `display_results` calculates:
- **Turnaround Time**: Completion Time - Arrival Time.
- **Waiting Time**: Turnaround Time - Burst Time.
- **Averages**: Computes the mean waiting and turnaround times for the batch.
- **Execution Order**: Sorts processes by completion time to print the final sequence (e.g., P1 -> P2 -> P3).

## Functions
- `void init_scheduler(const char *policy_name)`: Binds the strategy function.
- `void set_visual_mode(bool enable)`: Toggles the Ncurses interface.
- `void update_visualization(...)`: Updates the UI state.
- `void log_event(...)`: Handles console logging of context switches.
- `void execute_schedule(...)`: Invokes the selected policy function.
- `void display_results(...)`: Prints the final statistics table and execution chain.
