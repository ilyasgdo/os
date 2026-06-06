#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include "gestionFichier.h"


char buffer[9999];
int fini = 0; // Initialisé à 0 : le lecteur n'a pas fini
sem_t mut;

void * lecteur(){
    int des = open("src.txt", O_RDONLY);
    if(des == -1){
        perror("err open lecteur");
        exit(1);
    }
    char * tmp;
    int i;
    sem_wait(&mut);

    while(1){
        tmp = litLigne(des);
        
        if(tmp == NULL){
            break;
        }
        for (i = 0; tmp[i] != '\0'; i++){
            buffer[i] = tmp[i];
        }
        buffer[i] = '\0';
        free(tmp);
        
        // Note: Idéalement il faudrait un free(tmp) ici pour éviter la fuite,
        // mais on garde ta structure brute pour voir le comportement des threads.
    }
    sem_post(&mut);
    fini = 1; // Le lecteur a terminé tout le fichier
    return NULL;
}

void * ecrivain(){
    int des = open("dest.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int res;
    if(des == -1){
        perror("err open ecrivain");
        exit(1);
    }
    sem_wait(&mut);
    do {
        // L'écrivain écrit en boucle ce qu'il trouve dans le buffer
        res = write(des, buffer, strlen(buffer));
        if(res == -1){
            perror("err write ecrivain");
            exit(1);
        }
    } while(fini == 0); // Continue tant que le lecteur n'a pas mis fini à 1
    sem_post(&mut);
    
    return NULL;
}

int main(){
    pthread_t p1;
    pthread_t p2;
    if(sem_init(&mut,0,1)==-1){
        perror("err sem init");
        exit(1);
    }

    // Suppression du sleep(2) -> Les deux threads sont lancés en même temps
    if(pthread_create(&p1, NULL, lecteur, NULL) != 0){
        perror("err create p1");
        exit(1);
    }
    if(pthread_create(&p2, NULL, ecrivain, NULL) != 0){
        perror("err create p2");
        exit(1);
    }

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    return 0;
}