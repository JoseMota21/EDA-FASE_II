#include <stdio.h>
#include <stdbool.h> 

#ifndef TRANSPORTE_H 
#define TRANSPORTE_H  

/**
 * Estrutura para o registo do meio de mobilidade eletrica.
 */
typedef struct registo {
	int codigo; /** <ID do meio de transporte */
	char tipo[10]; /** <Tipo de meio de transporte (BIKE ou TROTINETE) */
	float bateria; /**< Bateria do meio de transporte */
	float autonomia; /**< Autonomia do restante km */
	char geocodigo[100]; /**< Localiza��o what3words */
	int disponivel; /**< Transporte disponivel */
	int volume; /** < Volume que cada meio de transporte ocupa */

	struct registo* seguinte;  

}Transporte;  

/**
 * Verifica se existe um meio de transporte com o ID do meio de tranporte. 
 * 
 * @param inicio aponrtador para o in�cio da lista de meios de transporte.
 * @param id ID do meio de transporte a ser verificado.
 * @return 1 se o meio de transporte existe, 0 caso contr�rio.
 */
int ExisteTransporte(Transporte* Inicio, int ID);

/**
* Solicita ao utilizador (Gestor) as informa��es de um novo meio de transporte e adiciona-o � lista.
*
* @param meioTransporte_1 aponrtador para o in�cio da lista de meios de transporte.
* @return apontador para o in�cio atualizado da lista de meios de transporte.
*/
Transporte* inputTransporte(Transporte* meioTransporte_1); 

/**
 * Remove o meio de transporte da lista com base no ID inserido pelo o utilizador.
 *
 * @param inicio apontador para o in�cio da lista de meios de transporte. 
 * @return apontador para o in�cio atualizado da lista de meios de transporte.
 */
Transporte* RemoverTransporte(Transporte* inicio);

/**
 * Lista os meios de transporte na consola.
 *
 * @param inicio apontador para o in�cio da lista de meios de transporte.
 * @return retorna 0. 
 */
Transporte* listarTransporte(Transporte* Inicio);

/**
 * Guarda as dados dos meios de transporte em ficheiro bin�rio.
 *
 * @param inicio apontador para o in�cio da lista de meios de transporte.
 * @return Retorna o apontador para o in�cio da lista de meios de transporte.
 */
Transporte* saveficheiroTransporte(Transporte* inicio);

/**
 * L� as dados dos meios de transporte a partir de um ficheiro bin�rio.
 *
 * @param inicio apontador para o in�cio da lista de meios de transporte.
 * @return Retorna o apontador para o in�cio da lista de meios de transporte.
 */
Transporte* lerFicheiroTransporte(Transporte* inicio);

/**
 * Troca as informa��es entre dois meios de transporte.
 *
 * @param t1 apontador para o primeiro meio de transporte.
 * @param t2 apontador para o segundo meio de transporte.
 */
void OrdenarTransportesPorAutonomiaDecrescente(Transporte* inicio);

/**
 * Imprime os dados atuais de todos os transportes da lista. 
 *
 * @param transporte apontador para o in�cio da lista de transportes.
 */
void imprimirListaTransportes(Transporte* transporte); 

/**
 * Permite ao utilizador alterar os dados de um meio de transporte espec�fico. 
 *
 * @param inicio apontador para o in�cio da lista de transportes. 
 * @return O apontador para o in�cio da lista de transportes ap�s as altera��es. 
 */
Transporte* AlterarDadosTransporte(Transporte* inicio);

/**
 * Guarda os dados dos transportes em um ficheiro tempor�rio.
 *
 * @param inicio apontador para o in�cio da lista de transportes.
 */
void saveAlterarDadosTransportes(Transporte* inicio);

/**
 * Mostra os meios de transporte dispon�veis na consola
 *
 * @param meioTransporte_1 apontador para o primeiro meio de transporte da lista.
 * @return Retorna 0.
 */
Transporte* transportesDisponiveis(Transporte* meioTransporte_1);

/**
 * Mostra os transportes na localidade pretendida.
 *
 * @param inicio apontador para o in�cio da lista de transportes.
 * @param localidade Nome da localidade a ser pesquisada. 
 * @return Retorna 1 se houver transportes na localidade, caso contr�rio retorna 0.
 */
int TransportePorLocalidade(Transporte* inicio, char* localidade);

/**
 * Imprime na consola os meios de transporte com a bateria inferior a 50%.
 *
 * @param inicio apontador para o in�cio da lista de transportes.
 * @return Retorna o apontador para o in�cio da lista de transportes.
 */
Transporte* inferior50(Transporte* inicio);

#endif "TRANSPORTE_H"  

