#pragma once
#include "priority_queue.h"
#include <stdlib.h>
#include <string.h>
#define CHAR_CNT 256


// -1 for internal node
struct binary_tree_node{
    unsigned char data;
    int freq;
    struct binary_tree_node *left, *right;
};

typedef struct binary_tree_node binary_tree_node;

binary_tree_node* construct_tree(int freq[CHAR_CNT]);
void printcodes(binary_tree_node *head, char *p, FILE *file);
void printfreq(binary_tree_node *head, FILE *file);
char **getcodes(binary_tree_node *head);
