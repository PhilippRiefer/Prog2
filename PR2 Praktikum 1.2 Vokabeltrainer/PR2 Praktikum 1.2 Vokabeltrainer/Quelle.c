/*****************************************
PRP2 Aufgabe 1.2
Vokabeltrainer
Autor:				Domenic Heidemann & Maxim Eigenser
Erstellungsdatum:	5.10.19
Fertigstellung:		9.10.19
******************************************/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define MAXLEN 80
#define MAXVOKABELN 10

//=================================================================================================================================================================================================

void main(void)
{
	char englisch[MAXVOKABELN][MAXLEN] = { "car", "tree", "book", "pencil", "bottle", "beeflabelingmonitoringdelegationact", "plant", "paper", "red", "blue"};
	char deutsch[MAXVOKABELN][MAXLEN] = { "Auto", "Baum", "Buch", "Bleistift", "Flasche", "Rindfleischetikettierungsueberwachungsaufgabenuebertragunsgesetz", "Pflanze", "Papier", "rot", "blau"};
	int abgleich[MAXVOKABELN] = { 0 };
	int lf = 0;			//Laufvariable Schleife
	int voklf = 0;		//Laufvariable abgefrage Vokabeln (Hilfreich zum Fehlererkennen)
	int felf = 0;		//Laufvariable Fehler
	int zw;				//Zufallswert
	char eingabe[MAXLEN];

	srand((int)time(NULL));	

	printf("VOKABEL-TRAINER");

	for (lf = 0; lf < MAXVOKABELN; lf++)				//Schleife, die bis zum Vokabellimit läuft
	{
		zw = rand() % MAXVOKABELN;						//Zufallswert wird generiert

		if (abgleich[zw] == 0) {						//Überprüfung, ob die Vokabel schon einmal abgefragt wurde

			printf("\nWas heisst \"%s\" auf englisch? : ", deutsch[zw]);
			scanf("%s", &eingabe);

			if (strcmp(eingabe, englisch[zw]) == 0) {	 //Überprüfung, ob die Eingabe der Lösung im Array entspricht
				printf("Richtig!");
				voklf++;
				abgleich[zw]++;							//Vokabel wird im Abgleichsarray als benutzt markiert
			}

			else {
				printf("Falsch! Die richtige Anwort lautet: ""%s""", englisch[zw]);
				voklf++;
				felf++;
				abgleich[zw]++;		//entfernbar, wenn man falsch beantwortete Vokabeln im Fragepool behalten will
			}
		}
		else lf--; //Notwendig, da sonst nicht 10 Vokabeln abgefragt werden, da bei doppelten Vokabeln trotzdem lf hochgezählt würde
	}

	printf("\n\nDu hast %d Fehler gemacht bei insgesamt %d Vokabeln.\n\n", felf, voklf);

	system("pause");
}