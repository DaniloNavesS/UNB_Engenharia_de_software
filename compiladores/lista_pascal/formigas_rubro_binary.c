#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    VERMELHO,
    PRETO
} Cor;

typedef struct Alimento {
    unsigned long string_valor;
    struct Alimento *esq, *dir;
}Alimento;

unsigned long hash_djb2(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash * 33) + hash) + c;
    }

    return hash;
}

typedef struct No {
    Alimento *alimento_struct;
    int id;
    Cor cor;
    struct No *esq, *dir;
} No;

Alimento *buscaAlimento(Alimento *r, unsigned long x) {
    if (r == NULL || r->string_valor == x) {
        return r;
    } else {
        if (x < r->string_valor) {
            return buscaAlimento(r->esq, x);
        } else {
            return buscaAlimento(r->dir, x);
        }
    }
}

Alimento *inserirAlimento (Alimento *r, unsigned long x) {
   if (r == NULL) {
      Alimento *novo = malloc(sizeof(Alimento));
      novo->string_valor = x;
      novo->dir = NULL;
      novo->esq = NULL;
      return novo;
   } else {
      if (x < r->string_valor) {
         r->esq = inserirAlimento(r->esq, x);
      } else if(x > r->string_valor) {
         r->dir = inserirAlimento(r->dir, x);
      }
      return r;
   }
}

No *busca(No *r, int x);

No *criarNo(int valor, char *alimento) {

    unsigned long string_in_number = hash_djb2(alimento);

    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        return NULL;
    }

    Alimento *string_alimento = (Alimento *)malloc(sizeof(Alimento));
    if (string_alimento == NULL) {
        return NULL;
    }

    novoNo->id = valor;
    
    novoNo->alimento_struct = inserirAlimento(string_alimento, string_in_number);

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
            unsigned long valor_string = hash_djb2(alimento);
             if(buscaAlimento(aux->alimento_struct, valor_string) != NULL) {
                printf("%d\n", id);
             } else {
                inserirAlimento(aux->alimento_struct, valor_string);
             }
            
        }
    }
}
