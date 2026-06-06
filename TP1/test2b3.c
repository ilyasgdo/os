#include "gestionFichier.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int n , char * argv[]){
  int des;
  if(n >1 ){
    des= getDescripteur(argv[1]);
  }
  else{
    des= getDescripteur("src.txt");
  }
  if(des<0){
    perror("err open");
  }
  char  * txt;
  while(1){
    txt = litLigne(des);
    if(txt ==NULL){
      break;
    }
    printf("\n%s\n",txt);
  }
  close(des);
  free(txt);
  return 0;
}