#include "parser.h"

void input_parser_init(input_parser *par, FILE *file) {
    if (!file) {
        printf("Invalid file!\n");
    }
    par->file = file;
    par->p = BUF_SIZE - 1;
}

char read_char(input_parser *par) {
    par->p++;
    if (par->p == BUF_SIZE) {
        par->p = 0;
        int c = fread(par->buf, 1, BUF_SIZE, par->file);
        if (c < BUF_SIZE) {
            par->buf[c + 1] = EOF;
        }
    }
    return par->buf[par->p];
}
void input_parser_delete(input_parser *par) {
    fclose(par->file);
    free(par);
    par = NULL;
}

void output_parser_init(output_parser *par, FILE *file) {
    if (!file) {
        printf("Invalid file!\n");
    }
    par->buf = 0;
    par->mp = 7;
}
void output_parser_delete(output_parser *par) {
    fclose(par->file);
    free(par);
    par = NULL;
}
void put_bit(output_parser *par, int bit) {
    par->mp++;
    if (par->mp == 8) {
        par->mp = 0;
        fputc(par->buf, par->file);
        par->buf = 0;
    }
    if (bit) {
        par->buf |= 1 << par->mp;
    } else {
        par->buf &= ~(1 << par->mp);
    }
}
void flush(output_parser *par) {
    if(par->mp) {
        fputc(par->buf, par->file);
        par->mp = 0;
        par->buf = 0;
    }
}