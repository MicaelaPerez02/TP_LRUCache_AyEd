#include "TDALruCache.h"

void crearLruCache(tCache *pc, unsigned capMax, Cmp cmp)
{
    if(!pc)
        return;

    crearLista(&pc->lista);
    pc->capMax=capMax;
    pc->cmpClaves=cmp;
    pc->ce=0;
}

void vaciarLruCache(tCache *pc)
{
    if(!pc)
        return;

    vaciarLista(&pc->lista);
    pc->capMax=0;
    pc->cmpClaves=NULL;
    pc->ce=0;
}

int agregarLruCache(tCache *pc, void *d, size_t tam)
{
    if(!pc)
        return PUNTERO_INVALIDO;
    else if(pc->capMax == 0)
        return SIN_CAPACIDAD;

    // Si esta duplicado, reemplazo la info y lo dejo adelante
    if( moverAlInicioLista(&pc->lista, d, pc->cmpClaves) == EXITO )
        return reemplazarInfoPrimeroLista(&pc->lista, d, tam);

    // Sino, inserto el valor al inicio
    if( insertarAlInicioLista(&pc->lista, d, tam) != EXITO )
        return SIN_MEMORIA;

    pc->ce++;

    // Si hay desborde, saco el ultimo
    if( (size_t)pc->ce > pc->capMax)
    {
        sacarUltimoLista(&pc->lista, NULL, tam);
        pc->ce--;
    }

    return EXITO;
}

int borrarLruCache(tCache *pc, void *d)
{
    if(!pc)
        return PUNTERO_INVALIDO;

    if( eliminarElementoLista(&pc->lista, d, pc->cmpClaves) == EXITO )
    {
        pc->ce--;
        return EXITO;
    }

    return NO_ENCONTRADO;
}

int obtenerLruCache(tCache *pc, void *d, size_t tam)
{
    if(!pc)
        return PUNTERO_INVALIDO;

    // Si lo encuentro, lo muevo al inicio de la lista
    if( moverAlInicioLista(&pc->lista, d, pc->cmpClaves) == EXITO )
    {
        // Copio el dato encontrado
        memcpy(d, pc->lista->info, MINIMO(tam, pc->lista->tamInfo));
        return EXITO;
    }

    return NO_ENCONTRADO;
}

int CmpXClave(const void *c1, const void *c2)
{
    int a = *(const int *)c1;
    int b = *(const int *)c2;

    return (a > b) - (a < b);
}
