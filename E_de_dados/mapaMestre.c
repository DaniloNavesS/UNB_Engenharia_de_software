#include <stdio.h>

#define MAX_X 100
#define MAX_Y 100

int main() {
    int x, y;
    char map[MAX_X][MAX_Y];
    
    // Leitura das dimensões do mapa
    scanf("%d", &x);
    scanf("%d", &y);
    
    // Leitura do mapa
    for (int i = 0; i < y; ++i) {
        scanf("%s", map[i]);
    }
    
    // Iniciando a partir do canto superior esquerdo (0, 0)
    int posX = 0, posY = 0;
    char direction = '>';  // Começando com direção para a direita
    
    // Inicializa um array para marcar visitados
    int visited[MAX_X][MAX_Y] = {0};
    
    while (1) {
        // Verifica se estamos fora dos limites do mapa
        if (posX < 0 || posX >= x || posY < 0 || posY >= y) {
            printf("!\n"); // Mapa é inválido (fora dos limites)
            return 0;
        }
        
        // Verifica se encontramos um baú
        if (map[posY][posX] == '*') {
            printf("*\n"); // Mapa é válido (encontrou o baú)
            return 0;
        }
        
        // Verifica se já visitamos este ponto
        if (visited[posY][posX]) {
            printf("!\n"); // Mapa é inválido (entrou em ciclo)
            return 0;
        }
        
        // Marca o ponto como visitado
        visited[posY][posX] = 1;
        
        // Move para a próxima posição de acordo com a direção
        switch (direction) {
            case '>':
                ++posX;
                break;
            case '<':
                --posX;
                break;
            case 'v':
                ++posY;
                break;
            case '^':
                --posY;
                break;
        }
        
        // Atualiza a direção se estiver em uma flecha
        if (map[posY][posX] == '>') direction = '>';
        else if (map[posY][posX] == '<') direction = '<';
        else if (map[posY][posX] == 'v') direction = 'v';
        else if (map[posY][posX] == '^') direction = '^';
    }
    
    return 0;
}