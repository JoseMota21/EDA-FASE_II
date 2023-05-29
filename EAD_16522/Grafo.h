#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include <float.h>
#include "Cliente.h" 
#include "API.h"

/**
@brief Estrutura que representa um v�rtice do grafo.
A estrutura Vertice cont�m informa��es relacionadas a um v�rtice no grafo.
Ela armazena o geoc�digo, ID, ID do v�rtice, n�vel de bateria, tipo e lista de meios de transporte dispon�veis no v�rtice.
Al�m disso, possui refer�ncias para as arestas adjacentes e o pr�ximo v�rtice na lista.
@note Esta estrutura � usada na representa��o do grafo. 
*/
typedef struct Vertice {
    char geocodigo[100]; 
    int ID;             
    int VerticeID;
    float bateria;       
    char Tipo[20];

    Transporte* meios; 

    struct Aresta* adjacencias; 
    struct Vertice* seguinte;
} Vertice;

/**

@brief Estrutura que representa uma aresta do grafo.
A estrutura Aresta cont�m informa��es relacionadas a uma aresta no grafo.
Ela armazena o v�rtice adjacente, o peso da aresta e a refer�ncia para a pr�xima aresta na lista.
@note Esta estrutura � usada na representa��o do grafo.
*/
typedef struct Aresta {
    int vertice_adjacente; 
    float peso;
   struct Aresta* proximo;
} Aresta;

/**
 * @struct Grafo
 * @brief Estrutura de dados que representa um grafo.
 *
 * A estrutura Grafo cont�m informa��es sobre o n�mero de v�rtices, uma matriz de v�rtices visitados,
 * um array de dist�ncias, uma lista de meios de transporte, uma matriz de arestas adjacentes e uma lista de v�rtices.
 */
typedef struct Grafo {
    int numeroVertices; 
    bool** visitados;
    Transporte* meios; 
    struct Aresta*** matrizadj;     
    struct Vertice* vertices;
} Grafo; 


/**
 * @brief Fun��o para criar os v�rtices do grafo.
 *
 * Esta fun��o cria os v�rtices do grafo com base na lista de meios de transporte fornecida.
 *
 * @param g Ponteiro para o ponteiro do grafo.
 * @param meios Lista de meios de transporte.
 * @return O primeiro v�rtice criado.
 */
Vertice* criarVertices(Grafo** g, Transporte* meios); 

/**
 * @brief Fun��o para encontrar um v�rtice no grafo com base no ID.
 *
 * Esta fun��o percorre a lista de v�rtices do grafo e retorna o v�rtice com o ID fornecido.
 *
 * @param g Ponteiro para o grafo.
 * @param id ID do v�rtice a ser encontrado.
 * @return O v�rtice encontrado ou NULL se n�o for encontrado.
 */ 
Vertice* encontrarVertice(Grafo* g, int id);  

/**

@brief Cria um novo grafo.
@param numeroVertices O n�mero de v�rtices do grafo.
@return Grafo* O ponteiro para a estrutura do grafo criado.
@retval NULL Se ocorrer um erro na aloca��o de mem�ria.
/
Grafo criarGrafo(int numeroVertices);
/**

@brief Aloca mem�ria para a estrutura do grafo e inicializa os seus atributos.
@param numeroVertices O n�mero de v�rtices do grafo.
@return Grafo* O ponteiro para a estrutura do grafo criado.
@retval NULL Se ocorrer um erro na aloca��o de mem�ria.
Esta fun��o aloca mem�ria para a estrutura do grafo e inicializa o n�mero de v�rtices.
Em seguida, aloca mem�ria para a matriz de visitados e a matriz de adjac�ncia do grafo,
e inicializa essas matrizes. Os v�rtices do grafo s�o inicializados como NULL.
Se ocorrer um erro na aloca��o de mem�ria, a fun��o retorna NULL.
*/
Grafo* criarGrafo(int numeroVertices); 

/**

@brief Cria uma nova aresta entre dois v�rtices.
@param g O ponteiro para o grafo.
@param origem O ID do v�rtice de origem.
@param destino O ID do v�rtice de destino.
@param peso O peso da aresta.
@return Aresta* O ponteiro para a nova aresta criada.
@retval NULL Se ocorrer algum erro na cria��o da aresta.
Esta fun��o cria uma nova aresta entre o v�rtice de origem e o v�rtice de destino no grafo fornecido.
Verifica se a origem e o destino s�o v�lidos e se a aresta j� existe entre os v�rtices.
Em seguida, cria a nova aresta e atualiza a matriz de adjac�ncia do grafo.
Se ocorrer algum erro na cria��o da aresta, a fun��o retorna NULL.
*/
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso);  

