#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <stdlib.h>

#define FULL_QUEUE -1
#define EMPTY_QUEUE -2

typedef struct queue *Queue;

/* Creates a new queue with the provided size. */
Queue queue_create(int);

/* Destroy the queue. */
void queue_destroy();

/* Put a new value in queue's tail. */
int enqueue(Queue, void*);

/* Retrieve the value in queue's head. */
void* dequeue(Queue);

/* Returns the number of elements in the queue. */
int size(Queue);

#endif
