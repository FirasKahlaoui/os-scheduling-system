#ifndef DISPLAY_H
#define DISPLAY_H

#include "process.h"

void init_graphical_display();
void update_graphical_display(process_t processes[], int n, int current_time, int running_idx);
void close_graphical_display();
void display_gantt_chart(process_t processes[], int n);
void print_welcome_screen();

#endif
