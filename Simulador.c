#include "Simulador.h"

void crearCache(tSimulador *sim, unsigned capacidad)
{
    if(sim->modo == CACHE_PARTE_1)
        crearLruCache(&sim->cache1, capacidad, CmpXClave);
    else if(sim->modo == CACHE_PARTE_2)
        crearLruCacheMejorada(&sim->cache2, capacidad, CmpXClave);
}

int buscarEnCache(tSimulador *sim, tPosteo *posteo)
{
    if(sim->modo == CACHE_PARTE_1)
        return obtenerLruCache(&sim->cache1, posteo, sizeof(tPosteo)) == EXITO;

    if(sim->modo == CACHE_PARTE_2)
        return obtenerLruCacheMejorada(&sim->cache2, posteo, sizeof(tPosteo)) == EXITO;

    return 0;
}

void guardarEnCache(tSimulador *sim, tPosteo *posteo)
{
    if(sim->modo == CACHE_PARTE_1)
        agregarLruCache(&sim->cache1, posteo, sizeof(tPosteo));
    else if(sim->modo == CACHE_PARTE_2)
        agregarLruCacheMejorada(&sim->cache2, posteo, sizeof(tPosteo));
}

unsigned obtenerAltura(tSimulador *sim)
{
    if(sim->modo == CACHE_PARTE_2)
        return alturaLruCacheMejorada(&sim->cache2);

    return 0;
}

void vaciarCache(tSimulador *sim)
{
    if(sim->modo == CACHE_PARTE_1)
        vaciarLruCache(&sim->cache1);
    else if(sim->modo == CACHE_PARTE_2)
        vaciarLruCacheMejorada(&sim->cache2);
}

int leerPosteo(FILE *pfPosteos, int id, tPosteo *posteo)
{
    // Esto se puede hacer por el acceso directo (el id coincide con el nro de registro)
    fseek(pfPosteos, (long)id * (long)sizeof(tPosteo), SEEK_SET);

    return fread(posteo, sizeof(tPosteo), 1, pfPosteos) == 1;
}


int simularUnaVez(const char *archivoFeeds, int modo, unsigned capacidad, tResultado *res)
{
    tUsuarioFeed usuarioFeed;
    tPosteo posteo;
    tSimulador sim;
    const int *idPosteo;
    FILE *pfPosteos = fopen(ARCH_POSTEOS, "rb");
    FILE *pfFeeds = fopen(archivoFeeds, "rb");

    if(!pfPosteos || !pfFeeds)
    {
        if(pfPosteos)
            fclose(pfPosteos);

        if(pfFeeds)
            fclose(pfFeeds);

        return SIM_ERROR;
    }

    // Configuracion para desactivar el buffer y que cada fseek + fread vaya a buscar el posteo al archivo, y no a una
    // copia que FILE ya tenia en memoria
    setvbuf(pfPosteos, NULL, _IONBF, 0);

    sim.modo = modo;
    crearCache(&sim, capacidad);

    res->aciertos = 0;
    res->fallos = 0;
    res->lecturas = 0;

    while(fread(&usuarioFeed, sizeof(tUsuarioFeed), 1, pfFeeds) == 1)
    {
        for(idPosteo = usuarioFeed.feed; idPosteo < usuarioFeed.feed + POSTEOS_POR_FEED; idPosteo++)
        {
            posteo.id = *idPosteo;

            if(buscarEnCache(&sim, &posteo))
                res->aciertos++;
            else
            {
                res->fallos++;

                if(leerPosteo(pfPosteos, *idPosteo, &posteo))
                {
                    res->lecturas++;
                    guardarEnCache(&sim, &posteo);
                }
            }
        }
    }

    res->altura = obtenerAltura(&sim);

    vaciarCache(&sim);
    fclose(pfPosteos);
    fclose(pfFeeds);

    return SIM_OK;
}

// Funcion para medir el tiempo de la simulacion promediando
int simularVariasVeces(const char *archivoFeeds, int modo, unsigned capacidad, int repeticiones, tResultado *res)
{
    int repeticion;
    clock_t inicio = clock(); // Devuelve el tiempo de CPU utilizado por el programa

    for(repeticion = 0; repeticion < repeticiones; repeticion++)
    {
        if(simularUnaVez(archivoFeeds, modo, capacidad, res) == SIM_ERROR)
            return SIM_ERROR;
    }

    res->segundos = (double)(clock() - inicio) / CLOCKS_PER_SEC / repeticiones;

    return SIM_OK;
}

const char *nombreModo(int modo)
{
    if(modo == CACHE_PARTE_1)
        return "Parte 1";

    if(modo == CACHE_PARTE_2)
        return "Parte 2";

    return "Sin cache";
}

void mostrarSeparador()
{
    printf("+-----------+--------+----------+---------+----------+-----------+--------------+-------------+--------+-----------+\n");
}

void mostrarEncabezado()
{
    mostrarSeparador();
    printf("| Modo      | Cap.   | Aciertos | Fallos  | Lecturas | Total (s) | Usuario (ms) | Posteo (us) | Altura | P1-P2 (s) |\n");
    mostrarSeparador();
}

