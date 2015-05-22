/// librerie incluse nel progetto
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     ///libreria necessaria per le funzioni delle stringhe, come la ricerca e il confronto
#include <time.h>       ///necessaria per stampare data e ora dello scontrino, inutile quanto elegante

/// costanti definite
#define NP 50  ///costante per le lettere del nome del piatto
#define NI 20   ///costante del vettore stringa del nome degli ingredienti
#define ING 3   ///numero di ingredienti totali
#define NT 15   ///numero dei tavoli disponibili


    /***definizione di strutture all'interno delle funzioni*/

    /***Questa struttura contiene tutte le informazioni relative
        alla composizione dei piatti*/

    typedef struct {
        int ID;     ///ID del piatto
        char piatto[NP];    ///nome del piatto
        char ingredienti[ING][NI];    ///vettore di tre stringhe contenente gli ingredienti del piatto
        enum Tipologia {Antipasto, Primo, Secondo, Contorno, Dessert} tipo;     ///specifica la tipologia del piatto
        float prezzo;   ///costo di ogni piatto
        int porzioni;   ///variabile definita solo durante la stampa degli scontrini
    } Piatto;

    /***Questa struttura contiene tutte le informazioni relative
        alla struttura deglle ordinazioni*/

    typedef struct{
        int tavolo;     ///numero del tavolo
        Piatto *ordini;     ///puntatore a struttura Piatto che verrà allocata dinamicamente
        float totale;   ///il conto totale viene memorizzato in una variabile float
        short effettuato;   ///controlla in fase di modifica se l'ordine è stato effettuato. short perchè detesto sprecare memoria
        int portate;    ///controlla il totale delle protate inserite, utile per evitare altre funzioni imprecise inserite in precedenza
    } Ordine;

    /***struttura utlizzata per la gestione delle scorte*/

    typedef struct {
        char ingredienti[NI];   ///vettore contenente il nome dell'ingrediente
        int utilizzo;       ///contatore di utilizzo dell'ingrediente
    } Scorte_ingredienti;



    /***prototipi di funzione*/

void gestione_menu();
void gestione_cassa();
int menu_principale();
void pulizia_schermo();
char seisicuro();
void crea_archivio();
int n_piatti_menu();
Piatto* vettore_elenco();
int menu_principale();
void gestione_scorte();
void aggiungi_piatto();
void stampa_menu();
void modifica_piatto();
void elimina_piatto();
void stampa_menu_input();
void cerca_piatto();
void gestione_menu();
void aggiorna_scorte();
void stampa_scontrino();
void modifica_ordine();
void gestione_ordinazioni();
void gestione_cassa();
void easteregg();
