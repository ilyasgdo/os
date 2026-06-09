#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include<semaphore.h>

char buffer[99];
int fin = 0;
sem_t mut;
int res;

void *  lecteur( void * h ){

    int src = open("test1.c",O_RDONLY);
    while(1){
        sem_wait(&mut);
         res = read(src,buffer,sizeof(buffer));
        sem_post(&mut);
        if(res == -1){
            perror("read src");
            exit(1);
        }
        if(res ==0){
            break;
        }

    }
    fin=1;
    close(src);

    return NULL;
}
void *  ecrivain(void * h){
    int des = open("des.txt",O_CREAT|O_RDWR,0644);
    //printf()
    do{
        sem_wait(&mut);
        write(des,buffer,res);
        sem_post(&mut);
        
    }while(fin == 0);
    return NULL;
}

int main(){
    pthread_t p1,p2;
    sem_init(&mut,0,1);
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
    sem_destroy(&mut);

    return 0;

}
