/*
 * test.c

 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

char **spielfeld;
int n	= 5;
int m	= 6;
int i = 0;


int main(int argc, char **argv)
{
	generiereSpielfeld(n, m);
	fuelleSpielfeld("2110", 0, 0);
	fuelleSpielfeld("1030", 0, 1);
	fuelleSpielfeld("2220", n, m);
	zeichneSpielfeld(spielfeld);
	free(spielfeld);
	
	return 0;
}

void generiereSpielfeld(int x, int y)
{
	//Versuche Speicher für Spielfeld zu reservieren
	spielfeld	= malloc((x+1)*sizeof(char[4]));
	if(spielfeld == NULL) 
	{
		//Falls kein Speicher reserviert werden konnte, gebe Meldung aus und breche das Programm sofort ab
		printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
		exit(0);
	}else
	{
		for(i=0; i<(x+1); i++)
		{
			spielfeld[i]	= malloc((y+1)*sizeof(char[4]));
			if(spielfeld[i] == NULL)
			{
				//Falls kein Speicher reserviert werden konnte, gib Meldung aus und breche das Programm sofort ab
				printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
				exit(0);
			}
		}
	}
}

void fuelleSpielfeld(char code[], int xpos, int ypos)
{
	if(spielfeld == NULL){
		printf("Fehler beim Spielfeld\n");
	}
	printf("%d\n", sizeof(char[4]));
	printf("%d\n", sizeof((char*)spielfeld));
	strcpy(spielfeld[xpos][ypos], code);
	
	printf("Spielfeld gefüllt! Data: %s\n", spielfeld[xpos][ypos]);
	
}

void zeichneSpielfeld(char **feld)
{
	printf("Der Befehl zum Zeichnen des Spielfeldes wurde entgegen genommen\n");
	printf("%s\n", spielfeld[0][0]);
	printf("Der Befehl zum Zeichnen des Spielfeldes wurde entgegen genommen\n");
	printf("%s\n", feld[0][1]);
	printf("Der Befehl zum Zeichnen des Spielfeldes wurde entgegen genommen\n");
	printf("%s\n", feld[n][m]);
}


