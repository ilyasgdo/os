#include "gestionFichier.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getDescripteur(const char *path) {
    int descripteur = open(path, O_RDWR);
    if (descripteur == -1) {
        return -1;
    }
    return descripteur;
}

char *litDixCaracteres(int descripteur) {
    char *res = malloc(BUFFERDIX * sizeof(char));
    ssize_t lus;

    if (res == NULL) {
        return NULL;
    }

    lus = read(descripteur, res, BUFFERDIX - 1);
    if (lus < 0) {
        free(res);
        return NULL;
    }

    res[lus] = '\0';
    return res;
}
char *litLigne(int descripteur){
    char * ligne=malloc(BUFFERLIGNE*sizeof(char));
    int nblu=0;
    char tmp;
    ssize_t lus;

    if (ligne == NULL) {
        return NULL;
    }

    do{
        lus = read(descripteur,&tmp,1);
        if (lus < 0) {
            free(ligne);
            return NULL;
        }
        if (lus == 0) {
            if (nblu == 0) {
                free(ligne);
                return NULL;
            }
            break;
        }
        if(nblu+1==BUFFERLIGNE-1 && tmp!='\n'){
            fprintf(stderr, "ligne trop longue\n");
            free(ligne);
            return NULL;
        }
        if(tmp=='\n'){
            ligne[nblu]=  '\0';
            return ligne;
        }
        ligne[nblu]= tmp;
        nblu++;

        
    }while(nblu<BUFFERLIGNE-1);
    ligne[nblu]=  '\0';

    return ligne;
}

int writeLigne(int descripteur,char* toWrite){
    int count=0;
    for(int i=0;toWrite[i]!='\0';i++){
    count ++;
    }
    if(write(descripteur,toWrite,count)==-1){
        fprintf(stderr, "err\n");
        return -1;
    };
    if(write(descripteur, "\n", 1) == -1) {
        fprintf(stderr, "Erreur d'écriture du saut de ligne\n");
        return -1;
    }
    return 0;
    
}
