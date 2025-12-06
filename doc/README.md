# Multi-task Process Scheduler on Linux

## Project Presentation

This project implements a multi-task process scheduler on Linux, capable of managing multiple scheduling policies. It simulates process execution based on arrival time, burst time, and priority.

## Features

- **Scheduling Policies**:

  - FIFO (First In First Out)
  - Round-Robin (configurable quantum)
  - Preemptive Static Priority
  - Multi-level Queues (Skeleton)
- **Interactive Mode**:
  - Dynamic menu to select policies at runtime.
  - Option to enable/disable graphical visualization.
- **Advanced Visualization**:
  - Real-time dashboard using `ncurses`.
  - Visual Process Table with progress bars.
  - CPU State indicator (IDLE/BUSY).
  - Visual Ready Queue.
  - Scrolling Gantt Chart timeline.

## Project Structure

```text
GroupeX-1ING1/
├── src/            # Source files (main, scheduler, display, etc.)
├── policies/       # Scheduling policies implementation
├── include/        # Headers
├── config_examples/# Configuration files
├── doc/            # Documentation (Reports, Install Guide)
├── obj/            # Object files
├── bin/            # Executable
└── Makefile        # Build script
```

## Installation

Prerequisites: `gcc`, `make`, `libncurses-dev`

Build:

```bash
make
```

Install (optional):

```bash
make install
```

## Usage

**1. Interactive Mode:**

Run without policy arguments to use the menu:

```bash
./bin/scheduler config_examples/test1.conf
```

**2. Command Line Mode:**

```bash
./bin/scheduler <config_file> [policy] [quantum]
```

Examples:

```bash
./bin/scheduler config_examples/test1.conf FIFO
./bin/scheduler config_examples/test2.conf RoundRobin 4
```

## Configuration File Format

```text
# Name Arrival Burst Priority
P1    0       10    1
P2    2       5     2
```
