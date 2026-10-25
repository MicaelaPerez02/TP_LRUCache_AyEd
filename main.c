#include "t_lru_cache.h"
#include "LotesPrueba.h"

int main()
{
    crearArchivoPosteos("posteos.bin");
    mostrarArchivoPosteos("posteos.bin");

    crearArchivoUsuariosFeed("usuariofeed.bin");
    mostrarArchivoUsuarioFeed("usuariofeed.bin");
    return 0;
}
