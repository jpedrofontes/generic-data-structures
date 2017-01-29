#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
#define FILA_CHEIA -1
#define FILA_VAZIA -2

typedef struct fila {
  int *valores;
  int cabeca;
  int cauda;
  int nr_elems;
} *Fila;

Fila criarFila(void) {
  Fila f = (Fila)malloc(sizeof(struct fila));
  if (f == NULL) 
    return NULL;
  
  f->valores = (int *)malloc(SIZE * sizeof(int));
  if (f->valores == NULL) {
    free(f);
    return NULL;
  }
  
  f->cabeca = 0;
  f->cauda = 0;
  f->nr_elems = 0;
  
  return f;
}

int enqueue(Fila f, int valor) {
  if (f->nr_elems == SIZE)
    return FILA_CHEIA;
  
  f->valores[f->cauda++] = valor;
  f->cauda %= SIZE;
  f->nr_elems++;

  return 0;
}

int dequeue(Fila f) {
  if (f->nr_elems == 0)
    return FILA_VAZIA;
  
  int del = f->valores[f->cabeca];
  
  f->cabeca++;
  f->cabeca %= SIZE;
  f->nr_elems--;
  return del;
}

void imprimirFila(Fila f) {
  for (int i = f->cabeca, k = 0; k < f->nr_elems; k++, i++)
    printf("%d | ", f->valores[i%SIZE]);
}

int main(void) {
  Fila q = criarFila();
  enqueue(q,3);
  enqueue(q,4);
  enqueue(q,5);
  enqueue(q,6);
  destruirFila(q);
  imprimirFila(q);
  printf("\n%d",enqueue(q,7)); //deve retornar -1
  printf("\n");
  enqueue(q,7);
  dequeue(q);
  dequeue(q);
  dequeue(q);
  printf("%d\n",dequeue(q)); //último elemento a ser removido: 6
  printf("%d\n",dequeue(q)); //deve retornar -2
  imprimirFila(q);
  return 0;
}
