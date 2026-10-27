#ifndef LOTESPRUEBA_H_INCLUDED
#define LOTESPRUEBA_H_INCLUDED

// Cantidades de la consigna
#define CANT_POSTEOS 50000
#define POSTEOS_POR_FEED 20
#define TAM_TEXTO 141
#define TAM_USUARIO 100

/* ---- Tipos de lote ---- */
#define LOTE_CONCENTRADO 1
#define LOTE_DISPERSO 2
#define LOTE_ORDENADO 3

// Lote concentrado
#define MAX_POPULARES 5000
#define PORCENTAJE_POPULARES 90
#define PORCENTAJE_MAXIMO 100

// Nombre archivos
#define ARCH_POSTEOS "posteos.bin"
#define ARCH_CONCENTRADO "feeds_concentrado.bin"
#define ARCH_DISPERSO "feeds_disperso.bin"
#define ARCH_ORDENADO "feeds_ordenado.bin"
#define ARCH_CONCENTRADO_GRANDE "feeds_concentrado_grande.bin"
#define ARCH_DISPERSO_GRANDE "feeds_disperso_grande.bin"
#define ARCH_ORDENADO_GRANDE "feeds_ordenado_grande.bin"

#define GEN_OK 1
#define GEN_ERROR 0

// rand() de Windows
#define TOPE_RAND 32768

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char texto[TAM_TEXTO];
} tPosteo;

typedef struct
{
    char usuario[TAM_USUARIO];
    int feed[POSTEOS_POR_FEED];
} tUsuarioFeed;

int aleatorioHasta(int limite);
int estaEnVector(const int *vec, int cantidad, int id);
void llenarVectorDistinto(int *vec, int cantidad);
void llenarFeedConcentrado(int *feed, const int *populares, int cantPopulares);
void llenarFeedOrdenado(int *feed, int indiceUsuario, int cantUsuarios);

int crearArchivoPosteos(const char *nombreArchivo);
void mostrarArchivoPosteos(const char *nombreArchivo, int limite);

int crearArchivoFeeds(const char *nombreArchivo, int tipoLote, int cantUsuarios, int cantPopulares);
void mostrarArchivoFeeds(const char *nombreArchivo, int limite);

#endif /* LOTESPRUEBA_H_INCLUDED */
