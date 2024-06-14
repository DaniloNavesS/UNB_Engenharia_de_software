#include <stdlib.h>
#include <stdio.h>

typedef struct No {
    unsigned long *hash;
    int id;
    struct No *esq, *dir;
} No;

unsigned long hash_djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

unsigned long hash_posicao(unsigned long id, int tam) {
    return id % tam;
}


void em_ordem(No *raiz, int n);

No *inserir(No *raiz,int id, unsigned long x);

No *inserir(No *raiz,int id, unsigned long x) {
  if (raiz == NULL) {
    No *novo = malloc(sizeof(No));
    novo->hash = malloc(sizeof(unsigned long) * 2147483647);
    unsigned long posicao_hash = hash_posicao(x, 2147483647);
    novo->hash[posicao_hash] = 1;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->id = id;

    return novo;

  } else {
    if (x < raiz->id) {
      raiz->esq = inserir(raiz->esq, id, x);
    } else if (x > raiz->id) {
      raiz->dir = inserir(raiz->dir, id, x);
    }
    return raiz;
  }
}

void em_ordem(No *raiz, int n) {
  if (raiz == NULL) {
    printf("VAZIO\n");
    return;
  }

  No *pilha[n];
  int top = 0;
  int count = 0;

  while ((raiz != NULL || top > 0)) {

    while (raiz != NULL) {
      pilha[top++] = raiz;
      raiz = raiz->esq;
    }

    raiz = pilha[--top];

    printf("%d ", raiz->id);
    count++;
    if (count >= n)
      break;
    raiz = raiz->dir;
  }
  printf("\n");
}

No *busca(No *r, int x) {
    if (r == NULL || r->id == x) {
        return r;
    } else {
        if (x < r->id) {
            return busca(r->esq, x);
        } else {
            return busca(r->dir, x);
        }
    }
}

int main() {
    int id;
    char alimento[11];
    No *formigueiro = NULL;
    No *aux = NULL;
    while (scanf("%d %s", &id, alimento) != EOF) {
        unsigned long hash = hash_djb2(alimento); 
        if(busca(formigueiro, id) == NULL) {
            formigueiro = inserir(formigueiro, id, hash);
        } else if((aux = busca(formigueiro, id)) != NULL) {
             int verificador = 0;
             unsigned long pos = hash_posicao(hash, 2147483647);
             if (aux->hash[pos] == hash)
             {
                printf("%d\n", id);
                verificador = 1;
             }
             
            if (verificador == 0)
            {
                inserir(formigueiro, id, hash);
            }
            
        }
    }
     //printf("Qnt: Alimentos: %d\n", aux->qntAlimentos);
}