/**

@brief Imprime o grafo na console.
@param g O ponteiro para o grafo.
Esta fun��o imprime na console a representa��o visual do grafo, exibindo todas as arestas e seus pesos.
A impress�o � feita em formato de tabela, exibindo os IDs dos v�rtices de origem e destino, juntamente com o peso da aresta.
*/
void imprimirGrafo(Grafo* g); 

/**

@brief Lista os v�rtices que representam os meios de transporte.
@param g O ponteiro para o grafo.
@return O ponteiro para o primeiro v�rtice da lista.
Esta fun��o lista na console os v�rtices que representam os meios de transporte presentes no grafo.
Para cada v�rtice, s�o exibidos o ID do v�rtice, o ID do meio de transporte, o tipo de transporte, a bateria e a localiza��o.
A lista � exibida em formato de tabela.
*/
Vertice* listarVertices(Grafo* g); 

/**

@brief Guarda o grafo em um arquivo.
@param g O ponteiro para o grafo.
@return O ponteiro para o grafo.
Esta fun��o salva o grafo em um arquivo de texto chamado "Grafo.txt". O arquivo cont�m as informa��es das arestas do grafo, incluindo a origem, o destino e o peso.
Os dados s�o escritos no formato "ORIGEM;DESTINO;DISTANCIA", onde ORIGEM representa o v�rtice de origem da aresta, DESTINO representa o v�rtice de destino e DISTANCIA representa o peso da aresta.
Se ocorrer algum erro ao criar ou escrever no arquivo, a fun��o exibe uma mensagem de erro na console.
*/
Grafo* guardarGrafo(Grafo* g); 

/**

@brief Conecta todos os v�rtices do grafo.
@param g O ponteiro para o grafo.
Esta fun��o conecta todos os v�rtices do grafo, criando as arestas correspondentes entre eles. A conex�o � estabelecida calculando a dist�ncia entre as coordenadas geogr�ficas dos v�rtices.
Para cada par de v�rtices, s�o obtidas as coordenadas geogr�ficas utilizando o servi�o de geocodifica��o do what3words.
Em seguida, � calculada a dist�ncia entre os v�rtices usando a f�rmula da dist�ncia haversine.
Por fim, � criada uma aresta entre os v�rtices com a dist�ncia calculada.
@note � importante garantir que os v�rtices estejam devidamente inicializados e que as informa��es de geoc�digo estejam corretas antes de chamar esta fun��o.
*/
void conetarVertices(Grafo* g);  

/**

@brief Guarda as informa��es dos v�rtices em um arquivo.
@param g O ponteiro para o grafo.
Esta fun��o guarda as informa��es dos v�rtices do grafo em um arquivo de texto.
Cada linha do arquivo cont�m os seguintes dados de um v�rtice separados por ponto e v�rgula (;):
ID do v�rtice, ID do meio de transporte, tipo de meio de transporte, bateria e localiza��o.
@note Certifique-se de que o grafo e os v�rtices estejam devidamente inicializados antes de chamar esta fun��o.
*/
Grafo* guardarVertices(Grafo* g);  

/**

@brief Realiza o percurso m�nimo para a recolha dos meios de transporte a partir de um v�rtice de origem.
@param g O ponteiro para o grafo.
@param origem O v�rtice de origem do percurso.
Esta fun��o realiza o percurso m�nimo para a recolha dos meios de transporte a partir de um v�rtice de origem.
Utiliza a heur�stica do vizinho mais pr�ximo para construir o caminho a ser percorrido.
Ap�s a constru��o do caminho, realiza a recolha dos meios de transporte, respeitando a capacidade dispon�vel do cami�o.
Imprime na tela o caminho a ser percorrido e os meios de transporte recolhidos.
@note Certifique-se de que o grafo e os v�rtices estejam devidamente inicializados antes de chamar esta fun��o.
@note Esta fun��o assume a exist�ncia das seguintes fun��es auxiliares:
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados): Retorna o v�rtice mais pr�ximo com bateria inferior a 50% que ainda n�o foi visitado.
void imprimirCaminho(int* caminho, int posicao): Imprime na tela o caminho a ser percorrido para a recolha dos meios de transporte.
void recolherMeios(Grafo* g, int origem, Transporte* Recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int* caminho, int posicao): Realiza a recolha dos meios de transporte ao longo do caminho.
void imprimirRecolhidos(Transporte* Recolhidos[], int numeroRecolhidos): Imprime na tela os meios de transporte recolhidos.
*/ 
void percursoMinimo(Grafo* g, int origem);   

