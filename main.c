/*
 * main.c
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

void kartenErstellen(void);
void spielen(char datei[]);

/***********************************************************************
 * 		Variablendeklaration Global			       					   *
 **********************************************************************/
	char *startwert;
	int anzahl;
	char *file;
	int i,j,k;

int main(int argc, char **argv){
	
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
   
/*
 * Karten erstellen
 */

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
	int karte[7][7];
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
				karte[j][k]=' ';
			}
		}
		
		for (j=0; j<7; j++){
			karte[j][0]='-';
			karte[j][6]='-';
		}
		for (j=1; j<6; j++){
			karte[0][j]='|';
			karte[6][j]='|';
		}
			if(code[0] == '1'){
				karte[3][1]='+';
				karte[3][2]='+';
				karte[3][3]='+';
			}
			if(code[1] == '1'){
				karte[5][3]='+';
				karte[4][3]='+';
				karte[3][3]='+';
			}
			if(code[2] == '1'){
				karte[3][5]='+';
				karte[3][4]='+';
				karte[3][3]='+';
			}
			if(code[3] == '1'){
				karte[1][3]='+';
				karte[2][3]='+';
				karte[3][3]='+';
			}
		
		//Stadt
		
		if(code[0] == '2'){
				karte[1][1]='x';
				karte[2][2]='x';
				karte[3][2]='x';
				karte[4][2]='x';
				karte[5][1]='x';
			}
			
		if(code[1] == '2'){
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
			
		if(code[2] == '2'){
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
			
		if(code[3] == '2'){
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
		
		for (j=0; j<7; j++){
			for (k=0; k<7; k++){
				fprintf (ausgabe, "%c", karte[k][j]);
			}
			fprintf (ausgabe, "\n");
		}
		
		
		
	}
	
		printf("Die Karten wurden in %s gespeichert.\n", file);
		fclose (ausgabe);
	
	
	
	free(p);
	
}
/***********************************************************************
 * 				Das Spiel
 **********************************************************************/

void spielen(char datei[]){
	FILE *eingabe;
	char *p = malloc(anzahl * 4 * sizeof(int)); 
	char code[4];
	
	eingabe = fopen(datei, "r");
	
	char c;
	int zeilenanzahl=1;
	while ((c=getc(eingabe))!=EOF)
	if (c=='\n') {zeilenanzahl++;}
		printf("%d\n",  zeilenanzahl);
	
	anzahl = (int)zeilenanzahl/8;
	
	printf("%i\n", anzahl);
	
	
	for (i=0; i<anzahl; i++){
		 fseek(eingabe,(long) 5+i*66, SEEK_SET);
		 
			 code[0] = getc(eingabe);
			 code[1] = getc(eingabe);
			 code[2] = getc(eingabe);
			 code[3] = getc(eingabe);
			 
			 printf("Code: %s\n", code);

	}
	
	free(p);
}
