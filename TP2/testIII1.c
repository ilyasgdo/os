//testIII1.c : Un programme qui se dédouble, puis pour lequel chacun des deux 
// processus ouvre le fichier fichierTest.txt donné plus bas, y lit une ligne et ferme le fichier.
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "gestionFichier.h"
int ouvrirLire(){
    int des=getDescripteur("src.txt");
    if(des<0){
        perror("err open");
        exit(1);
    }
    printf(" \n%s \n",litLigne(des));
    close(des);
    return 0;
}
int main(){
    int pid = fork();
    switch(pid){
        case -1:perror("err fork");exit(1);
        break;
        case 0: printf("\nfils : \n");ouvrirLire();
        break;
        default:printf("\npere : \n");ouvrirLire();
        break;
    }
    return 0;
}