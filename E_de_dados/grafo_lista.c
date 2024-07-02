#include <stdio.h>
#include <stdio.h>

typedef struct {
    int v;
    struct No *prox
}No;

typedef struct
{
    int *adf;
    int n;
} Grafo;

Grafo *cria_grafo(int n)
{
    Grafo *grafo = malloc(sizeof(Grafo));
    grafo->adf = calloc(n, sizeof(No));
    grafo->n = n;
    return grafo;
}

int main(int argc, char const *argv[])
{

    return 0;
}
