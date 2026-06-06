#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "gestionProcessus.h"

int printPID(char * S){
  printf("%s %d",S,getpid());
  return 0;
}
// La chaîne de caractère précédée du numéro d'identification de son père.
int printPPID(char * S){
  printf("%s %d",S,getppid());
  return 0;
}
// La chaîne de caractère précédée des deux informations ci-dessus.
int printIDS(char * S){
  printf("%s : <ppid-%d,pid-%d> \n\n",S,getppid(),getpid());
  return 0;
}
