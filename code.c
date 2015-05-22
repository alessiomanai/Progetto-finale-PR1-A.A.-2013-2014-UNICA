#include "header.h"

    /***in questa funzione sono contenute le funzioni di pulizia dello schermo
        a seconda del sistema operativo*/

void pulizia_schermo(){     ///funziona

    #ifdef _WIN32   ///nel caso sia un sistema operativo Microsoft compila queste porzioni di codice
    system("cls");
    #endif

    #ifdef linux    ///nel caso il sistema sia una distro Linux compila queste porzioni di codice
    system("clear");
    #endif

}

    /***Questa funzione crea un archivio da zero, utile per riscrivere l'intero menù da capo*/

void crea_archivio(){   ///funziona

    FILE *archivio = NULL;  ///puntatore all'archivio
    char conferma;  ///variabile di conferma

    printf("Sei sicuro? y/n ");     ///chiede conferma dell'operazione
    scanf("%c", &conferma);
    getchar();      ///commento ora per non commentare più: le getchar sono state utilizzare per evitare di saltare i controlli

    if (!('y' == conferma)){     ///chiede la conferma dell'operazione
        return;
    }

    ///nel caso la scrittura fallisca, stampa un messaggio di errore e permette di proseguire l'esecuzione del programma
    ///tramite l'inserimento di un qualsiasi numero all'interno della variabile creata

    if ((archivio = fopen("archivio.dat", "wb")) == NULL) {
        printf("Errore nella creazione del file\nPremi invio per continuare\n");
        getchar();
        #ifdef linux
        getchar();
        #endif // linux
        }
    else {
        printf("Archivio creato\nPremi invio per continuare\n");    ///in caso affermativo stampa (tecnicamente) un messaggio di conferma
        getchar();
    }
    fclose(archivio);   ///chiude il file appena creato

    return;

}

    /***la funzione n_piatti_menu conta il numero dei piatti presenti in archivio e
        restituisce il valore calcolato*/

int n_piatti_menu(){    ///funziona


    FILE *archivio = NULL;      ///puntatore al file archivio.dat
    int n_piatti_totali;    ///indice dei piatti totali presenti nel menù, inizializzato a 0 prima che inizi il conteggio
    Piatto lettura;     ///puntatore a struttura nel quale verrà allocato dinamicamente il menù dei piatti
    char scelta;    ///variabile per la creazione del



    if ((archivio = fopen("archivio.dat", "rb")) == NULL){   ///nel caso l'apertura del programma non vada a buon fine
        getchar();
        printf("Errore nell' apertura del file\nIl file potrebbe non esistere per effettuare i dovuti controlli\n"
                "Creare un nuovo archivio dei piatti? (Questo cancellera' il precedente) y/n: ");     ///stampa un messaggio di errore
        scanf("%c", &scelta);
        getchar();  ///evito l'uscita dalla funzione e dal programma

    /***in origine usciva direttamente dal programma, dopo alcune prove ho deciso di non far chiudere il programma
        e di lasciare all'utente la possibilità di crearlo nel caso sia la prima volta che il programma si avvii*/

        if (scelta == 'y'){
                crea_archivio();    ///in caso affermativo crea l'archivio
                return 0;   ///zero, in quanto il nuovo archivio creato sarà ovviamente vuoto
            }
        else {
                printf("Procedura annullata. \n");
                return -1;   ///-1 come flag di inesistenza menù

            }
        }
    else {      ///in caso contrario prosegue l'esecuzione del programma

        n_piatti_totali = 0;    ///inizializzo la variabile per il conteggio dei piatti presenti nel menù

        while (!feof(archivio)){    ///finchè il file non è stato completamente letto
        ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
        ///per evitare ciò è stato inserito un controllo if
            if (fread(&lettura, sizeof(Piatto), 1, archivio)){  ///leggi l'archivio e memorizza in una struttura di stampa apposita
        ///infine visualizza su schermo il contenuto
            n_piatti_totali++;      ///conta i piatti stampati a schermo
            }
        }
    }

    fclose(archivio);   ///chiusura di sicurezza

    return n_piatti_totali;     ///chiude la funzione e restituisce il numero dei piatti totali

}

    /***questa funzione permette di caricare l'archivio dei piatti e memorizzarla in
        un vettore dinamico di struttura. Prende in ingresso il numero dei piatti totali
        prenseti nel menù e restituisce un puntatore a struttura Piatto */

Piatto* vettore_elenco(int n_piatti_totali){    ///funziona

    int i; ///indici dei for
    FILE *archivio = NULL;      ///puntatore al file archivio.dat
    Piatto *elenco = NULL;     ///puntatore a struttura nel quale verrà allocato dinamicamente il menù dei piatti

    if ((archivio = fopen("archivio.dat", "rb")) == NULL) {     ///apro il file in lettura
        printf("Errore nell' apertura del file. Premi un tasto per continuare\n");
        getchar();
        return elenco;   ///in caso di errore esce
        }
    else {

        rewind(archivio);   ///faccio tornare per aumentare l'efficienza il puntatore del file all'inizio dell'archivio

        /***alloco dinamicamente una struttura che conterrà l'intero elenco dei piatti
            e i loro dettagli */

        elenco = (Piatto*) malloc(sizeof(Piatto)*n_piatti_totali);

        ///memorizzo i piatti dell'elenco nella struttura creata in precedenza

        while (!feof(archivio)){    ///finchè il file non è stato completamente letto
            ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
            ///per evitare ciò è stato inserito un controllo if
            for (i=0; i<n_piatti_totali; i++){
                if (fread(&elenco[i], sizeof(Piatto), 1, archivio)){  ///leggi l'archivio e memorizza in una struttura per permettere la ricerca
                    //DEBUG printf("%s\n", elenco[i].piatto);
                }
            }   ///fine stampa su schermo
        }   ///fine lettura del database

    }   ///fine condizione else

        fclose(archivio);   ///una volta terminata l'operazione chiude l'archivio

    return elenco;  ///chiude la funzione e restituisce il risultato ottenuto
}


    /***funzione che stampa il menù principale. Restituisce al main
        la variabile scelta per accedere ai vari menù*/

int menu_principale(){      ///funziona

    int scelta = -1;    ///variabile di scelta delle opzioni

    pulizia_schermo();

#ifdef linux
    printf("\t***** Progetto finale PR1 *****\n"
    "\nIl progetto è relativo alla gestione di un ristorante \n"
    "con %d tavoli e della gestione delle\n"
    "ordinazioni nonché della stampa degli scontrini.\n\n"
    "Puoi scegliere tra: \n"
    "\t1) Gestire l'archivio dei piatti\n"
    "\t2) Gestire le ordinazioni e la cassa\n\n"
    "Premi CTRL + C o un'altro tasto per uscire\nScelta: ", NT);
#endif

    /***Windows usa il set di caratteri WIN-1252 (detto anche CP-1252).
        La console del prompt dei comandi usa invece
        il set di caratteri CP-437 (anche chiamato OEM o IBM-PC),
        perciò non legge le lettere accentate (fonte: hwupgrade.it).
        Per ovviare a questo problema di stampa ho utilizzato
        la compilazione condizionale per le due tipologie di sistemi*/

#ifdef _WIN32
    printf("\t***** Progetto finale PR1 *****\n"
    "\nIl progetto e' relativo alla gestione di un ristorante \n"
    "con %d tavoli e della gestione delle\n"
    "ordinazioni nonche' della stampa degli scontrini.\n\n"
    "Puoi scegliere tra: \n"
    "\t1) Gestire l'archivio dei piatti\n"
    "\t2) Gestire le ordinazioni e la cassa\n\n"
    "Premi CTRL + C o un'altro tasto per uscire\nScelta: ", NT);
#endif

    scanf("%d", &scelta);   ///prende in ingresso la selezione

    fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input

    return scelta;      ///chiude la funzione e restituisce la scelta effettuata
}





    /************************************funzioni di gestione dell'archivio*******************************************/

    /***Funzionalità avanzate
        Per ogni piatto inserito verrà aggiunto, nel caso non sia presente, un nuovo ingrediente
    */

