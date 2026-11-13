## Hash table

- Why a hash table: it is the single ID-to-evidence path for the whole program
  (menu input, heap output, display). Lookup is O(1) average instead of O(n).
- Shared premise: evidence "arrives continuously", the same argument used for
  the heap and merge sort. The log grows, so lookup cost must not grow with it.
- Design: hand-written hash table, size 7, hash = id mod 7, collisions
  resolved by separate chaining (linked list per slot). Key = evidence ID,
  value = index into workingEvidence. Evidence 101 and 108 share slot 3
  (chain length 2), which tests collision handling.
- Complexity: insert and search are O(1) average, O(n) worst case
  (all keys in one chain). Space is O(n + table size).
- Why chaining: the table never fills up, and a collision just adds a node
  to the chain.
- Stored data: only id -> index, not a copy of the Evidence, so the `analyzed`
  flag never goes stale.
- Integration: findEvidence() is a wrapper around search(), so
  analyzeEvidence() and undo() are unchanged.
- Stale-index risk: never sort workingEvidence in place (see sorting module).
- Future scope: dynamic resizing / rehashing as the load factor grows; rebuild
  the table after a resize if the array becomes growable.
  BST: insert and search are O(log n) on average and O(n) worst case (a skewed tree). Inorder traversal is O(n). Space is O(n).
  Stack: push, pop, top and isEmpty are all O(1). Space is O(n).

Test log (input, expected, actual):
- search(101) and search(108) -> both return the correct index (slot 3 chain)
- search(999) -> -1
- print() -> slot 3 shows both 101 and 108
- analyzeEvidence() and undo() behave the same after the wrapper change
