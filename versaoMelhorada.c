//
// Created by bruno on 11/12/2019.
//

#include "versaoMelhorada.h"
#include "bruteforce.h"

void client_versaoMelhorada(){

    int aux[9][9]={{4,0,0,8,0,0,0,0,1},
                   {0,2,0,0,5,6,4,0,0},
                   {1,8,0,0,0,7,0,2,3},
                   {2,9,0,0,4,8,0,6,0},
                   {0,0,4,0,0,1,9,0,0},
                   {0,7,0,0,0,2,0,8,4},
                   {6,3,0,2,0,0,0,1,5},
                   {0,0,2,7,3,0,0,4,0},
                   {7,0,0,0,0,5,0,0,9}};




    MATRIXS *a;
    MATRIX m1,m2,m3;

    initQueue(a);
    create_matrix(&m1,9,aux);
    //create_matrix(&m2,6,aux);
    print_matrix(m1);
    printf("\n");

    //printf("%d",UsedInBox(&m1,0,6,3));

    SolveSudoku2(&m1);

    //clientTestQueues();

    //clientTestFiles();


    /*
    create_matrix(&m1,8,aux);
    create_matrix(&m2,4,aux);
    create_matrix(&m3,16,aux);

    enqueue(&a,m1);
    enqueue(&a,m2);
    enqueue(&a,m3);

    for (int i = 0; i < 3; i++) {
        MATRIX *aux=NULL;
        aux=dequeue(&a);
        print_matrix(*aux);
        printf("\n");
    }
    */

}

void clientTestQueues(){

    int aux[9][9]={{4,0,0,8,0,0,0,0,1},
                   {0,2,0,0,5,6,4,0,0},
                   {1,8,0,0,0,7,0,2,3},
                   {2,9,0,0,4,8,0,6,0},
                   {0,0,4,0,0,1,9,0,0},
                   {0,7,0,0,0,2,0,8,4},
                   {6,3,0,2,0,0,0,1,5},
                   {0,0,2,7,3,0,0,4,0},
                   {7,0,0,0,0,5,0,0,9}};




    MATRIXS *a;
    MATRIX m1,m2,m3;

    initQueue(a);
    create_matrix(&m1,8,aux);
    create_matrix(&m2,4,aux);
    create_matrix(&m3,16,aux);

    enqueue(a,m1);
    enqueue(a,m2);
    enqueue(a,m3);

    for (int i = 0; i < 3; i++) {
        MATRIX *aux=NULL;
        aux=dequeue(a);
        print_matrix(*aux);
        printf("\n");
    }


}

/**
 * cliente teste para as funções de leitura e escrita
 */

void clientTestFiles(){
    MATRIXS a,b;

    ler_txt(&a);
    print_matrix((a.parray[0]));
    printf("\n\n\n");
    SolveSudoku(&(a.parray[0]));
    gerar_txt(a);
    gerar_solucoes_bin(a);
    read_solutions_bin(a);
}

/**
 * função que cria a estrutura dinâmica que suporta a matriz
 * @param m matriz dinâmica
 * @param N tamanho da matriz
 * @param new matriz estática para passar para a dinâmica
 */

void create_matrix (MATRIX *m,int N,int new[M][M]){
    int auxlin=0,auxcol=0;
    m->pfirst = (BOX*) malloc(sizeof(BOX));
    m->N=N;
    m->pfirst->aux= (int*) malloc(sizeof(int)*N);

    m->pfirst->E = NULL;
    m->pfirst->S = NULL;
    m->pfirst->SE = NULL;
    m->pfirst->SO = NULL;

    m->pfirst->val=new[auxlin][auxcol];
    if(m->pfirst->val!=0)
        fillAuxArray0s(*m,m->pfirst);
    else
        fillAuxArray(*m,m->pfirst);
    m->pfirst->lin=auxlin;
    m->pfirst->col=auxcol;

    BOX *previous=m->pfirst,*previousLin=m->pfirst,*firstLin=m->pfirst;

    auxcol++;

    while (auxlin<N && auxcol<N){
        BOX *temp = (BOX*) malloc(sizeof(BOX));
        temp->aux= (int*) malloc(sizeof(int)*N);

        temp->val=new[auxlin][auxcol];
        if(temp->val!=0)
            fillAuxArray0s(*m,temp);
        else
            fillAuxArray(*m,temp);
        temp->lin=auxlin;
        temp->col=auxcol;
        temp->E=NULL;
        temp->S=NULL;
        temp->SO=NULL;
        temp->SE=NULL;
        if(auxlin==0) {                         // se tiver na primeira linha, apenas aponto para a direita
            previous->E=temp;
            previous=temp;
            if(auxcol<N-1)
                auxcol++;
            else{
                auxlin++;
                auxcol=0;
            }
        }else{
            if(auxcol==0){                      // se tiver na primeira coluna
                previousLin->S=temp;
                previousLin->E->SO=temp;
                auxcol++;
            }else if(auxcol==N-1){              // se tiver na ultima coluna
                previousLin->SE=temp;
                previousLin->S->E=temp;
                previousLin->E->S=temp;
                firstLin=firstLin->S;
                previousLin=firstLin;
                auxcol=0;
                auxlin++;
            }
            else{                               // se tiver no meio
                previousLin->S->E=temp;
                previousLin->SE=temp;
                previousLin->E->S=temp;
                previousLin->E->E->SO=temp;
                previousLin=previousLin->E;
                auxcol++;
            }
        }
    }
}

