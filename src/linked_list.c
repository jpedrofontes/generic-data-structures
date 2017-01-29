#include <linked_list.h>

typedef struct node {
	void* value;
	struct node* next;
} *List;

struct linkedlist {
	List list;
	int size;
	ListNodeComparator ll_node_comp;
};

/* Creates a new list with the provided node comparator. */
LinkedList list_create(ListNodeComparator ll_node_comp) {
	LinkedList l = malloc(sizeof(struct linkedlist));
	l->size = 0;
	l->ll_node_comp = ll_node_comp;
	return l;
}

/* Destroys Linked List. */
void ll_destroy(List *l) {
	List *p = l;
	while ((*p)) {
		List next = (*p)->next;
		free(*p);
		(*p) = NULL;
		p = &(next);
	}
}

/* Destroys the list. */
void list_destroy(LinkedList l) {
	if (l != NULL) {
		ll_destroy(&l->list);
		free(l);
		l = NULL;
	}
}

/* Creates a new Linked List element. */
List ll_new_node(void* value, List next_node) {
	List new = malloc(sizeof(struct node));
	new->value = value;
	new->next = next_node;
	return new;
}

/* Updates Linked List head. No order required. */
void ll_insert(List *l, void* value) {
	List *p = l;
	List tmp = (*p);
	List new = ll_new_node(value, tmp);
	(*p) = new;
}

/* Inserts a new element in the list. No order required. */
void insert(LinkedList l, void* value) {
	if (l != NULL) {
		ll_insert(&l->list, value);
		size++;
	}
}

/* Inserts a new element on linked list by ascending order. */
void ll_insert_asc(List *l, void* value, ListNodeComparator ll_node_comp) {
	List *p;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (ll_node_comp((*p)->value, value) > 0) {
			List tmp = *p;
			List new = ll_new_node(value,tmp);
			*p = new;
			break;
		}
	}
	if ((*p) == NULL)
		(*p) = ll_new_node(value, NULL);
}

/* Inserts a new element on the list by ascending order. */
void insert_asc(LinkedList l, void* value) {
	if (l != NULL) {
		ll_insert_asc(&l->list, value, l->ll_node_comp);
		size++;
	}
}

/* Inserts a new element on linked list by descending order */
void ll_insert_desc(List *l, void* value, ListNodeComparator ll_node_comp) {
	List *p;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (ll_node_comp(value, (*p)->value) > 0) {
			List tmp = (*p);
			List new = ll_new_node(value,tmp);
			(*p) = new;
			break;
		}
	}
	if ((*p) == NULL)
		(*p) = ll_new_node(value,NULL);
}

/* Inserts a new element on the list by descending order. */
void insert_desc(LinkedList l, void* value) {
	if (l != NULL) {
		ll_insert_desc(&l->list, value, l->ll_node_comp);
		size++;
	}
}

/* Deletes the specified value from linked list (first occurence), if exists. */
void ll_delete(List *l, void* value, ListNodeComparator ll_node_comp) {
	List *p;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (ll_node_comp((*p)->value, value) == 0){
			List del = (*p);
			(*p) = (*p)->next;
			free(del);
			break;
		}
	}
}

/* Deletes the specified value from the list, if exists. */
void delete(LinkedList l, void* value) {
	if (l != NULL) {
		ll_delete(&l->list, value, l->ll_node_comp);
		size--;
	}
}

/* Returns the number of elements in the list. */
int size(LinkedList l) {
	int size = 0;
	if (l != NULL)
		size = l->size;
	return size;
}

/* Determine of a value exists in the linked list. */
bool ll_contains(List *l, void* value, ListNodeComparator ll_node_comp) {
	List *p;
	bool enc = false;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (ll_node_comp((*p)->value, value) == 0){
			enc = true;
			break;
		}
	}
	return enc;
}

/* Determine of a value exists in the list. */
bool contains(LinkedList, void*) {
	if (l != NULL) {
		return ll_contains(&l->list, value, l->ll_node_comp);
}
