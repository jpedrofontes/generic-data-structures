#include <bool.h>
#include <stdio.h>
#include <string.h>

#include <avl_tree.h>
#include <linked_list.h>
#include <queue.h>
#include <stack.h>

/* Functions that compares 2 strings adapted to void* */
int strcomp(void* data1, void* data2) {
	return strcmp((char*) data1, (char *)data2);
}

/* Main test function */
int main() {
	#ifdef AVL
		AVLTree tree = avl_create(&strcomp);
		char* str1 = strdup("ohhh");
	puts("A INSERIR");
		avl_insert(tree, (void*) str1);
	puts("INSERIU");
	puts("A INSERIR");
		char* str2 = strdup("bff");
		avl_insert(tree, (void*) str2);
	puts("INSERIU");
	puts("A INSERIR");
		char* str3 = strdup("<3");
		avl_insert(tree, (void*) str3);
	puts("INSERIU");
	puts("A INSERIR");
		char* str4 = strdup("asqueroso");
		avl_insert(tree, (void*) str4);
	puts("INSERIU");
	puts("A INSERIR");
		avl_insert(tree, (void*) str4);
	puts("INSERIU");
	puts("A INSERIR");
		printf("%d\n", avl_size(tree));
		avl_destroy(tree);

	#endif
	#ifdef LIST
		// ...

	#endif
	#ifdef QUEUE
		// ...

	#endif
	#ifdef STACK
		// ...

	#endif
	return 0;
}
