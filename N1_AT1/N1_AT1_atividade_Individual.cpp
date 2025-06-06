#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_CARTAS 40
#define NUM_NAIPES 4
#define CARTAS_POR_NAIPE 10
#define CARTAS_POR_JOGADOR 3

const char *naipes[NUM_NAIPES] = {"Espadas", "Copas", "Ouros", "Paus"};
const int valoresPermitidos[CARTAS_POR_NAIPE] = {1, 2, 3, 4, 5, 6, 7, 10, 11, 12};

const int hierarquia[] = {4, 7, 1, 1, 7, 6, 5, 4, 3, 2, 12, 11, 10};

typedef struct {
    int valor;
    char naipe[10];
} Carta;

typedef struct {
    Carta cartas[CARTAS_POR_JOGADOR];
    int pontos;
    int ultimaAção;
    int aumentarProposto;
} Jogador;

typedef enum {
    AUMENTAR = 1,
    ACEITAR,
    DESISTIR,
    JOGAR_CARTA,
    TERMINAR_TURNO
} Ação;

void embaralhar(Carta baralho[NUM_CARTAS]) {
    for (int i = 0; i < NUM_CARTAS; i++) {
        int r = rand() % NUM_CARTAS;
        Carta temp = baralho[i];
        baralho[i] = baralho[r];
        baralho[r] = temp;
    }
}

void distribuirCartas(Carta baralho[NUM_CARTAS], Jogador *jogador1, Jogador *jogador2) {
    embaralhar(baralho);
    for (int i = 0; i < CARTAS_POR_JOGADOR; i++) {
        jogador1->cartas[i] = baralho[i * 2];
        jogador2->cartas[i] = baralho[i * 2 + 1];
    }
}

int compararCartas(Carta c1, Carta c2) {
    int hierarquia_c1 = -1, hierarquia_c2 = -1;
    for (int i = 0; i < 13; i++) {
        if (c1.valor == hierarquia[i]) hierarquia_c1 = i;
        if (c2.valor == hierarquia[i]) hierarquia_c2 = i;
    }
    return hierarquia_c2 - hierarquia_c1;
}

void exibirMao(Jogador *jogador) {
    printf("Mão do jogador:\n");
    for (int i = 0; i < CARTAS_POR_JOGADOR; i++) {
        printf("%d de %s\n", jogador->cartas[i].valor, jogador->cartas[i].naipe);
    }
}

void exibirStatus(int rodada, int mao, Jogador *jogador1, Jogador *jogador2, Carta ultimaCarta1, Carta ultimaCarta2) {
    printf("\n--- Status da Partida ---\n");
    printf("Rodada: %d | Mão: %d\n", rodada, mao);
    printf("Pontuação: Jogador 1 - %d | Jogador 2 - %d\n", jogador1->pontos, jogador2->pontos);
    printf("Última carta jogada (Jogador 1): %d de %s\n", ultimaCarta1.valor, ultimaCarta1.naipe);
    printf("Última carta jogada (Jogador 2): %d de %s\n", ultimaCarta2.valor, ultimaCarta2.naipe);
}

Ação escolherAcao(Jogador *jogador) {
    printf("\nEscolha sua ação (1: Aumentar, 2: Aceitar, 3: Desistir, 4: Jogar Carta, 5: Terminar Turno): ");
    int acao;
    scanf("%d", &acao);
    jogador->ultimaAção = acao;
    return acao;
}

void jogarCarta(Jogador *jogador) {
    int escolha;
    printf("Escolha uma carta para jogar (0, 1, 2): ");
    scanf("%d", &escolha);
    Carta carta = jogador->cartas[escolha];
    printf("\nJogador jogou %d de %s\n", carta.valor, carta.naipe);
}

int resolverMao(Jogador *jogador1, Jogador *jogador2, Carta *ultimaCarta1, Carta *ultimaCarta2) {
    printf("\nJogador 1: ");
    exibirMao(jogador1);
    printf("\nJogador 2: ");
    exibirMao(jogador2);

    printf("\nJogador 1, escolha sua ação:\n");
    Ação acao1 = escolherAcao(jogador1);
    printf("\nJogador 2, escolha sua ação:\n");
    Ação acao2 = escolherAcao(jogador2);

    if (acao1 == JOGAR_CARTA && acao2 == JOGAR_CARTA) {
        jogarCarta(jogador1);
        jogarCarta(jogador2);
        *ultimaCarta1 = jogador1->cartas[0];
        *ultimaCarta2 = jogador2->cartas[0];
        return compararCartas(jogador1->cartas[0], jogador2->cartas[0]);
    }

    return 0;
}

void jogarRodada(int rodada, Jogador *jogador1, Jogador *jogador2) {
    Carta ultimaCarta1 = {0, ""};
    Carta ultimaCarta2 = {0, ""};
    
    for (int mao = 1; mao <= 3; mao++) {
        exibirStatus(rodada, mao, jogador1, jogador2, ultimaCarta1, ultimaCarta2);
        int resultadoMao = resolverMao(jogador1, jogador2, &ultimaCarta1, &ultimaCarta2);

        if (resultadoMao == 1) {
            printf("\nJogador 1 vence a mão!\n");
            jogador1->pontos++;
        } else if (resultadoMao == 2) {
            printf("\nJogador 2 vence a mão!\n");
            jogador2->pontos++;
        } else {
            printf("\nEmpate na mão!\n");
        }
    }
}

int main() {
    srand(time(NULL));

    Carta baralho[NUM_CARTAS];
    int index = 0;
    for (int i = 0; i < NUM_NAIPES; i++) {
        for (int j = 0; j < CARTAS_POR_NAIPE; j++) {
            baralho[index].valor = valoresPermitidos[j];
            strcpy(baralho[index].naipe, naipes[i]);
            index++;
        }
    }

    Jogador jogador1 = {.pontos = 0};
    Jogador jogador2 = {.pontos = 0};
    int rodada = 1;

    while (jogador1.pontos < 12 && jogador2.pontos < 12) {
        printf("\n--- Início da Rodada %d ---\n", rodada);
        distribuirCartas(baralho, &jogador1, &jogador2);
        jogarRodada(rodada, &jogador1, &jogador2);
        printf("Pontuação Final da Rodada %d: Jogador 1 - %d | Jogador 2 - %d\n", rodada, jogador1.pontos, jogador2.pontos);
        rodada++;
    }

    printf("\nFim do jogo! Vencedor: %s\n", (jogador1.pontos >= 12) ? "Jogador 1" : "Jogador 2");
    return 0;
}

