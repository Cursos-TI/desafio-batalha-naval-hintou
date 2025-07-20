#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define OCUPADO 3
#define AFETADO 5
#define HABILIDADE_TAM 5

// Verifica se posição está dentro do tabuleiro
int dentro_limite(int linha, int coluna) {
    return linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO;
}

// Gera matriz de cone (aponta para baixo, centro no topo)
void gerar_matriz_cone(int matriz[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (j >= (HABILIDADE_TAM - 1) / 2 - i && j <= (HABILIDADE_TAM - 1) / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de cruz (centro horizontal e vertical)
void gerar_matriz_cruz(int matriz[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (i == HABILIDADE_TAM / 2 || j == HABILIDADE_TAM / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera matriz de octaedro (formato losango)
void gerar_matriz_octaedro(int matriz[HABILIDADE_TAM][HABILIDADE_TAM]) {
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (abs(i - HABILIDADE_TAM / 2) + abs(j - HABILIDADE_TAM / 2) <= HABILIDADE_TAM / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Aplica habilidade ao tabuleiro com base no centro
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                        int habilidade[HABILIDADE_TAM][HABILIDADE_TAM],
                        int origem_linha, int origem_coluna) {
    int offset = HABILIDADE_TAM / 2;
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origem_linha - offset + i;
                int coluna = origem_coluna - offset + j;
                if (dentro_limite(linha, coluna) && tabuleiro[linha][coluna] == 0) {
                    tabuleiro[linha][coluna] = AFETADO;
                }
            }
        }
    }
}

// Valida e posiciona navio
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int l, int c, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = l, coluna = c;
        if (!diagonal) {
            if (direcao == 0) coluna += i;
            else linha += i;
        } else {
            if (direcao == 0) { linha += i; coluna += i; }
            else { linha += i; coluna -= i; }
        }
        if (!dentro_limite(linha, coluna) || tabuleiro[linha][coluna] == OCUPADO)
            return 0;
    }
    return 1;
}

void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int l, int c, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = l, coluna = c;
        if (!diagonal) {
            if (direcao == 0) coluna += i;
            else linha += i;
        } else {
            if (direcao == 0) { linha += i; coluna += i; }
            else { linha += i; coluna -= i; }
        }
        tabuleiro[linha][coluna] = OCUPADO;
    }
}

// Exibe o tabuleiro no console
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nLegenda: 0 = Água, 3 = Navio, 5 = Área de Habilidade\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Define 4 navios: 2 lineares e 2 diagonais
    int navios[4][4] = {
        {2, 1, 0, 0},  // horizontal
        {5, 5, 1, 0},  // vertical
        {6, 0, 0, 1},  // diagonal \
        {0, 9, 1, 1}   // diagonal /
    };

    // Posiciona navios
    for (int i = 0; i < 4; i++) {
        int l = navios[i][0], c = navios[i][1], d = navios[i][2], diag = navios[i][3];
        if (pode_posicionar(tabuleiro, l, c, d, diag)) {
            posicionar_navio(tabuleiro, l, c, d, diag);
        } else {
            printf("Erro ao posicionar navio %d\n", i + 1);
            return 1;
        }
    }

    // Matrizes de habilidades
    int cone[HABILIDADE_TAM][HABILIDADE_TAM];
    int cruz[HABILIDADE_TAM][HABILIDADE_TAM];
    int octa[HABILIDADE_TAM][HABILIDADE_TAM];

    gerar_matriz_cone(cone);
    gerar_matriz_cruz(cruz);
    gerar_matriz_octaedro(octa);

    // Aplicar habilidades no tabuleiro (posições definidas no código)
    aplicar_habilidade(tabuleiro, cone, 1, 4);   // cone centrado em (1,4)
    aplicar_habilidade(tabuleiro, cruz, 5, 2);   // cruz centrado em (5,2)
    aplicar_habilidade(tabuleiro, octa, 8, 8);   // octaedro centrado em (8,8)

    // Exibir resultado final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
