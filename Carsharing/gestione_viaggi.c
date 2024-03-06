/*
 * gestione_viaggi.c
 *
 *  Created on: 15 giu 2023
 *      Author: angel
 */

// librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "strutture.h"

viaggio_t viaggio;

// file
FILE *filetemp;

void cancellazione_viaggio(int codice, FILE *file1) {
    // variabili locali
    int trovato = false;

    rewind(file1);

    // apertura del file temporaneo
    filetemp = fopen("file_temporaneo.bin", "wb+");

    if (filetemp == NULL) {
        printf("<--- !! Impossibile aprire il file temporaneo !! --->\n");
    }
    else {
		while(!feof(file1)) {
			if((fread(&viaggio, sizeof(viaggio_t), 1, file1)) == 1) {
				// scrittura nel file temporaneo di tutti i viaggi tranne quello da cancellare
				if(viaggio.dettagli.codice_viaggio != codice) {
					fwrite(&viaggio, sizeof(viaggio_t), 1, filetemp);
				}
				else {
					trovato = true;
				}
			}
		}

		fclose(file1); // chiusura del file originale
		fclose(filetemp); // chiusura del file temporaneo

		remove("file_viaggi.bin");
		rename("file_temporaneo.bin", "file_viaggi.bin");

		file1 = fopen("file_viaggi.bin", "rb+"); // riapertura del file originale in modalità di aggiornamento

		if(file1 == NULL) {
			printf("<--- !! Impossibile aprire il file !! -->\n");
		}
		else {
			if(trovato == true) {
				printf("Viaggio cancellato con successo.\n");
			}
			else {
				printf("<--- !! Viaggio non trovato !! --->\n");
			}
		}
    }
}

int controllo_data(int *flag, int giorno, int mese, int anno) {
	*flag = false;

	if(giorno < 0) {
		*flag = true; //errore: giorno non esistente
	}
	if(mese < 1 || mese > 12) {
		*flag = true; //errore: mese non esistente
	}
	if(anno < ANNO_CORRENTE) {
		*flag = true; //errore: anno antecedente all'anno corrente
	}
	if(mese == 1 && giorno > 31) {
		*flag = true; //errore: sconfinamento giorni in GENNAIO
	}
	if(mese == 2 && giorno > 28) {
		*flag = true; //errore: sconfinamento giorni in FEBBRAIO
	}
	if(mese == 3 && giorno > 31) {
		*flag = true; //errore: sconfinamento giorni in MARZO
	}
	if(mese == 4 && giorno > 30) {
		*flag = true; //errore: sconfinamento giorni in APRILE
	}
	if(mese == 5 && giorno > 31) {
		*flag = true; //errore: sconfinamento giorni in MAGGIO
	}
	if(mese == 6 && giorno > 30) {
		*flag = true; //errore: sconfinamento giorni in GIUGNO
	}
	if(mese == 7 && giorno > 31) {
		*flag = true; //errore: sconfinamento giorni in LUGLIO
	}
	if(mese == 8 && giorno > 31) {
		*flag = true; //errore: sconfinamento giorni in AGOSTO
	}
	if(mese == 9 && giorno > 30) {
		*flag = true; //errore: sconfinamento giorni in SETTEMBRE
	}
	if(mese == 10 && giorno > 31) {
		*flag = true; //errore: sconfinamento giorni in OTTOBRE
	}
	if(mese == 11 && giorno > 30) {
		*flag = true; //errore: sconfinamento giorni in NOVEMBRE
	}
	if(mese == 12 && giorno > 31) {
		*flag = true; //errore: sconfinamento giorni in DICEMBRE
	}

	return *flag;
}

int generazione_codice_viaggio(FILE *file) {
	// variabili locali
	int codice_generato, trovato = false;

	rewind(file);

	do {
		codice_generato = rand() % (MAX_CODICE_VIAGGIO_GENERABILE - MIN_CODICE_VIAGGIO_GENERABILE +1) + MIN_CODICE_VIAGGIO_GENERABILE;
		trovato = false;

		while(!feof(file) && !trovato) {
			if(viaggio.dettagli.codice_viaggio == codice_generato) {
				trovato = true;
			}
			fread(&viaggio, sizeof(viaggio_t), 1, file);
		}
	} while(trovato == true);

	return codice_generato;
}

