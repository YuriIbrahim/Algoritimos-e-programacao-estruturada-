# Jogo de Cartas em C

Este repositório contém a implementação de um jogo de cartas baseado em um baralho personalizado, desenvolvido em C. O jogo é disputado entre dois jogadores e tem como objetivo alcançar 12 pontos primeiro, através de rodadas e mãos de cartas.

## Características

- **Baralho personalizado**: O baralho contém 40 cartas divididas em 4 naipes (Espadas, Copas, Ouros, Paus), com valores de 1 a 7 e 10 a 12 (sem 8 e 9).
- **Hierarquia das cartas**: A ordem das cartas segue uma hierarquia específica, com cartas especiais como "Zap", "Espadão" e "Pé".
- **Rodadas e mãos**: Cada rodada tem 3 mãos. O jogador que vencer 2 mãos ganha a rodada.
- **Ações dos jogadores**: Durante o turno, os jogadores podem realizar as ações: "Aumentar", "Aceitar", "Desistir", "Jogar Carta" e "Terminar Turno".
- **Desempate**: Existem regras específicas para desempatar as mãos e as rodadas, garantindo que o jogo tenha um vencedor justo.
- **Interface de texto**: O jogo exibe informações sobre a última carta jogada, a pontuação dos jogadores, o número da rodada e mão atual, e as cartas na mão do jogador.

## Objetivo do Jogo

O objetivo do jogo é acumular 12 pontos. Cada rodada tem um valor de pontos (1, 3, 6 ou 9), e a pontuação pode ser alterada pela ação "Aumentar". O jogo termina quando um dos jogadores atinge 12 pontos.

## Como Jogar

1. **Início da Rodada**: O jogo começa com o valor da rodada igual a 1 ponto.
2. **Turnos**: Em cada turno, o jogador pode:
   - Aumentar o valor da rodada (se ainda não foi feito).
   - Aceitar o aumento de rodada proposto pelo adversário.
   - Desistir da rodada, dando o ponto ao adversário.
   - Jogar uma carta (se não foi solicitado um aumento).
   - Terminar o turno e passar para o adversário.
3. **Mão**: Uma mão é disputada entre os dois jogadores, onde o jogador que jogar a carta de maior valor vence.
4. **Fim de Rodada**: A rodada termina quando um dos jogadores vencer duas mãos ou quando as condições de desempate forem atendidas.
5. **Fim de Jogo**: O jogo termina quando um dos jogadores acumula 12 pontos.

## Compilação e Execução

### Para compilar o código:

```bash
gcc -o jogo_cartas jogo_cartas.c
