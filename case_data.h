#ifndef CASE_DATA_H
#define CASE_DATA_H
#include <iostream>
using namespace std;
#include "common.h"

const int NUM_ROOMS    = 6;
const int NUM_EDGES    = 6;
const int NUM_SUSPECTS = 5;
const int NUM_EVIDENCE = 8;
const int CRIME_ROOM   = 5;   // Study

const Room ROOMS[NUM_ROOMS] = {
    {0, "Entrance"},
    {1, "Hall"},
    {2, "Living Room"},
    {3, "Kitchen"},
    {4, "Bedroom"},
    {5, "Study"}
};

// Undirected edges between room ids
const int EDGES[NUM_EDGES][2] = {
    {0, 1}, {1, 2}, {1, 4}, {1, 5}, {2, 3}, {3, 0}
};

// Insert into the BST in this order: 50, 30, 70, 20, 60
const Suspect SUSPECTS[NUM_SUSPECTS] = {
    {50, "Hamza Qureshi",   "Nephew and heir",       0},
    {30, "Sana Malik",  "Business partner",      0},
    {70, "Waseem Akhtar",  "Driver",                0},
    {20, "Farah Naz",     "Neighbour",             0},
    {60, "Faisal Rana",   "Former employee",       0}
};

// Listed in collection order, deliberately NOT chronological
const Evidence EVIDENCE[NUM_EVIDENCE] = {
    {106, "Blood stain",        "Blood on study carpet, DNA profile matches Sana Malik", 5, 2046, 10, 30, false},
    {102, "CCTV frame",         "Figure in a dark jacket enters through the front door",   0, 2031,  9, 60, false},
    {108, "Threatening note",   "Torn note about the will, handwriting resembles Hamza Qureshi",   2, 1950,  6, 50, false},
    {104, "Phone call log",     "Victim's phone shows a two-minute call from Sana Malik",       5, 2037,  7, 30, false},
    {101, "Broken window latch","Kitchen window latch forced from outside",                3, 2028,  3, NO_SUSPECT, false},
    {105, "Fingerprint",        "Partial print on the desk drawer, matches Faisal Rana",   5, 2042,  8, 60, false},
    {107, "Car key fob",        "Driver’s spare key fob lying behind the sofa cushion",    2, 2015,  4, 70, false},
    {103, "Muddy boot print",   "Size 9 boot print leading from the hall toward the study",1, 2034,  5, 60, false}
};

#endif