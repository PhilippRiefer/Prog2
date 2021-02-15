/****************************************************************
Aufgabe 4.1
Autor Georg Westerkamp
Datum 12.12.2018
Kurzbeschreibung: Diese Funktionen dienen zum Einlesen einer BMP Datei und deren Darstellung.
*****************************************************************/

#include "main.h"

// ============================================================================================================
void erzeugenTestbild(TBild *pBild)
{
	// Das Bild wird zeilenweise gespeichert. 
	// Da die Zeilenlänge nicht konstant ist, wird für jede Zeile dynamisch Speicher angefordert 
	// und zwar genau so viel, wie für dieses Bild die Zeile lang ist.
	// Jedes Pixel belegt dabei sizeof(COLORREF) Bytes.

	// Da auch die Anzahl der Zeilen nicht konstant ist, werden die Zeilen als verkettete Liste geführt.
	// pBild->pBitmap zeigt auf das erste Listen(=Zeilen)-Element bestimmt also den Anfang der Liste.

	// Wir haben es hier also mit *zwei* dynamischen Strukturen zu tun, einmal der verketteten Liste der Zeilen
	// vom Typ TBmpZeilenElement und dann für jede Zeile einen Zeiger auf die Pixel dieser Zeile
	// TBmpZeilenElement.pPixelZeile.

	// Achten Sie darauf, dass Sie ein bisheriges Bild ggf erst wieder freigeben, bevor Sie ein neues Bild erzeugen.

	TBmpZeilenElement *pLast = NULL;

	loescheBild(pBild);										// eventuell vorhandes Bild löschen.

	pBild->breite = 400;
	pBild->hoehe = 400;

	for (int zeile = 0; zeile < pBild->hoehe; ++zeile)
	{
		// zerst eine neues Zeielen-Element anlegen
		TBmpZeilenElement *pZeile = (TBmpZeilenElement*)malloc(sizeof(TBmpZeilenElement));
		if (pZeile == NULL)
		{
			MessageBox(NULL, "kein Speicher mehr", "Fehler", MB_OK | MB_ICONERROR);
			return;
		}
		// verlinkung mit Nachfolger
		pZeile->next = pLast;
		pLast = pZeile;

		// jetzt für die Pixel dieser Zeile Speicher anfordern.
		pZeile->pPixelZeile = (COLORREF*)malloc(sizeof(COLORREF)*pBild->breite);
		if (pZeile->pPixelZeile == NULL)
		{
			MessageBox(NULL, "kein Speicher mehr", "Fehler", MB_OK | MB_ICONERROR);
			return;
		}
		// Die Pixel dieser Zeile mit einem bestimmten willkürlichen Muster füllen.
		for (int x = 0; x < pBild->breite; ++x)
		{
#define QUANTISIERER(x) ((((x)*32)/32) % 256)
			const int rotAnteil = QUANTISIERER(x + zeile);
			const int gruenAnteil = QUANTISIERER(zeile);
			const int blauAnteil = QUANTISIERER(x);

			const COLORREF pixel = RGB(rotAnteil, gruenAnteil, blauAnteil);
			pZeile->pPixelZeile[x] = pixel;
		}
	}

	pBild->pBitmap = pLast;
	strcpy_s(&pBild->dateiName[0], sizeof(pBild->dateiName), "<Testbild>");
}

// ============================================================================================================
void zeichnenBild(const HDC hdc, const TBild *pBild)
{
	int zeile = 0;
	TBmpZeilenElement *pZeile = pBild->pBitmap;

	while (pZeile != NULL)
	{
		const COLORREF *pPixel = pZeile->pPixelZeile;

		for (int x = 0; x < pBild->breite; ++x)
		{
			SetPixel(hdc, x, zeile, *pPixel);
			++pPixel;
		}

		++zeile;
		pZeile = pZeile->next;
		
	}
}

// ============================================================================================================
void loescheBild(TBild *pBild)
{
	TBmpZeilenElement *pAktZeile = pBild->pBitmap;

	while (pAktZeile != NULL)
	{
		// zuerst den Pixel Speicher für diese Zeile freigeben
		if (pAktZeile->pPixelZeile)
		{
			free(pAktZeile->pPixelZeile);
			pAktZeile->pPixelZeile = NULL;
		}

		// jetzt das Listenelement löschen
		{
			TBmpZeilenElement *pHilf = pAktZeile;
			pAktZeile = pAktZeile->next;
			free(pHilf);
		}
	}

	// zum Schluss das Bild "ausnullen".
	pBild->breite = 0;
	pBild->hoehe = 0;
	pBild->dateiName[0] = 0;
	pBild->pBitmap = NULL;
}

