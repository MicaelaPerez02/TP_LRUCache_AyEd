#include "t_lru_cache_mejorada.h"

void crear_lrucache_mejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp)
{
    if(!pc)
        return;

    crearListaDoble(&pc->listaDoble);
    crearArbolBinBusq(&pc->arbol);
    pc->capMax=capMax;
    pc->cmpClaves=cmp;
    pc->ce=0;
}

void vaciar_lrucache_mejorada(tCacheMejorada *pc)
{
    if(!pc)
        return;

    vaciarListaDoble(&pc->listaDoble);
    vaciarArbolBinBusq(&pc->arbol);
    pc->capMax=0;
    pc->cmpClaves=NULL;
    pc->ce=0;
}

unsigned altura_lrucache_mejorada(tCacheMejorada *pc)
{
    if(!pc)
        return 0;

    return alturaArbolBin(&pc->arbol);
}

int agregar_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam)
{
    tNodo *nodoDup, *nodoNuevo, *ultimo;

    if(!pc)
        return PUNTERO_INVALIDO;

    // Si la clave ya existia, saco el dato viejo primero del indice, despues de la lista
    nodoDup = sacarDeIndice(&pc->arbol, d, pc->cmpClaves);

    if(nodoDup)
    {
        eliminarNodoListaDoble(&pc->listaDoble, nodoDup);
        pc->ce--;
    }

    // Dato nuevo al inicio de la lista
    if(insertarAlInicioListaDoble(&pc->listaDoble, d, tam) != EXITO)
        return SIN_MEMORIA;

    nodoNuevo = pc->listaDoble;

    // Lo sumo al indice
    if(insertarEnIndice(&pc->arbol, nodoNuevo, pc->cmpClaves) != EXITO)
    {
        eliminarNodoListaDoble(&pc->listaDoble, nodoNuevo);
        return SIN_MEMORIA;
    }

    pc->ce++;

    // Si desborda, sale el ultimo
    if((size_t)pc->ce > pc->capMax)
    {
        ultimo = pc->listaDoble;
        while(ultimo->sig)
            ultimo = ultimo->sig;

        sacarDeIndice(&pc->arbol, ultimo->info, pc->cmpClaves); // la clave se lee ANTES de liberar el nodo
        eliminarNodoListaDoble(&pc->listaDoble, ultimo);
        pc->ce--;
    }

    return EXITO;
}
