#pragma once
#include <stdio.h>
//priority queue with heap
#define PQ_SIZE 256


typedef struct {
    void *heap[PQ_SIZE];
    unsigned int size;
    int (*cmp)(const void *, const void *);
}priority_queue;

void pq_init(priority_queue *queue, int (*cmp)(const void *, const void*));
void *pq_top(priority_queue *queue);
void *pq_pop(priority_queue *queue);
void pq_push(priority_queue *queue, void *val);