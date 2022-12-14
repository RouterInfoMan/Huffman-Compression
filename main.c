#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "binary_tree_huffman.h"
#include "parser.h"


void HuffmanTree(char *fileName) {
    FILE *file = fopen(fileName, "r");
    input_parser *inp = (input_parser *) malloc(sizeof(input_parser));
    input_parser_init(inp, file);

    int freq[CHAR_CNT] = {0};
    char p = read_char(inp);
    while (p != EOF && p != '\0') {
        freq[(int)p]++;
        p = read_char(inp);
    }
    binary_tree_node *head = construct_tree(freq);
    printtree(head, "");
}

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Wrong number of arguments: %d\n", argc);
        
        return -1;
    }
    if (strcmp(argv[1], "-d") == 0) {
        return 0;
    }
    if (strcmp(argv[1], "-c") == 0) {
        HuffmanTree(argv[2]);
        return 0;
    }
    printf("Unknown argument: \"%s\"\n", argv[1]);
    return 0;

}