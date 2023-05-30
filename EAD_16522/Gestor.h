#include <stdio.h>
#include <stdbool.h> 

/**
 * @brief Estrutura de dados para representar um registo de gestor.
 * A estrutura `Gestor` armazena informa��es sobre um gestor, incluindo nome, email e password.
 * Tamb�m possui um apontador para o pr�ximo gestor na lista. 
 */
typedef struct registoGestor {

	char nome[100]; /** <Nome do gestor */
	char email[100]; /**<Email do gestor */ 
	char password[100]; /**<senha do gestor */ 

	struct resgistoGestor* seguinte;  /** < Apontador para o proximo gestor da lista */ 

}Gestor;

/** 
 * @brief Estrutura de dados para representar o estado de login de um gestor.
 * A estrutura `loginGestor` armazena informa��es sobre o estado de login de um gestor,
 * incluindo se est� autenticado e um apontador para o gestor autenticado.
 */
typedef struct {
	bool autenticado; ///<Gestor logado 
	Gestor* gestor; ///<Apontador para o gestor autenticado
} loginGestor;

/**
 * @brief Insere um novo gestor na lista de gestores.
 * A fun��o `inserirGestor` cria uma nova inst�ncia da estrutura `Gestor`,
 * solicita informa��es ao gestor para preencher os dados do novo gestor e
 * adiciona-o no in�cio da lista de gestores.
 *
 * @param gestor_1 Apontador para o in�cio da lista de gestores.
 * @return O apontador para o novo gestor inserido.
 */
Gestor* inserirGestor(Gestor* gestor_1);

/**
 * @brief Verifica se j� existe um gestor com o email inserido.
 * A fun��o `existeGestor` percorre a lista de gestores a partir do gestor
 * passado como par�metro e verifica se existe algum gestor com o email
 * fornecido. Retorna o apontador para o gestor encontrado ou NULL caso n�o
 * exista.
 * @param gestor_1 Apontador para o in�cio da lista de gestores.
 * @param email Email a ser verificado.
 * @return O apontador para o gestor encontrado ou NULL caso n�o exista.
 */
Gestor* existeGestor(Gestor* gestor_1, const char* email); 
 
/**
 * @brief guarda os dados dos gestores em um ficheiro de texto.
 * A fun��o `saveficheiroGestor` percorre a lista de gestores a partir do gestor
 * passado como par�metro e escreve os dados de cada gestor em um ficheiro de texto.
 * Os dados s�o separados por ponto e v�rgula (;). Retorna o apontador para o in�cio
 * da lista de gestores.
 * @param inicio Apontador para o in�cio da lista de gestores.
 * @return O apontador para o in�cio da lista de gestores.
 */
Gestor* saveficheiroGestor(Gestor* inicio);

/**
 * @brief L� os dados dos gestores a partir de um arquivo de texto.
 * A fun��o `lerficheiroGestor` abre o arquivo de texto "Gestor.txt" e percorre cada linha,
 * armazena os dados na estrutura de gestor. Os dados s�o lidos na seguinte ordem:
 * nome, email e senha. Em seguida, o novo gestor � adicionado ao final da lista de gestores.
 * Retorna o apontador para o in�cio da lista de gestores.
 * @param inicio Apontador para o in�cio da lista de gestores.
 * @return O apontador para o in�cio da lista de gestores.
 */
Gestor* lerficheiroGestor(Gestor* inicio); 

/**
 * @brief Realiza o login de um gestor.
 * A fun��o `gestorlogin` solicita ao gestor que insira seu email e senha. Em seguida, ela percorre a lista de gestores
 * para encontrar um gestor que corresponda ao email e password fornecidos. Se encontrar um gestor correspondente, define o
 * campo `autenticado` como verdadeiro e armazena as informa��es do gestor no campo `gestor` da estrutura `loginGestor`.
 * Caso contr�rio, define o campo `autenticado` como falso. Retorna a estrutura `loginGestor` contendo as informa��es
 * sobre a autentica��o do gestor.
 * @param Login Apontador para o in�cio da lista de gestores.
 * @return A estrutura `loginGestor` contendo as informa��es sobre a autentica��o do gestor.
 */
loginGestor gestorlogin(Gestor* Login); 

