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
    char geocodigo[100];    /** <Localiza��o */
    int ID;                /** <ID do meio de transporte */ 
    int VerticeID;        /** <ID do v�rtice */
    float bateria;       /** <Bateria do meio de transporte */ 
    char Tipo[20];      /** <Tipo de meio de transporte(BIKE) (TROTINETE) */ 
    Transporte* meios; /** <Estrutura dos meios de transporte*/ 

    struct Aresta* adjacencias;  /**< Apontador para as arestas adjacentes */ 
    struct Vertice* seguinte;  /**< Apontador para o pr�ximo v�rtice na lista */  
} Vertice;

/**

@brief Estrutura que representa uma aresta do grafo.
A estrutura Aresta cont�m informa��es relacionadas a uma aresta no grafo.
Ela armazena o v�rtice adjacente, o peso da aresta e a refer�ncia para a pr�xima aresta na lista.
@note Esta estrutura � utilizada na representa��o do grafo.
*/
typedef struct Aresta {
    int vertice_adjacente;  /** <Vertice vizinho */ 
    float peso;             /** <Peso da aresta (Distancia) */ 
   struct Aresta* proximo;  /** <Proxima aresta */ 
} Aresta;

/**
 * @struct Grafo
 * @brief Estrutura de dados que representa o grafo.
 *
 * A estrutura Grafo cont�m informa��es sobre o n�mero de v�rtices, uma matriz de v�rtices visitados,
 * um array de dist�ncias, uma lista de meios de transporte, uma matriz de arestas adjacentes e uma lista de v�rtices.
 */
typedef struct Grafo {
    int numeroVertices; /** <N�mero de v�rtices no grafo */ 
    bool** visitados;   /** <Vistados */ 
    Transporte* meios;  /** <Estrutura dos meios de transporte */ 
    struct Aresta*** matrizadj;    /** < Matriz de adjacencia */
    struct Vertice* vertices;       /** < Lista de v�rtices */
} Grafo; 

/**
 * @brief Fun��o para criar os v�rtices do grafo.
 *
 * Esta fun��o cria os v�rtices do grafo com base na lista de meios de transporte . 
 *
 * @param g Apontador para o apontador do grafo.
 * @param meios Lista de meios de transporte.
 * @return O primeiro v�rtice criado.
 */
Vertice* criarVertices(Grafo** g, Transporte* meios); 

/**
 * @brief Fun��o para encontrar um v�rtice no grafo com base no ID.
 *
 * A fun��o percorre a lista de v�rtices do grafo e retorna o v�rtice com o ID fornecido.
 *
 * @param g Apontador para o grafo.
 * @param id ID do v�rtice a ser encontrado. 
 * @return O v�rtice encontrado ou NULL se n�o for encontrado. 
 */ 
Vertice* encontrarVertice(Grafo* g, int id);  

/**

@brief Cria o novo grafo.
@param numeroVertices O n�mero de v�rtices do grafo.
@return Grafo* O apontador para a estrutura do grafo criado.
@retval NULL Se ocorrer um erro na aloca��o de mem�ria. 

@brief Aloca mem�ria para a estrutura do grafo e inicializa os seus atributos.
@param numeroVertices O n�mero de v�rtices do grafo. 
@return Grafo* O apontador para a estrutura do grafo criado.
@retval NULL Se ocorrer um erro na aloca��o de mem�ria. 
Esta fun��o aloca mem�ria para a estrutura do grafo e inicializa o n�mero de v�rtices.
Em seguida, aloca mem�ria para a matriz de visitados e a matriz de adjac�ncia do grafo,
e inicializa essas matrizes. Os v�rtices do grafo s�o inicializados como NULL.
Se ocorrer um erro na aloca��o de mem�ria, a fun��o retorna NULL.
*/
Grafo* criarGrafo(int numeroVertices); 

