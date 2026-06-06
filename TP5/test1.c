#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include <getopt.h> // REQUIS pour getopt_long et struct option

#define MAX_FILE 20
#define MAX_RAND 20

// Petite fonction d'aide requise par ton main
void usage() {
    fprintf(stderr, "Usage: ./programme [--producer | --consumer | --reset]\n");
    exit(1);
}

int * init_sem_mem(sem_t ** vide, sem_t ** plein){
    int des = shm_open("/memoire", O_CREAT | O_RDWR, 0644);
    if(des == -1){
        perror("err shm open ");
        exit(1);
    }
    if(ftruncate(des, MAX_FILE * sizeof(int)) != 0){
        perror("err truncate");
       
    }

    int * tab = mmap(NULL, MAX_FILE * sizeof(int), PROT_WRITE | PROT_READ , MAP_SHARED, des ,0);
    if(tab == MAP_FAILED){
        perror("err mmap");
        exit(1);
    }
    close(des); // On ferme le descripteur devenu inutile

    *vide = sem_open("/sem_vide", O_CREAT , 0644, MAX_FILE);
    if(*vide == SEM_FAILED){
        perror("err sem open vide");
        exit(1);
    }
    
    *plein = sem_open("/sem_plein", O_CREAT, 0644, 0);
    if(*plein == SEM_FAILED){
        perror("err sem open plein");
        exit(1);
    }
    return tab;
}

int reset(){
    shm_unlink("/memoire");
    sem_unlink("/sem_vide");
    sem_unlink("/sem_plein");
    printf("Ressources système réinitialisées.\n");
    return 0;
}

int producteur(){
    int i;
    sem_t * vide;
    sem_t * plein;
    int * tab = init_sem_mem(&vide, &plein);
    if(tab == NULL){
        perror("tab prod NULL");
        exit(1);
    }
    srandom(time(NULL));
    for(i = 0; i < MAX_FILE; i++){
        sem_wait(vide);
        tab[i] = (int)((random() / (double) RAND_MAX) * MAX_RAND) + 1;
        printf("Producteur : %d\n", tab[i]);
        sem_post(plein);
    }
    sem_close(vide);
    sem_close(plein);
    munmap(tab, MAX_FILE * sizeof(int));  
    return 0;
}

int consomateur(){
    int i;
    sem_t * vide;
    sem_t * plein;
    int * tab = init_sem_mem(&vide, &plein);

    if(tab == NULL){
        perror("tab conso NULL");
        exit(1);
    }
    for(i = 0; i < MAX_FILE; i++){
        sem_wait(plein);
        printf("Consomateur: %d\n", tab[i]);
        sem_post(vide);
    }
    sem_close(vide);
    sem_close(plein);
    munmap(tab, MAX_FILE * sizeof(int));  
    return 0;
}

int main(int argc , char * argv[]){
    static struct option long_options[] = {
        {"reset",     no_argument, 0, 'r'},
        {"producer",  no_argument, 0, 'p'},
        {"consumer",  no_argument, 0, 'c'},
        {0, 0, 0, 0}
    };
    int option_index = 0;
    int c = getopt_long (argc, argv, "rpc", long_options, &option_index);

    if (c == -1) {
        usage();
    } else {
        switch (c) {
            case 'r':
                reset();
                break;
            case 'p':
                producteur();
                break;
            case 'c':
                consomateur(); // Correction orthographe (appel avec un seul 'm')
                break;
            default: 
                usage();
                break;
        }
    }
    return 0;
}