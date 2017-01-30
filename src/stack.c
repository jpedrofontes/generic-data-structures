/*
    Generic Stack implementation.
*/
#include "stack.h"

struct stack {
  void *values[CAPACITY];
  int nr_elems;
  StackElementComparator comparator;
};

/* Creates a new Stack, with capacity for CAPACITY elements. */
Stack stack_create (StackElementComparator comparator) {
  Stack s = (Stack) malloc (sizeof (struct stack) );
  if (s == NULL)
    return NULL;
  s -> nr_elems = 0;
  s -> comparator = comparator;
  return s;
}

/* Pushes an item onto the top of this stack.
   Returns SUCCESS if stack not full, FULL_STACK otherwise.
*/
int push (Stack s, void *value) {
  if (s -> nr_elems == CAPACITY) {
      return FULL_STACK;
  }
  else {
    s -> values[s -> nr_elems++] = value;
    return SUCCESS;
  }
}

/* Removes the object at the top of this stack.
   Returns SUCCESS if stack not empty, EMPTY_STACK otherwise.
*/
int pop (Stack s) {
  if (s -> nr_elems == 0) {
    return EMPTY_STACK;
  }
  else {
    s -> nr_elems--;
    return SUCCESS;
  }
}

/* Looks at the object at the top of this stack without removing it from the stack. */
void *peek (Stack s) {
  return s -> values[(s -> nr_elems) - 1];
}

/* Returns stack current size. */
int size (Stack s) {
  return s -> nr_elems;
}

/* Returns the 1-based position where an item is on this stack.
   Returns NOT_FOUND if the element is not on this stack.
*/
int search (Stack s, void *value) {
  Stack aux = s;
  for (int i = 0; i < aux -> nr_elems; i++) {
    if ( s -> comparator ( s -> values[i], value ) == 0 )
      return i;
  }
  return NOT_FOUND;
}

/* Tests if this stack is empty. */
bool empty (Stack s) {
  return ( s -> nr_elems == 0 );
}
