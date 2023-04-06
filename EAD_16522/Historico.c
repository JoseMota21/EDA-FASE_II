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

//Guardar o historico na estrutura 
void GuardarHistorico(HistoricoRegisto* historico) {

    // Abrir o arquivo de texto em modo de escrita
    FILE* fhistorico = fopen("historico.bin", "ab"); // "a" para adicionar o novo registro no final do arquivo

    // Verificar se o arquivo foi aberto com sucesso
    if (fhistorico == NULL) {
        printf("ERRO AO ABRIR O FICHEIRO");
        return;
    }

    // Percorrer a lista de histórico e escrever cada registro no arquivo de texto
    HistoricoRegisto* atual = historico;
    while (atual != NULL) {
        fprintf(fhistorico, "Cliente: %s, Meio de transporte: %s, Preco: %.2f, Distancia: %.2f, Localidade de inicio: %s, Localidade de fim: %s\n", atual->cliente->nome_cliente, atual->meioTransporte->tipo, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);
        atual = atual->seguinte;
    }

    // Fechar o arquivo
    fclose(fhistorico);
}

//Consultar o historico na consola 
void consultarhistorico() {

    HistoricoRegisto* atual = historico; 

        // Abrir o ficheiro com os dados de historico
        FILE * fhistorico = fopen("Historico.bin", "rb"); 

        // Se ficheiro não aberto corretamente informa o utilizador
            if (fhistorico == NULL) {
                printf("ERRO AO ABRIR O HISTORICO\n");
                return;
            }

            printf("Historico:\n");

            while (atual != NULL) {
                printf("Cliente: %s, Meio de transporte: %s, Preco: %.2f, Distancia: %.2f, Localidade de inicio: %s, Localidade de fim: %s\n",
                    atual->cliente->nome_cliente, atual->meioTransporte->tipo, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);
                atual = atual->seguinte;
            }
}

//Ler ficheiro historico 
HistoricoRegisto* lerficheiroHistorico (HistoricoRegisto* inicio) {

    //Abrir ficheiro 
    FILE* fhistorico = fopen("historico.bin", "rb"); // abrir o arquivo em modo leitura

    //Se impossivel abrir ficheiro informa o utilizador
    if (fhistorico == NULL) {
        printf("Erro ao abrir o arquivo.");
        return;
    }

    while (1) {
        // Alocar a capacidade necessária de memoria e indica o tamanho de espaço de memoria a ser alocado
        HistoricoRegisto* novoRegisto = (HistoricoRegisto*) malloc(sizeof (HistoricoRegisto)); 

        //Lê os dados do ficheiro binario para a estrutura e verifica se a leitura foi bem sucedida 
        if (fread(novoRegisto, sizeof(Cliente), 1, fhistorico) != 1) {

            free(novoRegisto); //Caso a leitura não tenha sido sucedida liberta a memória alocada
            break;
        }

        //Define o ultimo elemento da lista 
        novoRegisto->seguinte = NULL; 

        //Se a lista estiver vazia, a variável inicio é definida como a estrutura novo transporte
        if (inicio == NULL) {
            inicio = novoRegisto;
        }
        else {
            HistoricoRegisto* atual = inicio; 

            //Percorre a lista até encontrar o último elemento 
            while (atual->seguinte != NULL) {
                atual = atual->seguinte;
            }
            //Proximo elemento
            atual->seguinte = novoRegisto;
        }
    }
    //Fechar o ficheiro 
    fclose(fhistorico);

    return inicio;
 }
   