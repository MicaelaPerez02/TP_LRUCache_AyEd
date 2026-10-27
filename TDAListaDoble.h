#ifndef TDALISTADOBLE_H_INCLUDED
#define TDALISTADOBLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_DATOS -2
#define SIN_MEMORIA -1
#define EXITO 1

#ifndef MINIMO
#define MINIMO(X,Y)( (X)<=(Y)? (X):(Y) )
#endif

typedef struct sNodo
{
    void *info;
    size_t tamInfo;
    struct sNodo *ant;
    struct sNodo *sig;
} tNodoDoble;

typedef struct
{
    tNodoDoble *pri;
    tNodoDoble *ult;
} tListaDoble;

void crearListaDoble(tListaDoble *p);
int esListaDobleVacia(const tListaDoble *p);
int insertarAlInicioListaDoble(tListaDoble *p, const void *d, size_t tam);
int moverAlInicioListaDoble(tListaDoble *p, tNodoDoble *nodo);
int eliminarNodoListaDoble(tListaDoble *p, tNodoDoble *nodo);
int sacarUltimoListaDoble(tListaDoble *p, void *d, size_t tam);
void vaciarListaDoble(tListaDoble *p);

#endif // TDALISTADOBLE_H_INCLUDED
