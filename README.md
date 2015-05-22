# Progetto finale PR1 A.A. 2013-2014

Progetto finale PR1: "Il progetto è relativo alla gestione di un ristorante con 15 tavoli e della gestione delle ordinazioni nonché della stampa degli scontrini."

Il programma dovrà permettere le seguenti operazioni:
Gestione menu
L’operatore dovrà poter creare e aggiornare l’elenco dei piatti disponibili presso il
ristorante.
Ogni piatto dovrà essere memorizzato all’interno di una struttura contenente:
-­‐ ID, identificativo del piatto;
-­‐ Nome piatto, definito da una stringa minore o uguale ai 100 caratteri;
-­‐ Tipologia (Antipasto, Primo, Secondo, Contorno, Dessert) definito utilizzando
un’enumerazione;
-­‐ Ingredienti, memorizzati in un vettore di stringhe. Ogni piatto dovrà essere
composto (sempre) da tre ingredienti.
-­‐ Prezzo, espresso in euro con due cifre decimali.
L’elenco dei piatti dovrà essere memorizzato all’interno di un file binario, e, attraverso
l’uso di un menu dedicato, dovrà essere quindi possibile:
-­‐ Aggiungere nuovi piatti (evitando doppioni);
-­‐ Modificare qualsiasi campo dei piatti già esistenti;
-­‐ Eliminare piatti precedentemente inseriti (in questo caso prestare particolare
attenzione a come compattare poi l’elenco dei piatti);
-­‐ Stampare l’intero menù;
-­‐ Ricercare e stampare tutti i piatti aventi un certo ingrediente, effettuando una
ricerca sui tre ingredienti che compaiono in ogni piatto.
Gestione cassa
L’operatore dovrà poter gestire i tavoli serviti e le ordinazioni richieste.
Nel momento in cui arriva un’ordinazione, l’utente dovrà creare un nuovo
scontrino/ordinazione sulla base dei piatti ordinati. Nel caso in cui i clienti ordinino altri
piatti in un secondo momento, questi dovranno essere aggiunti allo
scontrino/ordinazione, e, nel momento in cui sarà chiesto il conto, lo scontrino definitivo
dovrà essere stampato.
Lo scontrino sarà memorizzato come una struttura contenente le seguenti informazioni:
-­‐ ID, rappresentante il numero del tavolo;
-­‐ Ordini, la cui organizzazione è lasciata a discrezione dello studente;
-­‐ Prezzo totale, che sarà editato direttamente al momento della stampa.Per ogni scontrino dovranno inoltre essere gestite le seguenti operazioni:
-­‐ Creazione nuovo scontrino: ogni scontrino sarà relativo ad un tavolo, non
possono esistere più scontrini per uno stesso tavolo.
-­‐ Aggiunta ordini: tale aggiunta dovrà essere basata sull’archivio creato in
precedenza specificando anche la quantità di porzioni richieste;
-­‐ Stampa scontrino: la stampa dovrà seguire l’esempio proposto.
Il calcolo del totale dello scontrino dovrà essere eseguito solo al momento della stampa
e, nel caso in cui l’importo sia maggiore di 40 €, dovrà essere applicato uno sconto sul
totale pari al 10%.
La stampa dello scontrino non avverrà attraverso stampanti ad aghi, a getto d’inchiostro o
laser, ma dovrà essere salvato all’interno di un file di testo.
Ogni nuovo scontrino che va in stampa sovrascriverà quello precedente.
Contestualmente alla stampa dello scontrino dovrà essere gestito un altro file di testo
contenente il totale di tutti gli scontrini stampati, aggiornando il totale e aggiungendo il
nuovo importo.