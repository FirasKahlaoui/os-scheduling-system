# Documentation: display.c

## Overview
`display.c` handles the **Graphical User Interface (GUI)** using the `ncurses` library. It transforms the terminal into a dynamic dashboard showing real-time simulation status.

## Key Components

### 1. Dashboard Layout
The screen is divided into several sections:
- **Header**: Project title and current time.
- **Process List**: A table showing the state (READY, RUNNING, TERMINATED) and progress of each process.
- **CPU State**: Shows which process is currently on the CPU.
- **Gantt Chart**: A scrolling horizontal bar chart at the bottom visualizing the execution history.

### 2. Visualization Logic
- `init_graphical_display()`: Sets up ncurses mode, hides the cursor, and enables colors.
- `update_graphical_display(...)`:
    - Clears the screen.
    - Draws borders using `draw_box_custom`.
    - Iterates through processes to draw **Progress Bars** (using `[` `|` `]` characters).
    - Updates the Gantt chart string by appending the current running process's name.
    - Refreshes the screen to show changes.

## Functions
- `void init_graphical_display()`: Initializes ncurses.
- `void close_graphical_display()`: Restores normal terminal mode.
- `void update_graphical_display(...)`: Main render loop.
- `void draw_progress_bar(...)`: Helper to render ASCII progress bars.
