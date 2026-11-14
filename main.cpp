#include <iostream>
#include <iomanip>
#include <string>
#include "common.h"
#include "case_data.h"
#include "stack.h"
#include "bst.h"
#include "heap.h"
#include "graph.h"
#include "sorting.h"
#include "ui.h"
using namespace std;

const int INCIDENT_TIME  = 2046;   // estimated time of the incident
const int DISCOVERY_TIME = 2110;   // when the body was found

void printTime(int t) {
    int h = t / 100, m = t % 100;
    cout << (h < 10 ? "0" : "") << h << ":" << (m < 10 ? "0" : "") << m;
}

int toMinutes(int t) { return (t / 100) * 60 + (t % 100); }

// 1. Crime scene (graph)
void examineScene(const Graph& g) {
    printHeader("CRIME SCENE: FLOOR PLAN AND ROUTES");
    showFloorPlan();

    cout << "\n  Where did the suspect get in?\n";
    cout << "    1. Front door (Entrance)\n";
    cout << "    2. Back door  (Kitchen)\n";
    int c = readInt("  Your pick > ");

    int start;
    if (c == 1)      start = 0;
    else if (c == 2) start = 3;
    else { cout << "  Not a valid entry point.\n"; return; }

    cout << "\n  Fastest way to the " << ROOMS[CRIME_ROOM].name << ":\n    ";
    shortestRoute(g, start, CRIME_ROOM, ROOMS);

    cout << "\n  Every possible route:\n";
    allRoutes(g, start, CRIME_ROOM, ROOMS);
}

// 2. Evidence locker (hash table, through findEvidence)
void lookupEvidence() {
    printHeader("EVIDENCE LOCKER");
    int id = readInt("  Exhibit number (e.g. 106) > ");

    int index = findEvidence(id);
    if (index == -1) {
        cout << "  No exhibit with that number.\n";
        return;
    }

    const Evidence& e = workingEvidence[index];
    cout << "\n  .----------------------------------------\n";
    cout << "  | EXHIBIT E" << e.id << ": " << e.name << "\n";
    cout << "  |   " << e.description << "\n";
    cout << "  |   Found in : " << ROOMS[e.roomId].name << " at ";
    printTime(e.timestamp);
    cout << "\n  |   Priority : " << e.priority << " / 10\n";
    cout << "  |   Status   : " << (e.analyzed ? "ANALYZED" : "PENDING") << "\n";
    cout << "  '----------------------------------------\n";
}

// 3. Lab queue (heap, then stack)
void analyzeNext(EvidenceHeap& heap, Stack& trail, SuspectNode* suspects) {
    printHeader("LAB QUEUE");
    Evidence next;
    if (!heap.extractMax(next)) {
        cout << "  Everything has been analyzed.\n";
        return;
    }
    cout << "  Most urgent exhibit: E" << next.id << " - " << next.name
         << " (priority " << next.priority << ")\n";
    cout << "  Sending to the lab...\n  ";
    analyzeEvidence(trail, suspects, next.id);
}

// 4. Undo (stack), and put the evidence back in the heap
void undoLast(EvidenceHeap& heap, Stack& trail, SuspectNode* suspects) {
    printHeader("INVESTIGATOR'S NOTEBOOK");
    if (trail.isEmpty()) {
        cout << "  Nothing to undo.\n";
        return;
    }
    int id = trail.top().evidenceID;     // remember which one before it is removed
    cout << "  Taking back the analysis of E" << id << "...\n  ";
    undo(trail, suspects);

    int index = findEvidence(id);
    if (index != -1) heap.insert(workingEvidence[index]);   // pending again
}

