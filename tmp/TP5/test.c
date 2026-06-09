#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include "test.h"
#define MAX_FILE 99
#define MAX_RAND 20

int  semInit(sem_t ** vide,sem_t ** plein){
    *vide = sem_open("/vide",O_CREAT,0644,MAX_FILE);
    *plein = sem_open("/plein",O_CREAT,0644,0);
    return 0;
}
int * openFile(){
    int des = shm_open("/tab",O_CREAT|O_RDWR,0644);
    if(des==-1){
        perror("err open");
    }
    ftruncate(des,MAX_FILE*sizeof(int));
    int * tab = mmap(NULL,MAX_FILE*sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED,des,0);
    close(des);
    return tab;
}
void reset(){
    shm_unlink("/tab");
    sem_unlink("/vide");
    sem_unlink("/plein");
}
int producteur(int * tab){
    tab=openFile();
    sem_t  * vide;
    sem_t * plein;
    semInit(&vide,&plein);
    srandom(time(NULL));
    for(int i = 0;i<MAX_FILE;i++){
        sem_wait(vide);
        tab[i]=(int)((random()/(double) RAND_MAX)*MAX_RAND)+1;
        printf("\nProducteur : %d",tab[i]);
        fflush(stdout);
        sem_post(plein);
    }
    sem_close(vide);
    sem_close(plein);
    munmap(tab, MAX_FILE * sizeof(int)); // CORRECTION : munmap au lieu de free
    return 0;

}
int consomateur(int * tab){
    tab=openFile();
    sem_t  * vide;
    sem_t * plein;
    semInit(&vide,&plein);
    for(int i = 0;i<MAX_FILE;i++){
        sem_wait(plein);
        printf("\nConsomateur : %d",tab[i]);
        fflush(stdout);
        sem_post(vide);
    }
    sem_close(vide);
    sem_close(plein);
    munmap(tab, MAX_FILE * sizeof(int)); // CORRECTION : munmap au lieu de free
    return 0;

}