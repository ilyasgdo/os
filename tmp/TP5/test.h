#ifndef TEST_H
#define TEST_H
#include <semaphore.h>
int  semInit(sem_t ** vide,sem_t ** plein);
int * openFile();
void reset();
int producteur(int * tab);
int consomateur(int * tab);
#endif