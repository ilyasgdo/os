all : test1 test2 test3 test4 clean



test4 : test4.o calcule.o 
	gcc -o test4 test4.o calcule.o 


test3 : test3.o calcule.o 
	gcc -o test3 test3.o calcule.o 

test1 : test1.o calcule.o 
	gcc -o test1 test1.o calcule.o 
test2 : test2.o calcule.o 
	gcc -o test2 test2.o calcule.o 


test1.o :  test1.c calcule.h
	gcc -o test1.o -c test1.c
test2.o :  test2.c calcule.h
	gcc -o test2.o -c test2.c

test3.o :  test3.c calcule.h
	gcc -o test3.o -c test3.c
test4.o :  test4.c calcule.h
	gcc -o test4.o -c test4.c

calcule.o: calcule.c calcule.o 
	gcc -o calcule.o -c calcule.c 

clean : 
	rm -f *.o

