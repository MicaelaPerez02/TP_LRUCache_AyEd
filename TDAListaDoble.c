#include "TDAListaDoble.h"

void crearListaDoble(tListaDoble *p)
{
    *p=NULL;
}

int esListaDobleVacia(const tListaDoble *p)
{
    return *p==NULL;
}

int esListaDobleLlena(const tListaDoble *p, size_t tam)
{
    void *aux=malloc(sizeof(tNodo));
    void *info=malloc(tam);

    free(aux);
    free(info);

    return aux==NULL || info==NULL;
}

int insertarAlInicioListaDoble(tListaDoble *p, const void *d, size_t tam)
{
    tNodo *nue, *act=*p;

    if(act)
        while( act->ant )
            act=act->ant;

    nue=malloc(sizeof(tNodo));
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
    nue->sig=act;
    nue->ant=NULL;

    if(act)
        act->ant=nue;

    *p=nue;

    return EXITO;
}

int insertarAlFinalListaDoble(tListaDoble *p, const void *d, size_t tam)
{
    tNodo *nue, *act=*p;

    if(act)
    {
        while(act->sig)
            act=act->sig;
    }

    nue=malloc(sizeof(tNodo));
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
    nue->sig=NULL;
    nue->ant=act;

    if(act)
        act->sig=nue;

    *p=nue;

    return EXITO;
}

void mostrarDeIzqADer(const tListaDoble *p, void(*mostrar)(const void *))
{
    tNodo *act=*p;

    if(act)
    {
        mostrar(NULL);
        while(act->ant)
        {
            act=act->ant;
        }

        while(act)
        {
            mostrar(act->info);
            act=act->sig;
        }
    }
}

void mostrarDeDerAIzq(const tListaDoble *p, void(*mostrar)(const void *))
{
    tNodo *act=*p;

    if(act)
    {
        mostrar(NULL);
        while(act->sig)
        {
            act=act->sig;
        }

        while(act)
        {
            mostrar(act->info);
            act=act->ant;
        }
    }
}

int sacarUltimoListaDoble(tListaDoble *p, void *d, size_t tam)
{
    tNodo *act=*p;


        if(act)
        {
            while(act->sig)
                act=act->sig;

            if(d) // d es opcional en este caso
                memcpy(d, act->info, MINIMO(act->tamInfo, tam));

            if(act->ant)
            {
                act->ant->sig=NULL;
                *p=act->ant;
            } else
            {
                *p=NULL; // Si no tengo anterior, no tengo mas nodos disponibles
            }

            free(act->info);
            free(act);
        } else
        {
            return SIN_DATOS;
        }

    return EXITO;
}

int eliminarNodoListaDoble(tListaDoble *p, tNodo *nodo)
{
    if(!nodo)
        return SIN_DATOS;

    if(nodo->ant)
        nodo->ant->sig=nodo->sig;
    if(nodo->sig)
        nodo->sig->ant=nodo->ant;

    if(*p==nodo)
    {
        if(nodo->ant)
            *p=nodo->ant;
        else
            *p=nodo->sig;
    }

    free(nodo->info);
    free(nodo);

    return EXITO;
}

int moverAlInicioListaDoble(tListaDoble *p, tNodo *nodo)
{
    if(nodo && *p)
    {
        while( (*p)->ant )
            *p=(*p)->ant;

        if(*p == nodo)
            return EXITO; // No muevo nada porque ya esta primero.

        if(nodo->ant)
            nodo->ant->sig=nodo->sig;
        if(nodo->sig)
            nodo->sig->ant=nodo->ant;

        nodo->ant=NULL;
        nodo->sig=*p;
        (*p)->ant=nodo;
        *p=nodo;
    } else
        return SIN_DATOS;

    return EXITO;
}

void vaciarListaDoble(tListaDoble *p)
{
    tNodo *aux, *act=*p;

    if(act)
    {
        while(act->ant)
            act=act->ant;

        while(act)
        {
            aux=act->sig;
            free(act->info);
            free(act);
            act=aux;
        }
        *p=NULL;
    }
}