void inserimento_viaggio(int *flag, FILE *file) {
	// variabili locali
	int c, exitflag = false, flag1 = false, trovato = false;

	do {
    	viaggio_t nuovo_viaggio = {
    	    .guidatore = {
			.somma_valutazione = 0,
			.numero_valutazioni = 0,
			.media_valutazione = 0.0
    	    }
    	}; // nuovo oggetto viaggio in ogni iterazione del ciclo

    	// acquisizione dati viaggio
        printf("\nInserire i dati del viaggio da registrare (MAX 1 VIAGGIO PER GUIDATORE)\n(0 nel numero di posti disponibili per terminare l'inserimento)");
        printf("\n\n\tNUMERO POSTI DISPONIBILI  -->  ");
        scanf("%d", &nuovo_viaggio.dettagli.numero_posti);
        if(nuovo_viaggio.dettagli.numero_posti > 0) {
			printf("\tNOME  -->  ");
			scanf("%s", nuovo_viaggio.guidatore.nome_guidatore);
			nuovo_viaggio.guidatore.nome_guidatore[0] = toupper(nuovo_viaggio.guidatore.nome_guidatore[0]);
			printf("\tCOGNOME  -->  ");
			scanf("%s", nuovo_viaggio.guidatore.cognome_guidatore);
			nuovo_viaggio.guidatore.cognome_guidatore[0] = toupper(nuovo_viaggio.guidatore.cognome_guidatore[0]);

        	do {
				trovato = false;
				printf("\tCODICE GUIDATORE  -->  ");
				scanf("%d", &nuovo_viaggio.guidatore.codice_guidatore);

				rewind(file);

				fread(&viaggio, sizeof(viaggio_t), 1, file);
				while(!feof(file) && !trovato) {
					if(viaggio.guidatore.codice_guidatore == nuovo_viaggio.guidatore.codice_guidatore) {
						trovato = true;
					}
					fread(&viaggio, sizeof(viaggio_t), 1, file);
				}

				if (trovato) {
					printf("\n<--- !! ERRORE: Esiste gia' un viaggio associato a questo codice guidatore. Riprova !! --->\n\n");
				}

        	} while(trovato);

			printf("\tDESTINAZIONE  -->  ");
            scanf("%s", nuovo_viaggio.dettagli.destinazione);
			nuovo_viaggio.dettagli.destinazione[0] = toupper(nuovo_viaggio.dettagli.destinazione[0]);
            do {
                printf("\tDATA DISPONIBILE (FORMATO GG/MM/AAAA)  -->  ");
                scanf("%d/%d/%d", &nuovo_viaggio.dettagli.data_partenza.giorno, &nuovo_viaggio.dettagli.data_partenza.mese, &nuovo_viaggio.dettagli.data_partenza.anno);
                controllo_data(&flag1, nuovo_viaggio.dettagli.data_partenza.giorno, nuovo_viaggio.dettagli.data_partenza.mese, nuovo_viaggio.dettagli.data_partenza.anno);
                if(flag1 == true) {
                    printf("\n<--- !! ERRORE: La data fornita non e' valida. Riprova !! --->\n\n");
                }
            } while(flag1 == true);
            do {
                printf("\tCOSTO DELLA CORSA  -->  ");
                scanf("%f", &nuovo_viaggio.dettagli.costo);
                if(nuovo_viaggio.dettagli.costo <= 0.0) {
                    printf("\n<--- !! ERRORE: Il costo del viaggio non e' valido. Riprova !! --->\n\n");
                }
            } while(nuovo_viaggio.dettagli.costo <= 0.0);
            nuovo_viaggio.dettagli.codice_viaggio = generazione_codice_viaggio(file);
            printf("\tNOTE RELATIVE ALLA MODALITA' DI VIAGGIO ((-) nel caso non vi sia niente da mostrare)  -->  ");
            while((c = getchar()) != '\n' && c != EOF);
            fgets(nuovo_viaggio.dettagli.note_viaggio, sizeof(nuovo_viaggio.dettagli.note_viaggio), stdin);
			nuovo_viaggio.dettagli.note_viaggio[strcspn(nuovo_viaggio.dettagli.note_viaggio, "\n")] = '\0';
            fwrite(&nuovo_viaggio, sizeof(viaggio_t), 1, file);
        }
        else {
        	exitflag = true;
        }
    } while(exitflag != true);
}

