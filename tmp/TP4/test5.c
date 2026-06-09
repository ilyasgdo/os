#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include<semaphore.h>

char buffer[99];
int fin = 0;
sem_t vide;
sem_t plein;
int res;

void * lecteur( void * h ){
    int src = open("test1.c", O_RDONLY);
    while(1){
        sem_wait(&vide);
        res = read(src, buffer, sizeof(buffer));
        
        if(res == -1){
            perror("read src");
            exit(1);
        }
        if(res == 0){
            sem_post(&plein); // On réveille l'écrivain pour lui dire que res == 0
            break;
        }
        sem_post(&plein);
    }
    close(src);
    return NULL;
}
void * ecrivain(void * h){
    int des = open("des.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    while(1){
        sem_wait(&plein);
        
        if(res == 0){
            sem_post(&vide); // Optionnel, par politesse pour libérer au cas où
            break; // On sort proprement de la boucle, le fichier est fini !
        }
        
        write(des, buffer, res);
        sem_post(&vide);
    }
    close(des);
    return NULL;
}

int main(){
    pthread_t p1,p2;
    sem_init(&plein,0,0);
    sem_init(&vide,0,1);
    if(pthread_create(&p1,NULL,&lecteur,NULL) !=0){
        perror("err create p1"),
        exit(1);
    }
    if(pthread_create(&p2,NULL,&ecrivain,NULL) !=0){
        perror("err create p2"),
        exit(1);
    }
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    sem_destroy(&plein);
    sem_destroy(&vide);
    return 0;

}
