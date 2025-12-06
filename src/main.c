#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "parser.h"
#include "scheduler.h"
#include "display.h"

void print_help(const char *topic) {
    if (topic == NULL || strlen(topic) == 0) {
        printf("\n=== Help System ===\n");
        printf("Available commands:\n");
        printf("  1-4           : Select a scheduling policy\n");
        printf("  help <policy> : Get details about a specific policy (e.g., 'help fifo')\n");
        printf("  ? <policy>    : Short for help\n");
        printf("  exit          : Exit the program\n");
        printf("\nAvailable policies: fifo, roundrobin, priority, multilevel\n");
    } else if (strcasecmp(topic, "fifo") == 0) {
        printf("\n[FIFO Help]\nFirst-In-First-Out: Processes execute in arrival order.\nNon-preemptive: Once a process starts, it runs until completion.\n");
    } else if (strcasecmp(topic, "roundrobin") == 0 || strcasecmp(topic, "rr") == 0) {
        printf("\n[Round-Robin Help]\nTime-sharing: Each process gets a quantum (time slice).\nPreemptive: If a process exceeds its quantum, it moves to the back of the queue.\n");
    } else if (strcasecmp(topic, "priority") == 0) {
        printf("\n[Priority Help]\nHighest priority runs first (Higher number = Higher priority).\nPreemptive: If a higher priority process arrives, the current one is paused.\n");
    } else if (strcasecmp(topic, "multilevel") == 0) {
        printf("\n[Multilevel Help]\nDynamic Priority Scheduling with Aging.\n- Processes with higher priority run first.\n- Aging: Waiting processes gain +1 priority every 10 ticks to prevent starvation.\n");
    } else {
        printf("\nUnknown topic: '%s'. Try 'help' for list.\n", topic);
    }
    printf("\n");
}

void print_menu() {
    printf("\n=== Scheduler Menu ===\n");
    printf("  1) FIFO (First-In-First-Out)\n");
    printf("  2) Round-Robin\n");
    printf("  3) Preemptive Priority\n");
    printf("  4) Multilevel\n");
    printf("  ?) Help\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <config_file> [policy] [quantum]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_processes;
    process_t *processes = parse_config(argv[1], &num_processes);
    if (!processes) return EXIT_FAILURE;

    char policy[20] = "FIFO";
    int quantum = 2;
    int choice = 0;

    if (argc >= 3) {
        
        strncpy(policy, argv[2], 19);
        if (argc >= 4) quantum = atoi(argv[3]);
    } else {
        
        char input[256];
        int valid_choice = 0;

        while (!valid_choice) {
            print_menu();
            printf("Enter choice > ");
            
            if (!fgets(input, sizeof(input), stdin)) {
                free(processes);
                return EXIT_FAILURE;
            }
            
            
            input[strcspn(input, "\n")] = 0;
            
            if (strlen(input) == 0) continue;

            
            if (input[0] == '?' || strncasecmp(input, "help", 4) == 0) {
                char *arg = NULL;
                if (input[0] == '?') {
                    if (input[1] != '\0') arg = input + 1;
                } else {
                    char *space = strchr(input, ' ');
                    if (space) arg = space + 1;
                }
                
                
                if (arg) {
                    while(*arg == ' ') arg++;
                    if (*arg == '\0') arg = NULL;
                }
                
                print_help(arg);
                continue;
            }

            
            if (strcasecmp(input, "exit") == 0 || strcasecmp(input, "quit") == 0) {
                free(processes);
                return EXIT_SUCCESS;
            }

            
            char *end;
            long val = strtol(input, &end, 10);
            if (end != input && *end == '\0' && val >= 1 && val <= 4) {
                choice = (int)val;
                valid_choice = 1;
            } else {
                printf("Invalid selection. Type '?' for help.\n");
            }
        }

        switch(choice) {
            case 1: strcpy(policy, "FIFO"); break;
            case 2: 
                strcpy(policy, "RoundRobin"); 
                printf("Enter quantum (default 2): ");
                if (fgets(input, sizeof(input), stdin)) {
                    int q = atoi(input);
                    if (q > 0) quantum = q;
                }
                break;
            case 3: strcpy(policy, "Priority"); break;
            case 4: strcpy(policy, "Multilevel"); break;
            default: strcpy(policy, "FIFO"); break;
        }

        printf("Enable graphical visualization? (y/n): ");
        if (fgets(input, sizeof(input), stdin)) {
            if (input[0] == 'y' || input[0] == 'Y') {
                set_visual_mode(true);
            }
        }
    }

    init_scheduler(policy);
    
    execute_schedule(processes, num_processes, quantum);

    display_results(processes, num_processes);

    free(processes);
    return EXIT_SUCCESS;
}
