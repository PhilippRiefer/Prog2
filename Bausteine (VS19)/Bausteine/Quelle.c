/******************************
Programmname
Autor
Vllt Erstellungsdatum
Funktion
******************************/

#define _CRT_SECURE_NO_WARNINGS		//Erm�glicht fehlerlose Nutzung von scanf()
#include<stdio.h>	//Standardbibliothek
#include<stdlib.h>	//Gute Frage, auf jeden Fall system("pause") und co glaub ich
#include<string.h>	//String-Funktionen
#include<conio.h>	//Keinen Schimmer.

#define VARIABLE 10



//Klassiker
rewind(stdin);		//Setzt Eingabe zur�ck oder so?
system("cls");		//L�scht die Ausgabe auf dem Bildschirm
system("pause");	//Beendet das Programm, wartet aber vorher auf eine beliebige Eingabe
char string[stringl�nge] = "Hallo";
char stringarray[stringanzahl][stringl�nge] = { "Hallo", "Tsch�ss" };

//STRINGFUNKTIONEN
strcmp(char* erster, char* zweiter); //Vergleicht 2 Strings
//=0 gleich, >0 erster nach zweitem <0 erster vor zweiten

strchr(char* string, int zeichen); //Durchsucht String von links nach rechts nach erstem Auftreten eines Zeichens
strrchr(char* string, int zeichen); //Durchsucht String von rechts nach links nach erstem Auftreten eines Zeichens
//Liefern im Erfolgsfall Adresse des Zeichens zur�ck, ansonsten NULL

strcpy(char* original, char kopie); //Kopiert einen String


//DATEI �FFNEN
//r: read, nur lesen, Anfang vorne
//w: write, nur schreiben, Anfang vorne, nicht existente erzeugen, existierende �berschreiben
//a/A: add? schreiben, Anfang hinten, nicht existente erzeugen, neu geschriebenes anh�ngen
//r+: lesen+schreiben, Anfang vorne
//w+: lesen, schreiben, Anfang vorne, nicht existente erzeugen, existente �berschreiben
//a+: genauso wie w+, nur dass es hinten anf�ngt. Why tho?
//r+b: Lesen im Bin�rmodus! Ist wohl wichtig f�r wahlfreien Dateizugriff
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
//Datei muss nat�rlich im richtigen Modus ge�ffnet sein. Duh.
int geleseneBytes = fread(&puffer, einzulesendeGr��e, anzahlWiederholungen, Datei);
if (bytesEinlesen = EOF) {
	printf("Ende der Datei erreicht\n");
}
else if (bytesEinlesen == NULL) {
	printf("Fehler beim Einlesen der Datei:\nKeine weiteren Bytes mehr eingelesen.\n\n")
}

//DATEI SCHREIBEN
int geschriebeneBytes = (puffer, zuSchreibendeGr��e, anzahlWiederholungen, Datei);
if (geschriebeneBytes == NULL) {
	printf("Fehler beim Schreiben in der Datei\n\n");
	return (Fehlercode);	//Oder so
}

//SPEICHERZUWEISUNG
puffer = (pufferTyp*)malloc(einzulesendeGr��e);	//Einzulesende Gr��e z.B. sizeof(pufferTyp)
if (puffer == NULL) 
{
	printf("Fehler! Unzureichende Speichermenge!\n\n");
	goto Fehler / system("pause") / return (fehlercode);
}

//SPEICHER FREIGEBEN
free(puffer);

//BUBBLESORT (Liste nach Zahlengr��e sortieren)
//	-*pListenAnfang mitgeben-
TListenName* pIterator1;
TListenName* pIterator2;
TListenName* pBeginn;
int j=0;
for (int i = 1; i <= Listenl�nge; i++) {
	pIterator1 = pAnfang;
	pIterator2 = pIterator1->next;
	pBeginn = pAnfang;
	while (pIterator2) {
		j++;
		if (pIterator1->gr��e > pIterator2->gr��e) {
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

//LISTE L�SCHEN
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


//ENUM (Variable, die simpel hochgez�hlt werden kann oder so)
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
	//Aktion in allen restlichen F�llen
}