void modifica_viaggi_preesistenti(FILE *file) {
	// variabili locali
	int codice_viaggio_modifica, c, trovato = false, flag1 = false;

	// acquisizione codice viaggio
	printf("\nInserire il codice del viaggio che si desidera modificare --> ");
	scanf("%d", &codice_viaggio_modifica);

	rewind(file);

	while(!feof(file) && !trovato) {
		fread(&viaggio, sizeof(viaggio_t), 1, file);
		// aggiornamento dei dati di viaggio
		if(viaggio.dettagli.codice_viaggio == codice_viaggio_modifica) {
			printf("\n\tNUMERO POSTI DISPONIBILI  -->  ");
			scanf("%d", &viaggio.dettagli.numero_posti);
			if (viaggio.dettagli.numero_posti > 0) {
				printf("\tDESTINAZIONE  -->  ");
				scanf("%s", viaggio.dettagli.destinazione);
				viaggio.dettagli.destinazione[0] = toupper(viaggio.dettagli.destinazione[0]);
				do {
					printf("\tDATA DISPONIBILE (FORMATO GG/MM/AAAA)  -->  ");
					scanf("%d/%d/%d", &viaggio.dettagli.data_partenza.giorno, &viaggio.dettagli.data_partenza.mese, &viaggio.dettagli.data_partenza.anno);
					controllo_data(&flag1, viaggio.dettagli.data_partenza.giorno, viaggio.dettagli.data_partenza.mese, viaggio.dettagli.data_partenza.anno);
					if (flag1 == true) {
						printf("\n<--- ERRORE: La data fornita non e' valida. Riprova --->\n\n");
					}
				} while (flag1 == true);
				do {
					printf("\tCOSTO DELLA CORSA  -->  ");
					scanf("%f", &viaggio.dettagli.costo);
					if (viaggio.dettagli.costo <= 0.0) {
						printf("\n<--- ERRORE: Il costo del viaggio non e' valido. Riprova --->\n\n");
					}
				} while (viaggio.dettagli.costo <= 0.0);
				printf("\tNOTE RELATIVE ALLA MODALITA' DI VIAGGIO ((-) nel caso non vi sia niente da mostrare)  -->  ");
				while((c = getchar()) != '\n' && c != EOF);

				fgets(viaggio.dettagli.note_viaggio, sizeof(viaggio.dettagli.note_viaggio), stdin);
				viaggio.dettagli.note_viaggio[strcspn(viaggio.dettagli.note_viaggio, "\n")] = '\0';

				fseek(file, -sizeof(viaggio_t), SEEK_CUR);
				fwrite(&viaggio, sizeof(viaggio_t), 1, file);

				trovato = true;
			}
		}
	}

	if(trovato == true) {
		printf("\nViaggio modificato correttamente\n");
	}
	else {
		printf("\n<--- !! Viaggio non trovato. Assicurati che il codice viaggio inserito sia valido !! --->\n");
	}
}

