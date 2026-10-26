#include "TDAIndice.h"

int cmpEntradas(const void *a, const void *b)
{
    const tEntradaIndice *entA = a;
    const tEntradaIndice *entB = b;

    return entA->cmp(entA->clave, entB->clave);
}

void armarEntrada(tEntradaIndice *entrada, const void *clave, tNodo *nodo, Cmp cmp)
{
    entrada->clave = clave;
    entrada->nodo = nodo;
    entrada->cmp = cmp;
}

void crearIndice(tIndice *pi, Cmp cmpClaves)
{
    crearArbolBinBusq(&pi->arbol);
    pi->cmpClaves = cmpClaves;
}

void vaciarIndice(tIndice *pi)
{
    vaciarArbolBinBusq(&pi->arbol);
}

int insertarEnIndice(tIndice *pi, tNodo *nodo)
{
    tEntradaIndice entrada;

    armarEntrada(&entrada, nodo->info, nodo, pi->cmpClaves);

    return insertarRecArbolBinBusq(&pi->arbol, &entrada, sizeof(tEntradaIndice), cmpEntradas);
}

tNodo *buscarEnIndice(const tIndice *pi, const void *clave)
{
    tEntradaIndice entrada;
    tArbolBinBusq *caja;

    armarEntrada(&entrada, clave, NULL, pi->cmpClaves);

    caja = buscarRecElemArbolBinBusq((tArbolBinBusq *)&pi->arbol, &entrada, cmpEntradas);

    if(!caja)
        return NULL;

    return ((tEntradaIndice *)(*caja)->info)->nodo;
}

tNodo *sacarDeIndice(tIndice *pi, const void *clave)
{
    tEntradaIndice entrada;
    tArbolBinBusq *caja;
    tNodo *nodo;

    armarEntrada(&entrada, clave, NULL, pi->cmpClaves);

    caja = buscarRecElemArbolBinBusq(&pi->arbol, &entrada, cmpEntradas);

    if(!caja)
        return NULL;

    nodo = ((tEntradaIndice *)(*caja)->info)->nodo;     // lo guardo ANTES de borrar la entrada

    eliminarRaizArbolBinBusq(caja);

    return nodo;
}

unsigned alturaIndice(tIndice *pi)
{
    return alturaArbolBin(&pi->arbol);
}
