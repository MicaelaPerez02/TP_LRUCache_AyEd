/*
    Genera los archivos de prueba de la simulacion:
        posteos.bin, feeds_concentrado.bin, feeds_disperso.bin y feeds_ordenado.bin

    Es un programa APARTE del simulador (proyecto nuevo con generador.c, LotesPrueba.c y LotesPrueba.h).
    Cada vez que se ejecuta genera archivos nuevos, porque la semilla sale de la hora.
    Las cantidades se cambian en LotesPrueba.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LotesPrueba.h"

#define MOSTRAR_REGISTROS 3

int main()
{
    unsigned semilla = (unsigned)time(NULL);

    srand(semilla);
    printf("Semilla: %u\n\n", semilla);

    if(crearArchivoPosteos(ARCH_POSTEOS) == GEN_ERROR
       || crearArchivoFeeds(ARCH_CONCENTRADO, LOTE_CONCENTRADO) == GEN_ERROR
       || crearArchivoFeeds(ARCH_DISPERSO, LOTE_DISPERSO) == GEN_ERROR
       || crearArchivoFeeds(ARCH_ORDENADO, LOTE_ORDENADO) == GEN_ERROR)
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
    return 0;
}
