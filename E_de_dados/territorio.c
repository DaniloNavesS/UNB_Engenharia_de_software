#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int **adf;
    int n;
} Grafo;

Grafo *cria_grafo(int n)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->n = n;

    grafo->adf = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) grafo->adf[i] = calloc(n, sizeof(int));

    return grafo;
}

void inserir_aresta_grafo(Grafo *grafo, int n, int m)
{
    grafo->adf[n][m] = 1;
    grafo->adf[m][n] = 1;
}
