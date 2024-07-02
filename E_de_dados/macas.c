#include <stdio.h>
#include <stdlib.h>

#define MAXN 500000

typedef struct {
    int type;
    int left;
    int right;
} Node;

Node tree[MAXN + 1];
int greenCount[MAXN + 1];
int redCount[MAXN + 1];

void bfs(int N) {
    int queue[MAXN + 1];
    int front = 0, back = 0;

    queue[back++] = 1;
    int level = 0;

    while (front < back) {
        int nodesAtCurrentLevel = back - front;
        greenCount[level] = 0;
        redCount[level] = 0;

        for (int i = 0; i < nodesAtCurrentLevel; i++) {
            int nodeIndex = queue[front++];

            if (tree[nodeIndex].type == 1) {
                greenCount[level]++;
            } else if (tree[nodeIndex].type == 2) {
                redCount[level]++;
            }

            if (tree[nodeIndex].left != 0) {
                queue[back++] = tree[nodeIndex].left;
            }
            if (tree[nodeIndex].right != 0) {
                queue[back++] = tree[nodeIndex].right;
            }
        }

        level++;
    }

    for (int i = 1; i < level; i++) {
        printf("%d %d\n", greenCount[i], redCount[i]);
    }
}

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 1; i <= N; i++) {
        if (i == 1) {
            int trunk, L0, R0;
            scanf("%d %d %d", &trunk, &L0, &R0);
            tree[1] = (Node) {0, L0, R0};
        } else {
            int type, left, right;
            scanf("%d %d %d", &type, &left, &right);
            tree[i] = (Node) {type, left, right};
        }
    }

    bfs(N);

    return 0;
}