#include "t_lru_cache.h"

int CmpXClave(const void *c1, const void *c2)
{
    return *(int *)c1 - *(int *)c2;
}

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
    vaciarLista(&pc->lista);
    pc->capMax=0;
    pc->cmpClaves=NULL;
    pc->ce=0;
}

int agregar_lrucache(tCache *pc, void *d, size_t tam)
{
    tLista *p = &pc->lista;
    tNodo *elim;
    int encontrado=0;

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
        } else
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
    tNodo *elim;
    tLista *p = &pc->lista;

    if(!pc || !pc->lista)
        return SIN_DATOS;

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