void gestione_scorte(Piatto pietanza){  ///funziona

    FILE *scorte = NULL;    ///puntatore al file contenente le scorte
    int i, j; ///indici dei for
    int ingredienti_totali;     ///variabile di conteggio delle
    Scorte_ingredienti *elenco_scorte;  ///vettore dinamico contenente gli ingredienti già presenti
    Scorte_ingredienti scrittura;   ///struttura di appoggio che permette il salvataggio di nuovi ingredienti nel file
    int presente;   ///variabile che controlla se è presente l'ingrediente all'interno dell'archivio

    if ((scorte = fopen("scorte.dat", "ab+")) == NULL) {    ///apro o creo il file
        printf("Errore nella gestione delle scorte di ingredienti. Premi un tasto per continuare\n");    ///se fallise esce dalla funzione
        getchar();
        return;
        }
    else {   ///nel caso il file venga aperto scrive il piatto inserito in un numero di byte pari a Piatto

        ingredienti_totali = 0;     ///inizializzo a zero gli ingredienti totali

        /***inizio conteggio dei piatti totali*/

        while (!feof(scorte)){    ///finchè il file non è stato completamente letto
        ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
        ///per evitare ciò è stato inserito un controllo if
            if (fread(&scrittura, sizeof(Scorte_ingredienti), 1, scorte)){  ///leggi l'archivio e memorizza in una struttura di stampa apposita
        ///infine visualizza su schermo il contenuto
            ingredienti_totali++;      ///conta i piatti stampati a schermo
            }
        }

        /***nel caso il file non contenesse ingredienti scrivo direttamente le informazioni sul
            file, altrimenti controllo se sono già presenti gli stessi ingredienti*/

        if (ingredienti_totali != 0) {

            rewind(scorte); ///faccio tornare il puntatore all'inizio del file

            ///creo un vettore contenente il totale degli ingredienti

            elenco_scorte = malloc(sizeof(Scorte_ingredienti)*ingredienti_totali);

            ///memorizzo i piatti dell'elenco nella struttura creata in precedenza

            while (!feof(scorte)){    ///finchè il file non è stato completamente letto
                ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
                ///per evitare ciò è stato inserito un controllo if
                for (i=0; i<ingredienti_totali; i++){
                    if (fread(&elenco_scorte[i], sizeof(Scorte_ingredienti), 1, scorte)){
                    }
                }   ///fine stampa su schermo
            }   ///fine lettura del database

        /***controllo la presenza di ingredienti simili: se non è presente in lista un ingrediente lo aggiunge
            altrimenti non scrive nulla*/


            for (i=0; i<ING; i++){  ///per ogni ingrediente in messo

                presente = 0;   ///inizializzo il contatore a zero

                for (j=0; j<ingredienti_totali; j++){   ///scorro la lista
                        //printf("DEBUG\n");
                    if ( strcmp( elenco_scorte[j].ingredienti, pietanza.ingredienti[i]) != 0 ){
                          //  printf("DEBUG1\n");
                        presente++;  ///nel caso l'ingrediente non risulti in lista, incremento di uno
                    }
                }   ///fine della condizione di avvenuta scrittura

                if (!(presente < ingredienti_totali)){  ///se le mancanze in lista dovessero risultare diversamente
                    ///minori rispetto al totale degli ingredienti, copia l'ingrediente scansionato, altrimenti passa al successivo
                    strcpy(scrittura.ingredienti, pietanza.ingredienti[i]);
                    scrittura.utilizzo = 0;   ///inizializza l'utilizzo degli ingredienti a zero

                    fwrite(&scrittura, sizeof(Scorte_ingredienti), 1, scorte);
                }

            }   ///fine ciclo for con i
        }   ///fine condizione ingredienti != 0

        else {  ///se il file degli ingredienti è vuoto scrive senza eseguire controlli

            elenco_scorte = malloc(sizeof(Scorte_ingredienti)*ING);

            for (i=0; i<ING; i++){
                    strcpy(elenco_scorte[i].ingredienti, pietanza.ingredienti[i]);
                    elenco_scorte[i].utilizzo = 0;   ///inizializza l'utilizzo degli ingredienti a zero

                    fwrite(&elenco_scorte[i], sizeof(Scorte_ingredienti), 1, scorte);
                }
            }

    }   ///fine condizione else

    free(elenco_scorte);   ///libero la memoria

    fclose(scorte);     ///chiudo il file contenente le scorte

    return;

}


    /***tramite questa funzione è possibile aggiungere un piatto all'interno del menù*/

void aggiungi_piatto(){     ///funziona

    pulizia_schermo();

    int tipo = 0;   ///variabile per la compilazione del modulo
    Piatto pietanza;    ///struttura a piatto
    int i;  ///variabile per la scansione del vettore
    FILE *archivio = NULL;  ///puntatore all'archivio
    //int variabile = 0;  ///variabile di appoggio per proseguire l'esecuzione del programma e permettere la visualizzazione del messaggio
    Piatto* elenco;     ///puntatore dinamico alla struttura piatto, gestisce l'elenco totale dei piatti del menù
    int numero;     ///variabile che contiene
    int j;  ///indice del for di controllo del menù

    /***stampo un messaggio a schermo compatibile a seconda del sistema operativo in uso*/

#ifdef linux
    printf("\tBenvenuto nel menù di aggiunta dei piatti\n\n"
        "Da questo modulo puoi aggiungere dei piatti nel database \n"
        "specificando la tipologia (es: primo, secondo, contorno),\nil nome, tre"
        " ingredienti che lo compongono e il prezzo.\n"
        "Per cominciare, specifica la tipologia del piatto tra: "
        "\n\t0) Antipasto\n\t1) Primo\n\t2) Secondo\n\t3) Contorno\n\t4) Dessert\n"
        );
#endif
#ifdef _WIN32
    printf("\tBenvenuto nel menu' di aggiunta dei piatti\n\n"
        "Da questo modulo puoi aggiungere dei piatti nel database \n"
        "specificando la tipologia (es: primo, secondo, contorno),\nil nome, tre"
        " ingredienti che lo compongono e il prezzo.\n"
        "Per cominciare, specifica la tipologia del piatto tra: "
        "\n\t0) Antipasto\n\t1) Primo\n\t2) Secondo\n\t3) Contorno\n\t4) Dessert\n");
#endif


    do {   ///controllo sulla scelta del tipo

        printf("Tipologia: ");
        scanf("%d", &tipo);     ///variabile di scelta della tipologia del piatto
        fflush(stdin);  ///evito errori di input

    } while (tipo < 0 || tipo > 4);

#ifdef linux    ///su linux saltava il campo
    getchar();  ///controllo per evitare che salti il campo del nome del piatto
#endif // linux

    printf("Inserisci il nome del piatto\n");
    scanf("%49[^\n]s", pietanza.piatto);    ///controllo per permettere una certa lunghezza del nome e l'input degli spazi fino alla conferma tramite invio

    numero = n_piatti_menu();   ///la funzione conta i piatti totali presenti nel menù e scrive il numero nella variabile

    /***la funzione prende in ingresso il numero dei piatti presenti e scarica l'intero menù
        dal file archivio sul puntatore elenco */

    if (numero == -1){   ///se non esiste un elenco esce dalla funzione
        printf("Premi invio per continuare");
        getchar();
        return;
    }

    if (numero != 0){   ///controllo per evitare che in caso di file vuoto dia errore

        elenco = vettore_elenco(numero);    ///carica l'elenco dei piatti

        /***controllo del menù: nel caso sia presente in elenco un piatto con lo stesso nome
            stampa a schermo un messaggio di errore ed esce dalla funzione*/

        for (j=0; j<numero; j++){   ///utilizzo un for per scorrere l'intero menù

            if (strcmp(pietanza.piatto, elenco[j].piatto) == 0){    ///nel caso trovi un piatto con lo stesso nome
                    printf("\nErrore, piatto gia' presente in elenco\nPremi invio per continuare. ");
                    getchar();
                    getchar();   ///riutilizzo la variabile dei piatti totali per stampare il messaggio precedente
                    return;     ///torna al menù di gestione dei piatti
                }
            }
        }

    getchar();  ///evita che la funzione salti l'input

    ///prosegue la compilazione delle caratteristiche del piatto aggiungendone gli ingredienti

    printf("Inserisci i %d ingredienti che lo compongono\n", ING);
    for (i=0; i<ING; i++){    ///ad ogni aggiunta di ingrediente passa alla scrittura di quello successivo
        printf("%d) ", i+1);     ///visualizza il numero del piatto
        scanf("%[^\n]19s", (char*) &pietanza.ingredienti[i][0]);     ///conversione esplicita a puntatore a carattere per evitare il warning in compilazione
        getchar();
    }

    do {    ///controllo sul prezzo, non può essere minore di zero
        printf("E il prezzo\n");    ///definisce il prezzo del piatto
        scanf("%f", &pietanza.prezzo);
        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input

    } while (pietanza.prezzo < 0);


    ///a seconda della tipologia del piatto assegna il tipo di enumerazione

    switch (tipo) {
        case Antipasto:     ///antipasti
            pietanza.tipo = 0;
                break;
        case Primo:     ///primi
            pietanza.tipo = 1;
                break;
        case Secondo:     ///secondi
            pietanza.tipo = 2;
                break;
        case Contorno:     ///contorni
            pietanza.tipo = 3;
                break;
        case Dessert:   ///desserts
            pietanza.tipo = 4;
                break;
        }


    ///algoritmo per l'assegnazione dell'ID del piatto, banale ma efficace
    pietanza.ID = (pietanza.tipo*100) + strlen(pietanza.piatto) + pietanza.prezzo;

    ///controllo per evitare che i piatti abbiano casualmente lo stesso ID
    if (numero != 0){
        for(i=0; i<numero; i++){
            if (pietanza.ID == elenco[i].ID){
                pietanza.ID++;
                i=0;    ///nel caso un ID sia uguale ad un altro, lo incrementa di uno e riesegue il controllo
            }
        }
    }

    /***scrittura del nuovo piatto all'interno dell'archivio: apre il file in modalità
        append binaria e accoda il nuovo piatto nell'elenco*/

    if ((archivio = fopen("archivio.dat", "ab+")) == NULL) {
        printf("Errore nella scrittura del file\n");
        printf("\nPremi invio per continuare\n");
        getchar();
        return;
        }
    else    ///nel caso il file venga aperto scrive il piatto inserito in un numero di byte pari a Piatto
        fwrite(&pietanza, sizeof(Piatto), 1, archivio);

    fclose(archivio);   ///chiude il file

    /***aggiuta degli ingredienti selezionati nell'archivio di gestione
        delle scorte*/

    gestione_scorte(pietanza);

    if (numero != 0){
        free(elenco);   ///libero la memoria occupata dall'elenco nel caso sia presente più di un piatto
    }

    return;     ///termina la funzione

}


    /***funzione di stampa del menù: questa funzione rimane sullo schermo
        fino a che non viene dato un qualsiasi input da comando*/

