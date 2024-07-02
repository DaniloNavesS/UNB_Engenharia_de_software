#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **adj;
    int n;
} Grafo;

Grafo *cria_grafo(int n) {
    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo->n = n;
    grafo->adj = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        grafo->adj[i] = (int *)calloc(n, sizeof(int));
    }
    return grafo;
}

void inserir_aresta_grafo(Grafo *grafo, int n, int m) {
    grafo->adj[n][m] = 1;
    grafo->adj[m][n] = 1;
}

void liberar_grafo(Grafo *grafo) {
    for (int i = 0; i < grafo->n; i++) {
        free(grafo->adj[i]);
    }
    free(grafo->adj);
    free(grafo);
}

void marcar_perigo(Grafo *grafo, int local, int *perigos) {
    perigos[local] = 1;
    for (int i = 0; i < grafo->n; i++) {
        if (grafo->adj[local][i] == 1) {
            perigos[i] = 1;
        }
    }
}

int main() {
    int N, M, J;
    scanf("%d %d %d", &N, &M, &J);

    Grafo *grafo = cria_grafo(N);

    for (int i = 0; i < N; i++) {
        int A, num_vizinhos;
        scanf("%d", &A);
        scanf("%d", &num_vizinhos);
        for (int j = 0; j < num_vizinhos; j++) {
            int vizinho;
            scanf("%d", &vizinho);
            inserir_aresta_grafo(grafo, A, vizinho);
        }
    }

    int *perigos = (int *)calloc(N, sizeof(int));

    for (int i = 0; i < M; i++) {
        int local;
        scanf("%d", &local);
        marcar_perigo(grafo, local, perigos);
    }

    for (int i = 0; i < J; i++) {
        int consulta;
        scanf("%d", &consulta);
        if (perigos[consulta]) {
            printf("Eu vou estar la\n");
        } else {
            printf("Nao vou estar la\n");
        }
    }

    free(perigos);
    liberar_grafo(grafo);

    return 0;
}