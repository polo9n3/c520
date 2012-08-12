/*
 * test.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

int n	= 1;
int m	= 1;
int x_size	= 0;
int y_size  = 0;

typedef struct karte {
	char code[4];
	char bild[56];
	struct karte * next;
	struct karte * previous;
} KARTE;

int karte[7][7];

char *** generiereSpielfeld(int x, int y);
void fuelleSpielfeld(char code[], int xpos, int ypos, char ***feld);
void zeichneSpielfeld(char ***feld);
void freeSpielfeld(char ***feld);
void berechneKoordinaten(int x_koor, int y_koor, int card[7][7], int output[x_size*7][y_size*7]);
char *** karteEinfuegen(char *co, char ***feld);



int main(int argc, char **argv)
{
	char ***spielfeld = generiereSpielfeld(n, m);
	fuelleSpielfeld("2101", 0, 0, spielfeld);
	zeichneSpielfeld(spielfeld);
	spielfeld = karteEinfuegen("0011", spielfeld);
	zeichneSpielfeld(spielfeld);
	
	return 0;
}


/***********************************************************************
 * 		Reserviert den Speicher für das Spielfeld
 **********************************************************************/

char *** generiereSpielfeld(int x, int y)
{
	int i = 0;
	int j = 0;
	x_size	= x;
	y_size	= y;
	char ***spielfeld;
	//Versuche Speicher für Spielfeld zu reservieren
	spielfeld	= malloc((x_size)*sizeof(char*));
	if(spielfeld == NULL) 
	{
		//Falls kein Speicher reserviert werden konnte, gebe Meldung aus und breche das Programm sofort ab
		printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
		exit(0);
	}else
	{
		for(i=0; i<x_size; i++)
		{
			spielfeld[i]	= malloc((y_size)*sizeof(char*));
			if(spielfeld[i] == NULL)
			{
				//Falls kein Speicher reserviert werden konnte, gib Meldung aus und breche das Programm sofort ab
				printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
				exit(0);
			}else
			{
				for(j=0; j<y_size; j++)
				{
					spielfeld[i][j] = malloc(sizeof(char[4]));
				}
			}
		}
		//Alle Elemente Nullen
		i=0;
		j=0;
		for(i=0; i<x_size; i++)
		{
			if(spielfeld != NULL)
			{
				for(j=0; j<y_size; j++)
				{
					spielfeld[i][j][0] = '3';
					spielfeld[i][j][1] = '3';
					spielfeld[i][j][2] = '3';
					spielfeld[i][j][3] = '3';
					spielfeld[i][j][4] = '\0';
				}
			}
		}
	}
	return spielfeld;
}

/***********************************************************************
 * 		Füllt das Spielfeld mit den Codes
 **********************************************************************/

void fuelleSpielfeld(char code[4], int xpos, int ypos, char ***feld)
{

	
	if(feld == NULL){
		printf("Fehler beim Spielfeld\n");
		exit(0);
	}
	feld[xpos][ypos][0]=code[0];
	feld[xpos][ypos][1]=code[1];
	feld[xpos][ypos][2]=code[2];
	feld[xpos][ypos][3]=code[3];
	feld[xpos][ypos][4]='\0';
	
}

