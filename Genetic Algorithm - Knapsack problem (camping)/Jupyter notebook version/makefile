main: main.o genetic.o
	gcc -o main main.o genetic.o
main.o: main.c genetic.h
	gcc -c main.c
genetic.o: genetic.c genetic.h
	gcc -c genetic.c
