#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binary_tree_huffman.h"
#include "parser.h"
#include "huffman.h"


int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Wrong number of arguments: %d\n", argc);
        return -1;
    }
    if (strcmp(argv[1], "-d") == 0) {
        HuffmanDecode(argv[2], argv[3]);
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        HuffmanEncode(argv[2], argv[3]);
        return 0;
    }
    printf("Unknown argument: \"%s\"\n", argv[1]);
    return 0;

}