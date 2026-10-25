#include "t_lru_cache.h"
#include "LotesPrueba.h"

int main()
{
    /*crearArchivoPosteos("posteos.bin");
    mostrarArchivoPosteos("posteos.bin");

    crearArchivoUsuariosFeed("usuariofeed.bin");
    mostrarArchivoUsuarioFeed("usuariofeed.bin");*/

    tCache pc;
    int x=1, x2=5, x3=10;
    //int buscado1=5;
    int buscado2=4;

    crear_lrucache(&pc, 100, CmpXClave);

    agregar_lrucache(&pc, &x, sizeof(x));
    agregar_lrucache(&pc, &x2, sizeof(x2));
    agregar_lrucache(&pc, &x3, sizeof(x3));

    recorrer_lrucache(&pc, mostrar);
    printf("\n");

    obtener_lrucache(&pc, &buscado2, sizeof(buscado2));
    recorrer_lrucache(&pc, mostrar);

    vaciar_lrucache(&pc);
    return 0;
}
