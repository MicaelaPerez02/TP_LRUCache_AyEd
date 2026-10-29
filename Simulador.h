#ifndef SIMULADOR_H_INCLUDED
#define SIMULADOR_H_INCLUDED

#include <time.h>
#include "LotesPrueba.h"
#include "TDALruCache.h"
#include "TDALruCacheMejorada.h"

#define MOSTRAR_REGISTROS 3
#define SEMILLA_FIJA 0

#define CANTIDAD(vec) ((int)(sizeof(vec) / sizeof((vec)[0])))

#define USUARIOS_LOTE 2500
#define POPULARES_CONCENTRADO 2000
#define REPETICIONES_LOTE 1

// Menu
#define OPCION_SALIR 0
#define OPCION_ESTATICO 1
#define OPCION_DINAMICO 2

#define TAM_LINEA 20
#define NUMERO_INVALIDO -1
#define CANT_CAPACIDADES_DINAMICO 1
#define MAX_CAPACIDAD 5000

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

// Manejo de la cache segun el modo
void crearCache(tSimulador *sim, unsigned capacidad);
int buscarEnCache(tSimulador *sim, tPosteo *posteo);
void guardarEnCache(tSimulador *sim, tPosteo *posteo);
unsigned obtenerAltura(tSimulador *sim);
void vaciarCache(tSimulador *sim);

// Simulacion
int leerPosteo(FILE *pfPosteos, int id, tPosteo *posteo);
int simularUnaVez(const char *archivoFeeds, int modo, unsigned capacidad, tResultado *res);
int simularVariasVeces(const char *archivoFeeds, int modo, unsigned capacidad, int repeticiones, tResultado *res);

// Tabla de resultados
const char *nombreModo(int modo);
void mostrarSeparador(void);
void mostrarEncabezado(void);
void mostrarFila(int modo, unsigned capacidad, const tResultado *res, int cantUsuarios, double diferencia);
void simularCaso(const char *titulo, const char *archivoFeeds, int cantUsuarios,
                 const unsigned *capacidades, int cantCapacidades, int repeticiones);

// Menu
int leerNumero(void);
void simularTodo(const unsigned *capacidades, int cantCapacidades);
void modoEstatico(void);
int pedirCapacidad(const char *texto);
void modoDinamico(void);
int mostrarMenu(void);

#endif // SIMULADOR_H_INCLUDED
