//
// Created by bruno on 11/12/2019.
//

#include "bruteforce.h"


int contador=0;


int SolveSudoku(MATRIX *m) {

    BOX *current=m->pfirst;
    // If there is no unassigned location, we are done
    current=FindUnassignedLocation(current);
    if (current==NULL) {
        return 1; // success!
    }
    //print_matrix(*m);
    //printf("\n");
    // consider digits 1 to 9
    for (int num = 1; num <= m->N; num++) {
        // if looks promising

        if (isSafe(m, *current, num)) {
            contador++;
            // make tentative assignment
            current->val = num;

            // return, if success, yay!
            if (SolveSudoku(m))
                return 1;

            // failure, unmake & try again
            current->val = UNASSIGNED;
        }else
            contador++;
    }
    return 0; // this triggers backtracking
}


BOX* FindUnassignedLocation(BOX *b) {     //está a encontrar o proximo 0, mas nao mexe no apontador, nao sai do sitio
    BOX *aux=b;
    while (b!=NULL){
        if(b->val==0){
            return b;
        }
        if(b->E==NULL){
            b=aux->S;
            aux=aux->S;
        }  else  b=b->E;
    }
    return NULL;
}


int UsedInRow(MATRIX *m, BOX b, int val) {
    BOX *temp=m->pfirst;
    while(temp->lin!=b.lin)
        temp=temp->S;
    while (temp!=NULL){
        if(temp->val==val)
            return 1;
        temp=temp->E;
    }
    return 0;
}

int UsedInCol(MATRIX *m, BOX b, int val) {
    BOX *temp=m->pfirst;
    while(temp->col!=b.col)
        temp=temp->E;
    while (temp!=NULL){
        if(temp->val==val)
            return 1;
        temp=temp->S;
    }
    return 0;
}


int UsedInBox(MATRIX *m, int row, int col, int val) {
    BOX *temp=m->pfirst,*aux=m->pfirst;
    while (temp!=NULL){
        if(temp->lin==row && temp->col==col)
            break;
        if(temp->E!=NULL){
            temp=temp->E;
        }  else  {
            temp=aux->S;
            aux=aux->S;
        }
    }
    aux = temp;
    int j=1,k=1;
    for (int i = 1; i <= m->N; i++) {
        if(temp->val==val)
                return 1;
        if(j==sqrt(m->N) && k==sqrt(m->N)) break;
        if(j==sqrt(m->N)){
                temp=aux->S;
                aux=aux->S;
                k++;
                j=1;
        } else {
                temp=temp->E;
                j++;
        }
    }
    return 0;
}

int UsedInFirstDiagonal(MATRIX *m, int val) {
    BOX *temp = m->pfirst;
    while (temp!=NULL){
        if(temp->val==val)
            return 1;
        temp=temp->SE;
    }
    return 0;
}

int UsedInSecondDiagonal(MATRIX *m,int val) {
    BOX *temp=m->pfirst;
    while (temp->E!=NULL) temp=temp->E;
    while (temp!=NULL){
        if(temp->val==val)
            return 1;
        temp=temp->SO;
    }
    return 0;
}


int isSafe(MATRIX *m, BOX current, int val) {
    /*

    if(current.lin == (m->N-1)/2 && current.col == (m->N-1)/2){                 // se for o centro das diagonais, testamos as dusa
        return !UsedInRow(m, current, val) &&
               !UsedInCol(m, current, val) &&
               //!UsedInBox(m, current.lin - current.lin%3 , current.col - current.col%3, val)&&
               !UsedInFirstDiagonal(m, val)&&
               !UsedInSecondDiagonal(m, val)&&
               current.val==UNASSIGNED;
    }
     if(current.lin==current.col){                                            //se tiver na diagonal principal
        return !UsedInRow(m, current, val) &&
               !UsedInCol(m, current, val) &&
               //!UsedInBox(m, current.lin - current.lin%3 , current.col - current.col%3, val)&&
               !UsedInFirstDiagonal(m, val)&&
               current.val==UNASSIGNED;

    } else if(current.lin+current.col==m->N-1){                                //se tiver na diagonal secundaria
        return !UsedInRow(m, current, val) &&
               !UsedInCol(m, current, val) &&
               //!UsedInBox(m, current.lin - current.lin%3 , current.col - current.col%3, val)&&
               !UsedInSecondDiagonal(m, val)&&
               current.val==UNASSIGNED;

    }else {                                                                    // se for qualquer outra celula
*/
         return !UsedInRow(m, current, val) &&
                !UsedInCol(m, current, val) &&
                !UsedInBox(m, current.lin - current.lin%3 , current.col - current.col%3, val) &&
                current.val == UNASSIGNED;


}


int main_teste() {
    return 0;
}
