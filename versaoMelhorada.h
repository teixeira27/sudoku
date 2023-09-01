//
// Created by bruno on 11/12/2019.
//

#ifndef PROJETOFASE2_VERSAOMELHORADA_H
#define PROJETOFASE2_VERSAOMELHORADA_H

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define QUEUE_CAPACITY 10

typedef struct box{
    int lin,col,val;
    int *aux;
    struct box *S,*E,*SE,*SO;
}BOX;

typedef struct matrix{
    int N;
    int *aux;
    BOX *pfirst;
}MATRIX;

typedef struct matrixes {
    int N,tail,head;
    MATRIX *parray;
}MATRIXS;

#define M 9

void client_versaoMelhorada();
void clientTestFiles();
void clientTestQueues();

void create_matrix (MATRIX *m,int N,int new[M][M]);
void print_matrix(MATRIX m);
void initQueue(MATRIXS *m);
void enqueue (MATRIXS *m, MATRIX m1);
MATRIX* dequeue (MATRIXS *m);

int main_teste2();
int isSafeMelhorada(MATRIX *m,BOX b);
int SolveSudoku2(MATRIX *m);
BOX* FindUnassignedLocationMelhorada(MATRIX m,BOX* b);

int teste1(MATRIX *m);
int teste111(MATRIX *m,BOX *b);
int clientOcultoLin(MATRIX *m);
int clientOcultoCol(MATRIX *m);
int clientOcultoBox(MATRIX *m);

int clientParOcultoLin(MATRIX *m);
void parOcultoLin(MATRIX *m, BOX *b);

int clientParOcultoCol(MATRIX *m);
void parOcultoCol(MATRIX *m,BOX *b);

int clientParOcultoBox (MATRIX *m);
void parOcultoBox (MATRIX *m,BOX *b);

void boxLineReduction(MATRIX *m,BOX *b);
int clientBoxLineReduction(MATRIX *m);

void printGrid(int grid[M][M]) ;


void print_array(BOX b);
int find2inArray (MATRIX *m,BOX *b);
int compare2arrays(BOX b1, BOX b2);
int compare2BoxsSquare(MATRIX m,BOX b1,BOX b2);

void removeDoublePairsLin(MATRIX *m,BOX b1,BOX b2);
void removeDoublePairsCol(MATRIX *m,BOX b1,BOX b2);
void removeDoublePairsBox (MATRIX *m,BOX b1,BOX b2);

int numeroOcultoLin (MATRIX *m,BOX *b);
int numeroOcultoCol (MATRIX *m,BOX *b);
int numeroOcultoBox (MATRIX *m,BOX *b);


void fillAuxArray(MATRIX m,BOX *b);
void fillAuxArray0s(MATRIX m,BOX *b);
int checkAuxArrayOnlyHave1(MATRIX m,BOX b);
void removeFromAux(BOX *b,int val);
void printAuxArray(MATRIX m,BOX b);

void checkMoreThenOneNumberInRow(MATRIX *m,BOX *b);
void checkMoreThenOneNumberInCol(MATRIX *m,BOX *b);
void checkMoreThenOneNumberInBox(MATRIX *m,BOX *b);

void ler_txt(MATRIXS *a);
void gerar_txt(MATRIXS a);
void gerar_solucoes_bin(MATRIXS b);
void read_solutions_bin(MATRIXS b);



#endif //PROJETOFASE2_VERSAOMELHORADA_H
