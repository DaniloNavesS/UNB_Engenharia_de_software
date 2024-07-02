#include <stdio.h>
#include <stdbool.h>

#define MAX_N 2000

int adjMatrix[MAX_N][MAX_N];
bool canEnter[MAX_N];

int main() {
    int N, M, J;
    scanf("%d %d %d", &N, &M, &J);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            adjMatrix[i][j] = 0;
        }
    }
    
    for (int i = 0; i < N; i++) {
        int A, Aj;
        scanf("%d", &A);
        for (int j = 0; j < A; j++) {
            scanf("%d", &Aj);
            adjMatrix[i][Aj] = 1;
        }
    }

    int places[M];
    for (int i = 0; i < M; i++) {
        scanf("%d", &places[i]);
    }

    for (int i = 0; i < N; i++) {
        canEnter[i] = false;
    }

    for (int i = 0; i < M; i++) {
        int house = places[i];
        canEnter[house] = true;
        for (int j = 0; j < N; j++) {
            if (adjMatrix[house][j] == 1) {
                canEnter[j] = true;
            }
        }
    }

    for (int i = 0; i < J; i++) {
        int query;
        scanf("%d", &query);
        
        if (canEnter[query]) {
            printf("Eu vou estar la\n");
        } else {
            printf("Nao vou estar la\n");
        }
    }

    return 0;
}