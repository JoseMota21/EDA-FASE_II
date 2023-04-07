#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Historico.h" 

// Variável global para o histórico
HistoricoRegisto* historico = NULL; 

//Inser novo registo na lista do historico
void InserirRegisto (Cliente* cliente, Transporte* meioTransporte, int ID, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim) {

    // Alocar dinamicamente uma nova estrutura de histórico
    HistoricoRegisto * novoRegisto = (HistoricoRegisto*)malloc(sizeof(HistoricoRegisto));

    // Atribuir os valores dos parâmetros à estrutura
    novoRegisto->cliente = cliente;
    novoRegisto->meioTransporte = meioTransporte;
  
    novoRegisto->ID = ID; 
    novoRegisto->preco = preco;
    novoRegisto->distancia = distanciaPer;
    strcpy(novoRegisto->moradaIni, localidadeIni);
    strcpy(novoRegisto->moradaFim, localidadeFim);

    novoRegisto->seguinte = NULL;

    if (historico == NULL) {
        historico = novoRegisto;
    }
    else {
        HistoricoRegisto* ultimo = historico;
        while (ultimo->seguinte != NULL) {
            ultimo = ultimo->seguinte;
        }
        ultimo->seguinte = novoRegisto;
    }
 }

//Guardar o historico na estrutura 
void GuardarHistorico(HistoricoRegisto* historico) {

    // Abrir o arquivo de texto em modo de escrita
    FILE* fhistorico = fopen("historico.txt", "a"); 

    // Verificar se o arquivo foi aberto com sucesso
    if (fhistorico == NULL) {
        printf("ERRO AO ABRIR O FICHEIRO");
        return;
    }

    // Percorrer a lista de histórico e escrever cada registro no arquivo de texto
    HistoricoRegisto* atual = historico;
    while (atual != NULL) {
        fprintf(fhistorico, "%s;%s;%d;%.2f;%.2f;%s;%s\n", atual->cliente->nome_cliente, atual->meioTransporte->tipo, atual->ID, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);
        atual = atual->seguinte;
    }

    // Fechar o arquivo
    fclose(fhistorico);
}

//Consultar o historico na consola 
HistoricoRegisto* consultarhistorico (HistoricoRegisto* historico) {

    if (historico == NULL) {
        printf("LISTA VAZIA\n");
        return NULL;
    }
 
    printf("Historico:\n"); 

    //Percorrer a lista
    while (historico != NULL) {
        printf("%s;%s;%d;%.2f;%.2f;%s;%s\n", historico->cliente->nome_cliente, historico->meioTransporte->tipo, historico->ID, historico->preco, historico->distancia, historico->moradaIni, historico->moradaFim);
        historico = historico->seguinte;
    }
    return NULL;
}

HistoricoRegisto* lerficheirohistorico(HistoricoRegisto* historico, Cliente* cliente, Transporte* meioTansporte) {

    FILE* fhistorico = fopen("historico.txt", "r");

    char linha[1000];

    //Se erro ao abrir o ficheiro informa o utilizador 
    if (fhistorico == NULL) {
        printf("Erro ao abrir o ficheiro historico.txt\n");
        return historico;
    }

    //Percorre cada linha e armazena a linha lida na variável linha
    while (fgets(linha, sizeof(linha), fhistorico) != NULL) {
        HistoricoRegisto* novoRegisto = (HistoricoRegisto*)malloc(sizeof(HistoricoRegisto));

        // Inicializar o cliente e o meio de transporte
        novoRegisto->cliente = cliente;
        novoRegisto->meioTransporte = meioTansporte; 

        sscanf(linha, "%[^;];%[^;];%d;%f;%f;%[^;];%s", novoRegisto->cliente->nome_cliente, novoRegisto->meioTransporte->tipo, &novoRegisto->ID, &novoRegisto->preco, &novoRegisto->distancia, novoRegisto->moradaIni, novoRegisto->moradaFim);

        // Indica que é o último da lista
        novoRegisto->seguinte = NULL;

        if (historico == NULL) {
            historico = novoRegisto;
        }
        // Se lista estiver vazia
        else {
            HistoricoRegisto* atual = historico;

            while (atual->seguinte != NULL) {
                atual = atual->seguinte;
            }
            atual->seguinte = novoRegisto;
        }
    }

    // Fechar o ficheiro
    fclose(fhistorico);
    return historico;
}