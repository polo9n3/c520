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
	 
	 //spielfeld[4][6] = "2135";
	 
	 //printf("%i,%i", x_size, y_size);
	 
	 for (i=0; i<(x_size-1); i++){
		 for (j=0; j<(y_size-1); j++){
			 
			 printf("Feld %i/%i=%s\n",i,j, spielfeld[i][j]);
			 
			 
		if (spielfeld[i][j][0] != EOF){
			
		/*	if(spielfeld[i][j][0] == '0'){
				karte[2][1]=' ';
				karte[3][1]=' ';
				karte[4][1]=' ';
			}
			if(spielfeld[i][j][1] == '0'){
				karte[5][2]='+';
				karte[5][3]='+';
				karte[5][4]='+';
			}
			if(spielfeld[i][j][2] == '0'){
				karte[3][5]='+';
				karte[3][4]='+';
				karte[3][3]='+';
			}
			if(spielfeld[i][j][3] == '0'){
				karte[1][3]='+';
				karte[2][3]='+';
				karte[3][3]='+';
			}
			*/
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
			
			/*for (k=0; k<7; k++){
				for (l=0; l<7; l++){
					printf("%c", karte[i][j]);
				}
				printf("\n");
			}*/
		}
		}
	 }
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
