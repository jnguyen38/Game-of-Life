/* CSE 20311
 * Jonathan Nguyen
 * playlife.c
 * This program simulates Conway's Game of Life
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "lifefunc.h"

#define BRDSZ 40


int main(int argc, char *argv[]) {
	int life[BRDSZ][BRDSZ], run = 1, row, col;
	char input[2];
	char choice;
	initLife(life);
	system("clear");
	
	// Interactive Mode

	if (argc == 1) { 
		printBoard(life);
		while(run) {
			printf("Command: ");
			scanf("%s", input);
			while (strlen(input) > 2) {
				checkNewline();
				printf("Error: Invalid Command Argument\n");
				printf("Command: ");
				scanf("%s", input);
			}
			choice = input[0];
			switch(choice) {
				case 'r':
					scanf("%d %d", &row, &col);
					if ((row >= 0) && (row < 40) && (col >= 0) && (col < 40))
						removeLife(life, row, col);
					else
						printf("Error: Row %d Col %d is not within board range\n", row, col);
					break;
				case 'a':
					scanf("%d %d", &row, &col);
					if ((row >= 0) && (row < 40) && (col >= 0) && (col < 40))
						addLife(life, row, col);
					else
						printf("Error: Row %d Col %d is not within board range\n", row, col);
					break;
				case 'n':
					next(life);
					break;
				case 'p':
					play(life);
					break;
				case 'q':
					printf("Goodbye!\n");
					return 0;
				default:
					printf("Error: Invalid Command Argument\n");
					break;
			}
		}
	}

	else if (argc == 2) { // Batch Mode
		FILE *fp;
		fp = getFile(argv[1]);
		if (fp == NULL) return 0;	
		printBoard(life);
		while (run) {
			printf("Command: ");
			fscanf(fp, "%s", input);
			puts(input);
			if (strlen(input) > 2) {
				checkNewline();
				printf("Error: File not formatted correctly\n");
				return 0;
			}
			choice = input[0];

			switch(choice) {
				case 'r':
					fscanf(fp, "%d %d", &row, &col);
					if ((row >= 0) && (row < 40) && (col >= 0) && (col < 40))
						removeLife(life, row, col);
					else {
						printf("Error: File not formatted correctly\n", row, col);
						return 0;
					}
					break;
				case 'a':
					fscanf(fp, "%d %d", &row, &col);
					if ((row >= 0) && (row < 40) && (col >= 0) && (col < 40))
						addLife(life, row, col);
					else {
						printf("Error: File not formatted correctly\n", row, col);
						return 0;
					}
					break;
				case 'n':
					next(life);
					break;
				case 'p':
					play(life);
					break;
				case 'q':
					printf("Goodbye!\n");
					return 0;
				default:
					printf("Error: File not formatted correctly\n");
					return 0;
			}

		}


	}
	
	else { // Invalid number of arguments
		puts("Error: Invalid number of arguments");
		return 0;
	}
	return 0;
}
