#define _CRT_SECURE_NO_DEPRECATE 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Historico.h" 

// Variável global para o histórico
HistoricoRegisto* historico = NULL;  

//Inser novo registo na lista do historico
void InserirRegisto(HistoricoRegisto** historico, char* nome, int NIF, char* tipo, int id, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim) {

    // Alocar dinamicamente uma nova estrutura de histórico
    HistoricoRegisto* novoRegisto = (HistoricoRegisto*)malloc(sizeof(HistoricoRegisto));

    // Atribuir os valores dos parâmetros à estrutura
    strcpy(novoRegisto->nome_cliente, nome);
    novoRegisto->nif = NIF;
    strcpy(novoRegisto->tipo, tipo);
    novoRegisto->ID = id;
    novoRegisto->preco = preco;
    novoRegisto->distancia = distanciaPer;
    strcpy(novoRegisto->moradaIni, localidadeIni);
    strcpy(novoRegisto->moradaFim, localidadeFim);

    novoRegisto->seguinte = NULL;

    // Se historico é NULL, não há registro de histórico 
    if (*historico == NULL) {
        // Atribui o endereço do novo registo ao historico  
        *historico = novoRegisto;
    }
    else {
        HistoricoRegisto* ultimo = *historico;

        // Adiciona o registo no fim da lista 
        while (ultimo->seguinte != NULL) {
            ultimo = ultimo->seguinte;
        }
        ultimo->seguinte = novoRegisto;
    }
}
 
//Guardar o historico na estrutura 
void GuardarHistorico(HistoricoRegisto* historico) {

    // Abrir o ficheiro de texto em modo de escrita
    FILE* fhistorico = fopen("historico.txt", "a"); 

    // Verificar se o arquivo foi aberto com sucesso
    if (fhistorico == NULL) {
        printf("ERRO AO ABRIR O FICHEIRO");
        return;
    }

    // Percorrer a lista de histórico e escrever cada registo no arquivo de texto
    HistoricoRegisto* atual = historico;
    while (atual != NULL) {
        //Escreve no ficheiro txt 
        fprintf(fhistorico, "%s;%d;%s;%d;%.2f;%.2f;%s;%s \n", atual->nome_cliente, atual->nif, atual->tipo, atual->ID, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);
        atual = atual->seguinte;
    }

    // Fechar o arquivo
    fclose(fhistorico);
}

//Consultar o historico na consola Gestor
HistoricoRegisto* consultarhistorico (HistoricoRegisto* historico) {

    //Se lista estiver vazia informa o utilizador com uma mensagem 
    if (historico == NULL) {
        printf("LISTA VAZIA\n");
        return NULL;
    }
       //Cabeçalho da lista 
       printf("\t\t++++++++++++++++++ HISTORICO  ++++++++++++++++++++++\n");
       printf("\n"); 
       printf("|%-5s | %-10s | %-10s | %-3s | %-5s | %-5s | %-26s | %-30s |\n", "NOME", "NIF", "TIPO", "ID", "PRECO", "DIST", "LOC. INICIAL", "LOC. FINAL");
       printf("---------------------------------------------------------------------------------------------------------------------\n");
    
       //Percorrer a lista até chegar ao fim 
    while (historico != NULL) {

        //Imprime o dados na consola 
        printf("|%-5s | %-10d | %-10s | %-3d | %-5.2f | %-5.2f | %-25s | %-30s |\n", historico->nome_cliente, historico->nif, historico->tipo, historico->ID, historico->preco, historico->distancia, historico->moradaIni, historico->moradaFim);
       
        //Passa para o seguinte 
        historico = historico->seguinte;
    }
    return NULL;
}

//Ler ficheiro txt de historico 
HistoricoRegisto* lerficheirohistorico(HistoricoRegisto* historico) {

    //Abre o ficheiro texto 
    FILE* fhistorico = fopen("historico.txt", "r");

    //Variável para a linha
    char linha[1000];

    //Se houver problema a abri o ficheiro informa o utilizador
    if (fhistorico == NULL) {
        printf("ERRO AO ABRIR O FICHEIRO DO HISTORICO\n");
        return historico;
    }

    //Percorre cada linha e armazena a linha lida na variável linha
    while (fgets(linha, sizeof(linha), fhistorico) != NULL) {
      
        //Aloca memoria 
        HistoricoRegisto* novoRegisto = (HistoricoRegisto*)malloc(sizeof(HistoricoRegisto));

        //Lê cada linha e armazena nas variáveis 
        sscanf(linha, "%[^;];%d;%[^;];%d;%f;%f;%[^;];%s", novoRegisto->nome_cliente, &novoRegisto->nif, novoRegisto->tipo, &novoRegisto->ID, &novoRegisto->preco, &novoRegisto->distancia, novoRegisto->moradaIni, novoRegisto->moradaFim);

        // Indica que é o último da lista
        novoRegisto->seguinte = NULL;

        //Verifica se a lista está vazia
        if (historico == NULL) {
            //Colocado como o primeiro da lista 
            historico = novoRegisto;
        }
        // Se lista estiver vazia
        else {
            HistoricoRegisto* atual = historico; 

            //Enquanto que o apontador seguinte for diferente de NULL 
            while (atual->seguinte != NULL) {
                atual = atual->seguinte;
            }
            //Quando for NULL o novo registo é o proximo da lista 
            atual->seguinte = novoRegisto;
        }
    }

    // Fechar o ficheiro 
    fclose(fhistorico);
    return historico;
} 

//Cliente consulta historico Cliente
void consultarHistoricoCliente(HistoricoRegisto* historico, int nif) {

    //Declarar variável 
    HistoricoRegisto* atual = historico;
    
    //Variável do tipo Boleana 
    bool encontrou = false; 

    //Cabeçalho da tabela 
    system("cls"); 
    printf("\t\t++++++++++++++++++ HISTORICO PESSOAL ++++++++++++++++++++++\n");
    printf("\n");

    printf("|%-5s | %-10s | %-10s | %-3s | %-5s | %-5s | %-25s | %-30s |\n", "NOME", "NIF", "TIPO", "ID", "PRECO", "DIST", "LOC. INICIAL", "LOC. FINAL");
    printf("---------------------------------------------------------------------------------------------------------------------\n");
   
    //Percorre até ser NULL 
    while (atual != NULL) {
       
        //Se o nif inserido do cliente logado for igual ao nif da estrutura 
        //imprime na consola os dados do historico desse cliete
        if (atual->nif == nif) {
            encontrou = true; 

            //Escrever na consola
            printf("|%-5s | %-10d | %-10s | %-3d | %-5.2f | %-5.2f | %-25s | %-30s |\n", atual->nome_cliente, atual->nif, atual->tipo, atual->ID, atual->preco, atual->distancia, atual->moradaIni, atual->moradaFim);

        }
        //Passa para o proximo registo 
        atual = atual->seguinte;

    }

    printf("\n");
    system("pause");
    system("cls");


    //Se não encontrado avisa o utilizador
    if (!encontrou) {
        printf("NENHUM REGISTO ENCONTRADO COM O NIF %d.\n", nif);

        system("pause"); 
        system("cls"); 
    }
}