#define _DEFAULT_SOURCE
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_POLICIES 10
#define POLICY_NAME_LENGTH 50


void list_scheduling_policies(char policies[][POLICY_NAME_LENGTH], int *count) {
    DIR *dir;
    struct dirent *entry;
    *count = 0;

    dir = opendir("policies");
    if (dir == NULL) {
        perror("Failed to open policies directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        
        if (strstr(entry->d_name, ".c") != NULL) {
            strncpy(policies[*count], entry->d_name, POLICY_NAME_LENGTH - 1);
            policies[*count][POLICY_NAME_LENGTH - 1] = '\0';
            
            
            char *dot = strrchr(policies[*count], '.');
            if (dot) *dot = '\0';
            
            (*count)++;
            if (*count >= MAX_POLICIES) {
                break; 
            }
        }
    }
    closedir(dir);
}
