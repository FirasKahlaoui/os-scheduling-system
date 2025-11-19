# Data Structures Module

This module defines the Process structure and the Queue system used by the scheduler. It gives you the core tools needed for FIFO and Round Robin.

## Process Structure

The `Process` struct in `include/process.h` represents one task.

You get these fields:

- **name** `char[]`  
  A unique label for the process.

- **arrivalTime** `int`  
  When the process enters the system.

- **executionTime** `int`  
  Total CPU cycles needed.

- **priority** `int`  
  Static priority value.

- **remainingTime** `int`  
  Tracks unfinished cycles for Round Robin or preemptive logic.

- **startTime** `int`  
  When the process first gets CPU time.

- **finishTime** `int`  
  When the process completes.

## Queue Management

The system uses a dynamic linked list queue. This removes size limits and lets you add or remove processes with simple operations.

Functions in `src/process.c`:

- **createQueue()**  
  Builds and returns an empty queue.

- **enqueue(Queue* q, Process* p)**  
  Adds a process to the end.

- **dequeue(Queue* q)**  
  Removes and returns the first process.

## File Organization

- **include/process.h**  
  Struct definitions.

- **src/process.c**  
  Queue operations.
