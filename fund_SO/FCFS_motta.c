#include <stdio.h>
#include <stdlib.h>

typedef struct Fila {
  int dado;
  int tempoRestante;
  int tempoTotal;
  struct Fila *prox;
} Fila;

Fila *fila = NULL;

void enfileira(int dado, int tempoRestante) {
  if (fila == NULL) {
    fila = malloc(sizeof(Fila));
    fila->dado = dado;
    fila->tempoRestante = tempoRestante;
    fila->tempoTotal = tempoRestante;
    fila->prox = NULL;
    return;
  }
  Fila *aux = fila;
  while (aux->prox != NULL)
    aux = aux->prox;

  aux->prox = malloc(sizeof(Fila));
  aux->prox->dado = dado;
  aux->prox->tempoRestante = tempoRestante;
  aux->prox->tempoTotal = tempoRestante;
  aux->prox->prox = NULL;
}

int desenfileira() {
  int dado;
  if (fila->prox == NULL) {
    dado = fila->dado;
    free(fila);
    return dado;
  }

  Fila *aux = fila->prox;
  dado = fila->dado;
  free(fila);
  fila = aux;

  return dado;
}

void joga_final() {
  if (fila == NULL)
    return;

  Fila *aux = fila;
  fila = fila->prox;
  Fila *aux2 = fila;

  while (aux2->prox != NULL)
    aux2 = aux2->prox;

  aux2->prox = aux;
}

int main() {
  int N;
  int tempoTotal = 0;
  int tempoRestanteTotal = 0;

  scanf("%d", &N);
  int *M = malloc(N * sizeof(int));
  int **matriz = malloc(N * sizeof(int *));

  for (int i = 0; i < N; i++) {
    scanf("%d", &M[i]);

    enfileira(i, M[i] * 10);
    tempoRestanteTotal += M[i] * 10;
    matriz[i] = malloc(M[i] * sizeof(int));
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M[i]; j++) {
      scanf("%d", &matriz[i][j]);
    }
  }

  while (tempoRestanteTotal > 0) {
    if (fila->tempoRestante == 0) {
      int printa = desenfileira();
      printf("%d (%d)\n", printa + 1, tempoTotal);
    }

    int mX = fila->dado;
    int mY = (fila->tempoTotal - fila->tempoRestante) / 10;

    if (matriz[mX][mY] == 0) {
      tempoTotal += 10;
      tempoRestanteTotal -= 10;
      fila->tempoRestante -= 10;
    } else if (matriz[mX][mY] == 1) {
      matriz[mX][mY] = 0;
      joga_final();
    }
  }

  int printa = desenfileira();
  printf("%d (%d)\n", printa + 1, tempoTotal);

  return 0;
}
