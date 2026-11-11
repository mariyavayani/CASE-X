#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include "common.h"

const int MAX_ROOMS = 20;

struct Graph {
    std::vector<int> adj[MAX_ROOMS];   // adj[r] = list of rooms connected to room r
    int numRooms;
};

// Fill the lists from the list of doors
inline void buildGraph(Graph& g, int numRooms, const int edges[][2], int numEdges) {
    g.numRooms = numRooms;
    for (int i = 0; i < MAX_ROOMS; i++) g.adj[i].clear();

    for (int e = 0; e < numEdges; e++) {
        int a = edges[e][0];
        int b = edges[e][1];
        g.adj[a].push_back(b);    // b is a neighbour of a
        g.adj[b].push_back(a);    // a is a neighbour of b (doors work both ways)
    }
}

// Print a route like: Entrance -> Hall -> Study
inline void printPath(const std::vector<int>& path, const Room rooms[]) {
    for (int i = 0; i < (int)path.size(); i++) {
        std::cout << rooms[path[i]].name;
        if (i < (int)path.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";
}

// BFS: prints the shortest route from start to goal
inline bool shortestRoute(const Graph& g, int start, int goal, const Room rooms[]) {
    bool visited[MAX_ROOMS] = {false};
    int parent[MAX_ROOMS];                       // the room we came from
    for (int i = 0; i < MAX_ROOMS; i++) parent[i] = -1;

    std::queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();                     // take the next room in line
        q.pop();
        for (int next : g.adj[cur]) {            // look at each connected room
            if (!visited[next]) {
                visited[next] = true;
                parent[next] = cur;              // remember how we got here
                q.push(next);                    // visit it later
            }
        }
    }

    if (!visited[goal]) return false;            // no way to get there

    // Walk back from the goal to the start, then print it the right way round
    std::vector<int> path;
    for (int r = goal; r != -1; r = parent[r]) path.push_back(r);
    std::vector<int> forward(path.rbegin(), path.rend());
    printPath(forward, rooms);
    return true;
}

// DFS: tries every door and prints each route that reaches the goal
inline void dfs(const Graph& g, int cur, int goal, bool visited[],
                std::vector<int>& path, const Room rooms[], int& count) {
    visited[cur] = true;
    path.push_back(cur);

    if (cur == goal) {
        count++;
        std::cout << "  Route " << count << ": ";
        printPath(path, rooms);
    } else {
        for (int next : g.adj[cur]) {
            if (!visited[next])
                dfs(g, next, goal, visited, path, rooms, count);
        }
    }

    path.pop_back();         // step back out of this room
    visited[cur] = false;    // so other routes can use it
}

// Prints every possible route and returns how many there are
inline int allRoutes(const Graph& g, int start, int goal, const Room rooms[]) {
    bool visited[MAX_ROOMS] = {false};
    std::vector<int> path;
    int count = 0;
    dfs(g, start, goal, visited, path, rooms, count);
    return count;
}

#endif