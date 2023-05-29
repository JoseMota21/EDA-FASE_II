#include "curl/curl.h"
#include <math.h> 

#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else 
#pragma comment (lib,"curl/libcurl_a.lib")
#endif 

#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib, "advapi32.lib")

/**
 * @brief Chave da API What3Words. 
 * A constante `API_KEY` representa a chave de acesso à API What3Words.
 * Essa chave é necessária para realizar requisições à API e obter as coordenadas geográficas correspondentes a três palavras.
 */
#define API_KEY  "0" // QK95ZNN1"  

 /**
  * @brief Raio médio da Terra em km.
  * A constante `EARTH_RADIUS` representa o raio médio da Terra em km.
  * Essa constante é utilizada na fórmula para calcular a distância entre dois pontos na fórmula de Haversine. 
  */
#define EARTH_RADIUS 6371.0 

  /**
   * @brief Valor de pi.
   * A constante `M_PI` representa um valor de pi. 
   * Esse valor é utilizado na fórmula de Haversine para converter ângulos de graus para radianos. 
   */
#define M_PI 3.14159265358979323846

/**
 * @brief Função de callback para receber a resposta da API cURL.
 *
 * A função `write_callback` é utilizada como um callback pelo cURL para receber a resposta da API.
 * Ela recebe os dados recebidos da API por meio do parâmetro `ptr` e os concatena com o buffer de resposta
 * especificado pelo parâmetro `userdata`. Essa função é chamada múltiplas vezes pelo cURL conforme os dados são recebidos.
 * Retorna o tamanho dos dados recebidos para o cURL.
 *
 * @param ptr apontador para os dados recebidos da API.
 * @param size Tamanho de cada elemento de dados recebido.
 * @param nmemb Número de elementos de dados recebidos.
 * @param userdata apontador para o buffer de resposta onde os dados serão concatenados.
 * @return O tamanho total dos dados recebidos (size * nmemb).
 */
static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata); 

/**
 * @brief Extrai as coordenadas geográficas correspondentes a três palavras utilizando a API What3Words.
 *
 * A função `get_coordinates` faz uma requisição à API What3Words para obter as coordenadas geográficas correspondentes a três palavras.
 * Ela recebe as palavras, a chave da API e dois apontadores para armazenar as coordenadas latitude e longitude.
 * As coordenadas são armazenadas nos apontadores `latitude` e `longitude` passados por referência.
 *
 * @param words As três palavras a serem convertidas em coordenadas.
 * @param api_key A chave da API What3Words.
 * @param latitude Ponteiro para armazenar a latitude da localização.
 * @param longitude Ponteiro para armazenar a longitude da localização.
 * @return 0 se as coordenadas foram extraídas com sucesso, ou 1 em caso de erro. 
 */
int get_coordinates(const char* words, const char* api_key, float* latitude, float* longitude); 

/**
 * @brief Calcula a distância entre dois pontos na superfície da Terra recorrendo à fórmula de Haversine.
 *
 * A função `haversine_distance` calcula a distância entre dois pontos geográficos na superfície da Terra usando a fórmula de Haversine.
 * Ela recebe as coordenadas latitude e longitude dos dois pontos (em graus) e retorna a distância entre eles em km.
 *
 * @param lat1 Latitude do primeiro ponto em graus. 
 * @param lon1 Longitude do primeiro ponto em graus. 
 * @param lat2 Latitude do segundo ponto em graus. 
 * @param lon2 Longitude do segundo ponto em graus. 
 * @return A distância entre os dois pontos em km.
 */
float haversine_distance(float lat1, float lon1, float lat2, float lon2); 
