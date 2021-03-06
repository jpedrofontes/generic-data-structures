#ifndef STACK_HEADER
#define STACK_HEADER

#include <stdlib.h>
#include "bool.h"

#define CAPACITY 100
#define FULL_STACK -1
#define EMPTY_STACK -2
#define NOT_FOUND -3
#define SUCCESS 0

typedef struct stack *Stack;

/* Function that compares stack elements. Returns -1 if A<B, 0 if A==B or 1 if A>B */
typedef int (*StackElementComparator)(void*, void*);

/* Creates a new Stack, with capacity for CAPACITY elements. */
Stack stack_create(StackElementComparator);

/* Pushes an item onto the top of this stack.
   Returns SUCCESS if stack not full, FULL_STACK otherwise.
*/
int stack_push (Stack, void *);

/* Removes the object at the top of this stack.
   Returns SUCCESS if stack not empty, EMPTY_STACK otherwise
*/
int stack_pop (Stack);

/* Looks at the object at the top of this stack without removing it from the stack. */
void* stack_peek (Stack);

/* Returns stack current size. */
int stack_size (Stack);

/* Returns the 1-based position where an item is on this stack.
   Returns NOT_FOUND if the element is not on this stack.
*/
int stack_search (Stack, void *);

/* Tests if this stack is empty. */
bool stack_empty (Stack);

#endif
