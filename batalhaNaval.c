#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define OCUPADO 3

// Função para verificar se as posições estão livres e dentro do tabuleiro
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        // Direção: 0 = horizontal, 1 = vertical
        if (!diagonal) {
            if (direcao == 0) c += i;
            else l += i;
        } else {
            // Direção: 0 = diagonal principal (\), 1 = diagonal secundária (/)
            if (direcao == 0) {
                l += i;
                c += i;
            } else {
                l += i;
                c -= i;
            }
        }

        // Verifica se está fora dos limites
        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;

        // Verifica sobreposição
        if (tabuleiro[l][c] == OCUPADO)
            return 0;
    }

    return 1;
}

// Função para posicionar o navio
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (!diagonal) {
            if (direcao == 0) c += i;  // horizontal
            else l += i;               // vertical
        } else {
            if (direcao == 0) {        // diagonal principal (\)
                l += i;
                c += i;
            } else {                   // diagonal secundária (/)
                l += i;
                c -= i;
            }
        }

        tabuleiro[l][c] = OCUPADO;
    }
}

int main() {
    // Tabuleiro inicializado com 0 (água)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posicionamentos pré-definidos dos navios
    int navios[4][4] = {
         {2, 1, 0, 0},  // navio horizontal em (2,1)
         {5, 5, 1, 0},  // navio vertical em (5,5)
         {6, 0, 0, 1},  // navio diagonal \ em (6,0)
         {0, 9, 1, 1}   // navio diagonal / em (0,9)
    };

    // Tentar posicionar cada navio e validar
    for (int i = 0; i < 4; i++) {
        int linha = navios[i][0];
        int coluna = navios[i][1];
        int direcao = navios[i][2];
        int diagonal = navios[i][3];

        if (pode_posicionar(tabuleiro, linha, coluna, direcao, diagonal)) {
            posicionar_navio(tabuleiro, linha, coluna, direcao, diagonal);
        } else {
            printf("Erro ao posicionar navio %d. Posição inválida ou sobreposição.\n", i + 1);
            return 1;
        }
    }

    // Exibir tabuleiro formatado
    printf("Tabuleiro Batalha Naval (0 = água, 3 = navio):\n\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
