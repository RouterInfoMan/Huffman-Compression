#pragma once
#include "priority_queue.h"
#include <stdlib.h>
#include <string.h>
#define CHAR_CNT 127


// -1 for internal node
struct binary_tree_node{
    char data;
    int freq;
    struct binary_tree_node *left, *right;
};

typedef struct binary_tree_node binary_tree_node;

binary_tree_node* construct_tree(int freq[CHAR_CNT]);
void printtree(binary_tree_node *head, char *p);

