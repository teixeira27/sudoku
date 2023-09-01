//
// Created by bruno on 11/12/2019.
//

#ifndef PROJETOFASE2_BRUTEFORCE_H
#define PROJETOFASE2_BRUTEFORCE_H

#include "versaoMelhorada.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define UNASSIGNED 0
#define MSIZE 1

int main_teste();
int isSafe(MATRIX *m, BOX current, int val);
int UsedInBox(MATRIX *m, int row, int col, int val);
int UsedInCol(MATRIX *m, BOX b, int val);
int UsedInRow(MATRIX *m, BOX b, int val);
int UsedInFirstDiagonal(MATRIX *m, int val);
int UsedInSecondDiagonal(MATRIX *m,int val);
BOX* FindUnassignedLocation(BOX *b);
int SolveSudoku(MATRIX *m);




#endif //PROJETOFASE2_BRUTEFORCE_H
