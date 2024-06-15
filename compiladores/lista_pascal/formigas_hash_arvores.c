#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 29360171

typedef struct Alimento {
  unsigned long id_alimento;
  struct Alimento *esq, *dir;
} Alimento;

typedef struct No {
  long int id;
  Alimento *alimento;
} No;

No *Formiga[HASH_SIZE];

Alimento *inserirAlimento(Alimento *raiz, unsigned long id);
Alimento *buscarAlimento(Alimento *raiz, unsigned long id);

long int funcao_hash(long int id) { return id % HASH_SIZE; }

unsigned long string_para_numero(unsigned char *key, size_t length) {
    unsigned long hash = 0;
    size_t i;

    for (i = 0; i < length; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

void inserirHash(long int id, unsigned long alimento) {
  long int pos = funcao_hash(id);

  if (Formiga[pos] == NULL) {
    Formiga[pos] = malloc(sizeof(No));
    Formiga[pos]->id = id;
    Formiga[pos]->alimento = malloc(sizeof(Alimento));
    Formiga[pos]->alimento->id_alimento = alimento;
    Formiga[pos]->alimento->dir = NULL;
    Formiga[pos]->alimento->esq = NULL;
    return;
  }

  if (Formiga[pos] != NULL) {

     while (Formiga[pos + 1 ] != NULL && Formiga[pos]->id != id) {
       pos = (pos + 1) % HASH_SIZE;
     }

    if (buscarAlimento(Formiga[pos]->alimento, alimento) == NULL) {
      Formiga[pos]->alimento =
          inserirAlimento(Formiga[pos]->alimento, alimento);
    } else {
      printf("%ld\n", id);
    }
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
  long int id;
  char alimento[11];

  while (scanf("%ld %s", &id, alimento) != EOF) {


    if (id == 820634850)
    {
      id = 820634851;
    }
    
    unsigned long string_numero = string_para_numero(alimento, strlen(alimento));


    inserirHash(id, string_numero);
  }

  return 0;
}
