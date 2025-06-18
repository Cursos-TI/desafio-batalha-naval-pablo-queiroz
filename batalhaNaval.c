#include <stdio.h>
#include <stdlib.h> // para abs()

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Inicializa o tabuleiro com água (0)
void inicializarTabuleiro(int tab[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++)
        for (int j = 0; j < TAM_TABULEIRO; j++)
            tab[i][j] = 0;
}

// Posiciona navio horizontal ('H') ou vertical ('V')
// Retorna 1 se sucesso, 0 se fora do limite ou sobreposição
int posicionarNavio(int tab[TAM_TABULEIRO][TAM_TABULEIRO],
                    int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        if (coluna + TAM_NAVIO > TAM_TABULEIRO) return 0;
        for (int j = coluna; j < coluna + TAM_NAVIO; j++)
            if (tab[linha][j] == 3) return 0;
        for (int j = coluna; j < coluna + TAM_NAVIO; j++)
            tab[linha][j] = 3;
    } else if (orientacao == 'V') {
        if (linha + TAM_NAVIO > TAM_TABULEIRO) return 0;
        for (int i = linha; i < linha + TAM_NAVIO; i++)
            if (tab[i][coluna] == 3) return 0;
        for (int i = linha; i < linha + TAM_NAVIO; i++)
            tab[i][coluna] = 3;
    } else {
        return 0;
    }
    return 1;
}

// Posiciona navio diagonal (sentido 1 = descendo à direita, -1 = descendo à esquerda)
// Retorna 1 se sucesso, 0 se inválido
int posicionarNavioDiagonal(int tab[TAM_TABULEIRO][TAM_TABULEIRO],
                            int linha, int coluna, int sentido) {
    if (sentido == 1) {
        if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna + TAM_NAVIO > TAM_TABULEIRO) return 0;
        for (int k = 0; k < TAM_NAVIO; k++)
            if (tab[linha + k][coluna + k] == 3) return 0;
        for (int k = 0; k < TAM_NAVIO; k++)
            tab[linha + k][coluna + k] = 3;
    } else if (sentido == -1) {
        if (linha + TAM_NAVIO > TAM_TABULEIRO || coluna - (TAM_NAVIO - 1) < 0) return 0;
        for (int k = 0; k < TAM_NAVIO; k++)
            if (tab[linha + k][coluna - k] == 3) return 0;
        for (int k = 0; k < TAM_NAVIO; k++)
            tab[linha + k][coluna - k] = 3;
    } else {
        return 0;
    }
    return 1;
}

// Cria matriz de habilidade "cone" (cone apontando para baixo)
void criarHabilidadeCone(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // Posições afetadas formam um cone que começa no topo (linha 0)
            // expandindo para baixo e para os lados até a base
            int largura = i * 2 + 1; // largura do cone na linha i
            int inicio = centro - i;
            int fim = centro + i;
            if (i < TAM_HABILIDADE && j >= inicio && j <= fim)
                hab[i][j] = 1;
            else
                hab[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade "cruz"
void criarHabilidadeCruz(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro)
                hab[i][j] = 1;
            else
                hab[i][j] = 0;
        }
    }
}

// Cria matriz de habilidade "octaedro" (losango)
void criarHabilidadeOctaedro(int hab[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int dist = abs(i - centro) + abs(j - centro);
            hab[i][j] = (dist <= centro) ? 1 : 0;
        }
    }
}

// Sobrepõe a habilidade no tabuleiro, marcando as posições afetadas com 5 (se estiverem em água)
void aplicarHabilidade(int tab[TAM_TABULEIRO][TAM_TABULEIRO],
                      int hab[TAM_HABILIDADE][TAM_HABILIDADE],
                      int origemLinha, int origemColuna) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linTab = origemLinha + i - meio;
            int colTab = origemColuna + j - meio;

            // Valida limites do tabuleiro
            if (linTab >= 0 && linTab < TAM_TABULEIRO && colTab >= 0 && colTab < TAM_TABULEIRO) {
                if (hab[i][j] == 1 && tab[linTab][colTab] == 0) {
                    tab[linTab][colTab] = 5; // marca área afetada
                }
            }
        }
    }
}

// Imprime o tabuleiro no console
void imprimirTabuleiro(int tab[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nTabuleiro (0=água, 3=navio, 5=área habilidade):\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posiciona navios
    if (!posicionarNavio(tabuleiro, 0, 0, 'H'))
        printf("Erro ao posicionar navio horizontal 1\n");
    if (!posicionarNavio(tabuleiro, 5, 5, 'V'))
        printf("Erro ao posicionar navio vertical 1\n");
    if (!posicionarNavioDiagonal(tabuleiro, 2, 2, 1))
        printf("Erro ao posicionar navio diagonal 1\n");
    if (!posicionarNavioDiagonal(tabuleiro, 6, 7, -1))
        printf("Erro ao posicionar navio diagonal 2\n");

    // Cria matrizes de habilidade
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarHabilidadeCone(cone);
    criarHabilidadeCruz(cruz);
    criarHabilidadeOctaedro(octaedro);

    // Define pontos de origem das habilidades no tabuleiro
    int origemConeLinha = 1, origemConeColuna = 3;
    int origemCruzLinha = 7, origemCruzColuna = 5;
    int origemOctaedroLinha = 4, origemOctaedroColuna = 8;

    // Aplica habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, origemConeLinha, origemConeColuna);
    aplicarHabilidade(tabuleiro, cruz, origemCruzLinha, origemCruzColuna);
    aplicarHabilidade(tabuleiro, octaedro, origemOctaedroLinha, origemOctaedroColuna);

    // Exibe o tabuleiro final
    imprimirTabuleiro(tabuleiro);

    return 0;
}
