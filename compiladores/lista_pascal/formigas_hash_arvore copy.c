#include <stdio.h>
#include <stdlib.h>

#define TAM_HASH 2097169


unsigned long hash_djb2(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

typedef struct No
{
    int id;
    struct No *esq, *dir;
} No;

No *hash[TAM_HASH];

int hash_function(int id)
{
    return id % TAM_HASH;
}

void inserir_na_hash(int id)
{
    int indice = hash_function(id);

    No *novo_no = (No *)malloc(sizeof(No));
    if (novo_no == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para novo nó.\n");
        exit(EXIT_FAILURE);
    }
    novo_no->id = id;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    if (hash[indice] == NULL)
    {
        hash[indice] = novo_no;
    }
    else
    {
        inserir_na_arvore(hash[indice], novo_no);
    }
}

void inserir_na_arvore(No *raiz, No *novo_no)
{
    if (novo_no->id < raiz->id)
    {
        if (raiz->esq == NULL)
        {
            raiz->esq = novo_no;
        }
        else
        {
            inserir_na_arvore(raiz->esq, novo_no);
        }
    }
    else
    {
        if (raiz->dir == NULL)
        {
            raiz->dir = novo_no;
        }
        else
        {
            inserir_na_arvore(raiz->dir, novo_no);
        }
    }
}

No *buscar_na_hash(int id)
{
    int indice = hash_function(id);

    // Procurar o nó na árvore binária correspondente ao índice
    return buscar_na_arvore(hash[indice], id);
}

No *buscar_na_arvore(No *raiz, int id)
{
    if (raiz == NULL || raiz->id == id)
    {
        return raiz;
    }

    if (id < raiz->id)
    {
        return buscar_na_arvore(raiz->esq, id);
    }
    else
    {
        return buscar_na_arvore(raiz->dir, id);
    }
}

int main()
{
    int id;
    char alimento[11];

    while (scanf("%d %s", &id, alimento) != EOF)
    {
        unsigned long chave = hash_djb2((unsigned char *)alimento);
        No *aux = malloc(sizeof(No));

        inserir_na_hash(id);

        if((aux = buscar_na_hash(id)) != NULL) {
            printf("id: %d\n",aux->id);
        }
    }

    return 0;
}