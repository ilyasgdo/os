#include "gestionFichier.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  int des =
      getDescripteur("/Users/ilyas/Documents/cours/os/tmp/TP1/src.txt");
char * tmp= litDixCaracteres(des);
  printf("%s\n",tmp );
  close(des);
  free(tmp);
  return 0;
}
