all: main

main: main.o hello.o libpgcd.a
	gcc main.o hello.o libpgcd.a -o main -Wall

main.o: main.c hello.h pgcd/pgcd.h
	gcc -c main.c -o main.o -Wall

hello.o: hello.c hello.h
	gcc -c hello.c  -o hello.o -Wall

pgcd.o: pgcd/pgcd.c pgcd/pgcd.h
	gcc -c  pgcd/pgcd.c -o pgcd.o  -Wall

libpgcd.a: pgcd.o
	ar -crs libpgcd.a pgcd.o 

clean:
	rm -f main *.o *.a 
