#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    long timestamp;
    char id_sensor[50];
    char valor[50];
} Registro;

int comparar(const void *a, const void *b) {
    Registro *ra = (Registro *)a;
    Registro *rb = (Registro *)b;

    if (ra->timestamp < rb->timestamp) return -1;
    else if (ra->timestamp > rb->timestamp) return 1;
    else return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <SENSOR>\n", argv[0]);
        return 1;
    }

    char *sensor = argv[1];
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
        printf("Nenhum dado no arquivo.\n");
        return 1;
    }

    qsort(registros, count, sizeof(Registro), comparar);

    fp = fopen(nome_arquivo, "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo para escrita %s\n", nome_arquivo);
        return 1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%ld %s %s\n", registros[i].timestamp, registros[i].id_sensor, registros[i].valor);
    }

    fclose(fp);

    printf("Arquivo %s ordenado com sucesso.\n", nome_arquivo);

    return 0;
}

