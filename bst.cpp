#include <iostream>
#include "bst.h"

using namespace std;

SuspectNode* insertSuspect(SuspectNode* root, Suspect s) {
    if(root == NULL)
        return new SuspectNode(s);

    if(s.id < root->data.id)
        root->left = insertSuspect(root->left, s);

    else if(s.id > root->data.id)
        root->right = insertSuspect(root->right, s);

    return root;
}

SuspectNode* buildSuspectBST() {
    SuspectNode* root = NULL;

    for(int i = 0; i < NUM_SUSPECTS; i++) {
        root = insertSuspect(root, SUSPECTS[i]);
    }

    return root;
}

SuspectNode* searchSuspect(SuspectNode* root, int id) {
    if(root == NULL || root->data.id == id)
        return root;

    if(id < root->data.id)
        return searchSuspect(root->left, id);

    return searchSuspect(root->right, id);
}

void displaySuspectsInorder(SuspectNode* root) {
    if(root == NULL)
        return;

    displaySuspectsInorder(root->left);

    cout << "ID: " << root->data.id
         << " | Name: " << root->data.name
         << " | Role: " << root->data.role
         << " | Score: " << root->data.score << endl;

    displaySuspectsInorder(root->right);
}
