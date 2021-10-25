// lifefunc.h
// Header file for function prototypes

#define BRDSZ 40

void printBoard(int [BRDSZ][BRDSZ]);
void checkNewline(void);
void borderline(void);
void initLife(int [BRDSZ][BRDSZ]);
void addLife(int [BRDSZ][BRDSZ], int, int);
FILE *getFile(char *);
void next(int [BRDSZ][BRDSZ]);
void play(int [BRDSZ][BRDSZ]);
