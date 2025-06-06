# Projetos de Programação em C

Este repositório contém dois projetos distintos desenvolvidos na linguagem C como parte das atividades avaliativas da disciplina.

---

## 📁 N1_AT1 — Jogo de Cartas em C

### Descrição
Implementação de um jogo de cartas baseado em um baralho personalizado, disputado entre dois jogadores. O objetivo é alcançar 12 pontos primeiro, vencendo rodadas compostas por três mãos de cartas.

### Características
- **Baralho personalizado** com 40 cartas (sem 8 e 9).
- **Hierarquia especial**: cartas como "Zap", "Espadão" e "Pé".
- **Rodadas e mãos**: ganha quem vencer 2 de 3 mãos.
- **Ações possíveis**: Aumentar, Aceitar, Desistir, Jogar Carta, Terminar Turno.
- **Regras de desempate** bem definidas.
- **Interface em texto**, mostrando status do jogo em tempo real.

### Objetivo do jogo
Alcançar 12 pontos acumulando vitórias nas rodadas, cujo valor pode ser aumentado ao longo do jogo por meio das ações dos jogadores.

### Como jogar
1. Rodada começa valendo 1 ponto.
2. Jogadores se revezam jogando cartas ou tomando ações.
3. Quem vencer duas mãos vence a rodada e soma os pontos.
4. O jogo termina quando alguém alcança 12 pontos.

### Execução
Você pode compilar localmente com `gcc` ou usar um compilador online como [OnlineGDB](https://www.onlinegdb.com/).

---

## 📁 N2_AT1 — Gerenciamento de Dados de Sensores

### Descrição
Conjunto de três programas em C que simulam a gravação, ordenação e consulta de dados de sensores, utilizando arquivos `.txt` para armazenamento e manipulação.

### Estrutura de programas

#### 1. `grava.exe`
Grava uma nova leitura no arquivo `<sensor>.txt`.

**Uso:**
grava.exe <sensor> <DD/MM/AAAA_HH:MM:SS> <valor>

**Exemplo:**
grava.exe sensor1 05/06/2025_14:30:00 32.5

---

#### 2. `ordena.exe`
Ordena o arquivo do sensor por ordem crescente de timestamp.

**Uso:**
ordena.exe <sensor>

**Exemplo:**
ordena.exe sensor1

---

#### 3. `consulta.exe`
Consulta a leitura mais próxima de um timestamp (em segundos desde Epoch).

**Uso:**
consulta.exe <sensor> <timestamp_em_segundos>

**Exemplo:**
consulta.exe sensor1 1749120600

---

### Fluxo de uso recomendado

1. Grave os dados com `grava.exe`.
2. Ordene o arquivo com `ordena.exe`.
3. Faça consultas precisas com `consulta.exe`.

### Compilação

Compile os três programas usando o GCC:

```bash
gcc grava.c -o grava.exe
gcc ordena.c -o ordena.exe
gcc consulta.c -o consulta.exe

📂 Organização do repositório

/N1_AT1
  └── jogo_cartas.c
  └── README_JOGO.md

/N2_AT1
  └── grava.c
  └── ordena.c
  └── consulta.c
  └── README_SENSORES.md

README.md  ← (você está aqui)
