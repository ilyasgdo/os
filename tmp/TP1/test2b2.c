
#include "gestionFichier.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int n, char *argv[]) {

  if (n <2) {
    return 0;
  }

  int des = getDescripteur(argv[1]);

  printf("%s\n", litLigne(des));
  return 0;
}
