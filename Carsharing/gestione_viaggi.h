/*
 * gestione_viaggi.h
 *
 *  Created on: 15 giu 2023
 *      Author: angel
 */

#ifndef GESTIONE_VIAGGI_H_
#define GESTIONE_VIAGGI_H_

void cancellazione_viaggio(int codice, FILE *file);
int controllo_data(int *flag, int giorno, int mese, int anno);
int generazione_codice_viaggio(FILE *file);
void inserimento_viaggio(int *flag, FILE *file);
void modifica_viaggi_preesistenti(FILE *file);
void prenotazione_viaggio(FILE *file, int codice_viaggio, char* citta_partenza, int numero_posti);
void visualizza_viaggi_prezzo_crescente(int *flag, FILE *file);
void ricerca_viaggio(FILE *file);
void visualizza_viaggi(FILE *file);

#endif /* GESTIONE_VIAGGI_H_ */
