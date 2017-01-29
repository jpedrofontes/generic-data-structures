#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "AVL.h"

/*implementação de uma árvore Adelson-Velskii Landis (árvore AVL)*/

/*Definição de um nodo da árvore*/
struct avlnode{


	char *dado; /*String que pretendemos comparar*/
	PtAVLNode PtEsq , PtDir; /*apontador para a parte esquerda e para a parte direita da árvore.*/
unsigned int Height; /*altura do nó*/

};

/*criar um nó decomposto da árvore*/

PtAVLNode AVLNodeCreate (char *dado, int tam){
	PtAVLNode Nodo = (PtAVLNode) malloc (sizeof (struct avlnode));
        if(Nodo==NULL) return NULL;
	Nodo->dado=(char *) calloc (tam , sizeof (char));
	strcpy(Nodo->dado,dado);
	Nodo->PtEsq =Nodo->PtDir = NULL;
	Nodo->Height =1;
return Nodo;
}


/*destruir um nodo, colocando-o em NULL*/
void AVLNodeDestroy (PtAVLNode* nodo){

	/*free((*nodo)->dado);*/
	free(*nodo);
	*nodo=NULL;

}

/*Consulta a altura da subárvore, se for NULL retorna 0, caso contrário retorna um inteiro positivo correspondente á altura (esta está sempre atualizada)*/
unsigned int AVLHeight (PtAVLNode elem){

    if(elem == NULL) return 0;
    return elem->Height;
}


/* ----------------INSERÇÃO DE ELEMENTOS---------------------*/

/*Rotação simples á direita*/
void SingleRightRotation(PtAVLNode *pnode){
 unsigned int LeftH, RightH; /*usar para guardar alturas*/

    PtAVLNode Node =(*pnode)->PtEsq;
	(*pnode)->PtEsq=Node->PtDir; Node->PtDir=*pnode;

/* atualiza a altura dos nós envolvidos na rotação */

    LeftH=AVLHeight((*pnode)->PtEsq);
    RightH=AVLHeight((*pnode)->PtDir);

    (*pnode)->Height= LeftH > RightH ? LeftH + 1 : RightH +1;

    LeftH=AVLHeight (Node->PtEsq);
    RightH= (*pnode)->Height; /*AVLHeight (Node->Ptdir);*/

    Node->Height = LeftH > RightH ? LeftH+1 : RightH +1;



/*No final substituimos o endereço, pois fica a apontar para a nova árvore construida através da rotação (e atualização de alturas) dos elementos que já possuía*/


    *pnode = Node; /*No inicio definimos o Node como um apontador para uma estrutura do tipo avlNode;*/

}



/*Rotação simples á esquerda; Processo análogo á rotação simples á esquerda.*/


void SingleLeftRotation(PtAVLNode *pnode){
   unsigned int LeftH,RightH;
   PtAVLNode Node = (*pnode)->PtDir;
   	(*pnode)->PtDir = Node->PtEsq; Node->PtEsq= *pnode;


/* atualizar alturas dos nós envolvidos na rotação*/
	LeftH=AVLHeight((*pnode)->PtEsq);
	RightH = AVLHeight ((*pnode)->PtDir);
	(*pnode) -> Height = LeftH > RightH ? LeftH +1 : RightH +1;

/* atualizar o nodo que rodou para cima, cuja sua esquerda agora é o nodo que foi atualizado já a sua altura em cima.*/

	LeftH = (*pnode) -> Height;
	RightH = AVLHeight(Node->PtDir);

	Node->Height = LeftH>RightH ? LeftH +1 : RightH +1; /*O nodo fica com altura = maior altura dos seus filhos +1.*/

*pnode=Node; /*No inicio definimos o Node como um apontador para uma estrutura do tipo avlNode;*/

}

/*Até aqui a compilar sem erros:

 Rotação dupla:



Direita-Esquerda:
implemeta-se a rotação dupla direita-esquerda. Quando se insere um novo elemento na subárvore direita do filho esquerdo do filho direito de um nó. O que provoca uma diferença de alturas das suas subárvores superior a uma unidade, o desequilíbrio é corrigido com a rotação à direita do seu filho direito seguida da sua rotação á esquerda.*/



void DoubleRightLeftRotation (PtAVLNode *pnode){
	SingleRightRotation (&(*pnode)->PtDir);
	SingleLeftRotation (pnode);


}



/*
Esquerda-Direita:
implemeta a rotação dupla à esquerda-direita. Quando se insere um novo elemento na subárvore esquerda do filho direito do filho esquerdo de um nó. que provoca uma diferença de alturas das suas subárvores superior a uma unidade.
p.s : entenda-se como subárvore esquerda , a parte esquerda da árvore (filho esquerdo do nó)
*/
void DoubleLeftRightRotation (PtAVLNode *pnode){

	SingleLeftRotation(&(*pnode)->PtEsq);
	SingleRightRotation(pnode);
}









/*Procedimento de reequilíbrio de um nó de uma árvore.*/

