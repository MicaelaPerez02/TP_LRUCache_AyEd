#ifndef TDALISTA_H_INCLUDED
#define TDALISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 1
#define SIN_MEMORIA -1
#define SIN_DATOS -2

#ifndef MINIMO
#define MINIMO(X, Y)((X)<=(Y) ? (X) : (Y))
#endif

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tLista;

void crearLista(tLista *p);
void vaciarLista(tLista *p);
int insertarAlInicioLista(tLista *p, const void *d, size_t tam);
int sacarUltimoLista(tLista *p, void *d, size_t tam);

#endif // TDALISTA_H_INCLUDED
