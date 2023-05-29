#include <stdio.h>
#include <stdbool.h> 
#include "Transporte.h" 
#include <float.h>
#include "Cliente.h" 
#include "API.h"

/**
@brief Estrutura que representa um vértice do grafo.
A estrutura Vertice contém informações relacionadas a um vértice no grafo.
Ela armazena o geocódigo, ID, ID do vértice, nível de bateria, tipo e lista de meios de transporte disponíveis no vértice.
Além disso, possui referências para as arestas adjacentes e o próximo vértice na lista.
@note Esta estrutura é usada na representação do grafo. 
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
A estrutura Aresta contém informações relacionadas a uma aresta no grafo.
Ela armazena o vértice adjacente, o peso da aresta e a referência para a próxima aresta na lista.
@note Esta estrutura é usada na representação do grafo.
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
 * A estrutura Grafo contém informações sobre o número de vértices, uma matriz de vértices visitados,
 * um array de distâncias, uma lista de meios de transporte, uma matriz de arestas adjacentes e uma lista de vértices.
 */
typedef struct Grafo {
    int numeroVertices; 
    bool** visitados;
    Transporte* meios; 
    struct Aresta*** matrizadj;     
    struct Vertice* vertices;
} Grafo; 


/**
 * @brief Função para criar os vértices do grafo.
 *
 * Esta função cria os vértices do grafo com base na lista de meios de transporte fornecida.
 *
 * @param g Ponteiro para o ponteiro do grafo.
 * @param meios Lista de meios de transporte.
 * @return O primeiro vértice criado.
 */
Vertice* criarVertices(Grafo** g, Transporte* meios); 

/**
 * @brief Função para encontrar um vértice no grafo com base no ID.
 *
 * Esta função percorre a lista de vértices do grafo e retorna o vértice com o ID fornecido.
 *
 * @param g Ponteiro para o grafo.
 * @param id ID do vértice a ser encontrado.
 * @return O vértice encontrado ou NULL se não for encontrado.
 */ 
Vertice* encontrarVertice(Grafo* g, int id);  

/**

@brief Cria um novo grafo.
@param numeroVertices O número de vértices do grafo.
@return Grafo* O ponteiro para a estrutura do grafo criado.
@retval NULL Se ocorrer um erro na alocação de memória.
/
Grafo criarGrafo(int numeroVertices);
/**

@brief Aloca memória para a estrutura do grafo e inicializa os seus atributos.
@param numeroVertices O número de vértices do grafo.
@return Grafo* O ponteiro para a estrutura do grafo criado.
@retval NULL Se ocorrer um erro na alocação de memória.
Esta função aloca memória para a estrutura do grafo e inicializa o número de vértices.
Em seguida, aloca memória para a matriz de visitados e a matriz de adjacência do grafo,
e inicializa essas matrizes. Os vértices do grafo são inicializados como NULL.
Se ocorrer um erro na alocação de memória, a função retorna NULL.
*/
Grafo* criarGrafo(int numeroVertices); 

/**

@brief Cria uma nova aresta entre dois vértices.
@param g O ponteiro para o grafo.
@param origem O ID do vértice de origem.
@param destino O ID do vértice de destino.
@param peso O peso da aresta.
@return Aresta* O ponteiro para a nova aresta criada.
@retval NULL Se ocorrer algum erro na criação da aresta.
Esta função cria uma nova aresta entre o vértice de origem e o vértice de destino no grafo fornecido.
Verifica se a origem e o destino são válidos e se a aresta já existe entre os vértices.
Em seguida, cria a nova aresta e atualiza a matriz de adjacência do grafo.
Se ocorrer algum erro na criação da aresta, a função retorna NULL.
*/
Aresta* criarAresta(Grafo* g, int origem, int destino, float peso);  

/**

@brief Imprime o grafo na console.
@param g O ponteiro para o grafo.
Esta função imprime na console a representação visual do grafo, exibindo todas as arestas e seus pesos.
A impressão é feita em formato de tabela, exibindo os IDs dos vértices de origem e destino, juntamente com o peso da aresta.
*/
void imprimirGrafo(Grafo* g); 