void mostrarFila(int modo, unsigned capacidad, const tResultado *res, int cantUsuarios, double diferencia)
{
    int cantPosteos = cantUsuarios * POSTEOS_POR_FEED;

    printf("| %-9s | ", nombreModo(modo));

    if(modo == SIN_CACHE)
        printf("%6s | %8s | %7s | ", "-", "-", "-");
    else
        printf("%6u | %8u | %7u | ", capacidad, res->aciertos, res->fallos);

    printf("%8u | %9.3f | %12.4f | %11.4f | ",
           res->lecturas,
           res->segundos,
           res->segundos / cantUsuarios * MS_POR_SEGUNDO,
           res->segundos / cantPosteos * US_POR_SEGUNDO);

    if(modo == CACHE_PARTE_2)
        printf("%6u | %9.3f |\n", res->altura, diferencia);
    else
        printf("%6s | %9s |\n", "-", "-");
}

void simularCaso(const char *titulo, const char *archivoFeeds, int cantUsuarios, const unsigned *capacidades, int cantCapacidades, int repeticiones)
{
    tResultado sinCache;
    tResultado parte1;
    tResultado parte2;
    const unsigned *capacidad;

    printf("\n=== %s: %d usuarios, %d posteos pedidos ===\n", titulo, cantUsuarios, cantUsuarios * POSTEOS_POR_FEED);

    // Cargo una vez el archivo
    simularUnaVez(archivoFeeds, SIN_CACHE, 0, &sinCache);

    if(simularVariasVeces(archivoFeeds, SIN_CACHE, 0, repeticiones, &sinCache) == SIM_ERROR)
    {
        printf("Error al abrir los archivos de %s\n", titulo);
        return;
    }

    mostrarEncabezado();
    mostrarFila(SIN_CACHE, 0, &sinCache, cantUsuarios, 0);
    mostrarSeparador();

    for(capacidad = capacidades; capacidad < capacidades + cantCapacidades; capacidad++)
    {
        if(simularVariasVeces(archivoFeeds, CACHE_PARTE_1, *capacidad, repeticiones, &parte1) == SIM_ERROR
           || simularVariasVeces(archivoFeeds, CACHE_PARTE_2, *capacidad, repeticiones, &parte2) == SIM_ERROR)
        {
            printf("Error al abrir los archivos de %s\n", titulo);
            return;
        }

        mostrarFila(CACHE_PARTE_1, *capacidad, &parte1, cantUsuarios, 0);
        mostrarFila(CACHE_PARTE_2, *capacidad, &parte2, cantUsuarios, parte1.segundos - parte2.segundos);
        mostrarSeparador();

        // Las dos caches son LRU: tienen que dar los mismos aciertos y fallos
        if(parte1.aciertos != parte2.aciertos || parte1.fallos != parte2.fallos)
            printf("ERROR: con capacidad %u la Parte 1 y la Parte 2 no coinciden\n", *capacidad);

    }
}

unsigned pedirSemilla()
{
    int semilla;

    printf("Semilla para generar los lotes (%d para usar la hora): ", SEMILLA_HORA);
    semilla = leerNumero();

    while(semilla < 0)
    {
        printf("Semilla invalida, ingresa un numero positivo (%d para usar la hora): ", SEMILLA_HORA);
        semilla = leerNumero();
    }

    if(semilla == SEMILLA_HORA)
        return (unsigned)time(NULL);

    return (unsigned)semilla;
}

int leerNumero()
{
    char linea[TAM_LINEA];
    int numero;

    if(!fgets(linea, TAM_LINEA, stdin))
        return 0;

    if(sscanf(linea, "%d", &numero) != 1)
        return NUMERO_INVALIDO;

    return numero;
}

void simularTodo(const unsigned *capacidades, int cantCapacidades)
{
    simularCaso("Concentrado", ARCH_CONCENTRADO, USUARIOS_LOTE,
                capacidades, cantCapacidades, REPETICIONES_LOTE);
    simularCaso("Disperso", ARCH_DISPERSO, USUARIOS_LOTE,
                capacidades, cantCapacidades, REPETICIONES_LOTE);
    simularCaso("Ordenado", ARCH_ORDENADO, USUARIOS_LOTE,
                capacidades, cantCapacidades, REPETICIONES_LOTE);
}

void modoEstatico()
{
    unsigned capacidades[] = {250, 500, 1000, 1500, 2000};

    simularTodo(capacidades, CANTIDAD(capacidades));
}

int pedirCapacidad(const char *texto)
{
    int capacidad;

    printf("\n%s (1 a %d, 0 para volver al menu): ", texto, MAX_CAPACIDAD);
    capacidad = leerNumero();

    while(capacidad < 0 || capacidad > MAX_CAPACIDAD)
    {
        printf("Capacidad invalida, ingresa un numero entre 1 y %d (0 para volver al menu): ", MAX_CAPACIDAD);
        capacidad = leerNumero();
    }

    return capacidad;
}

void modoDinamico()
{
    unsigned capacidades[CANT_CAPACIDADES_DINAMICO];
    int capacidad = pedirCapacidad("Capacidad de la cache");

    while(capacidad != 0)
    {
        *capacidades = (unsigned)capacidad;
        simularTodo(capacidades, CANT_CAPACIDADES_DINAMICO);

        capacidad = pedirCapacidad("Otra capacidad");
    }
}

int mostrarMenu()
{
    printf("\n1 - Modo estatico: Lotes con capacidades predefinidas\n");
    printf("2 - Modo dinamico: Se carga la capacidad deseada.\n");
    printf("0 - Salir\n\n");
    printf("Opcion: ");

    return leerNumero();
}
