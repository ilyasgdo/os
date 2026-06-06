#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "calcule.h"

#define N 2048
#define M 2048
int main(){
    int ** tab = (int **)malloc(N*sizeof(int*));
    
    for(int i=0 ;i<N;i++){
        tab[i]=(int*)malloc(M*sizeof(int));
    }

    for(int i=0 ;i<N;i++){
        for(int j=0 ;j<M;j++){
        tab[i][j]=i+j;
        }
    }
    printf("sommme 2 : %d",somme2(tab,N,M));


    for(int i=0 ;i<N;i++){
        free(tab[i]);
    }
    free(tab);
    return 0;

}