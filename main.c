//Aluno: Jonatha Salles Menezes
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define TAM 10
//---------------------------------------------------------------------------------------------------------------------------//
void render_player(char mat[TAM][TAM], int mI, int mJ, int iBody[3],int jBody[3],int *iHead,int *jHead,int *iTail,int *jTail);
int move_player(char mat[TAM][TAM], int iBody[3],int jBody[3],int *iHead,int *jHead,int *iTail,int *jTail,int *didntMove);
void render(char mat[TAM][TAM], int iBody[3],int jBody[3],int *iHead,int *jHead,int *iTail,int *jTail);
void count_visits(int *visitedQ ,int *iHead, int *jHead, char visited[TAM][TAM]);
void results(int moveCount, int moves, int numObs, int *visitedQ);
void placeObs(int numObs,int obsCont, char mat[TAM][TAM]);
void clear(char mat[TAM][TAM],char visited[TAM][TAM]);
void get_head(int *i,int *j);
int draw_menu();
int get_moves();
int get_num();
//----------------------------------------------------------------------------------------------------------------------=----//
int main()
{
  setlocale(LC_ALL,"");
  int gameState = 3, exit=0, reset=1, normal=2, menu = 3,i, j, numObs=0,iHead, jHead, iTail, jTail,
      obsCont=0, headI=0, headJ=0, moves, iBody[3], jBody[3],
      moveCount=1, didntMove=0,moved, mode, visitedQ=1;
  char mat[TAM][TAM], visited[TAM][TAM];

  do{
   if(gameState==menu){
    numObs=0, obsCont=0, headI=0, headJ=0,moveCount=1, didntMove=0, visitedQ=1;
    mode = draw_menu();
    if(mode == 1)gameState = reset;
    else gameState = exit;
   }

   if(gameState==reset){
    gameState = normal;
    numObs = get_num();
    clear(mat,visited);
    get_head(&headI, &headJ);
    render_player(mat, headI, headJ,iBody,jBody,&iHead,&jHead,&iTail,&jTail);
    placeObs(numObs, obsCont, mat);
    render(mat,iBody,jBody,&iHead,&jHead,&iTail,&jTail);
   }
   if(gameState==normal){
    moves = get_moves();
    render(mat,iBody,jBody,&iHead,&jHead,&iTail,&jTail);
    while(moveCount<=moves){
     moved = move_player(mat,iBody,jBody,&iHead,&jHead,&iTail,&jTail,&didntMove);
     if(moved == 1){render(mat,iBody,jBody,&iHead,&jHead,&iTail,&jTail);
      count_visits(&visitedQ,&iHead,&jHead,visited);
      printf("\n\t\t\t\t\tMovimentos realizados: %i/%i\n",moveCount,moves);
      sleep(1);
      moveCount++;
     }
     else break;
    }
    results(moveCount,moves,numObs,&visitedQ);
    gameState = menu;
   }
  }while(gameState != exit);
  return 0;
}

void placeObs(int numObs,int obsCont,char mat[TAM][TAM])
{
   int i,j;
    obsCont=0;
    srand(time(0));
    while(obsCont<numObs){
     i = rand()%TAM;
     j = rand()%TAM;
     if(mat[i][j] == '_' ){mat[i][j]='X'; obsCont++;}
    }
}
void render(char mat[TAM][TAM], int iBody[3],int jBody[3],int *iHead,int *jHead,int *iTail,int *jTail)
  {
   system("cls");
   int i, j, k;
   for(i=0;i<TAM;i++){
     if(i==0)
      printf("\n\t\t\t\t\t _______________________________________________\n\t\t\t\t\t|    ___ ___ ___ ___ ___ ___ ___ ___ ___ ___    | " );
     printf("\n\t\t\t\t\t|");
     for(j=0;j<TAM;j++){
      if(j==0) printf("   |");
      if(i == *iHead && j == *jHead)printf("_C_|");
      else if(i == *iTail && j == *jTail)printf("_._|");
      else if(i == iBody[0] && j == jBody[0]) printf("_*_|");
      else if(i == iBody[1] && j == jBody[1]) printf("_*_|");
      else if(i == iBody[2] && j == jBody[2]) printf("_*_|");
      else if(mat[i][j]=='X')printf("_%c_|",mat[i][j]);
      else printf("___|");
      if(j==9) {printf("   |");}
      if(j==9 && i==9)
        printf("\n\t\t\t\t\t|_______________________________________________|");
     }
   }
  }

