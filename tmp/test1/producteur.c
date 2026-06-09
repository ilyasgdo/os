
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>
char *  init_mem(){
    int des = shm_open("/compteur",O_CREAT|O_RDWR,0644);
    ftruncate(des,1*sizeof(char));
    char * res = mmap(NULL,1*sizeof(char),PROT_READ|PROT_WRITE,MAP_SHARED,des,0);
    return(res);
    
}

int init_sem(sem_t ** vide,sem_t ** plein){
    *vide=sem_open("/sem_vide",O_CREAT,0644,1);
    *plein=sem_open("/sem_plein",O_CREAT,0644,0);
    if(*plein==SEM_FAILED){
        perror("err open plein");
        exit(1);
    }
    if(*vide==SEM_FAILED){
        perror("err open vide");
        exit(1);
    }
    return 0;
    
}

int reset(){
    shm_unlink("/compteur");
    sem_unlink("/sem_plein");
    sem_unlink("/sem_vide");
    return 0;
}
int producteur(){
    char * compteur = init_mem();
    compteur[0]=(char)0;
    sem_t * vide;
    sem_t * plein;
    init_sem(&vide,&plein);
    int val;
    for(int i = 0;i<10;i++){
        sem_wait(vide);
        sleep(1);
         val = (int)compteur[0]+1;
        compteur[0]=(char)val;
        sem_post(plein);
    }
    sem_close(vide);
    sem_close(plein);
    munmap(compteur,1);
    return 0;
}
int consomateur(){
    char * compteur = init_mem();
    
    sem_t * vide;
    sem_t * plein;
    init_sem(&vide,&plein);
    for(int i = 0;i<10;i++){
        sem_wait(plein);
        printf("\n[Horloge] Temps écoulé : %d secondes ",(int)compteur[0]);
        sem_post(vide);
    }
    munmap(compteur,1);
    sem_close(vide);
    sem_close(plein);
    return 0;
}
int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        fprintf(stderr, "Erreur : Il manque un paramètre.\n");
        fprintf(stderr, "Usage : %s -p | -c | -r\n", argv[0]);
        exit(1);
    }

    
    if (strcmp(argv[1], "-p") == 0) {
        producteur();
    } 
    else if (strcmp(argv[1], "-c") == 0) {
        consomateur();
    } 
    else if (strcmp(argv[1], "-r") == 0) {
        reset();
    } 
    else {
        fprintf(stderr, "Erreur : L'option '%s' n'est pas valide.\n", argv[1]);
        fprintf(stderr, "Options autorisées : -p, -c, -r\n");
        exit(1);
    }

    return 0;
}