/**
 * imprime a matriz
 * @param m estrutura que guarda todas as matrizes
 */
void print_matrix(MATRIX m){
    BOX *temp=m.pfirst,*aux=m.pfirst;

    while (temp!=NULL){
        printf("%d ",temp->val);
        if(temp->E==NULL){
            temp=aux->S;
            aux=aux->S;
            printf("\n");
        }  else  temp=temp->E;
    }
}

/**
 * inicia a queue
 * @param m estrutura que guarda todas as matrizes
 */

void initQueue(MATRIXS *m){
    m->parray= (MATRIX*) malloc(sizeof(MATRIX));
    m->N=0;
    m->tail=0;
    m->head=0;
}

/**
 * adiciona na queue
 * @param m estrutura que guarda todas as matrizes
 * @param m1 matriz a adicionar
 */
void enqueue (MATRIXS *m, MATRIX m1){
    m->parray= (MATRIX*) realloc(m->parray, sizeof(MATRIX)+1);
    m->parray[m->tail]=m1;
    m->tail=(m->tail+1)%QUEUE_CAPACITY;
    m->N++;
}

/**
 * retira da queue
 * @param m estrutura que guarda todas as matrizes
 * @return
 */
MATRIX* dequeue (MATRIXS *m){
    MATRIX *pm;
    pm = &m->parray[m->head];
    m->head=(m->head+1)%QUEUE_CAPACITY;
    m->N--;
    return pm;
}

/**
 * função que resolve o sudoku
 * @param m matriz a resolver
 * @return
 */
int SolveSudoku2(MATRIX *m)
{
    int i=0;
    int c1=0,c2,c3;

    while(i<5){
    printf("TESTE1\n");
        while(teste1(m)>0){
            teste1(m);
        }
        print_matrix(*m);
        printf("OCULTO LIN\n");
        while(clientOcultoLin(m)>0){
            clientOcultoLin(m);
        }
        print_matrix(*m);
        printf("OCULTO COL\n");
        while(clientOcultoCol(m)>0){
            clientOcultoCol(m);
        }
        print_matrix(*m);
        printf("OCULTO BOX\n");
        while(clientOcultoBox(m)>0){
            clientOcultoBox(m);
        }

        print_matrix(*m);
        printf("PAR SOZINHO LINHA\n");
        clientParOcultoLin(m);

        print_matrix(*m);
        printf("PAR SOZINHO COLUNA\n");
        clientParOcultoCol(m);

        print_matrix(*m);
        printf("PAR SOZINHO BOX\n");
        clientParOcultoBox(m);

        //print_matrix(*m);
        //printf("BOX LINE\n");
        //clientBoxLineReduction(m);


        //teste3(m);
        print_matrix(*m);
        printf("\n");
        i++;
    }


    //teste1(m);
    //teste2(m);
    //teste3(m);
    //print_matrix(*m);
    //este1(m);
    //print_matrix(*m);



    //print_matrix(*m);
    //printf("\n");
    return 1;
}

/**
 * função que cruza informação da linha coluna e box para retirar possibilidades ao array de possibilidades
 * @param m matriz a resolver
 * @return
 */
