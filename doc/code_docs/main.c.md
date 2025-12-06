# Documentation: main.c

## Overview
`main.c` serves as the entry point for the Process Scheduler application. It is responsible for initializing the environment, parsing command-line arguments, and managing the user interaction loop. It acts as the controller that bridges the user's input (configuration files, policy selection) with the core scheduling logic.

## Key Functionality

### 1. Argument Parsing
The program expects at least one argument: the configuration file path.
- Usage: `./scheduler <config_file> [policy] [quantum]`
- If optional arguments (policy, quantum) are provided, the program runs in **non-interactive mode** and immediately starts the simulation.

### 2. Interactive Menu
If only the configuration file is provided, `main.c` enters an **interactive loop**:
- Displays a menu with available scheduling policies (FIFO, Round-Robin, Priority, Multilevel).
- Accepts user input for policy selection (1-4).
- Supports a **Help System**: Users can type `?` or `help <policy>` to get context-sensitive assistance.
- Allows toggling the **Graphical Visualization** (Ncurses mode) before starting.

### 3. Execution Flow
1.  **Parse Config**: Calls `parse_config` (from `parser.c`) to load processes from the file.
2.  **Select Policy**: Sets the scheduling algorithm based on user choice.
3.  **Init Scheduler**: Calls `init_scheduler` (from `scheduler.c`) to bind the correct function pointer.
4.  **Run Simulation**: Calls `execute_schedule` to start the processing loop.
5.  **Display Results**: After execution, calls `display_results` to show metrics and execution order.
6.  **Cleanup**: Frees allocated memory before exiting.

## Functions
- `void print_help(const char *topic)`: Displays detailed help messages for specific policies or general commands.
- `void print_menu()`: Prints the main selection menu to stdout.
- `int main(int argc, char *argv[])`: The main driver function containing the event loop and initialization logic.
