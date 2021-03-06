#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER

#include <bool.h>
#include <stdlib.h>

typedef void* ListNode;
typedef struct linkedlist* LinkedList;

/* Function that compares the nodes. Returns -1 if A<B, 0 if A==B or 1 if A>B */
typedef int (*ListNodeComparator)(ListNode, ListNode);

/* Creates a new list with the provided node comparator. */
LinkedList list_create(ListNodeComparator);

/* Destroys the list. */
void list_destroy(LinkedList);

/* Inserts a new element in the list. No order required. */
void list_insert(LinkedList, ListNode);

/* Inserts a new element on the list by ascending order. */
void list_insert_asc(LinkedList, ListNode);

/* Inserts a new element on the list by descending order. */
void list_insert_desc(LinkedList, ListNode);

/* Deletes the specified value from the list, if exists. */
void list_delete(LinkedList, ListNode);

/* Returns the number of elements in the list. */
int list_size(LinkedList);

/* Determine of a value exists in the list. */
bool list_contains(LinkedList, ListNode);

/* Returns the elements in the list. */
ListNode* list_to_array(LinkedList);

#endif