int teste1(MATRIX *m){                                     // CRUZA A INFORMAÇAO DE LINHA COLUNA E QUADRADO
    int verified=0,cont=0;
    BOX *current=m->pfirst,*aux=m->pfirst;
    while(1) {                                                  // TESTAR O NUMERO SOZINHO
        while(aux->lin!=current->lin)
            aux=aux->S;
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return cont;
        verified = teste111(m,current);
        if (verified >0 ) {                             // se só houver 1 único numero possivel, coloca o lá
            cont++;
        }
        if(current->lin==m->N-1 && current->col==m->N-1){
            return cont;
        }
        else if(current->E!=NULL)                                // proxima coluna
            current=current->E;
        else{                                                 // proxima linha
            current=aux->S;
            aux=aux->S;
        }
    }
}

/**
 * função auxiliar para retirar possibilidades ao array
 * @param m matriz a resolver
 * @param b box que está em teste
 * @return
 */
int teste111(MATRIX *m,BOX *b){
    int a=0,i=0;
    checkMoreThenOneNumberInRow(m,b);
    checkMoreThenOneNumberInCol(m,b);
    checkMoreThenOneNumberInBox(m,b);
    a=checkAuxArrayOnlyHave1(*m,*b);
    print_array(*b);

    if(a>0) {
        b->val = *(b->aux + a);
        printf("%d\n",++i);
        fillAuxArray0s(*m,b);
        return 1;
    }
    return 0;
}

/**
 * imprime o array de possibilidades da box
 * @param b box a imprimir
 */
void print_array(BOX b){
    printf("lin:%d , col:%d - aux: ",b.lin,b.col);
    for (int i = 0; i < 9; i++) {
        printf("%d,",*(b.aux+i));
    }
    printf("\n");
}

/**
 * cliente que percorre a matriz para testar se há 1 número oculto na linha
 * @param m matriz a resolver
 * @return
 */
int clientOcultoLin(MATRIX *m){
    int cont=0;
    BOX *current=m->pfirst,*aux=m->pfirst,*temp;

    while(1) {     // TESTAR O NUMERO SOZINHO OCULTO
        while(aux->lin!=current->lin){
            if(aux->S!=NULL)
                aux=aux->S;
            else
                return cont;
        }
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return cont;
        if(numeroOcultoLin(m,current)){
            cont++;
        }
        if(current->lin==m->N-1){
            return cont;
        }
        else if(current->E!=NULL)                                // proxima coluna
            current=current->E;
        else{                                                 // proxima linha
            current=aux->S;
            aux=aux->S;
        }
    }
}

/**
 * cliente que percorre a matriz para testar se há 1 número oculto na coluna
 * @param m matriz a resolver
 * @return
 */
int clientOcultoCol(MATRIX *m){
    int cont=0;
    BOX *current=m->pfirst,*aux=m->pfirst,*temp;

    while(1) {     // TESTAR O NUMERO SOZINHO OCULTO
        while(aux->lin!=current->lin){
            if(aux->E!=NULL)
                aux=aux->E;
            else
                return cont;
        }
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return cont;
        if(numeroOcultoCol(m,current)){
            cont++;
        }
        if(current->col==m->N-1){
            return cont;
        }
        else if(current->S!=NULL)                                // proxima coluna
            current=current->S;
        else{                                                 // proxima linha
            current=aux->E;
            aux=aux->E;
        }
    }
}

/**
 * cliente que percorre a matriz para testar se há 1 número oculto no quadrado perfeito
 * @param m matriz a resolver
 * @return
 */

int clientOcultoBox (MATRIX *m){
    int cont=0;
    BOX *current=m->pfirst,*aux=m->pfirst;
    while(1) {                                                  // TESTAR O NUMERO SOZINHO
        while(aux->lin!=current->lin)
            aux=aux->S;
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return cont;
        cont = numeroOcultoBox(m,current);
        if(current->lin==m->N-1){
            return 0;
        }
        if(current->E!=NULL)                                // proxima coluna
            current=current->E;
        else{                                                 // proxima linha
            current=aux->S;
            aux=aux->S;
        }
    }
}

/**
 * funçao que testa se há 1 número oculto 1 na linha
 * @param m matriz a resolver
 * @param b box em teste
 * @return
 */
int numeroOcultoLin (MATRIX *m,BOX *b){
    BOX *temp=m->pfirst,*aux=m->pfirst,*point=NULL,*aux2;
    int count=0;

    while(temp->lin!=b->lin)
        temp=temp->S;
    aux = temp;
    aux2 = temp;
    for (int k = 1; k <= m->N; k++) {
        for (int j = 1; j <= m->N ; j++) {
            if(count>1) break;
            if(*(temp->aux+(k-1))==k && temp->val==0){
                point=temp;
                count++;
            }
            temp=temp->E;
        }
        if(count==1){
            point->val=k;
            print_array(*point);
            fillAuxArray0s(*m,point);
            printf("%d-%d = %d\n",point->lin,point->col,k);
            return 1;
        }
        temp=aux;
    }
    return 0;
}