// 5. Timeline board (merge sort on a copy, so workingEvidence is never reordered)
void showTimelineBoard() {
    printHeader("TIMELINE BOARD");

    Evidence list[NUM_EVIDENCE];
    for (int i = 0; i < NUM_EVIDENCE; i++) list[i] = workingEvidence[i];
    mergeSort(list, 0, NUM_EVIDENCE - 1);

    cout << "  (*) analyzed    ( ) pending    <<< incident\n\n";

    for (int i = 0; i < NUM_EVIDENCE; i++) {
        if (i > 0) {
            int gap = toMinutes(list[i].timestamp) - toMinutes(list[i - 1].timestamp);
            cout << "          |\n";
            cout << "          |   " << gap << " min later\n";
            cout << "          |\n";
        }

        const Evidence& e = list[i];
        cout << "  ";
        printTime(e.timestamp);
        cout << "  " << (e.analyzed ? "(*)" : "( )")
             << "--- " << ROOMS[e.roomId].name << "\n";

        cout << "          |     " << e.name << " (E" << e.id << ")";
        if (e.timestamp == INCIDENT_TIME)
            cout << "   <<< ESTIMATED TIME OF INCIDENT";
        cout << "\n";
    }

    int gap = toMinutes(DISCOVERY_TIME) - toMinutes(list[NUM_EVIDENCE - 1].timestamp);
    cout << "          |\n";
    cout << "          |   " << gap << " min later\n";
    cout << "          |\n";
    cout << "  ";
    printTime(DISCOVERY_TIME);
    cout << "  [!]--- Victim found in the " << ROOMS[CRIME_ROOM].name << "\n";
}

// 6. Suspect register (BST)
void lookupSuspect(SuspectNode* suspects) {
    printHeader("SUSPECT REGISTER");
    int id = readInt("  Suspect ID > ");

    SuspectNode* node = searchSuspect(suspects, id);
    if (node == NULL) {
        cout << "  No suspect with that ID.\n";
        return;
    }
    cout << "\n  .----------------------------------------\n";
    cout << "  | SUSPECT FILE #" << node->data.id << "\n";
    cout << "  |   Name  : " << node->data.name << "\n";
    cout << "  |   Role  : " << node->data.role << "\n";
    cout << "  |   Evidence-association score: " << node->data.score << "\n";
    cout << "  '----------------------------------------\n";
}

// 7. Case board (scores from the BST, ranked by bubble sort)
void showSummary(SuspectNode* suspects) {
    printHeader("CASE BOARD: SUSPECT RANKING");

    Suspect ranked[NUM_SUSPECTS];
    int count = 0;
    collectSuspects(suspects, ranked, count);
    rankSuspects(ranked, count);

    for (int i = 0; i < count; i++) {
        int s = ranked[i].score;
        cout << "  " << (i + 1) << ". " << left << setw(16) << ranked[i].name
             << string(s > 0 ? s : 0, '#') << " " << s << "\n";
    }

    cout << "\n";
    if (count == 0 || ranked[0].score == 0)
        cout << "  No evidence analyzed yet. Use option 3 first.\n";
    else
        cout << "  Strongest evidence link so far: " << ranked[0].name << "\n";

    cout << "  Scores show how strongly the analyzed evidence is linked to\n"
         << "  each suspect. They are not a verdict.\n";
}

int main() {
    // ----- Setup -----
    initializeEvidence();             // working copy + hash table

    Graph g;
    buildGraph(g, NUM_ROOMS, EDGES, NUM_EDGES);

    SuspectNode* suspects = buildSuspectBST();   // built once, shared everywhere

    EvidenceHeap heap;
    for (int i = 0; i < NUM_EVIDENCE; i++) heap.insert(workingEvidence[i]);

    Stack trail;

    // ----- Menu -----
    showBanner();

    int choice = -1;
    while (choice != 0) {
        showMenu();
        choice = readInt("  Your move, detective > ");

        switch (choice) {
            case 1: examineScene(g);                      break;
            case 2: lookupEvidence();                     break;
            case 3: analyzeNext(heap, trail, suspects);   break;
            case 4: undoLast(heap, trail, suspects);      break;
            case 5: showTimelineBoard();                  break;
            case 6: lookupSuspect(suspects);              break;
            case 7: showSummary(suspects);                break;
            case 0: cout << "\n  Case closed. Good work, detective.\n\n"; break;
            default: cout << "  That is not on the menu.\n";
        }

        if (choice != 0) waitForEnter();
    }

    freeSuspects(suspects);
    return 0;
}