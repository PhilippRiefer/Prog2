/******************************************************
PR2 Praktikum 3.1
Autor:		Domenic Heidemann, Maxim Eigenser
Funktion:	Auslesen einer Datei, Inhalt als
			Liste abspeichern, Inhalt erweitern
******************************************************/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

//=====================================================================================

typedef enum
{
	unbekannt = 0,
	DVD,
	BluRay,
	BluRay3D
}TFilmTyp;

//=====================================================================================

typedef struct _film
{
	char name[60];
	char regie[40];
	int laenge;
	char monat;
	short jahr;
	TFilmTyp typ;
}TFilm;

//=====================================================================================

void druckeListe(TFilm pListe[], int *nummer);

TFilm* filmEingeben(TFilm pListe[100], int *nummer);

int sucheFilm(TFilm pListe[100], int *nummer);

void pruef(char puffer[]);

//=====================================================================================
//Hauptfunktion
//Zuerst wird die Datenbank ausgelesen und in einer Liste gespeichert
//Dann öffnet sich ein Menü, mit dem die einzelnen Funktionen per Eingabe abgerufen werden können
int main(void)
{
	TFilm pListe[100];
	int nummer=0;

	FILE *filmdat = NULL;
	filmdat = fopen("FilmDatenbank.dat", "r");
	if (filmdat == NULL) {
		printf("Fehler beim %cffnen der Datei\n", 153);
		return -1;
	}


	for (int lf = 1; lf <= 100; lf++)
	{
		int bytesEinlesen = fread(&pListe[lf], sizeof(char), 112, filmdat);
		if (bytesEinlesen == EOF) {
			printf("Fehler beim Einlesen der Datei:\nEnde der Datei erreicht");
			break;
		}
		else if (bytesEinlesen == 0) {
			//printf("Fehler beim Einlesen der Datei:\nKeine weiteren Bytes mehr eingelesen\n");
			break;
		}
		nummer++;
	}

	fclose(filmdat);
	int*pnummer = &nummer;
	int eingabe = 0;
	while (eingabe != 4) {
		printf("Was m%cchten Sie tun?\n\n", 148);
		printf("1: Alle Filme ausgeben.\n");
		printf("2: Einen weiteren Film eingeben.\n");
		printf("3: Nach einem bestimmten Film suchen.\n");
		printf("4: Das Programm beenden.\n");
		scanf("%d", &eingabe);
		rewind(stdin);
		system("cls");

		switch (eingabe)
		{
		case 1:
			druckeListe(pListe, pnummer);
			break;
		case 2:
			filmEingeben(pListe, pnummer);
			nummer++;
			break;
		case 3:
			sucheFilm(pListe, pnummer);
			break;
		}
	}
}

//=====================================================================================
//Liste Element für Element ausdrucken
void druckeListe(TFilm pListe[], int *nummer)
{
	for (int lf = 1; lf <= *nummer; lf++)
	{
		if (pListe[lf].name == NULL) {
			break;
		}
		printf("%d\nName: %s\n", lf, pListe[lf].name);
		printf("Regie: %s\n", pListe[lf].regie);
		printf("L%cnge in Minuten: %d\n", 132, pListe[lf].laenge);
		printf("Monat: ");
		switch (pListe[lf].monat) {
		case 1:
			printf("Januar\n");
			break;
		case 2:
			printf("Februar\n");
			break;
		case 3:
			printf("M%crz\n", 132);
			break;
		case 4:
			printf("April\n");
			break;
		case 5:
			printf("Mai\n");
			break;
		case 6:
			printf("Juni\n");
			break;
		case 7:
			printf("Juli\n");
			break;
		case 8:
			printf("August\n");
			break;
		case 9:
			printf("September\n");
			break;
		case 10:
			printf("Oktober\n");
			break;
		case 11:
			printf("November\n");
			break;
		case 12:
			printf("Dezember\n");
			break;
		}
		printf("Jahr: %d\n", pListe[lf].jahr);
		printf("Typ: ");
		switch (pListe[lf].typ)
		{
		case 0:
			printf("unbekannt\n\n");
			break;
		case 1:
			printf("DVD\n\n");
			break;
		case 2:
			printf("BluRay\n\n");
			break;
		case 3:
			printf("BluRay 3D\n\n");
			break;
		}
	}
}

//=====================================================================================
//Erstellen eines Listenelements auf Basis von Eingaben
TFilm* filmEingeben(TFilm pListe[100], int *nummer)
{
	int counter=*nummer;
	counter++;
	char name[60];
	char regie[40];
	printf("Name des Films: ");
	fgets(name, 60, stdin);
	char *c1 = strrchr(name, '\n');
	*c1 = '\0';
	strcpy(pListe[counter].name, name);
	printf("\nRegisseur: ");
	fgets(regie, 40, stdin);
	*c1 = strrchr(regie, '\n');
	*c1 = '\0';
	strcpy(pListe[counter].regie, regie);
	printf("\nL%cnge in Minuten: ", 132);
	scanf("%d", &pListe[counter].laenge);
	printf("\nZahl des Monats der Ver%cffentlichung? ", 148);
	rewind(stdin);
	scanf("%c", &pListe[counter].monat);
	pListe[counter].monat -= '0';
	printf("\nJahr der Ver%cffentlichung: ", 148);
	scanf("%hu", &pListe[counter].jahr);
	printf("Vorhandenes Filmformat: ");
	scanf("%d", &pListe[counter].typ);
	return pListe;
}

//=====================================================================================
//Gleicht der Reihe nach die Filme der Liste mit der Eingabe ab
//Untersucht erst, ob die Eingabe gleich dem Filmnamen ist, und wenn nicht, ob einzelne Teile gleich sind
//Sind einzelne Teile gleich, wird das Listenelement einer anderen Liste pSpeicher zugefügt, welche am Ende ausgedruckt wird
int sucheFilm(TFilm pListe[100], int *nummer)
{
	int max=*nummer;
	int lf, lf2 = 1;
	char eingabe[60];
	TFilm pSpeicher[100];

	printf("Welchen Film m%cchten Sie sehen?\n", 148);
	fgets(eingabe, 60, stdin);
	char *c1 = strrchr(eingabe, '\n');
	*c1 = '\0';

	for (lf = 1; lf <= max; lf++) {
		if (strcmp(eingabe, pListe[lf].name) == 0){
			printf("%d: \"%s\" von %s\nLaufzeit: %d Minuten\nVer%cffentlichung: %d\n\n", lf, pListe[lf].name, pListe[lf].regie, pListe[lf].laenge, 148, pListe[lf].jahr);
			return 1;
		}
		else if (strstr(pListe[lf].name, eingabe) != NULL)
		{
			pSpeicher[lf2] = pListe[lf];
			lf2++;
		}
	}

	if (lf2 > 1) {
		printf("Die Auswahl \"%s\" ist nicht eindeutig, was m%cchten Sie sehen?\n\n", eingabe, 148);
		for (lf = 1; lf < lf2; lf++)
			printf("%d: \"%s\" von %s\n", lf, pSpeicher[lf].name, pSpeicher[lf].regie);
	}
	else {
		printf("F%cr Ihre Eingabe gab es leider keine passenden Ergebnisse\n\n", 129);
	}

	return 0;
}