void zeichneSpielfeld(char ***feld)
{
	/*
	 * Hier wird dann das Spielfeld gezeichnet
	 */
	 int i=0;
	 int j=0;
	 int k=0;
	 int l=0;
	 int card[7][7];
	 int ausgabe[x_size*7][y_size*7];
	 int pups1 = 0, pups2 = 0;
	 
	 
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
							 card[pups1][pups2] = ' ';
						 }
					 }
					 
	
			 
			 printf("Feld %i/%i=%s hinzugefügt\n",i,j, feld[i][j]);
			 
			 
		if (feld[i][j][0] != EOF){
			
			if(strcmp(feld[i][j], "3333")==0){
				for (k=0; k<7; k++){
					for (l=0; l<7; l++){
						card[k][l]=' ';
					}
				}
			}else{
				for (k=0; k<7; k++){
					card[k][0]='-';
					card[k][6]='-';
				}
				for (k=1; k<6; k++){
				card[0][k]='|';
				card[6][k]='|';
				}
			}
			
			//Straße
			
			 if(feld[i][j][0] == '1'){
				card[3][1]='+';
				card[3][2]='+';
				card[3][3]='+';
			}
			if(feld[i][j][1] == '1'){
				card[5][3]='+';
				card[4][3]='+';
				card[3][3]='+';
			}
			if(feld[i][j][2] == '1'){
				card[3][5]='+';
				card[3][4]='+';
				card[3][3]='+';
			}
			if(feld[i][j][3] == '1'){
				card[1][3]='+';
				card[2][3]='+';
				card[3][3]='+';
			}
			
			//Stadt
			
			if(feld[i][j][0] == '2'){
				card[1][1]='x';
				card[2][2]='x';
				card[3][2]='x';
				card[4][2]='x';
				card[5][1]='x';
			}
			
		if(feld[i][j][1] == '2'){
			if(card[5][1] == 'x'){
				card[5][1] = ' ';
			}else card[5][1] = 'x';
			
			if(card[4][2] == 'x'){
				card[4][2] = ' ';
			}else card[4][2] = 'x';
			
			card[4][3]='x';
			card[4][4]='x';
			card[5][5]='x';

			}
			
		if(feld[i][j][2] == '2'){
			if(card[5][5] == 'x'){
				card[5][5] = ' ';
			}else card[5][5] = 'x';
			
			if(card[4][4] == 'x'){
				card[4][4] = ' ';
			}else card[4][4] = 'x';
			
			card[3][4]='x';
			card[2][4]='x';
			card[1][5]='x';
			}
			
		if(feld[i][j][3] == '2'){
			if(card[1][5] == 'x'){
				card[1][5] = ' ';
			}else card[1][5] = 'x';
			
			if(card[2][4] == 'x'){
				card[2][4] = ' ';
			}else card[2][4] = 'x';
			
			if(card[1][1] == 'x'){
				card[1][1] = ' ';
			}else card[1][1] = 'x';
			
			if(card[2][2] == 'x'){
				card[2][2] = ' ';
			}else card[2][2] = 'x';
			
			card[2][3]='x';
			}
			
			
			berechneKoordinaten(i,j,card,ausgabe);
			
			
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
 
 /**********************************************************************
  * 		Berechnet die Position der nächsten Karte
  *********************************************************************/

char *** karteEinfuegen(char *co, char ***feld)
{
	int i,j,k;
	int breite = m+2;
	int hoehe = n+2;
	char ***ausgabe;
	char ***feldGross = generiereSpielfeld(hoehe,breite);

	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			feldGross[i+1][j+1]=feld[i][j];
		}
	}
	ausgabe = feldGross;
	
/**
 * 	Wenn eine Reihe nicht genutzt wird, wird sie gelöscht
 */
	j=0;
	for(i=0; i<breite; i++){
		if(strcmp(feldGross[0][i],"3333") != 0){
			j++;
		}
	}
	k=0;
	for(i=0; i<hoehe; i++){
		if(strcmp(feldGross[i][0],"3333") != 0){
			k++;
		}
	}
	if (j==0){	
		hoehe-=1;
		char ***feldKleiner = generiereSpielfeld(hoehe,breite);	
		for(i=0; i<m+2; i++){
			for(j=1; j<n+2; j++){
				//feldKleiner[i][j-1]=feldGross[i][j];
			}
		}
			ausgabe = feldKleiner;
	}
	if (k==0){	
		breite-=1;
		char ***feldKleiner = generiereSpielfeld(hoehe,breite);	
		for(i=0; i<breite; i++){
			for(j=0; j<hoehe; j++){
				//feldKleiner[i][j]=feldGross[i+1][j];
			}
		}
			ausgabe = feldKleiner;
	}	

	return ausgabe;
}

/***********************************************************************
 * 		Gibt das gesamte Spielfeld frei
 **********************************************************************/

void freeSpielfeld(char ***feld)
{
	int k = 0;
	int p = 0;
	for(k=0; k<(x_size-1);k++)
	{
		for(p=0; p<(y_size-1); p++)
		{
			free(feld[k][p]);
		}
		free(feld[k]);
	}
	free(feld);
}
