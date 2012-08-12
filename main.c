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

typedef struct card {
	char code[4];
	char pic[56];
	struct card * next;
} CARD;


void creatCard(void);
void play(char file[]);
void push(char *co, char *pic);
CARD * pop(void);

/***********************************************************************
 * 		Variablendeklaration Global			       					   *
 **********************************************************************/
	char *start;
	int number;
	char *file;
	CARD *pos = NULL;
	CARD *next = NULL;
	CARD *begin = NULL;
	int x_size	= 0;
	int y_size  = 0;


char *** creatField(int x, int y);
void fillField(char code[], int xpos, int ypos, char ***field);
void drawField(char ***field);
void freeField(char ***field);
void drawCard(int x_koor, int y_koor, int card[7][7], int output[x_size*7][y_size*7]);
char *** fillInCard(char *co, char ***field);

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
					
					if(strlen(argv[3]) == 9){
						//Read Parameter
						
						//file[] = argv[2]
						file = malloc(sizeof(char[strlen(argv[2])]));
						for(i=0; i < strlen(argv[2]); i++){
							file[i] = argv[2][i];
						}
						
						start = malloc(sizeof(char[strlen(argv[3])]));
						for(j=0; j < strlen(argv[3]); j++){
							start[j] = argv[3][j];
						}
						number		= atoi(argv[4]);
						printf("Argumente erfolgreich eingelesen!\n");
						
						//Creat the cards
						creatCard();	
						
					}else{
						
						printf("Der übergeben Key hatte nicht genau 9 Zeichen!\n");
						
					}
				
				}else{
					
					printf("Für die Funktion 'creation' werden insgesamt 4 Parameter benötigt!\n");
					
				}
			
			}else if(strcmp(argv[1], "play") == 0){
				
				if(argc == 3){
					//read Parameter
					//file[]	= argv[2];
					file = malloc(sizeof(char[strlen(argv[2])]));
					for(i=0; i < strlen(argv[2]); i++){
						file[i] = argv[2][i];
					}
					//play
					play(file);
					
				}else{
					
					printf("Für die Funktion 'play' werden genau 2 Parameter benötigt!\n");
					
				}
				
			}
			
		}else{
			
			//No Parameter
			printf("Es wurden keine Parameter übergeben!\n");
			return 1;
		
	}

   free(file);
   free(start);
   
	return 0;
}
}

/***********************************************************************
 * 		Karten erstellen
 **********************************************************************/
  
void creatCard(void){
	int keyLen = number*4;
	int *p = malloc(keyLen * sizeof(char[4]));
	char code[4];
	char chain[keyLen];
	FILE *output;
	int card[7][7];
	int i,j,k;
	for (i=0; i<keyLen; i++){
		chain[i] = start[i%9];
	}

	for (i=0; i<keyLen; i++){
		
			if (chain[i] == '0' || chain[i] == '1' || chain[i] == '2'){
				p[i]='0';
			}
			else if (chain[i] == '3' || chain[i] == '4' || chain[i] == '5' || chain[i] == '6'){
				p[i]='1';
			}
			else if (chain[i] == '7' || chain[i] == '8' || chain[i] == '9'){
				p[i]='2';
			}
			
	}

		output = fopen (file, "w");
		if (output == NULL){
			printf("Fehler beim öffnen der Datei.\n");
			exit(0);
		}

		
	for (i=0; i<keyLen; i+=4){
		
		
		fprintf (output, "Code:");
		
		for(j=0; j<4; j++){
				code[j]=p[i+j];
		}
		fprintf (output, "%s\n", code);
		
//		Draw Card
		
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
		
		//City
		
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
				fprintf (output, "%c", card[k][j]);
			}
			fprintf (output, "\n");
		}
		
		
		
	}
	
		printf("Die Karten wurden in %s gespeichert.\n", file);
		fclose (output);
	
	
	//	free everything
	free(p);
	
}
/***********************************************************************
 * 				The Game
 **********************************************************************/

