#include "t_lru_cache_mejorada.h"

/* Auxiliares: son las unicas que tocan el arbol */
int compararClaveNodo(const void *a, const void *b);
int insertarClaveEnArbol(tCacheMejorada *pc, tNodo *nodo);
tNodo *buscarNodoPorClave(tCacheMejorada *pc, const void *clave);
tNodo *sacarClaveDelArbol(tCacheMejorada *pc, const void *clave);


void crear_lrucache_mejorada(tCacheMejorada *pc, unsigned capMax, Cmp cmp)
{
    if(!pc)
        return;

    crearListaDoble(&pc->listaDoble);
    crearArbolBinBusq(&pc->arbol);
    pc->capMax = capMax;
    pc->cmpClaves = cmp;
    pc->ce = 0;
}

void vaciar_lrucache_mejorada(tCacheMejorada *pc)
{
    if(!pc)
        return;

    vaciarListaDoble(&pc->listaDoble);
    vaciarArbolBinBusq(&pc->arbol);
    pc->capMax = 0;
    pc->cmpClaves = NULL;
    pc->ce = 0;
}

unsigned altura_lrucache_mejorada(tCacheMejorada *pc)
{
    if(!pc)
        return 0;

    return alturaArbolBin(&pc->arbol);
}

int agregar_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam)
{
    tNodo *nodoViejo;

    if(!pc)
        return PUNTERO_INVALIDO;

    /* 1. Si la clave ya existia, saco el dato viejo (primero del arbol, despues de la lista) */
    nodoViejo = sacarClaveDelArbol(pc, d);

    if(nodoViejo)
    {
        eliminarNodoListaDoble(&pc->listaDoble, nodoViejo);
        pc->ce--;
    }

    /* 2. Dato nuevo al inicio de la lista */
    if(insertarAlInicioListaDoble(&pc->listaDoble, d, tam) != EXITO)
        return SIN_MEMORIA;

    /* 3. Clave + nodo nuevo al arbol (el nodo nuevo es pri) */
    if(insertarClaveEnArbol(pc, pc->listaDoble.pri) != EXITO)
    {
        eliminarNodoListaDoble(&pc->listaDoble, pc->listaDoble.pri);    // deshago el paso 2
        return SIN_MEMORIA;
    }

    pc->ce++;

    /* 4. Desborde: sale el ultimo (primero del arbol, despues de la lista) */
    if((size_t)pc->ce > pc->capMax)
    {
        sacarClaveDelArbol(pc, pc->listaDoble.ult->info);   // la clave se lee ANTES de liberar el nodo
        sacarUltimoListaDoble(&pc->listaDoble, NULL, 0);
        pc->ce--;
    }

    return EXITO;
}

int obtener_lrucache_mejorada(tCacheMejorada *pc, void *d, size_t tam)
{
    tNodo *nodo;

    if(!pc)
        return PUNTERO_INVALIDO;

    nodo = buscarNodoPorClave(pc, d);   // el arbol solo se CONSULTA: no se modifica

    if(!nodo)
        return NO_ENCONTRADO;

    memcpy(d, nodo->info, MINIMO(tam, nodo->tamInfo));

    moverAlInicioListaDoble(&pc->listaDoble, nodo);     // ahora es el mas reciente

    return EXITO;
}

int borrar_lrucache_mejorada(tCacheMejorada *pc, void *d)
{
    tNodo *nodo;

    if(!pc)
        return PUNTERO_INVALIDO;

    if(esListaDobleVacia(&pc->listaDoble))
        return SIN_DATOS;

    nodo = sacarClaveDelArbol(pc, d);

    if(!nodo)
        return NO_ENCONTRADO;

    eliminarNodoListaDoble(&pc->listaDoble, nodo);
    pc->ce--;

    return EXITO;
}


/* ---------------------------- auxiliares del arbol ---------------------------- */

/* Es el cmp que recibe el ARBOL. Siempre lo llama cmp(d, info_del_nodo):
   - a (d)    = la variable local tBusqueda que arme yo (clave a buscar/insertar + cmp del usuario)
   - b (info) = la entrada tClaveNodo que ya esta guardada en el arbol
   Comparo las CLAVES con el cmp del usuario */
int compararClaveNodo(const void *a, const void *b)
{
    const tBusqueda *busq = a;
    const tClaveNodo *guardada = b;

    return busq->cmp(busq->entrada.clave, guardada->clave);
}

int insertarClaveEnArbol(tCacheMejorada *pc, tNodo *nodo)
{
    tBusqueda busq;

    busq.entrada.clave = nodo->info;
    busq.entrada.nodo = nodo;
    busq.cmp = pc->cmpClaves;

    return insertarRecArbolBinBusq(&pc->arbol, &busq, sizeof(tClaveNodo), compararClaveNodo);
}

tNodo *buscarNodoPorClave(tCacheMejorada *pc, const void *clave)
{
    tBusqueda busq;
    tArbolBinBusq *caja;

    busq.entrada.clave = clave;     // para buscar solo hacen falta la clave y el cmp (nodo no se usa)
    busq.cmp = pc->cmpClaves;

    caja = buscarRecElemArbolBinBusq(&pc->arbol, &busq, compararClaveNodo);

    if(!caja)
        return NULL;

    return ((tClaveNodo *)(*caja)->info)->nodo;
}

tNodo *sacarClaveDelArbol(tCacheMejorada *pc, const void *clave)
{
    tBusqueda busq;
    tArbolBinBusq *caja;
    tNodo *nodo;

    busq.entrada.clave = clave;
    busq.cmp = pc->cmpClaves;

    caja = buscarRecElemArbolBinBusq(&pc->arbol, &busq, compararClaveNodo);

    if(!caja)
        return NULL;

    nodo = ((tClaveNodo *)(*caja)->info)->nodo;     // lo guardo ANTES de borrar el nodo del arbol

    eliminarRaizArbolBinBusq(caja);

    return nodo;
}
