#include <stdio.h>
#include <stdbool.h> 
#include "Cliente.h"
#include "Transporte.h"

#ifndef HISTORICO_H
#define HISTORICO_H 

/**
 * @brief Estrutura para o registo de histórico. 
 * Esta estrutura representa um registo de histórico, contem informações sobre a viagem (deslocação) que foi realizada. 
 */
typedef struct historico {
 
	char nome_cliente[80]; 
	int nif; 
	int ID;
	char tipo[20];
	float preco; //Preço da viagem
	float distancia; //distancia percorrida
	char moradaIni[80]; //Morada inicial da viagem
	char moradaFim[80]; //Morada final da viagem
	struct  historico* seguinte; // endereço de memória para uma struct registo historico 

}HistoricoRegisto; 

/**
 * @brief Apontador externo para a lista de histórico.
 * Variável externa que armazena o apontador para a lista de histórico de registo.
 * Essa variável pode ser utilizado em outros ficheiro para referenciar a lista de histórico. 
 */
extern HistoricoRegisto* historico;  

/**
 * @brief Insere um novo registo na lista de histórico.
 *
 * Esta função cria um novo registo de histórico e o insere no final da lista.
 *
 * @param historico Um apontador para o apontador da lista de histórico.
 * @param nome O nome do cliente.
 * @param NIF O NIF do cliente.
 * @param tipo O tipo de viagem.
 * @param id O ID do registro.
 * @param preco O preço da viagem.
 * @param distanciaPer A distância percorrida na viagem.
 * @param localidadeIni A morada inicial da viagem.
 * @param localidadeFim A morada final da viagem.
 */
void InserirRegisto(HistoricoRegisto** historico_1, char* nome, int NIF, char* tipo, int id, float preco, float distanciaPer, char* localidadeIni, char* localidadeFim);

/**
 * @brief Guarda o histórico em ficheiro.
 * Esta função percorre a lista de histórico e escreve cada registo no ficheiro de texto.
 * @param historico Um apontador para a lista de histórico.
 */
void GuardarHistorico(HistoricoRegisto* historico); 

/**
 * @brief Consulta o histórico na consola do Gestor.
 * Esta função exibe os registo de todo histórico na consola.
 * @param historico Um apontador para a lista de histórico.
 * @return Um ponteiro nulo.
 */
HistoricoRegisto* consultarhistorico (HistoricoRegisto* historico); 

/**
 * @brief Lê o ficheiro de texto do histórico.
 * Esta função lê o ficheiro de texto "historico.txt" e armazena os registo na lista de histórico.
 * @param historico Um apontador para a lista de histórico.
 * @return Um apontador para a lista de histórico atualizada.
 */
HistoricoRegisto* lerficheirohistorico(HistoricoRegisto* historico);

/**
 * @brief Consulta o histórico de um cliente específico (logado).
 * Esta função exibe na tela o histórico de viagens de um cliente com base no seu NIF. 
 * @param historico Um apontador para a lista de histórico.
 * @param nif O NIF do cliente para o qual o histórico será consultado.
 */
void consultarHistoricoCliente(HistoricoRegisto* historico, int nif); 

#endif "HISTORICO_H" 