void prenotazione_viaggio(FILE *file, int codice_viaggio, char* citta_partenza, int numero_posti) {
	// variabili locali
	int trovato = false;

    rewind(file);

    while(!feof(file) && !trovato) {
    	fread(&viaggio, sizeof(viaggio_t), 1, file);
        if(viaggio.dettagli.codice_viaggio == codice_viaggio) {
        	trovato = true;
            if((numero_posti <= viaggio.dettagli.numero_posti) && (strcasecmp(viaggio.dettagli.destinazione, citta_partenza) != 0)) {
                viaggio.dettagli.numero_posti -= numero_posti;
                fseek(file, -sizeof(viaggio_t), SEEK_CUR); // spostamento all'indietro di un record
                fwrite(&viaggio, sizeof(viaggio_t), 1, file); // aggiornamento del record nel file

                *citta_partenza = toupper(*citta_partenza);
                printf("\n\nViaggio prenotato: %s - %s [Codice Viaggio: %d] (N. POSTI: %d)\n", citta_partenza, viaggio.dettagli.destinazione, viaggio.dettagli.codice_viaggio, numero_posti);
				if(viaggio.dettagli.numero_posti == 0) {
					cancellazione_viaggio(viaggio.dettagli.codice_viaggio, file);
				}
                if(strcmp(viaggio.dettagli.note_viaggio, "-") == 0) {
					printf("Note relative alla modalita' di viaggio: <-- niente da mostrare -->\n");
				}
				else {
					printf("Note relative alla modalita' di viaggio: '%s'\n", viaggio.dettagli.note_viaggio);
				}
            }
            else {
            	if(numero_posti > viaggio.dettagli.numero_posti) {
					printf("<--- !! Numero posti richiesti non disponibile. Prenotazione annullata !! --->\n");
            	}
            	else {
            		printf("<--- !! La destinazione e la citta' di partenza coincidono. Prenotazione annullata !! --->\n");
            	}
            }
        }
    }
    if(trovato == false) {
		printf("<--- !! Viaggio non trovato !! --->\n");
    }
}

int visualizza_viaggi_prezzo_crescente(int *flag, FILE *file) {
	// variabili locali
	int num_viaggi = 0;
	viaggio_t arrayviaggi[100];
	*flag = false;

	rewind(file);

	while(!feof(file)) {
		if(fread(&viaggio, sizeof(viaggio_t), 1, file) == 1) {
			arrayviaggi[num_viaggi++] = viaggio;
			*flag = true;
		}
	}

	if(*flag) {
		for(int i = 0; i < num_viaggi - 1; i++) {
			for(int j = i + 1; j < num_viaggi; j++) {
				if(arrayviaggi[i].dettagli.costo > arrayviaggi[j].dettagli.costo) {
					viaggio_t temp = arrayviaggi[i];
					arrayviaggi[i] = arrayviaggi[j];
					arrayviaggi[j] = temp;
				}
			}
		}

		printf("%-15s | %-15s | %-15s | %-15s | %-15s | %-25s | %-15s | %-15s\n", "Codice viaggio", "Numero posti", "Nome", "Cognome", "Codice", "Destinazione", "Data disponibile", "Costo della corsa");
		for(int i = 0; i < num_viaggi; i++) {
			viaggio_t viaggio = arrayviaggi[i];
			printf("%-15d | %-15d | %-15s | %-15s | %02d              | %-25s | %02d/%02d/%d       | %-15.2f\n", viaggio.dettagli.codice_viaggio, viaggio.dettagli.numero_posti, viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore, viaggio.dettagli.destinazione, viaggio.dettagli.data_partenza.giorno, viaggio.dettagli.data_partenza.mese, viaggio.dettagli.data_partenza.anno, viaggio.dettagli.costo);
		}
	}

	else {
		printf("<--- !! Non ci sono viaggi disponibili !! --->\n");
	}

	return *flag;
}

