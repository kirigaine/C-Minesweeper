/*******************************************************************\
*                                                                   *
* Author:		Dustin                                      *
* Date:			10/31/18                                    *
* Project ID:		minesweeper.c		                    *
* Problem Description:	Create a functional game of minesweeper     *
*                                                                   *
\********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ROW 100
#define MAX_COL 100
char game[MAX_ROW][MAX_COL];
unsigned char display[MAX_ROW][MAX_COL];
unsigned char difficulty = 1;
unsigned char hit_a_mine = 0;
int m, n, totalMines, hiddenCells;

void headerFormatting(){
	printf("     ");
	for(int i=0; i<n; i++) printf(" %2d", i);
	printf("\n");
	for(int i=0; i<(((n+1)*3)+2); i++) printf("-");
	printf("\n");
}

void drawGameBoard(){

	headerFormatting();
	
	for(int i=0; i<m; i++){
		printf("%3d | ", i);
		for(int j=0; j<n; j++){
			if (game[i][j] != -1) printf(" %d ", game[i][j]);
			if (game[i][j] == -1) printf(" - ");
		}
		printf("\n");
	}
	printf("\n");
}

void drawDisplayBoard(){

	headerFormatting();

	for(int i=0; i<m; i++){
		printf("%3d | ", i);
		for(int j=0; j<n; j++){
			if(!hit_a_mine && !(hiddenCells == totalMines)){
				if ((game[i][j] == 0) && (display[i][j] == 1)) printf("   ");
				if ((game[i][j] > 0) && (display[i][j] == 1)) printf(" %d ", game[i][j]);
				if (display[i][j] == 0) printf(" * ");
			}
			if(hit_a_mine || (hiddenCells == totalMines)){
				if ((display[i][j] == 1) && (game[i][j] != -1)) printf("   ");
				if ((display[i][j] == 1) && (game[i][j] == -1)) printf(" M ");
				if (display[i][j] == 0) printf(" * ");
			} 
		}
		printf("\n");
	}
	printf("\n");
}

void testDrawDisplayBoard(){
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			printf("%d ", display[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


void initializeMines(){
	int totalSpace = (m * n);
	int numberOfMines = (((totalSpace - 1)/20) * difficulty);
	if (numberOfMines <=3) numberOfMines = (totalSpace * .25); 
	//printf("calculateNumberMines(): numberOfMines = %d\n\n", numberOfMines);
	totalMines = numberOfMines;
	hiddenCells = totalSpace;
	srand(time(NULL));
	while(numberOfMines != 0){
		int randomNumber1 = (int)(rand()%m);
		int randomNumber2 = (int)(rand()%n);
		if (game[randomNumber1][randomNumber2] == 0) {
			game[randomNumber1][randomNumber2] = -1;
			numberOfMines--;
		}
	}
	hit_a_mine = 0;
}

void calculateAdjacentMines(){
	for (int i=0; i<m; i++){
		for (int j=0; j<n; j++){
			if (game[i][j] != -1){
				if (game[i+1][j] == -1) game[i][j]++;
				if (game[i-1][j] == -1) game[i][j]++;
				if (game[i][j+1] == -1) game[i][j]++;
				if (game[i][j-1] == -1) game[i][j]++;
				if (game[i+1][j+1] == -1) game[i][j]++;
				if (game[i+1][j-1] == -1) game[i][j]++;
				if (game[i-1][j+1] == -1) game[i][j]++;
				if (game[i-1][j-1] == -1) game[i][j]++;
			}
		}
	}
}

int checkSurroundingCells(int x, int y){
	if (game[x][y] == 0){
		display[x][y] = 1;
		if ((x+1 < m) && (display[x+1][y] != 1)){
			if (game[x+1][y] == 0) checkSurroundingCells(x+1, y);
			if (game[x+1][y] > 0) display[x+1][y] = 1;
		}
		if ((x-1 >= 0) && (display[x-1][y] != 1)){
			if (game[x-1][y] == 0) checkSurroundingCells(x-1, y);
			if (game[x-1][y] > 0) display[x-1][y] = 1;
		}
		if ((y+1 < n) && (display[x][y+1] != 1)){
			if (game[x][y+1] == 0) checkSurroundingCells(x, y+1);
			if (game[x][y+1] > 0) display[x][y+1] = 1;
		}
		if ((y-1 >= 0) && (display[x][y-1] != 1)){
			if (game[x][y-1] == 0) checkSurroundingCells(x, y-1);
			if (game[x][y-1] > 0) display[x][y-1] = 1;
		}
	}
	else return 0;
}

int main(int argc, char ** argv) {

	int i, j, r, c;
	char continuePlaying;
		
	// Determine proper number of arguments
	
	if (argc != 4) { 
		printf("Usage: ./a.out numberOfRows[2-100] numberOfColumns[2-100] difficulty[1-10]\n");
		return 0;
	}
	
	// Validate arguments
	
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	difficulty = atoi(argv[3]);
	
	if ((m <= 1 || m > MAX_ROW) || (n <= 1 || n > MAX_COL) || (difficulty <= 0 || difficulty > 10)) {
		printf("Usage: ./a.out numberOfRows[2-100] numberOfColumns[2-100] difficulty[1-10]\n");
		return 0;
	}	
	
	do{
		
		for(i = 0; i < 100; i++){
			for(j = 0; j < 100; j++){
				game[i][j] = 0;
				display[i][j] = 0;
			}
		}

		system("clear");
		//printf("Rows: %d | Columns: %d | Difficulty: %d\n", m,n,difficulty);
		initializeMines();
		calculateAdjacentMines();
		//printf("drawGameBoard():\n");
		//drawGameBoard();
		//printf("drawDisplayBoard():\n");
		drawDisplayBoard();
		//printf("testDrawDisplayBoard():\n");
		//testDrawDisplayBoard();

		do{
			do{
				r = -1;
				c = -1;
				printf("Input a coordinate (e.g. 0 0): ");
				scanf(" %d %d", &r, &c);
			} while ( (r < 0 || c < 0) || (r >= m || c >= n) );
			
			if (display[r][c] == 0) {
				switch ( game[r][c] ) {
					case -1:
						hit_a_mine = 1;
						break;
					case 0:
						display[r][c] = 1;
						checkSurroundingCells(r,c);
						system("clear");
						drawDisplayBoard();
						break;
					default:
						display[r][c] = 1;
						system("clear");
						drawDisplayBoard();
				}		
				hiddenCells = 0; 
				for (int i=0; i<m; i++){
					for (int j=0; j<n; j++){
						if (display[i][j] == 0) hiddenCells++;
					}
				}
			}
		} while ( (!hit_a_mine) && (hiddenCells != totalMines));
		
		system("clear");
		
		for (int i=0; i<m; i++){
			for (int j=0; j<n; j++){
				if (game[i][j] == -1) display[i][j] = 1;
			}
		}
		drawDisplayBoard();
		
		if (hit_a_mine == 1) {
			printf("\n\n***GAME OVER***");
		}

		if (hiddenCells == totalMines) {
			printf("\n\n***CONGRATULATIONS! YOU WIN!***\n");
		}

		do{
			printf("\n\nWould you like to play another game? (Y/N): ");
			scanf(" %c", &continuePlaying);
		} while (continuePlaying != 'Y' && continuePlaying != 'y' && continuePlaying != 'N' && continuePlaying != 'n');		
		
	} while ( continuePlaying == 'Y' || continuePlaying == 'y');
		
	printf("\nThanks for playing!\n");	
	
	return 0;
}
