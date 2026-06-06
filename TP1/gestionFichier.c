#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h> 
#include "gestionFichier.h"
int BUFFERDIX = 11;
int BUFFERLIGNE =99999;
int getDescripteur(char * path){
 return open(path,O_RDWR );
}
char * litDixCaracteres(int des ){
    char * res = (char*) malloc(BUFFERDIX*sizeof(char));
    int tmp = read(des,res,BUFFERDIX-1);
    if(res<=0){
        perror("nothing in there");
    }
    res[tmp+1]='\0';
    
    return res;
}
char * litLigne(int des){
    char * buffer  =(char*) malloc(BUFFERLIGNE*sizeof(char));
    if(buffer==NULL){
        perror("err malloc");
    }
    int count= 0;
    char c;
    int res;
    while(count<BUFFERLIGNE-1){
        res = read(des,&c,1);
        if(res==0){
            return NULL; 
            free(buffer);           
        }
        if(res<0){
            free(buffer);
            perror("err read");
        }
        if(c=='\n'){
            buffer[count]='\0';
            break;
        }
        buffer[count] = c;
        count ++;

    }
    char * resu = (char *) malloc(count+1*sizeof(char));
    int i;
    for( i = 0;i<count;i++ ){
        resu[i]=buffer[i];
        
    }
        resu[i]='\0';

    free(buffer);
    
    return resu;
    // return buffer;
}
int ecritLigne(int des  , char * tab){
    int count=0;
    for(int i = 0; tab[i]!='\0';i++ ){
        count++;
    }
   
    if( write(des,tab,count)==-1){
        perror("err ecriture");
    }
    return 0;
}

