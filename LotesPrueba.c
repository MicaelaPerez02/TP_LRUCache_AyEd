#include "LotesPrueba.h"

int aleatorioHasta(int limite)
{
    int numero = (rand() % TOPE_RAND) * TOPE_RAND + rand() % TOPE_RAND;

    return numero % limite;
}

int estaEnVector(const int *vec, int cantidad, int id)
{
    int posicion;

    for(posicion = 0; posicion < cantidad; posicion++)
        if(vec[posicion] == id)
            return 1;

    return 0;
}

void llenarVectorDistinto(int *vec, int cantidad)
{
    int cargados = 0;
    int id;

    while(cargados < cantidad)
    {
        id = aleatorioHasta(CANT_POSTEOS);

        if(!estaEnVector(vec, cargados, id))
        {
            vec[cargados] = id;
            cargados++;
        }
    }
}

void llenarFeedConcentrado(int *feed, const int *populares)
{
    int cargados = 0;
    int id;

    while(cargados < POSTEOS_POR_FEED)
    {
        if(aleatorioHasta(PORCENTAJE_MAXIMO) < PORCENTAJE_POPULARES)
            id = populares[aleatorioHasta(CANT_POPULARES)];
        else
            id = aleatorioHasta(CANT_POSTEOS);

        if(!estaEnVector(feed, cargados, id))
        {
            feed[cargados] = id;
            cargados++;
        }
    }
}

/* Cada acceso del archivo tiene su propio tramo de ids. Como los tramos van
   en orden, los ids crecen en TODO el archivo, no solo dentro de cada feed. */
void llenarFeedOrdenado(int *feed, int indiceUsuario)
{
    int tramo = CANT_POSTEOS / (CANT_USUARIOS * POSTEOS_POR_FEED);
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
        posteo.id = numeroRegistro;     /* el id coincide con el numero de registro */
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

int crearArchivoFeeds(const char *nombreArchivo, int tipoLote)
{
    FILE *pf = fopen(nombreArchivo, "wb");
    tUsuarioFeed usuarioFeed;
    int populares[CANT_POPULARES];
    int indiceUsuario;

    if(!pf)
        return GEN_ERROR;

    llenarVectorDistinto(populares, CANT_POPULARES);

    for(indiceUsuario = 0; indiceUsuario < CANT_USUARIOS; indiceUsuario++)
    {
        sprintf(usuarioFeed.usuario, "usuario%d", indiceUsuario + 1);

        if(tipoLote == LOTE_CONCENTRADO)
            llenarFeedConcentrado(usuarioFeed.feed, populares);
        else if(tipoLote == LOTE_DISPERSO)
            llenarVectorDistinto(usuarioFeed.feed, POSTEOS_POR_FEED);
        else
            llenarFeedOrdenado(usuarioFeed.feed, indiceUsuario);

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
