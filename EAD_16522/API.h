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
 * A constante `API_KEY` representa a chave de acesso � API What3Words.
 * Essa chave � necess�ria para realizar requisi��es � API e obter as coordenadas geogr�ficas correspondentes a tr�s palavras.
 */
#define API_KEY  "0" // QK95ZNN1"  

 /**
  * @brief Raio m�dio da Terra em km.
  * A constante `EARTH_RADIUS` representa o raio m�dio da Terra em km.
  * Essa constante � utilizada na f�rmula para calcular a dist�ncia entre dois pontos na f�rmula de Haversine. 
  */
#define EARTH_RADIUS 6371.0 

  /**
   * @brief Valor de pi.
   * A constante `M_PI` representa um valor de pi. 
   * Esse valor � utilizado na f�rmula de Haversine para converter �ngulos de graus para radianos. 
   */
#define M_PI 3.14159265358979323846

/**
 * @brief Fun��o de callback para receber a resposta da API cURL.
 *
 * A fun��o `write_callback` � utilizada como um callback pelo cURL para receber a resposta da API.
 * Ela recebe os dados recebidos da API por meio do par�metro `ptr` e os concatena com o buffer de resposta
 * especificado pelo par�metro `userdata`. Essa fun��o � chamada m�ltiplas vezes pelo cURL conforme os dados s�o recebidos.
 * Retorna o tamanho dos dados recebidos para o cURL.
 *
 * @param ptr apontador para os dados recebidos da API.
 * @param size Tamanho de cada elemento de dados recebido.
 * @param nmemb N�mero de elementos de dados recebidos.
 * @param userdata apontador para o buffer de resposta onde os dados ser�o concatenados.
 * @return O tamanho total dos dados recebidos (size * nmemb).
 */
static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata); 

/**
 * @brief Extrai as coordenadas geogr�ficas correspondentes a tr�s palavras utilizando a API What3Words.
 *
 * A fun��o `get_coordinates` faz uma requisi��o � API What3Words para obter as coordenadas geogr�ficas correspondentes a tr�s palavras.
 * Ela recebe as palavras, a chave da API e dois apontadores para armazenar as coordenadas latitude e longitude.
 * As coordenadas s�o armazenadas nos apontadores `latitude` e `longitude` passados por refer�ncia.
 *
 * @param words As tr�s palavras a serem convertidas em coordenadas.
 * @param api_key A chave da API What3Words.
 * @param latitude Ponteiro para armazenar a latitude da localiza��o.
 * @param longitude Ponteiro para armazenar a longitude da localiza��o.
 * @return 0 se as coordenadas foram extra�das com sucesso, ou 1 em caso de erro. 
 */
int get_coordinates(const char* words, const char* api_key, float* latitude, float* longitude); 

/**
 * @brief Calcula a dist�ncia entre dois pontos na superf�cie da Terra recorrendo � f�rmula de Haversine.
 *
 * A fun��o `haversine_distance` calcula a dist�ncia entre dois pontos geogr�ficos na superf�cie da Terra usando a f�rmula de Haversine.
 * Ela recebe as coordenadas latitude e longitude dos dois pontos (em graus) e retorna a dist�ncia entre eles em km.
 *
 * @param lat1 Latitude do primeiro ponto em graus. 
 * @param lon1 Longitude do primeiro ponto em graus. 
 * @param lat2 Latitude do segundo ponto em graus. 
 * @param lon2 Longitude do segundo ponto em graus. 
 * @return A dist�ncia entre os dois pontos em km.
 */
float haversine_distance(float lat1, float lon1, float lat2, float lon2); 
