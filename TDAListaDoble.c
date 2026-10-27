#include "TDAListaDoble.h"

void crearListaDoble(tListaDoble *p)
{
    p->pri = NULL;
    p->ult = NULL;
}

int esListaDobleVacia(const tListaDoble *p)
{
    return p->pri == NULL;
}

int insertarAlInicioListaDoble(tListaDoble *p, const void *d, size_t tam)
{
    tNodoDoble *nue = malloc(sizeof(tNodoDoble));

    if(!nue)
        return SIN_MEMORIA;

    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return SIN_MEMORIA;
    }

    memcpy(nue->info, d, tam);
    nue->tamInfo = tam;

    nue->ant = NULL;
    nue->sig = p->pri;

    if(p->pri)
        p->pri->ant = nue;
    else
        p->ult = nue;       // la lista estaba vacia: el nuevo es el primero Y el ultimo

    p->pri = nue;

    return EXITO;
}

int eliminarNodoListaDoble(tListaDoble *p, tNodoDoble *nodo)
{
    if(!nodo)
        return SIN_DATOS;

    /* lo desengancho de la lista: el anterior y el siguiente se "saltean" al nodo */
    if(nodo->ant)
        nodo->ant->sig = nodo->sig;
    else
        p->pri = nodo->sig;     // era el primero

    if(nodo->sig)
        nodo->sig->ant = nodo->ant;
    else
        p->ult = nodo->ant;     // era el ultimo

    free(nodo->info);
    free(nodo);

    return EXITO;
}

int moverAlInicioListaDoble(tListaDoble *p, tNodoDoble *nodo)
{
    if(!nodo)
        return SIN_DATOS;

    if(p->pri == nodo)
        return EXITO;           // ya estaba adelante de todo

    /* lo desengancho de donde esta (aca nunca es el primero, asi que ant existe) */
    nodo->ant->sig = nodo->sig;

    if(nodo->sig)
        nodo->sig->ant = nodo->ant;
    else
        p->ult = nodo->ant;     // era el ultimo

    /* y lo enlazo al principio */
    nodo->ant = NULL;
    nodo->sig = p->pri;
    p->pri->ant = nodo;
    p->pri = nodo;

    return EXITO;
}

int sacarUltimoListaDoble(tListaDoble *p, void *d, size_t tam)
{
    tNodoDoble *elim = p->ult;

    if(!elim)
        return SIN_DATOS;

    if(d)
        memcpy(d, elim->info, MINIMO(tam, elim->tamInfo));

    return eliminarNodoListaDoble(p, elim);
}

void vaciarListaDoble(tListaDoble *p)
{
    tNodoDoble *elim;

    while(p->pri)
    {
        elim = p->pri;
        p->pri = elim->sig;

        free(elim->info);
        free(elim);
    }

    p->ult = NULL;
}
