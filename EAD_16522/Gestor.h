#include <stdio.h>
#include <stdbool.h> 

/**
 * @brief Estrutura de dados para representar um registo de gestor.
 * A estrutura `Gestor` armazena informações sobre um gestor, incluindo nome, email e password.
 * Também possui um apontador para o próximo gestor na lista. 
 */
typedef struct registoGestor {

	char nome[100]; /** <Nome do gestor */
	char email[100]; /**<Email do gestor */ 
	char password[100]; /**<senha do gestor */ 

	struct resgistoGestor* seguinte;  /** < Apontador para o proximo gestor da lista */ 

}Gestor;

/** 
 * @brief Estrutura de dados para representar o estado de login de um gestor.
 * A estrutura `loginGestor` armazena informações sobre o estado de login de um gestor,
 * incluindo se está autenticado e um apontador para o gestor autenticado.
 */
typedef struct {
	bool autenticado; ///<Gestor logado 
	Gestor* gestor; ///<Apontador para o gestor autenticado
} loginGestor;

/**
 * @brief Insere um novo gestor na lista de gestores.
 * A função `inserirGestor` cria uma nova instância da estrutura `Gestor`,
 * solicita informações ao gestor para preencher os dados do novo gestor e
 * adiciona-o no início da lista de gestores.
 *
 * @param gestor_1 Apontador para o início da lista de gestores.
 * @return O apontador para o novo gestor inserido.
 */
Gestor* inserirGestor(Gestor* gestor_1);

/**
 * @brief Verifica se já existe um gestor com o email inserido.
 * A função `existeGestor` percorre a lista de gestores a partir do gestor
 * passado como parâmetro e verifica se existe algum gestor com o email
 * fornecido. Retorna o apontador para o gestor encontrado ou NULL caso não
 * exista.
 * @param gestor_1 Apontador para o início da lista de gestores.
 * @param email Email a ser verificado.
 * @return O apontador para o gestor encontrado ou NULL caso não exista.
 */
Gestor* existeGestor(Gestor* gestor_1, const char* email); 
 
/**
 * @brief guarda os dados dos gestores em um ficheiro de texto.
 * A função `saveficheiroGestor` percorre a lista de gestores a partir do gestor
 * passado como parâmetro e escreve os dados de cada gestor em um ficheiro de texto.
 * Os dados são separados por ponto e vírgula (;). Retorna o apontador para o início
 * da lista de gestores.
 * @param inicio Apontador para o início da lista de gestores.
 * @return O apontador para o início da lista de gestores.
 */
Gestor* saveficheiroGestor(Gestor* inicio);

/**
 * @brief Lê os dados dos gestores a partir de um arquivo de texto.
 * A função `lerficheiroGestor` abre o arquivo de texto "Gestor.txt" e percorre cada linha,
 * armazena os dados na estrutura de gestor. Os dados são lidos na seguinte ordem:
 * nome, email e senha. Em seguida, o novo gestor é adicionado ao final da lista de gestores.
 * Retorna o apontador para o início da lista de gestores.
 * @param inicio Apontador para o início da lista de gestores.
 * @return O apontador para o início da lista de gestores.
 */
Gestor* lerficheiroGestor(Gestor* inicio); 

/**
 * @brief Realiza o login de um gestor.
 * A função `gestorlogin` solicita ao gestor que insira seu email e senha. Em seguida, ela percorre a lista de gestores
 * para encontrar um gestor que corresponda ao email e password fornecidos. Se encontrar um gestor correspondente, define o
 * campo `autenticado` como verdadeiro e armazena as informações do gestor no campo `gestor` da estrutura `loginGestor`.
 * Caso contrário, define o campo `autenticado` como falso. Retorna a estrutura `loginGestor` contendo as informações
 * sobre a autenticação do gestor.
 * @param Login Apontador para o início da lista de gestores.
 * @return A estrutura `loginGestor` contendo as informações sobre a autenticação do gestor.
 */
loginGestor gestorlogin(Gestor* Login); 

