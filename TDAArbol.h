#ifndef TDAARBOL_H_INCLUDED
#define TDAARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_MEMORIA -1
#define SIN_DATOS -2
#define DUPLICADO -3
#define EXITO 1

#ifndef MINIMO
#define MINIMO(X, Y)((X)<=(Y) ? (X) : (Y))
#endif

#ifndef CMP_DEFINIDO
#define CMP_DEFINIDO
typedef int (*Cmp)(const void *, const void *);
#endif

typedef struct sNodoArbol
{
    void *info;
    size_t tamInfo;
    struct sNodoArbol *izq, *der;
} tNodoArbol;

typedef tNodoArbol *tArbolBinBusq;
void crearArbolBinBusq(tArbolBinBusq *p);
void vaciarArbolBinBusq(tArbolBinBusq *p);
int insertarRecArbolBinBusq(tArbolBinBusq *p, const void *d, size_t tam, Cmp cmp);
int eliminarRaizArbolBinBusq(tArbolBinBusq *p);
int eliminarRecArbolBinBusq(tArbolBinBusq *p, void *d, size_t tam, Cmp cmp);
unsigned alturaArbolBin(tArbolBinBusq *p);
tNodoArbol** buscarRecElemArbolBinBusq(tArbolBinBusq *p, const void *d, Cmp cmp);
tNodoArbol **menorNodoArbolBinBusq(const tArbolBinBusq *p);
tNodoArbol **mayorNodoArbolBinBusq(const tArbolBinBusq *p);

#endif
