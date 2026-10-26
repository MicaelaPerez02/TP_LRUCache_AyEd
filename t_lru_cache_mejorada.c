#include "t_lru_cache_mejorada.h"

void crear_lrucache_mejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp)
{
    if(!pc)
        return;

    crearListaDoble(&pc->listaDoble);
    crearIndice(&pc->indice, cmp);
    pc->capMax=capMax;
    pc->ce=0;
}

void vaciar_lrucache_mejorada(tCacheMejorada *pc)
{
    if(!pc)
        return;

    vaciarListaDoble(&pc->listaDoble);
    vaciarIndice(&pc->indice);
    pc->capMax=0;
    pc->ce=0;
}

int agregar_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam)
{
    tNodo *nodoDup, *nodoNuevo, *ultimo;

    if(!pc)
        return PUNTERO_INVALIDO;

    // Si la clave ya existia, saco el dato viejo primero del indice y despues de la lista
    nodoDup = sacarDeIndice(&pc->indice, d);

    if(nodoDup)
    {
        eliminarNodoListaDoble(&pc->listaDoble, nodoDup);
        pc->ce--;
    }

    // Dato nuevo al inicio de la lista
    if(insertarAlInicioListaDoble(&pc->listaDoble, d, tam) != EXITO)
        return SIN_MEMORIA;

    nodoNuevo = pc->listaDoble;

    // Inserto en el indice tambien
    if(insertarEnIndice(&pc->indice, nodoNuevo) != EXITO)
    {
        eliminarNodoListaDoble(&pc->listaDoble, nodoNuevo);
        return SIN_MEMORIA;
    }

    pc->ce++;

    // Si desborda, elimino el ultimo
    if( pc->ce > pc->capMax)
    {
        ultimo = pc->listaDoble;
        while(ultimo->sig)
            ultimo = ultimo->sig;

        sacarDeIndice(&pc->indice, ultimo->info);      // la clave se lee ANTES de liberar el nodo
        eliminarNodoListaDoble(&pc->listaDoble, ultimo);
        pc->ce--;
    }

    return EXITO;
}
