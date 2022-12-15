#include "binary_tree_huffman.h"

int cmp_node(const void *a, const void *b) {
    binary_tree_node *na = (binary_tree_node *) a;
    binary_tree_node *nb = (binary_tree_node *) b;

    return nb->freq - na->freq;
}

void binary_tree_init(binary_tree_node *node, char data, int freq) {
    node->data = data;
    node->freq = freq;

    node->left = NULL;
    node->right = NULL;
}

binary_tree_node* construct_tree(int freq[CHAR_CNT]) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    pq_init(q, cmp_node);
    
    int i;
    for (i = 0; i < CHAR_CNT; i++) {
        if (freq[i] <= 0) {
            continue;
        }
        binary_tree_node *a = (binary_tree_node *)malloc(sizeof(binary_tree_node));
        binary_tree_init(a, (char)i, freq[i]);
        pq_push(q, a);
    }
    while(q->size > 1) {
        binary_tree_node *a, *b;
        a = pq_pop(q);
        b = pq_pop(q);
        binary_tree_node *internal = (binary_tree_node *)malloc(sizeof(binary_tree_node));
        binary_tree_init(internal, -1, a->freq + b->freq);
        internal->left = a;
        internal->right = b;
        pq_push(q, internal);
    }
    binary_tree_node *head = pq_pop(q);
    pq_delete(q);
    return head;
}

char get_tree_char(binary_tree_node *head, char *str) {
    binary_tree_node *tmp = head;
    while(tmp->left != NULL) {
        if (*str == '1') {
            tmp = head->right;
        } else if (*str == '0') {
            tmp = head->left;
        } else {
            printf("?????\n");
        }
    }
    return tmp->data;
}
void printcodes(binary_tree_node *head, char *p, FILE *file) {
    char *t = (char *) malloc(strlen(p) + 1);
    if (!head->left && !head->right) {
        fprintf(file, "%c %d %s\n", head->data, head->freq, p);
    }
    if (head->left) {
        strcpy(t, p);
        strcat(t, "0");
        printcodes(head->left, t, file);
    }
    if (head->right) {
        strcpy(t, p);
        strcat(t, "1");
        printcodes(head->right, t, file);
    }
    free(t);
}
void _getcodes(binary_tree_node *head, char *array[CHAR_CNT], char *p, int len) { 
    if (!head->left && !head->right) {
        array[head->data] = (char *) calloc(len + 1, sizeof(char));
        strncpy(array[head->data], p, len);
        array[head->data][len+1] = 0;
    }
    if (head->left) {
        p[len] = '0';
        _getcodes(head->left, array, p, len + 1);
    }
    if (head->right) {
        p[len] = '1';
        _getcodes(head->right, array, p, len + 1);
    }
}
char **getcodes(binary_tree_node *head) {
    char **array = (char **) malloc(sizeof(char *) * CHAR_CNT);
    int i;
    for (i = 0; i < CHAR_CNT; i++) {
        array[i] = NULL;
    }
    char *p = (char *) calloc(CHAR_CNT, sizeof(char));
    _getcodes(head, array, p, 0);
    free(p);
    return array;
}
void printfreq(binary_tree_node *head, FILE *file) {
    if (!head->left && !head->right) {
        fprintf(file, "%c %d\n", head->data, head->freq);
    }
    if (head->left) {
        printfreq(head->left, file);
    }
    if (head->right) {
        printfreq(head->right, file);
    }
}