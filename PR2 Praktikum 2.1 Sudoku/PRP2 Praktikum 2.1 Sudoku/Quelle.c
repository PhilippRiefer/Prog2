/*********************************
PRP2 Praktikum 2.1 Sudoku
Autor: Domenic Heidemann
Erstellungsdatum: 23.10.19
*******************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ausgabe(int feld[9][9]);

//==============================================================================================================================

int istLoesung(int feld[9][9]);

//==============================================================================================================================

int istLegalerZug(int eingabe);

//==============================================================================================================================

/*	Hauptfunktion
	Erstellt und füllt das Sudoku-Array
	Dauerschleife aus Ausgabefunktion aufrufen, Eingabe abfragen und Lösungsfunktion aufrufen, bis die 
	Lösungsfunktion 1 zurückliefert	*/

void main(void)
{
	int feld[9][9] = { 0 };
	int zeile;
	int spalte;
	int eingabe;
	int loesung=1;

	//Zeile 1
	feld[0][1] = 3;
	feld[0][2] = 7;
	feld[0][3] = 8;
	feld[0][4] = 2;
	feld[0][5] = 4;
	feld[0][6] = 6;
	feld[0][7] = 9;
	feld[0][8] = 1;

	//Zeile 2
	feld[1][0] = 8;
	feld[1][1] = 4;
	feld[1][2] = 2;
	feld[1][3] = 1;
	feld[1][4] = 6;
	feld[1][5] = 9;
	feld[1][6] = 7;
	feld[1][7] = 3;
	feld[1][8] = 5;

	//Zeile 3
	feld[2][0] = 1;
	feld[2][1] = 9;
	feld[2][2] = 6;
	feld[2][3] = 5;
	feld[2][4] = 7;
	feld[2][5] = 3;
	feld[2][6] = 2;
	feld[2][7] = 4;
	feld[2][8] = 8;

	//Zeile 4
	feld[3][0] = 7;
	feld[3][1] = 8;
	feld[3][2] = 3;
	feld[3][3] = 2;
	feld[3][4] = 4;
	feld[3][5] = 1;
	feld[3][6] = 9;
	feld[3][7] = 5;
	feld[3][8] = 6;

	//Zeile 5
	feld[4][0] = 6;
	feld[4][1] = 5;
	feld[4][2] = 9;
	feld[4][3] = 7;
	feld[4][4] = 3;
	feld[4][5] = 8;
	feld[4][6] = 4;
	feld[4][7] = 1;
	feld[4][8] = 2;

	//Zeile 6
	feld[5][0] = 2;
	feld[5][1] = 1;
	feld[5][2] = 4;
	feld[5][3] = 6;
	feld[5][4] = 9;
	feld[5][5] = 5;
	feld[5][6] = 3;
	feld[5][7] = 8;
	feld[5][8] = 7;

	//Zeile 7
	feld[6][0] = 4;
	feld[6][1] = 6;
	feld[6][2] = 1;
	feld[6][3] = 9;
	feld[6][4] = 5;
	feld[6][5] = 7;
	feld[6][6] = 8;
	feld[6][7] = 2;
	feld[6][8] = 3;

	//Zeile 8
	feld[7][0] = 3;
	feld[7][1] = 2;
	feld[7][2] = 8;
	feld[7][3] = 4;
	feld[7][4] = 1;
	feld[7][5] = 6;
	feld[7][6] = 5;
	feld[7][7] = 7;
	feld[7][8] = 9;
	
	//Zeile 9
	feld[8][0] = 9;
	feld[8][1] = 7;
	feld[8][2] = 5;
	feld[8][3] = 3;
	feld[8][4] = 8;
	feld[8][5] = 2;
	feld[8][6] = 1;
	feld[8][7] = 6;
	feld[8][8] = 4;

	while (1) {
		system("cls");
		ausgabe(feld);
		printf("\nZeile:");
		scanf("%d", &zeile);
		
		//Eingabe per Koordinaten
		//If-Schleifen um sicherzugehen, dass es nur "legale" Eingaben von 1-9 gibt
		if (istLegalerZug(zeile)) {
			printf("\nSpalte:");
			scanf("%d", &spalte);
			if (istLegalerZug(spalte)) {
				printf("Zahl: ");
				scanf("%d", &eingabe);
				if (istLegalerZug(eingabe)) {
					feld[zeile - 1][spalte - 1] = eingabe;
				}
			}
		}
		if (istLoesung(feld) == 1) break;
	}
	system("cls");
	ausgabe(feld);
	printf("\n\nKorrekt!\n\n");
	system("pause");
}


//==============================================================================================================================

int istLegalerZug(int eingabe)
{
	if (eingabe >= 1 && eingabe < 10) return 1;
	else return 0;
}

//==============================================================================================================================

/*	Lösungsfunktion
	Überprüft der Reihe nach, ob sich in den Zeilen und Spalten keine Doppelten oder Nullen befinden
	Überprüft dann, ob sich die Zahlen in den Kästen alle voneinander unterscheiden	*/