/**

@brief Lista os vértices que representam os meios de transporte.
@param g O ponteiro para o grafo.
@return O ponteiro para o primeiro vértice da lista.
Esta função lista na console os vértices que representam os meios de transporte presentes no grafo.
Para cada vértice, são exibidos o ID do vértice, o ID do meio de transporte, o tipo de transporte, a bateria e a localização.
A lista é exibida em formato de tabela.
*/
Vertice* listarVertices(Grafo* g); 

/**

@brief Guarda o grafo em um arquivo.
@param g O ponteiro para o grafo.
@return O ponteiro para o grafo.
Esta função salva o grafo em um arquivo de texto chamado "Grafo.txt". O arquivo contém as informações das arestas do grafo, incluindo a origem, o destino e o peso.
Os dados são escritos no formato "ORIGEM;DESTINO;DISTANCIA", onde ORIGEM representa o vértice de origem da aresta, DESTINO representa o vértice de destino e DISTANCIA representa o peso da aresta.
Se ocorrer algum erro ao criar ou escrever no arquivo, a função exibe uma mensagem de erro na console.
*/
Grafo* guardarGrafo(Grafo* g); 

/**

@brief Conecta todos os vértices do grafo.
@param g O ponteiro para o grafo.
Esta função conecta todos os vértices do grafo, criando as arestas correspondentes entre eles. A conexão é estabelecida calculando a distância entre as coordenadas geográficas dos vértices.
Para cada par de vértices, são obtidas as coordenadas geográficas utilizando o serviço de geocodificação do what3words.
Em seguida, é calculada a distância entre os vértices usando a fórmula da distância haversine.
Por fim, é criada uma aresta entre os vértices com a distância calculada.
@note É importante garantir que os vértices estejam devidamente inicializados e que as informações de geocódigo estejam corretas antes de chamar esta função.
*/
void conetarVertices(Grafo* g);  

/**

@brief Guarda as informações dos vértices em um arquivo.
@param g O ponteiro para o grafo.
Esta função guarda as informações dos vértices do grafo em um arquivo de texto.
Cada linha do arquivo contém os seguintes dados de um vértice separados por ponto e vírgula (;):
ID do vértice, ID do meio de transporte, tipo de meio de transporte, bateria e localização.
@note Certifique-se de que o grafo e os vértices estejam devidamente inicializados antes de chamar esta função.
*/
Grafo* guardarVertices(Grafo* g);  

/**

@brief Realiza o percurso mínimo para a recolha dos meios de transporte a partir de um vértice de origem.
@param g O ponteiro para o grafo.
@param origem O vértice de origem do percurso.
Esta função realiza o percurso mínimo para a recolha dos meios de transporte a partir de um vértice de origem.
Utiliza a heurística do vizinho mais próximo para construir o caminho a ser percorrido.
Após a construção do caminho, realiza a recolha dos meios de transporte, respeitando a capacidade disponível do camião.
Imprime na tela o caminho a ser percorrido e os meios de transporte recolhidos.
@note Certifique-se de que o grafo e os vértices estejam devidamente inicializados antes de chamar esta função.
@note Esta função assume a existência das seguintes funções auxiliares:
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados): Retorna o vértice mais próximo com bateria inferior a 50% que ainda não foi visitado.
void imprimirCaminho(int* caminho, int posicao): Imprime na tela o caminho a ser percorrido para a recolha dos meios de transporte.
void recolherMeios(Grafo* g, int origem, Transporte* Recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int* caminho, int posicao): Realiza a recolha dos meios de transporte ao longo do caminho.
void imprimirRecolhidos(Transporte* Recolhidos[], int numeroRecolhidos): Imprime na tela os meios de transporte recolhidos.
*/ 
void percursoMinimo(Grafo* g, int origem);   

