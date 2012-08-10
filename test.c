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

typedef struct karte {
	char code[4];
	char bild[56];
	struct karte * next;
	struct karte * previous;
} KARTE;

int karte[7][7];

void generiereSpielfeld(int x, int y);
void fuelleSpielfeld(char code[], int xpos, int ypos);
void zeichneSpielfeld(void);
void freeSpielfeld(void);
void berechneKoordinaten(int x_koor, int y_koor, int card[7][7], int output[x_size*7][y_size*7]);




int main(int argc, char **argv)
{
	generiereSpielfeld(n, m);
	fuelleSpielfeld("2110", 0, 0);
	fuelleSpielfeld("1020", 0, 1);
	fuelleSpielfeld("2101", 0, 2);
	fuelleSpielfeld("2101", 0, 3);
	fuelleSpielfeld("2101", 0, 4);
	fuelleSpielfeld("2101", 2, 5);
	fuelleSpielfeld("2101", 4, 0);
	fuelleSpielfeld("2101", 3, 0);
	fuelleSpielfeld("2101", 2, 0);
	fuelleSpielfeld("2101", 1, 0);
	fuelleSpielfeld("2220", n-1, m-1);
	zeichneSpielfeld();
	freeSpielfeld();
	
	return 0;
}

/***********************************************************************
 * 		Reserviert den Speicher für das Spielfeld
 **********************************************************************/

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
		//Alle Elemente Nullen
		i=0;
		j=0;
		int s = 0;
		for(i=0; i<x; i++)
		{
			if(spielfeld != NULL)
			{
				for(j=0; j<y; j++)
				{
					for(s=0; s<4; s++)
					{
						spielfeld[i][j][s] = '0';
					}
				}
			}
		}
	}
}

/***********************************************************************
 * 		Füllt das Spielfeld mit den Codes
 **********************************************************************/

void fuelleSpielfeld(char code[], int xpos, int ypos)
{
	if(spielfeld == NULL){
		printf("Fehler beim Spielfeld\n");
	}
	spielfeld[xpos][ypos][0]=code[0];
	spielfeld[xpos][ypos][1]=code[1];
	spielfeld[xpos][ypos][2]=code[2];
	spielfeld[xpos][ypos][3]=code[3];
}

void zeichneSpielfeld(void)
{
	/*
	 * Hier wird dann das Spielfeld gezeichnet
	 */
	 int i=0;
	 int j=0;
	 int k=0;
	 int l=0;
	 int karte[7][7];
	 int ausgabe[x_size*7][y_size*7];
	 int pups1 = 0, pups2 = 0;
	 

	 //spielfeld[4][6] = "2135";
	 
	 printf("%i,%i", x_size, y_size);
	 
	 for (k=0; k<x_size*7; k++){
		for (l=0; l<y_size*7; l++){
			ausgabe[k][l] = ' ';
		}
	 }
	 
	for (i=0; i<x_size; i++){
		 for (j=0; j<y_size; j++){
			 
			 	 for(pups1=0;pups1<7;pups1++)
					 {
						 for(pups2=0;pups2<7;pups2++)
						 {
							 karte[pups1][pups2] = ' ';
						 }
					 }
					 
	
			 
			 printf("Feld %i/%i=%s hinzugefügt\n",i,j, spielfeld[i][j]);
			 
			 
		if (spielfeld[i][j][0] != EOF){
			
			if(strcmp(spielfeld[i][j], "0000")==0){
				for (k=0; k<7; k++){
					for (l=0; l<7; l++){
						karte[k][l]=' ';
					}
				}
			}else{
				for (k=0; k<7; k++){
					karte[k][0]='-';
					karte[k][6]='-';
				}
				for (k=1; k<6; k++){
				karte[0][k]='|';
				karte[6][k]='|';
				}
			}
			
			//Straße
			
			 if(spielfeld[i][j][0] == '1'){
				karte[3][1]='+';
				karte[3][2]='+';
				karte[3][3]='+';
			}
			if(spielfeld[i][j][1] == '1'){
				karte[5][3]='+';
				karte[4][3]='+';
				karte[3][3]='+';
			}
			if(spielfeld[i][j][2] == '1'){
				karte[3][5]='+';
				karte[3][4]='+';
				karte[3][3]='+';
			}
			if(spielfeld[i][j][3] == '1'){
				karte[1][3]='+';
				karte[2][3]='+';
				karte[3][3]='+';
			}
			
			//Stadt
			
			if(spielfeld[i][j][0] == '2'){
				karte[1][1]='x';
				karte[2][2]='x';
				karte[3][2]='x';
				karte[4][2]='x';
				karte[5][1]='x';
			}
			
		if(spielfeld[i][j][1] == '2'){
			if(karte[5][1] == 'x'){
				karte[5][1] = ' ';
			}else karte[5][1] = 'x';
			
			if(karte[4][2] == 'x'){
				karte[4][2] = ' ';
			}else karte[4][2] = 'x';
			
			karte[4][3]='x';
			karte[4][4]='x';
			karte[5][5]='x';

			}
			
		if(spielfeld[i][j][2] == '2'){
			if(karte[5][5] == 'x'){
				karte[5][5] = ' ';
			}else karte[5][5] = 'x';
			
			if(karte[4][4] == 'x'){
				karte[4][4] = ' ';
			}else karte[4][4] = 'x';
			
			karte[3][4]='x';
			karte[2][4]='x';
			karte[1][5]='x';
			}
			
		if(spielfeld[i][j][3] == '2'){
			if(karte[1][5] == 'x'){
				karte[1][5] = ' ';
			}else karte[1][5] = 'x';
			
			if(karte[2][4] == 'x'){
				karte[2][4] = ' ';
			}else karte[2][4] = 'x';
			
			if(karte[1][1] == 'x'){
				karte[1][1] = ' ';
			}else karte[1][1] = 'x';
			
			if(karte[2][2] == 'x'){
				karte[2][2] = ' ';
			}else karte[2][2] = 'x';
			
			karte[2][3]='x';
			}
			
			
			berechneKoordinaten(i,j,karte,ausgabe);
			
			
		}
		}
		
		
	 }
	 for (k=0; k<y_size*7; k++){
				for (l=0; l<x_size*7; l++){
					printf("%c", (char)ausgabe[l][k]);
				}
				printf("\n");
			}
}

/***********************************************************************
 * 		Berechnet die Position jedes char im Ausgabe-Array
 **********************************************************************/
 void berechneKoordinaten(int x_koor, int y_koor, int card[7][7], int output[x_size*7][y_size*7])
 {
	 int i, j;
	 int abzugX = 0;
	 int abzugY = 0;
		
		if(x_koor>0){
			abzugX=x_koor;
		}
		if(y_koor>0){
			abzugY=y_koor;
		}
	 
		 for (i=0; i<7; i++){
			 for (j=0; j<7; j++){
				 if (output[i+x_koor*7-abzugX][j+y_koor*7-abzugY] == '-') 
				 {
						card[i][j] = '-';
				 }
				 if (output[i+x_koor*7-abzugX][j+y_koor*7-abzugY] == '|')
				 {
					 card[i][j] = '|';
				 }
				 output[i+x_koor*7-abzugX][j+y_koor*7-abzugY]=card[i][j];
			 }
			 
		 }
		 return;
 }

/***********************************************************************
 * 		Gibt das gesamte Spielfeld frei
 **********************************************************************/

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
