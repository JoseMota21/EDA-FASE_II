#include <stdio.h>
#include <stdbool.h>
#include "API.h" 
#include "Transporte.h"

#ifndef CLIENTE_H
#define CLIENTE_H

/**
 * @brief Tamanho máximo para o nome de um cliente.
 */
#define MAX_NOME_CLIENTE 80  

 /**
  * @brief Tamanho máximo para a morada de um cliente.
  */ 
#define MAX_MORADA_CLIENTE 80 

  /**
   * @brief Tamanho máximo para a password de um cliente. 
   */
#define MAX_PASSWORD 20

/**
 * @brief Estrutura que representa um cliente. 
 *
 * Esta estrutura armazena os dados do cliente, inclui o nome, NIF, saldo, morada, password e o ID do veículo 
 * alugado pelo cliente. Além disso, possui um apontador `seguinte` que aponta para a próxima estrutura de cliente 
 * na lista encadeada. 
 */ 
typedef struct registoCliente {
	
	char nome_cliente[MAX_NOME_CLIENTE]; /**< Nome do cliente */
	int NIF; /**< Número de identificação fiscal do cliente */ 
	float saldo; /**< Saldo do cliente */  
	char morada[MAX_MORADA_CLIENTE]; /**< Morada do cliente */ 
	char password[MAX_PASSWORD];  /**< Password do cliente */
	int IDveiculoAlugado; /**< ID do veículo alugado pelo cliente */
	
	struct registoCliente* seguinte; 

}Cliente; 

/**
 * @brief Resultado de uma tentativa de login.
 *
 * Esta estrutura representa o resultado de uma tentativa de login. Possui um campo booleano `autenticado`
 * que indica se o login foi bem-sucedido ou não, e um campo `cliente` que contém um apontador para a estrutura
 * `Cliente` que corresponde ao cliente autenticado. Se o login for bem-sucedido, o campo `cliente` terá um valor 
 * válido; caso contrário, o campo `cliente` será `NULL`.
 */

typedef struct {
	bool autenticado;	/**< Indica se o login foi bem-sucedido. */
	Cliente* cliente;	/**< Ponteiro para a estrutura Cliente correspondente ao cliente autenticado. */
} LoginResult;

/**
 * @brief Verifica se um cliente com o NIF existe na lista ligada. 
 *
 * A função percorre a lista ligada de clientes e verifica se existe um cliente com o NIF.
 *
 * @param inicio O apontador para o primeiro cliente da lista.
 * @param nif O NIF do cliente a ser verificado. 
 * @return 1 se o cliente com o NIF  existe na lista, 0 caso contrário. 
 */
int ExisteCliente(Cliente* inicio, int nif); 

/**
 * @brief Lista os clientes na consola.
 *
 * Esta função exibe na consola os dados de todos os clientes presentes na lista ligada. 
 *
 * @param inicio O apontador para o primeiro cliente da lista.
 * @return O apontador para o primeiro cliente da lista.
 */
Cliente* listarCliente(Cliente* inicio); 

/**
 * @brief Guarda os dados dos clientes em um ficheiro binário. 
 *
 * Esta função percorre a lista ligada de clientes e escreve os dados de cada cliente no ficheiro binário.
 *
 * @param inicio O apontador para o primeiro cliente da lista. 
 * @return O apontador para o primeiro cliente da lista. 
 */
Cliente* saveficheiroCliente(Cliente* inicio); 

/**
 * @brief Lê os dados dos clientes de ficheiro binário e coloca-os na lista ligada.
 *
 * Esta função lê os dados de cada cliente do ficheiro binário e coloca na lista ligada de clientes. 
 *
 * @param inicio O apontador para o primeiro cliente da lista. 
 * @return O apontador para o primeiro cliente da lista atualizado com os dados lidos do ficheiro.
 */
Cliente* lerFicheiroCliente(Cliente* inicio); 

/**
 * @brief Remove o cliente da lista pelo NIF. 
 *
 * Esta função remove um cliente da lista ligada com base no número de identificação fiscal (NIF) fornecido. 
 *
 * @param inicio O apontador para o primeiro cliente da lista. 
 * @return O apontador para o primeiro cliente da lista após a remoção. 
 */
Cliente* RemoverCliente(Cliente* inicio); 

/**
 * @brief Insere um novo cliente na lista ligada. 
 * 
 * Esta função solicita ao gestor as informações necessárias para criar um novo cliente e o insere na lista ligada. 
 *
 * @param cliente_1 O apontador para o primeiro cliente da lista.
 * @return O apontador para o primeiro cliente da lista atualizado.
 */
