#ifndef TDAINDICE_H_INCLUDED
#define TDAINDICE_H_INCLUDED

#include "TDAListaDoble.h"
#include "TDAArbol.h"

typedef struct
{
    const void *clave;
    tNodo *nodo;
    Cmp cmp;
} tIndice;

int compararClaveIndice(const void *a, const void *b);

int insertarEnIndice(tArbolBinBusq *pa, tNodo *nodo, Cmp cmp);
tNodo *buscarEnIndice(tArbolBinBusq *pa, const void *clave, Cmp cmp);
tNodo *sacarDeIndice(tArbolBinBusq *pa, const void *clave, Cmp cmp);

#endif // TDAINDICE_H_INCLUDED
