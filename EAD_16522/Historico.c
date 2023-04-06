#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Historico.h" 

// Variável global para o histórico
HistoricoRegisto* historico = NULL; 

//Inser novo registo na lista do historico 
void InserirRegisto (Cliente* cliente, Transporte* meioTransporte, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim) {

	// Alocar dinamicamente uma nova estrutura de histórico
	HistoricoRegisto * novoRegisto = (HistoricoRegisto*)malloc(sizeof(HistoricoRegisto));

    // Atribuir os valores dos parâmetros à estrutura
    novoRegisto->cliente = cliente;
    novoRegisto->meioTransporte = meioTransporte;
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

void GuardarHistorico(HistoricoRegisto* historico) {

    // Abrir o arquivo de texto em modo de escrita
    FILE* fp = fopen("historico.txt", "w"); // "a" para adicionar o novo registro no final do arquivo

    // Verificar se o arquivo foi aberto com sucesso
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    // Percorrer a lista de histórico e escrever cada registro no arquivo de texto
    HistoricoRegisto* atual = historico;
    while (atual != NULL) {
        fprintf(fp, "Cliente: %s, Meio de transporte: %s, Preco: %.2f, Distancia: %.2f, Localidade de inicio: %s, Localidade de fim: %s\n", atual->cliente->nome_cliente, atual->meioTransporte->tipo, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);
        atual = atual->seguinte;
    }

    // Fechar o arquivo
    fclose(fp);
}






