/*
 ============================================================================
 Nome        : carsharing.c
 Autore      : Angelo Polito
 Matricola	 : 775433
 Corso		 : INFO (MZ)
 Descrizione : Caso di studio: Piattaforma di Carsharing
 ============================================================================
 */

// librerie
#include <stdlib.h>
#include <stdio.h>
#include "visualizza_menu.h"

// file
FILE *file;

// main
int main() {
	// apertura del file in modalita' lettura/scrittura binaria
	file = fopen("file_viaggi.bin", "rb+");

	if(file == NULL)
		printf("\n\n\n <--- !! ERRORE: Impossibile aprire il file !! ---> \n\n\n"); // errore nell'apertura del file
	else {
		visualizza_menu(file);
		fclose(file);
	}

	return 0;
}
