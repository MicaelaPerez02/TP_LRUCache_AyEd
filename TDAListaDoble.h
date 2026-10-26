
#ifndef TDALISTADOBLE_H_INCLUDED
#define TDALISTADOBLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIN_DATOS -2
#define SIN_MEMORIA -1
#define EXITO 1

#define MINIMO(X,Y)( (X)<=(Y)? (X):(Y) )

typedef struct sNodo{
    void *info;
    size_t tamInfo;
    struct sNodo *ant;
    struct sNodo *sig;
} tNodo;

typedef tNodo *tListaDoble;

void crearListaDoble(tListaDoble *p);
void vaciarListaDoble(tListaDoble *p);
int esListaDobleVacia(const tListaDoble *p);
int esListaDobleLlena(const tListaDoble *p, size_t tam);
int insertarAlInicioListaDoble(tListaDoble *p, const void *d, size_t tam);
int insertarAlFinalListaDoble(tListaDoble *p, const void *d, size_t tam);
void mostrarDeIzqADer(const tListaDoble *p, void(*mostrar)(const void *));
void mostrarDeDerAIzq(const tListaDoble *p, void(*mostrar)(const void *));

int moverAlInicioListaDoble(tListaDoble *p, tNodo *nodo);
int eliminarNodoListaDoble(tListaDoble *p, tNodo *nodo);
int sacarUltimoListaDoble(tListaDoble *p, void *d, size_t tam);

#endif // TDALISTADOBLE_H_INCLUDED