/**

@brief Realiza a recolha dos meios de transporte ao longo do caminho.
@param g O apontador para o grafo.
@param origem O vértice de origem do percurso.
@param recolhidos Um array de ponteiros para os meios de transporte recolhidos.
@param numeroRecolhidos O número atual de meios de transporte recolhidos.
@param capacidadeCamiao A capacidade total do camião de recolha.
@param caminho O array contendo o caminho a ser percorrido para a recolha dos meios de transporte.
@param posicao A posição atual no caminho.
Esta função percorre o caminho especificado e realiza a recolha dos meios de transporte encontrados.
A capacidade disponível do camião é verificada a cada etapa da recolha para garantir que não seja excedida.
Os meios de transporte recolhidos são armazenados no array recolhidos e o número atual de recolhidos é atualizado.
Os meios de transporte que não puderem ser recolhidos devido à capacidade limitada do camião são armazenados em naoRecolhidosArray.
@note Certifique-se de que o grafo e os vértices estejam devidamente inicializados antes de chamar esta função.
@note Esta função assume a existência das seguintes funções auxiliares:
Transporte* encontrarTransportePorVertice(Grafo* g, int vertice): Retorna o ponteiro para o meio de transporte associado ao vértice especificado.
void saveAlterarDadosTransportes(Transporte* head): Salva as alterações feitas nos dados dos meios de transporte em um arquivo binário.
void atualizarFicheiroNaoRecolhidos(const char* filename, Transporte* naoRecolhidosArray[], int naoRecolhidos): Atualiza o arquivo binário contendo os meios de transporte não recolhidos.
void imprimirNaoRecolhidos(Transporte* naoRecolhidosArray[], int naoRecolhidos): Imprime na tela os meios de transporte não recolhidos.
void saveNaoRecolhidos(Transporte* naoRecolhidosArray[], int naoRecolhidos, const char* filename): Salva os meios de transporte não recolhidos em um arquivo binário.
*/
void recolherMeios(Grafo* g, int origem, Transporte* recolhidos[], int* numeroRecolhidos, int capacidadeCamiao, int caminho[], int posicao); 

/**

@brief Imprime na consola o caminho a ser percorrido.
@param caminho O array contendo o caminho a ser percorrido.
@param posicao A posição atual no caminho.
Esta função imprime na consola o caminho a ser percorrido para a recolha dos meios de transporte.
@note Certifique-se de que o caminho esteja corretamente definido antes de chamar esta função.
*/
void imprimirCaminho(int caminho[], int posicao); 

/**

@brief Imprime na consola os meios de transporte que foram recolhidos.
@param recolhidos Um array contendo os meios de transporte recolhidos.
@param numeroRecolhidos O número de meios de transporte recolhidos.
Esta função imprime na consola os meios de transporte que foram recolhidos durante o percurso.
@note Certifique-se de que os meios de transporte recolhidos estejam corretamente definidos antes de chamar esta função.
*/
void imprimirRecolhidos(Transporte* recolhidos[], int numeroRecolhidos); 

/**

@brief Imprime na console os meios de transporte não recolhidos.
@param naoRecolhidos Um array que contém os apontadores para os meios de transporte não recolhidos.
@param numeroNaoRecolhidos O número de meios de transporte não recolhidos.
Esta função imprime na console os meios de transporte não recolhidos.
Recebe um array de apontadores para os meios de transporte não recolhidos e o número total de meios não recolhidos. 
A função itera sobre o array e imprime o ID e o tipo de cada meio de transporte não recolhido.  
*/
void imprimirNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos);

/**

@brief Encontra o meio de transporte associado a um determinado vértice.
@param g O grafo que contém os vértices e os meios de transporte.
@param verticeID O ID do vértice.
@return O meio de transporte encontrado, ou NULL se nenhum meio de transporte estiver associado ao vértice.
Esta função percorre a lista de vértices do grafo e verifica se o ID do vértice corresponde ao ID desejado.
Se um meio de transporte estiver associado ao vértice, ele será retornado. Caso contrário, a função retorna NULL.
@note Certifique-se de que o grafo e os vértices estejam corretamente definidos antes de chamar esta função.
*/
Transporte* encontrarTransportePorVertice(Grafo* g, int verticeID); 

