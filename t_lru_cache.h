#ifndef T_LRU_CACHE_H_INCLUDED
#define T_LRU_CACHE_H_INCLUDED

#include "TDALista.h"
#define PUNTERO_INVALIDO -4
#define NO_ENCONTRADO -3

typedef int (*Cmp)(const void *, const void *);
typedef void (*Accion)(const void *);

typedef struct
{
    tLista lista; // Puntero al primer nodo (tNodo *)
    size_t capMax; // Cantidad max de ELEMENTOS
    int ce;
    Cmp cmpClaves;
} tCache;

int CmpXClave(const void *c1, const void *c2);
void mostrar(const void *c1);

void crear_lrucache(tCache *pc, unsigned capMax, Cmp cmp);
int agregar_lrucache(tCache *pc, void *d, size_t tam);
int obtener_lrucache(tCache *pc, void *d, size_t tam);
int borrar_lrucache(tCache *pc, void *d);

void recorrer_lrucache(tCache *pc, Accion ac);

void vaciar_lrucache(tCache *pc);

#endif // T_LRU_CACHE_H_INCLUDED
