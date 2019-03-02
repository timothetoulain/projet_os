all : main
#all : test
#test :  my_functions.o test.o
#	gcc -o test test.o my_functions.o 
my_functions.o : my_functions.c my_functions.h
	gcc -c my_functions.c 
#test.o : test.c my_functions.h
#	gcc -c test.c 
main.o : my_functions.h main.c
	gcc -c main.c
main : my_functions.o main.o
	gcc -o main main.o my_functions.o 
clean :
	rm -rf *.o main
