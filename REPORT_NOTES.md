HASH TABLE:

Hash table (evidence lookup). Evidence records are stored in an array, and the hash table maps each evidence ID to that record's position in the array. It has 7 slots, and the slot for an ID is id mod 7. When two IDs land in the same slot (a collision), they are linked together in a chain, so nothing is overwritten. The table stores only the ID and the array position, not a copy of the evidence, so the "analyzed" flag is always read from the one real record. Insert and search both run in O(1) on average. The worst case is O(n), if every ID lands in one chain. Space is O(n + table size).

Why a hash table? Evidence arrives continuously in a real case, and every module that receives an evidence ID needs the record quickly. A loop over the array is O(n) and gets slower as the log grows. A sorted array with binary search is O(log n), but every insert needs O(n) shifting. A BST is O(log n) on average and O(n) if unbalanced, and evidence IDs have no ordering need. A hash table gives O(1) average for both, and this module only ever asks "fetch this ID".

Why chaining? The table never fills up, and a collision just adds a node to the chain.

Role in the simulator: it is the single ID-to-evidence path for the program. When the investigator analyzes or undoes evidence, findEvidence() asks the hash table for the position of that ID and works on that record.

Test result (case data): evidence 101 and 108 both land in slot 3 and form a chain of two, search(101) returns 4, search(108) returns 2, and search(999) returns -1 (not found).


STACK:

Stack (investigation trail). A stack stores the investigator's actions in the order they happened, so the most recent action is always on top (last in, first out). Each action records which evidence was analyzed and what its "analyzed" flag was beforehand. Analyzing evidence pushes an action. Undo pops the most recent one, restores the flag and subtracts the score that was added. Push, pop, top and isEmpty all run in O(1) (push is amortized O(1) because the underlying vector may occasionally resize). Space is O(n).

Why a stack? Undo must always reverse the latest action first, which is exactly last in, first out. A queue would undo the oldest action first, which is wrong. A list would also work, but it would allow access to any position, and the trail should only ever be changed at one end.

Role in the simulator: when the investigator chooses "Analyze next evidence," the evidence is marked as analyzed and the action is pushed on the stack. Choosing undo reverses the last step, so a wrong step can be taken back without restarting the case.

Test result (case data): analyzing 106 then 102 gives Sana 10 and Faisal 9. One undo removes 102 (Faisal back to 0, 102 unanalyzed), a second undo removes 106, and a third undo prints "Nothing to undo!".


BINARY SEARCH TREE:

Binary search tree (suspect lookup). Suspects are stored in a binary search tree keyed by suspect ID. Every node's left subtree holds smaller IDs and its right subtree holds larger ones, so each comparison discards half of the remaining tree. Insert and search run in O(log n) on average and O(n) in the worst case, when keys arrive in sorted order and the tree becomes a chain. Inorder traversal visits every suspect in ID order in O(n). Space is O(n).

Why a BST? A suspect is looked up by ID, and the tree keeps the suspects ordered without ever sorting them. An unsorted array needs an O(n) scan for every search, and a sorted array needs O(n) shifting to insert. A hash table gives fast lookup but no ordered traversal. A plain BST keeps the code simple, so a self-balancing AVL tree is listed as future scope.

Role in the simulator: when evidence is analyzed, the program searches the tree for the suspect it points to and adds the evidence priority to that suspect's score. The final summary collects the suspects from the tree and passes them to rankSuspects.

Test result (case data): inserting 50, 30, 70, 20, 60 gives root 50, with 30 and 70 as its children, 20 as the left child of 30, and 60 as the left child of 70. Inorder prints 20, 30, 50, 60, 70. Searching for 60 takes three comparisons (50, 70, 60), and searching for 99 returns not found. After all evidence is analyzed, the scores are Faisal 22, Sana 17, Hamza 6, Waseem 4, Farah 0.
