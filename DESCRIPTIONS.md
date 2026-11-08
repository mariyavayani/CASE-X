**SORTING:**

Sorting (timeline reconstruction). Evidence is collected in random order, so this module sorts it by timestamp to rebuild the sequence of events. Bubble sort (O(n²)) and merge sort (O(n log n)) are both implemented, and their comparison counts are compared. It can also rank suspects by association score.

BUBBLE SORT FOR SUSPECTS. MERGE SORT FOR EVIDENCES IN ORDER OF TIME STAMPS

Evidence timeline, merge sort: an evidence log can grow as a case develops, and merge sort stays fast at O(n log n). It’s also stable, so two items with the same timestamp keep their collection order, which matters for a timeline.

Suspect ranking, bubble sort: a case has only a handful of suspects, so a simple O(n²) sort is plenty. The cost is irrelevant at that size, and a short, readable sort is easier to explain.

How the two fit the story: the timeline option calls mergeSort on the evidence, and the final investigation summary calls rankSuspects after the scores are computed. Expected ranking with your case data: Karan 22, Meera 17, Rohan 6, Dev 4, Anita 0. That gives you an easy test.

One thing to coordinate: rankSuspects needs the suspect scores filled in first, and the suspects live in your teammate’s BST. Agree on how you’ll get them out, for example a BST function that copies all suspects into an array, which also gives them a natural use for in-order traversal.

