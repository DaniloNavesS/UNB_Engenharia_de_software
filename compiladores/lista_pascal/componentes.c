#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int elemento;
  struct No *esq, *dir;
} No;

No *inserirElemento(No *raiz, int id) {
  if (raiz == NULL) {
    No *novo = malloc(sizeof(No));
    novo->elemento = id;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
  } else {
    if (id < raiz->elemento) {
      raiz->esq = inserirElemento(raiz->esq, id);
    } else if (id > raiz->elemento) {
      raiz->dir = inserirElemento(raiz->dir, id);
    }
    return raiz;
  }
}

No *buscarElemento(No *raiz, int id) {
  if (raiz == NULL || raiz->elemento == id) {
    return raiz;
  } else {
    if (id < raiz->elemento) {
      buscarElemento(raiz->esq, id);
    } else {
      buscarElemento(raiz->dir, id);
    }
  }
}

No *BuscarMenor(No *r) {
  if (r == NULL) {
    return 0;
  }

  if (r->esq == NULL) {
    return r;
  }

  if (r->esq != NULL) {
    BuscarMenor(r->esq);
  }
}

No *encontrarMinimo(No *r) {
  No *atual = r->esq;

  while (atual->dir != NULL)
    atual = atual->dir;
  return atual;
}

No *remover(No *r, int x) {
  if (r == NULL)
    return NULL;

  if (x < r->elemento)
    r->esq = remover(r->esq, x);
  else if (x > r->elemento)
    r->dir = remover(r->dir, x);
  else {
    if (r->esq == NULL) {
      No *temp = r->dir;
      free(r);
      return temp;
    } else if (r->dir == NULL) {
      No *temp = r->esq;
      free(r);
      return temp;
    }
    No *temp = encontrarMinimo(r);
    r->elemento = temp->elemento;
    r->esq = remover(r->esq, temp->elemento);
  }
  return r;
}

int main() {
  No *tuboA;
  No *tuboB;
  No *mistura;
  int N, X;

  scanf("%d %d", &N, &X);

  for (int i = 0; i < N; i++) {

    int auxEntrada;

    scanf("%d", &auxEntrada);

    inserirElemento(tuboA, auxEntrada);
  }

  No *aux = BuscarMenor(tuboA);

  tuboB = inserirElemento(tuboB, aux->elemento);
  remover(Tubo, int x)

      return 0;
}
