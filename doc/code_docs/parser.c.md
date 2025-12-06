# Documentation: parser.c

## Overview
`parser.c` is responsible for reading the input configuration file and converting it into the internal `process_t` structures.

## File Format
The parser expects a file with the following columns:
`ProcessName ArrivalTime BurstTime Priority`
Example:
```
P1 0 10 3
P2 2 5 1
```

## Logic
1.  **File Opening**: Opens the specified file path.
2.  **Line Reading**: Reads the file line by line.
3.  **Parsing**: Uses `sscanf` or string tokenization to extract the 4 fields.
4.  **Validation**: Skips comments (lines starting with `#`) and empty lines.
5.  **Allocation**: Dynamically allocates an array of `process_t` to store the data.

## Functions
- `process_t *parse_config(const char *filename, int *num_processes)`: The main parsing function. Returns a pointer to the array of processes.
