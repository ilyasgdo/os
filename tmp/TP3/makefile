
all : testIB1 testIB2 clean


testIB2: testIB2.o
	gcc -o testIB2 testIB2.o

testIB1 : testIB1.o gestionFichier.o
	gcc -o testIB1 testIB1.o gestionFichier.o


testIB2.o : testIB2.c 
	gcc -o testIB2.o -c testIB2.c
testIB1.o : testIB1.c gestionFichier.h
	gcc -o testIB1.o -c testIB1.c

gestionFichier.o : gestionFichier.c gestionFichier.o
	gcc -o gestionFichier.o -c gestionFichier.c

clean :
	rm -f *.o 