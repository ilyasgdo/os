all : testIB1  testIB2 testIB3 testIII1  testIII2
testIII2 : testIII2.o gestionFichier.o
	gcc -o testIII2 testIII2.o gestionFichier.o
testIII1 : testIII1.o gestionFichier.o
	gcc -o testIII1 testIII1.o gestionFichier.o
testIB3: testIB3.o gestionProcessus.o
	gcc -o testIB3 testIB3.o gestionProcessus.o
testIB2 : testIB2.o gestionProcessus.o
	gcc -o testIB2 testIB2.o gestionProcessus.o
testIB1 : testIB1.o gestionProcessus.o
	gcc -o testIB1 testIB1.o gestionProcessus.o

testIII2.o : testIII2.c gestionFichier.h
	gcc -o testIII2.o -c testIII2.c
testIII1.o : testIII1.c gestionFichier.h
	gcc -o testIII1.o -c testIII1.c
testIB3.o : testIB3.c gestionProcessus.c
	gcc -o testIB3.o -c testIB3.c
testIB2.o : testIB2.c gestionProcessus.h
	gcc -o testIB2.o -c testIB2.c
testIB1.o : testIB1.c gestionProcessus.h
	gcc -o testIB1.o -c testIB1.c


gestionFichier.o : gestionFichier.c gestionFichier.h
	gcc -o gestionFichier.o -c gestionFichier.c
gestionProcessus.o : gestionProcessus.c gestionProcessus.h
	gcc -o gestionProcessus.o -c gestionProcessus.c

clean :
	rm -f *.o 

.PHONY: all clean