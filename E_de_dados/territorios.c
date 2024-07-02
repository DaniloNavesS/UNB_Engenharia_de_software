#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000

typedef struct {
    int u, v;
} Edge;

Edge edges[2000000];
int head[MAXN + 1];
int nextEdge[2000000];
int totalEdges;
int visited[MAXN + 1];

void addEdge(int u, int v) {
    edges[totalEdges].u = u;
    edges[totalEdges].v = v;
    nextEdge[totalEdges] = head[u];
    head[u] = totalEdges++;
}

void dfs(int node, int *territoryOR) {
    visited[node] = 1;
    *territoryOR |= node;
    for (int e = head[node]; e != -1; e = nextEdge[e]) {
        int v = edges[e].v;
        if (!visited[v]) {
            dfs(v, territoryOR);
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; ++i) {
        head[i] = -1;
    }

    totalEdges = 0;

    for (int i = 0; i < M; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    int totalPrice = 0;

    for (int i = 1; i <= N; ++i) {
        if (!visited[i]) {
            int territoryOR = 0;
            dfs(i, &territoryOR);
            totalPrice ^= territoryOR;
        }
    }

    printf("%d\n", totalPrice);

    return 0;
}