void ricerca_viaggio(FILE *file) {
	// variabili locali
	char scelta, destinazione_cercata[20], partenza_viaggio_prenotazione[20];
	int num_viaggi, giorno_cercato, mese_cercato, anno_cercato, codice_viaggio_prenotazione, numero_posti_prenotazione, trovato = false, flag1 = false;

	do {
		printf("\nVuoi effettuare una ricerca per destinazione, per data o vuoi semplicemente visualizzare tutti i prossimi viaggi?\n\n"
				"\t[1] - Ho una destinazione\n"
				"\t[2] - Mostrami tutti i viaggi in programma per una data specifica\n"
				"\t[3] - Mostrami l'elenco di tutti i prossimi viaggi ordinati per prezzo crescente\n"
				"\t[4] - Indietro\n\n"
				"Fai la tua scelta: ");
		scanf(" %c", &scelta);

		switch(scelta) {
			// ricerca per destinazione
			case '1':
				do {
					num_viaggi = 0;
					viaggio_t arrayviaggi[100];
					trovato = false;

					printf("\n\tDove vuoi andare? (Digitare 'esc' per uscire)  -->  ");
					scanf("%s", destinazione_cercata);

					rewind(file);

					while(!feof(file)) {
						if(fread(&viaggio, sizeof(viaggio_t), 1, file) == 1) {
							if (strcasecmp(viaggio.dettagli.destinazione, destinazione_cercata) == 0) {
								arrayviaggi[num_viaggi++] = viaggio;
								trovato = true;
							}
						}
					}

					if(trovato == true) {
						for(int i = 0; i < num_viaggi - 1; i++) {
							for(int j = i + 1; j < num_viaggi; j++) {
								if(arrayviaggi[i].dettagli.costo > arrayviaggi[j].dettagli.costo) {
									viaggio_t temp = arrayviaggi[i];
									arrayviaggi[i] = arrayviaggi[j];
									arrayviaggi[j] = temp;
								}
							}
						}

						printf("%-15s | %-15s | %-15s | %-15s | %-15s | %-25s | %-15s | %-15s\n", "Codice viaggio", "Numero posti", "Nome", "Cognome", "Codice", "Destinazione", "Data disponibile", "Costo della corsa");
						for(int i = 0; i < num_viaggi; i++) {
							viaggio_t viaggio = arrayviaggi[i];
							printf("%-15d | %-15d | %-15s | %-15s | %02d              | %-25s | %02d/%02d/%d       | %-15.2f\n", viaggio.dettagli.codice_viaggio, viaggio.dettagli.numero_posti, viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore, viaggio.dettagli.destinazione, viaggio.dettagli.data_partenza.giorno, viaggio.dettagli.data_partenza.mese, viaggio.dettagli.data_partenza.anno, viaggio.dettagli.costo);
						}

						// acquisizione dati di prenotazione
						printf("\nInserire il codice del viaggio che si vuole prenotare --> ");
						scanf("%d", &codice_viaggio_prenotazione);
						printf("\nInserire la citta' dalla quale si desidera partire --> ");
						scanf("%s", partenza_viaggio_prenotazione);
						printf("\nInserire il numero di posti che si vuole prenotare per il viaggio selezionato --> ");
						scanf("%d", &numero_posti_prenotazione);
						if(numero_posti_prenotazione > 0) {
							prenotazione_viaggio(file, codice_viaggio_prenotazione, partenza_viaggio_prenotazione, numero_posti_prenotazione);
						}
						else {
							printf("<--- !! Numero posti non valido !! --->\n");
						}
					}

					else {
						printf("Non sono disponibili viaggi relativi alla destinazione indicata.\n");
					}
				} while (strcmp(destinazione_cercata, "esc") != 0);

				break;
			case '2':
				// ricerca per data
				do {
					num_viaggi = 0;
					viaggio_t arrayviaggi[100];
					trovato = false;
					do {
						printf("\n\tIn che data vorresti partire? (FORMATO GG/MM/AAAA) (digitare 0 per uscire)  -->  ");
						scanf("%d/%d/%d", &giorno_cercato, &mese_cercato, &anno_cercato);
						controllo_data(&flag1, giorno_cercato, mese_cercato, anno_cercato);
						if(flag1 == true) {
							printf("\n<--- ERRORE: La data fornita non e' valida --->\n\n");
						}
					} while(flag1 == true);

					rewind(file);

					while (!feof(file)) {
						if(fread(&viaggio, sizeof(viaggio_t), 1, file) == 1) {
							if((giorno_cercato == viaggio.dettagli.data_partenza.giorno) && (mese_cercato == viaggio.dettagli.data_partenza.mese)) {
								arrayviaggi[num_viaggi++] = viaggio;
								trovato = true;
							}
						}
					}

					if(trovato == true) {
						for(int i = 0; i < num_viaggi - 1; i++) {
							for(int j = i + 1; j < num_viaggi; j++) {
								if(arrayviaggi[i].dettagli.costo > arrayviaggi[j].dettagli.costo) {
									viaggio_t temp = arrayviaggi[i];
									arrayviaggi[i] = arrayviaggi[j];
									arrayviaggi[j] = temp;
								}
							}
						}

						printf("%-15s | %-15s | %-15s | %-15s | %-15s | %-25s | %-15s | %-15s\n", "Codice viaggio", "Numero posti", "Nome", "Cognome", "Codice", "Destinazione", "Data disponibile", "Costo della corsa");
						for(int i = 0; i < num_viaggi; i++) {
							viaggio_t viaggio = arrayviaggi[i];
							printf("%-15d | %-15d | %-15s | %-15s | %02d              | %-25s | %02d/%02d/%d       | %-15.2f\n", viaggio.dettagli.codice_viaggio, viaggio.dettagli.numero_posti, viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore, viaggio.dettagli.destinazione, viaggio.dettagli.data_partenza.giorno, viaggio.dettagli.data_partenza.mese, viaggio.dettagli.data_partenza.anno, viaggio.dettagli.costo);
						}

						// acquisizione dati di prenotazione
						printf("\nInserire il codice del viaggio che si vuole prenotare --> ");
						scanf("%d", &codice_viaggio_prenotazione);
						printf("\nInserire la citta' dalla quale si vuole partire --> ");
						scanf("%s", partenza_viaggio_prenotazione);
						printf("\nInserire il numero di posti che si vuole prenotare per il viaggio selezionato --> ");
						scanf("%d", &numero_posti_prenotazione);
						if(numero_posti_prenotazione > 0) {
							prenotazione_viaggio(file, codice_viaggio_prenotazione, partenza_viaggio_prenotazione, numero_posti_prenotazione);
						}
						else {
							printf("<--- !! ERRORE: Numero posti non valido !! --->\n");
						}
					}

					else {
						printf("Non sono disponibili viaggi relativi alla data indicata.\n");
					}
				} while(giorno_cercato != 0);

				break;
			case '3':
				// visualizzazione di tutti i viaggi e prenotazione
				visualizza_viaggi_prezzo_crescente(&trovato, file);

				if(trovato) {
					// acquisizione dati di prenotazione
					printf("\nInserire il codice del viaggio che si vuole prenotare --> ");
					scanf("%d", &codice_viaggio_prenotazione);
					printf("\nInserire la citta' dalla quale si vuole partire --> ");
					scanf("%s", partenza_viaggio_prenotazione);
					printf("\nInserire il numero di posti che si vuole prenotare per il viaggio selezionato --> ");
					scanf("%d", &numero_posti_prenotazione);
					if(numero_posti_prenotazione > 0) {
						prenotazione_viaggio(file, codice_viaggio_prenotazione, partenza_viaggio_prenotazione, numero_posti_prenotazione);
					}
					else {
						printf("<--- !! ERRORE: Numero posti non valido !! --->\n");
					}
				}
				break;
			case '4':
				break;
			default:
				printf("<--- !! ERRORE: Scelta non valida. Riprovare !! --->\n");
				break;
		}
	} while (scelta != '4');
}

void visualizza_viaggi(FILE *file) {

	rewind(file);

	// stampa dei viaggi
	printf("%-15s | %-15s | %-15s | %-15s | %-15s | %-25s | %-15s | %-15s\n", "Codice viaggio", "Numero posti", "Nome", "Cognome", "Codice", "Destinazione", "Data disponibile", "Costo della corsa");
	while(!feof(file)) {
		if(fread(&viaggio, sizeof(viaggio_t), 1, file) == 1) {
			printf("%-15d | %-15d | %-15s | %-15s | %02d              | %-25s | %02d/%02d/%d       | %-15.2f\n", viaggio.dettagli.codice_viaggio, viaggio.dettagli.numero_posti, viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore, viaggio.dettagli.destinazione, viaggio.dettagli.data_partenza.giorno, viaggio.dettagli.data_partenza.mese, viaggio.dettagli.data_partenza.anno, viaggio.dettagli.costo);
		}
	}
}
