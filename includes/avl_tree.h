#ifndef AVL_TREE_HEADER
#define AVL_TREE_HEADER

#include <bool.h>
#include <stdlib.h>

typedef struct avltree* AVLTree;

/* Function that compares the nodes. Returns -1 if A<B, 0 if A==B or 1 if A>B */
typedef int (*AVLNodeComparator)(void*, void*);

/* Creates a new tree with the provided node comparator. */
AVLTree avl_create(AVLNodeComparator);

/* Destroys the tree. */
void avl_destroy(AVLTree);

/* Inserts a new element in the tree. Assumes that tree is a binary search tree. */
void insert(AVLTree, void*);

/* Deletes the specified value from the tree, if exists. */
void delete(AVLTree, void*);

/* Returns the number of elements in the tree. */
int size(AVLTree);

/* Determine of a value exists in the tree. */
bool contains(AVLTree, void*);

/* Get values in the tree, executing a in order traversal. */
void** inorder(AVLTree);

#endif
