#include <stdio.h>
#include <stdbool.h>
#include "API.h" 
#include "Transporte.h"

#ifndef CLIENTE_H
#define CLIENTE_H

/**
 * @brief Tamanho m�ximo para o nome de um cliente.
 */
#define MAX_NOME_CLIENTE 80  

 /**
  * @brief Tamanho m�ximo para a morada de um cliente.
  */ 
#define MAX_MORADA_CLIENTE 80 

  /**
   * @brief Tamanho m�ximo para a password de um cliente. 
   */
#define MAX_PASSWORD 20

/**
 * @brief Estrutura que representa um cliente. 
 *
 * Esta estrutura armazena os dados do cliente, inclui o nome, NIF, saldo, morada, password e o ID do ve�culo 
 * alugado pelo cliente. Al�m disso, possui um apontador `seguinte` que aponta para a pr�xima estrutura de cliente 
 * na lista encadeada. 
 */ 
typedef struct registoCliente {
	
	char nome_cliente[MAX_NOME_CLIENTE]; /**< Nome do cliente */
	int NIF; /**< N�mero de identifica��o fiscal do cliente */ 
	float saldo; /**< Saldo do cliente */  
	char morada[MAX_MORADA_CLIENTE]; /**< Morada do cliente */ 
	char password[MAX_PASSWORD];  /**< Password do cliente */
	int IDveiculoAlugado; /**< ID do ve�culo alugado pelo cliente */
	
	struct registoCliente* seguinte; 

}Cliente; 

/**
 * @brief Resultado de uma tentativa de login.
 *
 * Esta estrutura representa o resultado de uma tentativa de login. Possui um campo booleano `autenticado`
 * que indica se o login foi bem-sucedido ou n�o, e um campo `cliente` que cont�m um apontador para a estrutura
 * `Cliente` que corresponde ao cliente autenticado. Se o login for bem-sucedido, o campo `cliente` ter� um valor 
 * v�lido; caso contr�rio, o campo `cliente` ser� `NULL`.
 */

typedef struct {
	bool autenticado;	/**< Indica se o login foi bem-sucedido. */
	Cliente* cliente;	/**< Ponteiro para a estrutura Cliente correspondente ao cliente autenticado. */
} LoginResult;

/**
 * @brief Verifica se um cliente com o NIF existe na lista ligada. 
 *
 * A fun��o percorre a lista ligada de clientes e verifica se existe um cliente com o NIF.
 *
 * @param inicio O apontador para o primeiro cliente da lista.
 * @param nif O NIF do cliente a ser verificado. 
 * @return 1 se o cliente com o NIF  existe na lista, 0 caso contr�rio. 
 */
int ExisteCliente(Cliente* inicio, int nif); 

/**
 * @brief Lista os clientes na consola.
 *
 * Esta fun��o exibe na consola os dados de todos os clientes presentes na lista ligada. 
 *
 * @param inicio O apontador para o primeiro cliente da lista.
 * @return O apontador para o primeiro cliente da lista.
 */
Cliente* listarCliente(Cliente* inicio); 

/**
 * @brief Guarda os dados dos clientes em um ficheiro bin�rio. 
 *
 * Esta fun��o percorre a lista ligada de clientes e escreve os dados de cada cliente no ficheiro bin�rio.
 *
 * @param inicio O apontador para o primeiro cliente da lista. 
 * @return O apontador para o primeiro cliente da lista. 
 */
Cliente* saveficheiroCliente(Cliente* inicio); 

/**
 * @brief L� os dados dos clientes de ficheiro bin�rio e coloca-os na lista ligada.
 *
 * Esta fun��o l� os dados de cada cliente do ficheiro bin�rio e coloca na lista ligada de clientes. 
 *
 * @param inicio O apontador para o primeiro cliente da lista. 
 * @return O apontador para o primeiro cliente da lista atualizado com os dados lidos do ficheiro.
 */
Cliente* lerFicheiroCliente(Cliente* inicio); 

/**
 * @brief Remove o cliente da lista pelo NIF. 
 *
 * Esta fun��o remove um cliente da lista ligada com base no n�mero de identifica��o fiscal (NIF) fornecido. 
 *
 * @param inicio O apontador para o primeiro cliente da lista. 
 * @return O apontador para o primeiro cliente da lista ap�s a remo��o. 
 */
Cliente* RemoverCliente(Cliente* inicio); 

/**
 * @brief Insere um novo cliente na lista ligada. 
 * 
 * Esta fun��o solicita ao gestor as informa��es necess�rias para criar um novo cliente e o insere na lista ligada. 
 *
 * @param cliente_1 O apontador para o primeiro cliente da lista.
 * @return O apontador para o primeiro cliente da lista atualizado.
 */
