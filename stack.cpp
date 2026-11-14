#include <iostream>
#include "stack.h"
#include "hash_table.h"

using namespace std;

Evidence workingEvidence[NUM_EVIDENCE];
HashTable evidenceTable;

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

void buildEvidenceTable() {
    evidenceTable.clear();
    for(int i = 0; i < NUM_EVIDENCE; i++) {
        evidenceTable.insert(workingEvidence[i].id, i);
    }
}

void initializeEvidence() {
    for(int i = 0; i < NUM_EVIDENCE; i++) {
        workingEvidence[i] = EVIDENCE[i];
    }
    buildEvidenceTable();
}

int findEvidence(int id) {
    return evidenceTable.search(id);
}

void analyzeEvidence(Stack &s, SuspectNode* root, int id) {   
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

    addScore(root, workingEvidence[index].suspectId,        
             workingEvidence[index].priority);

    cout << "Evidence analyzed!\n";
}

void undo(Stack &s, SuspectNode* root) {              
    if(s.isEmpty()) {
        cout << "Nothing to undo!\n";
        return;
    }

    Action a = s.top();
    s.pop();

    int index = findEvidence(a.evidenceID);

    if(index != -1) {
        workingEvidence[index].analyzed = a.previousAnalyzed;

        addScore(root, workingEvidence[index].suspectId,      
                 -workingEvidence[index].priority);

        cout << "Action undone!\n";
    }
}
