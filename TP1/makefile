all: test1c test2b1 test2b2 test2b3 test3b1

test1c : test1c.o gestionFichier.o
	gcc -o test1c test1c.o gestionFichier.o 

test2b1 : test2b1.o gestionFichier.o
	gcc -o test2b1 test2b1.o gestionFichier.o

test2b2 : test2b2.o gestionFichier.o
	gcc -o test2b2 test2b2.o gestionFichier.o

test2b3 : test2b3.o gestionFichier.o
	gcc -o test2b3 test2b3.o gestionFichier.o

# Correction ici : dépend de test3b1.o
test3b1 : test3b1.o gestionFichier.o
	gcc -o test3b1 test3b1.o gestionFichier.o

test2b1.o : test2b1.c gestionFichier.h
	gcc -c test2b1.c -o test2b1.o

test2b2.o : test2b2.c gestionFichier.h
	gcc -c test2b2.c -o test2b2.o

# Remis dans le bon ordre (-c puis -o)
test2b3.o : test2b3.c gestionFichier.h
	gcc -c test2b3.c -o test2b3.o

test1c.o : test1c.c gestionFichier.h
	gcc -c test1c.c -o test1c.o

# Correction ici : compilation de test3b1.c en test3b1.o
test3b1.o : test3b1.c gestionFichier.h
	gcc -c test3b1.c -o test3b1.o

gestionFichier.o : gestionFichier.c gestionFichier.h
	gcc -c gestionFichier.c -o gestionFichier.o

# Correction ici : tous les exécutables sont maintenant nettoyés
clean :
	rm -f *.o test1c test2b1 test2b2 test2b3 test3b1

.PHONY: all clean