/**

@brief Realiza a recolha dos meios de transporte ao longo do caminho.
@param g O apontador para o grafo.
@param origem O v�rtice de origem do percurso.
@param recolhidos Um array de ponteiros para os meios de transporte recolhidos.
@param numeroRecolhidos O n�mero atual de meios de transporte recolhidos.
@param capacidadeCamiao A capacidade total do cami�o de recolha.
@param caminho O array contendo o caminho a ser percorrido para a recolha dos meios de transporte.
@param posicao A posi��o atual no caminho.
Esta fun��o percorre o caminho especificado e realiza a recolha dos meios de transporte encontrados.
A capacidade dispon�vel do cami�o � verificada a cada etapa da recolha para garantir que n�o seja excedida.
Os meios de transporte recolhidos s�o armazenados no array recolhidos e o n�mero atual de recolhidos � atualizado.
Os meios de transporte que n�o puderem ser recolhidos devido � capacidade limitada do cami�o s�o armazenados em naoRecolhidosArray.
@note Certifique-se de que o grafo e os v�rtices estejam devidamente inicializados antes de chamar esta fun��o.
@note Esta fun��o assume a exist�ncia das seguintes fun��es auxiliares:
Transporte* encontrarTransportePorVertice(Grafo* g, int vertice): Retorna o ponteiro para o meio de transporte associado ao v�rtice especificado.
void saveAlterarDadosTransportes(Transporte* head): Salva as altera��es feitas nos dados dos meios de transporte em um arquivo bin�rio.
void atualizarFicheiroNaoRecolhidos(const char* filename, Transporte* naoRecolhidosArray[], int naoRecolhidos): Atualiza o arquivo bin�rio contendo os meios de transporte n�o recolhidos.
void imprimirNaoRecolhidos(Transporte* naoRecolhidosArray[], int naoRecolhidos): Imprime na tela os meios de transporte n�o recolhidos.
void saveNaoRecolhidos(Transporte* naoRecolhidosArray[], int naoRecolhidos, const char* filename): Salva os meios de transporte n�o recolhidos em um arquivo bin�rio.
*/
void recolherMeios(Grafo* g, int origem, Transporte* recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int caminho[], int posicao); 

/**

@brief Imprime na consola o caminho a ser percorrido.
@param caminho O array contendo o caminho a ser percorrido.
@param posicao A posi��o atual no caminho.
Esta fun��o imprime na consola o caminho a ser percorrido para a recolha dos meios de transporte.
@note Certifique-se de que o caminho esteja corretamente definido antes de chamar esta fun��o.
*/
void imprimirCaminho(int caminho[], int posicao); 

/**

@brief Imprime na consola os meios de transporte que foram recolhidos.
@param recolhidos Um array contendo os meios de transporte recolhidos.
@param numeroRecolhidos O n�mero de meios de transporte recolhidos.
Esta fun��o imprime na consola os meios de transporte que foram recolhidos durante o percurso.
@note Certifique-se de que os meios de transporte recolhidos estejam corretamente definidos antes de chamar esta fun��o.
*/
void imprimirRecolhidos(Transporte* recolhidos[], int numeroRecolhidos); 

/**

@brief Imprime na console os meios de transporte n�o recolhidos.
@param naoRecolhidos Um array que cont�m os apontadores para os meios de transporte n�o recolhidos.
@param numeroNaoRecolhidos O n�mero de meios de transporte n�o recolhidos.
Esta fun��o imprime na console os meios de transporte n�o recolhidos.
Recebe um array de apontadores para os meios de transporte n�o recolhidos e o n�mero total de meios n�o recolhidos. 
A fun��o itera sobre o array e imprime o ID e o tipo de cada meio de transporte n�o recolhido.  
*/
void imprimirNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos);

/**

@brief Encontra o meio de transporte associado a um determinado v�rtice.
@param g O grafo que cont�m os v�rtices e os meios de transporte.
@param verticeID O ID do v�rtice.
@return O meio de transporte encontrado, ou NULL se nenhum meio de transporte estiver associado ao v�rtice.
Esta fun��o percorre a lista de v�rtices do grafo e verifica se o ID do v�rtice corresponde ao ID desejado.
Se um meio de transporte estiver associado ao v�rtice, ele ser� retornado. Caso contr�rio, a fun��o retorna NULL.
@note Certifique-se de que o grafo e os v�rtices estejam corretamente definidos antes de chamar esta fun��o.
*/
Transporte* encontrarTransportePorVertice(Grafo* g, int verticeID); 