/**

@brief Cria uma nova aresta entre dois v�rtices.
@param g Apontador para o grafo.
@param origem O ID do v�rtice de origem.
@param destino O ID do v�rtice de destino.
@param peso O peso da aresta.
@return Aresta* O apontador para a nova aresta criada.
@retval NULL Se ocorrer algum erro na cria��o da aresta.
Esta fun��o cria uma nova aresta entre o v�rtice de origem e o v�rtice de destino no grafo fornecido.
Verifica se a origem e o destino s�o v�lidos e se a aresta j� existe entre os v�rtices.
Em seguida, cria a nova aresta e atualiza a matriz de adjac�ncia do grafo.
Se ocorrer algum erro na cria��o da aresta, a fun��o retorna NULL.
*/
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso);  

/**

@brief Imprime o grafo na consola.
@param g O apontador para o grafo.
Esta fun��o imprime na consola a representa��o visual do grafo, exibe todas as arestas e seus pesos. 
A impress�o � feita em formato de tabela, com os IDs dos v�rtices de origem e destino, juntamente com o peso da aresta. 
*/
void imprimirGrafo(Grafo* g); 

/**

@brief Lista os v�rtices que representam os meios de transporte.
@param g O apontador para o grafo.
@return O apontador para o primeiro v�rtice da lista.
Esta fun��o lista na consola os v�rtices que representam os meios de transporte presentes no grafo. 
Para cada v�rtice, s�o exibidos o ID do v�rtice, o ID do meio de transporte, o tipo de transporte, a bateria e a localiza��o.

*/
Vertice* listarVertices(Grafo* g); 

/**

@brief Guarda o grafo em um ficheiro.
@param g O apontador para o grafo.
@return O apontador para o grafo.
Esta fun��o gaurda o grafo em um ficheiro de texto com o nome de "Grafo.txt". O ficheiro cont�m as informa��es das arestas do grafo, incluindo a origem, o destino e o peso.
Os dados s�o escritos no formato "ORIGEM;DESTINO;DISTANCIA", onde ORIGEM representa o v�rtice de origem da aresta, DESTINO representa o v�rtice de destino e DISTANCIA representa o peso da aresta.
Se ocorrer algum erro ao criar ou escrever no ficheiro, a fun��o exibe uma mensagem de erro na consola.
*/
Grafo* guardarGrafo(Grafo* g); 

/**

@brief Conecta todos os v�rtices do grafo.
@param g O apontador para o grafo.
Esta fun��o liga todos os v�rtices do grafo, cria as arestas correspondentes entre eles. A conetividade � realizada com o calcula da dist�ncia entre as coordenadas.
Para cada par de v�rtices, s�o obtidas as coordenadas. 
Em seguida, � calculada a dist�ncia entre os v�rtices recorrendo � f�rmula da dist�ncia haversine. 
Por fim, � criada uma aresta entre os v�rtices com a dist�ncia calculada. 
*/
void conetarVertices(Grafo* g);  

/**

@brief Guarda as informa��es dos v�rtices em um ficheiro.
@param g O apontador para o grafo.
Esta fun��o guarda os dados dos v�rtices do grafo num ficheiro de texto. 
Cada linha do ficheiro cont�m os dados de um v�rtice separados por ponto e v�rgula (;):
ID do v�rtice, ID do meio de transporte, tipo de meio de transporte, bateria e localiza��o.
*/
Grafo* guardarVertices(Grafo* g);  

/**

@brief Realiza o percurso m�nimo para a recolha dos meios de transporte a partir de um v�rtice de origem.
@param g O apontador para o grafo.
@param origem O v�rtice de origem (armaz�m) do percurso.
Esta fun��o realiza o percurso m�nimo para a recolha dos meios de transporte a partir de um v�rtice de origem.
Utiliza a heur�stica do vizinho mais pr�ximo para construir o caminho a ser percorrido.
Ap�s a constru��o do caminho, realiza a recolha dos meios de transporte, respeitando a capacidade dispon�vel do cami�o.
Imprime na consola o caminho a ser percorrido e os meios de transporte recolhidos. 
@note O grafo e os v�rtices tem que estar inicializados
@note Esta fun��o necessita das seguintes fun��es auxiliares: 
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados): Retorna o v�rtice mais pr�ximo com bateria inferior a 50% que ainda n�o foi visitado.
void imprimirCaminho(int* caminho, int posicao): Imprime na tela o caminho a ser percorrido para a recolha dos meios de transporte.
void recolherMeios(Grafo* g, int origem, Transporte* Recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int* caminho, int posicao): Realiza a recolha dos meios de transporte ao longo do caminho.
void imprimirRecolhidos(Transporte* Recolhidos[], int numeroRecolhidos): Imprime na consola os meios de transporte recolhidos.
*/ 
void percursoMinimo(Grafo* g, int origem);   

