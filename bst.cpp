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

bool addScore(SuspectNode* root, int id, int points) {
    SuspectNode* node = searchSuspect(root, id);

    if(node == NULL)
        return false;

    node->data.score += points;
    return true;
}

void collectSuspects(SuspectNode* root, Suspect arr[], int &count) {
    if(root == NULL)
        return;

    collectSuspects(root->left, arr, count);
    arr[count++] = root->data;
    collectSuspects(root->right, arr, count);
}

void freeSuspects(SuspectNode* root) {
    if(root == NULL)
        return;

    freeSuspects(root->left);
    freeSuspects(root->right);
    delete root;
}