void stampa_menu(){     ///funziona

    FILE *archivio = NULL;  ///puntatore al file contenente l'elenco dei piatti
    Piatto lettura;     ///struttura di appoggio per la visualizzazione dei piatti
    short contatore;    ///in caso di piatti presenti non permette la stampa del messaggio d'errore

    //pulizia_schermo();

    ///apro il file contenente il menù
    if ((archivio = fopen("archivio.dat", "rb")) == NULL) {
        printf("Errore nell' apertura del file. Piatti o menu' inesistenti.\n");
        //getchar();   ///nel caso non vada a buon fine visualizza un messaggio di errore
        return;
        }
    else

        contatore = 0;

        #ifdef linux
        printf("\t\t\t***** Menù *****\n"   ///intestazione
        "%5s\t%35s\t%5s\t%3s\n", "ID", "Nome Piatto", "Tipo", "Prezzo");
        #endif

        #ifdef _WIN32
        printf("\t\t\t***** Menu' *****\n"   ///intestazione
        "%5s\t%35s\t%5s\t%3s\n", "ID", "Nome Piatto", "Tipo", "Prezzo");
        #endif

        ///inizio lettura dell'archivio
        while (!feof(archivio)){    ///finchè il file non è stato completamente letto
        ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
        ///per evitare ciò è stato inserito un controllo if
            if (fread(&lettura, sizeof(Piatto), 1, archivio)){  ///leggi l'archivio e memorizza in una struttura di stampa apposita
        ///infine visualizza su schermo il contenuto
            printf("%5d%40s\t%3d\t%6.2f\n", lettura.ID, lettura.piatto, lettura.tipo, lettura.prezzo);
            contatore = 1;
            }
        }   ///fine ciclo while

        if (contatore == 0){    ///stampa un messaggio a schermo nel caso non siano presenti piatti nel menù
            printf("\n\tNon sono presenti piatti nell'archivio\n");

        }

    fclose(archivio);   ///chiusura di sicurezza

    return;
}

    /***funzione di modifica di un piatto*/

void modifica_piatto(){     ///funziona

    int id;     ///variabile di scelta del piatto da modificare
    Piatto* elenco;     ///struttura dinamica contenente l' elenco dei piatti
    FILE *archivio;     ///puntatore al piatto dell
    int numero;     ///conta il totale dei piatti presenti in elenco
    int i;      ///variabile del ciclo for
    int j;      ///variabile del ciclo di controllo
    int flag;   ///variabile che seleziona il piatto che si vuole modificare e ne permette l'individuazione
    int tipo;   ///variabile che seleziona la tipologia del piatto
    Piatto *lettura;    ///strutta contenente le informazioni del piatto
    int scelta;     ///variabile di selezione delle opzioni
    char conferma;  ///perchè si

    pulizia_schermo();

    stampa_menu();  ///visualizza il menù per facilitare la modifica

    numero = n_piatti_menu();   ///conta il totale dei piatti presenti in elenco

    if (numero == 0 || numero == -1){   ///se non esiste il menù stampa un messaggio di errore
        printf("\nNessun piatto presente. Premi invio per continuare.");
        //getchar();
        getchar();
        return;

    }

    elenco = vettore_elenco(numero);    ///carica i piatti nel vettore dinamico

#ifdef linux
    printf("\n\t\t\t***** Modifica menù *****\n");
#endif
#ifdef _WIN32
    printf("\n\t\t\t***** Modifica menu' *****\n");
#endif

    ///la selezione del piatto avviene tramite ID

    flag = -1;  ///assegno a flag il valore -1 come sentinella nel caso non esista il piatto

    do {
        printf("\nSeleziona l'ID del piatto da modificare: ");
        scanf("%d", &id);
        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input
    }while (id < -1);

    ///cerco l'ID desiderato per tutto l'elenco

    for (i=0; i<numero; i++){
        ///se l'ID scelto corrisponde ad un piatto
        if (id == elenco[i].ID){

            printf("\nE' stato selezionato questo piatto: \n"
                "%5s\t%35s\t%5s\t%3s\n", "ID", "Nome Piatto", "Tipo", "Prezzo");
            printf("%5d\t%35s\t%3d\t%6.2f\n\n", elenco[i].ID, elenco[i].piatto, elenco[i].tipo, elenco[i].prezzo);

            printf("Sei sicuro? y/n ");     ///chiede la conferma dell'operazione
            scanf("%c", &conferma);

            if (!('y' == conferma)){     ///in caso non positivo
                printf("Operazione annullata. Premi invio per continuare.");
                getchar();
                getchar();
                return;
            }
            else
                flag = i;   ///seleziona la posizione in elenco nel piatto e la copia in flag
        }

    }   ///fine ciclo for

    if (flag != -1){    ///nel caso abbia trovato il piatto, prosegue la modifica

        lettura = vettore_elenco(numero);    ///carica i piatti per effettuare i confronti

        ///inizio procedura di modifica del piatto

        do {    ///non viene dato il comando di uscita
            printf("\nScegli quali campi vuoi modificare.\nDigita -1 per uscire\n"
                   "\t1) Modifica del nome\n\t2) Modifica degli ingredienti\n"
                   "\t3) Modifica del prezzo\n\t4) Modifica tipologia\n Scelta: ");
            scanf("%d", &scelta);

        ///switch di scelta opzione

            switch (scelta){
                case 1:{    ///Modifica del nome
                    getchar();
                    printf("Inserisci il nome del nuovo piatto\n");
                    scanf("%49[^\n]s", elenco[flag].piatto);
                    getchar();

                    if (numero != 0){   ///controllo per evitare che in caso di file vuoto dia errore

                        ///    controllo del menù: nel caso sia presente in elenco un piatto con lo stesso nome
                        ///    stampa a schermo un messaggio di errore ed esce dalla funzione

                        for (j=0; j<numero; j++){   ///utilizzo un for per scorrere l'intero menù

                            if (strcmp(elenco[flag].piatto, lettura[j].piatto) == 0){    ///nel caso trovi un piatto con lo stesso nome
                                    printf("\nErrore, piatto già presente in elenco\nPremi invio per continuare. ");
                                    getchar();   ///riutilizzo la variabile dei piatti totali per stampare il messaggio precedente
                                    return;     ///torna al menù di gestione dei piatti
                                }
                            }
                        }
                    break;
                }
                case 2:{    ///Modifica degli ingredienti
                    printf("Inserisci gli ingredienti che lo compongono\n");
                    getchar();
                    for (i=0; i<ING; i++){
                        printf("%d) ", i+1);     ///visualizza il numero del piatto
                        scanf("%[^\n]19s", (char*) &elenco[flag].ingredienti[i][0]); ///cast esplicito per evitare il warning
                        getchar();
                    }
                }
                    break;
                case 3:{
                    do {    ///controllo sul prezzo per evitare numeri assurdi
                        printf("E il prezzo\n");
                        scanf("%f", &elenco[flag].prezzo);
                        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input oppure lo faccia apposta

                        } while (elenco[flag].prezzo < 0);  ///ovvio che un prezzo non debba essere negativo!
                }
                    break;
                case 4:{    ///a seconda della tipologia del piatto assegna il tipo di enumerazione

                            do {

                                printf("Inserisci la tipologia del piatto: \n"
                                        "\t0) Antipasto\t1) Primo\n"
                                        "\t2) Secondo\t3) Contorno\t4) Dessert\n");
                                scanf("%d", &tipo);

                                fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input

                            } while (tipo < 0 || tipo > 4);

                            switch (tipo) {
                                case Antipasto:     ///antipasti
                                    elenco[flag].tipo = 0;
                                        break;
                                case Primo:     ///primi
                                    elenco[flag].tipo = 1;
                                        break;
                                case Secondo:     ///secondi
                                    elenco[flag].tipo = 2;
                                        break;
                                case Contorno:     ///contorni
                                    elenco[flag].tipo = 3;
                                        break;
                                case Dessert:
                                    elenco[flag].tipo = 4;
                                        break;
                                }


                }
                    break;
                case -1:    ///in caso di segnale di uscita esce dal menù di modifica
                    break;
            }

        } while (scelta != -1);

        ///riassegno un diverso ID al piatto modificato
        elenco[flag].ID = (elenco[flag].tipo*100) + strlen(elenco[flag].piatto) + elenco[flag].prezzo;

        ///controllo per evitare che i piatti abbiano casualmente lo stesso ID
        for(i=0; i<numero; i++){
            if (elenco[flag].ID == lettura[i].ID){
                elenco[flag].ID++;
                i=0;    ///nel caso un ID sia uguale ad un altro, lo incrementa di uno e riesegue il controllo
            }
        }


        ///alla fine delle operazioni, riescrive l'elenco nell'archivio

        if ((archivio = fopen("archivio.dat", "wb")) == NULL) { ///se non riesce a scrivere sul piatto esce
            printf("Errore nella modifica del menù\n");
            printf("\nDigita qualsiasi cosa e premi invio per continuare\n");
            getchar();
            return;
            }

        else{   ///altrimenti riscrive tutto l'elenco
            for (i=0; i<numero; i++){
                fwrite(&elenco[i], sizeof(Piatto), 1, archivio);
            }
        }

        free(elenco);   ///libero la memoria

        fclose(archivio);   ///una volta utilizzato chiude il file dell'archivio

    }

    else {  ///altrimenti esce dalla funzione

        #ifdef linux
        getchar();
        #endif

        printf("Piatto non presente in elenco. \nPremi invio per proseguire\n");
        getchar();

    }

    return;

}



    /***Tramite questa funzione è possibile eliminare un piatto dall'elenco*/

