#include "LotesPrueba.h"

int abrirArchivo(FILE **fp, const char *nombreArchivo, const char *modoApertura, int mostrarError)
{
    *fp=fopen(nombreArchivo, modoApertura);

    if(! *fp)
    {
        if(mostrarError)
        {
            printf("Ocurrio un error al abrir el archivo %s en modo %s. \n", nombreArchivo, modoApertura);
        }
        return ERROR_APERTURA_ARCHIVO;
    } else
        printf("Archivo %s en modo %s abierto correctamente. \n", nombreArchivo, modoApertura);

    return EXITO_APERTURA_ARCHIVO;
}

int crearArchivoPosteos(char *nombreArchivo)
{
    FILE *fpPosteos;

    tPosteo vecPosteos[]={
        {1, "¿Tu sistema va lento? La caché LRU acelera el procesamiento guardando los datos más accedidos. ¡Optimizá tu memoria!"},
        {2, "En nuestro TDA, el dato menos usado recientemente se descarta primero al llenarse la caché garantizando eficiencia pura."},
        {3, "Implementar una caché genérica en C requiere dominar punteros dobles y malloc. ¡Clave validar para evitar fugas!"},
        {4, "Combinamos listas doblemente enlazadas y árboles binarios índice para maximizar el rendimiento de las búsquedas."},
        {5, "Preparando la defensa del TP de Algoritmos. ¡Estructurar bien los datos marca la diferencia a la hora de aprobar!"},
    };

    if(abrirArchivo(&fpPosteos, "posteos.bin", "wb", MOSTRAR_ERROR_APERTURA) )
        return ERROR_APERTURA_ARCHIVO;

    if(fpPosteos)
    {
        fwrite(vecPosteos, sizeof(vecPosteos), 1, fpPosteos);
        fclose(fpPosteos);
        return EXITO_CREACION_ARCHIVO;
    }

    return ERROR_CREACION_ARCHIVO;
}

void mostrarArchivoPosteos(char *nombreArchivo)
{
    tPosteo post;
    FILE *fp;

    fp=fopen(nombreArchivo, "rb");
    if(!fp)
        return;

    while( fread(&post, sizeof(tPosteo), 1, fp) )
    {
        printf("ID: %d \t POST: %s \n", post.id, post.texto);
    }

    fclose(fp);
}

int crearArchivoUsuariosFeed(char *nombreArchivo)
{
    FILE *fpUsuariosFeed;

    tUsuarioFeed vecUsuarioFeed[]={
        {"Micaela Perez", {1,3,5} },
        {"Lionel Messi", {1,4} },
        {"Javier Milei", {2,3} }
    };

    if(abrirArchivo(&fpUsuariosFeed, "usuariofeed.bin", "wb", MOSTRAR_ERROR_APERTURA) )
        return ERROR_APERTURA_ARCHIVO;

    if(fpUsuariosFeed)
    {
        fwrite(vecUsuarioFeed, sizeof(vecUsuarioFeed), 1, fpUsuariosFeed);
        fclose(fpUsuariosFeed);
        return EXITO_CREACION_ARCHIVO;
    }

    return ERROR_CREACION_ARCHIVO;
}

void mostrarArchivoUsuarioFeed(char *nombreArchivo)
{
    tUsuarioFeed userPost;
    FILE *fp;
    int i;

    fp=fopen(nombreArchivo, "rb");
    if(!fp)
        return;

    while( fread(&userPost, sizeof(tUsuarioFeed), 1, fp) )
    {
        printf("USUARIO: %s \t", userPost.usuario);

        i=0;
        while(userPost.feed[i] != 0)
        {
            printf("\tPOSTEO ID: %d \n", userPost.feed[i]);
            i++;
        }
    }

    fclose(fp);
}