int get_num()
{
    int numObs;
    do{
     system("cls");
     printf("\n\n\n\n\n\n\n\n\t\t\t\t\tIndique o número de obstáculos -> ");
     scanf("%i",&numObs);
     if(numObs>80 || numObs<0){
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\tEntrada inválida!");
        sleep(1);
     }
    }while(numObs>80 || numObs<0);
    return numObs;
}

void clear(char mat[TAM][TAM], char visited[TAM][TAM])
{
   int i, j;
   for(i=0;i<TAM;i++){
    for(j=0;j<TAM;j++){
     mat[i][j] = '_';
     visited[i][j] = 'N';
    }
   }
}

void render_player(char mat[TAM][TAM], int mI, int mJ, int iBody[3],
                   int jBody[3],int *iHead,int *jHead,int *iTail,int *jTail)
{
    int i=0, auxI, auxJ;
    srand(time(0));
    mat[mI][mJ] = 'M';
    *iHead = mI;
    *jHead = mJ;
    while(i<4){
     if(rand()%2 == 0){
      if(rand()%2 == 0){
       if(mI<9 && mat[mI+1][mJ] == '_'){
        mI++; mat[mI][mJ] = 'M'; if(i<3) {iBody[i] = mI; jBody[i] = mJ;i++;}
       else {*iTail = mI; *jTail = mJ;i++;}}}
      else{
       if(mI>0 && mat[mI-1][mJ] == '_') {
        mI--; mat[mI][mJ] = 'M'; if(i<3) {iBody[i] = mI; jBody[i] = mJ;i++;}
       else {*iTail = mI; *jTail = mJ;i++;}}}
     }
     else {
      if(rand()%2 == 0){
       if(mJ<9 && mat[mI][mJ+1] == '_'){
        mJ++;mat[mI][mJ] = 'M'; if(i<3) {iBody[i] = mI; jBody[i] = mJ;i++;}
       else {*iTail = mI; *jTail = mJ;i++;}}}
      else{
        if(mJ>0 && mat[mI][mJ-1] == '_'){
          mJ--;mat[mI][mJ] = 'M'; if(i<3) {iBody[i] = mI; jBody[i] = mJ;i++;}
        else {*iTail = mI; *jTail = mJ;i++;}}}
     }
    }
}

void get_head(int *i, int *j)
{
    int mI, mJ;
    do{
       system("cls");
       printf("\n\n\n\n\n\n\n\n\t\t\t\tIndique a linha inicial da cabeça da minhoca(1 a 10) -> ");
       scanf("%i", &mI);
       if(mI<1 || mI > 10){
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\tEntrada inválida!");
        sleep(1);
        fflush(stdin);
       }
    }while(mI<1 || mI > 10);

    do{
       system("cls");
       printf("\n\n\n\n\n\n\n\n\t\t\t\tIndique a coluna inicial da cabeça da minhoca(1 a 10) -> ");
       scanf("%i", &mJ);
       if(mJ < 1 || mJ > 10){
        system("cls");
        printf("\n\n\n\n\n\n\n\n\t\t\t\tEntrada inválida!");
        sleep(1);
        fflush(stdin);
       }
    }while(mJ < 1 || mJ > 10);
    *i = mI-1;
    *j = mJ-1;
}

int get_moves()
{
    int moves;
    do{
     printf("\n\t\t\t\t\tQuantos movimentos a minhoca deve realizar? -> ");
     scanf("%i", &moves);
     if(moves < 0){
        printf("\n\t\t\t\t\tEntrada inválida!\n");
        sleep(1);
        fflush(stdin);
       }
    }while(moves < 0);

 return moves;
}