void elimina_piatto(){      ///funziona

    char conferma;      ///conferma l'operazione
    int id;     ///variabile di scelta del piatto da eliminare
    Piatto* elenco;     ///vettore contenente l'elenco
    FILE *archivio;     ///puntatore al file che contiene il menù
    int numero;     ///variabile dei piatti totali
    int i;      ///variabile del for
    int flag;   ///variabile che seleziona il piatto che si vuole eliminare e ne permette l'individuazione

    pulizia_schermo();

    stampa_menu();  ///visualizza il menù

    numero = n_piatti_menu();   ///conta i piatti presenti nel menù

    if (numero == 0 || numero == -1){   ///se non presenti, esce
        printf("\nPremi invio per continuare.");
        getchar();
        #ifdef linux
        getchar();
        #endif // linux
        return;

    }

    elenco = vettore_elenco(numero);    ///scarico il menù in un vettore dinamico

    printf("\n\t\t\t***** Elimina piatto *****\n");

    do {
        printf("\nSeleziona l'ID del piatto da eliminare: ");
        scanf("%d", &id);   ///prende in ingresso l'ID del piatto che si desidera eliminare
        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input
    } while (id < -2);

    flag = -1;  ///flag portato a -1 perchè è l'unico elemento che non comparirà nel vettore

    if (numero == 1){   ///nel caso sia l'unico piatto presente in archivio lo ricrea per non provocare errori

        if (id == elenco[0].ID){    ///se è l'unico piatto, si troverà per forza all'inizio del vettore, no?
            printf("\nE' stato selezionato questo piatto: \n"
                    "%5s\t%35s\t%5s\t%3s\n", "ID", "Nome Piatto", "Tipo", "Prezzo");
            printf("%5d\t%35s\t%3d\t%6.2f\n\n", elenco[0].ID, elenco[0].piatto, elenco[0].tipo, elenco[0].prezzo);

            printf("Sei sicuro? y/n ");
            scanf("%c", &conferma);
            getchar();

            if (conferma != 'y'){   ///se non confermato
                printf("Operazione annullata. ");
                getchar();
                return;
            }
            else {  ///altrimenti riscrive l'intero menù da zero, tanto il piatto era uno solo

                if ((archivio = fopen("archivio.dat", "wb")) == NULL) {
                    printf("Errore nella creazione del file\nPremi invio per continuare\n");
                    getchar();
                    return;
                }
                else
                    printf("Piatto eliminato.\nPremi invio per continuare");    ///messaggio di conferma
                    getchar();
                    return;

            }
        }
        else {  ///se l'ID non corrisponde, esce
            printf("Piatto non trovato. Premi invio per continuare\n");
            getchar();
            return;
        }

    }
    else

        if (numero > 1){    ///se presente più di un piatto

            ///cerco l'ID desiderato per tutto l'elenco

            for (i=0; i<numero; i++){

                if (id == elenco[i].ID){    ///se trova l'id corrispondente chiede la conferma per l'eliminazione

                    printf("\nE' stato selezionato questo piatto: \n"
                        "%5s\t%35s\t%5s\t%3s\n", "ID", "Nome Piatto", "Tipo", "Prezzo");
                    printf("%5d\t%35s\t%3d\t%6.2f\n\n", elenco[i].ID, elenco[i].piatto, elenco[i].tipo, elenco[i].prezzo);

                    printf("Sei sicuro? y/n ");
                    scanf("%c", &conferma);
                    getchar();

                    if ((conferma == 'y')){     ///chiede la conferma dell'operazione
                        flag = i;   ///seleziona la posizione in elenco nel piatto e la copia in flag
                    }
                    else {  ///altrimenti annulla tutto ed esce
                        printf("Operazione annullata. Premi invio per continuare.");
                        getchar();

                        return;
                    }
                }
            }



            if (flag != -1){    ///nel caso trovi il piatto prosegue con l'eliminazione

            /***Il punto è questo: il codice scritto sotto ifdef linux è giusta, su linux
                funziona ma su Windows per qualche strano motivo non va, crea un casino assurdo
                e mi ha fatto uscire per tre giorni (e più, dato che non ha dato altri problemi)
                di testa, quando poi la mattina ti alzi, ti lavi la faccia e ti viene in mente che puoi
                saltare un codice simile inserendo un flag da qualche parte, magari in una variabile
                che non viene utilizzata per segnalare che quel piatto non va scritto in elenco e
                il gioco è fatto. La soluzione è molto più efficiente di quella scritta per linux
                ma tant'è, la lascio in compilazione condizionale*/

            #ifdef linux
                /***copio tutti i piatti successivi a quello selezionato al posto dei piatti che li precedono
                    in modo che il piatto da cancellare venga sovrascritto dal successivo e così via*/

                for ( ; flag < numero; flag++){
                    elenco[flag] = elenco[flag+1];      ///copia dei piatti
                }

            /*debugger
                for(i=0; i< numero; i++){
                    printf("%5d\t%35s\t%3d\t%6.2f\n", elenco[i].ID, elenco[i].piatto, elenco[i].tipo, elenco[i].prezzo);

                }
            */
                ///reallaco il vettore contenente l'elenco

                if ((elenco = (Piatto*) realloc(elenco, numero-1)) == NULL) {
                    printf("Errore durante l'eliminazione del piatto\n");
                    printf("\nPremi invio per continuare\n");
                    //getchar();   ///se l'operazione non va a buon fine visualizza un messaggio di errore
                    return;
                }
                else {
                    ///altrimenti apre il file del menù
                    if ((archivio = fopen("archivio.dat", "wb")) == NULL) {
                        printf("Errore nella modifica del menù\n");
                        printf("\nPremi invio per continuare\n");
                        //getchar();   ///se l'operazione non va a buon fine visualizza un messaggio di errore grazie alla scanf che blocca la computazione
                        return;
                        }
                    else {
                        ///e riescrive l'elenco senza il piatto selezionato
                        for (i=0; i<numero-1; i++){
                            fwrite(&elenco[i], sizeof(Piatto), 1, archivio);
                        }
                    }
                }   ///chiusura prima condizione else
                #endif // linux

                #ifdef _WIN32   ///soluzione per windows

                        elenco[flag].porzioni = -1;     ///applico il flag di eliminazione in una variabile inutilizzata

                        if ((archivio = fopen("archivio.dat", "wb")) == NULL) {
                            printf("Errore nella modifica del menù\n");
                            printf("\nPremi invio per continuare\n");
                            //getchar();   ///se l'operazione non va a buon fine visualizza un messaggio di errore grazie alla scanf che blocca la computazione
                            return;
                            }
                        else {

                            for (i=0; i<numero; i++){
                                if (elenco[i].porzioni != -1){
                                    fwrite(&elenco[i], sizeof(Piatto), 1, archivio);
                                }
                            }
                        }
                #endif // _WIN32

                printf("Piatto eliminato.\nPremi invio per continuare");    ///messaggio di conferma
                getchar();

                free(elenco);   ///libero la memoria
                fclose(archivio);   ///chiudo il file

            }
            else {      ///nel caso non trovi il piatto stampa un messaggio di errore
                printf("Piatto non trovato. Premi invio per continuare\n");
                getchar();

            }
        }

    return;
}

    ///!!!
/*
void easteregg(){

    printf("88888888888888888888888888888888888888888888888\n"
            "88888888888888888888888888888888888888888888888\n"
            "88888888888888888888888888888888888888888888888\n"
            "88888888888888888888888888888888888888888888888\n"
            "888888888 888 8     8     8     8 888 888888888\n"
            "888888888 888 8 888 8 888 8 888 88 8 8888888888\n"
            "888888888     8     8     8     888 88888888888\n"
            "888888888 888 8 888 8 88888 8888888 88888888888\n"
            "888888888 888 8 888 8 88888 8888888 88888888888\n"
            "88888888888888888888888888888888888888888888888\n"
            "888888     8     88    8     8     8     888888\n"
            "888888 88888 888 8  888888 888 88888 888 888888\n"
            "888888   888     888  8888 888  8888     888888\n"
            "888888 88888 888 88888 888 888 88888 88 8888888\n"
            "888888     8 888 8    8888 888     8 888 888888\n"
            "88888888888888888888888888888888888888888888888\n"
            "88888888888888888888888888888888888888888888888\n"
            "888888888888888888 AlessioManai 201488888888888\n"
            "88888888888888888888888888888888888888888888888\n"
            "\nPrez entre pls");
#ifdef linux
    getchar();
#endif // linux
    getchar();

    return;

}
*/
    /***questa funzione stampa semplicemente il menù e lo mantiene
        sullo schermo fino a nuovo ordine*/

