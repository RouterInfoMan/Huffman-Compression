#include "huffman.h"

void HuffmanEncode(char *in, char *out) {
    FILE *input = fopen(in, "r");
    if (!input) {
        printf("Invalid file!\n");
        return;
    }
    input_parser *inp = (input_parser *) malloc(sizeof(input_parser));
    input_parser_init(inp, input);

    int freq[CHAR_CNT] = {0};
    unsigned char p;
    int eof = read_uchar(inp, &p);
    int cnt = 0;
    while (!eof) {
        if(!freq[p]++){
            cnt++;
        }
        eof = read_uchar(inp, &p);
    }
    binary_tree_node *head = construct_tree(freq);
    
    char **codes = getcodes(head);

    input_parser_rewind(inp);
    
    FILE *output = fopen(out, "w");
    fprintf(output, "%d\n", cnt);
    printfreq(head, output);

    bit_parser *bp = (bit_parser *) malloc(sizeof(bit_parser));
    bit_parser_init(bp, input, output, inp);
    eof = read_uchar(inp, &p);
    while(!eof) {
        for (int i = 0; codes[p][i]; i++) {
            put_bit(bp, codes[p][i] - '0');
        }
        eof = read_uchar(inp, &p);
    }
    bit_flush(bp);
    int i;
    for (i = 0; i < CHAR_CNT; i++) {
        if(codes[i]) {
            free(codes[i]);
        }
    }
    free(codes);
}

void HuffmanDecode(char *in, char *out) {
    FILE *input = fopen(in, "r");
    FILE *output = fopen(out, "w");

    int freq[CHAR_CNT] = {0};
    int keys, fr, i, ccnt = 0, eof;
    unsigned char c;

    input_parser *par = (input_parser *) malloc(sizeof(input_parser));
    input_parser_init(par, input);

    read_uint(par, &keys);

    for (i = 0; i < keys; i++) {
        read_uchar(par, &c);
        read_uint(par, &fr);
        freq[c] = fr;
        ccnt += fr;
    }
    binary_tree_node *head = construct_tree(freq), *tmp;
    tmp = head;

    bit_parser *bp = (bit_parser *) malloc(sizeof(bit_parser));
    bit_parser_init(bp, input, output, par);
    for (i = 0; i < ccnt;) {
        int bit = get_bit(bp);
        if (bit == 0) {
            tmp = tmp->left;
        } else {
            tmp = tmp->right;
        }
        if(!tmp->left) {
            fprintf(output, "%c", tmp->data);
            tmp = head;
            i++;
        }
    }
}


