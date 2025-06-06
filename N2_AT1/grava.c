#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long converter_para_timestamp(int dia, int mes, int ano, int hora, int min, int seg) {
    struct tm t;
    t.tm_year = ano - 1900;
    t.tm_mon = mes - 1;
    t.tm_mday = dia;
    t.tm_hour = hora;
    t.tm_min = min;
    t.tm_sec = seg;
    t.tm_isdst = -1;
    return mktime(&t);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s <sensor> <DD/MM/AAAA_HH:MM:SS> <valor>\n", argv[0]);
        return 1;
    }

    char *sensor = argv[1];
    char *data_hora = argv[2];
    char *valor = argv[3];

    for (int i = 0; data_hora[i]; i++) {
        if (data_hora[i] == '_') data_hora[i] = ' ';
    }

    int dia, mes, ano, hora, min, seg;
    if (sscanf(data_hora, "%d/%d/%d %d:%d:%d", &dia, &mes, &ano, &hora, &min, &seg) != 6) {
        printf("Formato de data inválido.\n");
        return 1;
    }

    long timestamp = converter_para_timestamp(dia, mes, ano, hora, min, seg);

    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%s.txt", sensor);

    FILE *arquivo = fopen(nome_arquivo, "a");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fprintf(arquivo, "%ld %s %s\n", timestamp, sensor, valor);
    fclose(arquivo);

    printf("Dados gravados com sucesso.\n");

    return 0;
}

