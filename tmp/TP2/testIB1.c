// testIB1.c : Un programme qui affiche "bonjour" précédé du numéro
//  d'identification du processus et de son père,
//  lorsqu'on ne lui passe pas d'arguments.
//  Si on lui passe au moins un argument,
//  le programme affiche le premier argument.

#include "gestionProcessus.h"
int main(int n , char * t[]){
  if(n<2){
    printIDS("bonjour");
    return 0;
  }
  printIDS(t[1]);
  return 0;
}

