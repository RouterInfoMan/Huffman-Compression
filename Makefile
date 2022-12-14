all: main.o huffmann.o
	gcc -o main main.o huffmann.o 

main.o: main.c
	gcc -c main.c

huffmann.o: huffmann.c
	gcc -c huffmann.c

clean:
	rm *.o