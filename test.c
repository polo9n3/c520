/*
 * test.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

char ***spielfeld;
int n	= 5;
int m	= 6;
int x_size	= 0;
int y_size  = 0;

void generiereSpielfeld(int x, int y);
void fuelleSpielfeld(char code[], int xpos, int ypos);
void zeichneSpielfeld(void);
void freeSpielfeld(void);



int main(int argc, char **argv)
{
	generiereSpielfeld(n, m);
	fuelleSpielfeld("2110", 0, 0);
	fuelleSpielfeld("1030", 0, 1);
	fuelleSpielfeld("2220", n-1, m-1);
	zeichneSpielfeld();
	freeSpielfeld();
	
	return 0;
}

void generiereSpielfeld(int x, int y)
{
	int i = 0;
	int j = 0;
	x_size	= x;
	y_size	= y;
	//Versuche Speicher für Spielfeld zu reservieren
	spielfeld	= malloc((x)*sizeof(char*));
	if(spielfeld == NULL) 
	{
		//Falls kein Speicher reserviert werden konnte, gebe Meldung aus und breche das Programm sofort ab
		printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
		exit(0);
	}else
	{
		for(i=0; i<x; i++)
		{
			spielfeld[i]	= malloc((y)*sizeof(char*));
			if(spielfeld[i] == NULL)
			{
				//Falls kein Speicher reserviert werden konnte, gib Meldung aus und breche das Programm sofort ab
				printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
				exit(0);
			}else
			{
				for(j=0; j<y; j++)
				{
					spielfeld[i][j] = malloc(sizeof(char[4]));
				}
			}
		}
	}
}

void fuelleSpielfeld(char code[], int xpos, int ypos)
{
	if(spielfeld == NULL){
		printf("Fehler beim Spielfeld\n");
	}
	strcpy(spielfeld[xpos][ypos], code);
}

void zeichneSpielfeld(void)
{
	/*
	 * Hier wird dann das Spielfeld gezeichnet
	 * */
	 spielfeld[4][6] = "2135";
}

void freeSpielfeld(void)
{
	int k = 0;
	int p = 0;
	for(k=0; k<(x_size-1);k++)
	{
		for(p=0; p<(y_size-1); p++)
		{
			free(spielfeld[k][p]);
		}
		free(spielfeld[k]);
	}
	free(spielfeld);
}
