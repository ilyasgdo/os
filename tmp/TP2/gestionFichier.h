
#ifndef GESTION_FICHIER_H
#define GESTION_FICHIER_H

int getDescripteur(const char *path);
char *litDixCaracteres(int descripteur);
char *litLigne(int descripteur);
int writeLigne(int descripteur,char* toWrite);

#define BUFFERDIX 1133
#define BUFFERLIGNE 1000033

#endif