void stampa_menu_input(){   ///funziona

    //int numero;
    pulizia_schermo();

    stampa_menu();  ///visualizza il menù

    printf("\nPremi invio per continuare\n");   ///messaggio a video

    getchar();
#ifdef linux
    getchar();
#endif // linux
    return;

}

    /***funzione di ricerca di piatti per ingrediente*/

void cerca_piatto(){        ///funziona

    char cerca[NI];     ///stringa in cui verrà inserito il nome dell'ingrediente da ricercare
    Piatto* elenco;     ///struttura dinamica per il caricamento dell'elenco
    int numero;     ///variabile che conta il totale dei piatti
    int i, k;   ///variabili del ciclo for
    short flag;     ///segnala la presenza o meno di piatti trovati
    int glag;     ///segnala la presenza o meno di piatti trovati. perchè glag? finite le idee. e poi f -> g

    pulizia_schermo();

    printf("\t\t\t***** Ricerca piatto *****\n");

    ///carica l'elenco in un vettore dinamico

    numero = n_piatti_menu();

    if (numero == 0 || numero == -1){   ///se non esiste un elenco, esce
        printf("Non sono presenti piatti nell'archivio.\nPremi invio per continuare.");
        getchar();
        #ifdef linux
        getchar();
        #endif // linux
        return;

    }

    elenco = vettore_elenco(numero);

    ///funzioni di ricerca piatto

    //getchar();  ///evita di saltare i controlli

    printf("\nDigita un ingrediente per avviare la ricerca: ");
    scanf("%[^\n]s", cerca);

    getchar();  ///getchar affinchè la funzione non si chiuda

    flag = 0;   ///variabile inizializzata a zero
    glag = 0;   ///variabile di stampa intestazione inizializzata a zero

    ///ricerca
    for (i=0; i<numero; i++){
        for (k=0; k<ING; k++){
            if (strcmp(elenco[i].ingredienti[k], cerca) == 0){  ///se trova l'ingrediente stampa a schermo le informazioni del piatto

                flag = 1;   ///se trova qualche piatto corrispondente viene cambiato a 1

                if (glag == 0){     ///se trova i piatti, stampa a schermo l'intestazione una e una sola volta
                    printf("\n%5s\t%35s\t%5s\t%3s\n", "ID", "Nome Piatto", "Tipo", "Prezzo");
                    glag++;    ///incremento per evitare le che ristampi l'intestazione
                }

                printf("%5d\t%35s\t%3d\t%3.2f\n", elenco[i].ID, elenco[i].piatto, elenco[i].tipo, elenco[i].prezzo);
                }
        }

    }

    ///se la variabile non ha subito modifiche stampa un messaggio di errore
    if (flag == 0){
        printf("\n\tNessuna corrispondenza per \"%s\"\n", cerca);
    }

    free(elenco);   ///una volta finito cancella l'elenco dalla memoria

    ///lascia che il risultato rimanga sullo schermo fino all' input successivo

    printf("\nPremi invio per continuare. ");
    getchar();

    return;
}



    /***questa funzione stampa e avvia il menù di gestione
        dell'archivio dei piatti. A seconda del sistema è
        prevista la stampa del menù*/

void gestione_menu(){   ///funziona

    int scelta;     ///variabile per la selezione del menù
    char conferma;  ///varibile di conferma per l'uscita

    while (1) {     ///mantiene attiva la funzione finchè non si da un comando di uscita

        pulizia_schermo();

    #ifdef linux
        printf("\t***** Gestione dell'archivio dei piatti *****\n\n"
            "Tramite questo menù puoi:\n"
            "\t0) Creare un archivio da zero o resettare quello esistente\n"
            "\t1) Aggiungere nuovi piatti\n"
            "\t2) Modificare qualsiasi campo dei piatti già esistenti\n"
            "\t3) Eliminare piatti precedentemente inseriti\n"
            "\t4) Stampare l'intero menù\n"
            "\t5) Cercare un piatto per ingrediente\n"
            "Per tornare al menu principale digita un qualunque altro numero\nScelta: ");
    #endif
    #ifdef _WIN32
        printf("\t***** Gestione dell'archivio dei piatti *****\n\n"
            "Tramite questo menu' puoi:\n"
            "\t0) Creare un archivio da zero o resettare quello esistente\n"
            "\t1) Aggiungere nuovi piatti\n"
            "\t2) Modificare qualsiasi campo dei piatti gia' esistenti\n"
            "\t3) Eliminare piatti precedentemente inseriti\n"
            "\t4) Stampare l' intero menu'\n"
            "\t5) Cercare un piatto per ingrediente\n"
            "Per tornare al menu principale digita un qualunque altro numero\nScelta: ");
    #endif
        scanf("%d", &scelta);

        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input


        switch (scelta) {
            case 1: aggiungi_piatto();      ///avvia la funzione per aggiungere piatti
                break;
            case 2: modifica_piatto();      ///avvia la funzione per modificare piatti
                break;
            case 3: elimina_piatto();      ///avvia la funzione per eliminare piatti
                break;
            case 4: stampa_menu_input();    ///stampa a schermo l'intero menù
                break;
            case 5: cerca_piatto();      ///avvia la funzione di ricerca di piatti per ingrediente
                break;
            case 0: crea_archivio();      ///avvia la funzione per la creazione di un archivio da zero
                break;
            default:    ///con qualsiasi altro numero esce dal menù
                printf("Stai per uscire dal menu'. Sei sicuro? y/n ");    ///chiede la conferma dell'azione
                scanf("%c", &conferma);
                if ('y' == conferma){
                    return;
                    }
                break;
                }

    }

    return;
}









    /************************************funzioni di gestione della cassa*******************************************/

    /***funzione che aggiorna l'archivio delle scorte subito dopo la stampa dello scontrino,
        prende in ingresso la lista delle ordinazioni*/

void aggiorna_scorte(Ordine *ordinazione, int tavolo){   ///sviluppo

    FILE *scorte = NULL;    ///puntatore al file contenente le scorte
    int i, j, k; ///indici dei for
    int ingredienti_totali;     ///variabile di conteggio delle
    Scorte_ingredienti *elenco_scorte;  ///vettore dinamico contenente gli ingredienti già presenti
    int numero_ordinazioni;     ///numero di ordinazioni effettuate
    Scorte_ingredienti appoggio;    ///struttura di appoggio per la lettura del file

    numero_ordinazioni = ordinazione[tavolo].portate;   ///scarico il numero di ordinazioni

    if ((scorte = fopen("scorte.dat", "ab+")) == NULL) {    ///apro o creo il file
        printf("Errore nella gestione delle scorte di ingredienti. Premi invio per continuare\n");    ///se fallise esce dal programma
        getchar();
        return;
        }
    else {   ///nel caso il file venga aperto scrive il piatto inserito in un numero di byte pari a Piatto

        ingredienti_totali = 0;     ///inizializzo a zero gli ingredienti totali

        /***inizio conteggio dei piatti totali*/

        while (!feof(scorte)){    ///finchè il file non è stato completamente letto
        ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
        ///per evitare ciò è stato inserito un controllo if
            if (fread(&appoggio, sizeof(Scorte_ingredienti), 1, scorte)){  ///leggi l'archivio e memorizza in una struttura di stampa apposita
        ///infine visualizza su schermo il contenuto
            ingredienti_totali++;      ///conta i piatti stampati a schermo
            }
        }

        ///creo un vettore contenente il totale degli ingredienti

        elenco_scorte = malloc(sizeof(Scorte_ingredienti)*ingredienti_totali);

        ///memorizzo i piatti dell'elenco nella struttura creata in precedenza

        while (!feof(scorte)){    ///finchè il file non è stato completamente letto
            ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
            ///per evitare ciò è stato inserito un controllo if
            for (i=0; i<ingredienti_totali; i++){
                if (fread(&elenco_scorte[i], sizeof(Scorte_ingredienti), 1, scorte)){
                }
            }   ///fine stampa su schermo

            fclose(scorte);     ///chiusura del file di lettura

        }   ///fine lettura del database

        ///inizio delle operazioni aggiornamento scorte

        for (i=0; i<numero_ordinazioni; i++){
            for (k=0; k<ING; k++){
                for (j=0; j<ingredienti_totali; j++){   ///effettuo una ricerca tra gli ingredienti presenti nelle scorte
                    ///nel caso uno degli ingredienti corrisponda ad uno di quelli presenti nel piatto
                    if (strcmp(elenco_scorte[j].ingredienti, ordinazione[tavolo].ordini[i].ingredienti[k]) != 0){

                        elenco_scorte[j].utilizzo++;    ///incrementa il suo utilizzo di uno

                    }
                }
            }
        }   ///fine for di controllo

        ///salvo l'aggiornamento nel file

        if ((scorte = fopen("scorte.dat", "wb")) == NULL) {    ///apro il file
            printf("Errore nella gestione delle scorte di ingredienti. Premi invio per continuare\n");    ///nel caso fallisse esce dal programma
            getchar();
            return;
            }

        else {

            for (i=0; i<ingredienti_totali; i++){   ///ogni ingrediente presente nell'elenco viene scritto nel file con le dovute modifiche
                fwrite(&elenco_scorte[i], sizeof(Scorte_ingredienti), 1, scorte);
            }

            fclose(scorte);     ///chiudo il file
        }

        free(elenco_scorte);    ///libera la memoria dall'elenco

    }   ///fine condizione else

    return ;

}


    /***questa funzione gestisce la stampa dello scontrino, prende in ingresso il vettore
        delle ordinazioni, il totale degli scontrini creati in giornata e crea un file
        txt contenente lo scontrino*/

