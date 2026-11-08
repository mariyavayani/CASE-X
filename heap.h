#ifndef HEAP_H
#define HEAP_H

#include "common.h"

// Max-heap of evidence, ordered by priority (highest on top)
class EvidenceHeap {
    static const int CAPACITY = 100;
    Evidence data[CAPACITY];
    int size;

    int parent(int i) const { return (i - 1) / 2; }
    int left(int i)   const { return 2 * i + 1; }
    int right(int i)  const { return 2 * i + 2; }

    void swapItems(int a, int b) {
        Evidence temp = data[a];
        data[a] = data[b];
        data[b] = temp;
    }

    // Move a new item up until its parent is at least as important
    void heapifyUp(int i) {
        while (i > 0 && data[parent(i)].priority < data[i].priority) {
            swapItems(i, parent(i));
            i = parent(i);
        }
    }

    // Push an item down until both children are less important
    void heapifyDown(int i) {
        while (true) {
            int largest = i;
            int l = left(i);
            int r = right(i);
            if (l < size && data[l].priority > data[largest].priority) largest = l;
            if (r < size && data[r].priority > data[largest].priority) largest = r;
            if (largest == i) break;
            swapItems(i, largest);
            i = largest;
        }
    }

public:
    EvidenceHeap() : size(0) {}

    bool isEmpty() const { return size == 0; }
    bool isFull()  const { return size == CAPACITY; }
    int  count()   const { return size; }

    // O(log n)
    bool insert(const Evidence& e) {
        if (isFull()) return false;
        data[size] = e;          // place at the end
        size++;
        heapifyUp(size - 1);     // restore heap order
        return true;
    }

    // O(1): look at the top without removing it
    bool peekMax(Evidence& out) const {
        if (isEmpty()) return false;
        out = data[0];
        return true;
    }

    // O(log n): remove and return the highest-priority evidence
    bool extractMax(Evidence& out) {
        if (isEmpty()) return false;
        out = data[0];
        data[0] = data[size - 1];   // move the last item to the top
        size--;
        if (size > 0) heapifyDown(0);
        return true;
    }
};

#endif