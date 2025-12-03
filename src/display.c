#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "display.h"

#define COLOR_READY 1
#define COLOR_RUNNING 2
#define COLOR_WAITING 3
#define COLOR_TERMINATED 4
#define COLOR_BORDER 5
#define COLOR_HEADER 6
#define COLOR_IDLE 7

#define MAX_HISTORY 200
static char gantt_history[MAX_HISTORY][10]; 
static int history_count = 0;
static int last_recorded_time = -1;

void init_graphical_display() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    use_default_colors();
    
    init_pair(COLOR_READY, COLOR_YELLOW, -1);
    init_pair(COLOR_RUNNING, COLOR_GREEN, -1);
    init_pair(COLOR_WAITING, COLOR_RED, -1);
    init_pair(COLOR_TERMINATED, COLOR_CYAN, -1);
    init_pair(COLOR_BORDER, COLOR_WHITE, -1);
    init_pair(COLOR_HEADER, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_IDLE, COLOR_MAGENTA, -1);
}

void draw_progress_bar(int y, int x, int width, int percentage, int color_pair) {
    attron(COLOR_PAIR(color_pair));
    mvprintw(y, x, "[");
    int fill = (width - 2) * percentage / 100;
    for(int i=0; i<width-2; i++) {
        if(i < fill) addch('|');
        else addch(' ');
    }
    addch(']');
    attroff(COLOR_PAIR(color_pair));
    mvprintw(y, x + width + 1, "%3d%%", percentage);
}

void draw_box_custom(int y, int x, int h, int w, const char* title) {
    attron(COLOR_PAIR(COLOR_BORDER));
    
    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y, x + w - 1, ACS_URCORNER);
    mvaddch(y + h - 1, x, ACS_LLCORNER);
    mvaddch(y + h - 1, x + w - 1, ACS_LRCORNER);
    
    
    for(int i = 1; i < w - 1; i++) {
        mvaddch(y, x + i, ACS_HLINE);
        mvaddch(y + h - 1, x + i, ACS_HLINE);
    }
    
    
    for(int i = 1; i < h - 1; i++) {
        mvaddch(y + i, x, ACS_VLINE);
        mvaddch(y + i, x + w - 1, ACS_VLINE);
    }
    
    if (title) {
        mvprintw(y, x + 2, " %s ", title);
    }
    attroff(COLOR_PAIR(COLOR_BORDER));
}

