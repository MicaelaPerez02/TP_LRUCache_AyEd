#include "TDAIndice.h"

int compararClaveIndice(const void *a, const void *b)
{
    const tIndice *idxA = a;
    const tIndice *idxB = b;

    return idxA->cmp(idxA->clave, idxB->clave);
}

int insertarEnIndice(tArbolBinBusq *pa, tNodo *nodo, Cmp cmp)
{
    tIndice idx;

    idx.clave = nodo->info;
    idx.nodo = nodo;
    idx.cmp = cmp;

    return insertarRecArbolBinBusq(pa, &idx, sizeof(tIndice), compararClaveIndice);
}

tNodo *buscarEnIndice(tArbolBinBusq *pa, const void *clave, Cmp cmp)
{
    tIndice idx;
    tArbolBinBusq *caja;

    idx.clave = clave;
    idx.cmp = cmp;

    caja = buscarRecElemArbolBinBusq(pa, &idx, compararClaveIndice);

    if(!caja)
        return NULL;

    return ((tIndice *)(*caja)->info)->nodo;
}

tNodo *sacarDeIndice(tArbolBinBusq *pa, const void *clave, Cmp cmp)
{
    tIndice idx;
    tArbolBinBusq *caja;
    tNodo *nodo;

    idx.clave = clave;
    idx.cmp = cmp;

    caja = buscarRecElemArbolBinBusq(pa, &idx, compararClaveIndice);

    if(!caja)
        return NULL;

    nodo = ((tIndice *)(*caja)->info)->nodo; // lo guardo ANTES de borrar el nodo del arbol

    eliminarRaizArbolBinBusq(caja);

    return nodo;
}
