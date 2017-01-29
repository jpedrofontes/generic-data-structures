#include <stdio.h>
#include <stdlib.h>
#define TAM 100
#define PILHA_CHEIA -1
#define PILHA_VAZIA -2

typedef struct pilha {
  int valores[TAM];
  int nr_elems;
} *Pilha;

Pilha criarPilha(void) {
  Pilha p = (Pilha)malloc(sizeof(struct pilha));
  if (p == NULL) 
    return NULL;
  p->nr_elems = 0;
  return p;
}

int push(Pilha p, int valor) {
  if (p->nr_elems == TAM)
    return PILHA_CHEIA;
  p->valores[p->nr_elems++] = valor;
  return 0;  
}

int pop(Pilha p) {
  if (p->nr_elems == 0)
    return PILHA_VAZIA;
  p->nr_elems--;
  return 0;
}

int top(Pilha p) {
  return p->valores[(p->nr_elems)-1];
}

void imprimirPilha(Pilha p){
  Pilha aux = p;
  for (int i = 0; i < aux->nr_elems; i++)
    printf("%d | ", aux->valores[i]);
}

int main(void){
  Pilha p = criarPilha();
  
  for (int i = 0; i < 50; i++)
    push(p,i);    
    
  for (int i = 0; i < 25; i++)
    pop(p);
    
  imprimirPilha(p);

  return 0;
}
