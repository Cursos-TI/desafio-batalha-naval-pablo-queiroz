#include <stdio.h>

#define TAB_SIZE 10     // Tamanho do tabuleiro (10x10)
#define SHIP_SIZE 3     // Tamanho fixo dos navios

// Função para imprimir o tabuleiro no console
void imprimirTabuleiro(int tab[TAB_SIZE][TAB_SIZE]) {
    printf("Tabuleiro Batalha Naval:\n");
    for (int i = 0; i < TAB_SIZE; i++) {
        for (int j = 0; j < TAB_SIZE; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAB_SIZE][TAB_SIZE] = {0};  // Inicializa tabuleiro com 0 (água)

    // Vetores representando os navios (tamanho fixo)
    int navio_vertical[SHIP_SIZE] = {3, 3, 3};     // valor 3 representa navio
    int navio_horizontal[SHIP_SIZE] = {3, 3, 3};   // valor 3 representa navio

    // Coordenadas iniciais definidas diretamente no código
    int nav_v_linha = 1;      // Linha inicial do navio vertical
    int nav_v_coluna = 5;     // Coluna fixa do navio vertical

    int nav_h_linha = 6;      // Linha fixa do navio horizontal
    int nav_h_coluna = 2;     // Coluna inicial do navio horizontal

    // Validar limites para navio vertical
    if (nav_v_linha + SHIP_SIZE > TAB_SIZE) {
        printf("Erro: Navio vertical ultrapassa limites do tabuleiro.\n");
        return 1;
    }

    // Validar limites para navio horizontal
    if (nav_h_coluna + SHIP_SIZE > TAB_SIZE) {
        printf("Erro: Navio horizontal ultrapassa limites do tabuleiro.\n");
        return 1;
    }

    // Validar sobreposição simples:
    // Para cada posição do navio vertical, verifica se coincide com alguma posição do navio horizontal
    for (int i = 0; i < SHIP_SIZE; i++) {
        int linha_vert = nav_v_linha + i;
        int coluna_vert = nav_v_coluna;

        for (int j = 0; j < SHIP_SIZE; j++) {
            int linha_hori = nav_h_linha;
            int coluna_hori = nav_h_coluna + j;

            if (linha_vert == linha_hori && coluna_vert == coluna_hori) {
                printf("Erro: Navios se sobrepõem!\n");
                return 1;
            }
        }
    }

    // Posicionar navio vertical no tabuleiro copiando valores do vetor
    for (int i = 0; i < SHIP_SIZE; i++) {
        tabuleiro[nav_v_linha + i][nav_v_coluna] = navio_vertical[i];
    }

    // Posicionar navio horizontal no tabuleiro copiando valores do vetor
    for (int i = 0; i < SHIP_SIZE; i++) {
        tabuleiro[nav_h_linha][nav_h_coluna + i] = navio_horizontal[i];
    }

    // Exibir o tabuleiro completo
    imprimirTabuleiro(tabuleiro);

    return 0;
}
