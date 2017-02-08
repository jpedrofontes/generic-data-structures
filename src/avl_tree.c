#include "avl_tree.h"

typedef struct node {
	AVLNode value;
	int height;
	struct node *left, *right;
} *Node;

struct avltree {
	Node tree;
	int size;
	AVLNodeComparator avl_node_comp;
};

/* Creates a new tree with the provided node comparator. */
AVLTree avl_create(AVLNodeComparator comp) {
	AVLTree t = malloc(sizeof(struct avltree));
	t->size = 0;
	t->avl_node_comp = comp;
	return t;
}

void tree_destroy(Node* t) {
	Node* p = t;
	while ((*p)) {
		Node next = (*p)->next;
		free(*p);
		(*p) = NULL;
		p = &(next);
	}
}

/* Destroys the tree. */
void avl_destroy(AVLTree t) {
	if (t != NULL) {
		tree_destroy(&t->tree);
		free(t);
		t = NULL;
	}
}

/* Creates a new tree element. */
Node avl_new_node(AVLNode value) {
 	Node new = malloc(sizeof(struct node));
	new->value = value;
	new->left = NULL;
	new->right = NULL;
	return new;
}

unsigned int avl_height(Node value) {
    if (value == NULL)
		return 0;
    return value->height;
}

void avl_single_right_rotation(Node *tree){
 	unsigned int left_height, right_height;

    Node Node = (*tree)->left;
	(*tree)->left = Node->right;
	Node->right = *tree;

    left_height = avl_height((*tree)->left);
    right_height = avl_height((*tree)->right);

    (*tree)->height= left_height > right_height ? left_height + 1 : right_height + 1;

    left_height = avl_height (Node->left);
    right_height = (*tree)->height;

    Node->height = left_height > right_height ? left_height + 1 : right_height + 1;
    *tree = Node;
}

void avl_single_left_rotation(Node *tree){
   	unsigned int left_height,right_height;

   	Node Node = (*tree)->right;
   	(*tree)->right = Node->left;
	Node->left = *tree;

	left_height = avl_height((*tree)->left);
	right_height = avl_height ((*tree)->right);

	(*tree)->height = left_height > right_height ? left_height + 1 : right_height + 1;

	left_height = (*tree)->height;
	right_height = avl_height(Node->right);

	Node->height = left_height > right_height ? left_height + 1 : right_height + 1;
	*tree=Node;
}

void avl_double_right_left_rotation(Node *tree){
	avl_single_right_rotation(&(*tree)->right);
	avl_single_left_rotation(tree);
}

void avl_double_left_right_rotation(Node *tree){
	avl_single_left_rotation(&(*tree)->left);
	avl_single_right_rotation(tree);
}

void avl_balance(Node* tree){
	unsigned int left_height,right_height;

	if (*tree == NULL)
		return;

	left_height = avl_height ((*tree)->left);
	right_height = avl_height ((*tree)->right);

	if (left_height - right_height == 2) {
		left_height = avl_height ((*tree)->left->left);
		right_height = avl_height ((*tree)->left->right);

		if(left_height >=right_height)
			avl_single_right_rotation (tree);
		else
			avl_double_left_right_rotation(tree);
	}
	else if (right_height - left_height ==2) {
		left_height = avl_height ((*tree)->right->left);
		right_height = avl_height ((*tree)->right->right);

		if (right_height>=left_height)
			avl_single_left_rotation (tree);
		else
			avl_double_right_left_rotation(tree);
	}
	else
		(*tree)->height = left_height > right_height ? left_height +1 : right_height +1;
}

bool avl_insert(Node* tree, AVLNode value, AVLNodeComparator avl_node_comp) {
	if (*tree == NULL)
	 	*tree = avl_new_node(value);
	else {
		if (avl_node_comp(((*tree)->value), value) > 0)
			avl_insert(&(*tree)->left, value, avl_node_comp);
		else {
			if (avl_node_comp(((*tree)->value), value) < 0)
				avl_insert(&(*tree)->right, value, avl_node_comp);
			else
				return false;
		}
	}
	avl_balance(tree);
	return true;
}

/* Inserts a new element in the tree. Assumes that tree is a binary search tree. */
void insert(AVLTree tree, AVLNode value) {
	if (tree != NULL) {
		bool ins = avl_insert(&tree->tree, value, tree->avl_node_comp);
		if (ins)
			tree->size++;
	}
}

/* Deletes the specified value from the tree, if exists. */
void delete(AVLTree, AVLNode);

/* Returns the number of elements in the tree. */
int size(AVLTree tree) {
	if (tree != NULL)
		return tree->size;
	return 0;
}

/* Determine of a value exists in the tree. */
bool avl_contains(Node* tree, AVLNode value, AVLNodeComparator avl_node_comp) {
	if (*tree == NULL)
		return false;
	if (avl_node_comp(value, (*tree)->value) == 0)
		return true;
	else {
		if (avl_node_comp(value, (*tree)->value) > 0)
			return avl_contains(&(*tree)->right, value, avl_node_comp);
		else
			return avl_contains(&(*tree)->left, value, avl_node_comp);
	}
 	return false;
}

bool contains(AVLTree tree, AVLNode value) {
	if (tree != NULL)
		return avl_contains(&tree->tree, value, tree->avl_node_comp);
	return false;
}

void avl_inorder(Node* tree, AVLNode* list, int* i) {
	if ((*tree) != NULL) {
		avl_inorder(&((*tree)->left), list, i);
		list[(*i)++] = (*tree)->value;
		avl_inorder(&((*tree)->right), list, i);
	}
}

/* Get values in the tree, executing a in order traversal. */
AVLNode* inorder(AVLTree tree) {
	int i=0;
	AVLNode* list = malloc(size(tree) * sizeof(AVLNode));
	avl_inorder(&tree->tree, list, &i);
	return list;
}
