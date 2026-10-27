#ifndef SIMULADOR_H_INCLUDED
#define SIMULADOR_H_INCLUDED

#include <time.h>
#include "LotesPrueba.h"
#include "t_lru_cache.h"
#include "t_lru_cache_mejorada.h"

// Modos de la simulacion
#define SIN_CACHE 0
#define CACHE_PARTE_1 1
#define CACHE_PARTE_2 2

#define SIM_OK 1
#define SIM_ERROR 0

#define MS_POR_SEGUNDO 1000
#define US_POR_SEGUNDO 1000000

typedef struct
{
    unsigned aciertos;
    unsigned fallos;
    unsigned lecturas;
    unsigned altura;
    double segundos;
} tResultado;

typedef struct
{
    int modo;
    tCache cache1;
    tCacheMejorada cache2;
} tSimulador;

void simularCaso(const char *titulo, const char *archivoFeeds, int cantUsuarios,
                 const unsigned *capacidades, int cantCapacidades, int repeticiones);

#endif // SIMULADOR_H_INCLUDED
