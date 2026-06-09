#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
     #include <fcntl.h>
char buffer[99];
int fin = 0;
void *  lecteur( void * h ){
    int src = open("test1.c",O_RDONLY);
    int res;
    while(1){
        int res = read(src,buffer,sizeof(buffer));
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
        write(des,buffer,strlen(buffer));
        
    }while(fin == 0);
    return NULL;
}

int main(){
    pthread_t p1,p2;

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
    return 0;

}
