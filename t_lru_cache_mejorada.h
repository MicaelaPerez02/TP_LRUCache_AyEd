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

/* Lo que guarda cada nodo del arbol: SOLO la clave y el nodo de la lista donde esta el dato */
typedef struct
{
    const void *clave;      // direccion de la clave: vive dentro del dato del nodo de la lista
    tNodo *nodo;            // el nodo de la lista que tiene ese dato
} tClaveNodo;

/* Variable LOCAL que se arma en cada insertar/buscar/sacar: la entrada + el cmp del usuario.
   Es lo que le paso al arbol como "d", asi compararClaveNodo tiene el cmp sin guardarlo en el arbol */
typedef struct
{
    tClaveNodo entrada;
    Cmp cmp;
} tBusqueda;

typedef struct
{
    tListaDoble listaDoble;     // los datos, ordenados por uso: pri = mas reciente, ult = menos reciente
    tArbolBinBusq arbol;        // clave -> nodo de la lista, ordenado por clave
    size_t capMax;              // cantidad max de ELEMENTOS
    int ce;
    Cmp cmpClaves;
} tCacheMejorada;

void crear_lrucache_mejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp);
int agregar_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam);
int obtener_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam);
int borrar_lrucache_mejorada(tCacheMejorada *pc, void *d);
void vaciar_lrucache_mejorada(tCacheMejorada *pc);
unsigned altura_lrucache_mejorada(tCacheMejorada *pc);     // altura del arbol (la pide la consigna)

#endif // T_LRU_CACHE_MEJORADA_H_INCLUDED
