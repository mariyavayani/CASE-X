
#ifndef STACK_H
#define STACK_H

#include <vector>
#include "case_data.h"
#include "bst.h" 
           
struct Action {
    int evidenceID;
    bool previousAnalyzed;
};

class Stack {
    std::vector<Action> v;

public:
    void push(Action a);
    void pop();
    Action top();
    bool isEmpty();
};

// Shared working copy of master evidence
extern Evidence workingEvidence[NUM_EVIDENCE];

// Investigation functions
void initializeEvidence();
int findEvidence(int id);
void analyzeEvidence(Stack &s, SuspectNode* root, int id);
void undo(Stack &s, SuspectNode* root);

#endif
