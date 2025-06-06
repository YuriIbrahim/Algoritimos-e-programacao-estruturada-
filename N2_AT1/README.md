# Projeto de Gerenciamento de Dados de Sensores

Este projeto contém três programas em C para manipulação de dados de sensores: gravação, ordenação e consulta de leituras baseadas em timestamps.

---

## Programas

### 1. grava.exe  
Grava uma nova leitura de sensor no arquivo `<sensor>.txt`.  
**Uso:**  
grava.exe <sensor> <DD/MM/AAAA_HH:MM:SS> <valor>

Exemplo:  
grava.exe sensor1 05/06/2025_14:30:00 32.5

---

### 2. ordena.exe  
Ordena as leituras do arquivo `<sensor>.txt` pelo timestamp em ordem crescente.  
**Uso:**  
ordena.exe <sensor>

Exemplo:  
ordena.exe sensor1

---

### 3. consulta.exe  
Consulta a leitura mais próxima de um timestamp informado no arquivo `<sensor>.txt`.  
**Uso:**  
consulta.exe <sensor> <timestamp_em_segundos>

Exemplo:  
consulta.exe sensor1 1622895600

---

## Fluxo recomendado para uso

1. Use o programa `grava.exe` para adicionar leituras novas.  
2. Use `ordena.exe` para ordenar os dados do sensor.  
3. Use `consulta.exe` para consultar leituras mais próximas de um timestamp específico.

---

## Observações

- Os arquivos de dados são salvos no formato `<sensor>.txt`.  
- O timestamp utilizado nos arquivos e na consulta é o valor em segundos desde o Epoch (01/01/1970).  
- É importante ordenar o arquivo após gravações para garantir a consulta eficiente.  

---

## Compilação

Para compilar os programas, use o GCC no terminal:  

```bash
gcc grava.c -o grava.exe
gcc ordena.c -o ordena.exe
gcc consulta.c -o consulta.exe