/**

@brief Encontra o vértice mais próximo com bateria inferior a 50% a partir de um vértice atual.
@param g O grafo que contém os vértices e as arestas.
@param verticeAtual O ID do vértice atual.
@param visitados Um vetor de booleanos indicando quais vértices foram visitados.
@return O ID do vértice mais próximo com bateria inferior a 50%, ou -1 se não houver vértices disponíveis.
Esta função percorre as arestas do vértice atual e verifica se o vértice adjacente tem bateria inferior a 50%.
Se o vértice atender a essa condição e tiver um peso menor que os vértices anteriores, ele é considerado o mais próximo.
Caso contrário, o vértice mais próximo atual permanece o mesmo.
A função retorna o ID do vértice mais próximo encontrado ou -1 se nenhum vértice estiver disponível.
@note Certifique-se de que o grafo, as arestas e os vértices estejam corretamente definidos antes de chamar esta função.
*/
int EncontrarMaisProximo50(Grafo* g, int verticeAtual, bool* visitados);  

/**

@brief Guarda os meios de transporte não recolhidos em um arquivo binário.
@param naoRecolhidos Um vetor de ponteiros para os meios de transporte não recolhidos.
@param numeroNaoRecolhidos O número de meios de transporte não recolhidos.
@param TransportesNaoRecolhidos O nome do arquivo onde os dados serão salvos.
Esta função recebe um vetor de ponteiros para os meios de transporte não recolhidos,
o número de meios de transporte não recolhidos e o nome do arquivo onde os dados serão salvos.
A função abre o arquivo no modo de escrita binária, escreve o número de meios de transporte não recolhidos
e em seguida escreve cada meio de transporte não recolhido no arquivo.
Após salvar os dados, o arquivo é fechado.
@note Certifique-se de que os meios de transporte não recolhidos e o nome do arquivo estejam corretamente definidos antes de chamar esta função.
*/
void saveNaoRecolhidos(Transporte* naoRecolhidos[], int numeroNaoRecolhidos, const char* TransportesNaoRecolhidos);  

/**

@brief Lê os dados de um arquivo contendo os meios de transporte não recolhidos.
@param TransportesNaoRecolhidos O nome do arquivo que contém os dados dos meios de transporte não recolhidos.
Esta função lê os dados de um arquivo binário que contém os meios de transporte não recolhidos.
A função abre o arquivo no modo de leitura binária, lê o número de meios de transporte não recolhidos,
aloca memória para armazenar os dados e lê os dados do arquivo.
Em seguida, imprime os dados lidos na console, indicando o ID e o tipo de cada meio de transporte não recolhido.
Por fim, a memória alocada para armazenar os dados é liberada.
@note Certifique-se de que o nome do arquivo esteja corretamente definido antes de chamar esta função.
*/
void lerDadosDeArquivo(const char* TransportesNaoRecolhidos); 

/**

@brief Atualiza o arquivo de meios de transporte não recolhidos.
@param nomeArquivo O nome do arquivo a ser atualizado.
@param naoRecolhidosArray Um array contendo os dados dos meios de transporte não recolhidos.
@param numeroNaoRecolhidos O número de meios de transporte não recolhidos.
Esta função atualiza o arquivo de meios de transporte não recolhidos com os dados fornecidos.
Ela recebe o nome do arquivo, um array contendo os dados dos meios de transporte não recolhidos e o número total de meios não recolhidos.
A função abre o arquivo em modo de escrita binária, escreve o número de meios não recolhidos e em seguida escreve os dados de cada meio de transporte no arquivo.
Por fim, o arquivo é fechado.
@note Certifique-se de que os parâmetros foram corretamente preenchidos antes de chamar esta função.
*/
void atualizarFicheiroNaoRecolhidos (const char* nomeArquivo, Transporte* naoRecolhidosArray, int numeroNaoRecolhidos);  

void imprimirMeiosNaoRecolhidos(Transporte* naoRecolhidosArray, int numeroNaoRecolhidos); 