void stampa_scontrino(Ordine *ordinazione, float *totale){    ///funziona

    FILE *scontrino = NULL;     ///puntatore al file che genera lo scontrino
//    FILE *taccuino = NULL;
    FILE *scontrini_totali = NULL;  ///puntatore al file che contiene il totale degli scontrini
    //Ordine ordinazione;
    int i, j;   ///indici dei for
    int n_portate_totali;   ///numero dei piatti totali presenti nell'ordine
    float sconto;   ///variabile nella quale verrà scritto il totale
    int tavolo;

    ///variabili per la gestione dell'ora stampata nello scontrino
    time_t rawtime;     ///variabile del tempo e del calendario basta sull'orologio del computer
    time (&rawtime);    ///sincronizza l'orario interno del pc
    struct tm* orario;  ///struttura che contiene le informazioni su data e ora
    orario = localtime(&rawtime);   ///sincronizza la struttura con l'orario del pc

    ///avvio del codice

    do {    ///controllo sulla scelta del tavolo, in caso negativo ripete la richiesta
        printf("Di quale tavolo vuoi stampare lo scontrino? (1-%d): ", NT);
        scanf("%d", &tavolo);
        fflush(stdin);  ///evita errori di input

    } while (tavolo < 1 || tavolo > NT);

    tavolo--;   ///decrementa di uno per individuarne il vettore corrispondente

    if(ordinazione[tavolo].effettuato != 1){    ///se il tavolo non ha ordini precedenti esce dalla funzione

        printf("Sembra non sia stato ordinato nessun piatto \nin questo tavolo. Premi invio per continuare\n");
        #ifdef linux
        getchar();
        #endif
        getchar();
        return;

    }

    ///inizia la stampa dello scontrino

    if ((scontrino = fopen("scontrino.txt", "w")) == NULL) {     ///creo un file scontrino
        printf("Errore nella stampa dello scontrino.\n"     ///nel caso fallisca stampo un messaggio video
            "Controllare la disponibilità di carta o di\nspazio su disco.\n"
            "Premi invio per continuare.\n");
            getchar();
            return ;
            }
    else {      ///altrimenti inizia a stampare lo scontrino
        fprintf(scontrino, "\t\t*** RISTORANTE K&R ***\n\t Zucchero sintattico, spaghetti-code \n\t\te piatti tipici regionali\n"
            "Dipartimento di Matematica e Informatica\n  Palazzo delle Scienze, via Ospedale 72 \n\t\t 09124 Cagliari\n"
            "\t\tTel. 070 6754675\n\n");    ///intestazione

        fprintf(scontrino, "Tavolo: %d %40s\n", tavolo+1, "Euro");    ///stampa l'intestazione

    //fclose(scontrini_totali);   ///chiude il file

        /***i for che seguono scansionano la lista delle ordinazioni per tipologia dei piatti:
            nel caso corrispondano nell'ordine prestabilito, stampa la serie di piatti che
            corrispondono alla tipologia; nel caso non esistano piatti di quel tipo non scrive
            niente*/

        n_portate_totali = ordinazione[tavolo].portate;

        /***controllo dei doppioni dei piatti inseriti, se presenti li "accorpa"*/

        for (i=0; i<n_portate_totali; i++){
            for(j=i; j<n_portate_totali; j++){
                if(ordinazione[tavolo].ordini[i].ID == ordinazione[tavolo].ordini[j+1].ID && ordinazione[tavolo].ordini[i].porzioni != 0){
                    ordinazione[tavolo].ordini[i].porzioni++;   ///incrementa la portata di uno
                    ordinazione[tavolo].ordini[j+1].porzioni = 0;   ///azzera quella sommata in precedenza
                }
            }
        }

        for (j=0; j<n_portate_totali; j++){
            ///antipasti
            if (ordinazione[tavolo].ordini[j].tipo == Antipasto){
                fprintf(scontrino, "\nAntipasti:");     ///nel caso sia presente almeno un antipasto, scrive l'intestazione
                j = n_portate_totali;   ///conclude il ciclo for con j
                for (i=0; i<n_portate_totali; i++){
                    if (ordinazione[tavolo].ordini[i].tipo == Antipasto && ordinazione[tavolo].ordini[i].porzioni != 0){
                    fprintf(scontrino, "\n %d x %30s \t%8.2f €", ordinazione[tavolo].ordini[i].porzioni, ordinazione[tavolo].ordini[i].piatto, ordinazione[tavolo].ordini[i].prezzo*ordinazione[tavolo].ordini[i].porzioni);
                    }
                }
            }
        }


            ///primi
        for (j=0; j<n_portate_totali; j++){
            if (ordinazione[tavolo].ordini[j].tipo == Primo){
                fprintf(scontrino, "\nPrimi:");
                j = n_portate_totali;
                for (i=0; i<n_portate_totali; i++){
                    if (ordinazione[tavolo].ordini[i].tipo == Primo && ordinazione[tavolo].ordini[i].porzioni != 0){
                    fprintf(scontrino, "\n %d x %30s    \t%8.2f €", ordinazione[tavolo].ordini[i].porzioni, ordinazione[tavolo].ordini[i].piatto, ordinazione[tavolo].ordini[i].prezzo*ordinazione[tavolo].ordini[i].porzioni);
                    }
                }
            }
        }
            ///secondi
        for (j=0; j<n_portate_totali; j++){
            if (ordinazione[tavolo].ordini[j].tipo == Secondo){
                fprintf(scontrino, "\nSecondi:");
                j = n_portate_totali;
                for (i=0; i<n_portate_totali; i++){
                    if (ordinazione[tavolo].ordini[i].tipo == Secondo && ordinazione[tavolo].ordini[i].porzioni != 0){
                    fprintf(scontrino, "\n %d x %30s    \t%8.2f €", ordinazione[tavolo].ordini[i].porzioni, ordinazione[tavolo].ordini[i].piatto, ordinazione[tavolo].ordini[i].prezzo*ordinazione[tavolo].ordini[i].porzioni);
                    }
                }
            }
        }
            ///contorni
        for (j=0; j<n_portate_totali; j++){
            if (ordinazione[tavolo].ordini[j].tipo == Contorno){
                fprintf(scontrino, "\nContorni:");
                j = n_portate_totali;
                for (i=0; i<n_portate_totali; i++){
                    if (ordinazione[tavolo].ordini[i].tipo == Contorno && ordinazione[tavolo].ordini[i].porzioni != 0){
                    fprintf(scontrino, "\n %d x %30s    \t%8.2f €", ordinazione[tavolo].ordini[i].porzioni, ordinazione[tavolo].ordini[i].piatto, ordinazione[tavolo].ordini[i].prezzo*ordinazione[tavolo].ordini[i].porzioni);
                    }
                }
            }
        }
            ///dessert
        for (j=0; j<n_portate_totali; j++){
            if (ordinazione[tavolo].ordini[j].tipo == Dessert){
                fprintf(scontrino, "\nDessert:");
                j = n_portate_totali;
                for (i=0; i<n_portate_totali; i++){
                    if (ordinazione[tavolo].ordini[i].tipo == Dessert && ordinazione[tavolo].ordini[i].porzioni != 0){
                    fprintf(scontrino, "\n %d x %30s    \t%8.2f €", ordinazione[tavolo].ordini[i].porzioni, ordinazione[tavolo].ordini[i].piatto, ordinazione[tavolo].ordini[i].prezzo*ordinazione[tavolo].ordini[i].porzioni);
                    }
                }
            }
        }

        ///stampa l'importo parziale (letto nelle FAQ, altrimenti sarebbe stato nell'if dello sconto)
        fprintf(scontrino, "\n\nImporto parziale: %30.2f €", ordinazione[tavolo].totale);

        if (ordinazione[tavolo].totale > 40){   ///nel caso l'importo parziale sia maggiore di 40 euro applico lo sconto del 10%
            sconto = (ordinazione[tavolo].totale)/10;
            fprintf(scontrino, "\nSconto (10%%) %35.2f €", sconto);
            ordinazione[tavolo].totale -= sconto;   ///sottrae lo sconto al prezzo totale
            }

        fprintf(scontrino, "\n\nTotale: %40.2f €", ordinazione[tavolo].totale);     ///stampa il conto totale

        fprintf(scontrino, "\n\n\n\nCassa: 1\tOra: %d:%d    Data: %d-%d-%d\n\tARRIVEDERCI E GRAZIE", orario->tm_hour,
                                orario->tm_min, orario->tm_mday,
                                orario->tm_mon +1, orario->tm_year + 1900);     ///stampa di ora e data dello scontrino

    }    ///fine condizione else

    fclose(scontrino);  ///al termine delle operazioni chiude lo scontrino e lo stampa

    /***a questo punto inizia a scrivere su un file a parte i totali degli scontrini precedenti*/

    *totale += ordinazione[tavolo].totale;   ///aggiungo il totale dello scontrino attuale a quello dei totali

    ordinazione[tavolo].effettuato = 0;     ///libera il tavolo per un successivo ordine

    if ((scontrini_totali = fopen("scontrini_totali.txt", "a+")) == NULL){     ///creo un file per gli scontrini totali
        printf("Errore nella stampa dello scontrino.\n"     ///nel caso fallisca stampo un messaggio video
            "Controllare la disponibilità di carta o di\nspazio su disco.\n"
            "Premi invio per continuare\n");
            getchar();
            return;
            }     ///esce dal programma
    else {      ///altrimenti inizia a stampare lo scontrino
        fprintf(scontrino, "Ora: %d:%d Data: %d-%d-%d Totale: %.2f €\n", orario->tm_hour,
                                orario->tm_min, orario->tm_mday,    ///stampa di data, ora, giorno e totale
                                orario->tm_mon +1, orario->tm_year + 1900, ordinazione[tavolo].totale);
        ///stampa dei totali
        fprintf(scontrino, "Totali degli scontrini: %.2f €\n", *totale);
        }

    aggiorna_scorte(ordinazione, tavolo);   ///aggiorna la gestione delle scorte

    fclose(scontrini_totali);   ///chiude il file

    return;

}



    /***questa funzione va ad aggiungere piatti in un secondo momento, riceve in ingresso l'ordinazione
        */

