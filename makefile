all : test
test :  my_functions.o test.o
	gcc -o test test.o my_functions.o 
my_functions.o : my_functions.c my_functions.h
	gcc -c my_functions.c 
test.o : test.c my_functions.h
	gcc -c test.c 
clean :
	rm -rf *.o test
