#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

sem_t * mut ;
void * codeduthread(void * a){
    int j ;
    int i = (int)a;
    for(j = 0; j < 10; j++){
        sem_wait(mut);
        printf("Affichage %d du thread %d\n", j+1, i);
        sem_post(mut);
    }
    return NULL;
}
int main()  {
    
    mut = sem_open("/hellomut", O_CREAT, 0644, 1);
    if (mut == SEM_FAILED) {
        perror("err sem_open");
        exit(1);
    }
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;

    pthread_create(&t1,NULL,codeduthread,(void*)1);
    pthread_create(&t2,NULL,codeduthread,(void*)3);
    pthread_create(&t3,NULL,codeduthread,(void*)3);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    sem_unlink("/hellomut");
    sem_close(mut);
    return 0;


}
