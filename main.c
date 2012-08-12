/*
 * main.c
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

/***********************************************************************
 * 			Typdeklaration
 **********************************************************************/

typedef struct karte {
	char code[4];
	char bild[56];
	struct karte * next;
} KARTE;


void kartenErstellen(void);
void spielen(char datei[]);
void push(char *co, char *bi);
KARTE * pop(void);

/***********************************************************************
 * 		Variablendeklaration Global			       					   *
 **********************************************************************/
	char *startwert;
	int anzahl;
	char *file;
	KARTE *pos = NULL;
	KARTE *next = NULL;
	KARTE *anfang = NULL;
	//char ***spielfeld = NULL;
	int x_size	= 0;
	int y_size  = 0;


char *** generiereSpielfeld(int x, int y);
void fuelleSpielfeld(char code[], int xpos, int ypos, char ***feld);
void zeichneSpielfeld(char ***feld);
void freeSpielfeld(char ***feld);
void berechneKoordinaten(int x_koor, int y_koor, int card[7][7], int output[x_size*7][y_size*7]);
char *** karteEinfuegen(char *co, char ***feld);

/***********************************************************************
 * 			Carcassonne
 **********************************************************************/


int main(int argc, char **argv){
	
	int i,j;
	
	if (argc > 5){
	   printf("Es wurden zu viele Parameter übergeben.\n");
	   return 1;
	}
	else {
		if(argc > 1){
			
			for(i=0; i < argc; i++) {
				printf("argv[%d] = %s", i, argv[i]);
				printf("\n");
			}

			if(strcmp(argv[1], "creation") == 0){
			
				if(argc == 5){
					
					//Prüfe, ob der Key genau 9 Zeichen hat
					if(strlen(argv[3]) == 9){
						//Lese Parameter ein
						
						//file[] = argv[2]
						file = malloc(sizeof(char[strlen(argv[2])]));
						for(i=0; i < strlen(argv[2]); i++){
							file[i] = argv[2][i];
						}
						
						//startwert[] = argv[3];
						startwert = malloc(sizeof(char[strlen(argv[3])]));
						for(j=0; j < strlen(argv[3]); j++){
							startwert[j] = argv[3][j];
						}
						anzahl		= atoi(argv[4]);
						printf("Argumente erfolgreich eingelesen!\n");
						
						//Erstelle Karten
						kartenErstellen();	
						
					}else{
						
						printf("Der übergeben Key hatte nicht genau 9 Zeichen!\n");
						
					}
				
				}else{
					
					printf("Für die Funktion 'creation' werden insgesamt 4 Parameter benötigt!\n");
					
				}
			
			}else if(strcmp(argv[1], "play") == 0){
				
				if(argc == 3){
					//Lese Parameter ein
					//file[]	= argv[2];
					file = malloc(sizeof(char[strlen(argv[2])]));
					for(i=0; i < strlen(argv[2]); i++){
						file[i] = argv[2][i];
					}
					//play
					spielen(file);
					
				}else{
					
					printf("Für die Funktion 'play' werden genau 2 Parameter benötigt!\n");
					
				}
				
			}
			
		}else{
			
			//Keine Parameter übergeben
			printf("Es wurden keine Parameter übergeben!\n");
			return 1;
		
	}

   free(file);
   free(startwert);
   
	return 0;
}
}

/***********************************************************************
 * 		Karten erstellen
 **********************************************************************/
  
