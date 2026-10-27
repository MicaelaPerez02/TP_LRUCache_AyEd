#include "Simulador.h"
#include "LotesPrueba.h"
#include <time.h>

int main()
{
    unsigned semilla = SEMILLA_FIJA;
    int opcion;

    if(semilla == 0)
        semilla = (unsigned)time(NULL);

    srand(semilla);
    ////printf("Semilla: %u\n\n", semilla);

    if(crearArchivoPosteos(ARCH_POSTEOS) == GEN_ERROR
       || crearArchivoFeeds(ARCH_CONCENTRADO, LOTE_CONCENTRADO, USUARIOS_LOTE, POPULARES_CONCENTRADO) == GEN_ERROR
       || crearArchivoFeeds(ARCH_DISPERSO, LOTE_DISPERSO, USUARIOS_LOTE, POPULARES_CONCENTRADO) == GEN_ERROR
       || crearArchivoFeeds(ARCH_ORDENADO, LOTE_ORDENADO, USUARIOS_LOTE, POPULARES_CONCENTRADO) == GEN_ERROR)
    {
        printf("Error al crear los archivos\n");
        return 1;
    }

    //printf("Primeros posteos de %s:\n", ARCH_POSTEOS);
    //mostrarArchivoPosteos(ARCH_POSTEOS, MOSTRAR_REGISTROS);

    //printf("\nPrimeros feeds de %s:\n", ARCH_CONCENTRADO);
    //mostrarArchivoFeeds(ARCH_CONCENTRADO, MOSTRAR_REGISTROS);

    //printf("\nPrimeros feeds de %s:\n", ARCH_DISPERSO);
    //mostrarArchivoFeeds(ARCH_DISPERSO, MOSTRAR_REGISTROS);

    //printf("\nPrimeros feeds de %s:\n", ARCH_ORDENADO);
    //mostrarArchivoFeeds(ARCH_ORDENADO, MOSTRAR_REGISTROS);

    //printf("\nArchivos generados.\n");

    printf("\n=========SIMULADOR=========\n");

    opcion = mostrarMenu();

    while(opcion != OPCION_SALIR)
    {
        if(opcion == OPCION_ESTATICO)
            modoEstatico();
        else if(opcion == OPCION_DINAMICO)
            modoDinamico();
        else
            printf("\nOpcion invalida\n");

        opcion = mostrarMenu();
    }

    return 0;
}
