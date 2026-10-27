#ifndef T_LRU_CACHE_MEJORADA_H_INCLUDED
#define T_LRU_CACHE_MEJORADA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "TDAListaDoble.h"
#include "TDAArbol.h"

#ifndef PUNTERO_INVALIDO
#define PUNTERO_INVALIDO -4
#endif

#ifndef NO_ENCONTRADO
#define NO_ENCONTRADO -3
#endif

typedef struct
{
    const void *clave;
    tNodoDoble *nodo;
} tClaveNodo;

typedef struct
{
    tClaveNodo entrada;
    Cmp cmp;
} tBusqueda;

typedef struct
{
    tListaDoble listaDoble;
    tArbolBinBusq arbol;
    size_t capMax;
    int ce;
    Cmp cmpClaves;
} tCacheMejorada;

void crear_lrucache_mejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp);
int agregar_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam);
int obtener_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam);
int borrar_lrucache_mejorada(tCacheMejorada *pc, void *d);
void vaciar_lrucache_mejorada(tCacheMejorada *pc);
unsigned altura_lrucache_mejorada(tCacheMejorada *pc);

// Auxiliares que tocan el arbol
int compararClaveNodo(const void *a, const void *b);
int insertarClaveEnArbol(tCacheMejorada *pc, tNodoDoble *nodo);
tNodoDoble *buscarNodoPorClave(tCacheMejorada *pc, const void *clave);
tNodoDoble *sacarClaveDelArbol(tCacheMejorada *pc, const void *clave);

#endif // T_LRU_CACHE_MEJORADA_H_INCLUDED
