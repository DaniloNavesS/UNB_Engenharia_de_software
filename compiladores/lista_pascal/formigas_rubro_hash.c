#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 2097169

typedef struct No {
  int id;
  struct No *esq, *dir;
} No;

No *hash = calloc(TAM_HASH, sizeof(No));

unsigned long hash_djb2(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

int hashCode(unsigned long chave) { return chave % TAM_HASH; }

// Função para inserir um elemento na tabela hash usando sondagem linear para
// tratar colisões
Hash *inserir(Hash **tabela, unsigned long dado) {
  int indice = hashCode(dado);

  Hash *novoNo = (Hash *)malloc(sizeof(Hash));
  novoNo->palavra = dado;
  novoNo->prox = NULL;

  if (tabela[indice] == NULL) {
    tabela[indice] = novoNo;
  } else {
    int novaIndice = (indice + 1) % TAM_HASH;

    while (novaIndice != indice) {
      if (tabela[novaIndice] == NULL) {
        tabela[novaIndice] = novoNo;
        return novoNo;
      }
      novaIndice = (novaIndice + 1) % TAM_HASH;
    }
    printf("Tabela Hash cheia. Não é possível inserir o elemento %lu.\n", dado);
    free(novoNo);
    return NULL;
  }
  return novoNo;
}

No *busca_formigueiro(No *r, int x) {
  if (r == NULL || r->id == x) {
    return r;
  } else {
    if (x < r->id) {
      return busca_formigueiro(r->esq, x);
    } else {
      return busca_formigueiro(r->dir, x);
    }
  }
}

No *inserir_formigueiro(No *r, int x, char *alimento) {
  if (r == NULL) {
    No *novo = malloc(sizeof(No));
    novo->id = x;
    novo->dir = NULL;
    novo->esq = NULL;

    novo->alimento_struct = calloc(TAM_HASH, sizeof(Hash *));

    Hash *hash =
        inserir(novo->alimento_struct, hash_djb2((unsigned char *)alimento));

    return novo;
  } else {
    if (x < r->id) {
      r->esq = inserir_formigueiro(r->esq, x, alimento);
    } else if (x > r->id) {
      r->dir = inserir_formigueiro(r->dir, x, alimento);
    }
    return r;
  }
}

int main() {
  int id;
  char alimento[11];
  No *formigueiro = NULL;

  while (scanf("%d %s", &id, alimento) != EOF) {
    unsigned long hash = hash_djb2((unsigned char *)alimento);

    No *aux = busca_formigueiro(formigueiro, id);

    if (aux == NULL) {
      formigueiro = inserir_formigueiro(formigueiro, id, alimento);
    } else {
      int posicao = hashCode(hash);

      if (aux->alimento_struct[posicao] != NULL) {
        printf("%d\n", id);
      } else {
        inserir(aux->alimento_struct, hash);
      }
    }
  }

  return 0;
}
