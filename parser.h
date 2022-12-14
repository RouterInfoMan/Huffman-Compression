#pragma once
#include <stdio.h>

#define BUF_SIZE 4096

typedef struct {
    FILE *file;
    char buf[4096];
    unsigned int p; 
}parser;

void init_parser(parser *par, FILE *file);
char read_char(parser *par);