#include "queue.h"
#include <assert.h>
#include <stdio.h>

#define CAPACITY 50000

int main() {
    Queue* q = create_queue(CAPACITY);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    assert(q->length == 3);
    dequeue(q, 2);
    assert(q->length == 2);
    assert(q->items[0] == 2);
    assert(q->items[1] == 3);
    assert(q->items[2] == 0);
    printf("%s\n", "All tests passed!");
    return 0;
}