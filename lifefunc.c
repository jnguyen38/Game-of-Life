// Function file for playlife.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BRDSZ 40
#define COMLEN 5
#define MAXLENGTH 256

void borderline(void) {
	int i;

	for (i = 0; i < BRDSZ + 2; i++)
		printf("-");
	putchar(10);
}

void checkNewline(void) {
	char whiteSpace;
	do {
			whiteSpace = getchar();
	} while (whiteSpace != '\n');
}

void printBoard(int life[BRDSZ][BRDSZ]) {
	int i, j;

	borderline();
	for (i = 0; i < BRDSZ; i++) {
		printf("|");
		for (j = 0; j < BRDSZ; j++) {
			if (life[i][j]) 
				printf("X");
			else
				printf(" ");
		} 
		printf("|\n");
	}
	borderline();
}

void initLife(int life[BRDSZ][BRDSZ]) {
	int i, j;
	
	for (i = 0; i < BRDSZ; i++)
		for (j = 0; j < BRDSZ; j++) 
			life[i][j] = 0;
}

void addLife(int life[BRDSZ][BRDSZ], int row, int col) {
	if (life[row][col]) 
		printf("Error: Row %d Column %d is already alive\n", row, col);
	else {
		life[row][col] = 1;
		system("clear");
		printBoard(life);
	}
}

void removeLife(int life[BRDSZ][BRDSZ], int row, int col) {
	if (life[row][col]) { 
		life[row][col] = 0;
		system("clear");
		printBoard(life);
	}
	else
		printf("Error: Row %d Column %d is not alive\n", row, col);
}

FILE *getFile(char *arg) {
	FILE *fp;
	fp = fopen(arg, "r");
	while (!fp) {
		printf("Your file \"%s\" not found\n", arg);
		printf("Enter the file name or press 'q' to quit: ");
		scanf("%s", arg);
		if (!strcmp(arg, "q")) return NULL;
		fp = fopen(arg, "r");
	}
	return fp;
}

void next(int life[BRDSZ][BRDSZ]) {
	int i, j, row, col, nearCount, nextLife[BRDSZ][BRDSZ];

	for (row = 0; row < BRDSZ; row++) {
		for (col = 0; col < BRDSZ; col++) {
			nearCount = -(life[row][col]);
			for (i = -1; i < 2; i++)
				for (j = -1; j < 2; j++){
					if ((row + i >= 0) && (row + i < 40) && (col + j >= 0) && (col + j < 40))
						nearCount = nearCount + life[row+i][col+j];
				}
			if (life[row][col])
				if (nearCount != 2 && nearCount != 3 ) {
					nextLife[row][col] = 0;
				} else 
					nextLife[row][col] = life[row][col];
			else
				if (nearCount == 3) {
					nextLife[row][col] = 1;
				} else
					nextLife[row][col] = life[row][col];
		}
	}
	for (row = 0; row < BRDSZ; row++) {
		for (col = 0; col < BRDSZ; col++) {
			life[row][col] = nextLife[row][col];
		}
	}
	system("clear");
	printBoard(life);
}

void play(int life[BRDSZ][BRDSZ]) {	
	while(1) {
		next(life);
		usleep(75000);
	}
}