/**

@brief Realiza a recolha dos meios de transporte ao longo do caminho.
@param g O apontador para o grafo.
@param origem O v�rtice de origem do percurso.
@param recolhidos Um array de apontadores para os meios de transporte recolhidos.
@param numeroRecolhidos O n�mero atual de meios de transporte recolhidos.
@param capacidadeCamiao A capacidade total do cami�o de recolha.
@param caminho O array que coont�m o caminho a ser percorrido para a recolha dos meios de transporte. 
@param posicao A posi��o atual no caminho. 
Esta fun��o percorre o caminho especificado e realiza a recolha dos meios de transporte encontrados.
A capacidade dispon�vel do cami�o � verificada a cada etapa da recolha para garantir que n�o seja excedida. 
Os meios de transporte recolhidos s�o armazenados no array recolhidos e o n�mero atual de recolhidos � atualizado.
Os meios de transporte que n�o puderem ser recolhidos devido � capacidade limitada do cami�o s�o armazenados em naoRecolhidosArray.
@note O grafo e os v�rtices tem que estar inicializados
@note A fun��o utiliza as seguintes fun��es auxiliares: 
Transporte* encontrarTransportePorVertice(Grafo* g, int vertice): Retorna o apontador para o meio de transporte associado ao v�rtice.
void saveAlterarDadosTransportes(Transporte* head): Guarda as altera��es feitas nos dados dos meios de transporte em um ficheiro bin�rio.
void atualizarFicheiroNaoRecolhidos(const char* filename, Transporte* naoRecolhidosArray[], int naoRecolhidos): Atualiza o ficheiro bin�rio contendo os meios de transporte n�o recolhidos.
void imprimirNaoRecolhidos(Transporte* naoRecolhidosArray[], int naoRecolhidos): Imprime na consola os meios de transporte n�o recolhidos.
void saveNaoRecolhidos(Transporte* naoRecolhidosArray[], int naoRecolhidos, const char* filename): Guarda os meios de transporte n�o recolhidos em um ficheiro bin�rio.
*/
void recolherMeios(Grafo* g, int origem, Transporte* recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int caminho[], int posicao); 

/**

@brief Imprime na consola o caminho a ser percorrido.
@param caminho O array contem o caminho a ser percorrido.
@param posicao A posi��o atual no caminho.
Esta fun��o imprime na consola o caminho a ser percorrido para a recolha dos meios de transporte.
@note Caminho tem que estar definido para chamar a fun��o
*/
void imprimirCaminho(int caminho[], int posicao); 

/**

@brief Imprime na consola os meios de transporte que foram recolhidos.
@param recolhidos Um array contem os meios de transporte recolhidos.
@param numeroRecolhidos O n�mero de meios de transporte recolhidos.
Esta fun��o imprime na consola os meios de transporte que foram recolhidos durante o percurso.
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
void imprimirNaoRecolhidos (Transporte* naoRecolhidos[], int numeroNaoRecolhidos); 

/**

@brief Encontra o meio de transporte associado a um determinado v�rtice. 
@param g O grafo que cont�m os v�rtices e os meios de transporte.
@param verticeID O ID do v�rtice.
@return O meio de transporte encontrado, ou NULL se nenhum meio de transporte estiver associado ao v�rtice. 
Esta fun��o percorre a lista de v�rtices do grafo e verifica se o ID do v�rtice corresponde ao ID desejado. 
Se um meio de transporte estiver associado ao v�rtice, ele ser� retornado. Caso contr�rio, a fun��o retorna NULL.
@note Grafo e v�rtices tem que estar definidos
*/
Transporte* encontrarTransportePorVertice(Grafo* g, int verticeID); 

