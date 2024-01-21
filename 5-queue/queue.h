#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
    int* items;
    int length;
} Queue;

Queue* create_queue(int size);
void enqueue(Queue* q, int item);
int dequeue(Queue* q, int item);
void print_queue(Queue* q);

#endif