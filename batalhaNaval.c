#include <stdio.h>

#define TAB_SIZE 10    // Tamanho do tabuleiro 10x10
#define SHIP_SIZE 3    // Tamanho fixo dos navios

// Função para imprimir o tabuleiro
void imprimirTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro Batalha Naval:\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se uma posição está livre (0) no tabuleiro
int posicaoLivre(int tab[TAB_SIZE][TAB_SIZE], int linha, int coluna) {
    if (tab[linha][coluna] == 0) return 1;  // livre
    return 0;                              // ocupada
}

// Função para verificar sobreposição para um navio horizontal/vertical
int verificaSobreposicaoHV(int tab[TAB_SIZE][TAB_SIZE], int linha_inicial, int coluna_inicial, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < tamanho; i++) {
            if (!posicaoLivre(tab, linha_inicial, coluna_inicial + i)) {
                return 0; // sobreposição
            }
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < tamanho; i++) {
            if (!posicaoLivre(tab, linha_inicial + i, coluna_inicial)) {
                return 0; // sobreposição
            }
        }
    }
    return 1; // sem sobreposição
}

// Função para verificar sobreposição para um navio diagonal
int verificaSobreposicaoDiagonal(int tab[TAB_SIZE][TAB_SIZE], int linha_inicial, int coluna_inicial, int tamanho, char tipo) {
    // tipo 'D' para diagonal crescente (linha++, coluna++)
    // tipo 'A' para diagonal decrescente (linha++, coluna--)
    if (tipo == 'D') {
        for (int i = 0; i < tamanho; i++) {
            if (!posicaoLivre(tab, linha_inicial + i, coluna_inicial + i)) {
                return 0; // sobreposição
            }
        }
    } else if (tipo == 'A') {
        for (int i = 0; i < tamanho; i++) {
            if (!posicaoLivre(tab, linha_inicial + i, coluna_inicial - i)) {
                return 0; // sobreposição
            }
        }
    }
    return 1; // sem sobreposição
}

// Função para posicionar navio horizontal ou vertical no tabuleiro
void posicionarNavioHV(int tab[TAB_SIZE][TAB_SIZE], int linha_inicial, int coluna_inicial, int tamanho, char orientacao) {
    if (orientacao == 'H') {
        for (int i = 0; i < tamanho; i++) {
            tab[linha_inicial][coluna_inicial + i] = 3;
        }
    } else if (orientacao == 'V') {
        for (int i = 0; i < tamanho; i++) {
            tab[linha_inicial + i][coluna_inicial] = 3;
        }
    }
}

// Função para posicionar navio diagonal no tabuleiro
void posicionarNavioDiagonal(int tab[TAB_SIZE][TAB_SIZE], int linha_inicial, int coluna_inicial, int tamanho, char tipo) {
    if (tipo == 'D') { // diagonal crescente
        for (int i = 0; i < tamanho; i++) {
            tab[linha_inicial + i][coluna_inicial + i] = 3;
        }
    } else if (tipo == 'A') { // diagonal decrescente
        for (int i = 0; i < tamanho; i++) {
            tab[linha_inicial + i][coluna_inicial - i] = 3;
        }
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};  // Inicializa tabuleiro com água (0)

    // Definição dos navios - tamanho fixo 3
    // 1) Navio vertical
    int nv_linha = 1, nv_coluna = 1;

    // 2) Navio horizontal
    int nh_linha = 5, nh_coluna = 3;

    // 3) Navio diagonal crescente (linha++, coluna++)
    int ndc_linha = 0, ndc_coluna = 6;

    // 4) Navio diagonal decrescente (linha++, coluna--)
    int ndd_linha = 6, ndd_coluna = 9;

    // Validações dos limites e posicionamentos

    // Navio vertical - verifica limite
    if (nv_linha + SHIP_SIZE > TAB_SIZE) {
        printf("Erro: Navio vertical ultrapassa limites.\n");
        return 1;
    }

    // Navio horizontal - verifica limite
    if (nh_coluna + SHIP_SIZE > TAB_SIZE) {
        printf("Erro: Navio horizontal ultrapassa limites.\n");
        return 1;
    }

    // Navio diagonal crescente - verifica limite
    if (ndc_linha + SHIP_SIZE > TAB_SIZE || ndc_coluna + SHIP_SIZE > TAB_SIZE) {
        printf("Erro: Navio diagonal crescente ultrapassa limites.\n");
        return 1;
    }

    // Navio diagonal decrescente - verifica limite
    if (ndd_linha + SHIP_SIZE > TAB_SIZE || ndd_coluna - (SHIP_SIZE - 1) < 0) {
        printf("Erro: Navio diagonal decrescente ultrapassa limites.\n");
        return 1;
    }

    // Verifica sobreposição dos navios (simplificada)

    if (!verificaSobreposicaoHV(tabuleiro, nv_linha, nv_coluna, SHIP_SIZE, 'V')) {
        printf("Erro: Sobreposição no navio vertical.\n");
        return 1;
    }
    if (!verificaSobreposicaoHV(tabuleiro, nh_linha, nh_coluna, SHIP_SIZE, 'H')) {
        printf("Erro: Sobreposição no navio horizontal.\n");
        return 1;
    }
    if (!verificaSobreposicaoDiagonal(tabuleiro, ndc_linha, ndc_coluna, SHIP_SIZE, 'D')) {
        printf("Erro: Sobreposição no navio diagonal crescente.\n");
        return 1;
    }
    if (!verificaSobreposicaoDiagonal(tabuleiro, ndd_linha, ndd_coluna, SHIP_SIZE, 'A')) {
        printf("Erro: Sobreposição no navio diagonal decrescente.\n");
        return 1;
    }

    // Posiciona os navios no tabuleiro
    posicionarNavioHV(tabuleiro, nv_linha, nv_coluna, SHIP_SIZE, 'V');
    posicionarNavioHV(tabuleiro, nh_linha, nh_coluna, SHIP_SIZE, 'H');
    posicionarNavioDiagonal(tabuleiro, ndc_linha, ndc_coluna, SHIP_SIZE, 'D');
    posicionarNavioDiagonal(tabuleiro, ndd_linha, ndd_coluna, SHIP_SIZE, 'A');

    // Imprime o tabuleiro
    imprimirTabuleiro(tabuleiro);

    return 0;
}
