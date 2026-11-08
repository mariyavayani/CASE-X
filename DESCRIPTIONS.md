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

Graph (crime scene map). The building is modelled as a graph. Rooms are vertices and the doors and passages between them are undirected edges, stored in an adjacency list. Two traversals answer two investigation questions:

BFS (shortest route): explores room by room in widening rings using a queue, so the first time it reaches the destination is by the fewest rooms. It records each room’s parent and rebuilds the route backwards. Complexity is O(V + E).
DFS with backtracking (all possible routes): follows each path as deep as it can, never entering the same room twice on one route, then backs up and tries the next door. It lists every route a suspect could have taken.

Role in the simulator: the CCTV frame (E102) shows someone at the front door, and the broken window latch (E101) points to the Kitchen. The investigator picks an entry point, and the program shows the quickest way to the Study (Entrance, Hall, Study) and every other possible route (Entrance, Kitchen, Living Room, Hall, Study). The evidence then tells them which route fits.

Why a graph? Rooms and doors are naturally a network. A list or table can’t express “which rooms connect to which” or find routes between them.

Test result (case data): 2 possible routes from Entrance to Study, and 2 from Entrance to Bedroom, which is a dead end.
