#include <stdio.h>
#include <stdlib.h>
#include "../include/scheduler.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <config_file>\n", argv[0]);
        return 1;
    }

    // Load the processes from the file
    Scheduler* scheduler = load_processes_from_file(argv[1]);

    if (scheduler == NULL) {
        printf("Failed to load %s\n", argv[1]);
        return 1;
    }

    printf("Successfully loaded %d\n", scheduler->processCount);
    for (int i = 0; i < scheduler->processCount; i++) {
        printf("  Process %d: %s (Arrive at: %d, Eexecution_time: %d, Priority: %d)\n",
               i + 1,
               scheduler->processes[i].name,
               scheduler->processes[i].arrivalTime,
               scheduler->processes[i].executionTime,
               scheduler->processes[i].priority);
    }
    int request=0,a;
    
    do{printf("please choose between these schedulers \n 0 to exit \n 1 for Fifo \n 2 for Round Robin \n :");
        scanf("%d",&request);
        if(request==1)
        {
        fifo_scheduler(scheduler);printf("\n");
        }
    if(request==2)
        {
        printf("donnez le quantum \n ");
        scanf("%d",&a);
        round_robin_scheduler(scheduler,a);printf("\n");
        }    
    }while(request!=0);
    free(scheduler->processes);
    free(scheduler);
    return 0;
}
