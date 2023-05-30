#include <stdio.h>
#include <stdbool.h> 
#include "Cliente.h"
#include "Transporte.h"

#ifndef HISTORICO_H
#define HISTORICO_H 

/**
 * @brief Estrutura para o registo de hist�rico. 
 * Esta estrutura representa um registo de hist�rico, contem informa��es sobre a desloca��o que foi realizada. 
 */
typedef struct historico {
 
	char nome_cliente[80]; /**< Nome do cliete */
	int nif; /**< NIF do cliente */
	int ID; /**<ID do meio de transporte */
	char tipo[20]; /**< Tipo de meio de transporte*/
	float preco; /**< Pre�o da viagem*/
	float distancia; /** <distancia percorrida */
	char moradaIni[80]; /** <Morada inicial da viagem */
	char moradaFim[80]; /** <Morada final da viagem */
	struct  historico* seguinte; 

}HistoricoRegisto;  

/**
 * @brief Apontador externo para a lista de hist�rico.
 * Vari�vel externa que armazena o apontador para a lista de hist�rico de registo.
 * Essa vari�vel pode ser utilizado em outros ficheiro para referenciar a lista de hist�rico. 
 */
extern HistoricoRegisto* historico;  

/**
 * @brief Insere um novo registo na lista de hist�rico.
 *
 * Esta fun��o cria um novo registo de hist�rico e o insere no final da lista.
 *
 * @param historico Um apontador para o apontador da lista de hist�rico.
 * @param nome O nome do cliente.
 * @param NIF O NIF do cliente.
 * @param tipo O tipo de viagem.
 * @param id O ID do registro.
 * @param preco O pre�o da viagem.
 * @param distanciaPer A dist�ncia percorrida na viagem.
 * @param localidadeIni A morada inicial da viagem.
 * @param localidadeFim A morada final da viagem.
 */
void InserirRegisto(HistoricoRegisto** historico_1, char* nome, int NIF, char* tipo, int id, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim);

/**
 * @brief Guarda o hist�rico em ficheiro.
 * Esta fun��o percorre a lista de hist�rico e escreve cada registo no ficheiro de texto.
 * @param historico Um apontador para a lista de hist�rico.
 */
void GuardarHistorico(HistoricoRegisto* historico); 

/**
 * @brief Consulta o hist�rico na consola do Gestor.
 * Esta fun��o exibe os registo de todo hist�rico na consola.
 * @param historico Um apontador para a lista de hist�rico.
 * @return Um ponteiro nulo.
 */
HistoricoRegisto* consultarhistorico (HistoricoRegisto* historico); 

/**
 * @brief L� o ficheiro de texto do hist�rico.
 * Esta fun��o l� o ficheiro de texto "historico.txt" e armazena os registo na lista de hist�rico.
 * @param historico Um apontador para a lista de hist�rico.
 * @return Um apontador para a lista de hist�rico atualizada.
 */
HistoricoRegisto* lerficheirohistorico(HistoricoRegisto* historico);

/**
 * @brief Consulta o hist�rico de um cliente logado.
 * Esta fun��o exibe na consola o hist�rico de viagens de um cliente com base no seu NIF. 
 * @param historico Um apontador para a lista de hist�rico.
 * @param nif O NIF do cliente para o qual o hist�rico ser� consultado.
 */
void consultarHistoricoCliente(HistoricoRegisto* historico, int nif); 

#endif "HISTORICO_H" 