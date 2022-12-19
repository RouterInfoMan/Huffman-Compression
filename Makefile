all: main.o huffman.o priority_queue.o parser.o binary_tree_huffman.o
	gcc -g -o compress main.o huffman.o priority_queue.o parser.o binary_tree_huffman.o

main.o: main.c
	gcc -c  main.c

huffman.o: huffman.c
	gcc -c  huffman.c

parser.o: parser.c
	gcc -c  parser.c

priority_queue.o: priority_queue.c
	gcc -c  priority_queue.c

binary_tree_huffman.o: binary_tree_huffman.c
	gcc -c  binary_tree_huffman.c

clean:
	rm *.o
