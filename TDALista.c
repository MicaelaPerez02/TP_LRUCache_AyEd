#include "TDALista.h"

void crearLista(tLista *p)
{
    *p=NULL;
}

void vaciarLista(tLista *p)
{
    tNodo *aux;

    while(*p)
    {
        aux=*p;
        *p=aux->sig;

        free(aux->info);
        free(aux);
    }
}

int insertarAlInicioLista(tLista *p, const void *d, size_t tam)
{
    tNodo *nue;

    nue=(tNodo *)malloc(sizeof(tNodo));
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
    nue->sig=*p;

    *p=nue;

    return EXITO;
}

int sacarUltimoLista(tLista *p, void *d, size_t tam)
{
    if(!*p)
        return SIN_DATOS;

    while( (*p)->sig )
        p=&(*p)->sig;

    if(d) // d es opcional en este caso
    {
        memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));
    }

    free((*p)->info);
    free(*p);

    *p=NULL;

    return EXITO;
}


int moverAlInicioLista(tLista *p, const void *d,  Cmp cmp)
{
    tLista *act=p;
    tNodo *aux;

    if(!*act)
        return SIN_DATOS;

    while(*act)
    {
        if(cmp((*act)->info, d) == 0)
        {
            // Desengancho
            aux=*act;
            *act=aux->sig;

            // Reengancho adelante
            aux->sig=*p;
            *p=aux;

            return EXITO;
        }

        act=&(*act)->sig;
    }

    return NO_ENCONTRADO;
}

int eliminarElementoLista(tLista *p, const void *d, Cmp cmp)
{
    tNodo *aux;

    if(!*p)
        return SIN_DATOS;

    while(*p)
    {
        if( cmp((*p)->info, d)==0 )
        {
            // Desengancho
            aux=*p;
           *p=aux->sig;

            // Elimino
           free(aux->info);
           free(aux);

           return EXITO;
        }

        p=&(*p)->sig;
    }

    return NO_ENCONTRADO;
}
