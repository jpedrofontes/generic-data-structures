#include <avl_tree.h>

typedef struct node {
	AVLNode value;
	int height;
	struct node *left, *right;
} *Node;

struct avltree {
	Node tree;
	int size;
	AVLNodeComparator node_comp;
};

/* Creates a new tree with the provided node comparator. */
AVLTree avl_create(AVLNodeComparator comp) {
	AVLTree t = malloc(sizeof(struct avltree));
	t->tree = NULL;
	t->size = 0;
	t->node_comp = comp;
	return t;
}

void destroy(Node* t) {
	if ((*t) != NULL) {
		destroy(&(*t)->left);
		destroy(&(*t)->right);
		free(*t);
		(*t) = NULL;
	}
}

/* Destroys the tree. */
void avl_destroy(AVLTree t) {
	if (t != NULL) {
		destroy(&t->tree);
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

void avl_single_right_rotation(Node* tree){
 	unsigned int left_height, right_height;

    Node node = (*tree)->left;
	(*tree)->left = node->right;
	node->right = *tree;

    left_height = avl_height((*tree)->left);
    right_height = avl_height((*tree)->right);

    (*tree)->height= left_height > right_height ? left_height + 1 : right_height + 1;

    left_height = avl_height(node->left);
    right_height = (*tree)->height;

    node->height = left_height > right_height ? left_height + 1 : right_height + 1;
    *tree = node;
}

void avl_single_left_rotation(Node* tree){
   	unsigned int left_height,right_height;

   	Node node = (*tree)->right;
   	(*tree)->right = node->left;
	node->left = *tree;

	left_height = avl_height((*tree)->left);
	right_height = avl_height((*tree)->right);

	(*tree)->height = left_height > right_height ? left_height + 1 : right_height + 1;

	left_height = (*tree)->height;
	right_height = avl_height(node->right);

	node->height = left_height > right_height ? left_height + 1 : right_height + 1;
	*tree = node;
}

void avl_double_right_left_rotation(Node* tree){
	avl_single_right_rotation(&(*tree)->right);
	avl_single_left_rotation(tree);
}

void avl_double_left_right_rotation(Node* tree){
	avl_single_left_rotation(&(*tree)->left);
	avl_single_right_rotation(tree);
}

void avl_balance(Node* tree){
	unsigned int left_height,right_height;

	if (*tree == NULL)
		return;

	left_height = avl_height((*tree)->left);
	right_height = avl_height((*tree)->right);

	if (left_height - right_height == 2) {
		left_height = avl_height((*tree)->left->left);
		right_height = avl_height((*tree)->left->right);

		if (left_height >= right_height)
			avl_single_right_rotation(tree);
		else
			avl_double_left_right_rotation(tree);
	}
	else if (right_height - left_height == 2) {
		left_height = avl_height((*tree)->right->left);
		right_height = avl_height((*tree)->right->right);

		if (right_height >= left_height)
			avl_single_left_rotation(tree);
		else
			avl_double_right_left_rotation(tree);
	}
	else
		(*tree)->height = left_height > right_height ? left_height + 1 : right_height + 1;
}

bool insert(Node* tree, AVLNode value, AVLNodeComparator node_comp) {
	bool ins = true;
	if (*tree == NULL)
	 	*tree = avl_new_node(value);
	else {
		if (node_comp(((*tree)->value), value) > 0)
			ins = insert(&(*tree)->left, value, node_comp);
		else {
			if (node_comp(((*tree)->value), value) < 0)
				ins = insert(&(*tree)->right, value, node_comp);
			else
				return false;
		}
	}
	if (ins == true)
		avl_balance(tree);
	return ins;
}

/* Inserts a new element in the tree. Assumes that tree is a binary search tree. */
void avl_insert(AVLTree tree, AVLNode value) {
	if (tree != NULL) {
		bool ins = insert(&tree->tree, value, tree->node_comp);
		if (ins == true)
			tree->size++;
	}
}

/* Deletes the specified value from the tree, if exists. */
void avl_delete(AVLTree, AVLNode);

/* Returns the number of elements in the tree. */
int avl_size(AVLTree tree) {
	if (tree != NULL)
		return tree->size;
	return 0;
}

/* Determine of a value exists in the tree. */
bool contains(Node* tree, AVLNode value, AVLNodeComparator node_comp) {
	if (*tree == NULL)
		return false;
	if (node_comp(value, (*tree)->value) == 0)
		return true;
	else {
		if (node_comp(value, (*tree)->value) > 0)
			return contains(&(*tree)->right, value, node_comp);
		else
			return contains(&(*tree)->left, value, node_comp);
	}
 	return false;
}

bool avl_contains(AVLTree tree, AVLNode value) {
	if (tree != NULL)
		return contains(&tree->tree, value, tree->node_comp);
	return false;
}

void inorder(Node* tree, AVLNode* list, int* i) {
	if ((*tree) != NULL) {
		inorder(&((*tree)->left), list, i);
		list[(*i)++] = (*tree)->value;
		inorder(&((*tree)->right), list, i);
	}
}

/* Get values in the tree, executing a in order traversal. */
AVLNode* avl_inorder(AVLTree tree) {
	int i=0;
	AVLNode* list = malloc(avl_size(tree) * sizeof(AVLNode));
	inorder(&tree->tree, list, &i);
	return list;
}