Cliente* inputCliente(Cliente* cliente_1); 

/**
 * @brief Realiza o login de um cliente.
 *
 * Esta fun��o permite que um cliente fa�a login introduzindo seu n�mero de identifica��o fiscal (NIF) e password. 
 *
 * @param login O apontador para o primeiro cliente da lista.
 * @return O resultado do login, indica se foi autenticado com sucesso e o cliente correspondente. 
 */
LoginResult loginCliente(Cliente* login); 

/**
 * @brief Consulta os dados do cliente logado.
 *
 * Esta fun��o mostra os dados do cliente espec�fico na consola. O cliente logado � aquele que realizou o login. 
 *
 * @param cliente O apontador para o cliente logado.
 * @return O apontador para o cliente logado.
 */
Cliente* clientedados(Cliente* cliente);  

/**
 * @brief Imprime os dados do cliente na consola. 
 * 
 * Esta fun��o imprime na consola os dados do cliente.
 *
 * @param cliente O apontador para o cliente cujos dados devem ser impressos. 
 */
void imprimirDadosCliente(Cliente* cliente); 

/**
 * @brief Altera os dados do cliente.
 *
 * Esta fun��o permite alterar os dados do cliente com base no seu NIF. 
 * O utilizador seleciona o campo a ser alterado e insere os novos dados. 
 *
 * @param inicio O apontador para o in�cio da lista de clientes.   
 * @param nif O NIF do cliente para alterar os dados 
 * @return O apontador para o in�cio da lista atualizada de clientes. 
 */
Cliente* AlterarDadosCliente(Cliente* inicio, int nif); 

/**
 * @brief Guarda as altera��es feitas nos dados dos clientes em no ficheiro bin�rio.
 *
 * Esta fun��o recebe o apontador para o in�cio da lista de clientes e salva as altera��es 
 * feitas nos dados dos clientes em um ficheiro bin�rio nomeado de "Cliente.bin". 
 *
 * @param inicio O apontador para o in�cio da lista de clientes.
 */
void saveAlterarDados(Cliente* inicio); 

/**
 * @brief Carrega saldo para o cliente logado. 
 *
 * Esta fun��o permite que o cliente carregue saldo na sua conta. Recebe o apontador para o
 * cliente logado e o  NIF como argumentos. Em seguida, solicita ao cliente que insira o
 * saldo a ser carregado e atualiza o saldo do cliente. Tamb�m guarda as altera��es feitas no
 * saldo no ficheiro bin�rio.
 *
 * @param cliente O apontador para o cliente logado.
 * @param nif O NIF do cliente logado.
 * @return O apontador para o cliente atualizado.
 */
Cliente* carregarSaldo(Cliente* cliente_1, int nif); 

/**
 * @brief Localiza os meios de transporte dentro de um determinado raio a partir de uma localiza��o. 
 *
 * Esta fun��o localiza os meios de transporte dispon�veis dentro de um determinado raio, a partir de uma
 * localiza��o espec�fica. Recebe como argumentos a localiza��o atual, o tipo de meio de transporte desejado,
 * o raio em km e a lista de meios de transporte. A fun��o utiliza as coordenadas da localiza��o
 * atual e dos meios de transporte para calcular a dist�ncia entre eles, verifica se a dist�ncia est� dentro
 * do raio especificado. Os meios de transporte encontrados s�o exibidos na consola. Caso n�o sejam encontrados
 * meios de transporte dentro do raio ou do tipo especificado, uma mensagem de aviso � exibida ao utilizador.
 *
 * @param localizacaoAtual A localiza��o atual.
 * @param tipoMeio O tipo de meio de transporte pretendido.
 * @param raio O raio em km.
 * @param meio A lista de meios de transporte.
 * @return 0 se a fun��o for executada com sucesso. 
 */
int veiculosRaio(char localizacaoAtual[], char tipoMeio[], int raio, Transporte* meio); 

/**
 * @brief Calcula o raio entre duas coordenadas.
 *
 * A fun��o calcula o raio em km entre duas coordenadas. Recebe os valores de latitude e longitude das duas
 * coordenadas como argumentos. As coordenadas devem estar em graus decimais. A fun��o converte
 * as coordenadas para radianos e calcula a dist�ncia entre os pontos recorrendo � f�rmula da
 * haversine.
 * Retorna a dist�ncia em km. 
 *
 * @param lat1 A latitude da primeira coordenada. 
 * @param lng1 A longitude da primeira coordenada. 
 * @param lat2 A latitude da segunda coordenada. 
 * @param lng2 A longitude da segunda coordenada.
 * @return A dist�ncia em km entre as duas coordenadas.
 */
float calcularRaio(float lat1, float lng1, float lat2, float lng2);

#endif "CLIENTE_H" 