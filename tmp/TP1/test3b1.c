
#include "gestionFichier.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int n, char *argv[]) {
int des;
  if(n >1 ){
    des= getDescripteur(argv[1]);
  }
  else{
    des= getDescripteur("src.txt");
  }
  int des2=getDescripteur("des.txt");
  if(des<0){
    perror("err open");
  }
  char  * txt;
  while(1){
    txt = litLigne(des);
    if(txt ==NULL){
      break;
    }
    ecritLigne(des2,txt);
    printf("\n%s\n",txt);
  }
  close(des);
  close(des2);
  free(txt);
  return 0;
}
