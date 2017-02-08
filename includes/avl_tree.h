#ifndef AVL_TREE_HEADER
#define AVL_TREE_HEADER

#include <bool.h>
#include <stdlib.h>

typedef void* AVLNode;
typedef struct avltree* AVLTree;

/* Function that compares the nodes. Returns -1 if A<B, 0 if A==B or 1 if A>B */
typedef int (*AVLNodeComparator)(AVLNode, AVLNode);

/* Creates a new tree with the provided node comparator. */
AVLTree avl_create(AVLNodeComparator);

/* Destroys the tree. */
void avl_destroy(AVLTree);

/* Inserts a new element in the tree. Assumes that tree is a binary search tree. */
void avl_insert(AVLTree, AVLNode);

/* Deletes the specified value from the tree, if exists. */
void avl_delete(AVLTree, AVLNode);

/* Returns the number of elements in the tree. */
int avl_size(AVLTree);

/* Determine of a value exists in the tree. */
bool avl_contains(AVLTree, AVLNode);

/* Get values in the tree, executing a in order traversal. */
AVLNode* avl_inorder(AVLTree);

#endif