int istLoesung(int feld[9][9])	
{
	int lfzeile;
	int lfspalte;
	int lfdrölf;

	//Zeilen
	/*	Gleicht der Reihe nach eine Zahl mit den restlichen in der Zeile ab, wobei doppelte Abfragen oder Abgleiche 
		von der Abgleichszahl mit sich selbst durch lfdrölf verhindert werden*/
	for (lfzeile = 0; lfzeile <= 8; lfzeile++)
	{
		for (lfdrölf=0; lfdrölf<=7; lfdrölf++)
		{		
			for (lfspalte = 1 + lfdrölf; lfspalte <= 8; lfspalte++) 
			{
				if (feld[lfzeile][lfdrölf] == feld[lfzeile][lfspalte] || feld[lfzeile][lfdrölf]==0) 
				{ return 0; break; }
			}
		}
	}
	
	//Spalten
	//Funktioniert genauso wie bei den Zeilen
	for (lfspalte = 0; lfspalte <= 8; lfspalte++)
	{
		for (lfdrölf = 0; lfdrölf <= 7; lfdrölf++)
		{
			for (lfzeile = 1 + lfdrölf; lfzeile <= 8; lfzeile++)
			{
				if (feld[lfdrölf][lfspalte] == feld[lfzeile][lfspalte] || feld[lfdrölf][lfspalte] == 0) 
				{ return 0; break; }
			}
		}
	}
	
	//Kasten
	for (lfspalte = 0; lfspalte <= 6; lfspalte = lfspalte + 3)
	{
		for (lfzeile = 0; lfzeile <= 6; lfzeile = lfzeile + 3)
		{
			if (feld[lfzeile][lfspalte] != feld[lfzeile][lfspalte + 1] && feld[lfzeile][lfspalte + 1] != feld[lfzeile][lfspalte + 2]
				&&feld[lfzeile+1][lfspalte]!=feld[lfzeile+1][lfspalte+1]&&feld[lfzeile+1][lfspalte+1]!=feld[lfzeile+1][lfspalte+2]
				&&feld[lfzeile+2][lfspalte]!=feld[lfzeile+2][lfspalte+1]&&feld[lfzeile+2][lfspalte+1]!=feld[lfzeile+2][lfspalte+2])
			{
				return 1;
			}
			else return 0;
		}
	}
	return 1;
}

//==============================================================================================================================

/*	Ausgabefunktion
	Druckt das Feld aus. Muss ich das erklähren? */
int ausgabe(int feld[9][9])
{
	//Hätte mir rückblickend einiges an %c sparen können mit ner einfachen Leertaste...
	printf("\n      1   2   3   4   5   6   7   8   9");
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 203, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 203, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	printf("\n  1 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[0][0], 255, 179, 255, feld[0][1], 255, 179, 255, feld[0][2], 255, 186, 255, feld[0][3], 255, 179, 255, feld[0][4], 255, 179, 255, feld[0][5], 255, 186, 255, feld[0][6], 255, 179, 255, feld[0][7], 255, 179, 255, feld[0][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186);
	printf("\n  2 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[1][0], 255, 179, 255, feld[1][1], 255, 179, 255, feld[1][2], 255, 186, 255, feld[1][3], 255, 179, 255, feld[1][4], 255, 179, 255, feld[1][5], 255, 186, 255, feld[1][6], 255, 179, 255, feld[1][7], 255, 179, 255, feld[1][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186);
	printf("\n  3 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[2][0], 255, 179, 255, feld[2][1], 255, 179, 255, feld[2][2], 255, 186, 255, feld[2][3], 255, 179, 255, feld[2][4], 255, 179, 255, feld[2][5], 255, 186, 255, feld[2][6], 255, 179, 255, feld[2][7], 255, 179, 255, feld[2][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 204, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 185);
	printf("\n  4 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[3][0], 255, 179, 255, feld[3][1], 255, 179, 255, feld[3][2], 255, 186, 255, feld[3][3], 255, 179, 255, feld[3][4], 255, 179, 255, feld[3][5], 255, 186, 255, feld[3][6], 255, 179, 255, feld[3][7], 255, 179, 255, feld[3][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186);
	printf("\n  5 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[4][0], 255, 179, 255, feld[4][1], 255, 179, 255, feld[4][2], 255, 186, 255, feld[4][3], 255, 179, 255, feld[4][4], 255, 179, 255, feld[4][5], 255, 186, 255, feld[4][6], 255, 179, 255, feld[4][7], 255, 179, 255, feld[4][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186);
	printf("\n  6 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[5][0], 255, 179, 255, feld[5][1], 255, 179, 255, feld[5][2], 255, 186, 255, feld[5][3], 255, 179, 255, feld[5][4], 255, 179, 255, feld[5][5], 255, 186, 255, feld[5][6], 255, 179, 255, feld[5][7], 255, 179, 255, feld[5][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 204, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 185);
	printf("\n  7 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[6][0], 255, 179, 255, feld[6][1], 255, 179, 255, feld[6][2], 255, 186, 255, feld[6][3], 255, 179, 255, feld[6][4], 255, 179, 255, feld[6][5], 255, 186, 255, feld[6][6], 255, 179, 255, feld[6][7], 255, 179, 255, feld[6][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186);
	printf("\n  8 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[7][0], 255, 179, 255, feld[7][1], 255, 179, 255, feld[7][2], 255, 186, 255, feld[7][3], 255, 179, 255, feld[7][4], 255, 179, 255, feld[7][5], 255, 186, 255, feld[7][6], 255, 179, 255, feld[7][7], 255, 179, 255, feld[7][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186, 196, 196, 196, 197, 196, 196, 196, 197, 196, 196, 196, 186);
	printf("\n  9 %c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c%c%d%c%c", 186, 255, feld[8][0], 255, 179, 255, feld[8][1], 255, 179, 255, feld[8][2], 255, 186, 255, feld[8][3], 255, 179, 255, feld[8][4], 255, 179, 255, feld[8][5], 255, 186, 255, feld[8][6], 255, 179, 255, feld[8][7], 255, 179, 255, feld[8][8], 255, 186);
	printf("\n    %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188);
	return 1;
}