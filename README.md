# CASE-X: Case File No. 001 — The Qureshi Residence Incident

**A crime scene investigation and evidence analysis simulator built with Data Structures and Algorithms in C++.**

CASE-X is a console-based simulation of a fictional crime. It does not store criminal records. Instead, every data structure and algorithm has one clear job in the investigation: finding evidence by ID, choosing what the lab examines first, undoing a mistaken step, looking up suspects, mapping routes through the house, rebuilding the timeline and ranking suspects.

> **Course:** Data Structure Algorithms and Applications (DSA)
> **Instructor:** Dr Muhammad Imran
> **University:** NED University of Engineering & Technology, Karachi
> **Language:** C++

---

## Table of Contents

- [The Case](#the-case)
- [Data Structures and Algorithms Used](#data-structures-and-algorithms-used)
- [How the Modules Connect](#how-the-modules-connect)
- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Sample Results](#sample-results)
- [Complexity Summary](#complexity-summary)
- [Limitations and Future Work](#limitations-and-future-work)
- [Ethics Note](#ethics-note)
- [Team](#team)

---

## The Case

The homeowner was found dead in the **Study** at **21:10**. The estimated time of the incident is **20:46**. Someone entered the house that evening, but the evidence points in more than one direction. The investigator must work out where the intruder could have walked, what happened and in what order, and whom the evidence points to most.

The case contains **6 rooms**, **5 suspects** and **8 pieces of evidence**.

### The House

| ID | Room |
|----|------|
| 0 | Entrance (front door) |
| 1 | Hall |
| 2 | Living Room |
| 3 | Kitchen (back door) |
| 4 | Bedroom |
| 5 | Study (crime scene) |

Doors: Entrance–Hall, Hall–Living Room, Hall–Bedroom, Hall–Study, Living Room–Kitchen, Kitchen–Entrance. The Entrance, Hall, Living Room and Kitchen form a loop on purpose, so different search methods give different routes.

### Suspects

| ID | Name | Role |
|----|------|------|
| 60 | Faisal Rana | Former employee |
| 30 | Sana Malik | Business partner |
| 50 | Hamza Qureshi | Nephew and heir |
| 70 | Waseem Akhtar | Driver |
| 20 | Farah Naz | Neighbour |

### Evidence

Listed in collection order, which is deliberately not chronological. Times are the *estimated event times*, not when the item was collected.

| ID | Item | Room | Time | Priority | Points to |
|----|------|------|------|----------|-----------|
| 106 | Blood stain, DNA profile | Study | 20:46 | 10 | Sana Malik |
| 102 | CCTV frame, figure in dark jacket | Entrance | 20:31 | 9 | Faisal Rana |
| 108 | Torn threatening note about the will | Living Room | 19:50 | 6 | Hamza Qureshi |
| 104 | Phone call log | Study | 20:37 | 7 | Sana Malik |
| 101 | Broken window latch | Kitchen | 20:28 | 3 | nobody |
| 105 | Partial fingerprint on desk drawer | Study | 20:42 | 8 | Faisal Rana |
| 107 | Spare car key fob behind sofa | Living Room | 20:15 | 4 | Waseem Akhtar |
| 103 | Muddy boot print | Hall | 20:34 | 5 | Faisal Rana |

The CCTV frame (E102) shows someone at the **front door**, while the broken latch (E101) points to the **Kitchen**, so the program examines both possible entry points.

---

## Data Structures and Algorithms Used

| Investigator's problem | Data structure / algorithm | Module |
|------------------------|---------------------------|--------|
| Pull up exhibit 106 right now | Hash table (separate chaining) | Evidence Locker |
| What should the lab examine first? | Max-heap (priority queue) | Lab Queue |
| We analyzed the wrong item, take it back | Stack | Investigator's Notebook |
| Who is suspect 60? | Binary search tree | Suspect Register |
| Where could the suspect have walked? | Graph, BFS and DFS | Scene Map |
| What happened, and in what order? | Merge sort | Timeline Board |
| Who does the evidence point to most? | Bubble sort | Suspect Ranking |

### Module Details

**Evidence Locker (Hash Table)** — 7 slots, slot = `id mod 7`, collisions handled by separate chaining. Each node stores only the evidence ID and its index in `workingEvidence`, so the analyzed flag is always read from the single real record.

**Lab Queue (Max-Heap)** — Array-based heap ordered by priority (1–10), capacity 100. Uses `heapifyUp` on insert and `heapifyDown` on extract. The lab always receives the most urgent exhibit first: `106, 102, 105, 104, 108, 103, 107, 101`.

**Investigator's Notebook (Stack)** — Built on a `vector`. Each action stores the evidence ID and the previous value of its analyzed flag. Undo pops the latest action, restores the flag and subtracts the same score from the suspect.

**Suspect Register (BST)** — Keyed by suspect ID, insertion order `50, 30, 70, 20, 60`. This is the single place where suspect scores are kept. Inorder traversal gives suspects in ID order.

```
        50
       /  \
     30    70
    /     /
  20    60
```

**Scene Map (Graph, BFS and DFS)** — Rooms are vertices, doors are edges, stored as an adjacency list. **BFS** finds the shortest route (fewest doors). **DFS with backtracking** lists every possible route without re-entering a room on the current route.

**Timeline Board (Merge Sort)** — Stable merge sort on a *copy* of the evidence array, ordered by timestamp, with the gap between events printed in minutes.

**Suspect Ranking (Bubble Sort)** — Suspects are collected from the BST by inorder traversal and ranked by score, highest first, with an early exit if a pass makes no swaps. Equal scores stay in ID order.

---

## How the Modules Connect

1. The **heap** decides which exhibit is analyzed next.
2. The **hash table** finds that exhibit's record.
3. The **stack** records the action so it can be undone.
4. The **BST** receives the exhibit's priority as points on the linked suspect.
5. Suspects are collected from the BST and ranked by **bubble sort**.
6. The **timeline** sorts a copy of the evidence by **merge sort**.
7. The **graph** answers the route questions.

> **Stale-index rule:** because the hash table stores array positions, `workingEvidence` must never be sorted in place. The timeline therefore always sorts a copy.

---

## Features

- Examine the crime scene: floor plan, fastest route (BFS) and every possible route (DFS) from either entry point
- Look up any exhibit instantly by ID
- Analyze evidence in priority order through the lab queue
- Undo the last analysis, with the suspect's score reversed correctly
- View a chronological timeline with analyzed/pending markers and time gaps
- Look up any suspect by ID
- View a ranked case board of evidence-association scores
- Input validation on every prompt (e.g. typing `1 2` prints "Please type a number." and asks again)

---

## Project Structure

```
CASE-X/
├── common.h        # Shared types and constants
├── case_data.h     # Built-in case data (rooms, suspects, evidence)
├── hash_table.h    # Evidence Locker (hash table with chaining)
├── heap.h          # Lab Queue (max-heap)
├── stack.h         # Investigator's Notebook (stack) - declarations
├── stack.cpp       # Investigator's Notebook - implementation
├── bst.h           # Suspect Register (BST) - declarations
├── bst.cpp         # Suspect Register - implementation
├── graph.h         # Scene Map (graph, BFS, DFS)
├── sorting.h       # Merge sort and bubble sort
├── ui.h            # Console user interface helpers
└── main.cpp        # Menu loop and module integration
```

---

## Getting Started

### Requirements

- A C++ compiler with C++11 support or later (e.g. `g++` from MinGW-w64 or GCC)

### Build

```bash
g++ main.cpp stack.cpp bst.cpp -o casex
```

### Run

**Windows (PowerShell):**

```powershell
.\casex
```

**Linux / macOS:**

```bash
./casex
```

---

## Usage

On start-up the program shows the case banner and the investigation menu:

```
INVESTIGATION MENU
  1. Examine the crime scene
  2. Evidence locker: look up an exhibit
  3. Lab queue: analyze next evidence
  4. Undo last analysis
  5. Timeline board
  6. Suspect register: look up a suspect
  7. Case board: suspect ranking
  0. Close the case
```

### Suggested walkthrough

1. **Option 1** — view the floor plan and routes from the front door and the back door.
2. **Option 2** — look up exhibit `106` (blood stain, status PENDING).
3. **Option 3** — run three times to analyze E106, E102, then E105.
4. **Option 4** — undo the last analysis (E105 goes back into the queue).
5. **Option 5** — view the timeline from 19:50 to the discovery of the body at 21:10.
6. **Option 6** — look up suspect `60` (Faisal Rana).
7. **Option 7** — view the ranked case board.

---

## Sample Results

**Routes from the Front Door (Entrance):**

```
Fastest: Entrance -> Hall -> Study
Route 1: Entrance -> Hall -> Study
Route 2: Entrance -> Kitchen -> Living Room -> Hall -> Study
```

**Routes from the Back Door (Kitchen):**

```
Fastest: Kitchen -> Living Room -> Hall -> Study
Route 1: Kitchen -> Living Room -> Hall -> Study
Route 2: Kitchen -> Entrance -> Hall -> Study
```

**Timeline order (all exhibits):** `108, 107, 101, 102, 103, 104, 105, 106`

**Final suspect scores (all 8 exhibits analyzed):**

| Rank | Suspect | Score | Evidence |
|------|---------|-------|----------|
| 1 | Faisal Rana | 22 | 9 + 5 + 8 |
| 2 | Sana Malik | 17 | 10 + 7 |
| 3 | Hamza Qureshi | 6 | 6 |
| 4 | Waseem Akhtar | 4 | 4 |
| 5 | Farah Naz | 0 | none |

Faisal Rana has the most evidence links, while Sana Malik is linked to the highest-priority item (the DNA match). This is why the score is a ranking of evidence links, **not** proof of guilt.

<!-- Optional: add screenshots, e.g.
![Start-up menu](docs/images/figure1_menu.png)
![Scene map](docs/images/figure5_scene_map.png)
![Timeline board](docs/images/figure7_timeline.png)
![Case board](docs/images/figure9_case_board.png)
-->

---

## Complexity Summary

| Module | Operation | Time | Extra space |
|--------|-----------|------|-------------|
| Hash table | insert / search | O(1) average, O(n) worst | O(n + 7) total |
| Max-heap | insert / extractMax | O(log n) | O(n) total |
| Max-heap | peekMax | O(1) | O(1) |
| Stack | push / pop / top | O(1) (push amortized) | O(n) total |
| BST | insert / search / addScore | O(log n) average, O(n) worst | O(h) recursion |
| Graph | build | O(V + E) | O(V + E) |
| Graph | BFS shortest route | O(V + E) | O(V) |
| Graph | DFS all routes | exponential in worst case (small here) | O(V) |
| Merge sort | best / average / worst | O(n log n) | O(n) |
| Bubble sort | worst / average | O(n²) | O(1) |
| Bubble sort | best (already sorted) | O(n) | O(1) |

---

## Limitations and Future Work

- The BST is not self-balancing; sorted input degrades it to O(n). An **AVL tree** would guarantee O(log n).
- The hash table has a fixed size of 7. A larger system would **resize and rehash** as the load grows.
- The case is built into `case_data.h`. Future work: **load cases from files**.
- DFS route counts can grow quickly in large buildings, so bigger maps would need limits or smarter search.
- The program is console-only. A **graphical interface** is future work.

---

## Ethics Note

The case, the people and the evidence are entirely **fictional**. The evidence-association score is a simple educational metric that ranks evidence links in this case. It does not claim to identify a real offender.

---

## Team

| Member | Roll number | Modules |
|--------|-------------|---------|
| Mariya Vayani | CT-25061 | Heap, Graph (BFS and DFS), Sorting (merge sort and bubble sort) |
| Ujala Usman | CT-25073 | Hash table, Stack, Binary search tree |
| Both members | — | Shared case data (`common.h`, `case_data.h`), integration and user interface (`main.cpp`, `ui.h`), testing and report |

---

*Submitted for Data Structure Algorithms and Applications (DSA), NED University of Engineering & Technology, Karachi — 18 November 2026.*