void kartenErstellen(void){
	int schluesselgroesse = anzahl*4;		//Die Größe des Schlüssels
	int *p = malloc(schluesselgroesse * sizeof(char[4]));
	char code[4];
	char kette[schluesselgroesse];
	FILE *ausgabe;
	int card[7][7];
	int i,j,k;
	for (i=0; i<schluesselgroesse; i++){
		kette[i] = startwert[i%9];
	}

	for (i=0; i<schluesselgroesse; i++){
		
			if (kette[i] == '0' || kette[i] == '1' || kette[i] == '2'){
				p[i]='0';
			}
			else if (kette[i] == '3' || kette[i] == '4' || kette[i] == '5' || kette[i] == '6'){
				p[i]='1';
			}
			else if (kette[i] == '7' || kette[i] == '8' || kette[i] == '9'){
				p[i]='2';
			}
			
	}

		ausgabe = fopen (file, "w");
		if (ausgabe == NULL){
			printf("Fehler beim öffnen der Datei.\n");
			exit(0);
		}

		
	for (i=0; i<schluesselgroesse; i+=4){
		
		
		fprintf (ausgabe, "Code:");
		
		for(j=0; j<4; j++){
				code[j]=p[i+j];
		}
		fprintf (ausgabe, "%s\n", code);
		
//		Karten Zeichenen
		
		for (j=0; j<7; j++){
			for (k=0; k<7; k++){
				card[j][k]=' ';
			}
		}
		
		for (j=0; j<7; j++){
			card[j][0]='-';
			card[j][6]='-';
		}
		for (j=1; j<6; j++){
			card[0][j]='|';
			card[6][j]='|';
		}
			if(code[0] == '1'){
				card[3][1]='+';
				card[3][2]='+';
				card[3][3]='+';
			}
			if(code[1] == '1'){
				card[5][3]='+';
				card[4][3]='+';
				card[3][3]='+';
			}
			if(code[2] == '1'){
				card[3][5]='+';
				card[3][4]='+';
				card[3][3]='+';
			}
			if(code[3] == '1'){
				card[1][3]='+';
				card[2][3]='+';
				card[3][3]='+';
			}
		
		//Stadt
		
		if(code[0] == '2'){
				card[1][1]='x';
				card[2][2]='x';
				card[3][2]='x';
				card[4][2]='x';
				card[5][1]='x';
			}
			
		if(code[1] == '2'){
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
			
		if(code[2] == '2'){
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
			
		if(code[3] == '2'){
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
		
		for (j=0; j<7; j++){
			for (k=0; k<7; k++){
				fprintf (ausgabe, "%c", card[k][j]);
			}
			fprintf (ausgabe, "\n");
		}
		
		
		
	}
	
		printf("Die Karten wurden in %s gespeichert.\n", file);
		fclose (ausgabe);
	
	
	//	Und alles wieder frei geben
	free(p);
	
}
/***********************************************************************
 * 				Das Spiel
 **********************************************************************/

void spielen(char datei[]){
	FILE *eingabe;
	char code[4];
	char bild[56];
	int i,j;
	
	eingabe = fopen(datei, "r");
	
	char c;
	int zeilenanzahl=1;
	while ((c=getc(eingabe))!=EOF)
	if (c=='\n') {zeilenanzahl++;}
	
	anzahl = (int)zeilenanzahl/8;
	
	KARTE *p;
	char ***feld;
	
	
	for (i=0; i<anzahl; i++){
		 fseek(eingabe,(long) 5+i*66, SEEK_SET);
		 
			 code[0] = getc(eingabe);
			 code[1] = getc(eingabe);
			 code[2] = getc(eingabe);
			 code[3] = getc(eingabe);
			 code[4] = '\0';
			 
			 
			 fseek(eingabe,(long) 10+i*66, SEEK_SET);
			 
			 for (j=0; j<55; j++){
				bild[j] = getc(eingabe);
			 }
/**
 * 		Karten auf den Stack legen
 */
			 //printf("%s\n%s\n", code, bild);
			 push(code, bild);
	}
	

//	
//	Hier muss noch unsere Überprüfung hin, wo die neue Karte hin gelegt werden soll
//	und gegebenenfalls das alte Array in das neue Übertragen werden
//

/**
 * 		Legen der Startkarte
 */

		feld = generiereSpielfeld(1, 1);
		fuelleSpielfeld("2101", 0, 0, feld);
		zeichneSpielfeld(feld);
		
	for (i=0; i<anzahl; i++){


		p = pop();
		
		//printf("Vor:%s\n", p->code);
		
		for(j=0; j<4; j++){
			code[j] = p->code[j];
		}
				
		//printf("Nach:%s\n", code);
		

		//feld = karteEinfuegen(p->code, feld);
		//feld = generiereSpielfeld(1, 1);
		fuelleSpielfeld(code, 0, 0, feld);
		zeichneSpielfeld(feld);
		
	}
	
	freeSpielfeld(feld);
}

/***********************************************************************
 * 		Push-Funktion für den Stack
 **********************************************************************/

void push(char *co, char *bi)
{
	if (anfang == NULL){
		anfang = (KARTE *) malloc(sizeof(KARTE));
		pos = anfang;
		pos->next = NULL;
	}else{
		next = pos;
		pos = (KARTE *) malloc(sizeof(KARTE));
		pos->next = next;
	}
	if (pos == NULL) {
		fprintf(stderr, "Kein Speicherplatz vorhanden für neues Element\n");
		exit(0);
	}
	strcpy(pos->code, co);
	//printf("Neu in der Liste:%s\n", pos->code);
	strcpy(pos->bild, bi);
	//printf("Neu in der Liste:\n%s\n", pos->bild);
}

/***********************************************************************
 * 		Pop-Funktion für de Stack. Gibt KARTE zurück
 **********************************************************************/

KARTE * pop(void){
	
	KARTE * temp = NULL;
	//printf("Hole eine karte vom Stack\n");
	
    if (anfang == NULL){
		printf("Die Liste ist Leer");
	}
	else{
		temp = pos;
		free(pos);
		pos = temp->next;
	}
			return temp;
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
					spielfeld[i][j][0] = '0';
					spielfeld[i][j][1] = '0';
					spielfeld[i][j][2] = '0';
					spielfeld[i][j][3] = '0';
					spielfeld[i][j][4] = '\0';
				}
			}
		}
	}
	//zeichneSpielfeld(spielfeld);
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
	 
	 
	 //printf("%i,%i", x_size, y_size);
	 
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
			
			if(strcmp(feld[i][j], "0000")==0){
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
	int breite = y_size+2;
	int hoehe = x_size+2;
	char ***ausgabe;
	char ***feldGross = generiereSpielfeld(hoehe,breite);

	for(i=0; i<x_size; i++){
		for(j=0; j<y_size; j++){
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
		for(i=0; i<x_size+2; i++){
			for(j=1; j<y_size+2; j++){
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

