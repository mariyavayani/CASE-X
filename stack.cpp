#include <iostream>
#include "stack.h"

using namespace std;

Evidence workingEvidence[NUM_EVIDENCE];

void Stack::push(Action a) {
    v.push_back(a);
}

void Stack::pop() {
    v.pop_back();
}

Action Stack::top() {
    return v.back();
}

bool Stack::isEmpty() {
    return v.empty();
}

void initializeEvidence() {
    for(int i = 0; i < NUM_EVIDENCE; i++) {
        workingEvidence[i] = EVIDENCE[i];
    }
}

int findEvidence(int id) {
    for(int i = 0; i < NUM_EVIDENCE; i++) {
        if(workingEvidence[i].id == id) {
            return i;
        }
    }
    return -1;
}

void analyzeEvidence(Stack &s, int id) {
    int index = findEvidence(id);

    if(index == -1) {
        cout << "Evidence not found!\n";
        return;
    }

    if(workingEvidence[index].analyzed) {
        cout << "Evidence already analyzed!\n";
        return;
    }

    Action a;
    a.evidenceID = id;
    a.previousAnalyzed = workingEvidence[index].analyzed;

    s.push(a);
    workingEvidence[index].analyzed = true;

    cout << "Evidence analyzed!\n";
}

void undo(Stack &s) {
    if(s.isEmpty()) {
        cout << "Nothing to undo!\n";
        return;
    }

    Action a = s.top();
    s.pop();

    int index = findEvidence(a.evidenceID);

    if(index != -1) {
        workingEvidence[index].analyzed = a.previousAnalyzed;
        cout << "Action undone!\n";
    }
}
