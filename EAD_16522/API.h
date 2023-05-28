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

//Key da API 
#define API_KEY  "QK95ZNN1"  
#define EARTH_RADIUS 6371.0
#define M_PI 3.14159265358979323846

// Função de callback do curl para receber a resposta da API
static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata); 

//Extrair as coordenadas
int get_coordinates(const char* words, const char* api_key, float* latitude, float* longitude); 

//Calcular a distância entre dois pontos
float haversine_distance(float lat1, float lon1, float lat2, float lon2); 
