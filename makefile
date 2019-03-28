all : main
my_functions.o : my_functions.c my_functions.h
	gcc -c my_functions.c 
main.o : my_functions.h main.c
	gcc -c main.c
main : my_functions.o main.o
	gcc -o main main.o my_functions.o 
clean :
	rm -rf *.o main
