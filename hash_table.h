#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
using namespace std;

// Hash table with separate chaining.
// Maps evidence ID -> index in workingEvidence.
// Table size 7, hash = id mod 7. Collisions go into a linked list (chain).
class HashTable {
    struct Node {
        int id;
        int index;
        Node* next;
        Node(int i, int idx, Node* n) : id(i), index(idx), next(n) {}
    };

    static const int SIZE = 7;
    Node* buckets[SIZE];     // buckets[s] = head of the chain
    int count;               // number of entries stored

    // Slot for an ID. The extra step keeps the result valid even for negative IDs.
    int hash(int id) const { return ((id % SIZE) + SIZE) % SIZE; }

public:
    HashTable() : count(0) {
        for (int i = 0; i < SIZE; i++) buckets[i] = nullptr;
    }

    ~HashTable() { clear(); }

    // Copying would make two tables own the same nodes (double free)
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    // Add an entry, or update the index if the ID already exists.
    // O(1) average (O(chain length) to check for an existing ID)
    void insert(int id, int index) {
        int slot = hash(id);

        for (Node* cur = buckets[slot]; cur != nullptr; cur = cur->next) {
            if (cur->id == id) {         // already present: update it
                cur->index = index;
                return;
            }
        }

        buckets[slot] = new Node(id, index, buckets[slot]);  // add at head of chain
        count++;
    }

    // Returns the index, or -1 if the ID is not present.
    // O(1) average, O(n) worst case (every ID in one chain)
    int search(int id) const {
        for (Node* cur = buckets[hash(id)]; cur != nullptr; cur = cur->next) {
            if (cur->id == id) return cur->index;
        }
        return -1;
    }

    // Free every chain. O(n)
    void clear() {
        for (int i = 0; i < SIZE; i++) {
            Node* cur = buckets[i];
            while (cur != nullptr) {
                Node* nextNode = cur->next;
                delete cur;
                cur = nextNode;
            }
            buckets[i] = nullptr;
        }
        count = 0;
    }

    int size() const { return count; }

    // For demos and the viva: shows every slot and its chain
    void print() const {
        for (int i = 0; i < SIZE; i++) {
            cout << "Slot " << i << ": ";
            if (buckets[i] == nullptr) cout << "(empty)";
            for (Node* cur = buckets[i]; cur != nullptr; cur = cur->next) {
                cout << cur->id << "->idx" << cur->index;
                if (cur->next != nullptr) cout << "  ->  ";
            }
            cout << "\n";
        }
    }
};

#endif
