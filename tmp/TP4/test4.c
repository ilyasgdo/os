#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include<semaphore.h>

char buffer[99];
int res;

int fin = 0;
void *  lecteur( void * h ){
    sem_t * vide =sem_open("/mutvide", 0);
    sem_t * plein =sem_open("/mutplein",0);

    int src = open("test1.c",O_RDONLY);
    while(1){
        sem_wait(vide);

        res = read(src,buffer,sizeof(buffer));
       
        if(res == -1){
            perror("read src");
            exit(1);
        }
        if(res ==0){
                fin=1;

                    sem_post(plein);

            break;
        }
        sem_post(plein);

    }
    close(src);
    sem_close(plein);
    sem_close(vide);
    return NULL;
}
void *  ecrivain(void * h){
    sem_t * vide =sem_open("/mutvide", 0);
    sem_t * plein =sem_open("/mutplein",0);

    int des = open("des.txt",O_CREAT|O_RDWR,0644);
    //printf()
    do{
        sem_wait(plein);
        write(des,buffer,res);
        sem_post(vide);
        
    }while(fin == 0);
    
    sem_close(plein);
    sem_close(vide);
    return NULL;
}

int main(){
    pthread_t p1,p2;
      sem_open("/mutvide", O_CREAT,0644,1);
      sem_open("/mutplein", O_CREAT,0644,0);

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
     sem_unlink("/mutvide");
    sem_unlink("/mutplein");
    return 0;

}
