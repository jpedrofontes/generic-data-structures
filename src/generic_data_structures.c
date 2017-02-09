#include <bool.h>
#include <stdio.h>
#include <string.h>

#include <avl_tree.h>
#include <linked_list.h>
#include <queue.h>
#include <stack.h>

/* Functions that compares 2 strings adapted to void*. */
int strcomp(void* data1, void* data2) {
	return strcmp((char*) data1, (char*) data2);
}

/* Main test function. */
int main() {
	#ifdef AVL
		/* Create AVL. */
		AVLTree tree = avl_create(&strcomp);
		/* Insert strings from file clients.txt. */
		char buffer[1024];
		FILE* clients_file = fopen("inputs/clients.txt", "r");
		/* Inserts on tree without garbage (\r or \n) FMM <3 */
		while ( fgets(buffer, 1024, clients_file) != NULL )
			avl_insert(tree, strdup(strtok(buffer, "\r\n")));
		/* Test size (it has to be 10 because all clients apear repeated). */
		printf("\nSIZE: %d\n\nVALUES:\n", avl_size(tree));
		/* Get all values in the tree. */
		int i;
		char** values = (char**) avl_inorder(tree);
		for (i=0; i < avl_size(tree); i++)
			printf("\t%s\n", values[i]);
		/* Tell me if 2 clients exist in the tree. */
		printf("\nClient FU469 exists? %s\n", avl_contains(tree, (void*) "FU469") == true ? "Yes" : "No");
		printf("Client CENAS exists? %s\n\n", avl_contains(tree, (void*) "CENAS") == true ? "Yes" : "No");
		/* Destroy the tree. */
		avl_destroy(tree);

	#endif
	#ifdef LIST
		/* Create 3 Lists. */
		LinkedList list_normal = list_create(&strcomp);
		LinkedList list_asc = list_create(&strcomp);
		LinkedList list_desc = list_create(&strcomp);
		/* Insert strings from file clients.txt. */
		char buffer[1024];
		FILE* clients_file = fopen("inputs/clients.txt", "r");
		/* Inserts on the lists without garbage (\r or \n) FMM <3 */
		while ( fgets(buffer, 1024, clients_file) != NULL ) {
			list_insert(list_normal, strdup(strtok(buffer, "\r\n")));
			list_insert_asc(list_asc, strdup(strtok(buffer, "\r\n")));
			list_insert_desc(list_desc, strdup(strtok(buffer, "\r\n")));
		}
		/* Test size (it has to be 20). */
		printf("\nSIZE OF normal: %d\n\nVALUES\tnormal\tasc\tdesc\n\n", list_size(list_normal));
		/* Get all values in the lists. */
		int i;
		char** values_normal = (char**) list_to_array(list_normal);
		char** values_asc = (char**) list_to_array(list_asc);
		char** values_desc = (char**) list_to_array(list_desc);
		for (i=0; i < list_size(list_normal); i++)
			printf("\t%s\t%s\t%s\n", values_normal[i], values_asc[i], values_desc[i]);
		/* Tell me if 2 clients exist in the normal list. */
		printf("\nClient FU469 exists on normal? %s\n", list_contains(list_normal, (void*) "FU469") == true ? "Yes" : "No");
		printf("Client CENAS exists on normal? %s\n\n", list_contains(list_normal, (void*) "CENAS") == true ? "Yes" : "No");
		/* Destroy the lists. */
		list_destroy(list_normal);
		list_destroy(list_asc);
		list_destroy(list_desc);

	#endif
	#ifdef QUEUE
		// ...

	#endif
	#ifdef STACK
		// ...

	#endif
	return 0;
}
