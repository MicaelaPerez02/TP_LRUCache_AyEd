#ifndef LOTESPRUEBA_H_INCLUDED
#define LOTESPRUEBA_H_INCLUDED

#define ERROR_APERTURA_ARCHIVO 1
#define MOSTRAR_ERROR_APERTURA 1
#define ERROR_CREACION_ARCHIVO 1

#define EXITO_APERTURA_ARCHIVO 0
#define EXITO_CREACION_ARCHIVO 0


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char texto[141];
} tPosteo;

typedef struct
{
    char usuario[15];
    int feed[20];
} tUsuarioFeed;

int abrirArchivo(FILE **fp, const char *nombreArchivo, const char *modoApertura, int mostrarError);
int crearArchivoPosteos(char *nombreArchivo);
void mostrarArchivoPosteos(char *nombreArchivo);
int crearArchivoUsuariosFeed(char *nombreArchivo);
void mostrarArchivoUsuarioFeed(char *nombreArchivo);

#endif // LOTESPRUEBA_H_INCLUDED
