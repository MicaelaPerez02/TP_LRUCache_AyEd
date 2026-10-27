#include "t_lru_cache.h"

void crear_lrucache(tCache *pc, unsigned capMax, Cmp cmp)
{
    if(!pc)
        return;

    crearLista(&pc->lista);
    pc->capMax=capMax;
    pc->cmpClaves=cmp;
    pc->ce=0;
}

void vaciar_lrucache(tCache *pc)
{
    if(!pc)
        return;

    vaciarLista(&pc->lista);
    pc->capMax=0;
    pc->cmpClaves=NULL;
    pc->ce=0;
}

int agregar_lrucache(tCache *pc, void *d, size_t tam)
{
    tLista *p;
    tNodo *elim;
    int encontrado=0;

    if(!pc)
        return PUNTERO_INVALIDO;

    p=&pc->lista;

    while(*p && !encontrado)
    {
        if(pc->cmpClaves( (*p)->info, d)==0 )
        {
            elim=*p;
            *p=(*p)->sig;

            free(elim->info);
            free(elim);

            pc->ce--;
            encontrado=1;
        }
        else
        {
            p=&(*p)->sig;
        }
    }

    if( insertarAlInicioLista(&pc->lista, d, tam) != EXITO )
        return SIN_MEMORIA;
    pc->ce++;

    if(pc->ce > pc->capMax)
    {
        sacarUltimoLista(&pc->lista, NULL, tam);
        pc->ce--;
    }

    return EXITO;
}

int borrar_lrucache(tCache *pc, void *d)
{
    tLista *p;
    tNodo *elim;

    if(!pc)
        return PUNTERO_INVALIDO;

    p=&pc->lista;

    while(*p)
    {
        if( pc->cmpClaves((*p)->info, d) == 0 )
        {
            elim=*p;
            *p = elim->sig;

            free(elim->info);
            free(elim);

            pc->ce--;

            return EXITO;
        }

        p=&(*p)->sig;
    }

    return NO_ENCONTRADO;
}

int obtener_lrucache(tCache *pc, void *d, size_t tam)
{
    tLista *p; // La dirección de la lista, sin el & tengo el primer nodo, no puedo modificar a donde a punta la lista como tal
    tNodo *aux;

    if(!pc)
        return PUNTERO_INVALIDO;

    p=&pc->lista;

    // Mientras tenga nodos (pc->lista)
    // Y no haya encontrado la clave (*p)->info = pc->lista->info
    while(*p && pc->cmpClaves( (*p)->info, d) != 0)
    {
        p = &(*p)->sig; // Puntero a la caja sig. del nodo actual
    }

    if(*p) // Si lo encontre
    {
        memcpy(d, (*p)->info, MINIMO(tam, (*p)->tamInfo));

        // Desengancho
        aux=*p;
        *p=(*p)->sig;

        // Engancho al inicio
        aux->sig = pc->lista;
        pc->lista=aux;
    }
    else
    {
        return NO_ENCONTRADO;
    }

    return EXITO;
}

void recorrer_lrucache(tCache *pc, Accion ac)
{
    tNodo *p;

    if(!pc)
        return;

    p=pc->lista;

    while(p)
    {
        ac(p->info);
        p=p->sig;
    }
}

int CmpXClave(const void *c1, const void *c2)
{
    int a = *(const int *)c1;
    int b = *(const int *)c2;

    return (a > b) - (a < b);
}