/**

@brief Encontra o v�rtice mais pr�ximo com bateria inferior a 50% a partir de um v�rtice atual. 
@param g O grafo que cont�m os v�rtices e as arestas. 
@param verticeAtual O ID do v�rtice atual. 
@param visitados Um vetor de booleanos que indica quais v�rtices que foram visitados.
@return O ID do v�rtice mais pr�ximo com bateria inferior a 50%, ou -1 se n�o houver v�rtices dispon�veis. 
Esta fun��o percorre as arestas do v�rtice atual e verifica se o v�rtice adjacente tem bateria inferior a 50%. 
Se o v�rtice atender a essa condi��o e tiver um peso menor que os v�rtices anteriores, ele � considerado o mais pr�ximo.
Caso contr�rio, o v�rtice mais pr�ximo atual permanece o mesmo.
A fun��o retorna o ID do v�rtice mais pr�ximo encontrado ou -1 se nenhum v�rtice estiver dispon�vel. 
@note O grafo, as arestas e os v�rtices estejam corretamente definidos antes de chamar esta fun��o.
*/
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados);  

/**

@brief Guarda os meios de transporte n�o recolhidos em um ficheiro bin�rio.
@param naoRecolhidos Um vetor de apontadores para os meios de transporte n�o recolhidos.
@param numeroNaoRecolhidos O n�mero de meios de transporte n�o recolhidos.
@param TransportesNaoRecolhidos O nome do ficheiro onde os dados s�o guardados.
Esta fun��o recebe um vetor de apontadores para os meios de transporte n�o recolhidos,
o n�mero de meios de transporte n�o recolhidos e o nome do ficheiro onde os dados ser�o salvos.
A fun��o abre o arquivo no modo de escrita bin�ria, escreve o n�mero de meios de transporte n�o recolhidos
e em seguida escreve cada meio de transporte n�o recolhido no ficheiro.
Ap�s gaurdar os dados, o ficheiro � fechado.
@note Os meios de transporte n�o recolhidos e o nome do arquivo estejam corretamente definidos antes de chamar esta fun��o.
*/
void saveNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos, const char* TransportesNaoRecolhidos);  

/**

@brief L� os dados de um ficheiro que cont�m os meios de transporte n�o recolhidos.
@param TransportesNaoRecolhidos O nome do ficheiro que cont�m os dados dos meios de transporte n�o recolhidos.
Esta fun��o l� os dados de um ficheiro bin�rio que cont�m os meios de transporte n�o recolhidos.
A fun��o abre o ficheiro no modo de leitura bin�ria, l� o n�mero de meios de transporte n�o recolhidos,
aloca mem�ria para armazenar os dados e l� os dados do arquivo.
Em seguida, imprime os dados lidos na consola, e indica o ID e o tipo de cada meio de transporte n�o recolhido.
Por fim, a mem�ria alocada para armazenar os dados � libertda.
@note O nome do ficheiro tem que estar corretamente definido antes de chamar esta fun��o.  
*/
void lerDadosDeArquivo(const char* TransportesNaoRecolhidos); 

/**

@brief Atualiza o ficheiro de meios de transporte n�o recolhidos.
@param nomeArquivo O nome do ficheiro a ser atualizado.
@param naoRecolhidosArray Um array que cont�m os dados dos meios de transporte n�o recolhidos. 
@param numeroNaoRecolhidos O n�mero de meios de transporte n�o recolhidos. 
Esta fun��o atualiza o ficheiro de meios de transporte n�o recolhidos com os dados pretendidos. 
Recebe o nome do ficheiro, um array que cont�m os dados dos meios de transporte n�o recolhidos e o n�mero total de meios n�o recolhidos. 
A fun��o abre o ficheiro em modo de escrita bin�ria, escreve o n�mero de meios n�o recolhidos e em seguida escreve os dados de cada meio de transporte no arquivo.
Por fim, o ficheiro � fechado.

*/
void atualizarFicheiroNaoRecolhidos (const char* nomeArquivo, Transporte* naoRecolhidosArray, int numeroNaoRecolhidos);  

/**
 * Imprime na consola os meios de transporte que n�o foram recolhidos.
 * @param naoRecolhidosArray O array de meios de transporte n�o recolhidos. 
 * @param numeroNaoRecolhidos O n�mero de meios de transporte n�o recolhidos. 
 */
void imprimirMeiosNaoRecolhidos(Transporte* naoRecolhidosArray, int numeroNaoRecolhidos); 