void play(char file[]){
	FILE *input;
	char code[4];
	char pic[56];
	int i,j;
	
	input = fopen(file, "r");
	
	char c;
	int lineNumber=1;
	while ((c=getc(input))!=EOF)
	if (c=='\n') {lineNumber++;}
	
	number = (int)lineNumber/8;
	
	CARD *p;
	char ***field;
	
	
	for (i=0; i<number; i++){
		 fseek(input,(long) 5+i*66, SEEK_SET);
		 
			 code[0] = getc(input);
			 code[1] = getc(input);
			 code[2] = getc(input);
			 code[3] = getc(input);
			 code[4] = '\0';
			 
			 
			 fseek(input,(long) 10+i*66, SEEK_SET);
			 
			 for (j=0; j<55; j++){
				pic[j] = getc(input);
			 }
/**
 * 		Put Cards on Stack
 */
			 push(code, pic);
	}
	


		field = creatField(1, 1);
		fillField("2101", 0, 0, field);
		drawField(field);
		
	for (i=0; i<number; i++){


		p = pop();
		
		//printf("Vor:%s\n", p->code);
		
		for(j=0; j<4; j++){
			code[j] = p->code[j];
		}
				
		//printf("Nach:%s\n", code);
		

		//field = fillInCard(p->code, feld);
		//field = creatField(1, 1);
		fillField(code, 0, 0, field);
		drawField(field);
		
	}
	
	freeField(field);
}

/***********************************************************************
 * 		Push-Funktion of the Stack
 **********************************************************************/

void push(char *co, char *pi)
{
	if (begin == NULL){
		begin = (CARD *) malloc(sizeof(CARD));
		pos = begin;
		pos->next = NULL;
	}else{
		next = pos;
		pos = (CARD *) malloc(sizeof(CARD));
		pos->next = next;
	}
	if (pos == NULL) {
		fprintf(stderr, "Kein Speicherplatz vorhanden für neues Element\n");
		exit(0);
	}
	strcpy(pos->code, co);
	strcpy(pos->pic, pi);
}

/***********************************************************************
 * 		Pop-Funktion of the Stack. Return CARD
 **********************************************************************/

