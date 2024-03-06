/*
 * visualizza_menu.c
 *
 *  Created on: 30 mag 2023
 *      Author: angel
 */

// librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestione_viaggi.h"
#include "gestione_guidatori.h"
#include "strutture.h"

viaggio_t viaggio;

void visualizza_menu(FILE *file) {
    // variabili locali
	int codice_viaggio_cancellazione, flag1 = false;
    char logo[] =
        "  _____              _____ _                _             \n"
        " / ____|            / ____| |              (_)            \n"
        "| |     __ _ _ __  | (___ | |__   __ _ _ __ _ _ __   __ _ \n"
        "| |    / _` | '__|  \\___ \\| '_ \\ / _` | '__| | '_ \\ / _` |\n"
        "| |___| (_| | |     ____) | | | | (_| | |  | | | | | (_| |\n"
        " \\_____\\__,_|_|    |_____/|_| |_|\\__,_|_|  |_|_| |_|\\__, |\n"
        "                                                     __/ |\n"
        "                                                    |___/   ";

    char scelta = '1', scelta2 = '1', scelta3 = '1', scelta4 = '1';

    printf("%s\n\nBenvenuto sulla nostra piattaforma di Car Sharing!\nPer iniziare:\n", logo);

    // menu
    do {
        printf("\n\t[1] - Sono un guidatore\n"
               "\t[2] - Sono un passeggero\n"
               "\t[3] - Visualizza statistiche\n"
               "\t[4] - Terminare il programma\n\n"
               "Fai la tua scelta: ");
        scanf(" %c", &scelta);

        switch (scelta) {
        	// menu guidatore
            case '1':
                do {
                    printf("\n\t[1] - Voglio inserire un viaggio\n"
                    		"\t[2] - Voglio modificare un viaggio preesistente\n"
                           "\t[3] - Voglio cancellare un viaggio\n"
                           "\t[4] - Indietro\n\n"
                           "Fai la tua scelta: ");
                    scanf(" %c", &scelta2);

                    switch (scelta2) {
                        case '1':
                            inserimento_viaggio(&flag1, file);
                            break;
                        case '2':
                            visualizza_viaggi(file);
                            modifica_viaggi_preesistenti(file);
                            break;
                        case '3':
                        	visualizza_viaggi(file);
                        	printf("\nInserire il codice del viaggio da cancellare: ");
							scanf("%d", &codice_viaggio_cancellazione);
							cancellazione_viaggio(codice_viaggio_cancellazione, file);
                            break;
                        case '4':
                        	break;
                        default:
                            printf("<--- !! ERRORE: Scelta non valida. Riprovare !! --->\n");
                            break;
                    }
                } while (scelta2 != '4');
                break;
            case '2':
            	// menu passeggero
                do {
                    printf("\n\t[1] - Voglio prenotare un viaggio\n"
                           "\t[2] - Voglio inserire una valutazione per un guidatore\n"
                           "\t[3] - Indietro\n\n"
                           "Fai la tua scelta: ");
                    scanf(" %c", &scelta3);
                    switch (scelta3) {
                        case '1':
                            ricerca_viaggio(file);
                            break;
                        case '2':
                            visualizza_profili_guidatori(file);
                            inserimento_valutazione_guidatore(file);
                            break;
                        case '3':
                            break;
                        default:
                            printf("<--- !! ERRORE: Scelta non valida. Riprovare !! --->\n");
                            break;
                    }
                } while (scelta3 != '3');
                break;
            case '3':
            	// menu statistiche
                do {
                    printf("\n\t[1] - Guidatore con valutazione piu' alta\n"
                    		"\t[2] - Statistiche guidatori\n"
                           "\t[3] - Indietro\n\n"
                           "Fai la tua scelta: ");
                    scanf(" %c", &scelta4);
                    switch (scelta4) {
                        case '1':
                            visualizza_miglior_guidatore(file);
                            break;
                        case '2':
                        	visualizza_valutazioni_guidatori(file);
                            break;
                        case '3':
                        	break;
                        default:
                            printf("<--- !! ERRORE: Scelta non valida. Riprovare !! --->\n");
                            break;
                    }
                } while (scelta4 != '3');
                break;
            case '4':
                printf("Grazie per averci scelto. A presto!");
                break;
            default:
                printf("<--- !! ERRORE: Scelta non valida. Riprovare !! --->\n");
                break;
        }
    } while (scelta != '4');
}
