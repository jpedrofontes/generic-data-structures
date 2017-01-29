#include <queue.h>

struct queue {
	void* values;
	int head;
	int tail;
	int size;
	int nr_elems;
};

/* Creates a new queue with the provided size. */
Queue queue_create(int size) {
	Queue q = malloc(sizeof(struct queue));
	if (q == NULL)
		return NULL;
	q->values = malloc(size * sizeof(void*));
	if (q->values == NULL) {
		free(q);
		return NULL;
	}
	q->head = 0;
	q->tail = 0;
	q->size = size;
	q->nr_elems = 0;
	return q;
}

/* Destroy the queue. */
void queue_destroy() {
	if (q != NULL) {
		free(q->values);
		free(q);
	}
}

/* Put a new value in queue's tail. */
int enqueue(Queue q, void* value) {
	if (q->nr_elems == q->size)
		return FULL_QUEUE;
	q->values[q->tail++] = value;
	q->tail %= q->size;
	q->nr_elems++;
	return 0;
}

/* Retrieve the value in queue's head. */
void* dequeue(Queue q) {
	if (q->nr_elems == 0)
		return EMPTY_QUEUE;
	void* del = q->values[q->head];
	q->head++;
	q->head %= q->size;
	q->nr_elems--;
	return del;
}

/* Returns the number of elements in the queue. */
int size(Queue q) {
	int size = 0;
	if (q != NULL)
		size = q->nr_elems;
	return size;
}
