/*
 * gestione_guidatori.c
 *
 *  Created on: 15 giu 2023
 *      Author: angel
 */

// librerie
#include <stdio.h>
#include <stdlib.h>
#include "strutture.h"

viaggio_t viaggio;

void inserimento_valutazione_guidatore(FILE *file) {
	// variabili locali
	int guidatore_cercato, valutazione, trovato = false;

	do {
		trovato = false;

		// acquisizione codice guidatore
		printf("\nInserire il codice del guidatore da valutare (Digitare 0 per uscire)  -->  ");
		scanf("%d", &guidatore_cercato);

		rewind(file);

		// stampa profilo guidatore cercato
		while (!feof(file) && !trovato) {
			fread(&viaggio, sizeof(viaggio_t), 1, file);
			if (viaggio.guidatore.codice_guidatore == guidatore_cercato) {
				printf("%-15s | %-15s | %-15s\n", "Nome", "Cognome", "Codice");
				printf("%-15s | %-15s | %02d              \n", viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore);
				trovato = true;
			}
		}

		if(trovato == true) {
			do {
				// inserimento valutazione
				printf("\nInserire una valutazione da 1 a 5 --> ");
				scanf("%d", &valutazione);
				if(valutazione != 1 && valutazione != 2 && valutazione != 3 && valutazione != 4 && valutazione != 5) {
					printf("\n<--- !! Valutazione inserita non valida. Riprovare !! --->\n");
				}
			} while(valutazione < 1 || valutazione > 5);

			viaggio.guidatore.somma_valutazione +=  valutazione;
			viaggio.guidatore.numero_valutazioni++;

			fseek(file, -sizeof(viaggio_t), SEEK_CUR);
			fwrite(&viaggio, sizeof(viaggio_t), 1, file);
			printf("\nValutazione correttamente registrata.\n");
		}
		else {
			if(guidatore_cercato != 0) {
				printf("<--- !! Il guidatore cercato non esiste !! --->\n");
			}
		}
	} while (guidatore_cercato != 0);
}

void visualizza_miglior_guidatore(FILE *file) {
    // variabili locali
    int num_guidatori = 0, trovato = false;
    guidatore_t arrayguidatori[100];

    rewind(file);

    while (!feof(file)) {
    	if(fread(&viaggio, sizeof(viaggio_t), 1, file) == 1) {
    		if (viaggio.guidatore.numero_valutazioni > 0) {
				trovato = true;
				viaggio.guidatore.media_valutazione = (float)viaggio.guidatore.somma_valutazione / viaggio.guidatore.numero_valutazioni;
				arrayguidatori[num_guidatori++] = viaggio.guidatore;
			}
    	}
    }

    if (trovato) {
        float max_valutazione = arrayguidatori[0].media_valutazione;

        // trova la valutazione massima
        for (int i = 1; i < num_guidatori; i++) {
            if (arrayguidatori[i].media_valutazione > max_valutazione) {
                max_valutazione = arrayguidatori[i].media_valutazione;
            }
        }

        printf("GUIDATORE CON LA VALUTAZIONE PIU' ALTA:\n");
        for (int i = 0; i < num_guidatori; i++) {
            if (arrayguidatori[i].media_valutazione == max_valutazione) {
                printf("%.2f/5.00 | %s %s (CODICE GUIDATORE: %02d)\n", arrayguidatori[i].media_valutazione, arrayguidatori[i].nome_guidatore, arrayguidatori[i].cognome_guidatore, arrayguidatori[i].codice_guidatore);
            }
        }
    } else {
        printf("<-- !! Non sono presenti valutazioni per i guidatori !! -->\n");
    }
}

void visualizza_profili_guidatori(FILE *file) {
	rewind(file);

	// stampa di tutti i profili guidatori
	while (!feof(file)) {
		if(fread(&viaggio, sizeof(viaggio_t), 1, file) == 1) {
			printf("%s %s (CODICE GUIDATORE: %02d)\n", viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore);
		}
	}
}

void visualizza_valutazioni_guidatori(FILE *file) {
	// variabili locali
	float valutazione_media;

	rewind(file);

	// stampa di tutti i profili guidatori con relative valutazioni
	while (!feof(file)) {
		if(fread(&viaggio, sizeof(viaggio_t), 1, file) == 1) {
			if (viaggio.guidatore.numero_valutazioni > 0) {
				valutazione_media = (float)viaggio.guidatore.somma_valutazione / viaggio.guidatore.numero_valutazioni;
				printf("%.2f/5.00 | %s %s (CODICE GUIDATORE: %02d)\n", valutazione_media, viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore);
			} else {
				printf("Nessuna valutazione per %s %s (CODICE GUIDATORE: %d)\n", viaggio.guidatore.nome_guidatore, viaggio.guidatore.cognome_guidatore, viaggio.guidatore.codice_guidatore);
			}
		}
	}
}
