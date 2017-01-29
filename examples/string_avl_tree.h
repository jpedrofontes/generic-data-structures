#ifndef __AVL__
#define __AVL__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*implementar ab dados*/


typedef struct avlnode* PtAVLNode;


/*
Retorna a altura de um dado nodo da árvore
*/
unsigned int AVLHeight (PtAVLNode elem);


/*
Insere um dado elemento na árvore balanceada, permanecendo esta balanceada após a inserção
*/
void AVLInsert(PtAVLNode* raiz, char* elem, int tam);


/*
Verifica se um dado elemento se encontra na árvore
*/
int ExisteAVL(PtAVLNode* raiz, char* elem);


/*
Remove um dado elemento da árvore balanceada, permanecendo esta balanceada após a remoção
*/
void AVLRemove(PtAVLNode* raiz, char* elem);

/*
Retorna o tamanho da arvore
*/
unsigned int AVLSize(PtAVLNode arvore);

void AVLInorder(PtAVLNode* arvore, char *lista[], int *indice);

void AVLDestroy(PtAVLNode* raiz);

#endif