void modifica_ordine(Ordine *lettura){     /// funziona

    FILE* taccuino = NULL;      ///puntatore al file di backup
    Piatto *elenco;     ///struttura nella quale verrà memorizzato l'intero elenco dei piatti disponibili
    //Ordine lettura;
    int ordini_totali;  ///numero totale degli ordini presenti
    int aggiunta;   ///numero di piatti da aggiungere
    int i, k, j;    ///indici dei for
    int n_piatti_totali;    ///numero di piatti totale presente nel menù
    int flag;   ///variabile booleana: se il piatto richiesto è presente nell'elenco, passa da 0 a 1 e ne permette la scrittura nell'ordinazione
    int tavolo;     ///variabile di selezione del tavolo
    int cerca;      ///variabile di ricerca piatto

    pulizia_schermo();

    stampa_menu();

    ///carica il menù dei piatti
    n_piatti_totali = n_piatti_menu();

    if (n_piatti_totali == 0 || n_piatti_totali == -1){     ///se non ci sono piatti nel menù non fa partire la procedura
        printf("\nNon sono presenti piatti nel menu'. Premi invio per continuare.");
        getchar();
        return;

    }

    elenco = vettore_elenco(n_piatti_totali);

    do {
        printf("\nA quale tavolo vuoi effettuare aggiunte? (1-%d): ", NT);
        scanf("%d", &tavolo);
        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input

    } while (tavolo < 1 || tavolo > NT);

    tavolo--;   ///decrementa in modo da poter trovare il vettore corrispondente al tavolo

    //printf("debug%d", tavolo);

    if( (lettura[tavolo].effettuato != 1)){     ///se il tavolo non ha ordini precedenti esce dalla funzione

        printf("Sembra non sia stato ordinato nessun piatto \nin questo tavolo. Premi invio per continuare\n");
        getchar();
        #ifdef linux
        getchar();
        #endif // linux
        return ;

    }

    do {
        printf("Quanti piatti vuoi aggiungere? ");   ///prende in ingresso i piatti totali da aggiungere
        scanf("%d", &aggiunta);
        fflush(stdin);  ///evito loop vari nel caso l'utonte sbagli l'input

    } while (aggiunta < 0);

    ordini_totali = aggiunta + lettura[tavolo].portate;     ///conta i piatti totali presenti all'interno dell'ordine

    (lettura[tavolo].ordini) = (Piatto*) realloc((lettura[tavolo].ordini), ordini_totali * sizeof(Piatto));   ///aggiunge nuovi piatti a quelli già presenti

    /***se la calloc dovesse fallire e azzerare il vettore, ripristina l'ordinazione precedente
        e permette comunque l'aggiunta di nuovi piatti all'interno dell'ordine*/

    if ( lettura[tavolo].ordini == NULL ) {
        ///messaggio di errore
        printf("OPS! Il cameriere ha perso l'ordine!\nIn attesa che torni dal cassiere a caricare l'ordine...\n");

        free(lettura[tavolo].ordini); ///per precauzione libero completamente la memoria degli ordini

        if ((taccuino = fopen("taccuino.dat", "rb")) == NULL) {
            printf("Errore nell' apertura del file. Premi invio per proseguire\n");     ///nel caso l'apertura del file fallisce esce dal programma
            getchar();
            return ;
        }

        /***alloco dinamicamente una struttura che conterrà l'intero elenco dei piatti
            e i loro dettagli */

        ordini_totali = lettura[tavolo].portate;

        (lettura[tavolo].ordini) = (Piatto*) malloc(sizeof(Piatto)*(ordini_totali));

        ///memorizzo i piatti inseriti nella prima ordinanzione delle prime posizioni del vettore dinamico

        while (!feof(taccuino)){    ///finchè il file non è stato completamente letto
            ///il ciclo while effettua 'un giro in più' e visualizza due volte l'ultimo piatto della lista
            ///per evitare ciò è stato inserito un controllo if
            for (i=0; i<ordini_totali; i++){
                if (fread(&lettura[tavolo], sizeof(Ordine), 1, taccuino)){  ///legge il taccuino e memorizza in una struttura per permettere la ricerca
                    //DEBUG printf("%s\n", elenco[i].piatto);
                }
            }
        }   ///fine lettura del database

        fclose(taccuino);   ///una volta terminata l'operazione chiude il taccuino

    }   ///fine della condizione if


    /***avvio delle operazioni di inserimento*/

    for (i = lettura[tavolo].portate; i<(ordini_totali); ){

        printf("Inserisci l'ID del piatto %d da aggiungere:\n", i+1);
        scanf("%d", &cerca);

        getchar();  ///evita che salti gli input

        flag = 0;   ///per ogni ciclo andato a buon fine, reimposto il flag a zero

            /***scansione del menù dei piatti: nel caso il piatto richiesto sia presente
                copia tutte le informazioni sul piatto nel vettore delle ordinazioni*/

        for (k=0; k<n_piatti_totali; k++){  ///scansiono il menù dei piatti

                if (cerca == elenco[k].ID){     ///nel caso sia presente
                    ///inizia la copia delle informazioni
                    lettura[tavolo].ordini[i].ID = elenco[k].ID;    ///copia ID
                    strcpy(lettura[tavolo].ordini[i].piatto, elenco[k].piatto);     ///copia nome
                        for (j=0; j<ING; j++){  ///copia ingredienti
                            strcpy(lettura[tavolo].ordini[i].ingredienti[j], elenco[k].ingredienti[j]);
                        }
                    lettura[tavolo].ordini[i].tipo = elenco[k].tipo;    ///copia tipologia
                    lettura[tavolo].ordini[i].prezzo = elenco[k].prezzo;    ///copia prezzo
                    lettura[tavolo].ordini[i].porzioni = 1;
                    printf("Ordine inserito\n");
                    flag = 1;    ///nel caso l'ordine sia stato accettato, passa all'ordine successivo
                    i++;    ///flag: se la scrittura dell'ordine è avvenuta correttamente, passa alla prossima ordinazione
                    k = n_piatti_totali -1; ///chiude il ciclo una volta trovato il piatto ed evita la ristampa di messaggi di errore
                }
            }   ///chiusura del for di ricerca

            if (flag == 0) {      ///nel caso il piatto non sia stato trovato in elenco, riporta un messaggio di errore
                printf("Piatto non trovato. Aggiornare il database o riprovare.\n\n");
            }
    }   ///chiusura for aggiunta

    lettura[tavolo].portate = ordini_totali;    ///determina il numero totale di piatti presenti nell'ordine

    lettura[tavolo].totale = 0;     ///porta il prezzo totale dell'ordine a zero

    ///e lo conta
    for (i=0; i<(ordini_totali); i++){
        lettura[tavolo].totale += lettura[tavolo].ordini[i].prezzo;
    }

    /***backup dell'ordine su un file binario*/

    if ((taccuino = fopen("taccuino.dat", "wb")) == NULL){  ///nel caso non sia riuscito a creare il file da un
            printf("Ops! Il cameriere si è distratto, ripetere l'ordine\n"
            "Premi invio per continuare\n");    ///messaggio di errore
            getchar();
            return ;   ///ed esce dal programma
            }
    else {
        fwrite(&lettura, sizeof(Ordine), 1, taccuino);     ///nel caso si stato aperto correttamente, segna tutto in un file binario,
    }                                                           ///questo per evitare il passaggio di parametri dalla funzione

    fclose(taccuino);   ///al termine delle operazioni chiude tutto

    return ;
}



    /***funzione che gestisce le nuove ordinazioni */

