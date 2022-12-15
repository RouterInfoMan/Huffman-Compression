#pragma once
#include <stdio.h>
#include "parser.h"
#include "priority_queue.h"
#include "binary_tree_huffman.h"

void HuffmanEncode(char *in, char *out);
void HuffmanDecode(char *in, char *out);