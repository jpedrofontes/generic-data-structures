#include <linked_list.h>

typedef struct node {
	ListNode value;
	struct node* next;
} *List;

struct linkedlist {
	List list;
	int size;
	ListNodeComparator node_comp;
};

/* Creates a new list with the provided node comparator. */
LinkedList list_create(ListNodeComparator node_comp) {
	LinkedList l = malloc(sizeof(struct linkedlist));
	l->list = NULL;
	l->size = 0;
	l->node_comp = node_comp;
	return l;
}

void ll_destroy(List* l) {
	List* p = l;
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
List new_node(ListNode value, List next_node) {
	List new = malloc(sizeof(struct node));
	new->value = value;
	new->next = next_node;
	return new;
}

void ll_insert(List* l, ListNode value) {
	List* p = l;
	List tmp = (*p);
	List new = new_node(value, tmp);
	(*p) = new;
}

/* Inserts a new element in the list. No order required. */
void list_insert(LinkedList l, ListNode value) {
	if (l != NULL) {
		ll_insert(&l->list, value);
		l->size++;
	}
}

void insert_asc(List* l, ListNode value, ListNodeComparator node_comp) {
	List* p;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (node_comp((*p)->value, value) > 0) {
			List tmp = *p;
			List new = new_node(value,tmp);
			*p = new;
			break;
		}
	}
	if ((*p) == NULL)
		(*p) = new_node(value, NULL);
}

/* Inserts a new element on the list by ascending order. */
void list_insert_asc(LinkedList l, ListNode value) {
	if (l != NULL) {
		insert_asc(&l->list, value, l->node_comp);
		l->size++;
	}
}

void insert_desc(List* l, ListNode value, ListNodeComparator node_comp) {
	List* p;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (node_comp(value, (*p)->value) > 0) {
			List tmp = (*p);
			List new = new_node(value,tmp);
			(*p) = new;
			break;
		}
	}
	if ((*p) == NULL)
		(*p) = new_node(value,NULL);
}

/* Inserts a new element on the list by descending order. */
void list_insert_desc(LinkedList l, ListNode value) {
	if (l != NULL) {
		insert_desc(&l->list, value, l->node_comp);
		l->size++;
	}
}

void delete(List* l, ListNode value, ListNodeComparator node_comp) {
	List* p;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (node_comp((*p)->value, value) == 0){
			List del = (*p);
			(*p) = (*p)->next;
			free(del);
			break;
		}
	}
}

/* Deletes the specified value from the list, if exists. */
void list_delete(LinkedList l, ListNode value) {
	if (l != NULL) {
		delete(&l->list, value, l->node_comp);
		l->size--;
	}
}

/* Returns the number of elements in the list. */
int list_size(LinkedList l) {
	int size = 0;
	if (l != NULL)
		size = l->size;
	return size;
}

bool ll_contains(List* l, ListNode value, ListNodeComparator node_comp) {
	List* p;
	bool enc = false;
	for (p = l; (*p) != NULL; p = &((*p)->next)) {
		if (node_comp((*p)->value, value) == 0){
			enc = true;
			break;
		}
	}
	return enc;
}

/* Determine of a value exists in the list. */
bool list_contains(LinkedList l, ListNode value) {
	if (l != NULL) {
		return ll_contains(&l->list, value, l->node_comp);
	}
	return false;
}

void to_array(List* l, ListNode* list, int* i) {
	List* p;
	for (p = l; (*p) != NULL; p = &((*p)->next))
		list[(*i)++] = (*p)->value;
}

ListNode* list_to_array(LinkedList l) {
	int i=0;
	ListNode* list = malloc(list_size(l) * sizeof(ListNode));
	to_array(&l->list, list, &i);
	return list;
}
