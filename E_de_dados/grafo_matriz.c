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

int mais_popular(Grafo *grafo)
{
    int grau_max = 0, grau, v_max;

    for (int i = 0; i < grafo->n; i++)
    {
        grau = 0;
        for (int j = 0; j < grafo->n; j++)
        {
            if (grafo->adf[i][j] == 1)
                grau++;
        }

        if (grau > grau_max)
        {
            grau_max = grau;
            v_max = i;
        }
    }

    return v_max;
}

int *bfs(Grafo *grafo, int v) {
    int *pai = malloc(grafo->n * sizeof(int));
    for (int i = 0; i < grafo->n; i++) pai[i] = -1;
    pai[v];
    enfileira(v);

    while (!fila_vazia())
    {
        v = desinfileira();
        for (int i = 0; i < grafo->n; i++)
        {
            if (grafo->adf[v][i] && pai[i] != -1)
            {
                pai[i] = v;
                enfileira(i);
            }
            
        }
        
    }
    
    return pai;
    
} 

void dfs(Grafo *grafo, int *pai, int p, int v) {
    pai[v] = p;

    for (int i = 0; i < grafo->n; i++)
    {
        if(grafo->adf[v][i] && pai[i] == -1) dfs(grafo, pai, v, i);
    }
    
}

int *caminho(Grafo *grafo, int start) {
    int *pai = malloc(grafo->n * sizeof(int));

    for (int i = 0; i < grafo->n; i++) pai[i] = -1;

    dfs(grafo, pai, start, start);
    

    return pai;
}

int main(int argc, char const *argv[])
{
    Grafo *grafo = cria_grafo(6);

    grafo->adf[1][3] = 1;
    grafo->adf[1][4] = 1;
    grafo->adf[3][1] = 1;
    grafo->adf[5][2] = 1;
    inserir_aresta_grafo(grafo, 5, 5);
    grafo->adf[5][1] = 1;

    printf("%d\n", mais_popular(grafo));
    
    return 0;
}
