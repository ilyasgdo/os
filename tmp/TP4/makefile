all :  testIB1 testIB2 testIB3 testIB4 clean
testIB4 : testIB4.o gestionFichier.o
	gcc -o testIB4 testIB4.o gestionFichier.o -lpthread
testIB4.o : testIB4.c gestionFichier.h
	gcc -o testIB4.o -c testIB4.c

testIB3 : testIB3.o gestionFichier.o
	gcc -o testIB3 testIB3.o gestionFichier.o -lpthread
testIB3.o : testIB3.c gestionFichier.h
	gcc -o testIB3.o -c testIB3.c
testIB2 : testIB2.o gestionFichier.o
	gcc -o testIB2 testIB2.o gestionFichier.o -lpthread
testIB2.o : testIB2.c gestionFichier.h
	gcc -o testIB2.o -c testIB2.c
testIB1 : testIB1.o gestionFichier.o
	gcc -o testIB1 testIB1.o gestionFichier.o -lpthread
testIB1.o : testIB1.c gestionFichier.h
	gcc -o testIB1.o -c testIB1.c




gestionFichier.o : gestionFichier.c gestionFichier.h
	gcc -o gestionFichier.o -c gestionFichier.c
clean :
	 rm -f *.o