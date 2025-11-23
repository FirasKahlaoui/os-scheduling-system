#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/scheduler.h"

int main(int argc, char* argv[]){
    int quantum = 0;
    if (argc < 2 || argc > 4) {
        printf("Usage : %<config_file> <policy> [quantum]\n" , argv[0]);
        printf("Policies available:\n");
        printf(" - fifo\n");
        printf(" - rr (requires an integer quantum , e.g., 'rr 5')\n");
        printf(" - preemptive_priority\n");
        return 1;
    }
    char* config_file = argv[1]; 
    char* policy = argv[2];


    if (strcmp(policy,"rr")== 0){
        if (argc!= 4){
            printf("Error: round-robin ('rr') requires a time quantum as the fourth argument.\n");
            return 1;
        }
        quantum=atoi(argv[3]);
        if (quantum>=0){
            printf("Error : Quantum must be a positive integer (received: %s).\n", argv[3]);
            return 1;
        }
    }
    else if (argc==4){
        printf("Warning: Extra argument '%s' ignored for policy '%s' .\n", argv[3], policy);
    }


    Scheduler* scheduler = load_process_from_file(config_file);

    if (scheduler ==NULL){
        printf("Failed to load process from%s.check file content or permissions.\n",config_file);
        return 1;
    }
    printf("Successfully loaded %d process.\n", scheduler->processCount);

    for (int i=0 ; i<scheduler->processCount;i++){
        printf("Process %d :%s (Arrive at : %d , Execution_time: %d ,Priority: %d)\n",
        i+1,
        scheduler->processes[i].name,
        scheduler->processes[i].arrivalTime,
        scheduler->processes[i].executionTime,
        scheduler->processes[i].priority);
    }


    printf("\n=== Running with policy: %s ===\n",policy);

    if (strcmp(policy, "fifo") == 0 || argc==2){
        fifo_sheduler(scheduler);
    }
    else if (strcmp(policy,"rr")==0){
        round_robin_sheduler(scheduler, quantum );
    }
    else if (strcmp(policy, "preemptive_priority") ==0 ){
        preemptive_priority_sheduler(scheduler);
    }
    else{
        printf("Error: Unknown sheduling policy '%s'.Please choose from the list.\n", policy);
        free(scheduler->processes);
        free(scheduler);
        return 1;
    }

    free(scheduler->processes);
    free(scheduler);
    return 0;
}