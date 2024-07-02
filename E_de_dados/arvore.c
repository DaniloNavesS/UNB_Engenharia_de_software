#include <stdio.h>
#include <string.h>

#define MAX 300

int parent[MAX];
int rank[MAX];

void makeSet(int n) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int main() {
    int M, N;
    scanf("%d %d", &M, &N);

    makeSet(M);

    char name1[21], relation[21], name2[21];
    char names[MAX][21];
    int nameIndex = 0;

    for (int i = 0; i < N; ++i) {
        scanf("%s %s %s", name1, relation, name2);

        int index1 = -1, index2 = -1;
        for (int j = 0; j < nameIndex; ++j) {
            if (strcmp(names[j], name1) == 0) {
                index1 = j;
            }
            if (strcmp(names[j], name2) == 0) {
                index2 = j;
            }
        }

        if (index1 == -1) {
            strcpy(names[nameIndex], name1);
            index1 = nameIndex++;
        }
        if (index2 == -1) {
            strcpy(names[nameIndex], name2);
            index2 = nameIndex++;
        }

        unionSets(index1, index2);
    }

    int families = 0;
    int roots[MAX] = {0};
    for (int i = 0; i < M; ++i) {
        int root = find(i);
        if (!roots[root]) {
            roots[root] = 1;
            families++;
        }
    }

    printf("%d\n", families);

    return 0;
}