void gestione_ordinazioni(Ordine *ordinazione){    ///funziona

    //Ordine ordinazione[NT];     ///struttura nella quale verrà memorizzato l'ordine
    int numero_porzioni = 0;    ///variabile che contiene il totale delle ordinazioni, decisa a priori così da poter allocare il vettore delle ordinazioni dinamicamente
    int i, k, j; ///indici dei for
    Piatto *elenco = NULL;     ///puntatore a struttura nel quale verrà allocato dinamicamente il menù dei piatti
    //FILE *archivio = NULL;      ///puntatore al file archivio.dat
    int n_piatti_totali = 0;    ///indice dei piatti totali presenti nel menù, inizializzato a 0 prima che inizi il conteggio
    FILE *taccuino = NULL;  ///file in cui viene scritta l'ordinazione, l'ho ritenuto più versatile e semplice rispetto al passaggio di una struttura
    int flag;   ///variabile booleana: se il piatto richiesto è presente nell'elenco, passa da 0 a 1 e ne permette la scrittura nell'ordinazione
    int tavolo;     ///varibile di selezione del tavolo
    char scelta;    ///varibile di conferma in caso di piatto occupato
    int cerca;      ///variabile di ricerca ID piatto

    ///avvio del codice

    pulizia_schermo();
    stampa_menu();  ///visualizza il menù

    ///carica l'elenco nei piatti in un vettore

    n_piatti_totali = n_piatti_menu();

    if (n_piatti_totali == 0 || n_piatti_totali == -1){     ///se non sono presenti piatti, esce
        printf("\nNon sono presenti piatti nel menu'. Premi invio per continuare.");
        getchar();
        return;

    }

    elenco = vettore_elenco(n_piatti_totali);

    //printf("Debug: %s", elenco[0].piatto);




    do {    ///controllo sull' input per il tavolo
        printf("\nNuova ordinazione\nTavolo (1-%d): ", NT);
        scanf("%d", &tavolo);
        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input

    } while (tavolo < 1 || tavolo > NT);

    tavolo--;   ///decrementa la variabile per farlo corrispondere al vettore

    if (ordinazione[tavolo].effettuato == 1){   ///nel caso il tavolo non sia libero visualizza un messaggio di errore
        printf("Sembra che il tavolo sia gia' occupato, effettuare \nlo stesso una nuova ordinazione? y/n\n");

        scanf("%c", &scelta);   ///input di scelta

        if (!(scelta == 'y')){  ///ulteriore conferma
            return ;
        }

    }

    do{
        printf("Seleziona il numero delle ordinazioni: ");
        scanf("%d", &numero_porzioni);
        fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input

    } while (numero_porzioni < 0);

#ifdef linux
    getchar();  ///funzione getchar per evitare che salti la richiesta dell'ordine
#endif // linux

    /***alloco dinamicamente */
    (ordinazione[tavolo].ordini) = (Piatto*) malloc(sizeof(Piatto)*numero_porzioni);

    if ((ordinazione[tavolo].ordini)==NULL){    ///nel caso ciò non avvenga
        printf("Errore nella gestione dell'ordinazione\nContattare il programmatore o consultare la documentazione\n"
        "Premi invio per proseguire\n");
        getchar();   ///il programma terminerà
        return ;
        }

    else {
        for (i=0; i<numero_porzioni; ){
            //printf("DEBUG: %d %d", numero_porzioni, n_piatti_totali);
            printf("Inserisci l'ID piatto numero %d ordinato: ", i+1);

            scanf("%d", &cerca);     ///inserisce l'ordine

            getchar();  ///impedisco che il programma salti degli input

                for (k=0; k<n_piatti_totali; k++){  ///scansiono l'elenco dei piatti

                    flag = 0;   ///per ogni ciclo andato a buon fine, reimposto il flag a zero

                /***scansione del menù dei piatti: nel caso il piatto richiesto sia presente
                    copia tutte le informazioni sul piatto nel vettore delle ordinazioni*/

                    if (cerca == elenco[k].ID){   ///se il piatto è presente
                        ///inizia la copia delle informazioni
                        ordinazione[tavolo].ordini[i].ID = elenco[k].ID;
                        strcpy(ordinazione[tavolo].ordini[i].piatto, elenco[k].piatto);     ///copia il nome del piatto
                        for (j=0; j<ING; j++){  ///copia degli ingredienti
                            strcpy((char*)ordinazione[tavolo].ordini[i].ingredienti[j], (char*) elenco[k].ingredienti[j]);
                        }
                        ordinazione[tavolo].ordini[i].tipo = elenco[k].tipo;
                        ordinazione[tavolo].ordini[i].prezzo = elenco[k].prezzo;
                        ordinazione[tavolo].ordini[i].porzioni = 1;
                        printf("Ordine inserito\n");    ///messaggio di conferma
                        flag = 1;    ///flag: se la scrittura dell'ordine è avvenuta correttamente, passa alla prossima ordinazione
                        i++;    ///nel caso l'ordine sia stato accettato, passa all'ordine successivo
                        k = n_piatti_totali -1; ///chiude il ciclo una volta trovato il piatto ed evita la ristampa di messaggi di errore
                        }
                    }   ///chiusura del for di ricerca

                    if (flag == 0) {      ///nel caso il piatto non sia stato trovato in elenco, riporta un messaggio di errore
                        printf("Piatto non trovato. Aggiornare il database o riprovare.\n\n");
                    }
            }   ///chiusura del for di scrittura ordini

    ordinazione[tavolo].portate = numero_porzioni;  ///determina il totale dei piatti ordinati

    ordinazione[tavolo].totale = 0;     ///porta il prezzo totale dell'ordine a zero

    ///e conta il totale
    for (i=0; i<numero_porzioni; i++){
        ordinazione[tavolo].totale += ordinazione[tavolo].ordini[i].prezzo;
    }

    /******************In origine**************************
    questa funzione era dedicata alla trascrizione dell'ordine su un file binario
    per evitare di passare continuamente valori tra le funzioni. Dopo aver letto le FAQ
    che la trascrizione su un supporto non era consentito ho dovuto modificare un po' il
    codice, che lascio comunque commentato. La soluzione che segue verrà utilizzata
    solamente se la relloc nel menù di aggiunta delle ordinazioni fallirà
    ********************************************************/

    if ((taccuino = fopen("taccuino.dat", "wb")) == NULL){  ///nel caso non sia riuscito a creare il file da un
                printf("Ops! Il cameriere si è distratto, ripetere l'ordine\n"
                "Premi invio per continuare\n");    ///messaggio di errore
                getchar();
                return ;
            }
    else {
             //fprintf(taccuino, "%d %s", ordinazione.ordini[i].ID, ordinazione.ordini[0].piatto);
            fwrite(&ordinazione, sizeof(ordinazione), 1, taccuino);     ///nel caso si stato aperto correttamente, segna tutto in un file binario,
        }                                                           ///questo per evitare il passaggio di parametri dalla funzione
    }   ///chiusura dell'else degli ordini
    fclose(taccuino);   ///al termine delle operazioni chiude tutto

    if (numero_porzioni != 0){
        ordinazione[tavolo].effettuato = 1;     ///flag per segnalare il tavolo occupato
    }
    /*printf("%d %d", ordinazione[tavolo].effettuato, tavolo);
    getchar();*/

    return;
}

    ///stampa a schermo il menù di gestione della cassa e degli scontrini

void gestione_cassa(){      ///funziona

    int scelta;     ///variabile di scelta del menù
    Ordine ordinazione[NT];     ///struttura contenente le ordinazioni
    float totale = 0;    ///variabile contenente il totale di tutti gli scontrini
    char conferma;

    while (1){  ///loop continuo per non andare in segmentation fault all'uscita delle ordinazioni

    pulizia_schermo();

    #ifdef linux
        printf("\t***** Gestione cassa *****\n\n"
            "Tramite questo menù puoi:\n"
            "\t1) Creare una nuova ordinazione\n"
            "\t2) Modificare un' ordinazione (nel caso si verifichi un'aggiunta)\n"
            "\t3) Chiudere il conto e stampare lo scontrino\n"
            "\t0) Torna al menù principale. \n\t ATTENZIONE: ogni ordinazione effettuata verrà persa\n"
            "Scelta: " );
    #endif
    #ifdef _WIN32
            printf("\t***** Gestione cassa *****\n\n"
            "Tramite questo menu' puoi:\n"
            "\t1) Creare una nuova ordinazione\n"
            "\t2) Modificare un' ordinazione (nel caso si verifichi un'aggiunta)\n"
            "\t3) Chiudere il conto e stampare lo scontrino\n"
            "\t0) Tornare al menu' principale. \n\t ATTENZIONE: ogni ordinazione effettuata verra' persa\n"
            "Scelta: " );
    #endif
        do {
            scanf("%d", &scelta);
            fflush(stdin);  ///evito loop vari nel caso l'utente sbagli l'input
        } while (scelta < -2);

        switch (scelta) {
            case 1: gestione_ordinazioni(ordinazione);   ///avvia una nuova ordinazione
                break;
            case 2: modifica_ordine(ordinazione);     ///modifica l'ordine precedente
                break;
            case 3: stampa_scontrino(ordinazione, &totale);  ///avvia la stampa dello scontrino
                break;
            case 0:
                printf("Stai per uscire dalla gestione cassa. Sei sicuro? y/n ");
                scanf("%c", &conferma);
                if (('y' == conferma)){     ///chiede la conferma dell'operazione
                return ;
                }     ///chiude il menù
                break;
            }

        printf("\n\n");     ///spazi per una migliore lettura su schermo
    }

    return ;

}