int move_player(char mat[TAM][TAM], int iBody[3],int jBody[3],int *iHead,int *jHead,int *iTail,int *jTail,int *didntMove)
{

   int moveHead = 1, auxI, auxJ, mI, mJ, i, up, down, left , right, moved=1;
   if(moved == 1){moved=0;up=1;down=1;right=1;left=1;*didntMove=0;}
   mat[*iTail][*jTail] = '_';
   mat[iBody[0]][jBody[0]] = 'M'; mat[iBody[1]][jBody[1]] = 'M'; mat[iBody[2]][jBody[2]] = 'M';
   mI = *iHead;
   mJ = *jHead;
   auxI = mI;
   auxJ = mJ;
   moveHead = 1;
   do{
    srand(time(0));
    if(rand()%2 == 0){
      if(rand()%2 == 0){
       if(mI<9 && mat[mI+1][mJ] == '_'){mI++;moveHead=0;*iHead = mI; *jHead = mJ;moved=1;}
       else{down=0;}
      }
      else{
       if(mI>0 && mat[mI-1][mJ] == '_'){mI--;moveHead=0;*iHead = mI; *jHead = mJ;moved=1;}
       else {up=0;}
     }
    }
     else{
      if(rand()%2 == 0){
       if(mJ<9 && mat[mI][mJ+1] == '_') {mJ++;moveHead=0;*iHead = mI; *jHead = mJ;moved=1;}
       else {right=0;}
      }
      else{
       if(mJ>0 && mat[mI][mJ-1] == '_') {mJ--;moveHead=0;*iHead = mI; *jHead = mJ;moved=1;}
       else {left=0;}
      }
     }
     if(up==0 && down==0 && left==0 && right==0){moveHead=0;*didntMove=1;printf("\n\t\t\t\t\tImpossível se mover!\n");sleep(3);}
    }while(moveHead==1);

   if(moveHead==0 && moved==1){
    *iTail = iBody[2];
    *jTail = jBody[2];
    iBody[2] = iBody[1];
    jBody[2] = jBody[1];
    iBody[1] = iBody[0];
    jBody[1] = jBody[0];
    iBody[0] = auxI;
    jBody[0] = auxJ;
   }
   mat[*iHead][*jHead] = 'M';
   mat[*iTail][*jTail] = 'M';

   return moved;
}

void results(int moveCount, int moves, int numObs, int *visitedQ)
{
    int conf;
    system("cls");
    printf("\n\t\t\t\t\t _______________________________________________" );
    printf("\n\t\t\t\t\t|             RESULTADOS DO PASSEIO             |");
    printf("\n\t\t\t\t\t  Número de obstáculos -> %i                     ",numObs);
    printf("\n\t\t\t\t\t  Casas visitadas -> %i/100 (%i%%)               ",*visitedQ,*visitedQ);
    printf("\n\t\t\t\t\t  Casas não visitadas -> %i                      ",100-(*visitedQ));
    printf("\n\t\t\t\t\t  Movimentos concluídos -> %i/%i (%.1f%%)        ",moveCount-1,moves,(float)(moveCount-1)/moves * 100);
    printf("\n\t\t\t\t\t|_______________________________________________|");
    sleep(3);
    printf("\n\t\t\t\t\t             Digite 1 para voltar  "); do{scanf("%i",&conf);}while(conf != 1);
}

int draw_menu()
{
   int mode;
   do{
    system("cls");
    printf("\n\t\t\t\t ===============================================" );
    printf("\n\t\t\t\t  Bem-Vindo ao passeio da minhoca desgovernada!" );
    printf("\n\t\t\t\t    *Desenvolvido por Jonatha Salles Menezes*" );
    printf("\n\t\t\t\t ===============================================" );
    printf("\n\t\t\t\t  1) Começar o passeio" );
    printf("\n\t\t\t\t  2) Sair" );
    printf("\n\t\t\t\t ===============================================" );
    printf("\n\t\t\t\t  O que deseja fazer? -> " ); scanf("%i",&mode);
   }while(mode!=1 && mode!=2);
 return mode;
}

void count_visits(int *visitedQ, int *iHead, int *jHead, char visited[TAM][TAM])
{
   int visits; visits = *visitedQ;
   if(visited[*iHead][*jHead] != 'Y') {visited[*iHead][*jHead] = 'Y'; visits++;}
   *visitedQ = visits;
}