CARD * pop(void){
	
	CARD * temp = NULL;
	//printf("Hole eine karte vom Stack\n");
	
    if (begin == NULL){
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
 * 		creats a new empty Field
 **********************************************************************/

char *** creatField(int x, int y)
{
	int i = 0;
	int j = 0;
	x_size	= x;
	y_size	= y;
	char ***field;
	//Versuche Speicher für field zu reservieren
	field	= malloc((x_size)*sizeof(char*));
	if(field == NULL) 
	{
		//Falls kein Speicher reserviert werden konnte, gebe Meldung aus und breche das Programm sofort ab
		printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
		exit(0);
	}else
	{
		for(i=0; i<x_size; i++)
		{
			field[i]	= malloc((y_size)*sizeof(char*));
			if(field[i] == NULL)
			{
				//Falls kein Speicher reserviert werden konnte, gib Meldung aus und breche das Programm sofort ab
				printf("Es konnte nicht genug Speicher für das Spielfeld reserviert werden!\n");
				exit(0);
			}else
			{
				for(j=0; j<y_size; j++)
				{
					field[i][j] = malloc(sizeof(char[4]));
				}
			}
		}
		//Alle Elemente Nullen
		i=0;
		j=0;
		for(i=0; i<x_size; i++)
		{
			if(field != NULL)
			{
				for(j=0; j<y_size; j++)
				{
					field[i][j][0] = '0';
					field[i][j][1] = '0';
					field[i][j][2] = '0';
					field[i][j][3] = '0';
					field[i][j][4] = '\0';
				}
			}
		}
	}
	return field;
}

/***********************************************************************
 * 		Fill field with codes
 **********************************************************************/

void fillField(char code[4], int xpos, int ypos, char ***field)
{

	
	if(field == NULL){
		printf("Fehler beim Spielfeld\n");
		exit(0);
	}
	field[xpos][ypos][0]=code[0];
	field[xpos][ypos][1]=code[1];
	field[xpos][ypos][2]=code[2];
	field[xpos][ypos][3]=code[3];
	field[xpos][ypos][4]='\0';
	
}

void drawField(char ***field)
{
	/*
	 * drawing the field
	 */
	 int i=0;
	 int j=0;
	 int k=0;
	 int l=0;
	 int card[7][7];
	 int output[x_size*7][y_size*7];
	 int a1 = 0, a2 = 0;
	 
	 
	 
	 for (k=0; k<x_size*7; k++){
		for (l=0; l<y_size*7; l++){
			output[k][l] = ' ';
		}
	 }
	 
	for (i=0; i<x_size; i++){
		 for (j=0; j<y_size; j++){
			 
			 	 for(a1=0;a1<7;a1++)
					 {
						 for(a2=0;a2<7;a2++)
						 {
							 card[a1][a2] = ' ';
						 }
					 }
					 
	
			 
			 printf("Feld %i/%i=%s hinzugefügt\n",i,j, field[i][j]);
			 
			 
		if (field[i][j][0] != EOF){
			
			if(strcmp(field[i][j], "0000")==0){
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
			
			//Street
			
			 if(field[i][j][0] == '1'){
				card[3][1]='+';
				card[3][2]='+';
				card[3][3]='+';
			}
			if(field[i][j][1] == '1'){
				card[5][3]='+';
				card[4][3]='+';
				card[3][3]='+';
			}
			if(field[i][j][2] == '1'){
				card[3][5]='+';
				card[3][4]='+';
				card[3][3]='+';
			}
			if(field[i][j][3] == '1'){
				card[1][3]='+';
				card[2][3]='+';
				card[3][3]='+';
			}
			
			//City
			
			if(field[i][j][0] == '2'){
				card[1][1]='x';
				card[2][2]='x';
				card[3][2]='x';
				card[4][2]='x';
				card[5][1]='x';
			}
			
		if(field[i][j][1] == '2'){
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
			
		if(field[i][j][2] == '2'){
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
			
		if(field[i][j][3] == '2'){
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
			
			
			drawCard(i,j,card,output);
			
			
		}
		}
		
		
	 }
	 for (k=0; k<y_size*7; k++){
				for (l=0; l<x_size*7; l++){
					printf("%c", (char)output[l][k]);
				}
				printf("\n");
			}
}

/***********************************************************************
 * 		Berechnet die Position jedes char im Ausgabe-Array
 **********************************************************************/
 void drawCard(int x_koor, int y_koor, int card[7][7], int output[x_size*7][y_size*7])
 {
	 int i, j;
	 int minusX = 0;
	 int minusY = 0;
		
		if(x_koor>0){
			minusX=x_koor;
		}
		if(y_koor>0){
			minusY=y_koor;
		}
	 
		 for (i=0; i<7; i++){
			 for (j=0; j<7; j++){
				 if (output[i+x_koor*7-minusX][j+y_koor*7-minusY] == '-') 
				 {
						card[i][j] = '-';
				 }
				 if (output[i+x_koor*7-minusX][j+y_koor*7-minusY] == '|')
				 {
					 card[i][j] = '|';
				 }
				 output[i+x_koor*7-minusX][j+y_koor*7-minusY]=card[i][j];
			 }
			 
		 }
		 return;
 }
 
/**********************************************************************
 * 		Berechnet die Position der nächsten Karte
 *********************************************************************/

char *** fillInCard(char *co, char ***field)
{
	int i,j,k;
	int width = y_size+2;	
	int higth = x_size+2;
	char ***output;
	char ***fieldBig = creatField(higth,width);

	for(i=0; i<x_size; i++){
		for(j=0; j<y_size; j++){
			fieldBig[i+1][j+1]=field[i][j];
		}
	}

	output = fieldBig;
	
/**
 * 	delete empty rows
 */
	j=0;
	for(i=0; i<width; i++){
		if(strcmp(fieldBig[0][i],"3333") != 0){
			j++;
		}
	}
	k=0;
	for(i=0; i<higth; i++){
		if(strcmp(fieldBig[i][0],"3333") != 0){
			k++;
		}
	}
	if (j==0){	
		higth-=1;
		char ***fieldSmall = creatField(higth,width);	
		for(i=0; i<x_size+2; i++){
			for(j=1; j<y_size+2; j++){
				//fieldSmall[i][j-1]=fieldBig[i][j];
			}
		}
			output = fieldSmall;
	}
	if (k==0){	
		width-=1;
		char ***fieldSmall = creatField(higth,width);	
		for(i=0; i<width; i++){
			for(j=0; j<higth; j++){
				//fieldSmall[i][j]=fieldBig[i+1][j];
			}
		}
			output = fieldSmall;
	}	

	return output;
}

/***********************************************************************
 * 		free the field
 **********************************************************************/

void freeField(char ***field)
{
	int k = 0;
	int p = 0;
	for(k=0; k<(x_size-1);k++)
	{
		for(p=0; p<(y_size-1); p++)
		{
			free(field[k][p]);
		}
		free(field[k]);
	}
	free(field);
}

