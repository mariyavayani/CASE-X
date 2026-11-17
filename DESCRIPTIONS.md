**SORTING:**

Sorting (timeline reconstruction). Evidence is collected in random order, so this module sorts it by timestamp to rebuild the sequence of events. Bubble sort (O(n²)) and merge sort (O(n log n)) are both implemented, and their comparison counts are compared. It can also rank suspects by association score.

BUBBLE SORT FOR SUSPECTS. MERGE SORT FOR EVIDENCES IN ORDER OF TIME STAMPS

Evidence timeline, merge sort: an evidence log can grow as a case develops, and merge sort stays fast at O(n log n). It’s also stable, so two items with the same timestamp keep their collection order, which matters for a timeline.

Suspect ranking, bubble sort: a case has only a handful of suspects, so a simple O(n²) sort is plenty. The cost is irrelevant at that size, and a short, readable sort is easier to explain.

How the two fit the story: the timeline option calls mergeSort on the evidence, and the final investigation summary calls rankSuspects after the scores are computed. Expected ranking with case data: Karan 22, Meera 17, Rohan 6, Dev 4, Anita 0. That gives you an easy test.



**HEAP:**


Heap (evidence priority). A max-heap ordered by evidence priority, stored in an array. The most important piece of evidence (the DNA sample, priority 10) is always at the top, so the investigator can analyze the most critical evidence first without searching the whole list. New evidence is added at the bottom and moves up to its correct position (heapifyUp), and the top item is removed by replacing it with the last item and sinking that down (heapifyDown). Insert and extract-max both run in O(log n), and viewing the top item is O(1).

Why a heap? Evidence arrives continuously in a real case, and the next item to process should always be the most important one. A sorted array would need up to O(n) shifting to insert each new item, while a heap handles both inserting and removing in O(log n).

Role in the simulator: it decides the order of the analysis queue. When the investigator chooses “Analyze next evidence,” the heap returns the highest-priority item, which is then marked as analyzed through the stack so the step can be undone.

Test result (case data): evidence is processed in the order E106, E102, E105, E104, E108, E103, E107, E101.


**GRAPH:**

Graph (crime scene map). The building is modelled as a graph. Each room is a vertex, and each door or passage between rooms is an edge. The graph is stored as an adjacency list: every room keeps a vector listing the rooms it connects to, and each door is added to both rooms’ lists, since a door works in both directions. Two traversals answer two investigation questions:

BFS (shortest route): uses a queue to explore the map in rings, first every room one door away, then two doors away, and so on. It records the room each one was reached from, so the first time it reaches the destination is by the fewest rooms, and the route is rebuilt by following those records backwards. Complexity is O(V + E).
DFS with backtracking (all possible routes): walks through one door after another as deep as it can, never entering a room already on the current route. When it reaches the destination it records the route, then steps back and tries the next door. It lists every route a suspect could have taken. This is fast on a small building, though the number of routes can grow quickly in very large maps.

Why a graph? Rooms and doors form a network. A list or table can’t express which rooms connect to which, or find routes between them, but a graph does both naturally.

Why an adjacency list? It stores only the doors that exist, so BFS visits each room and door once, which is more efficient than checking every pair of rooms as an adjacency matrix would.

Role in the simulator: the CCTV frame (E102) shows someone at the front door, and the broken window latch (E101) points to the Kitchen. The investigator picks an entry point, and the program shows the quickest way to the Study (Entrance, Hall, Study) and every other possible route (Entrance, Kitchen, Living Room, Hall, Study). The evidence then tells them which route fits.

Test result (case data): 18 of 18 checks passed. There are 2 possible routes from Entrance to Study, the Bedroom is a dead end with exactly 1 route, and unreachable rooms return no route.


**HASH TABLE:**

Hash table (evidence lookup). Evidence records are stored in an array, and the hash table maps each evidence ID to that record's position in the array. It has 7 slots, and the slot for an ID is id mod 7. When two IDs land in the same slot (a collision), they are linked together in a chain, so nothing is overwritten. The table stores only the ID and the array position, not a copy of the evidence, so the "analyzed" flag is always read from the one real record. Insert and search both run in O(1) on average. The worst case is O(n), if every ID lands in one chain. Space is O(n + table size).

Why a hash table? Evidence arrives continuously in a real case, and every module that receives an evidence ID needs the record quickly. A loop over the array is O(n) and gets slower as the log grows. A sorted array with binary search is O(log n), but every insert needs O(n) shifting. A BST is O(log n) on average and O(n) if unbalanced, and evidence IDs have no ordering need. A hash table gives O(1) average for both, and this module only ever asks "fetch this ID".

Why chaining? The table never fills up, and a collision just adds a node to the chain.

Role in the simulator: it is the single ID-to-evidence path for the program. When the investigator analyzes or undoes evidence, findEvidence() asks the hash table for the position of that ID and works on that record.

Test result (case data): evidence 101 and 108 both land in slot 3 and form a chain of two, search(101) returns 4, search(108) returns 2, and search(999) returns -1 (not found).


**STACK:**

Stack (investigation trail). A stack stores the investigator's actions in the order they happened, so the most recent action is always on top (last in, first out). Each action records which evidence was analyzed and what its "analyzed" flag was beforehand. Analyzing evidence pushes an action. Undo pops the most recent one, restores the flag and subtracts the score that was added. Push, pop, top and isEmpty all run in O(1) (push is amortized O(1) because the underlying vector may occasionally resize). Space is O(n).

Why a stack? Undo must always reverse the latest action first, which is exactly last in, first out. A queue would undo the oldest action first, which is wrong. A list would also work, but it would allow access to any position, and the trail should only ever be changed at one end.

Role in the simulator: when the investigator chooses "Analyze next evidence," the evidence is marked as analyzed and the action is pushed on the stack. Choosing undo reverses the last step, so a wrong step can be taken back without restarting the case.

Test result (case data): analyzing 106 then 102 gives Sana 10 and Faisal 9. One undo removes 102 (Faisal back to 0, 102 unanalyzed), a second undo removes 106, and a third undo prints "Nothing to undo!".


**BINARY SEARCH TREE:**

Binary search tree (suspect lookup). Suspects are stored in a binary search tree keyed by suspect ID. Every node's left subtree holds smaller IDs and its right subtree holds larger ones, so each comparison discards half of the remaining tree. Insert and search run in O(log n) on average and O(n) in the worst case, when keys arrive in sorted order and the tree becomes a chain. Inorder traversal visits every suspect in ID order in O(n). Space is O(n).

Why a BST? A suspect is looked up by ID, and the tree keeps the suspects ordered without ever sorting them. An unsorted array needs an O(n) scan for every search, and a sorted array needs O(n) shifting to insert. A hash table gives fast lookup but no ordered traversal. A plain BST keeps the code simple, so a self-balancing AVL tree is listed as future scope.

Role in the simulator: when evidence is analyzed, the program searches the tree for the suspect it points to and adds the evidence priority to that suspect's score. The final summary collects the suspects from the tree and passes them to rankSuspects.

Test result (case data): inserting 50, 30, 70, 20, 60 gives root 50, with 30 and 70 as its children, 20 as the left child of 30, and 60 as the left child of 70. Inorder prints 20, 30, 50, 60, 70. Searching for 60 takes three comparisons (50, 70, 60), and searching for 99 returns not found. After all evidence is analyzed, the scores are Faisal 22, Sana 17, Hamza 6, Waseem 4, Farah 0.
