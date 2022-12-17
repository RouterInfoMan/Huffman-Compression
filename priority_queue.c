#include "priority_queue.h"

void pq_init(priority_queue *q, int (*cmp)(const void *, const void*)) {
    memset(q->heap, 0, sizeof(void *));
    q->size = 0;
    q->cmp = cmp;
}
void pq_heapify(priority_queue *q, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    void **heap = q->heap;

    if (heap[left]) {
        if (left < q->size && q->cmp(heap[left], heap[index]) > 0) {
            largest = left;
        }
    }
    if (heap[right]) {
        if (right < q->size && q->cmp(heap[right], heap[index]) > 0) {
            largest = right;
        }
    }
    if (largest != index) {
        void *tmp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = tmp;

        pq_heapify(q, largest);
    }
}
void *pq_top(priority_queue *q) {
    return q->heap[0];
}
void *pq_pop(priority_queue *q) {
    if (q->size == 0) {
        return NULL;
    }
    void *tmp = q->heap[0];
    q->heap[0] = q->heap[q->size - 1];
    q->heap[q->size - 1] = NULL;
    q->size--;

    //heapify
    int i;
    for (i = q->size/2 - 1; i >= 0; i--) {
        pq_heapify(q, i);
    }
    return tmp;
}
void pq_push(priority_queue *q, void *val) {
    if (q->size == 0) {
        q->heap[0] = val;
        q->size++;
    } else {
        q->heap[q->size] = val;
        q->size++;
        //heapify
        int i;
        for (i = q->size/2 - 1; i >= 0; i--) {
            pq_heapify(q, i);
        }
    }
}
void pq_delete(priority_queue *q) {
    void *p;
    while (p = pq_pop(q)) {
        free(p);
    }
    free(q);
    q = NULL;
}