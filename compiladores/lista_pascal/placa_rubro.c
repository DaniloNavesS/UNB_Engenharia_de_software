#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    VERMELHO,
    PRETO
} Cor;

typedef struct No
{
    long long int valor;
    Cor cor;
    struct No *esq, *dir;
} No;

No *criarNo(int valor)
{
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->valor = valor;
    novoNo->cor = VERMELHO;
    novoNo->esq = novoNo->dir = NULL;
    return novoNo;
}

No *rotacaoEsquerda(No *h)
{
    No *x = h->dir;
    h->dir = x->esq;
    x->esq = h;
    x->cor = h->cor;
    h->cor = VERMELHO;
    return x;
}

No *rotacaoDireita(No *h)
{
    No *x = h->esq;
    h->esq = x->dir;
    x->dir = h;
    x->cor = h->cor;
    h->cor = VERMELHO;
    return x;
}

void inverterCores(No *h)
{
    h->cor = VERMELHO;
    h->esq->cor = PRETO;
    h->dir->cor = PRETO;
}

No *inserir(No *h, int valor)
{
    if (h == NULL)
        return criarNo(valor);

    if (valor < h->valor)
        h->esq = inserir(h->esq, valor);
    else if (valor > h->valor)
        h->dir = inserir(h->dir, valor);

    if (h->dir != NULL && h->dir->cor == VERMELHO && (h->esq == NULL || h->esq->cor == PRETO))
        h = rotacaoEsquerda(h);
    if (h->esq != NULL && h->esq->cor == VERMELHO && h->esq->esq != NULL && h->esq->esq->cor == VERMELHO)
        h = rotacaoDireita(h);
    if (h->esq != NULL && h->esq->cor == VERMELHO && h->dir != NULL && h->dir->cor == VERMELHO)
        inverterCores(h);

    return h;
}

No *inserirRubroNegra(No *raiz, int valor)
{
    raiz = inserir(raiz, valor);
    raiz->cor = PRETO;
    return raiz;
}

void em_ordem(No *raiz, int n) {
  if (raiz == NULL) {
    printf("VAZIO\n");
    return;
  }

 // No **pilha = malloc(sizeof(No) * 10000);
  No *pilha[101];
  int top = 0;
  int count = 0;

  while (count < n && (raiz != NULL || top > 0)) {

    while (raiz != NULL) {
      pilha[top++] = raiz;
      raiz = raiz->esq;
    }

    raiz = pilha[--top];

    printf("%lld ", raiz->valor);
    count++;
    raiz = raiz->dir;
  }
  printf("\n");
}



int main()
{
    No *arvore = NULL;
    long long int aux;
    int opcao;

    while (scanf("%d %lld", &opcao, &aux) != EOF)
    {
        if (opcao == 1)
        {
            arvore = inserirRubroNegra(arvore,aux);
        }else
        {
          em_ordem(arvore, aux);
        }
    }

    free(arvore);

    return 0;
}
