#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <stdlib.h>
#include "bool.h"

#define CAPACITY 100
#define FULL_QUEUE -1
#define EMPTY_QUEUE -2
#define NOT_FOUND -3
#define SUCCESS 0

typedef void* QueueElement;
typedef struct queue *Queue;

/* Function that compares queue elements. Returns -1 if A<B, 0 if A==B or 1 if A>B */
typedef int (*QueueElementComparator)(QueueElement, QueueElement);

/* Creates a new Queue, with capacity for CAPACITY elements. */
Queue queue_create(QueueElementComparator);

/* Destroys the queue. */
void queue_destroy(Queue);

/* Pushes an item onto the top of this queue.
   Returns SUCCESS if queue not full, FULL_STACK otherwise.
*/
int enqueue(Queue, QueueElement);

/* Retrieves, but does not remove, the head of this queue,
   or returns null if this queue is empty.
*/
QueueElement peek(Queue);

/* Retrieves and removes the head of this queue,
   or returns null if this queue is empty.
*/
QueueElement dequeue(Queue);

/* Returns queue current size. */
int size(Queue);

/* Returns the 1-based position where an item is on this queue.
   Returns NOT_FOUND if the element is not on this queue.
*/
int search(Queue, QueueElement);

/* Tests if this queue is empty. */
bool empty(Queue);

#endif
