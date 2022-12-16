#pragma once
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 4096

typedef struct {
    FILE *file;
    unsigned char buf[4096], byte;
    unsigned int p, bpos;
    int eofp;
}input_parser;

void input_parser_init(input_parser *par, FILE *file);
int read_uchar(input_parser *par, unsigned char *c);
unsigned int read_uint(input_parser *par, unsigned int *res);
void input_parser_delete(input_parser *par);
int input_parser_rewind(input_parser *par);

typedef struct {
    FILE *in, *out;
    input_parser *par;
    unsigned char ibyte, obyte;
    int ipos, opos;
}bit_parser;

int get_bit(bit_parser *par);
void put_bit(bit_parser *par, int bit);
void bit_flush(bit_parser *par);
