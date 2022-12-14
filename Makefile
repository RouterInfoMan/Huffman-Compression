all: main.o huffmann.o priority_queue.o parser.o
	gcc -g -o main main.o huffmann.o priority_queue.o parser.o

main.o: main.c
	gcc -c main.c

huffmann.o: huffmann.c
	gcc -c huffmann.c

parser.o: parser.c
	gcc -c parser.c

priority_queue.o: priority_queue.c
	gcc -c priority_queue.c


clean:
	rm *.o
