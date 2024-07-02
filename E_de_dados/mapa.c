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

int main () {
    int largura, altura, n;
    char entrada[1000];
    int x = 0, y = 0;
    int index;
    int passos = 0;
    scanf("%d", &largura);
    scanf("%d", &altura);

    if (largura >= altura) n = largura; else n = altura;
    
    Grafo *mapa = cria_grafo(n);

    inserir_aresta_grafo(mapa, x, y);

    scanf("%s", entrada);

    printf("%s", entrada);

    for (int i = 0; entrada[i] != '\0'; i++)
    {

        if (entrada[i] = '>') index = i;
        if (entrada[i] = '<') index = i;
        if (entrada[i] = 'v') index = i;
        if (entrada[i] = '^') index = i;

        
        while (entrada[i] == '.')
        {
            passos++;
            i++;
        }
    }
    
    
    printf("Passos dados: %d\n", passos);




    
    return 0;
}