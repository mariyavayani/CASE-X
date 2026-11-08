#include <iostream>
#include "common.h"
#include "case_data.h"
#include "heap.h"
using namespace std;

int passed = 0, total = 0;

void check(bool condition, const string& label) {
    total++;
    if (condition) { passed++; cout << "  PASS: " << label << "\n"; }
    else           {           cout << "  FAIL: " << label << "\n"; }
}

int main() {
    EvidenceHeap heap;

    cout << "TEST 1: insert and extract in priority order\n";
    for (int i = 0; i < NUM_EVIDENCE; i++) heap.insert(EVIDENCE[i]);
    check(heap.count() == NUM_EVIDENCE, "8 items inserted");

    Evidence top;
    heap.peekMax(top);
    check(top.id == 106, "peek shows E106 (priority 10) on top");

    int expected[NUM_EVIDENCE] = {106, 102, 105, 104, 108, 103, 107, 101};
    bool orderOk = true;
    for (int i = 0; i < NUM_EVIDENCE; i++) {
        Evidence e;
        heap.extractMax(e);
        cout << "  E" << e.id << "  " << e.name << "  priority " << e.priority << "\n";
        if (e.id != expected[i]) orderOk = false;
    }
    check(orderOk, "extraction order is 106, 102, 105, 104, 108, 103, 107, 101");
    check(heap.isEmpty(), "heap is empty afterwards");

    cout << "\nTEST 2: edge cases\n";
    Evidence dummy;
    check(!heap.extractMax(dummy), "extract from empty heap returns false");
    check(!heap.peekMax(dummy),    "peek on empty heap returns false");

    heap.insert(EVIDENCE[0]);   // E106
    heap.insert(EVIDENCE[4]);   // E101
    Evidence e1;
    heap.extractMax(e1);
    heap.insert(EVIDENCE[1]);   // E102
    Evidence e2;
    heap.extractMax(e2);
    check(e1.id == 106 && e2.id == 102, "insert after extract still keeps order");

    cout << "\nResult: " << passed << " of " << total << " checks passed\n";
    return (passed == total) ? 0 : 1;
}