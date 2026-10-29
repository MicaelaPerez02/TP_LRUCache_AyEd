#ifndef TDALISTADOBLE_H_INCLUDED
#define TDALISTADOBLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 1
#define SIN_MEMORIA -1
#define SIN_DATOS -2
#ifndef PUNTERO_INVALIDO
#define PUNTERO_INVALIDO -4
#endif

#ifndef MINIMO
#define MINIMO(X,Y)( (X)<=(Y)? (X):(Y) )
#endif

typedef struct sNodoDoble
{
    void *info;
    size_t tamInfo;
    struct sNodoDoble *ant;
    struct sNodoDoble *sig;
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