Cliente* inputCliente(Cliente* cliente_1); 

/**
 * @brief Realiza o login de um cliente.
 *
 * Esta função permite que um cliente faça login introduzindo seu número de identificação fiscal (NIF) e password. 
 *
 * @param login O apontador para o primeiro cliente da lista.
 * @return O resultado do login, indica se foi autenticado com sucesso e o cliente correspondente. 
 */
LoginResult loginCliente(Cliente* login); 

/**
 * @brief Consulta os dados do cliente logado.
 *
 * Esta função mostra os dados do cliente específico na consola. O cliente logado é aquele que realizou o login. 
 *
 * @param cliente O apontador para o cliente logado.
 * @return O apontador para o cliente logado.
 */
Cliente* clientedados(Cliente* cliente);  

/**
 * @brief Imprime os dados do cliente na consola. 
 * 
 * Esta função imprime na consola os dados do cliente.
 *
 * @param cliente O apontador para o cliente cujos dados devem ser impressos. 
 */
void imprimirDadosCliente(Cliente* cliente); 

/**
 * @brief Altera os dados do cliente.
 *
 * Esta função permite alterar os dados do cliente com base no seu NIF. 
 * O utilizador seleciona o campo a ser alterado e insere os novos dados. 
 *
 * @param inicio O apontador para o início da lista de clientes.   
 * @param nif O NIF do cliente para alterar os dados 
 * @return O apontador para o início da lista atualizada de clientes. 
 */
Cliente* AlterarDadosCliente(Cliente* inicio, int nif); 

/**
 * @brief Guarda as alterações feitas nos dados dos clientes em no ficheiro binário.
 *
 * Esta função recebe o apontador para o início da lista de clientes e salva as alterações 
 * feitas nos dados dos clientes em um ficheiro binário nomeado de "Cliente.bin". 
 *
 * @param inicio O apontador para o início da lista de clientes.
 */
void saveAlterarDados(Cliente* inicio); 

/**
 * @brief Carrega saldo para o cliente logado. 
 *
 * Esta função permite que o cliente carregue saldo na sua conta. Recebe o apontador para o
 * cliente logado e o  NIF como argumentos. Em seguida, solicita ao cliente que insira o
 * saldo a ser carregado e atualiza o saldo do cliente. Também guarda as alterações feitas no
 * saldo no ficheiro binário.
 *
 * @param cliente O apontador para o cliente logado.
 * @param nif O NIF do cliente logado.
 * @return O apontador para o cliente atualizado.
 */
Cliente* carregarSaldo(Cliente* cliente_1, int nif); 

/**
 * @brief Localiza os meios de transporte dentro de um determinado raio a partir de uma localização. 
 *
 * Esta função localiza os meios de transporte disponíveis dentro de um determinado raio, a partir de uma
 * localização específica. Recebe como argumentos a localização atual, o tipo de meio de transporte desejado,
 * o raio em km e a lista de meios de transporte. A função utiliza as coordenadas da localização
 * atual e dos meios de transporte para calcular a distância entre eles, verifica se a distância está dentro
 * do raio especificado. Os meios de transporte encontrados são exibidos na consola. Caso não sejam encontrados
 * meios de transporte dentro do raio ou do tipo especificado, uma mensagem de aviso é exibida ao utilizador.
 *
 * @param localizacaoAtual A localização atual.
 * @param tipoMeio O tipo de meio de transporte pretendido.
 * @param raio O raio em km.
 * @param meio A lista de meios de transporte.
 * @return 0 se a função for executada com sucesso. 
 */
int veiculosRaio(char localizacaoAtual[], char tipoMeio[], int raio, Transporte* meio); 

/**
 * @brief Calcula o raio entre duas coordenadas.
 *
 * A função calcula o raio em km entre duas coordenadas. Recebe os valores de latitude e longitude das duas
 * coordenadas como argumentos. As coordenadas devem estar em graus decimais. A função converte
 * as coordenadas para radianos e calcula a distância entre os pontos recorrendo à fórmula da
 * haversine.
 * Retorna a distância em km. 
 *
 * @param lat1 A latitude da primeira coordenada. 
 * @param lng1 A longitude da primeira coordenada. 
 * @param lat2 A latitude da segunda coordenada. 
 * @param lng2 A longitude da segunda coordenada.
 * @return A distância em km entre as duas coordenadas.
 */
float calcularRaio(float lat1, float lng1, float lat2, float lng2);

#endif "CLIENTE_H" 