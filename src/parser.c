#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#define MAX_LINE_LENGTH 256
#define INITIAL_CAPACITY 10

process_t* parse_config(const char *filename, int *num_processes) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening config file");
        return NULL;
    }

    int capacity = INITIAL_CAPACITY;
    process_t *processes = malloc(capacity * sizeof(process_t));
    if (!processes) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    *num_processes = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        
        if (line[0] == '\n' || line[0] == '#' || line[0] == '\r') continue;

        char name[32];
        int arrival, burst, priority;

        if (sscanf(line, "%31s %d %d %d", name, &arrival, &burst, &priority) == 4) {
            if (*num_processes >= capacity) {
                capacity *= 2;
                process_t *temp = realloc(processes, capacity * sizeof(process_t));
                if (!temp) {
                    perror("Memory reallocation failed");
                    free(processes);
                    fclose(file);
                    return NULL;
                }
                processes = temp;
            }
            init_process(&processes[*num_processes], name, arrival, burst, priority);
            (*num_processes)++;
        }
    }

    fclose(file);
    return processes;
}
