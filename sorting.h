#ifndef SORTING_H
#define SORTING_H

#include "common.h"

// Counts steps so the two algorithms can be compared
struct SortStats {
    long comparisons;
    long swaps;
    SortStats() : comparisons(0), swaps(0) {}
};

// Bubble sort by timestamp, O(n^2)
inline void bubbleSort(Evidence arr[], int n, SortStats& s) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            s.comparisons++;
            if (arr[j].timestamp > arr[j + 1].timestamp) {
                Evidence temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                s.swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;   // already sorted
    }
}

// Rank suspects by association score, highest first (bubble sort)
inline void rankSuspects(Suspect arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].score < arr[j + 1].score) {   // lower score moves down
                Suspect temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Merge two sorted halves: arr[left..mid] and arr[mid+1..right]
inline void mergeHalves(Evidence arr[], int left, int mid, int right, SortStats& s) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    Evidence* L = new Evidence[n1];
    Evidence* R = new Evidence[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        s.comparisons++;
        if (L[i].timestamp <= R[j].timestamp) arr[k++] = L[i++];
        else                                  arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

// Merge sort by timestamp, O(n log n)
inline void mergeSort(Evidence arr[], int left, int right, SortStats& s) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, s);
    mergeSort(arr, mid + 1, right, s);
    mergeHalves(arr, left, mid, right, s);
}

#endif