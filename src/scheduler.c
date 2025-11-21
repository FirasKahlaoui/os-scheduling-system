#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scheduler.h"
#include <ctype.h>

int is_empty_line(const char* line) {
    while (*line && isspace((unsigned char)*line)) {
        line++;
    }
    return *line == '\0';
}

Scheduler* load_processes_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    // Count valid lines first
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        if (line[0] != '#' && !is_empty_line(line) && (line[0]=='P') || (line[0]=='p')) {
            count++;
        }
    }

    if (count == 0) {
        fclose(file);
        return NULL;
    }

    // Allocate scheduler and process array
    Scheduler* scheduler = malloc(sizeof(Scheduler));
    scheduler->processes = malloc(count * sizeof(Process));
    scheduler->processCount = count;
    scheduler->currentTime = 0;

    // Read data into the array
    rewind(file);
    int i = 0;
    while (fgets(line, sizeof(line), file) && i < count) {
        line[strcspn(line, "\n")] = 0;
        if (line[0] == '#' || is_empty_line(line)) continue;

        if (sscanf(line, "%s %d %d %d", 
                   scheduler->processes[i].name,
                   &scheduler->processes[i].arrivalTime,
                   &scheduler->processes[i].executionTime,
                   &scheduler->processes[i].priority) == 4) {
            
            // Initialize other fields
            scheduler->processes[i].remainingTime = scheduler->processes[i].executionTime;
            scheduler->processes[i].startTime = -1;
            scheduler->processes[i].finishTime = -1;
            i++;
        }
    }

    fclose(file);
    return scheduler;
}
