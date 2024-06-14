#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VERMELHO,
    PRETO
} Cor;

typedef struct No {
    char **alimento;
    int qntAlimentos;
    int id;
    Cor cor;
    struct No *esq, *dir;
} No;




No *busca(No *r, int x);

No *criarNo(int valor, char *alimento) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        return NULL;
    }
    novoNo->qntAlimentos = 1;
    novoNo->id = valor;
    
    novoNo->alimento = (char **)malloc(sizeof(char *));
    if (novoNo->alimento == NULL) {
        free(novoNo);
        return NULL;
    }
    
    novoNo->alimento[0] = (char *)malloc(strlen(alimento) + 1);
    if (novoNo->alimento[0] == NULL) {
        free(novoNo->alimento);
        free(novoNo);
        return NULL;
    }
    strcpy(novoNo->alimento[0], alimento);
    
    novoNo->cor = VERMELHO;
    novoNo->esq = novoNo->dir = NULL;
    return novoNo;
}

No *rotacaoEsquerda(No *h) {
    No *x = h->dir;
    h->dir = x->esq;
    x->esq = h;
    x->cor = h->cor;
    h->cor = VERMELHO;
    return x;
}

No *rotacaoDireita(No *h) {
    No *x = h->esq;
    h->esq = x->dir;
    x->dir = h;
    x->cor = h->cor;
    h->cor = VERMELHO;
    return x;
}

void inverterCores(No *h) {
    h->cor = VERMELHO;
    h->esq->cor = PRETO;
    h->dir->cor = PRETO;
}

No *inserir(No *h, int valor, char alimento[]) {
    if (h == NULL)
        return criarNo(valor, alimento);

    if (valor < h->id)
        h->esq = inserir(h->esq, valor, alimento);
    else if (valor > h->id)
        h->dir = inserir(h->dir, valor, alimento);
    else {
        h->qntAlimentos++;
        h->alimento = (char **)realloc(h->alimento, h->qntAlimentos * sizeof(char *));
        h->alimento[h->qntAlimentos - 1] = (char *)malloc(strlen(alimento) + 1);
        strcpy(h->alimento[h->qntAlimentos - 1], alimento);
    }

    if (h->dir != NULL && h->dir->cor == VERMELHO && (h->esq == NULL || h->esq->cor == PRETO))
        h = rotacaoEsquerda(h);
    if (h->esq != NULL && h->esq->cor == VERMELHO && h->esq->esq != NULL && h->esq->esq->cor == VERMELHO)
        h = rotacaoDireita(h);
    if (h->esq != NULL && h->esq->cor == VERMELHO && h->dir != NULL && h->dir->cor == VERMELHO)
        inverterCores(h);

    return h;
}

No *inserirRubroNegra(No *raiz, int valor, char *alimento) {
    raiz = inserir(raiz, valor, alimento);
    raiz->cor = PRETO;
    return raiz;
}

void em_ordem(No *raiz, int n) {
    if (raiz == NULL) {
        printf("VAZIO\n");
        return;
    }

    No *pilha[101];
    int top = 0;
    int count = 0;

    while (count < n && (raiz != NULL || top > 0)) {
        while (raiz != NULL) {
            pilha[top++] = raiz;
            raiz = raiz->esq;
        }

        raiz = pilha[--top];

        printf("%d ", raiz->id);
        count++;
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
        if(busca(formigueiro, id) == NULL) {
            formigueiro = inserirRubroNegra(formigueiro, id, alimento);
        } else if((aux = busca(formigueiro, id)) != NULL) {
             int verificador = 0;
            for (int i = 0; i < aux->qntAlimentos; i++) {
                if(strcmp(aux->alimento[i], alimento) == 0) {
                    verificador = 1;
                    printf("%d\n", aux->id);
                }
            }
            if (verificador == 0)
            {
                inserirRubroNegra(formigueiro, id, alimento);
            }
            
        }
    }
     //printf("Qnt: Alimentos: %d\n", aux->qntAlimentos);
}
