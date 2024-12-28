#include "../headers/queue.h"

Queue* create_queue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));

    if (q == NULL) {
        printf("Error allocation memory for queue!");
        return NULL;
    }

    q->capacity = capacity;
    q->size = 0;
    q->front = 0;
    q->rear = -1;
    q->items = (void**)malloc(capacity * sizeof(void*));

    return q;
}

void enqueue(Queue* q, void* item) {
    if (q->size == q->capacity) 
        return;

    q->rear = (q->rear + 1) % q->capacity;
    q->items[q->rear] = item;
    q->size++;
}

void* dequeue(Queue* q) {
    if (q->size == 0) 
        return NULL;

    void* item = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return item;
}

int is_queue_empty(Queue* q) {
    return q->size == 0;
}

void free_queue(Queue* q) {
    free(q->items);
    free(q);
}