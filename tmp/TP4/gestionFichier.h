
#ifndef GESTION_FICHIER_H
#define GESTION_FICHIER_H

int getDescripteur(const char *path);
char *litDixCaracteres(int descripteur);
char *litLigne(int descripteur);
int litfichier(int un , int deux);
int writeLigne(int descripteur,char* toWrite);

#define BUFFERDIX 11
#define BUFFERLIGNE 100033

#endif
