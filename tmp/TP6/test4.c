//Ecrivez une troisième fonction de copieur utilisant mmap.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
     #include <string.h>
int fileLen(char * filePath){
    int des = open(filePath,O_RDWR);
    int len = lseek(des, 0, SEEK_END);
    lseek(des, 0, SEEK_SET); // On remet le curseur au début pour la lecture future
    return len;
}
int copieFichier(char * filePath){
    int len =fileLen(filePath);

    int src = open(filePath,O_RDWR);
    char * tabS =mmap(NULL,len,PROT_READ, MAP_SHARED ,src,0);

    if(tabS==NULL){
        perror("err mmap 1");
        exit(1);
    }

    int des = open("des.txt",O_CREAT|O_RDWR,0644);
    ftruncate(des,len*sizeof(char));
    char * tabD =mmap(NULL,len,PROT_WRITE, MAP_SHARED ,des,0);

    if(tabD==NULL){
        perror("err mmap 2");
        exit(1);
    }
    memcpy(tabD,tabS,len);
    munmap(tabD,len);
    munmap(tabS,len);
    close(src);
    close(des);
    
    return 0;
}

int main(){
    copieFichier("test3.c");
    return 0;
}