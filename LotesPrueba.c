#include "LotesPrueba.h"

int aleatorioHasta(int limite)
{
    // Usamos dos rand porque tenemos 50mil registros, el rand de windows solo llega a 32767
    int numero = (rand() % TOPE_RAND) * TOPE_RAND + rand() % TOPE_RAND;

    if(limite <= 0)
        return 0;

    return numero % limite;
}

int estaEnVector(const int *vec, int cantidad, int id)
{
    const int *fin = vec + cantidad;

    while(vec < fin)
    {
        if(*vec == id)
            return 1;

        vec++;
    }

    return 0;
}

void llenarVectorDistinto(int *vec, int cantidad)
{
    int *act = vec;
    int cargados = 0;
    int id;

    while(cargados < cantidad)
    {
        id = aleatorioHasta(CANT_POSTEOS);

        if(!estaEnVector(vec, cargados, id)) // Validamos que sean diferentes
        {
            *act = id;
            act++;
            cargados++;
        }
    }
}

void llenarFeedConcentrado(int *feed, const int *populares, int cantPopulares)
{
    int *act = feed;
    int cargados = 0;
    int id;

    while(cargados < POSTEOS_POR_FEED)
    {
        if(aleatorioHasta(PORCENTAJE_MAXIMO) < PORCENTAJE_POPULARES) // Si es menor que 90
            id = *(populares + aleatorioHasta(cantPopulares)); // Popular al azar
        else
            id = aleatorioHasta(CANT_POSTEOS); // Sino cualquiera

        if(!estaEnVector(feed, cargados, id))
        {
            *act = id;
            act++;
            cargados++;
        }
    }
}

/* Cada acceso del archivo tiene su propio tramo de ids. Como los tramos van
   en orden, los ids crecen en TODO el archivo, no solo dentro de cada feed. */
void llenarFeedOrdenado(int *feed, int indiceUsuario, int cantUsuarios)
{
    int tramo = CANT_POSTEOS / (cantUsuarios * POSTEOS_POR_FEED);
    int posicion;
    int numeroAcceso;

    for(posicion = 0; posicion < POSTEOS_POR_FEED; posicion++)
    {
        numeroAcceso = indiceUsuario * POSTEOS_POR_FEED + posicion;
        feed[posicion] = numeroAcceso * tramo + aleatorioHasta(tramo);
    }
}

int crearArchivoPosteos(const char *nombreArchivo)
{
    FILE *pf = fopen(nombreArchivo, "wb");
    tPosteo posteo;
    int numeroRegistro;

    if(!pf)
        return GEN_ERROR;

    for(numeroRegistro = 0; numeroRegistro < CANT_POSTEOS; numeroRegistro++)
    {
        posteo.id = numeroRegistro;
        sprintf(posteo.texto, "Posteo numero %d: texto de prueba para la simulacion", numeroRegistro);

        if(fwrite(&posteo, sizeof(tPosteo), 1, pf) != 1)
        {
            fclose(pf);
            return GEN_ERROR;
        }
    }

    fclose(pf);
    return GEN_OK;
}

int crearArchivoFeeds(const char *nombreArchivo, int tipoLote, int cantUsuarios, int cantPopulares)
{
    FILE *pf;
    tUsuarioFeed usuarioFeed;
    int populares[MAX_POPULARES];
    int indiceUsuario;

    if(cantUsuarios <= 0)
        return GEN_ERROR;

    if(cantPopulares > MAX_POPULARES)
        return GEN_ERROR;

    if(tipoLote == LOTE_CONCENTRADO && cantPopulares <= 0)
        return GEN_ERROR;

    // en el ordenado cada acceso necesita al menos un id propio
    if(tipoLote == LOTE_ORDENADO && cantUsuarios * POSTEOS_POR_FEED > CANT_POSTEOS)
        return GEN_ERROR;

    pf = fopen(nombreArchivo, "wb");

    if(!pf)
        return GEN_ERROR;

    llenarVectorDistinto(populares, cantPopulares);

    for(indiceUsuario = 0; indiceUsuario < cantUsuarios; indiceUsuario++)
    {
        sprintf(usuarioFeed.usuario, "Usuario numero %d de la red social Tweener", indiceUsuario + 1);

        if(tipoLote == LOTE_CONCENTRADO)
            llenarFeedConcentrado(usuarioFeed.feed, populares, cantPopulares);
        else if(tipoLote == LOTE_DISPERSO)
            llenarVectorDistinto(usuarioFeed.feed, POSTEOS_POR_FEED);
        else
            llenarFeedOrdenado(usuarioFeed.feed, indiceUsuario, cantUsuarios);

        if(fwrite(&usuarioFeed, sizeof(tUsuarioFeed), 1, pf) != 1)
        {
            fclose(pf);
            return GEN_ERROR;
        }
    }

    fclose(pf);
    return GEN_OK;
}

void mostrarArchivoPosteos(const char *nombreArchivo, int limite)
{
    FILE *pf = fopen(nombreArchivo, "rb");
    tPosteo posteo;
    int mostrados = 0;

    if(!pf)
    {
        printf("No se pudo abrir %s\n", nombreArchivo);
        return;
    }

    while(mostrados < limite && fread(&posteo, sizeof(tPosteo), 1, pf) == 1)
    {
        printf("%d | %s\n", posteo.id, posteo.texto);
        mostrados++;
    }

    fclose(pf);
}

void mostrarArchivoFeeds(const char *nombreArchivo, int limite)
{
    FILE *pf = fopen(nombreArchivo, "rb");
    tUsuarioFeed usuarioFeed;
    int mostrados = 0;
    int posicion;

    if(!pf)
    {
        printf("No se pudo abrir %s\n", nombreArchivo);
        return;
    }

    while(mostrados < limite && fread(&usuarioFeed, sizeof(tUsuarioFeed), 1, pf) == 1)
    {
        printf("%s |", usuarioFeed.usuario);

        for(posicion = 0; posicion < POSTEOS_POR_FEED; posicion++)
            printf(" %d", usuarioFeed.feed[posicion]);

        printf("\n");
        mostrados++;
    }

    fclose(pf);
}
