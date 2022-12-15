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
    char p = read_char(inp);
    int cnt = 0;
    while (p != EOF && p != '\0') {
        if(!freq[p]++) cnt++;
        p = read_char(inp);
    }
    binary_tree_node *head = construct_tree(freq);
    
    char **codes = getcodes(head);

    input_parser_rewind(inp);
    
    FILE *output = fopen(out, "w");
    fprintf(output, "%d\n", cnt);
    printfreq(head, output);

    p = read_char(inp);
    while(p != '\0' && p != EOF) {
        fprintf(output, "%s", codes[p]);
        p = read_char(inp);
    }
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
    int keys, fr, i, ccnt = 0;
    char c;
    fscanf(input, "%d", &keys);
    fgetc(input);
    char *str = (char *) malloc(sizeof(char) * CHAR_CNT);
    for (i = 0; i < keys; i++) {
        fgets(str, CHAR_CNT, input);
        sscanf(str+1, "%d", &fr);
        freq[str[0]] = fr;
        ccnt += fr;
    }
    binary_tree_node *head = construct_tree(freq), *tmp;
    tmp = head;


    for (i = 0; i < ccnt;) {
        c = fgetc(input);
        if (c == '0') {
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


