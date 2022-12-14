#pragma once
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 4096

typedef struct {
    FILE *file;
    char buf[4096];
    unsigned int p; 
}input_parser;

void input_parser_init(input_parser *par, FILE *file);
char read_char(input_parser *par);
void input_parser_delete(input_parser *par);

typedef struct {
    FILE *file;
    char buf;
    unsigned int mp;
}output_parser;

void output_parser_init(output_parser *par, FILE *file);
void output_parser_delete(output_parser *par);
void put_bit(output_parser *par, int bit);
void flush(output_parser *par);