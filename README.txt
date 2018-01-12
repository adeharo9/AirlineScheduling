AIRLINE SCHEDULING

Programa per a resoldre el problema d'airline scheduling, seleccionant el mínim número de pilots que poden dur a terme un seguit de rutes entre ciutats donat un seguit de restriccions en el seu fluxe de treball.

COM COMPILAR?

Des de la carpeta base del projecte, executar la següent comanda des de la línia de comandes:

$ make

COM EXECUTAR?

Des de la carpeta base del projecte, executar la següent comanda des de la línia de comandes:

$ ./AirlineScheduling

A continuació apareixerà una descripció de les opcions per tal de configurar apropiadament una sessió d'execució del programa.

$ ./AirlineScheduling [-12hL] [-a algoritme] [-AM]

OPCIONS

    · -1: Executa els algorismes seleccionats amb la versió 1 del problema.
    · -2: Executa els algorismes seleccionats amb la versió 2 del problema.
    · -h, --help: Mostra el missatge d'ajuda.
    · -L, --ALL: Executa els algorismes seleccionats amb totes les versions del problema.

    · -a, --algorithm ALG: Executa el programe amb l'algorisme identificat pel seu descriptor ALG. Els descriptors disponibles són:
        · DI: algorisme de bloqueig de fluxe de Dinic.
        · EK: algorisme d'Edmonds-Karp.
        · FF: mètode de Ford-Fulkerson amb DFS.
        · ALL: Executa tots els algorismes anteriorment anomenats de forma seqüencial.

    · -A, --auto: Executa l'entrada de dades automàtica.
    · -M, --manual: Executa l'entrada de dades manual.
