#include "t_lru_cache_mejorada.h"

void crearLruCacheMejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp)
{
    if(!pc)
        return;

    crearListaDoble(&pc->listaDoble);
    crearArbolBinBusq(&pc->arbol);
    pc->capMax = capMax;
    pc->cmpClaves = cmp;
    pc->ce = 0;
}

void vaciarLruCacheMejorada(tCacheMejorada *pc)
{
    if(!pc)
        return;

    vaciarListaDoble(&pc->listaDoble);
    vaciarArbolBinBusq(&pc->arbol);
    pc->capMax = 0;
    pc->cmpClaves = NULL;
    pc->ce = 0;
}

unsigned alturaLruCacheMejorada(tCacheMejorada *pc)
{
    if(!pc)
        return 0;

    return alturaArbolBin(&pc->arbol);
}

int agregarLruCacheMejorada(tCacheMejorada *pc, void *d, size_t tam)
{
    tNodoDoble *nodoViejo;

    if(!pc)
        return PUNTERO_INVALIDO;
    else if(pc->capMax == 0)
        return SIN_CAPACIDAD;

    // Si la clave ya existia piso el dato en su nodo y lo llevo al inicio
    nodoViejo = buscarNodoEnArbol(pc, d);
    if(nodoViejo)
    {
        if(reemplazarInfoNodoListaDoble(nodoViejo, d, tam) != EXITO)
            return SIN_MEMORIA;

        moverAlInicioListaDoble(&pc->listaDoble, nodoViejo);
        return EXITO;
    }

    // Dato nuevo, se inserta en lista y arbol
    if(insertarAlInicioListaDoble(&pc->listaDoble, d, tam) != EXITO)
        return SIN_MEMORIA;

    if(registrarNodoEnArbol(pc, pc->listaDoble.pri) != EXITO)
    {
        eliminarNodoListaDoble(&pc->listaDoble, pc->listaDoble.pri);
        return SIN_MEMORIA;
    }

    pc->ce++;

    // Si hay desborde, saco el ultimo
    if((size_t)pc->ce > pc->capMax)
    {
        sacarNodoDelArbol(pc, pc->listaDoble.ult->info);
        sacarUltimoListaDoble(&pc->listaDoble, NULL, 0);
        pc->ce--;
    }

    return EXITO;
}

int obtenerLruCacheMejorada(tCacheMejorada *pc, void *d, size_t tam)
{
    tNodoDoble *nodo;

    if(!pc)
        return PUNTERO_INVALIDO;

    nodo = buscarNodoEnArbol(pc, d); // el arbol solo se CONSULTA: no se modifica

    if(!nodo)
        return NO_ENCONTRADO;

    memcpy(d, nodo->info, MINIMO(tam, nodo->tamInfo));

    moverAlInicioListaDoble(&pc->listaDoble, nodo); // ahora es el mas reciente

    return EXITO;
}

int borrarLruCacheMejorada(tCacheMejorada *pc, void *d)
{
    tNodoDoble *nodo;

    if(!pc)
        return PUNTERO_INVALIDO;

    nodo = sacarNodoDelArbol(pc, d);

    if(!nodo)
        return NO_ENCONTRADO;

    eliminarNodoListaDoble(&pc->listaDoble, nodo);
    pc->ce--;

    return EXITO;
}


/* ---------------------------- auxiliares del arbol ---------------------------- */

int compararEntradas(const void *entradaBuscada, const void *entradaGuardada, const void *contexto)
{
    const tClaveNodo *buscada = entradaBuscada;
    const tClaveNodo *guardada = entradaGuardada;
    const tCacheMejorada *pc = contexto;

    return pc->cmpClaves(buscada->clave, guardada->nodo->info);
}

int registrarNodoEnArbol(tCacheMejorada *pc, tNodoDoble *nodo)
{
    tClaveNodo entrada;

    entrada.clave = nodo->info;
    entrada.nodo = nodo;

    return insertarRecArbolBinBusq(&pc->arbol, &entrada, sizeof(tClaveNodo), compararEntradas, pc);
}

tNodoDoble *buscarNodoEnArbol(tCacheMejorada *pc, const void *clave)
{
    tClaveNodo entrada;
    tArbolBinBusq *caja;

    entrada.clave = clave;      // para buscar solo importa la clave
    entrada.nodo = NULL;

    caja = buscarRecElemArbolBinBusq(&pc->arbol, &entrada, compararEntradas, pc);

    if(!caja)
        return NULL;

    return ((tClaveNodo *)(*caja)->info)->nodo;
}

tNodoDoble *sacarNodoDelArbol(tCacheMejorada *pc, const void *clave)
{
    tClaveNodo entrada;
    tArbolBinBusq *caja;
    tNodoDoble *nodo;

    entrada.clave = clave;
    entrada.nodo = NULL;

    caja = buscarRecElemArbolBinBusq(&pc->arbol, &entrada, compararEntradas, pc);

    if(!caja)
        return NULL;

    nodo = ((tClaveNodo *)(*caja)->info)->nodo;     // lo guardo ANTES de borrar el nodo del arbol

    eliminarRaizArbolBinBusq(caja);

    return nodo;
}
