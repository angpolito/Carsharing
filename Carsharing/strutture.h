/*
 * struct_viaggio.h
 *
 *  Created on: 14 giu 2023
 *      Author: angel
 */

#ifndef STRUTTURE_H_
#define STRUTTURE_H_

// costanti
#define true 1
#define false 0
#define ANNO_CORRENTE 2023
#define MIN_CODICE_VIAGGIO_GENERABILE 11000
#define MAX_CODICE_VIAGGIO_GENERABILE 12000

// struct
typedef struct {
	int giorno;
	int mese;
	int anno;
} data_t;

typedef struct {
	char nome_guidatore[10];
	char cognome_guidatore[10];
	int codice_guidatore;
	int somma_valutazione;
	int numero_valutazioni;
	float media_valutazione;
} guidatore_t;

typedef struct {
	char destinazione[20];
	char note_viaggio[50];
	int numero_posti;
	int codice_viaggio;
	float costo;
	data_t data_partenza;
} dettagli_viaggio_t;

typedef struct {
	dettagli_viaggio_t dettagli;
	guidatore_t guidatore;
} viaggio_t;

#endif /* STRUTTURE_H_ */
