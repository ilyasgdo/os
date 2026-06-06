
#include "gestionFichier.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  int des =
      getDescripteur("src.txt");
      
  printf("%s\n", litLigne(des));
  close(des);
  return 0;
}
