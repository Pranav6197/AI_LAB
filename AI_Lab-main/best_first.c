#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

int graph[MAX][MAX];    // adjacency matrix
int heuristic[MAX];     // heuristic values
int visited[MAX];       // visited array
int n;                  // number of nodes

// Find the unvisited node with the lowest heuristic from current's neighbors
int get_best_next(int current) {
    int best_node = -1;
    int best_h = 9999;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] && !visited[i]) {
            if (heuristic[i] < best_h) {
                best_h = heuristic[i];
                best_node = i;
            }
        }
    }
    return best_node;
}

void best_first_search(int start, int goal) {
    int current = start;

    while (true) {
        printf("Visited: %d\n", current);
        visited[current] = 1;

        if (current == goal) {
            printf("Goal %d reached!\n", goal);
            return;
        }

        int next = get_best_next(current);
        if (next == -1) {
            printf("No path to goal.\n");
            return;
        }

        current = next;
    }
}

int main() {
    // Example: graph with 6 nodes
    n = 6;

    // Adjacency matrix
    int temp_graph[6][6] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 0}
    };

    // Heuristic values to goal (node 5)
    int temp_h[] = {5, 3, 4, 6, 2, 0};

    // Initialize
    for (int i = 0; i < n; i++) {
        heuristic[i] = temp_h[i];
        visited[i] = 0;
        for (int j = 0; j < n; j++)
            graph[i][j] = temp_graph[i][j];
    }

    int start = 0, goal = 5;
    printf("Best-First Search (no priority queue) from %d to %d:\n", start, goal);
    best_first_search(start, goal);

    return 0;
}
