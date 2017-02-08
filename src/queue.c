#include "queue.h"

struct queue {
	QueueElement* values;
	int head;
	int tail;
	int size;
	int nr_elems;
	QueueElementComparator comparator;
};

/* Creates a new queue with the provided size. */
Queue queue_create(QueueElementComparator c) {
	Queue q = malloc(sizeof(struct queue));
	if (q == NULL)
		return NULL;
	q->values = malloc(CAPACITY * sizeof(QueueElement));
	if (q->values == NULL) {
		free(q);
		return NULL;
	}
	q->head = 0;
	q->tail = 0;
	q->size = CAPACITY;
	q->nr_elems = 0;
	q->comparator = c;
	return q;
}

/* Destroy the queue. */
void queue_destroy(Queue q) {
	if (q != NULL) {
		free(q->values);
		free(q);
	}
}

/* Pushes an item onto the top of this queue.
   Returns SUCCESS if queue not full, FULL_STACK otherwise.
*/
int enqueue(Queue q, QueueElement value) {
	if ( q->nr_elems == q->size )
		return FULL_QUEUE;
	q->values[ q->tail++ ] = value;
	q->tail %= q->size;
	q->nr_elems++;
	return SUCCESS;
}

/* Retrieves, but does not remove, the head of this queue,
   or returns null if this queue is empty.
*/
QueueElement peek(Queue q) {
	if (q->nr_elems == 0)
		return NULL;
	QueueElement del = q->values[ q->head ];
	return del;
}

/* Retrieves and removes the head of this queue,
   or returns null if this queue is empty.
*/
QueueElement dequeue(Queue q) {
	if (q->nr_elems == 0)
		return NULL;
	QueueElement del = q->values[ q->head ];
	q->head++;
	q->head %= q->size;
	q->nr_elems--;
	return del;
}

/* Returns queue current size. */
int size(Queue q) {
	int size = 0;
	if (q != NULL)
		size = q->nr_elems;
	return size;
}

/* Returns the 1-based position where an item is on this queue.
   Returns NOT_FOUND if the element is not on this queue.
*/
int search (Queue q, QueueElement value) {
	Queue aux = q;
    for (int i=0; i < aux->nr_elems; i++) {
    	if ( aux->comparator( aux->values[i], value ) == 0 )
			return i;
    }
    return NOT_FOUND;
}

/* Tests if this queue is empty. */
bool empty (Queue q) {
	return (q->nr_elems == 0);
}
