#include <stdio.h>
#include <stdlib.h>

#define TAM_HASH 2097169

unsigned long string_para_numero(unsigned char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

typedef struct No
{
    unsigned long id;
    struct No *esq, *dir;
} Alimento;

typedef struct No
{
    int id;
    struct Alimento *alimento;
} No;
 

int hash_function(int id)
{
    return id % TAM_HASH;
}

void inserir_na_arvore(Alimento *raiz, unsigned long id)
{
    Alimento *novo_no = malloc(sizeof(Alimento));
    novo_no->id = id;

    if (id < raiz->id)
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

void inserir_na_hash(No *hash,int id,unsigned long alimento) {
    int pos = hash_function(id);
    unsigned long string_alimento = hash_djb2(alimento);

    if(hash[pos] == NULL) {
        Alimento *alimentoItem = malloc(alimento);

        alimentoItem->id = string_alimento;

        No *item = malloc(sizeof(No));
        item->id = id;
        item->alimento = alimentoItem;


        hash[pos] = item;
    }
    

}
int main()
{
    int id;
    char alimento[11];
    No *hash[TAM_HASH];



    while (scanf("%d %s", &id, alimento) != EOF)
    {
        unsigned long chave = hash_djb2((unsigned char *)alimento);
        No *aux = malloc(sizeof(No));

        inserir_na_hash(hash,id, alimento);

        if((aux = buscar_na_hash(id)) != NULL) {
            printf("id: %d\n",aux->id);
        }
    }

    return 0;
}