## Hash table

- Why a hash table: it is the single ID-to-evidence path for the whole program
  (menu input, heap output, display). Lookup is O(1) average instead of O(n).
- Shared premise: evidence "arrives continuously", the same argument used for
  the heap and merge sort. The log grows, so lookup cost must not grow with it.
- Design: key = evidence ID, value = index into workingEvidence. Built on
  std::unordered_map (a hash table that resolves collisions by chaining).
- Complexity: insert, search, remove are O(1) average and O(n) worst case
  (all keys collide). Space is O(n).
- Stored data: only id -> index, not a copy of the Evidence, so the `analyzed`
  flag never goes stale.
- Integration: findEvidence() is a wrapper around search(), so
  analyzeEvidence() and undo() are unchanged.
- Stale-index risk: never sort workingEvidence in place (see sorting module).
- Future scope: rebuild the table after a resize if the array becomes growable.

Test log (input, expected, actual):
- search(101) and search(108) -> both return the correct index
- search(999) -> -1
- analyzeEvidence() and undo() behave the same after the wrapper change
