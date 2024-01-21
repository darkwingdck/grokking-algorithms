#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int* items;
    int length;
} Queue;

Queue* create_queue(int size) {
    Queue* q = (Queue*) malloc(sizeof(Queue));
    q->length = 0;
    q->items = (int*) calloc(size, sizeof(int));

    for (int i = 0; i < size; i++) {
        q->items[i] = 0;
    }
    return q;
}

void enqueue(Queue* q, int item) {
    q->items[q->length] = item;
    q->length++;
}

int dequeue(Queue* q, int item) {
    if (q->length == 0) {
        return 0;
    }

    int dequeued_item = q->items[0];

    for (int i = 0; i < q->length; i++) {
        q->items[i] = q->items[i + 1];
    }

    q->length--;

    return dequeued_item;
}

void print_queue(Queue* q) {
    printf("Length: %d, Items: ", q->length);
    for (int i = 0; i < q->length; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}
