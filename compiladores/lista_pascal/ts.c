#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 2097169

typedef struct Alimento {
  unsigned long id_alimento;
  struct Alimento *esq, *dir;
} Alimento;

typedef struct No {
  int id;
  Alimento *alimento;
  struct No *prox; // Para encadeamento na tabela hash
} No;

No *Formiga[HASH_SIZE];

Alimento *inserirAlimento(Alimento *raiz, unsigned long id);
Alimento *buscarAlimento(Alimento *raiz, unsigned long id);

int funcao_hash(int id) { return id % HASH_SIZE; }

unsigned long string_para_numero(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

void inserirHash(int id, unsigned long alimento) {
  int pos = funcao_hash(id);

  No *novo = malloc(sizeof(No));
  novo->id = id;
  novo->alimento = malloc(sizeof(Alimento));
  novo->alimento->id_alimento = alimento;
  novo->alimento->dir = NULL;
  novo->alimento->esq = NULL;
  novo->prox = NULL;

  // Insere o novo elemento no início da lista encadeada na posição da tabela
  // hash
  if (Formiga[pos] == NULL) {
    Formiga[pos] = novo;
  } else {
    novo->prox = Formiga[pos];
    Formiga[pos] = novo;
  }
}

Alimento *inserirAlimento(Alimento *raiz, unsigned long id) {
  if (raiz == NULL) {
    Alimento *novo = malloc(sizeof(Alimento));
    novo->id_alimento = id;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
  } else {
    if (id < raiz->id_alimento) {
      raiz->esq = inserirAlimento(raiz->esq, id);
    } else if (id > raiz->id_alimento) {
      raiz->dir = inserirAlimento(raiz->dir, id);
    }
    return raiz;
  }
}

Alimento *buscarAlimento(Alimento *raiz, unsigned long id) {
  if (raiz == NULL || raiz->id_alimento == id) {
    return raiz;
  } else {
    if (id < raiz->id_alimento) {
      buscarAlimento(raiz->esq, id);
    } else {
      buscarAlimento(raiz->dir, id);
    }
  }
}

int main() {
  int id;
  char alimento[11];

  while (scanf("%d %s", &id, alimento) != EOF) {
    unsigned long string_numero = string_para_numero((unsigned char *)alimento);

    inserirHash(id, string_numero);
  }

  return 0;
}