/**
 * funçao que testa se há 1 número oculto 1 na linha
 * @param m matriz a resolver
 * @param b box em teste
 * @return
 */
int numeroOcultoCol (MATRIX *m,BOX *b){
    BOX *temp=m->pfirst,*aux,*point=NULL;
    int count=0;

    while(temp->col!=b->col)
        temp=temp->E;
    aux=temp;
    for (int k = 1; k <= m->N; k++) {
        for (int j = 1; j <= m->N ; j++) {
            if(count>1) break;
            if(*(temp->aux+(k-1))==k){
                point=temp;
                count++;
            }
            temp=temp->S;
        }
        if(count==1){
            point->val=k;
            return 1;
        }
        temp=aux;
    }
    return 0;
}

/**
 * funçao que testa se há 1 número oculto 1 no quadrado perfeito
 * @param m matriz a resolver
 * @param b box em teste
 * @return
 */

int numeroOcultoBox (MATRIX *m,BOX *b){
    int lin=b->lin - b->lin%3 , col=b->col - b->col%3;
    BOX *temp=m->pfirst,*aux=m->pfirst,*point=NULL;
    while (temp!=NULL){
        if(temp->lin==lin && temp->col==col)
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
    int count=0;
    for (int l = 1; l <= m->N; l++) {
        for (int i = 0; i < m->N+1; i++) {
            if(count>1) break;
            if(*(temp->aux+(l-1))==l){
                point=temp;
                count++;
            }
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
        if(count==1){
            point->val=k;
            return 1;
        }
    }
    return 0;
}

/**
 * cliente que percorre a matriz para ver se há 1 duplo par oculto na linha
 * @param m matriz a resolver
 * @return
 */
int clientParOcultoLin(MATRIX *m){                                  //cliente par sozinho linha
    BOX *current = m->pfirst,*aux=m->pfirst;
    while(1) {                                                  // TESTAR PARES SOZINHOS
        while(aux->lin!=current->lin){
            if(aux->S!=NULL)
                aux=aux->S;
            else
                return 0;
        }
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return 0;
        parOcultoLin(m,current);
        if(current->lin==m->N-1){
            return 0;
        }
        if(current->E!=NULL)                                // proxima coluna
            current=current->E;
        else{                                                 // proxima linha
            current=aux->S;
            aux=aux->S;
        }
    }
}

/**
 * função que testa se há 1 duplo par oculto na linha
 * @param m matriz a resolver
 * @param b box em teste
 */
void parOcultoLin(MATRIX *m, BOX *b){
    BOX *temp=m->pfirst;
    BOX *array[m->N];
    int i=0;
    while(temp->lin!=b->lin)
        temp=temp->S;

    while (temp!=NULL){            //guarda num array auxiliar todas as box's que tenham apenas 2 possibilidades
        if(temp->val==UNASSIGNED){
            if(find2inArray(m,temp)==2){
                *(array+i)=temp;
                i++;
            }
        }
        temp=temp->E;
    }
    for (int j = 0; j < i-1; j++) {                         //comparo se as 2 possibilidades são as mesmas, se sim removo essas 2 de todos os outros
        for (int k = j+1; k < i; k++) {
            if(compare2arrays(*(*(array+j)),*(*(array+k)))) {
                removeDoublePairsLin(m, *(*(array + j)), *(*(array + k)));
            }
        }
    }
}


/**
 * cliente que percorre a matriz para ver se há 1 duplo par oculto na coluna
 * @param m matriz a resolver
 * @return
 */
int clientParOcultoCol(MATRIX *m){                                  //cliente par sozinho linha
    BOX *current = m->pfirst,*aux=m->pfirst;
    while(1) {                                                  // TESTAR PARES SOZINHOS
        while(aux->lin!=current->lin){
            if(aux->E!=NULL)
                aux=aux->E;
            else
                return 0;
        }
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return 0;
        parOcultoCol(m,current);
        if(current->col==m->N-1){
            return 0;
        }
        if(current->S!=NULL)                                // proxima coluna
            current=current->S;
        else{                                                 // proxima linha
            current=aux->E;
            aux=aux->E;
        }
    }
}


/**
 * função que testa se há 1 duplo par oculto na coluna
 * @param m matriz a resolver
 * @param b box em teste
 */
void parOcultoCol(MATRIX *m, BOX *b){
    BOX *temp=m->pfirst;
    BOX *array[m->N];
    int i=0;
    while(temp->col!=b->col)
        temp=temp->E;

    while (temp!=NULL){                                  //guarda num array auxiliar todas as box's que tenham apenas 2 possibilidades
        if(temp->val==UNASSIGNED){
            if(find2inArray(m,temp)==2){
                *(array+i)=temp;
                i++;
            }
        }
        temp=temp->S;
    }
    for (int j = 0; j < i-1; j++) {                         //comparo se as 2 possibilidades são as mesmas, se sim removo essas 2 de todos os outros
        for (int k = j+1; k < i; k++) {
            if(compare2arrays(*(*(array+j)),*(*(array+k)))) {
                removeDoublePairsCol(m, *(*(array + j)), *(*(array + k)));
            }
        }
    }
}

/**
 * cliente que percorre a matriz para ver se há 1 duplo par oculto no quadrado perfeito
 * @param m matriz a resolver
 * @return
 */
int clientParOcultoBox (MATRIX *m){
    BOX *current = m->pfirst,*aux=m->pfirst;
    double s = sqrt(m->N);
    while(1) {                                                  // TESTAR PARES SOZINHOS
        while(aux->lin!=current->lin)
            aux=aux->S;
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return 0;
        parOcultoBox(m,current);
        if(current->lin==m->N-1){
            return 0;
        }
        if(current->E!=NULL)                                // proxima coluna
            current=current->E;
        else{                                                 // proxima linha
            current=aux->S;
            aux=aux->S;
        }
    }
}

/**
 * função que testa se há 1 duplo par oculto no quadrado perfeito
 * @param m
 * @param b
 */
void parOcultoBox (MATRIX *m,BOX *b){
    BOX *array[m->N];
    int lin=b->lin - b->lin%3 , col=b->col - b->col%3;
    BOX *temp=m->pfirst,*aux=m->pfirst,*point=NULL;
    while (temp!=NULL){
        if(temp->lin==lin && temp->col==col)
            break;
        if(temp->E!=NULL){
            temp=temp->E;
        }  else  {
            temp=aux->S;
            aux=aux->S;
        }
    }
    aux = temp;
    int j=1,k=1,y=0;

    for (int l = 1; l <= m->N; l++) {
        for (int i = 0; i < m->N+1; i++) {
                if(temp->val==UNASSIGNED){                              //guarda num array auxiliar todas as box's que tenham apenas 2 possibilidades
                    if(find2inArray(m,temp)==2){
                        *(array+y)=temp;
                        y++;
                    }
                }
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
    }
    for (int u = 0; u < y-1; u++) {                         //comparo se as 2 possibilidades são as mesmas, se sim removo essas 2 de todos os outros
        for (int h = u+1; h < y; h++) {
            if(compare2arrays(*(*(array+u)),*(*(array+h)))) {
                removeDoublePairsBox(m, *(*(array + u)), *(*(array + h)));
            }
        }
    }
}

/**
 * função auxiliar que compara se 2 arrays de possibilidades são iguais
 * @param b1 box a comparar
 * @param b2 box a comparar
 * @return
 */
int compare2arrays(BOX b1, BOX b2){                         // comparo os 2 arrays das 2 box's que recebe, 0 se forem diferentes, 1 se forem iguais
    for (int i = 0; i < 9; i++) {
        if(*(b1.aux+i)==*(b2.aux+i))
            continue;
        else
            return 0;
    }
    return 1;
}

/**
 * função auxiliar que testa se um array de uma box tem apenas 2 possibilidades
 * @param m matriz a resolver
 * @param b box a testar
 * @return
 */
int find2inArray (MATRIX *m,BOX *b){
    int contador=0;
    for (int i = 0; i < m->N; i++) {
        if(*(b->aux+i)!=UNASSIGNED)
            contador++;
        if(contador>2) return -1;
    }
    return contador;                             //retorna 2 se só houver 2 números iguais e !=0 em ambos os arrays, caso contrário -1
}

/**
 * função que remove dois pares dos arrays de possibilidades de uma linha
 * @param m matriz a resolver
 * @param b1 box que contém o par
 * @param b2 box que contém o par
 */
void removeDoublePairsLin(MATRIX *m,BOX b1,BOX b2){                //remove o par de todos os outros arrays
    BOX *temp=m->pfirst;
    int i=0;
    while(temp->lin!=b1.lin)
        temp=temp->S;
    //printf("REMOVING - %d %d - %d %d\n",b1.lin,b1.col,b2.lin,b2.col);
    for (i = 0; i< m->N; i++) {                                 //percorro todas as box's dessa linha
        if(temp->val==UNASSIGNED){
            if((temp->lin!=b1.lin && temp->col!=b1.col) && (temp->lin!=b2.lin && temp->col!=b2.col)){       // se nao forem as box's do double pair
            for (int j = 0; j < m->N; j++) {
                if(*(b1.aux+j)>=0 && *(temp->aux+j)==*(b1.aux+j)) {
                    *(temp->aux + j) = UNASSIGNED;
                }
            }

            }
        }
        temp=temp->E;
    }
}

/**
 * função que remove dois pares dos arrays de possibilidades de uma coluna
 * @param m matriz a resolver
 * @param b1 box que contém o par
 * @param b2 box que contém o par
 */
void removeDoublePairsCol(MATRIX *m,BOX b1,BOX b2){                //remove o par de todos os outros arrays
    BOX *temp=m->pfirst;
    int i=0;
    while(temp->col!=b1.col)
        temp=temp->E;
    //printf("REMOVING - %d %d - %d %d\n",b1.lin,b1.col,b2.lin,b2.col);
    for (i = 0; i< m->N; i++) {
        if(temp->val==UNASSIGNED){
            if((temp->lin!=b1.lin && temp->col!=b1.col) && (temp->lin!=b2.lin && temp->col!=b2.col)){
                for (int j = 0; j < m->N; j++) {
                    if (*(b1.aux + j) >= 0 && *(temp->aux + j) == *(b1.aux + j)) {
                        *(temp->aux + j) = UNASSIGNED;
                    }
                }
            }
        }
        temp=temp->S;
    }
}

/**
 * função que remove dois pares dos arrays de possibilidades de uma coluna
 * @param m matriz a resolver
 * @param b1 box que contém os pares
 * @param b2 box que contém os pares
 */
void removeDoublePairsBox (MATRIX *m,BOX b1,BOX b2){
    int lin=b1.lin - b1.lin%3 , col=b1.col - b1.col%3;
    BOX *temp=m->pfirst,*aux=m->pfirst,*point=NULL;
    while (temp!=NULL){
        if(temp->lin==lin && temp->col==col)
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
    //printf("REMOVING - %d %d - %d %d\n",b1.lin,b1.col,b2.lin,b2.col);
    for (int l = 1; l <= m->N; l++) {
        for (int i = 0; i < m->N+1; i++) {
            if(temp->val==UNASSIGNED){
                if((temp->lin!=b1.lin && temp->col!=b1.col) || (temp->lin!=b2.lin && temp->col!=b2.col)){       // se nao forem as box's do double pair
                    for (int u = 0; u < m->N; u++) {
                        if(*(b1.aux+u)>=0 && *(temp->aux+u)==*(b1.aux+u)) {
                            *(temp->aux + u) = UNASSIGNED;
                        }
                    }
                }
            }
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
    }
}

/*
//BOX LINE REDUCTION
//PERCORRER LINHA A LINHA
//PARA CADA LINHA VARRER OS ARRAYS DE POSSIBILIDADES EM PARALELO

int clientBoxLineReduction(MATRIX *m){
    int cont=0;
    BOX *current=m->pfirst,*aux=m->pfirst,*temp;

    while(1) {     // TESTAR O NUMERO SOZINHO OCULTO
        while(aux->lin!=current->lin){
            if(aux->S!=NULL)
                aux=aux->S;
            else
                return cont;
        }
        current=FindUnassignedLocationMelhorada(*m,current);
        if(current==NULL)
            return cont;
        boxLineReduction(m,current);
        if(current->lin==m->N-1){
            return cont;
        }
        else if(current->E!=NULL)                                // proxima coluna
            current=current->E;
        else{                                                 // proxima linha
            current=aux->S;
            aux=aux->S;
        }
    }
}

void boxLineReduction(MATRIX *m,BOX *b){
    BOX *temp=m->pfirst,*aux,*point=NULL;
    BOX *array[m->N];
    while(temp->lin!=b->lin)
        temp=temp->S;
    aux=temp;
    int i=0,t=0;
    for (int k = 1; k <= m->N; k++) {                                //guarda as possibilidades de box's para k numero
        for (int j = 1; j <= m->N ; j++) {
            if(temp->val==0 && *(temp->aux+(k-1))!=0){
                *(array+i)=temp;
                i++;
            }
            temp=temp->E;
        }
        if(i<sqrt(m->N)-1){                                         // se tiver menos possibilidades que  o maximo de possibilidades de uma box numa linha
            for (t = 0; t < i-1; t++) {                         //comparo se as 2 possibilidades são as mesmas, se sim removo essas 2 de todos os outros
                for (int l = t+1; l < i; l++) {
                    if(!compare2BoxsSquare(*m,*(*(array+t)),*(*(array+l)))) {
                        t=36;                                           //sai do for de fora
                        break;
                    }
                }
            }
            if(t!=36){
                temp=aux;
                for (int o = 1; o <= m->N ; o++) {
                    if(temp->val==0 && *(temp->aux+(k-1))!=0){
                        removeFromAux(temp,k);
                    }
                    print_array(*temp);
                    temp=temp->E;
                    print_array(*temp);
                }
            }
        }
        temp=aux;
    }

}
*/

/**
 * função auxiliar que compara se duas box's estão no mesmo quadrado perfeito
 * @param m matriz a resolver
 * @param b1 box em teste
 * @param b2 box em teste
 * @return
 */
int compare2BoxsSquare(MATRIX m,BOX b1,BOX b2){
    int aux=(int)sqrt(m.N);
    for (int i = aux-1; i < m.N-1; i+=aux) {
        if( b1.lin<i && b2.lin<i && b1.col<i && b2.col<i)                   //se tiverem no mesmo quadrado return 1
            return 1;
    }
    return 0;
}

/**
 * função que encontra o próximo 0 na matriz
 * @param m matriz a resolver
 * @param b box em teste
 * @return
 */

BOX* FindUnassignedLocationMelhorada(MATRIX m,BOX *b) {
    BOX *aux=m.pfirst;
    while(aux->lin!=b->lin)
        aux=aux->S;
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

/**
 * função que retira ao array de possibilidades todos os números dessa linha
 * @param m matriz a resolver
 * @param b box em teste
 */

void checkMoreThenOneNumberInRow(MATRIX *m,BOX *b){     //checka a linha para ver se so ha 1 numero possivel
    BOX *temp=m->pfirst;
    while(temp->lin!=b->lin)
        temp=temp->S;
    while (temp!=NULL){
        if(temp->val!=UNASSIGNED)
            removeFromAux(b,temp->val);
        temp=temp->E;
    }
}

/**
 *  função que retira ao array de possibilidades todos os números dessa coluna
 * @param m matriz a resolver
 * @param b box em teste
 */
void checkMoreThenOneNumberInCol(MATRIX *m,BOX *b){      //checka a coluna para ver se so ha 1 numero possivel
    BOX *temp=m->pfirst;
    while(temp->col!=b->col)
        temp=temp->E;
    while (temp!=NULL){
        if(temp->val!=UNASSIGNED)
            removeFromAux(b,temp->val);
        temp=temp->S;
    }
}

/**
 *  função que retira ao array de possibilidades todos os números dessa linha
 * @param m matriz a resolver
 * @param b box em teste
 */
void checkMoreThenOneNumberInBox(MATRIX *m,BOX *b){      //checka a box para ver se so ha 1 numero possivel
    for (int i = 1; i<= m->N; i++) {
        if(UsedInBox(m, b->lin - b->lin%(int)sqrt(m->N) , b->col - b->col%(int)sqrt(m->N),i))
            removeFromAux(b,i);
    }
}

/**
 * função auxiliar que teste se só há 1 possibilidade para aquela box
 * @param m matriz a resolver
 * @param b box em teste
 * @return
 */
int checkAuxArrayOnlyHave1(MATRIX m,BOX b){               // verifica no array de possibilidades, se so há 1 numero posssivel naquela celula
    int n=0,track=0;
    if(b.val!=0) return -1;
    for (int j = 0; j < m.N; j++) {
        if(*(b.aux+j)>0){
            n++;
            track=j;
        }
        if(n>1)
            return -1;
    }
    return track;
}

/**
 * função auxiliar para preencher o array de possibilidades
 * @param m matriz a resolver
 * @param b box em teste
 */

void fillAuxArray(MATRIX m,BOX *b){                        // volta a preencher o array de possibilidades
    for (int i = 0; i < m.N; i++) {
        *(b->aux+i)=i+1;
    }
}

/**
 * função auxiliar para preencher o array de possibilidades com 0's
 * @param m matriz a resolver
 * @param b box em teste
 */

 void fillAuxArray0s(MATRIX m,BOX *b){
    for (int i = 0; i < m.N; i++) {
        *(b->aux+i)=UNASSIGNED;
    }
}

/**
 * função que remove um número do array de possibilidades
 * @param b box em questão
 * @param val valor a remover
 */
void removeFromAux(BOX *b,int val){                // remove o numero do array
    *(b->aux+(val-1))=0;
}


/**
 * imprime o array de possibilidades
 * @param m matriz a resolver
 * @param b box em questão
 */

void printAuxArray(MATRIX m,BOX b){
    for (int i = 0; i < m.N; i++) {
        printf("%d ",*(b.aux+i));
    }
    printf("\n");
}

/**
 * função que lê n matrizes de um ficheiro para a estrutura
 * @param a estrutura que guarda as matrizes
 */
void ler_txt(MATRIXS *a) {
    FILE *fp;
    MATRIX m;
    int p=0;
    fp = fopen("C:\\Users\\bruno\\Desktop\\projetofase2\\data\\matrix.txt", "r");
    initQueue(a);
    if (fp != NULL) {
        int i,j;
        fscanf(fp, "%d",&p);
        for(int k=0;k< p;k++) {
            fscanf(fp, "%d", &m.N);
            int aux[m.N][m.N];
            for (i = 0; i < m.N; i++) {
                for (j = 0; j < m.N; j++)
                    fscanf(fp, "%d ", &aux[i][j]);
                fscanf(fp,"\n");
            }
            create_matrix(&m, m.N, aux);
            enqueue(a, m);

            print_matrix(m);
            printf("\n");
        }
    }
    fclose(fp);
}

/**
 * guarda os tabuleiros resolvidos
 * @param a estrutura que guarda as matrizes
 */
void gerar_txt(MATRIXS a){
    FILE *fp;
    fp=fopen("C:\\Users\\bruno\\Desktop\\projetofase2\\data\\tabuleiros.txt","w");
    if(fp!=NULL){
        printf("\n");
        for (int i = 0; i < a.N; i++) {
            BOX* temp= a.parray[i].pfirst, *aux= a.parray[i].pfirst;
            while (temp != NULL) {
                fprintf(fp,"%d ",temp->val);
                if (temp->E == NULL) {
                    temp = aux->S;
                    aux = aux->S;
                    fprintf(fp,"\n");
                } else
                    temp = temp->E;
            }
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
}

/**
 * guarda os tabuleiros resolvidos
 * @param b estrutura que guarda as matrizes
 */
void gerar_solucoes_bin(MATRIXS b){
    FILE *fp;
    fp=fopen("C:\\Users\\bruno\\Desktop\\projetofase2\\data\\solutions.bin","wb");
    if(fp!=NULL){
        for (int i = 0; i < b.N; i++) {
            BOX* temp= b.parray[i].pfirst, *aux= b.parray[i].pfirst;
            while (temp != NULL) {
                fwrite(&temp->val, sizeof(int), 1, fp);
                if (temp->E == NULL) {
                    temp = aux->S;
                    aux = aux->S;
                } else
                    temp = temp->E;
            }
        }
    }
    fclose(fp);
}

/**
 * lê os tabuleiros resolvidos
 * @param b
 */
void read_solutions_bin(MATRIXS b){
    FILE *fp;
    fp=fopen("C:\\Users\\bruno\\Desktop\\projetofase2\\data\\solutions.bin","rb");
    printf("\n");
    if(fp!=NULL){
        for (int i = 0; i < b.N; i++) {
            BOX* temp= b.parray[i].pfirst, *aux= b.parray[i].pfirst;
            while (temp != NULL) {
                fread(&temp->val, sizeof(int), 1, fp);
                if (temp->E == NULL) {
                    temp = aux->S;
                    aux = aux->S;
                } else
                    temp = temp->E;
            }
            print_matrix(b.parray[i]);
            printf("\n");
        }
    }
    fclose(fp);
}

void printGrid(int grid[M][M]) {
    for (int row = 0; row < M; row++) {
        for (int col = 0; col < M; col++)
            printf("%2d", grid[row][col]);
        printf("\n");
    }
}

