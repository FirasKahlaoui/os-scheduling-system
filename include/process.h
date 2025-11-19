#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    char name[50];
    int arrivalTime;
    int executionTime;
    int priority;
    int remainingTime;
    int startTime;
    int finishTime;
} Process;

typedef struct Node {
    Process* process;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, Process* p);
Process* dequeue(Queue* q);

#endif
