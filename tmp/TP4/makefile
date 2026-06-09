all :  test1 test2 test3 test4 test5 test6 clean
test4 : test4.o gestionFichier.o
	gcc -o test4 test4.o gestionFichier.o -lpthread
test4.o : test4.c gestionFichier.h
	gcc -o test4.o -c test4.c

test3 : test3.o gestionFichier.o
	gcc -o test3 test3.o gestionFichier.o -lpthread
test3.o : test3.c gestionFichier.h
	gcc -o test3.o -c test3.c
test2 : test2.o gestionFichier.o
	gcc -o test2 test2.o gestionFichier.o -lpthread
test2.o : test2.c gestionFichier.h
	gcc -o test2.o -c test2.c
test1 : test1.o gestionFichier.o
	gcc -o test1 test1.o gestionFichier.o -lpthread
test1.o : test1.c gestionFichier.h
	gcc -o test1.o -c test1.c

test5: test5.o gestionFichier.o
	gcc -o test5 test5.o gestionFichier.o -lpthread
test5.o : test5.c gestionFichier.h
	gcc -o test5.o -c test5.c
test6 : test6.o gestionFichier.o
	gcc -o test6 test6.o gestionFichier.o -lpthread
test6.o : test1.c gestionFichier.h
	gcc -o test6.o -c test6.c


gestionFichier.o : gestionFichier.c gestionFichier.h
	gcc -o gestionFichier.o -c gestionFichier.c
clean :
	 rm -f *.o