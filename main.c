#include "Simulador.h"
#include "LotesPrueba.h"
#include <time.h>

#define MOSTRAR_REGISTROS 3

/* 0: la semilla sale de la hora. Cualquier otro valor regenera siempre los mismos lotes */
#define SEMILLA_FIJA 0

#define CANTIDAD(vec) ((int)(sizeof(vec) / sizeof((vec)[0])))

// Lotes de la consigna
#define USUARIOS_BASE 200
#define POPULARES_BASE 50
#define REPETICIONES_BASE 10

// Lotes grandes: sirven para que la diferencia de tiempos entre las caches se note
#define USUARIOS_CONCENTRADO_GRANDE 6000
#define POPULARES_CONCENTRADO_GRANDE 4000
#define USUARIOS_DISPERSO_GRANDE 5000
#define USUARIOS_ORDENADO_GRANDE 2500
#define REPETICIONES_GRANDE 1

int main()
{
    unsigned semilla = SEMILLA_FIJA;
    unsigned capacidadesBase[] = {10, 50, 100, 500, 1000, 2000, 4000};
    unsigned capacidadesConcentrado[] = {500, 1000, 2000, 3000};
    unsigned capacidadesDisperso[] = {250, 500, 1000, 1500};
    unsigned capacidadesOrdenado[] = {250, 500, 1000, 1250};

    if(semilla == 0)
        semilla = (unsigned)time(NULL);

    srand(semilla);
    printf("Semilla: %u\n\n", semilla);

    if(crearArchivoPosteos(ARCH_POSTEOS) == GEN_ERROR
       || crearArchivoFeeds(ARCH_CONCENTRADO, LOTE_CONCENTRADO, USUARIOS_BASE, POPULARES_BASE) == GEN_ERROR
       || crearArchivoFeeds(ARCH_DISPERSO, LOTE_DISPERSO, USUARIOS_BASE, POPULARES_BASE) == GEN_ERROR
       || crearArchivoFeeds(ARCH_ORDENADO, LOTE_ORDENADO, USUARIOS_BASE, POPULARES_BASE) == GEN_ERROR
       || crearArchivoFeeds(ARCH_CONCENTRADO_GRANDE, LOTE_CONCENTRADO, USUARIOS_CONCENTRADO_GRANDE, POPULARES_CONCENTRADO_GRANDE) == GEN_ERROR
       || crearArchivoFeeds(ARCH_DISPERSO_GRANDE, LOTE_DISPERSO, USUARIOS_DISPERSO_GRANDE, POPULARES_BASE) == GEN_ERROR
       || crearArchivoFeeds(ARCH_ORDENADO_GRANDE, LOTE_ORDENADO, USUARIOS_ORDENADO_GRANDE, POPULARES_BASE) == GEN_ERROR)
    {
        printf("Error al crear los archivos\n");
        return 1;
    }

    printf("Primeros posteos de %s:\n", ARCH_POSTEOS);
    mostrarArchivoPosteos(ARCH_POSTEOS, MOSTRAR_REGISTROS);

    printf("\nPrimeros feeds de %s:\n", ARCH_CONCENTRADO);
    mostrarArchivoFeeds(ARCH_CONCENTRADO, MOSTRAR_REGISTROS);

    printf("\nPrimeros feeds de %s:\n", ARCH_DISPERSO);
    mostrarArchivoFeeds(ARCH_DISPERSO, MOSTRAR_REGISTROS);

    printf("\nPrimeros feeds de %s:\n", ARCH_ORDENADO);
    mostrarArchivoFeeds(ARCH_ORDENADO, MOSTRAR_REGISTROS);

    printf("\nListo. Archivos generados.\n");

    printf("\n=========SIMULADOR=========\n");

    simularCaso("Concentrado", ARCH_CONCENTRADO, USUARIOS_BASE,
                capacidadesBase, CANTIDAD(capacidadesBase), REPETICIONES_BASE);
    simularCaso("Disperso", ARCH_DISPERSO, USUARIOS_BASE,
                capacidadesBase, CANTIDAD(capacidadesBase), REPETICIONES_BASE);
    simularCaso("Ordenado", ARCH_ORDENADO, USUARIOS_BASE,
                capacidadesBase, CANTIDAD(capacidadesBase), REPETICIONES_BASE);

    simularCaso("Concentrado grande", ARCH_CONCENTRADO_GRANDE, USUARIOS_CONCENTRADO_GRANDE,
                capacidadesConcentrado, CANTIDAD(capacidadesConcentrado), REPETICIONES_GRANDE);
    simularCaso("Disperso grande", ARCH_DISPERSO_GRANDE, USUARIOS_DISPERSO_GRANDE,
                capacidadesDisperso, CANTIDAD(capacidadesDisperso), REPETICIONES_GRANDE);
    simularCaso("Ordenado grande", ARCH_ORDENADO_GRANDE, USUARIOS_ORDENADO_GRANDE,
                capacidadesOrdenado, CANTIDAD(capacidadesOrdenado), REPETICIONES_GRANDE);

    return 0;
}