void update_graphical_display(process_t processes[], int n, int current_time, int running_idx) {
    
    if (current_time > last_recorded_time) {
        if (history_count < MAX_HISTORY) {
            if (running_idx != -1) {
                strncpy(gantt_history[history_count], processes[running_idx].name, 9);
            } else {
                strcpy(gantt_history[history_count], "_");
            }
            history_count++;
        }
        last_recorded_time = current_time;
    }

    clear();
    int height, width;
    getmaxyx(stdscr, height, width);

    
    attron(COLOR_PAIR(COLOR_HEADER) | A_BOLD);
    for(int i=0; i<width; i++) mvaddch(0, i, ' ');
    mvprintw(0, (width-36)/2, " LINUX PROCESS SCHEDULER SIMULATION ");
    mvprintw(0, width-15, "Time: %04d", current_time);
    attroff(COLOR_PAIR(COLOR_HEADER) | A_BOLD);

    
    int table_h = n + 4;
    draw_box_custom(2, 1, table_h, width - 2, "Process Table");
    
    attron(A_BOLD | A_UNDERLINE);
    mvprintw(3, 3, "PID   Name      Prio   Arr   Burst   Rem   State       Progress");
    attroff(A_BOLD | A_UNDERLINE);

    for(int i=0; i<n; i++) {
        int color = COLOR_READY;
        char state_str[12];
        
        if (processes[i].state == TERMINATED) {
            color = COLOR_TERMINATED;
            strcpy(state_str, "DONE");
        } else if (i == running_idx) {
            color = COLOR_RUNNING;
            strcpy(state_str, "RUNNING");
        } else if (processes[i].arrival_time > current_time) {
            color = COLOR_WAITING;
            strcpy(state_str, "WAITING");
        } else {
            color = COLOR_READY;
            strcpy(state_str, "READY");
        }

        attron(COLOR_PAIR(color));
        if (i == running_idx) attron(A_BOLD);
        
        mvprintw(4 + i, 3, "%-5d %-9s %-6d %-5d %-7d %-5d %-10s", 
            i, processes[i].name, processes[i].priority, 
            processes[i].arrival_time, processes[i].burst_time, 
            processes[i].remaining_time, state_str);
        
        if (i == running_idx) attroff(A_BOLD);
        attroff(COLOR_PAIR(color));
        
        int progress = 0;
        if (processes[i].burst_time > 0) {
            progress = ((processes[i].burst_time - processes[i].remaining_time) * 100) / processes[i].burst_time;
        }
        if (processes[i].state == TERMINATED) progress = 100;
        
        draw_progress_bar(4 + i, 60, 20, progress, color);
    }

    
    int cpu_y = table_h + 3;
    draw_box_custom(cpu_y, 1, 5, 30, "CPU State");
    if (running_idx != -1) {
        attron(COLOR_PAIR(COLOR_RUNNING) | A_BOLD);
        mvprintw(cpu_y + 2, 3, " [ BUSY ] Executing: %s", processes[running_idx].name);
        attroff(COLOR_PAIR(COLOR_RUNNING) | A_BOLD);
    } else {
        attron(COLOR_PAIR(COLOR_IDLE) | A_BOLD);
        mvprintw(cpu_y + 2, 3, " [ IDLE ] Waiting...");
        attroff(COLOR_PAIR(COLOR_IDLE) | A_BOLD);
    }

    
    draw_box_custom(cpu_y, 32, 5, width - 33, "Ready Queue");
    int q_x = 34;
    for(int i=0; i<n; i++) {
        if(processes[i].state == READY && processes[i].arrival_time <= current_time && i != running_idx) {
            attron(COLOR_PAIR(COLOR_READY));
            mvprintw(cpu_y + 2, q_x, "[%s]", processes[i].name);
            attroff(COLOR_PAIR(COLOR_READY));
            q_x += strlen(processes[i].name) + 3;
            if (q_x > width - 5) break;
        }
    }

    
    int gantt_y = cpu_y + 6;
    draw_box_custom(gantt_y, 1, 5, width - 2, "Gantt Timeline");
    
    int start_idx = 0;
    if (history_count > (width - 6)) {
        start_idx = history_count - (width - 6);
    }

    for(int i = start_idx; i < history_count; i++) {
        int color = COLOR_IDLE;
        if (strcmp(gantt_history[i], "_") != 0) {
            
            
            color = COLOR_RUNNING;
        }
        
        attron(COLOR_PAIR(color));
        mvaddch(gantt_y + 2, 3 + (i - start_idx), '|');
        attroff(COLOR_PAIR(color));
        
        
        if (i == start_idx || strcmp(gantt_history[i], gantt_history[i-1]) != 0) {
             mvprintw(gantt_y + 1, 3 + (i - start_idx), "%s", gantt_history[i]);
        }
    }

    refresh();
}

void close_graphical_display() {
    attron(COLOR_PAIR(COLOR_HEADER) | A_BOLD | A_BLINK);
    mvprintw(LINES/2, (COLS-40)/2, " SIMULATION COMPLETED - PRESS ANY KEY ");
    attroff(COLOR_PAIR(COLOR_HEADER) | A_BOLD | A_BLINK);
    refresh();
    getch();
    endwin();
}

void display_gantt_chart(process_t processes[], int n) {
    printf("\n=== Final Gantt Chart ===\n");
    for (int i = 0; i < n; i++) {
        printf("| %s ", processes[i].name);
    }
    printf("|\n");
}
