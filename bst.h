#ifndef BST_H
#define BST_H

#include "case_data.h"

struct SuspectNode {
    Suspect data;
    SuspectNode* left;
    SuspectNode* right;

    SuspectNode(Suspect s) {
        data = s;
        left = right = NULL;
    }
};

SuspectNode* insertSuspect(SuspectNode* root, Suspect s);
SuspectNode* buildSuspectBST();
SuspectNode* searchSuspect(SuspectNode* root, int id);
void displaySuspectsInorder(SuspectNode* root);

#endif