/**

@brief Encontra o v�rtice mais pr�ximo com bateria inferior a 50% a partir de um v�rtice atual.
@param g O grafo que cont�m os v�rtices e as arestas.
@param verticeAtual O ID do v�rtice atual.
@param visitados Um vetor de booleanos indicando quais v�rtices foram visitados.
@return O ID do v�rtice mais pr�ximo com bateria inferior a 50%, ou -1 se n�o houver v�rtices dispon�veis.
Esta fun��o percorre as arestas do v�rtice atual e verifica se o v�rtice adjacente tem bateria inferior a 50%.
Se o v�rtice atender a essa condi��o e tiver um peso menor que os v�rtices anteriores, ele � considerado o mais pr�ximo.
Caso contr�rio, o v�rtice mais pr�ximo atual permanece o mesmo.
A fun��o retorna o ID do v�rtice mais pr�ximo encontrado ou -1 se nenhum v�rtice estiver dispon�vel.
@note Certifique-se de que o grafo, as arestas e os v�rtices estejam corretamente definidos antes de chamar esta fun��o.
*/
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados);  

/**

@brief Guarda os meios de transporte n�o recolhidos em um arquivo bin�rio.
@param naoRecolhidos Um vetor de ponteiros para os meios de transporte n�o recolhidos.
@param numeroNaoRecolhidos O n�mero de meios de transporte n�o recolhidos.
@param TransportesNaoRecolhidos O nome do arquivo onde os dados ser�o salvos.
Esta fun��o recebe um vetor de ponteiros para os meios de transporte n�o recolhidos,
o n�mero de meios de transporte n�o recolhidos e o nome do arquivo onde os dados ser�o salvos.
A fun��o abre o arquivo no modo de escrita bin�ria, escreve o n�mero de meios de transporte n�o recolhidos
e em seguida escreve cada meio de transporte n�o recolhido no arquivo.
Ap�s salvar os dados, o arquivo � fechado.
@note Certifique-se de que os meios de transporte n�o recolhidos e o nome do arquivo estejam corretamente definidos antes de chamar esta fun��o.
*/
void saveNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos, const char* TransportesNaoRecolhidos);  

/**

@brief L� os dados de um arquivo contendo os meios de transporte n�o recolhidos.
@param TransportesNaoRecolhidos O nome do arquivo que cont�m os dados dos meios de transporte n�o recolhidos.
Esta fun��o l� os dados de um arquivo bin�rio que cont�m os meios de transporte n�o recolhidos.
A fun��o abre o arquivo no modo de leitura bin�ria, l� o n�mero de meios de transporte n�o recolhidos,
aloca mem�ria para armazenar os dados e l� os dados do arquivo.
Em seguida, imprime os dados lidos na console, indicando o ID e o tipo de cada meio de transporte n�o recolhido.
Por fim, a mem�ria alocada para armazenar os dados � liberada.
@note Certifique-se de que o nome do arquivo esteja corretamente definido antes de chamar esta fun��o.
*/
void lerDadosDeArquivo(const char* TransportesNaoRecolhidos); 

/**

@brief Atualiza o arquivo de meios de transporte n�o recolhidos.
@param nomeArquivo O nome do arquivo a ser atualizado.
@param naoRecolhidosArray Um array contendo os dados dos meios de transporte n�o recolhidos.
@param numeroNaoRecolhidos O n�mero de meios de transporte n�o recolhidos.
Esta fun��o atualiza o arquivo de meios de transporte n�o recolhidos com os dados fornecidos.
Ela recebe o nome do arquivo, um array contendo os dados dos meios de transporte n�o recolhidos e o n�mero total de meios n�o recolhidos.
A fun��o abre o arquivo em modo de escrita bin�ria, escreve o n�mero de meios n�o recolhidos e em seguida escreve os dados de cada meio de transporte no arquivo.
Por fim, o arquivo � fechado.
@note Certifique-se de que os par�metros foram corretamente preenchidos antes de chamar esta fun��o.
*/
void atualizarFicheiroNaoRecolhidos (const char* nomeArquivo, Transporte* naoRecolhidosArray, int numeroNaoRecolhidos);  

void imprimirMeiosNaoRecolhidos(Transporte* naoRecolhidosArray, int numeroNaoRecolhidos); 