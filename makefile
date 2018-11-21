all: main.o helper_functions.o
	gcc main.o helper_functions.o
	
main.o: main.c helper_functions.h
	gcc -c main.c

helper_functions.o:
	gcc -c helper_functions.c
	
run:
	./a.out