void Balance (PtAVLNode * pnode){
	unsigned int LeftH,RightH;

	if(*pnode == NULL) return;  /*sub-árvore vazia*/
	LeftH = AVLHeight ((*pnode)->PtEsq); /*altura da sub-árvore esquerda*/
	RightH = AVLHeight ((*pnode)->PtDir); /*altura da sub-árvore direita*/

	if (LeftH - RightH == 2) /*subárvore esquerda está desiquilibrada , ou seja, tem mais elementos do que o que deveria*/
	{
	    LeftH=AVLHeight ((*pnode)->PtEsq->PtEsq);
	    RightH = AVLHeight ((*pnode)->PtEsq->PtDir);
	    if(LeftH >=RightH) SingleRightRotation (pnode); /*verificar argumento, possível problema com apontadores aqui. */
	    else DoubleLeftRightRotation(pnode);
	}

	else if (RightH - LeftH ==2)
	     {
		LeftH =AVLHeight ((*pnode)->PtDir->PtEsq);
		RightH = AVLHeight ((*pnode)->PtDir->PtDir);
		if(RightH>=LeftH)  SingleLeftRotation (pnode);
		else DoubleRightLeftRotation(pnode);

	     }
	    else (*pnode)->Height = LeftH > RightH ? LeftH +1 : RightH +1; /* a árvore no fim fica sempre com mais um de altura, do máximo de altura dos seus 2 filhos.*/
}

/*Inserção na árvore:*/



void AVLInsert(PtAVLNode* raiz, char* elem, int tam){

	if(*raiz == NULL) *raiz = AVLNodeCreate(elem, tam); /*inserir o elemento */
	else {if( strcmp(((*raiz)->dado),elem) > 0) /*uso do strcmp para comparar as strings*/
			AVLInsert(&(*raiz)->PtEsq,elem, tam); /*iserir na parte esquerda da árvore*/
	     else {if (strcmp(((*raiz)->dado),elem)<0) /*uso do strcmp para comparar as strings*/
			AVLInsert(&(*raiz)->PtDir,elem, tam);  /*inserir na parte direita da árvore*/
		  else return;}} /*o elemento já existe*/


Balance(raiz); /*reequilibrar a árvore no fim*/

}

unsigned int AVLSize(PtAVLNode arvore){

	if(arvore==NULL) { return 0;}
	else return 1+ AVLSize (arvore->PtEsq) + AVLSize (arvore->PtDir);
}

unsigned int AVLHeight2(PtAVLNode arvore){
      unsigned int LeftHeight,RightHeight;

	if(arvore==NULL) return 0;
	else 	/*altura da parte esquerda*/
	{	LeftHeight = AVLHeight2 (arvore->PtEsq);
		/*altura da parte direita	*/
		RightHeight = AVLHeight2 (arvore->PtDir);
		/*retornar a maior altura da árvore*/
		if(LeftHeight > RightHeight) return 1+LeftHeight; else return 1+RightHeight;



	}
	}



int Balanceada(PtAVLNode arvore){
	PtAVLNode Left,Right;
	if(arvore==NULL) return 1;

	Left = arvore->PtEsq;
	Right = arvore->PtDir;
	if(abs(AVLHeight(Left) - AVLHeight(Right)) > 1) return 0; else return Balanceada(Left) || Balanceada(Right);


	/*passando esta parte, fazemos cópias para investigação*/



}



int ExisteAVL(PtAVLNode* raiz, char* elem){
         if(*raiz==NULL) return 0;

         if(strcmp(elem,(*raiz)->dado)==0) return 1; else{ if (strcmp(elem,(*raiz)->dado)>0) return ExisteAVL(&(*raiz)->PtDir,elem);
                                                        else return ExisteAVL(&(*raiz)->PtEsq,elem);}

      return 0;


}




PtAVLNode FindMin(PtAVLNode raiz){

         PtAVLNode Nodo = raiz;

         while(Nodo->PtEsq != NULL) Nodo =Nodo->PtEsq;
        return Nodo;  /*devolve um ponteiro para o elemento*/

}




void NodeDelete(PtAVLNode* algo);
void AVLRemove(PtAVLNode* raiz, char* elem){
         if(*raiz==NULL) return;

         else if (strcmp((*raiz)->dado,elem)<0) AVLRemove(&(*raiz)->PtDir,elem);
              else { printf("entrou no nodeDelete!!!\n");
                     *elem = *(*raiz)->dado;
                      NodeDelete(raiz);

                    }

Balance(raiz);

 }





void NodeDelete(PtAVLNode* raiz){

	PtAVLNode Nodo = *raiz;

	if(((*raiz)->PtEsq == NULL) && ((*raiz) -> PtDir == NULL)) AVLNodeDestroy(raiz); /*nó folha eliminar elemento*/
	else if((*raiz)->PtEsq==NULL) /*ligar á direita e eliminar o elemento*/
	     {
		*raiz = (*raiz)->PtDir; AVLNodeDestroy(&Nodo);
	     }

	    else if((*raiz)->PtDir ==NULL) /*ligar á esquerda e eliminar o elemento*/
		  {
		   *raiz = (*raiz)->PtEsq; AVLNodeDestroy(&Nodo);
		  }
		 else   /*Chegado a este caso é porque tem subárvores direita e esquerda */
		  { /*substituir pelo menor elemento da subárvore direita, de forma a manter a propriedade, e de seguida remover recursivamente o elemento usado na substituição.*/
/*o bug está aqui pois pretende-se copiar uma string toda	*/
		  (*raiz)->dado = FindMin((*raiz)->PtDir) -> dado;

		   /*remover o menor elemento da subárvore direita*/
		   AVLRemove(&((*raiz)->PtDir),((*raiz)->dado));

		  }

}

void AVLInorder(PtAVLNode *raiz, char *lista[], int *i)
{
	if ((*raiz) != NULL)
	{
		AVLInorder(&((*raiz)->PtEsq), lista, i);
		lista[(*i)++] = strdup((*raiz)->dado);
		AVLInorder(&((*raiz)->PtDir), lista, i);
	}
}

void AVLDestroy(PtAVLNode* raiz)
{
	if((*raiz)!=NULL)
		{
 			AVLDestroy(&(*raiz)->PtEsq);
			AVLDestroy(&(*raiz)->PtDir);
			AVLNodeDestroy(raiz);
		}



}
