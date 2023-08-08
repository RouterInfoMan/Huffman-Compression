#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binary_tree_huffman.h"
#include "parser.h"
#include "huffman.h"


int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Wrong number of arguments: %d\n", argc - 1);
        return -1;
    }
    if (strcmp(argv[1], "-d") == 0) {
        HuffmanDecode(argv[2], argv[3]); // Enter decode functions
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        HuffmanEncode(argv[2], argv[3]); // Enter encode function
        return 0;
    }
    printf("Unknown argument: \"%s\"\n", argv[1]);
    return 0;

}