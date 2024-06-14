#include <stdio.h>

#define TAMANHO 10

unsigned long string_para_numero(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

struct No {
    int dado;
    struct No* prox;
};

struct No* tabelaHash[TAMANHO];

void inserir(int dado) {
    int indice = hashCode(dado); 

    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->dado = dado;
    novoNo->prox = NULL;


    if (tabelaHash[indice] == NULL) {
        tabelaHash[indice] = novoNo;
    } else {
        int novaIndice = (indice + 1) % TAMANHO; 

        while (novaIndice != indice) {
            if (tabelaHash[novaIndice] == NULL) { 
                tabelaHash[novaIndice] = novoNo;
                return;
            }
            novaIndice = (novaIndice + 1) % TAMANHO; 
        }
        printf("Tabela Hash cheia. Não é possível inserir o elemento %d.\n", dado);
    }
}

unsigned long hash_code(unsigned long id, int tam) {
    return id % tam;
}





int main() {
    unsigned char str[] = "maicom";
    unsigned long hash_value = string_para_numero(str);
    unsigned long hash_posicao = hash_code(hash_value, 2147483647);

    printf("O valor do hash para '%s' é %lu\n", str, hash_value);
    printf("A posicao e: %lu\n", hash_posicao);

    return 0;
}