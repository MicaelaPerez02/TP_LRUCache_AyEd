#ifndef TDALISTA_H_INCLUDED
#define TDALISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 1
#define SIN_MEMORIA -1
#define SIN_DATOS -2
#define NO_ENCONTRADO -3

#ifndef MINIMO
#define MINIMO(X, Y)((X)<=(Y) ? (X) : (Y))
#endif

#ifndef CMP_DEFINIDO
#define CMP_DEFINIDO
typedef int (*Cmp)(const void *, const void *);
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
int moverAlInicioLista(tLista *p, const void *d,  Cmp cmp);
int eliminarElementoLista(tLista *p, const void *d, Cmp cmp);
int reemplazarInfoPrimeroLista(tLista *p, const void *d, size_t tam);

#endif // TDALISTA_H_INCLUDED