// ============================================================================================================
BOOL ladeDatei(const char *dateiName, TBild *pBild)
{
	FILE* Datei;
	TBitmapFileHeader *pFileHeader=NULL;
	TBitmapInfoHeader *pInfoHeader=NULL;
	TBmpZeilenElement* pZeilenElement=NULL;
	TBmpZeilenElement* pTemp = NULL;
	int gelesenebytes;
	int m;

	//Datei öffnen
	Datei = fopen(dateiName, "rb");
	if (Datei == NULL)
	{
		printf("Fehler beim %cffnen der Datei\n\n", 153);
		goto Fehler;
	}


	loescheBild(pBild);


	//Speicherallokation
	pFileHeader = (TBitmapFileHeader*)malloc(sizeof(TBitmapFileHeader));
	if (pFileHeader == NULL) {
		printf("Fehler! Unzureichende Speichermenge!\n\n");
		goto Fehler;
	}
	//Auslesen des ersten Headers in pFileHeader
	gelesenebytes = fread(pFileHeader, sizeof(TBitmapFileHeader), 1, Datei);
	if (gelesenebytes == 0) {
		free(pFileHeader);
		printf("Fehler beim Einlesen des ersten Headers.\n");
		goto Fehler;
	}


	//Speicherallokation
	pInfoHeader = (TBitmapInfoHeader*)malloc(sizeof(TBitmapInfoHeader));
	if (pInfoHeader == NULL) {
		printf("Fehler! Unzureichende Speichermenge!\n\n");
		goto Fehler;
	}
	//Auslesen des zweiten Headers in pInfoHeader
	gelesenebytes = fread(pInfoHeader, sizeof(TBitmapInfoHeader), 1, Datei);
	if (gelesenebytes == 0) {
		free(pInfoHeader);
		printf("Fehler beim Einlesen des zweiten Headers.\n");
		goto Fehler;
	}
	
	//Überprüfung der Parameter eines unterstützten Bilds
	if (pFileHeader->kKennung == 19778	//BM funktioniert nicht, 19778 ist stattdessen in allen BMP-Dateien bei mir
		&& pFileHeader->reserved1zero == NULL
		&& pInfoHeader->biSize == sizeof(TBitmapInfoHeader)
		&& pInfoHeader->biPlanes == 1
		&& pInfoHeader->biBitCount == 24
		&& pInfoHeader->biCompression == 0)
	{
		//Filepointer wird an den Beginn der Pixel gesetzt
		int lauf = fseek(Datei, pFileHeader->offsetInBytes, 0);
		if (lauf == -1) {
			printf("Fehler beim Datenzugriff per fseek\n\n");
			goto Fehler;
		}


		char *pixelZeile;
		int colorrefZeile;
		int zeilenBytes = pInfoHeader->biWidth * 3;
		while (zeilenBytes % 4 != 0)zeilenBytes++;

		//Speicherallokation Einlesepuffer
		pixelZeile = malloc(sizeof(char) * zeilenBytes);
		if (pixelZeile == NULL) {
			printf("Fehler! Unzureichender Speicher für Pixelpuffer!\n\n");
			goto Fehler;
		}

		//Berechnung Puffergröße für pBild
		colorrefZeile = pInfoHeader->biWidth * sizeof(COLORREF);


		//Pixel-Einleseschleife
		//Ließt zuerst zeilenweise die Pixel aus der Datei in dem Puffer pixelZeile ein, um diese Informationen dann in COLORREF umgewandelt in einer verketteten Liste abzuspeichern
		for (int i = 0; i < abs(pInfoHeader->biHeight); i++) 
		{
			//Speicherallokation Listenelement
			pZeilenElement = (TBmpZeilenElement*)malloc(colorrefZeile);
			if (pZeilenElement == NULL) {
				printf("Fehler! Unzureichender Speicher für Zeilenpuffer!\n\n");
				free(pixelZeile);
				goto Fehler;
			}
			//Verkettung
			pZeilenElement->next = pTemp;
			pTemp = pZeilenElement;

			//Einlesen der Pixel in den Pixelpuffer
			gelesenebytes=fread(pixelZeile, sizeof(char), zeilenBytes, Datei);
			if (gelesenebytes == NULL) {
				free(pixelZeile);
				free(pZeilenElement);
				goto Fehler;
			}

			//Speicherallokation pZeilenElement->pPixelZeile
			pZeilenElement->pPixelZeile = (COLORREF*)malloc(sizeof(COLORREF) * pInfoHeader->biWidth);
			if (pZeilenElement->pPixelZeile == NULL) {
				free(pixelZeile);
				free(pZeilenElement);
				goto Fehler;
			}
			m = 0;

			//Umwandeln der Pixel in COLORREF, Abspeichern in der Liste
			for (int k = 0; k < pInfoHeader->biWidth; k++)
			{
				const char blau = pixelZeile[m];
				const char gruen = pixelZeile[m + 1];
				const char rot = pixelZeile[m + 2];

				const COLORREF pixel = RGB(rot, gruen, blau);
				pZeilenElement->pPixelZeile[k] = pixel;
				m += 3;
			}
		}
		

		




		//Zuweisung der für pBild benötigten Daten, Spiegelung des Bildes wenn nötig
		pBild->breite = pInfoHeader->biWidth;
		pBild->hoehe = pInfoHeader->biHeight;
		pBild->pBitmap = pZeilenElement;
		if (pInfoHeader->biHeight< 0) {
			spiegelnBild(pBild);
		}
	}
	else {
		printf("Das Bild wird nicht unterst%ctzt.\n\n", 129);
		goto Fehler;
	}



	//Notfallabsicherung
	if (Datei != NULL) {
			goto Fehler;
	}
	if (pFileHeader != NULL) free(pFileHeader);
	if (pInfoHeader != NULL) free(pInfoHeader);
	return TRUE;

	//Fehlerfall: Die Datei wird geschlossen und die Funktion mit dem Rückgabewert FALSE beendet
	Fehler:
	if (Datei != NULL) fclose(Datei);
	if (pFileHeader!=NULL) free(pFileHeader);
	if (pInfoHeader != NULL) free(pInfoHeader);
	return FALSE;
}

// ============================================================================================================
void spiegelnBild(TBild *pBild)
{
	//Funktioniert alles prima!
	TBmpZeilenElement* pPuffer = pBild->pBitmap;
	TBmpZeilenElement* pNext = NULL;
	TBmpZeilenElement* pIterator=pPuffer;

	while (pIterator)
	{
		pPuffer = pPuffer->next;
		pIterator->next = pNext;
		pNext = pIterator;
		pIterator = pPuffer;
	}
	pBild->pBitmap = pNext;
	return;
}