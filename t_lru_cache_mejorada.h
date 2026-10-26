#ifndef T_LRU_CACHE_MEJORADA_H_INCLUDED
#define T_LRU_CACHE_MEJORADA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "TDAListaDoble.h"
#include "TDAIndice.h"

#ifndef PUNTERO_INVALIDO
#define PUNTERO_INVALIDO -4
#endif

typedef struct
{
    tListaDoble listaDoble;
    tIndice indice;
    size_t capMax;
    int ce;
} tCacheMejorada;

void crear_lrucache_mejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp);
int agregar_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam);
void vaciar_lrucache_mejorada(tCacheMejorada *pc);

#endif // T_LRU_CACHE_MEJORADA_H_INCLUDED
