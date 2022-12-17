#include "parser.h"

void input_parser_init(input_parser *par, FILE *file) {
    if (!file) {
        printf("Invalid file!\n");
    }
    par->file = file;
    par->p = BUF_SIZE - 1;
    par->eofp = BUF_SIZE + 1;
}
int read_uchar(input_parser *par, unsigned char *c) {
    par->p++;
    if (par->p == BUF_SIZE) {
        par->p = 0;
        int c = fread(par->buf, 1, BUF_SIZE, par->file);
        if (c < BUF_SIZE) {
            par->eofp = c;
        }
    }
    if (par->eofp == par->p) {
        *c = 0;
        return 1;
    }
    *c = par->buf[par->p];
    return 0;
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

void bit_parser_init(bit_parser *par, FILE *in, FILE *out, input_parser *par2) {
    par->ipos = 7;
    par->opos = 0;
    par->par = par2;
    
    par->in = in;
    par->out = out;
}
int get_bit(bit_parser *par) {
    par->ipos++;
    if (par->ipos == 8) {
        par->ipos = 0;
        read_uchar(par->par, &par->ibyte);
    }
    return (par->ibyte & (1 << par->ipos)) >> par->ipos;
}
void put_bit(bit_parser *par, int bit) {
    if (par->opos == 8) {
        par->opos = 0;
        fprintf(par->out, "%c", par->obyte);
    }
    if (bit) {
        par->obyte |= (1 << par->opos);
    } else {
        par->obyte &= ~(1 << par->opos);
    }
    par->opos++;
}
void bit_flush(bit_parser *par) {
    fprintf(par->out, "%c", par->obyte);
    par->opos = 0;
}