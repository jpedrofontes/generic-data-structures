/*
    Example of an int LinkedList implementation using pointers to pointers, providing an efficient and correct manipulation of data. 
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int value;
  struct node *next;
}*List;

/* Creates first Linked List node. */
List list_create(int value){
  List new = malloc(sizeof(struct node));
  new->value = value;
  new->next = NULL;
  return new;
}

/* Destroys Linked List. */
void list_destroy(List *l){
  List *p = l;
  while ((*p)){
    List next = (*p)->next;
    free(*p);
    (*p) = NULL;
    p = &(next);
  }
}

/* Creates a new Linked List element. */
List new_node(int value, List next_node){
  List new = malloc(sizeof(struct node));
  new->value = value;
  new->next = next_node;
  return new;
}

/* Updates Linked List head. No order required. */
void insert(List *l, int value){
  List *p = l;
  List tmp = (*p);
  List new = new_node(value,tmp);
  (*p) = new;
}

/* Inserts a new element on linked list by ascending order. */
void insert_asc(List *l, int value){
  List *p;
  for(p = l; (*p) != NULL; p = &((*p)->next))
    if ((*p)->value >= value){
      List tmp = *p;
      List new = new_node(value,tmp);
      *p = new;
      break;
    }
  if ((*p) == NULL)
    (*p) = new_node(value, NULL);
}

/* Inserts a new element on linked list by descending order */
void insert_desc(List *l, int value){
  List *p;
  for(p = l; (*p) != NULL; p = &((*p)->next))
    if (value >= (*p)->value){
      List tmp = (*p);
      List new = new_node(value,tmp);
      (*p) = new;
      break;
    }
  if ((*p) == NULL)
    (*p) = new_node(value,NULL);
}

/* Deletes the specified value from linked list (first occurence), if exists. */
void delete(List *l, int value){
  List *p;
  for(p = l; (*p) != NULL; p = &((*p)->next))
    if ((*p)->value == value){
        List del = (*p);
        (*p) = (*p)->next;
        free(del);
        break;
    }
}

/* Prints Linked List elements. */
void print_list(List l){
  List aux;
  for(aux = l; aux != NULL; aux = aux->next)
    printf("Value: %d\n", aux->value);
}

int main(void){
  List n = list_create(0);

  for(int i = 1; i < 10; i++)
    insert(&n,i);
  print_list(n);

  for (int i = 0; i < 10; i += 2)
    delete(&n,i);
  printf("\nRemoval of even numbers; New List:\n");
  print_list(n);

  printf("\nDestroy List result:\n");
  list_destroy(&n);
  print_list(n);

  return 0;
}
