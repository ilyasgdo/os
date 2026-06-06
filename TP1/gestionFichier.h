#ifndef GESTION_FICHIER_H
#define GESTION_FICHIER_H
int getDescripteur(char * path);
char * litDixCaracteres(int des );
char * litLigne(int des);
int ecritLigne(int des  , char * tab);
#endif