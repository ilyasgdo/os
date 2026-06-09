
all : producteur consomateur  clean

producteur : producteur.o test.o
	gcc -o producteur producteur.o test.o -lpthread
consomateur: consomateur.o test.o
	gcc -o consomateur consomateur.o test.o  -lpthread
producteur.o : producteur.c test.h
	gcc -o producteur.o -c producteur.c
consomateur.o : consomateur.c test.h
	gcc -o consomateur.o -c consomateur.c

test.o : test.c test.h
	gcc -o test.o -c test.c
clean: 
	rm -f *.o