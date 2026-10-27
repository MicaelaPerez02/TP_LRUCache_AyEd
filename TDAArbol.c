#include "TDAArbol.h"
void crearArbolBinBusq(tArbolBinBusq *p)
{
    *p=NULL;
}

int insertarRecArbolBinBusq(tArbolBinBusq *p, const void *d, size_t tam, Cmp cmp)
{
    tNodoArbol *nue;
    int rc;

    if(*p)
    {
        if( (rc=cmp(d, (*p)->info)) < 0 )
            return insertarRecArbolBinBusq(&(*p)->izq, d, tam, cmp);
        else if(rc > 0)
            return insertarRecArbolBinBusq(&(*p)->der, d, tam, cmp);
        else
            return DUPLICADO;
    }

    nue=(tNodoArbol *)malloc(sizeof(tNodoArbol));
    if(!nue)
        return SIN_MEMORIA;

    nue->info=malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return SIN_MEMORIA;
    }

    memcpy(nue->info, d, tam);
    nue->tamInfo=tam;
    nue->der=nue->izq=NULL;
    *p=nue;

    return EXITO;
}

tNodoArbol **buscarRecElemArbolBinBusq(tArbolBinBusq *p, const void *d, Cmp cmp)
{
    int rc;
    if(!*p)
        return NULL;

    if(*p && (rc=cmp(d, (*p)->info)) )
    {
        if(rc < 0)
            return buscarRecElemArbolBinBusq(&(*p)->izq, d, cmp);

        return buscarRecElemArbolBinBusq(&(*p)->der, d, cmp);
    }

    return (tNodoArbol **)p;
}

tNodoArbol **mayorNodoArbolBinBusq(const tArbolBinBusq *p)
{
    if(!*p)
        return NULL;

    while( (*p)->der )
        p=&(*p)->der;

    return (tNodoArbol **)p;
}

tNodoArbol **menorNodoArbolBinBusq(const tArbolBinBusq *p)
{
    if(!*p)
        return NULL;

    while( (*p)->izq )
        p=&(*p)->izq;

    return (tNodoArbol **)p;
}

int eliminarRaizArbolBinBusq(tArbolBinBusq *p)
{
    tNodoArbol **remp, *elim;

    if(!*p)
        return SIN_DATOS;

    free((*p)->info);

    if(!(*p)->izq && !(*p)->der)
    {
        free(*p);
        *p=NULL;
        return EXITO;
    }

    remp = alturaArbolBin(&(*p)->izq) > alturaArbolBin(&(*p)->der) ?
                mayorNodoArbolBinBusq(&(*p)->izq) :
                menorNodoArbolBinBusq(&(*p)->der);

    elim= *remp;
    (*p)->info = elim->info;
    (*p)->tamInfo = elim->tamInfo;
    *remp = elim->izq?elim->izq:elim->der;
    free(elim);

    return EXITO;
}

int eliminarRecArbolBinBusq(tArbolBinBusq *p, void *d, size_t tam, Cmp cmp)
{
    if(! (p = buscarRecElemArbolBinBusq(p, d, cmp)) )
        return 0;

    memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo) );

    return eliminarRaizArbolBinBusq(p);
}

void vaciarArbolBinBusq(tArbolBinBusq *p)
{
    if(*p)
    {
        vaciarArbolBinBusq( &(*p)->izq );
        vaciarArbolBinBusq( &(*p)->der );
        free( (*p)->info );
        free(*p);
        *p=NULL;
    }
}

unsigned alturaArbolBin(tArbolBinBusq *p)
{
    int hi, hd;

    if(!*p)
        return 0;

    hi = alturaArbolBin(&(*p)->izq );
    hd = alturaArbolBin(&(*p)->der );

    return (hi > hd? hi : hd ) + 1;
}
