#ifndef TDAINDICE_H_INCLUDED
#define TDAINDICE_H_INCLUDED

#include "TDAListaDoble.h"
#include "TDAArbol.h"

#ifndef NO_ENCONTRADO
#define NO_ENCONTRADO -3
#endif

typedef struct
{
    tArbolBinBusq arbol;
    Cmp cmpClaves;
} tIndice;

typedef struct
{
    const void *clave;
    tNodo *nodo;
    Cmp cmp;
} tEntradaIndice;

void crearIndice(tIndice *pi, Cmp cmpClaves);
void vaciarIndice(tIndice *pi);

int insertarEnIndice(tIndice *pi, tNodo *nodo);
tNodo *buscarEnIndice(const tIndice *pi, const void *clave);
tNodo *sacarDeIndice(tIndice *pi, const void *clave);
unsigned alturaIndice(tIndice *pi);

#endif // TDAINDICE_H_INCLUDED
