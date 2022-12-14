#include "priority_queue.h"

void pq_init(priority_queue *queue, int (*cmp)(const void *, const void*)) {
    queue->size = 0;
    queue->cmp = cmp;
}
void pq_heapify(priority_queue *queue, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest;
    void **heap = queue->heap;

    if (left <= queue->size && queue->cmp(heap[left], heap[index]) > 0) {
        largest = left;
    } else {
        largest = index;
    }
    if (right <= queue->size && queue->cmp(heap[right], heap[index]) > 0) {
        largest = right;
    }
    if (largest != index) {
        void *tmp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = tmp;

        pq_heapify(queue, largest);
    }
}
void *pq_top(priority_queue *queue) {
    return queue->heap[0];
}
void *pq_pop(priority_queue *queue) {
    if (queue->size == 0) {
        return NULL;
    }
    void *tmp = queue->heap[0];
    queue->heap[0] = queue->heap[queue->size - 1];
    queue->size--;

    //heapify
    int i;
    for (i = queue->size/2 - 1; i >= 0; i--) {
        pq_heapify(queue, i);
    }
    return tmp;
}
void pq_push(priority_queue *queue, void *val) {
    if (queue->size == 0) {
        queue->heap[0] = val;
        queue->size++;
    } else {
        queue->heap[queue->size] = val;
        queue->size++;
        //heapify
        int i;
        for (i = queue->size/2 - 1; i >= 0; i--) {
            pq_heapify(queue, i);
        }
    }
}