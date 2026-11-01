#include <iostream>
#include "common.h"
#include "case_data.h"
#include "sorting.h"
using namespace std;

int passed = 0, total = 0;

void check(bool condition, const string& label) {
    total++;
    if (condition) { passed++; cout << "  PASS: " << label << "\n"; }
    else           {           cout << "  FAIL: " << label << "\n"; }
}

void printTime(int t) {
    int h = t / 100, m = t % 100;
    cout << (h < 10 ? "0" : "") << h << ":" << (m < 10 ? "0" : "") << m;
}

int main() {
    // ---------- Test 1: merge sort on evidence (timeline) ----------
    cout << "TEST 1: Merge sort, evidence timeline\n";

    Evidence ev[NUM_EVIDENCE];
    for (int i = 0; i < NUM_EVIDENCE; i++) ev[i] = EVIDENCE[i];   // copy, EVIDENCE is const

    
    mergeSort(ev, 0, NUM_EVIDENCE - 1);

    for (int i = 0; i < NUM_EVIDENCE; i++) {
        cout << "  ";
        printTime(ev[i].timestamp);
        cout << "  E" << ev[i].id << "  " << ev[i].name << "\n";
    }

    int expectedEv[NUM_EVIDENCE] = {108, 107, 101, 102, 103, 104, 105, 106};
    bool evOk = true;
    for (int i = 0; i < NUM_EVIDENCE; i++)
        if (ev[i].id != expectedEv[i]) evOk = false;
    check(evOk, "evidence is in chronological order (108 ... 106)");

    // Sorting an already sorted array must not change it
    mergeSort(ev, 0, NUM_EVIDENCE - 1);
    bool stillOk = true;
    for (int i = 0; i < NUM_EVIDENCE; i++)
        if (ev[i].id != expectedEv[i]) stillOk = false;
    check(stillOk, "sorting an already sorted list changes nothing");

    // ---------- Test 2: bubble sort on suspects (ranking) ----------
    cout << "\nTEST 2: Bubble sort, suspect ranking\n";

    Suspect sus[NUM_SUSPECTS];
    for (int i = 0; i < NUM_SUSPECTS; i++) sus[i] = SUSPECTS[i];  // copy

    // Score = sum of priorities of the evidence pointing to each suspect
    for (int e = 0; e < NUM_EVIDENCE; e++) {
        if (EVIDENCE[e].suspectId == NO_SUSPECT) continue;
        for (int s = 0; s < NUM_SUSPECTS; s++)
            if (sus[s].id == EVIDENCE[e].suspectId)
                sus[s].score += EVIDENCE[e].priority;
    }

    cout << "  Before ranking:\n";
    for (int i = 0; i < NUM_SUSPECTS; i++)
        cout << "    " << sus[i].id << "  " << sus[i].name << "  score " << sus[i].score << "\n";

    rankSuspects(sus, NUM_SUSPECTS);

    cout << "  After ranking:\n";
    for (int i = 0; i < NUM_SUSPECTS; i++)
        cout << "    " << sus[i].id << "  " << sus[i].name << "  score " << sus[i].score << "\n";

    int expectedId[NUM_SUSPECTS]    = {60, 30, 50, 70, 20};
    int expectedScore[NUM_SUSPECTS] = {22, 17,  6,  4,  0};
    bool idOk = true, scoreOk = true;
    for (int i = 0; i < NUM_SUSPECTS; i++) {
        if (sus[i].id    != expectedId[i])    idOk = false;
        if (sus[i].score != expectedScore[i]) scoreOk = false;
    }
    check(scoreOk, "scores are 22, 17, 6, 4, 0");
    check(idOk,    "ranking order is suspects 60, 30, 50, 70, 20");

    // ---------- Summary ----------
    cout << "\nResult: " << passed << " of " << total << " checks passed\n";
    return (passed == total) ? 0 : 1;
}