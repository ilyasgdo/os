all: test1 test2 clean 

test2 : test2.o gestionFichier.o
	gcc -o test2 test2.o gestionFichier.o
test2.o: test2.c gestionFichier.h
	gcc -o test2.o -c test2.c
test1 : test1.o gestionFichier.o
	gcc -o test1 test1.o gestionFichier.o
test1.o: test1.c gestionFichier.h
	gcc -o test1.o -c test1.c
gestionFichier.o: gestionFichier.c gestionFichier.h
	gcc -o gestionFichier.o -c gestionFichier.c 
clean : 
	rm -f *.o