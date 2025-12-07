# Installation and Usage Guide

## 1. Prerequisites

This project is designed for Linux environments. Ensure you have the following tools installed:

- **GCC** (GNU Compiler Collection)
- **Make** (Build automation tool)
- **libncurses-dev** (Library for the graphical interface)

### Installing Prerequisites

On Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install build-essential libncurses5-dev libncursesw5-dev
```

## 2. Compilation

To compile the project, navigate to the project root directory and run:

```bash
make
```

This will compile all source files and generate the executable in the `bin/` directory.

To clean the build (remove object files and executable):

```bash
make clean
```

## 3. Installation (Optional)

You can install the scheduler to your local bin directory (`~/.local/bin`) so it can be run from anywhere:

```bash
make install
```

## 4. Usage

### Interactive Mode (Recommended)

Run the scheduler with a configuration file. You will be prompted to select a scheduling policy and enable visualization.

```bash
./bin/scheduler config_examples/test1.conf
```

**Menu Options:**

1. **FIFO**: First-In-First-Out scheduling.
2. **Round-Robin**: Time-slice based scheduling (requires quantum).
3. **Preemptive Priority**: Priority-based scheduling with preemption.
4. **Multilevel**: Multi-level queue scheduling.
5. **Help**: Help menu.

**Available Commands:**

- `1-4`: Select a scheduling policy.
- `help <policy>`: Get details about a specific policy (e.g., `help fifo`).
- `? <policy>`: Short for help.
- `exit`: Exit the program.

### Command Line Mode

You can specify the policy and quantum directly as arguments:

**Syntax:**

```bash
./bin/scheduler <config_file> <policy_name> [quantum]
```

**Examples:**

```bash
# Run FIFO
./bin/scheduler config_examples/test1.conf FIFO

# Run Round-Robin with quantum 4
./bin/scheduler config_examples/test2.conf RoundRobin 4

# Run Priority
./bin/scheduler config_examples/big_test.conf Priority
```

## 5. Configuration File Format

The configuration file defines the processes to be scheduled. Each line represents a process.

**Format:**

```text
Name    Arrival_Time    Burst_Time    Priority
```

**Example:**

```text
# This is a comment
P1      0              10            1
P2      2              5             2
P3      4              2             3
```

- **Name**: String (max 31 chars)
- **Arrival_Time**: Integer (>= 0)
- **Burst_Time**: Integer (> 0)
- **Priority**: Integer (Higher value = Higher priority)
