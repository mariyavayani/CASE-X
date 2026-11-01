#ifndef COMMON_H
#define COMMON_H
#include <iostream>
using namespace std;

#include <string>

const int NO_SUSPECT = -1;   // evidence not linked to anyone

struct Room {
    int id;
    string name;
};

struct Suspect {
    int id;                  // BST key
    string name;
    string role;
    int score;               // evidence-association score, starts at 0
};

struct Evidence {
    int id;                  // hash table key, e.g. 101
    string name;
    string description;
    int roomId;              // room where it was found
    int timestamp;           // HHMM, e.g. 2031 means 20:31
    int priority;            // 1 (low) to 10 (high), heap key
    int suspectId;           // suspect it points to, or NO_SUSPECT
    bool analyzed;           // false until processed
};

#endif