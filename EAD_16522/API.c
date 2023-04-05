#define CURL_STATICLIB
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "API.h"

// Função de callback do curl para receber a resposta da API
static size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    size_t realsize = size * nmemb;
    char* response = (char*)userdata;
    strncat(response, ptr, realsize);
    return realsize;
}

//Calcular a distância entre dois pontos
float haversine_distance(float lat1, float lon1, float lat2, float lon2) {
    float dlat = (lat2 - lat1) * M_PI / 180.0;
    float dlon = (lon2 - lon1) * M_PI / 180.0;
    float a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) * sin(dlon / 2) * sin(dlon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float distancia = EARTH_RADIUS * c; 

    return distancia;
}

//Extrair as coordenadas através das 3 palavras introduzidas
int get_coordinates(const char* words, const char* api_key, float* latitude, float* longitude) {
    // Construir a URL da API
    char url[256];

    snprintf(url, 256, "https://api.what3words.com/v3/convert-to-coordinates?words=%s&key=%s", words, api_key);

    // Configurar a requisição HTTP
    CURL* curl = curl_easy_init();
    if (!curl) {
        printf("Erro ao inicializar o curl\n");
        return 1;
    }
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Armazenar a resposta da API em uma string
    char response[1024] = { 0 };
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)response);

    // Enviar a requisição HTTP
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("Erro ao enviar a requisição HTTP: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return 1;
    }
    // Extrair as coordenadas correspondentes à palavra da resposta da API
    const char* start = strstr(response, "\"coordinates\":{\"lng\":");
    if (!start) {
        printf("Erro ao extrair as coordenadas da resposta da API\n");
        curl_easy_cleanup(curl);
        return 1;
    }

    sscanf(start + strlen("\"coordinates\":{\"lng\":"), "%f,\"lat\":%f", longitude, latitude);

    // Limpar a memória
    curl_easy_cleanup(curl);

    return 0;
}