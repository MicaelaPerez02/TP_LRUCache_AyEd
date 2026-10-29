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
    if(!p)
        return PUNTERO_INVALIDO;

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
        p->ult = nue; // la lista estaba vacia: el nuevo es el primero Y el ultimo

    p->pri = nue;

    return EXITO;
}

int eliminarNodoListaDoble(tListaDoble *p, tNodoDoble *nodo)
{
    if(!p || !nodo)
        return PUNTERO_INVALIDO;

    // lo desengancho de la lista
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
    if(!p || !nodo)
        return PUNTERO_INVALIDO;

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
    tNodoDoble *elim;

    if(!p)
        return PUNTERO_INVALIDO;

    elim = p->ult;
    if(!elim)
        return SIN_DATOS;

    if(d)
        memcpy(d, elim->info, MINIMO(tam, elim->tamInfo));

    // Desenganche, el anterior pasa a ser el ultimo
    if(elim->ant)
    {
        elim->ant->sig=elim->sig;
        p->ult=elim->ant;
    }
    else     // Si es el ultimo no tiene siguiente, si no tiene anterior no hay mas nodos
    {
        p->ult=NULL;
        p->pri=NULL;
    }

    free(elim->info);
    free(elim);

    return EXITO;
}

int reemplazarInfoNodoListaDoble(tNodoDoble *nodo, const void *d, size_t tam)
{
    void *nueInfo;

    if(!nodo)
        return SIN_DATOS;

    if(nodo->tamInfo != tam)
    {
        nueInfo = realloc(nodo->info, tam);
        if(!nueInfo)
            return SIN_MEMORIA;
        nodo->info = nueInfo;
        nodo->tamInfo = tam;
    }

    memcpy(nodo->info, d, tam);
    return EXITO;
}

void vaciarListaDoble(tListaDoble *p)
{
    tNodoDoble *elim;

    if(!p)
        return;

    while(p->pri)
    {
        elim = p->pri;
        p->pri = elim->sig;

        free(elim->info);
        free(elim);
    }

    p->ult = NULL;
}
