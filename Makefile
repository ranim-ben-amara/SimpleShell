all: main.o parse.o
	gcc -o shell main.o parse.o

main.o: main.c
	gcc -o main.o -c main.c

parse.o: parse.c
	gcc -o parse.o -c parse.c

clean:
	rm -f *.o prog

