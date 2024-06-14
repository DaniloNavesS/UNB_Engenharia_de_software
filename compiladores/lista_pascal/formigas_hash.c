#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define HASH_SIZE 19001

typedef struct No {
    unsigned long *hash;
    int id;
    struct No *esq, *dir;
} No;

unsigned long hash_djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash * 33) + hash) + c;
    }

    return hash;
}

unsigned long hash_posicao(unsigned long id, int tam) {
    return id % tam;
}

No *criar_no(int id, unsigned long x) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar nó\n");
        return NULL;
    }
    novo->hash = calloc(HASH_SIZE, sizeof(unsigned long));
    if (novo->hash == NULL) {
        printf("Erro ao alocar vetor hash\n");
        free(novo);
        return NULL;
    }
    unsigned long posicao_hash = hash_posicao(x, HASH_SIZE);

    while (novo->hash[posicao_hash] != 0) {
        posicao_hash = (posicao_hash + 1) % HASH_SIZE;
    }

    novo->hash[posicao_hash] = x;
    novo->id = id;
    novo->esq = NULL;
    novo->dir = NULL;

    return novo;
}

No *inserir(No *raiz, int id, unsigned long x) {
    if (raiz == NULL) {
        return criar_no(id, x);
    }

    if (id < raiz->id) {
        raiz->esq = inserir(raiz->esq, id, x);
    } else if (id > raiz->id) {
        raiz->dir = inserir(raiz->dir, id, x);
    }
    return raiz;
}

No *busca(No *raiz, int id) {
    while (raiz != NULL && raiz->id != id) {
        if (id < raiz->id) {
            raiz = raiz->esq;
        } else {
            raiz = raiz->dir;
        }
    }
    return raiz;
}

void liberar_arvore(No *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq);
        liberar_arvore(raiz->dir);
        free(raiz->hash);
        free(raiz);
    }
}

int main() {
    int id;
    char alimento[11];
    No *formigueiro = NULL;

    while (scanf("%d %s", &id, alimento) != EOF) {
        unsigned long hash = hash_djb2((unsigned char*)alimento);
        No *aux = busca(formigueiro, id);
        
        if (aux == NULL) {
            formigueiro = inserir(formigueiro, id, hash);
        } else {
            unsigned long pos = hash_posicao(hash, HASH_SIZE);

            while (aux->hash[pos] != 0 && aux->hash[pos] != hash) {
                pos = (pos + 1) % HASH_SIZE;
            }

            if (aux->hash[pos] == hash) {
                printf("%d\n", id);
            } else {
                aux->hash[pos] = hash;
            }
        }
    }

    return 0;
}
