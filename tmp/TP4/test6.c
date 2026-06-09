#include <stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mut;
void * boucle(void * a){
    int i=(int)a;
    sem_wait(&mut);
    int j;
    for(j = 0; j < 10; j++)
        printf("Affichage %d du thread %d\n", j+1, i); // Thread Pi avec i = 1, 2, 3
    sem_post(&mut);
    return NULL;


}


int main(){
    sem_init(&mut,0,1);
    pthread_t p1,p2,p3;
    if(pthread_create(&p1,NULL,&boucle,(void * )1)!=0){
        perror("err crate thread");
        exit(1);
        
    }
    if(pthread_create(&p2,NULL,&boucle,(void * )2)!=0){
        perror("err crate thread");
        exit(1);
    }
    if(pthread_create(&p3,NULL,&boucle,(void * )3)!=0){
        perror("err crate thread");
        exit(1);
    }
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    return 0;
}