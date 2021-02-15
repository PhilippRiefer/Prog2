/******************************
Programmname
Autor
Vllt Erstellungsdatum
Funktion
******************************/

#define _CRT_SECURE_NO_WARNINGS		//Ermöglicht fehlerlose Nutzung von scanf()
#include<stdio.h>	//Standardbibliothek
#include<stdlib.h>	//Gute Frage, auf jeden Fall system("pause") und co glaub ich
#include<string.h>	//String-Funktionen
#include<conio.h>	//Keinen Schimmer.

#define VARIABLE 10



//Klassiker
rewind(stdin);		//Setzt Eingabe zurück oder so?
system("cls");		//Löscht die Ausgabe auf dem Bildschirm
system("pause");	//Beendet das Programm, wartet aber vorher auf eine beliebige Eingabe
char string[stringlänge] = "Hallo";
char stringarray[stringanzahl][stringlänge] = { "Hallo", "Tschüss" };

//STRINGFUNKTIONEN
strcmp(char* erster, char* zweiter); //Vergleicht 2 Strings
//=0 gleich, >0 erster nach zweitem <0 erster vor zweiten

strchr(char* string, int zeichen); //Durchsucht String von links nach rechts nach erstem Auftreten eines Zeichens
strrchr(char* string, int zeichen); //Durchsucht String von rechts nach links nach erstem Auftreten eines Zeichens
//Liefern im Erfolgsfall Adresse des Zeichens zurück, ansonsten NULL

strcpy(char* original, char kopie); //Kopiert einen String


//DATEI ÖFFNEN
//r: read, nur lesen, Anfang vorne
//w: write, nur schreiben, Anfang vorne, nicht existente erzeugen, existierende überschreiben
//a/A: add? schreiben, Anfang hinten, nicht existente erzeugen, neu geschriebenes anhängen
//r+: lesen+schreiben, Anfang vorne
//w+: lesen, schreiben, Anfang vorne, nicht existente erzeugen, existente überschreiben
//a+: genauso wie w+, nur dass es hinten anfängt. Why tho?
//r+b: Lesen im Binärmodus! Ist wohl wichtig für wahlfreien Dateizugriff
FILE* Datei;
Datei = fopen(dateiName, "r");	
if (Datei == NULL)
{
	printf("Fehler beim %cffnen der Datei\n\n", 153);
	goto Fehler / system("pause") / return (fehlercode);
}

//DATEI SCHLIESSEN
fclose(Datei);

//DATEI LESEN
//Datei muss natürlich im richtigen Modus geöffnet sein. Duh.
int geleseneBytes = fread(&puffer, einzulesendeGröße, anzahlWiederholungen, Datei);
if (bytesEinlesen = EOF) {
	printf("Ende der Datei erreicht\n");
}
else if (bytesEinlesen == NULL) {
	printf("Fehler beim Einlesen der Datei:\nKeine weiteren Bytes mehr eingelesen.\n\n")
}

//DATEI SCHREIBEN
int geschriebeneBytes = (puffer, zuSchreibendeGröße, anzahlWiederholungen, Datei);
if (geschriebeneBytes == NULL) {
	printf("Fehler beim Schreiben in der Datei\n\n");
	return (Fehlercode);	//Oder so
}

//SPEICHERZUWEISUNG
puffer = (pufferTyp*)malloc(einzulesendeGröße);	//Einzulesende Größe z.B. sizeof(pufferTyp)
if (puffer == NULL) 
{
	printf("Fehler! Unzureichende Speichermenge!\n\n");
	goto Fehler / system("pause") / return (fehlercode);
}

//SPEICHER FREIGEBEN
free(puffer);

//BUBBLESORT (Liste nach Zahlengröße sortieren)
//	-*pListenAnfang mitgeben-
TListenName* pIterator1;
TListenName* pIterator2;
TListenName* pBeginn;
int j=0;
for (int i = 1; i <= Listenlänge; i++) {
	pIterator1 = pAnfang;
	pIterator2 = pIterator1->next;
	pBeginn = pAnfang;
	while (pIterator2) {
		j++;
		if (pIterator1->größe > pIterator2->größe) {
			pIterator1->next = pIterator2->next;
			pIterator2->next = pIterator1;
			if (j == 1) {
				pAnfang = pIterator2;
			}
			else {
				pBeginn->next = pIterator2;
			}
			pBeginn = pIterator2;
			pIterator2 = pIterator1->next;
		}
	}
}
return pAnfang;

//LISTE LÖSCHEN
// -*pListenName mitgeben-
TListenName* pIterator = pListenName;
while (pIterator) {
	TListenName* pFree = pIterator;
	pIterator = pIterator->next;
	free(pFree);
}

//LISTE UMDREHEN
//*umzudrehendeListe ist nicht zwingend vom Typ TStructName
TStructName* pPuffer = *umzudrehendesListenElement;
TStructName* pNext = NULL;
TStructName* pIterator = pPuffer;

while (pIterator)
{
	pPuffer = pPuffer->next;
	pIterator->next = pNext;
	pNext = pIterator;
	pIterator = pPuffer;
}
umzudrehendeListe = pNext;


//VERKETTETE LISTE DEFINIEREN
typedef struct _structname TStructName;
typedef struct _structname
{
	int a;
	char b;
	TStructName* next;
}TStructName;

TStructName* pListenName;
TStructName* pListenAnfang = NULL;


//LISTE VERKETTEN
pListenName = whatever; //Inhaltszuweisung, nachdem idealerweise Speicher zugewiesen wurde
pListenName->next = pListenAnfang;
pListenAnfang = pListenName;


//ENUM (Variable, die simpel hochgezählt werden kann oder so)
enum name
{
	a,
	b,
	c
};

//SWITCH
switch (variable) {
case 1:
	//Aktion
	break;
case 2:
	//Aktion
	break;
default:
	//Aktion in allen restlichen Fällen
}