# Technical Report - Multi-task Scheduler

**Group:** The Sudoers Group - 1ING3

**Date:** December 2025

## 1. Introduction

This project consists of creating a process scheduler simulator on Linux. The objective is to understand and implement different scheduling algorithms (FIFO, Round-Robin, Priority) and visualize their execution.

## 2. Project Architecture

The project is structured in a modular way to facilitate the addition of new policies and maintenance.

### File Structure

- **src/**: Contains the main source code and header files (main, scheduler, display, utils, parser, process).
- **policies/**: Contains the implementation of scheduling algorithms. Each `.c` file implements a specific policy.
- **config_examples/**: Configuration files to test the simulator.
- **doc/**: Documentation files, including this report and code documentation.
- **bin/**: Compiled executable.
- **obj/**: Object files.

### Data Structures

The main structure is `process_t`, defined in `process.h`. It contains all the information necessary for managing a process:

- `name`: Process identifier.
- `arrival_time`, `burst_time`, `priority`: Input parameters.
- `remaining_time`: Remaining execution time (for preemptive algorithms).
- `state`: Current state (READY, RUNNING, WAITING, TERMINATED).
- `waiting_time`, `turnaround_time`: Performance metrics.

## 3. Implemented Algorithms

### FIFO (First In First Out)

- **Principle**: Processes are executed in the order of their arrival.
- **Implementation**: Initial sorting of processes by arrival time, then sequential execution.

### Round-Robin

- **Principle**: Each process receives a CPU time quantum. If the process has not finished, it returns to the queue.
- **Implementation**: A main loop manages global time. It iterates over the list of ready processes. If a process still has time to execute, it is allocated at most `quantum` time units.

### Preemptive Priority

- **Principle**: The process with the highest priority (highest value) is executed. If a new higher priority process arrives, the current process is interrupted.
- **Implementation**: At each time unit, the scheduler checks all ready processes and selects the one with the highest priority.

### Multilevel Queue (with Aging)

- **Principle**: Processes are managed in multiple queues based on priority. To prevent starvation of lower-priority processes, an aging mechanism is used.
- **Implementation**: Uses 4 dynamic priority levels. A process's priority increases by 1 for every 10 time units it spends waiting in the queue.

## 4. Graphical Interface (ncurses)

An advanced interface was developed using the `ncurses` library. It offers:

- A real-time dashboard.
- A visualization of the CPU state (IDLE/BUSY).
- A visual waiting queue.
- A scrolling Gantt chart.
- Progress bars for each process.

## 5. SCRUM Methodology

### Sprint 1: Initialization

- Setup of the directory structure and Makefile.
- Creation of basic data structures (`process_t`).
- Implementation of the configuration file parser.

### Sprint 2: Basic Algorithms

- Implementation of FIFO.
- Implementation of Round-Robin.
- Unit tests with simple configuration files.

### Sprint 3: Advanced Features

- Implementation of Preemptive Priority.
- Development of the `ncurses` graphical interface.
- Addition of the interactive menu.

## 6. Difficulties Encountered

- **Time Management**: Synchronizing the graphical display with the logical simulation required the use of delays (`usleep`).
- **Preemption**: Correctly managing the saving of the state of an interrupted process (Round-Robin and Priority) required special attention to the `remaining_time` and `state` variables.
- **Ncurses Display**: Managing windows and colors in the terminal required several iterations to obtain a clean and flicker-free rendering.

## 7. Conclusion

This project allowed us to put into practice the theoretical concepts of operating systems. The modular architecture makes it easy to extend the simulator with other algorithms (e.g., SJF, Multilevel Feedback Queue).

## 8. Licensing and Copyright

The project is licensed under the MIT License. This choice is justified by a code scan performed using `scancode-toolkit` (version 32.4.1), which confirmed that the codebase contains no existing third-party licenses or copyright notices that would conflict with MIT. The scan results are available in `scan_results.json`.
