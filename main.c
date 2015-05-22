#include "header.h"     ///includo il file con tutte le librerie


/***PROGETTO FINALE PR1

    Progetto finale PR1: "Il progetto è relativo alla gestione di un ristorante
    con 15 tavoli e della gestione delle ordinazioni nonché della stampa degli scontrini."

    */

	 /***il programma ha inizio con la funzione main*/

int main()
{
    int scelta = -1;    ///variabile di selezione del menù

    while (1){  ///condizione necessaria per eseguire il loop del menù principale finchè non sia dato un comando di chiusura

    ///stampa del menù principale del programma
    scelta = menu_principale();

    switch (scelta) {
        case 1: gestione_menu();    ///visualizza le opzioni di gestione dell'archivio dei piatti
            break;
        case 2: gestione_cassa();   ///gestisce gli ordini e stampa gli scontri
            break;
        /*case 4:
                easteregg();    ///happy easter!
            break;*/
        default: return 0;  ///qualsiasi altra opzione chiude il programma
            break;
            }

    }   ///fine del blocco while

    return 0;
}
