#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Historico.h" 

// Variável global para o histórico
HistoricoRegisto* historico = NULL; 

//Inser novo registo na lista do historico
void InserirRegisto (char* nome, int NIF, char* tipo, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim) {

    // Alocar dinamicamente uma nova estrutura de histórico
    HistoricoRegisto * novoRegisto = (HistoricoRegisto*)malloc(sizeof(HistoricoRegisto));

    // Atribuir os valores dos parâmetros à estrutura
    strcpy(novoRegisto->nome_cliente, nome);
    novoRegisto->nif = NIF;
    strcpy(novoRegisto->tipo, tipo);
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
        fprintf(fhistorico, "%s;%d;%s;%d;%.2f;%.2f;%s;%s \n", atual->nome_cliente, atual->nif, atual->tipo, atual->ID, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);
        atual = atual->seguinte;
    }

    // Fechar o arquivo
    fclose(fhistorico);
}

//Consultar o historico na consola Gestor
HistoricoRegisto* consultarhistorico (HistoricoRegisto* historico) {

    if (historico == NULL) {
        printf("LISTA VAZIA\n");
        return NULL;
    }
 
    printf("HISTORICO:\n"); 

    //Percorrer a lista
    while (historico != NULL) {
        printf("%s;%d;%s;%d;%.2f;%.2f;%s;%s\n", historico->nome_cliente, historico->nif, historico->tipo, historico->ID, historico->preco, historico->distancia, historico->moradaIni, historico->moradaFim);
        historico = historico->seguinte;
    }
    return NULL;
}

//Ler ficheiro txt de historico 
HistoricoRegisto* lerficheirohistorico(HistoricoRegisto* historico) {

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

        sscanf(linha, "%[^;];%d;%[^;];%d;%f;%f;%[^;];%s", novoRegisto->nome_cliente, &novoRegisto->nif, novoRegisto->tipo, &novoRegisto->ID, &novoRegisto->preco, &novoRegisto->distancia, novoRegisto->moradaIni, novoRegisto->moradaFim);

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

//Cliente consulta historico Cliente
void consultarHistoricoCliente(HistoricoRegisto* historico, int nif) {

    HistoricoRegisto* atual = historico;
    int encontrou = 0;

    while (atual != NULL) {
        if (atual != NULL) {
            if (atual->nif == nif)
            encontrou = 1; 

            system("cls"); 
                
            //Escrever na consola
            printf("%s;%d;%s;%d;%.2f;%.2f;%s;%s\n", atual->nome_cliente, atual->nif, atual->tipo, atual->ID, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);
            
            system("pause"); 
            system("cls"); 
        }        
                
        atual = atual->seguinte;
    }
    //Se não encontrado avisa o utilizador
    if (!encontrou) {
        printf("Nenhum registo encontrado para o cliente %d.\n", nif);
    }
}