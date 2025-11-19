#include <stdlib.h>
#include <stdio.h>
#include "../include/process.h"

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = q->tail = NULL;
    return q;
}

void enqueue(Queue* q, Process* p) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = p;
    newNode->next = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = newNode;
        return;
    }
    q->tail->next = newNode;
    q->tail = newNode;
}

Process* dequeue(Queue* q) {
    if (q->head == NULL) return NULL;

    Node* temp = q->head;
    Process* p = temp->process;
    q->head = q->head->next;

    if (q->head == NULL) q->tail = NULL;

    free(temp);
    return p;
}
