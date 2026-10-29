#ifndef T_LRU_CACHE_H_INCLUDED
#define T_LRU_CACHE_H_INCLUDED

#include "TDALista.h"
#define PUNTERO_INVALIDO -4
#define SIN_CAPACIDAD -5

#ifndef CMP_DEFINIDO
#define CMP_DEFINIDO
typedef int (*Cmp)(const void *, const void *);
#endif

typedef struct
{
    tLista lista; // tNodo **
    size_t capMax; // cant max de ELEMENTOS
    int ce;
    Cmp cmpClaves;
} tCache;

int CmpXClave(const void *c1, const void *c2);

void crearLruCache(tCache *pc, unsigned capMax, Cmp cmp);
int agregarLruCache(tCache *pc, void *d, size_t tam);
int obtenerLruCache(tCache *pc, void *d, size_t tam);
int borrarLruCache(tCache *pc, void *d);
void vaciarLruCache(tCache *pc);

#endif // T_LRU_CACHE_H_INCLUDED
