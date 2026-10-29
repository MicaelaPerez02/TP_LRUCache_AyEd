#ifndef T_LRU_CACHE_MEJORADA_H_INCLUDED
#define T_LRU_CACHE_MEJORADA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "TDAListaDoble.h"
#include "TDAArbol.h"

#define SIN_CAPACIDAD -5
#define PUNTERO_INVALIDO -4

#ifndef NO_ENCONTRADO
#define NO_ENCONTRADO -3
#endif

#ifndef CMP_DEFINIDO
#define CMP_DEFINIDO
typedef int (*Cmp)(const void *, const void *);
#endif

typedef struct
{
    const void *clave;
    tNodoDoble *nodo;
} tClaveNodo;

typedef struct
{
    tListaDoble listaDoble;
    tArbolBinBusq arbol;
    size_t capMax;
    int ce;
    Cmp cmpClaves;
} tCacheMejorada;

void crearLruCacheMejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp);
int agregarLruCacheMejorada(tCacheMejorada *pc, void *d, size_t tam);
int obtenerLruCacheMejorada(tCacheMejorada *pc, void *d, size_t tam);
int borrarLruCacheMejorada(tCacheMejorada *pc, void *d);
void vaciarLruCacheMejorada(tCacheMejorada *pc);
unsigned alturaLruCacheMejorada(tCacheMejorada *pc);

// Auxiliares que tocan el arbol
int compararEntradas(const void *entradaBuscada, const void *entradaGuardada, const void *contexto);
int registrarNodoEnArbol(tCacheMejorada *pc, tNodoDoble *nodo);
tNodoDoble *buscarNodoEnArbol(tCacheMejorada *pc, const void *clave);
tNodoDoble *sacarNodoDelArbol(tCacheMejorada *pc, const void *clave);

#endif // T_LRU_CACHE_MEJORADA_H_INCLUDED
