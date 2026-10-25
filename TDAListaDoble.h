
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

typedef tNodo *tLista;

void crearListaDoble(tLista *p);
void vaciarListaDoble(tLista *p);
int esListaDobleVacia(const tLista *p);
int esListaDobleLlena(const tLista *p, size_t tam);
int insertarAlInicio(tLista *p, const void *d, size_t tam);
int insertarAlFinal(tLista *p, const void *d, size_t tam);
void mostrarDeIzqADer(const tLista *p, void(*mostrar)(const void *));
void mostrarDeDerAIzq(const tLista *p, void(*mostrar)(const void *));

int moverAlInicioListaDoble(tLista *p, tNodo *nodo);
int eliminarNodoListaDoble(tLista *p, tNodo *nodo);
int sacarUltimoListaDoble(tLista *p, void *d, size_t tam);

#endif // TDALISTADOBLE_H_INCLUDED
