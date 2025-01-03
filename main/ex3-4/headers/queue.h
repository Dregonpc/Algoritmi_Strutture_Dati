#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    void** items;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* create_queue(int capacity);

void enqueue(Queue* q, void* item);

void* dequeue(Queue* q);

int is_queue_empty(Queue* q);

void free_queue(Queue* q);

#endif //QUEUE_H