#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para um nó da árvore binária de alimentos
typedef struct Alimento {
    char nome[11]; // Nome do alimento (P)
    struct Alimento *esq, *dir;
} Alimento;

// Estrutura para um formigueiro na tabela hash
typedef struct Formigueiro {
    int localizacao; // Localização da colônia (C)
    struct Alimento *alimentos; // Árvore binária de alimentos
    struct Formigueiro *prox; // Para encadeamento na tabela hash
} Formigueiro;

// Tamanho da tabela hash
#define TAM_HASH 10007

// Função de hash simples para localização da colônia
int hash_function(int localizacao) {
    return localizacao % TAM_HASH;
}


// Função para inserir um alimento na árvore binária de um formigueiro
void inserir_alimento(Alimento **raiz, char *nome) {
    if (*raiz == NULL) {
        // Criar novo nó para o alimento
        Alimento *novo = (Alimento *) malloc(sizeof(Alimento));
        strcpy(novo->nome, nome);
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
    } else {
        int cmp = strcmp(nome, (*raiz)->nome);
        if (cmp < 0) {
            inserir_alimento(&((*raiz)->esq), nome);
        } else if (cmp > 0) {
            inserir_alimento(&((*raiz)->dir), nome);
        } else {
            // Alimento já existe, não fazer nada (não deve ocorrer pelo enunciado)
        }
    }
}

// Função para buscar um alimento na árvore binária de um formigueiro
Alimento *buscar_alimento(Alimento *raiz, char *nome) {
    if (raiz == NULL || strcmp(nome, raiz->nome) == 0) {
        return raiz;
    }
    if (strcmp(nome, raiz->nome) < 0) {
        return buscar_alimento(raiz->esq, nome);
    } else {
        return buscar_alimento(raiz->dir, nome);
    }
}

// Função para inserir um formigueiro na tabela hash
void inserir_formigueiro(Formigueiro **hash, int localizacao, char *nome_alimento) {
    int pos = hash_function(localizacao);

    // Verificar se o formigueiro já existe na posição pos
    Formigueiro *atual = hash[pos];
    while (atual != NULL) {
        if (atual->localizacao == localizacao) {
            // Formigueiro encontrado, inserir o alimento nele
            inserir_alimento(&(atual->alimentos), nome_alimento);
            return;
        }
        atual = atual->prox;
    }

    // Se o formigueiro não existir na posição pos, criar um novo
    Formigueiro *novo = (Formigueiro *) malloc(sizeof(Formigueiro));
    novo->localizacao = localizacao;
    novo->alimentos = NULL;
    inserir_alimento(&(novo->alimentos), nome_alimento);
    novo->prox = hash[pos];
    hash[pos] = novo;
}

// Função para buscar um formigueiro na tabela hash
Formigueiro *buscar_formigueiro(Formigueiro **hash, int localizacao) {
    int pos = hash_function(localizacao);

    Formigueiro *atual = hash[pos];
    while (atual != NULL) {
        if (atual->localizacao == localizacao) {
            return atual; // Formigueiro encontrado
        }
        atual = atual->prox;
    }
    return NULL; // Formigueiro não encontrado
}


int main() {
    // Inicializar a tabela hash de formigueiros
    Formigueiro *hash[TAM_HASH] = { NULL };

    int localizacao;
    char nome_alimento[11];

    while (scanf("%d %s", &localizacao, nome_alimento) != EOF) {
        // Inserir formigueiro ou adicionar alimento se já existir
        inserir_formigueiro(hash, localizacao, nome_alimento);
    }

    // Buscar duplicações de alimentos nos formigueiros
    for (int i = 0; i < TAM_HASH; ++i) {
        Formigueiro *atual = hash[i];
        while (atual != NULL) {
            Alimento *alimento = atual->alimentos;
            while (alimento != NULL) {
                Alimento *dup = buscar_alimento(alimento->dir, alimento->nome);
                if (dup != NULL) {
                    printf("%d\n", atual->localizacao);
                    return 0;
                }
                alimento = alimento->esq;
            }
            atual = atual->prox;
        }
    }

    return 0;
}
