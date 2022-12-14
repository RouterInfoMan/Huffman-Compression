#include "parser.h"

void init_parser(parser *par, FILE *file) {
    if (!file) {
        printf("Invalid file!\n");
    }
    par->file = file;
    par->p = BUF_SIZE - 1;
}

char read_char(parser *par) {
    par->p++;
    if (par->p == BUF_SIZE) {
        par->p = 0;
        fread(par->buf, 1, BUF_SIZE, par->file);
    }
    return par->buf[par->p];
}

