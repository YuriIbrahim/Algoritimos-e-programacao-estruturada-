#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct {
    long timestamp;
    char id_sensor[50];
    char valor[50];
} Registro;

long converter_para_timestamp(const char *data_hora_str) {

    struct tm t;
    memset(&t, 0, sizeof(struct tm));

    char buf[20];
    strncpy(buf, data_hora_str, sizeof(buf)-1);
    buf[sizeof(buf)-1] = '\0';

    for (int i = 0; buf[i]; i++) {
        if (buf[i] == '_') buf[i] = ' ';
    }

    int dia, mes, ano, hora, min, seg;
    if (sscanf(buf, "%2d/%2d/%4d %2d:%2d:%2d",
               &dia, &mes, &ano, &hora, &min, &seg) != 6) {
        return -1; // erro
    }

    t.tm_mday = dia;
    t.tm_mon = mes - 1;
    t.tm_year = ano - 1900;
    t.tm_hour = hora;
    t.tm_min = min;
    t.tm_sec = seg;
    t.tm_isdst = -1;

    return mktime(&t);
}

Registro busca_binaria_mais_proxima(Registro *dados, int tamanho, long alvo) {
    int esquerda = 0, direita = tamanho - 1;
    Registro mais_proximo = dados[0];
    long menor_diferenca = labs(dados[0].timestamp - alvo);

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        long diferenca = labs(dados[meio].timestamp - alvo);

        if (diferenca < menor_diferenca) {
            menor_diferenca = diferenca;
            mais_proximo = dados[meio];
        }

        if (dados[meio].timestamp < alvo)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }

    return mais_proximo;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <SENSOR> <DD/MM/AAAA_HH:MM:SS>\n", argv[0]);
        return 1;
    }

    char *sensor = argv[1];
    char *data_hora_str = argv[2];

    long timestamp_alvo = converter_para_timestamp(data_hora_str);
    if (timestamp_alvo == -1) {
        printf("Formato de data/hora inválido. Use DD/MM/AAAA_HH:MM:SS\n");
        return 1;
    }

    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", sensor);

    FILE *fp = fopen(nome_arquivo, "r");
    if (!fp) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return 1;
    }

    Registro registros[1000];
    int count = 0;
    while (fscanf(fp, "%ld %49s %49s", &registros[count].timestamp, registros[count].id_sensor, registros[count].valor) == 3) {
        count++;
        if (count >= 1000) break;  
    }
    fclose(fp);

    if (count == 0) {
        printf("Nenhum dado encontrado no arquivo.\n");
        return 1;
    }

    Registro resultado = busca_binaria_mais_proxima(registros, count, timestamp_alvo);

    printf("Leitura mais próxima:\n");
    printf("%ld %s %s\n", resultado.timestamp, resultado.id_sensor, resultado.valor);

    return 0;
}

