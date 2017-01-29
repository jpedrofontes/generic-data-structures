#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

#include <bool.h>
#include <stdlib.h>

typedef struct linkedlist* LinkedList;

/* Function that compares the nodes. Returns -1 if A<B, 0 if A==B or 1 if A>B */
typedef int (*ListNodeComparator)(void*, void*);

/* Creates a new list with the provided node comparator. */
LinkedList list_create(ListNodeComparator);

/* Destroys the list. */
void list_destroy(LinkedList);

/* Inserts a new element in the list. No order required. */
void insert(LinkedList, void*);

/* Inserts a new element on the list by ascending order. */
void insert_asc(LinkedList, void*);

/* Inserts a new element on the list by descending order. */
void insert_desc(LinkedList, void*);

/* Deletes the specified value from the list, if exists. */
void delete(LinkedList, void*);

/* Returns the number of elements in the list. */
int size(LinkedList);

/* Determine of a value exists in the list. */
bool contains(LinkedList, void*);

#endif
