#include "parser.h"

void input_parser_init(input_parser *par, FILE *file) {
    if (!file) {
        printf("Invalid file!\n");
    }
    par->file = file;
    par->p = BUF_SIZE - 1;
    par->eof = 0;
    par->pos = BUF_SIZE + 1;
}

int read_uchar(input_parser *par, unsigned char *c) {
    par->p++;
    if (par->p == BUF_SIZE) {
        par->p = 0;
        int c = fread(par->buf, 1, BUF_SIZE, par->file);
        if (c < BUF_SIZE) {
            par->eof = 1;
            par->pos = c;
        }
    }
    *c = par->buf[par->p];
}
unsigned int read_uint(input_parser *par, unsigned int *res) {
    *res = 0;
    char p;
    int eof;
    eof = read_uchar(par, &p);
    if (eof)
        return eof;
    while (!('0' <= p && p <= '9')) {
        eof = read_uchar(par, &p);
        if (eof)
            return eof;
    }
    while ('0' <= p && p <= '9') {
        *res = *res * 10 + p - '0';
        eof = read_uchar(par, &p);
        if (eof)
            return eof;
    }
    return 0;
}
int input_parser_rewind(input_parser *par) {
    input_parser_init(par, par->file);
    return fseek(par->file, 0, SEEK_SET);
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