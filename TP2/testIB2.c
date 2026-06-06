// testIB2.c : Un programme qui se dédouble par l'appel fork
//  et pour lequel les processus père et fils affichent
//  respectivement "père" et "fils" précédés des mêmes
//  informations que ci-dessus.

#include "gestionProcessus.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void fils(){
  printIDS("\nfils");
}
void pere(){
  printIDS("\npere");

}
int main(){
  int pid = fork();
  switch(pid){
    case -1 : perror("err fork"); 
    break;
    case 0 : fils();
    break;
    default : pere(); wait(NULL);
  }
  return 0;

}
