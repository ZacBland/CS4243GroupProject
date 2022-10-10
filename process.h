#ifndef PROCESS_H
#define PROCESS_H

void readFile(char inputFile[25], int cols);
int processSetup(int rows, int columns, int col, int processes, int *fout, int *fin);
int processCreation(int processes, int location, char* values[], int sizes[], int rows, int cols, int *fout, int *fin);

#endif
